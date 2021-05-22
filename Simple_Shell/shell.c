#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX_LINE 80 /* The maximum length command */

// 연산자 ID 부여
int operator_id(char *str){ 
    if(strcmp(str,">") == 0) return 1;
    if(strcmp(str, "<") == 0) return 2;
    if(strcmp(str, "|") == 0) return 3;
    if(strcmp(str, "&") == 0) return 4;
    return 0;
}

// '<', '>'을 만나면 file redirecting
void redirecting(char* file, int id){
    if(id == 1){ // ‘>’ 
        int fd = open(file, O_WRONLY|O_CREAT, 0666);
        dup2(fd,STDOUT_FILENO);
        close(fd);
    }
    else if(id == 2){ // ‘<’ 
        int fd = open(file, O_RDONLY, 0666);
        dup2(fd,STDIN_FILENO);
        close(fd);
    }
}

/* command_pos의 바로 다음 명령어를 찾는 함수
 더 이상 실행할 명령어가 args에 없으면 종료.
 command_pos부터 오른쪽으로 탐색하며 '<', '>', '&', '|'을 만나면 NULL로 바꿔주고
 각각 '<', '>'은 redirection, '&', '|'은 새로 fork하여 자식 프로세서에서 command_pos 위치의 명령어
를 실행한다.
 '&', '|' 바로 오른쪽의 args 값은 명령어이기 때문에 다음 명령어 자리로 one_command를 다시 호출한다.*/
void one_command(char **args, int command_pos, int size){
    if(command_pos == size) return;

    int background = 0, is_pipe = 0, next_command = size;

    for(int i=command_pos; i<next_command; i++){
        int id = operator_id(args[i]);

        if(!id) continue;
        args[i] = NULL;

        if(id <= 2) redirecting(args[i+1],id); // <, > 
        else{
            if(id == 3) is_pipe = 1; // pipe
            else if(id == 4) background = 1; // &
            next_command = i+1; // the right of '&', '|' is command
        }
    }

    if(is_pipe){
        int state, fd[2];
        pipe(fd); 
        pid_t pid = fork();
        
        // pipe(A|B)
        if(pid < 0){
            fprintf(stderr, "Fork failed");
            return;
        }
        else if(pid > 0){ // parent(B)
            waitpid(pid, &state, 0);

            dup2(fd[0],STDIN_FILENO);
            close(fd[1]);
            one_command(args, next_command, size);
        }
        else{ // child(A)
            dup2(fd[1],STDOUT_FILENO);
            close(fd[0]);
            
            execvp(args[command_pos], &args[command_pos]);
        }
        return;
    } 
    else{
        int state;
        pid_t pid;
        pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork failed");
            return;
        }
        else if(pid > 0){ // parent
            // if background is false, wait child process terminated. 
            if(!background) waitpid(pid, &state, 0); 
            one_command(args, next_command, size);
        }
        else if(pid == 0){ // child
            execvp(args[command_pos], &args[command_pos]);
        }
        return;
    }
}

// delimiter를 기준으로 args 문자열을 자름
int parse_args(char* istream, char** args, char *delimiter){
    char *token = strtok(istream, delimiter);
    int cnt = 0;

    while(token!=NULL){
        args[cnt++] = strdup(token);
        token = strtok(NULL, delimiter);
    }

    args[cnt] = NULL;
    return cnt;
}

// args를 읽고 " ", "\n"을 기준으로 파싱한다.
int get_args(char** args){
    char istream[MAX_LINE];

    fgets(istream, sizeof(istream), stdin);
    fflush(stdout);
    return parse_args(istream, args, " \n");
}

int main(void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */

    while(should_run) { 
        printf("osh>");
        int size = get_args(args);
        if(size && strcmp(args[0], "exit") == 0) break;

        int state;
        pid_t pid;
        pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork failed");
            break;
        }
        else if(pid > 0){ // parent process
            waitpid(pid, &state, 0); 
            printf("Done\n");
        }
        else if(pid == 0){ // child process
            one_command(args, 0, size);
            break;
        } 
    }
    return 0;
}