# ๐ข Operating Systems
## **Project #1**

**์ํํธ์จ์ดํ๋ถ 2021๋ 3์ 18์ผ**
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
below illustrates the prompt osh> and the userโs next command: cat prog.c. (This command
displays the file prog.c on the terminal using the UNIX cat command.)
> <br>
> <br>
> ```
> osh> cat prog.c
> ```
> <br>
> the parent and child processes will run concurrently. The separate child process is created using the fork() system call, and the userโs command is executed using one of the system calls in the exec() family.
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

## **๋ช๋?น์ด ํ์ฑ๊ณผ ์ค๋ฅ ์ฒ๋ฆฌ**
> ์ด๋ฒ ํ๋ก์?ํธ๋ ํ๋ก์ธ์ค ์์ฑ๊ณผ ํ๋ก์ธ์ค๊ฐ ํต์?์ ์ดํดํ๋ ๊ฒ์ด ์ฃผ์ ๋ชฉ์?์ด๋ค. ์๋?ฅ๋
๋ช๋?น์ด๋ฅผ ํ์ฑํด์ ํ์์ ์ด๊ธ๋๋ ๋ช๋?น์ด ์ค๋ฅ๋ฅผ ์?์ฐํ๊ฒ ์ฒ๋ฆฌํ๋ ๊ฒ์ ํ์ํ์ง๋ง ์ด๋ฒ
์ฃผ์?์๋ ๋ณ๊ฐ์ ๋ฌธ์?์ด๋ฏ๋ก ์ฌ๊ธฐ์๋ ๊ณ?๋?คํ์ง ์๋๋ค. ๋ฌธ์?๋ฅผ ๊ฐ๋จํ๊ฒ ํ๊ธฐ ์ํด์ Simple
Shell ์ฌ์ฉ์๋ ๋ค์ ํ์์ ๋ช๋?น์ด๋ง ์ฌ๋ฐ๋ฅด๊ฒ ์ฌ์ฉํ๋ค๊ณ? ๊ฐ์?ํ๊ณ? ๋ช๋?น์ด๋ฅผ ์ค์บํ๋ค. <br>
> <br>
> โข ๋ช๋?น์ด or ๋ช๋?น์ด & <br>
> โข ๋ช๋?น์ด > ํ์ผ๋ช or ๋ช๋?น์ด > ํ์ผ๋ช & <br>
> โข ๋ช๋?น์ด < ํ์ผ๋ช or ๋ช๋?น์ด < ํ์ผ๋ช & <br>
> โข ๋ช๋?น์ด1 | ๋ช๋?น์ด2 or ๋ช๋?น์ด1 | ๋ช๋?น์ด2 & <br>
> โข exit <br>
> <br>
> ๋ง์ผ ์ ํ์์ ๋ฐ๋ฅด์ง ์์ ๋ช๋?น์ด๊ฐ ์๋?ฅ๋๋ฉด ์?์ฒด๋ฅผ ๋ฌด์ํ๊ฑฐ๋ ๋๋ ์ธ์๋ ๋ถ๋ถ๊น์ง๋ง
์ฒ๋ฆฌํ๊ณ? ๋๋จธ์ง๋ ๋ฒ๋ฆฐ๋ค. ๋ค๋ง ๋ช๋?น์ด๋ ์ต์์ ํฌํจํ? ์ ์์ด์ผ ํ๋ค.
