#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
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


int main()
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

	//initialization
	int count = 0;
	memset(in_buf, 0, MAX_USER_IN);
	for(i=0; i<MAX_NUM_ARGS; i++) {
		memset(parse_args[i], 0, MAX_ARG_LEN);
	}

	//display prompt
	printf("Command> ");

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

	printf("input:%s\n", in_buf);


	char *token = strtok(in_buf, " \n");
	int cnt = 0;

	while(token != NULL){
		for(int i=0; token[i]!='\0'; i++)
			parse_args[cnt][i] = token[i];
		cnt++;
		token = strtok(NULL, " \n");
	}

	num_args = cnt;

	printf("output:\n");
	for(i=0; i<num_args; i++) {
		printf("arg[%d]:%s\n", i, parse_args[i]);
	}

	return num_args;
}


/**
  * get parsed args (parse_args) and execute using them
  * input1: num_args (1st arg)
  * input2: parse_args (2nd args)
**/
void execute_cmd(int num_args, char parse_args[MAX_NUM_ARGS][MAX_ARG_LEN])
{
	int state, background = 0;
	pid_t pid = fork();

	char *str[num_args];
	for(int i=0; i<num_args; i++) str[i] = parse_args[i];
	
	if(num_args && strcmp(str[num_args-1],"&") == 0) num_args--, background = 1;
	str[num_args] = NULL;

	if(pid < 0){
		fprintf(stderr, "Fork failed");
		return;
	}
	else if(pid > 0){
		if(!background) waitpid(pid, &state, 0);
	}
	else{
		execvp(str[0], str);
	}
}
