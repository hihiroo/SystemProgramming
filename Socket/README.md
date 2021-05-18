# 🦄 컴퓨터 네트워크

### Project 1. C로 웹 서버 구축하기
<br>

## Instructions
```
이 프로젝트는 파트 A와 파트 B로 구성됩니다.
```

* **파트 A** : request를 콘솔로 dump하는 웹서버를 구현한다. 인터넷 익스플로러, 파이어폭스, 크롬과 같은 클라이언트 환경의 브라우저에서 서버에 연결을 요청했을 때 request 메시지를 터미널에 띄운다.

<br>

* **파트 B** : 파트 A에서 구현한 코드를 기반으로 request를 파싱하여 클라이언트에게 직접 response를 전송한다. <br>
  <br>
> **Content-Type**
> 1. HTML
> 2. GIF
> 3. JPG
> 4. MP3
> 5. PDF

<br>

## 웹 서버 열기
```bash
$ make
$ server <port number>
```
1. 브라우저에서 localhost:port number/filename 입력하여 request 전송

2. server.c와 같은 위치에 있는 파일 중에 요청하는 파일이 있는지 확인하고 파일 타입 확인 후 response
   