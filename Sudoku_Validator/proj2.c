/*
 * Copyright 2021. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니
다.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
/*
 * 기본 스도쿠 퍼즐
 */
int sudoku[9][9] = {{6,3,9,8,4,1,2,7,5},{7,2,4,9,5,3,1,6,8},{1,8,5,7,2,6,3,9,4}
,{2,5,6,1,3,7,4,8,9},{4,9,1,5,8,2,6,3,7},{8,7,3,4,6,9,5,2,1},{5,4,2,3,9,8,7,1,6
},{3,1,8,6,7,5,9,4,2},{9,6,7,2,1,4,8,5,3}};
/*
 * valid[0][0], valid[0][1], ..., valid[0][8]: 각 행이 올바르면 1, 아니면 0
 * valid[1][0], valid[1][1], ..., valid[1][8]: 각 열이 올바르면 1, 아니면 0
 * valid[2][0], valid[2][1], ..., valid[2][8]: 각 3x3 그리드가 올바르면 1, 아니면
 0
 */
int valid[3][9];
/*
 * 스도쿠 퍼즐의 각 행이 올바른지 검사한다.
 * 행 번호는 0부터 시작하며, i번 행이 올바르면 valid[0][i]에 1을 기록한다.
 */
void *check_rows(void *arg){
    for(int i=0; i<9; i++){
        int cnt[10] = {0,};
        valid[0][i] = 1; 

        for(int j=0; j<9; j++){ // columns 
            cnt[sudoku[i][j]]++; // 각 숫자가 몇 번 나왔는지 카운트
        }
        for(int j=1; j<=9; j++){ 
            if(cnt[j] != 1){ // 1부터 9까지의 숫자가 한 번씩 등장한게 아니라면
                valid[0][i] = 0; // 비정상으로 체크하고 종료
                break;
            } 
        }
    }
    pthread_exit(NULL); // 스레드 종료
}
/*
 * 스도쿠 퍼즐의 각 열이 올바른지 검사한다.
 * 열 번호는 0부터 시작하며, j번 열이 올바르면 valid[1][j]에 1을 기록한다.
 */
void *check_columns(void *arg){
    for(int i=0; i<9; i++){ 
        int cnt[10] = {0,};
        valid[1][i] = 1;

        for(int j=0; j<9; j++){ // rows
            cnt[sudoku[j][i]]++; // 각 숫자가 몇 번 나왔는지 카운트
        }
        for(int j=1; j<=9; j++){
            if(cnt[j] != 1){ // 1부터 9까지의 숫자가 한 번씩 등장한게 아니라면
                valid[1][i] = 0; // 비정상으로 체크하고 종료
                break;
            }
        }
    }
    pthread_exit(NULL); // 스레드 종료
}
/*
 * 스도쿠 퍼즐의 각 3x3 서브그리드가 올바른지 검사한다.
 * 3x3 서브그리드 번호는 0부터 시작하며, 왼쪽에서 오른쪽으로, 위에서 아래로 증가한다.
 * k번 서브그리드가 올바르면 valid[2][k]에 1을 기록한다.
 */
void *check_subgrid(void *arg){
    int id = *(int *)arg; // subgrid ID로 0~8 숫자
    int i = 3*(id/3); // subgrid의 시작 행 번호
    int j = 3*(id%3); // subgrid의 시작 열 번호
    int cnt[10] = {0,};

    for(int di=0; di<3; di++){ 
        for(int dj=0; dj<3; dj++){
            cnt[sudoku[i+di][j+dj]]++; // subgrid의 숫자 등장 횟수 카운트
        }
    }
 
    valid[2][id] = 1; 

    for(int n=1; n<=9; n++){
        if(cnt[n] != 1){ // 1~9까지의 숫자가 한 번씩 등장한게 아니라면
            valid[2][id] = 0; // 비정상으로 체크하고 종료
            break;
        }
    }
    pthread_exit(NULL); // 스레드 종료
}
/*
 * 스도쿠 퍼즐이 올바르게 구성되어 있는지 11개의 스레드를 생성하여 검증한다.
 * 한 스레드는 각 행이 올바른지 검사하고, 다른 한 스레드는 각 열이 올바른지 검사한다.
 * 9개의 3x3 서브그리드에 대한 검증은 9개의 스레드를 생성하여 동시에 검사한다.
 */
void check_sudoku(void){
    int i, j;
 
    /*
    * 검증하기 전에 먼저 스도쿠 퍼즐의 값을 출력한다.
    */
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j)
            printf("%2d", sudoku[i][j]);
        printf("\n");
    }
    printf("---\n");

    /*
    * 스레드를 생성하여 각 행을 검사하는 check_rows() 함수를 실행한다.
    */
    pthread_t tid[11];

    if (pthread_create(&tid[9], NULL, check_rows, NULL) != 0) {
        fprintf(stderr, "pthread_create error: check_rows\n");
        exit(-1);
    }

    /*
    * 스레드를 생성하여 각 열을 검사하는 check_columns() 함수를 실행한다.
    */
    if (pthread_create(&tid[10], NULL, check_columns, NULL) != 0) {
        fprintf(stderr, "pthread_create error: check_columns\n"); 
        exit(-1);
    }

    /*
    * 9개의 스레드를 생성하여 각 3x3 서브그리드를 검사하는 check_subgrid() 함수를
    실행한다.
    * 3x3 서브그리드의 위치를 식별할 수 있는 값을 함수의 인자로 넘긴다.
    */
    int subgrid_id[9];
    for(int i=0; i<9; i++){
        subgrid_id[i] = i;
        if (pthread_create(&tid[i], NULL, check_subgrid, &subgrid_id[i]) != 0){
            fprintf(stderr, "pthread_create error: check_subgrid %d\n",i);
            exit(-1);
        }
    }

    /*
    * 11개의 스레드가 종료할 때까지 기다린다.
    */
    for(int i=0; i<11; i++) 
        pthread_join(tid[i], NULL);

    /*
    * 각 행에 대한 검증 결과를 출력한다.
    */
    printf("ROWS: ");
    for (i = 0; i < 9; ++i)
        printf(valid[0][i] == 1 ? "(%d,YES)" : "(%d,NO)", i);
    printf("\n");

    /*
    * 각 열에 대한 검증 결과를 출력한다.
    */
    printf("COLS: ");
    for (i = 0; i < 9; ++i)
        printf(valid[1][i] == 1 ? "(%d,YES)" : "(%d,NO)", i);
    printf("\n");

    /*
    * 각 3x3 서브그리드에 대한 검증 결과를 출력한다.
    */
    printf("GRID: ");
    for (i = 0; i < 9; ++i)
        printf(valid[2][i] == 1 ? "(%d,YES)" : "(%d,NO)", i);
    printf("\n---\n");
}

/*
 * 스도쿠 퍼즐의 값을 3x3 서브그리드 내에서 무작위로 섞는 함수이다.
 */
void *shuffle_sudoku(void *arg){ 
    int i, tmp;
    int grid;
    int row1, row2;
    int col1, col2;
 
    srand(time(NULL));
    for (i = 0; i < 100; ++i) {
        /*
        * 0부터 8번 사이의 서브그리드 하나를 무작위로 선택한다.
        */
        grid = rand() % 9;
        /*
        * 해당 서브그리드의 좌측 상단 행열 좌표를 계산한다.
        */
        row1 = row2 = (grid/3)*3;
        col1 = col2 = (grid%3)*3;
        /*
        * 해당 서브그리드 내에 있는 임의의 두 위치를 무작위로 선택한다.
        */
        row1 += rand() % 3; col1 += rand() % 3;
        row2 += rand() % 3; col2 += rand() % 3;
        /*
        * 홀수 서브그리드이면 두 위치에 무작위 수로 채우고,
        */
        if (grid & 1) {
            sudoku[row1][col1] = rand() % 8 + 1;
            sudoku[row2][col2] = rand() % 8 + 1;
        }
        /*
        * 짝수 서브그리드이면 두 위치에 있는 값을 맞바꾼다.
        */
        else {
            tmp = sudoku[row1][col1];
            sudoku[row1][col1] = sudoku[row2][col2];
            sudoku[row2][col2] = tmp;
        }
    }
    pthread_exit(NULL);
}

/*
 * 메인 함수는 위에서 작성한 함수가 올바르게 동작하는지 검사하기 위한 것으로 수정하면
안 된다.
 */
int main(void){
    int tmp;
    pthread_t tid;
    
    /*
    * 기본 스도쿠 퍼즐을 출력하고 검증한다. */
    check_sudoku();
    /*
    * 기본 퍼즐에서 값 두개를 맞바꾸고 검증해본다.
    */
    tmp = sudoku[5][3]; sudoku[5][3] = sudoku[6][2]; sudoku[6][2] = tmp;
    check_sudoku();
    /*
    * 기본 스도쿠 퍼즐로 다시 바꾼 다음, shuffle_sudoku 스레드를 생성하여 퍼즐을 섞
    는다.
    */
    tmp = sudoku[5][3]; sudoku[5][3] = sudoku[6][2]; sudoku[6][2] = tmp;
    if (pthread_create(&tid, NULL, shuffle_sudoku, NULL) != 0) {
        fprintf(stderr, "pthread_create error: shuffle_sudoku\n");
        exit(-1);
    }
    /*
    * 무작위로 섞는 중인 스도쿠 퍼즐을 검증해본다.
    */
    check_sudoku();
    /*
    * shuffle_sudoku 스레드가 종료될 때까지 기다란다.
    */
    pthread_join(tid, NULL);
    /*
    * shuffle_sudoku 스레드 종료 후 다시 한 번 스도쿠 퍼즐을 검증해본다.
    */
    check_sudoku();
    exit(0);
}