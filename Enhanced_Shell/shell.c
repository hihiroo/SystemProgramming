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

	switch(pid)
	{
		case -1:
			perror("Fork Error");
			break;
		case 0:
			execvp(args[0], args);
			break;
		default:
			waitpid(pid,&status,0);
	}
}
