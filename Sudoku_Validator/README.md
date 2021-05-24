# 🌴 Operating Systems
## **Project #2**

**소프트웨어학부 2021년 4월 1일**
<br><br>

```
This project consists of designing a multithreaded application that determines whether the solution to a 9x9 grid Sudoku puzzle is valid.
```
<br>

There are several different ways of multithreading this application. One suggested strategy is to create threads that check the follwing criteria: <br>

> • A thread to check that each column contains the digits 1 through 9 <br>
> • A thread to check that each row contains the digits 1 through 9 <br>
> • Nine threads to check that each of the 3 × 3 subgrids contains the digits 1 through 9

<br>

## **골격 파일**
이번 프로그래밍 프로젝트는 골격 파일인 proj2.skeleton.c를 학생들에게 제공한다. 학생들은 골격 파일 내에 미완성으로 남아 있는 몇 개의 함수를 목적에 맞게 완성해야 하는데, 그 함수의 목록은 다음과 같다. <br>

>• void *check_rows(void *arg): 스도쿠 퍼즐의 9개 행의 구성이 올바른지 검사하는 함수이다. 하나의 스레드가 이 함수를 수행하게 한다. 매개변수 arg는 사용하지 않는다. <br><br>
>
>• void *check_columns(void *arg): 스도쿠 퍼즐의 9개 열의 구성이 올바른지 검사하는 함수이다. 하나의 스레드가 이 함수를 수행하게 한다. 매개변수 arg는 사용하지 않는다.<br><br>
>
>• void *check_subgrid(void *arg): 스도쿠 퍼즐의 3 × 3 서브그리드의 구성이 올바른지 9개 서브그리드 중 어느 하나를 검사하는 함수이다. 어떤 위치에 있는 서브그리드를 검사할 것인지는 매개변수 arg를 통해 정보를 전달한다. 이 함수를 사용하여 9개의 스레드가 각기 다른 위치에 있는 서브그리드의 구성을 검사하게 한다. <br><br>
>
>• void check_sudoku(void): 스도쿠 퍼즐이 올바르게 구성되어 있는지 11개의 스레드를 생성하여 검증한다. 한 스레드는 각 행이 올바른지 검사하고, 다른 한 스레드는 각 열이 올바른지 검사한다. 9개의 3x3 서브그리드에 대한 검증은 9개의 스레드를 생성하여 동시에 검사한다.
