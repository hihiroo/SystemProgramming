# 🐇 2021 ERICA 시스템 프로그래밍

```
2021 소프트웨어학부 전공 운영체제론, 시스템프로그래밍 강의에서 다루는 내용 및 과제
```

모든 코드는 Linux(Ubuntu) & macOS 환경에서 실행됩니다.

<br>

## 운영체제
[**Reader-Writer Problem**](https://github.com/hihiroo/SystemProgramming/tree/master/Reader_Writer_Problem)
> 멀티 스레딩으로 Reader와 Writer를 실행했을 때 Reader끼리는 최대한 중복을 허용하고, Writer는 다른 Writer나 Reader가 끼어들 수 없도록 한다. 이때 스레드의 우선순위를 정하는 방법에 따라 Reader선호, Writer선호, Fair-reader-writer, 세 가지 방식으로 구현해본다.

<br>

[**Unix Simple Shell 만들기**](https://github.com/hihiroo/SystemProgramming/tree/master/Simple_Shell)
> Unix 기반의 간단한 shell을 만들어본다. execvp를 이용하여 입력된 명령어를 실행하고, &, >, <, |을 올바르게 처리할 수 있어야 한다.

<br>

[**Sudoku Validator**](https://github.com/hihiroo/SystemProgramming/tree/master/Sudoku_Validator)
> 멀티스레드를 이용하여 9X9 스도쿠를 검증하는 코드를 작성한다. 열과 행, 9개의 서브그리드, 총 11개의 스레드를 동시에 실행한다.

<br>

[**Cigarette Smokers Problem**](https://github.com/hihiroo/SystemProgramming/tree/master/Cigarette_Smokers_Problem)
> 3명의 흡연자는 각각 하나의 재료를 가지고 있고 담뱃잎, 종이, 불, 3가지 재료가 모두 모이면 흡연을 할 수 있다. 공급자는 2개의 재료를 무작위로 제공하고 흡연자가 흡연을 끝낼 때까지 기다린다. 세마포를 사용하여 공급자가 흡연자에게 재료를 공급하는 코드를 구현하고 발생하는 문제와 원인을 분석한다.

<br>

[**Thread Pool**](https://github.com/hihiroo/SystemProgramming/tree/master/Thread_Pool)
> 스레드 풀을 만들고 관리하는 프로그램을 만든다. 대기열에 있는 작업을 하나씩 꺼내서 스레드 풀에 있는 스레드에 할당한다.


<br>

## 시스템 프로그래밍
[**Mini Shell 만들기**](https://github.com/hihiroo/SystemProgramming/tree/master/Mini_Shell)
> Unix Simple Shell 프로젝트와 동일하지만 뼈대 코드가 더 완성도 있게 주어져 비교적 쉽다.