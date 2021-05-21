# 🐇 2021 ERICA 시스템 프로그래밍

```
2021 소프트웨어학부 전공 운영체제론, 시스템프로그래밍, 컴퓨터네트워크 강의에서 다루는 내용 및 과제
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

## 컴퓨터 네트워크
[**C로 웹 서버 구축하기**](https://github.com/hihiroo/SystemProgramming/tree/master/Socket)
> C언어로 직접 소켓을 열어 웹 서버를 구축해본다. Chrome이나 Firefox같은 웹 브라우저로부터 html, jpg, mp3, pdf 등의 파일을 요청받으면 request massage를 분석하여 해당 파일을 response할 수 있어야 한다.

<br>

