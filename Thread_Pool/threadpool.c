/*
 * Copyright 2021. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include "threadpool.h"

/*
 * 스레드 풀의 FIFO 대기열 길이와 일꾼 스레드의 갯수를 지정한다.
 */
#define QUEUE_SIZE 10
#define NUMBER_OF_BEES 3

/*
 * 스레드를 통해 실행할 작업 함수와 함수의 인자정보 구조체 타입
 */
typedef struct {
    void (*function)(void *p);
    void *data;
} task_t;

/*
 * 스레드 풀의 FIFO 대기열인 worktodo 배열로 원형 버퍼의 역할을 한다.
 */
static task_t worktodo[QUEUE_SIZE];
int front, rear, cnt; // 원형 큐의 front, rear, 큐 사이즈
/*
 * mutex는 대기열을 조회하거나 변경하기 위해 사용하는 상호배타 락이다.
 */
static pthread_mutex_t mutex;

/*
 * 대기열에 새 작업을 넣는다.
 * enqueue()는 성공하면 0, 꽉 차서 넣을 수 없으면 1을 리턴한다.
 */

static int isFull(){
    return cnt == QUEUE_SIZE;
}

static int isEmpty(){
    return cnt == 0;
}

static int enqueue(task_t t)
{
     if(isFull()) return 1;
     rear = (rear+1) % QUEUE_SIZE;
     worktodo[rear] = t;
     cnt++;

     return 0;
}

/*
 * 대기열에서 실행을 기다리는 작업을 꺼낸다.
 * dequeue()는 성공하면 0, 대기열에 작업이 없으면 1을 리턴한다.
 */
static int dequeue(task_t *t)
{
    if(isEmpty()) return 1;
    front = (front+1) % QUEUE_SIZE;
    *t = worktodo[front];
    cnt--;
    return 0;
}

/*
 * bee는 작업을 수행하는 일꾼 스레드의 ID를 저장하는 배열이다.
 * 세마포 sem은 카운팅 세마포로 그 값은 대기열에 입력된 작업의 갯수를 나타낸다.
 */
static pthread_t bee[NUMBER_OF_BEES];
static sem_t *sem;

/*
 * 풀에 있는 일꾼 스레드로 FIFO 대기열에서 기다리고 있는 작업을 하나씩 꺼내서 실행한다.
 */
static void *worker(void *param)
{
    while(1){
        sem_wait(sem); // 대기열에 작업이 있는 경우 실행
        
        task_t task; 

        pthread_mutex_lock(&mutex);
        int failed = dequeue(&task);
        pthread_mutex_unlock(&mutex);
        
        if(!failed) task.function(task.data);
    }
    pthread_exit(0);
}

/*
 * 스레드 풀에서 실행시킬 함수와 인자의 주소를 넘겨주며 작업을 요청한다.
 * pool_submit()은 작업 요청이 성공하면 0을, 그렇지 않으면 1을 리턴한다.
 */
int pool_submit(void (*f)(void *p), void *p)
{
    task_t task = {.function = f, .data = p};

    pthread_mutex_lock(&mutex);
    int failed = enqueue(task); // 대기열에 실행할 함수 push
    if(!failed) sem_post(sem);
    pthread_mutex_unlock(&mutex);

    return failed;
}

/*
 * 각종 변수, 락, 세마포, 일꾼 스레드 생성 등 스레드 풀을 초기화한다.
 */
void pool_init(void)
{
    front = -1, rear = -1, cnt = 0; // 큐 비우기
    pthread_mutex_init(&mutex, NULL); 
    sem = sem_open("sem", O_CREAT, 0644, 0);

    for(int i=0; i<NUMBER_OF_BEES; i++){
        pthread_create(&bee[i],NULL,worker,NULL);
    }
}

/*
 * 현재 진행 중인 모든 일꾼 스레드를 종료시키고, 락과 세마포를 제거한다.
 */
void pool_shutdown(void)
{
    for(int i=0; i<NUMBER_OF_BEES; i++){
        pthread_cancel(bee[i]);
    }

    pthread_mutex_destroy(&mutex);
    sem_close(sem); 
    sem_unlink("sem");
}
