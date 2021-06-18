#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_USER_IN 100
#define MAX_NUM_ARGS 5
#define MAX_ARG_LEN 20

//put string user types 
static char in_buf[MAX_USER_IN];
//parse the string to arguments
static char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN];

//given code; keyboard input to buffer
int user_in ();
//your implementation: buffer (1t arg) to parsed args (2nd arg)
int parse_cmd (char* in_buf, char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN]);
//your implementation: execute using parsed args (2nd args)
void execute_cmd (int num_args, char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN]);


void main()
{
	int num_args;

	while((num_args = user_in()) != EOF)
	{
		execute_cmd(num_args, parse_args);
	}
	printf("\n");
}


int user_in ()
{
	int c, i;
	char cwd[1024];

	//initialization
	int count = 0;
	memset(in_buf, 0, MAX_USER_IN);
	for(i=0; i<MAX_NUM_ARGS; i++) {
		memset(parse_args[i], 0, MAX_ARG_LEN);
	}

	//display current directory prompt
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s$ ", cwd);

	//fill in_buf from user input
	while(1)
	{
		//get a character 
		c = getchar();
		in_buf[count] = c;
	
		//ctrl+D, then exit
		if(c  == EOF) {
			return EOF;
		}
	
		//return, then stop user input
		if(c == '\n') {
			in_buf[count] = '\0';
			break;
		}

		count ++;
	}

	//call parse_cmd()
	int num_args = parse_cmd(in_buf, parse_args);

	return num_args;
}


/**
  * get a string (in_buf) and parse it into multiple arguments (parse_args) 
  * input: in_buf (1st arg)
  * output1: parse_args (2nd args)
  * output2: num_args (return val)
**/
int parse_cmd(char *in_buf, char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN])
{
	int i = 0;
	int num_args = MAX_NUM_ARGS;

	char *tok;

	//printf("input:%s\n", in_buf);

	tok = strtok(in_buf, " ");

	while (tok != NULL)
	{
		strcpy(parse_args[i++], tok);
		tok = strtok(NULL," ");
	}

	num_args = i;

	//printf("output:\n");
	//for(i=0; i<num_args; i++) {
	//	printf("arg[%d]:%s\n", i, parse_args[i]);
	//}

	return num_args;
}


/**
  * get parsed args (parse_args) and execute using them
  * input1: num_args (1st arg)
  * input2: parse_args (2nd args)
**/
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

void execute_cmd(int num_args, char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN])
{
	int i = 0;
	int status;
	char *args[num_args+1];
	pid_t pid;

	for (;i < num_args;i++)
		args[i] = parse_args[i];

	args[i] = NULL;

	pid = fork();

	for(int i=0; i<num_args; i++){
		if(strcmp(args[i], "cd") == 0) chdir(args[i+1]);
	}

	switch(pid)
	{
		case -1:
			perror("Fork Error");
			break;
		case 0:
			one_command(args,0,num_args);
			exit(0);
		default:
			waitpid(pid,&status,0);
	}
}
