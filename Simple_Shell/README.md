# 🐢 Operating Systems
## **Project #1**

**소프트웨어학부 2021년 3월 18일**
<br><br>

## **UNIX Simple Shell**
>This project consists of designing a C program to serve as a shell interface that accepts user
commands and then executes each command in a separate process. Your implementation will
support input and output redirection, as well as pipes as a form of IPC between a pair of commands.
Completing this project will involve using the UNIX fork(), exec(), wait(), dup2(), and
pipe() system calls and can be completed on any Linux, UNIX, or macOS system.

<br>

## **Overview**
>A shell interface gives the user a prompt, after which the next command is entered. The example
below illustrates the prompt osh> and the user’s next command: cat prog.c. (This command
displays the file prog.c on the terminal using the UNIX cat command.)
> <br>
> <br>
> ```
> osh> cat prog.c
> ```
> <br>
> the parent and child processes will run concurrently. The separate child process is created using the fork() system call, and the user’s command is executed using one of the system calls in the exec() family.
> <br>
> <br>
> A C program that provides the general operations of a command-line shell is supplied in Figure 1. The main() function presents the prompt osh> and outlines the steps to be taken after input from the user has been read. The main() function continually loops as long as should_run equals 1; when the user enters exit at the prompt, your program will set should_run to 0 and terminate
> <br>
> <br>
> This project is organized into several parts:
> <br>
> 1. Creating the child process and executing the command in the child <br>
> 2. Adding support of input and output redirection <br>
> 3. Allowing the parent and child processes to communicate via a pipe

<br>

```c
#include <stdio.h>
#include <unistd.h>
#define MAX LINE 80 /* The maximum length command */
int main(void)
{
char *args[MAX LINE/2 + 1]; /* command line arguments */
int should run = 1; /* flag to determine when to exit program */
while (should run) {
printf("osh>");
fflush(stdout);
/**
* After reading user input, the steps are:
* (1) fork a child process using fork()
* (2) the child process will invoke execvp()
* (3) parent will invoke wait() unless command included &
*/
}
return 0;
}
```
Figure 1: Outline of simple shell

<br>

## **명령어 파싱과 오류 처리**
> 이번 프로젝트는 프로세스 생성과 프로세스간 통신을 이해하는 것이 주요 목적이다. 입력된
명령어를 파싱해서 형식에 어긋나는 명령어 오류를 유연하게 처리하는 것은 필요하지만 이번
주제와는 별개의 문제이므로 여기서는 고려하지 않는다. 문제를 간단하게 하기 위해서 Simple
Shell 사용자는 다음 형식의 명령어만 올바르게 사용한다고 가정하고 명령어를 스캔한다. <br>
> <br>
> • 명령어 or 명령어 & <br>
> • 명령어 > 파일명 or 명령어 > 파일명 & <br>
> • 명령어 < 파일명 or 명령어 < 파일명 & <br>
> • 명령어1 | 명령어2 or 명령어1 | 명령어2 & <br>
> • exit <br>
> <br>
> 만일 앞 형식을 따르지 않은 명령어가 입력되면 전체를 무시하거나 또는 인식된 부분까지만
처리하고 나머지는 버린다. 다만 명령어는 옵션을 포함할 수 있어야 한다.
