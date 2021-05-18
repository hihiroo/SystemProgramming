/* 
   A simple server in the internet domain using TCP
   Usage:./server port (E.g. ./server 10000 )
*/
#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void parsing(char *buffer, char** arg){
   // http 리퀘스트 메시지에서 url 파싱
   // arg[0] = filename, arg[1] = filetype

   int s = 0, f = 0, m = 0; 
   while(buffer[s] != '/') s++;
   f = ++s;
   while(buffer[f] != ' '){
      if(buffer[f] == '.') m = f;
      f++;
   }
   
   char url[f-s+1];
   for(int i=0; i<f-s; i++) url[i] = buffer[s+i];
   if(s != f) arg[2] = strdup(url);
   else arg[2] = NULL;

   char *tmp;
   tmp = strtok(url, ". ");
   if(s != f){
      arg[0] = strdup(tmp);
      tmp = strtok(NULL, ". ");
   }
   else arg[0] = NULL;

   if(tmp != NULL) arg[1] = strdup(tmp);
   else arg[1] = NULL;
}

int makeResponse(int newsockfd, char **arg){
   char path[3000], message[1000000] = "";
   getcwd(path,3000);
   DIR *dir_ptr = opendir(path);
   struct dirent *file;

   while(arg[2] != NULL && (file = readdir(dir_ptr)) != NULL){
      if(strcmp(file->d_name, arg[2]) == 0){
         strcat(message, "HTTP/1.1 200 OK\nAccept_Ranges: bytes\nContent-Type: ");

         printf("%s %s\n", file->d_name, arg[2]);
         if(strcmp(arg[1], "html") == 0){
            strcat(message,"text/html; charset=utf-8\n\n");
            FILE *fp = fopen(file->d_name,"r");
            char str[1000];

            while(fgets(str,sizeof(str),fp)) strcat(message,str);
            fclose(fp);

            write(newsockfd,message,strlen(message));
         }
         else{
            if(strcmp(arg[1], "gif") == 0){
               strcat(message,"image/gif\n\n");
            }
            else if(strcmp(arg[1], "pdf") == 0){
               strcat(message,"application/pdf\n\n");
            }
            else if(strcmp(arg[1], "jpg") == 0){
               strcat(message,"image/jpg\n\n");
            }
            else if(strcmp(arg[1], "jpeg") == 0){
               strcat(message,"image/jpeg\n\n");
            }
            else if(strcmp(arg[1], "mp3") == 0){
               strcat(message,"audio/mp3\nContent-Disposition: inline\n\n");
            }

            FILE *fp = fopen(file->d_name,"rb");
            fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
            int size = ftell(fp);  // 파일 포인터의 현재 위치를 얻음    
            fseek(fp, 0, SEEK_SET); // 다시 파일 포인터를 처음으로 올긴다.
      
            char *reply = (char*)malloc(strlen(message)+size);
            strcat(reply, message);
            while(1){
               unsigned char buff[size+1];
               bzero(buff,size+1);
               int now_read = fread(buff,1,size,fp);
               
               if(now_read > 0){
                     memcpy(reply+strlen(message), buff, size);
               }
               if (now_read <= size){
                     break;
               }
            }
            write(newsockfd, reply, strlen(message)+size);
            fclose(fp);
         }
         return 0;
      }
   }
   
   strcat(message, "HTTP/1.1 404 Not Found\nContent-type: text/html\n\n<html>\n\t<body>\n\t\t<h1>Not Found</h1>\n\t\t<p>The requested URL was not found on this server.</p>\n\t</body>\n</html>\n");
   return -1;
}

int main(int argc, char *argv[])
{  
   int sockfd, newsockfd; //descriptors rturn from socket and accept system calls
   int portno; // port number
   socklen_t clilen;
   
   char buffer[4096];
   
   /*sockaddr_in: Structure Containing an Internet Address*/
   struct sockaddr_in serv_addr, cli_addr;
   
   int n;
   // 만약 파일 실행시 들어온 인자가 2개 미만이면 에러
   if (argc < 2) {
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
   }
   
   /*Create a new socket
      AF_INET: Address Domain is Internet 
      SOCK_STREAM: Socket Type is STREAM Socket */
      // SOCK_STREAM은 TCP를 위한 타입
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) 
      error("ERROR opening socket");
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]); //atoi converts from String to Integer
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY; //for the server the IP address is always the address that the server is running on
   serv_addr.sin_port = htons(portno); //convert from host to network byte order
   
   // 소켓에 ip와 포트번호 부여
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //Bind the socket to the server address
            error("ERROR on binding");
   
   listen(sockfd,5); // Listen for socket connections. 
   //Backlog queue (connections to wait) is 5

   clilen = sizeof(cli_addr);
   /*accept function: 
      1) Block until a new connection is established
      2) the new socket descriptor will be used for subsequent communication with the newly connected client.
   */

   while(1){
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0) 
            error("ERROR on accept");

      bzero(buffer,4096);
      n = read(newsockfd,buffer,4095); //Read is a block function. It will read at most 255 bytes
      if (n < 0) error("ERROR reading from socket");
         printf("Here is the message: %s\n",buffer);

      // filename, type parsing
      // arg[0] = filename, arg[1] = filetype
      char *arg[3];
      parsing(buffer, arg);
      makeResponse(newsockfd, arg);

      close(newsockfd);
   }
   close(sockfd);
   return 0; 
}
