# Operating Systems 
## **Project #3**

**소프트웨어학부 2021년 5월 6일**
<br><br>

## Reader-Writer 문제
>Reader와 writer가 공유자원에 접근할 때, reader는 다른 reader와 동시에 접근할 수 있다. 하지만 writer가 다른 writer나 reader와 동시에 접근하면 문제가 발생할 수 있는 것을 reader-writer 문제라고 한다. 이 문제를 해결하기 위한 해법에는 reader 선호, writer 선호, 공정한 reader-writer, 세가지가 있다. 어떤 방식이든 모두 writer에게는 상호배타를 보장하고, reader에게는 다른 reader와 최대한 중복을 허용하는 것을 목표로 한다.

<br>

## Reader 선호
>수업시간에 배운 해법으로 CS(Critical Section; 임계구역)에 reader가 있으면 다른 reader가 중복해서 들어갈 수 있다. 그러나 이 방식은 늦게 온 reader가 기다리고 있는 writer를 앞지를 수 있어서 writer가 굶주릴 수 있다. 특히 reader의 수가 상대적으로 많은 환경에서는 writer가 기회조차 얻지 못하는 경우가 발생할지도 모른다.

<br>

## Writer 선호
>Reader의 중복을 최대한 허용하되 기다리는 writer가 있으면 reader가 더 이상 writer를 앞지르지 못하게 하는 방식이다. 뿐만 아니라 늦게 온 writer는 기다리고 있는 reader를 앞지를 수 있어서 이번에는 reader가 굶주릴 수 있다. 이러한 방식을 writer 선호라 부르고, writer의 수가 상대적으로 적은 환경에서 유리하다.

<br>

## 공정한 reader-writer
>Reader 선호 방식이나 writer 선호 방식은 어느 한 쪽이 굶주릴 수 있다. 공정한 reader-writer는 선착순으로 CS에 들어가면서 reader의 중복을 최대한 허용하는 방식이다. 이 방식에서는 늦게온 reader/writer가 기다리고 있는 다른 reader/writer를 앞지르지 못한다.

<br>

## **과제 요구사항**
>시스템에 10개의 reader 스레드와 3개의 writer 스레드가 있다. 각 스레드는 CS에 들어가서 필요한 공유자원을 읽거나 쓴다. 13개의 스레드가 올바르게 동기화하며 동작할 수 있도록 앞에서 언급한 writer 선호 방식과 공정한 reader-writer 방식을 사용하여 reader-writer 문제를 푼다. 스레드가 CS에 들어가면 가상 공유자원을 접근한다고 가정하고, 스레드가 CS에 들어왔다는 것을 보이기 위해 다음과 같은 문자나 문자열을 출력한다. (주의: 출력 결과를 올바르게 보려면 큰 화면을 사용해야 한다.) <br> 
<br>
> • Reader가 CS에 들어가면 첫 번째 reader는 A 문자를, 두 번째 reader는 B 문자를, ..., 이런식으로 각 reader는 같은 문자를 8192개 출력하고 CS를 빠져나온다.
<br>
• Writer가 CS에 들어가면 어떤 배열에 저장된 얼굴 이미지를 출력한다. 출력이 끝나면 CS를 빠져나온다.
<br>
<br>
>앞에서 요구한 reader와 writer는 proj3.skeleton.c라는 골격파일에 이미 구현이 된 상태로
학생들에게 제공된다. 다만 CS 접근을 통제할 수 있는 스레드 동기화 코드가 빠져있다. 이 골
격파일을 사용하여 reader-writer 문제를 푸는 두 가지 방식을 설계하고, POSIX pthread API를
사용하여 구현한다.

<br>

## 동기화 도구
> 학생들은 POSIX의 mutex lock을 사용해서 두 가지 해법을 구현할 수 있다. 코딩해야 하는 양이 많지는 않지만 병행 프로그램의 특성상 오류를 범하기 쉽고, 디버깅하기가 다소 까다롭다. 어쩌면 생각했던 것보다 시간이 더 걸릴지도 모른다. POSIX pthread는 모니터를 제공하지는 않지만 조건변수를 제공한다. 이 POSIX 조건변수를 사용하여 writer 선호 해법을 구현할 수도 있다. 다만 조건변수를 사용하여 공정한 reader-writer 방식을 구현하는 것은 어려울 수 있다. 선택은
학생들의 몫으로 남겨 둔다.

<br>

## proj3.skeleton.c
> 앞에서 언급한 것처럼 골격파일에는 reader와 writer가 이미 구현되어 있다. 이 골격파일을 컴파일해서 실행하면 약 0.2초 동안 13개의 스레드가 동기화 없이 각자 출력을 쏟아내고 종료한다. 컴퓨터 성능에 따라 차이가 있겠지만 13개의 스레드가 최대 1MB까지 문자를 출력할 수 있다.

<br>

## **제출물**
> Reader-writer 문제에 대한 두 가지 해법이 잘 설계되고 구현되었다는 것을 보여주는 자료를 각자가 판단하여 PDF로 묶어서 이름_학번_PROJ3.pdf로 제출한다. 여기에는 다음과 같은 것이 반드시 포함되어야 한다.
> <br>
> <br>
> • 본인이 설계한 writer 선호, 공정한 reader-writer 알고리즘 (2쪽 이내)<br>
> • 프로그램 소스파일 2개 (fair_reader_writer.c, writer_prefer.c)<br>
> • 컴파일 과정을 보여주는 화면 캡처<br>
> • 실행 결과물의 주요 장면을 발췌해서 그에 대한 설명 및 차이점 등<br>
> <br>
> 다만 두 해법을 실행한 결과는 그 크기가 방대하기 때문에 별도의 파일로 저장하여 제출한다. 파일의 이름은 fair_reader_writer.txt와 writer_prefer.txt로 명한다.

