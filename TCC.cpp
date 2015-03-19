#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include        <time.h>
#define SA      struct sockaddr
#include <stdio.h>
#include <regex.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <math.h>
#include <netdb.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>

void            ReadFromKeyBoard(int sockfd);
void            ReadFromSocket(int sockfd);

void SIGhandler(int sig);


using namespace std;


int chatPort=10907;
int infoPort=10908;
int
main(int argc, char **argv)
{

    int             sockfd;
    int             pid;
    struct sockaddr_in servaddr;
    struct hostent *hp, *gethostbyname(const char *name);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof (servaddr));
    hp = gethostbyname("localhost");
    bcopy(hp->h_addr, &(servaddr.sin_addr.s_addr), hp->h_length);

    signal(SIGINT, SIGhandler);


       servaddr.sin_family = AF_INET;
       servaddr.sin_port = htons(chatPort);

       if (connect(sockfd, (SA *) & servaddr, sizeof(servaddr)) < 0) {
           perror("connect error");
           exit(-1);
       }

       pid = fork();
       if (pid == 0) {
           ReadFromKeyBoard(sockfd);
           kill(getppid(), 9);
       } else {
           ReadFromSocket(sockfd);
           kill(pid, 9);
       }
   }


void ReadFromKeyBoard(int sockfd)
   {

       int             nread;
       char            buffer[512];
       for (;;) {
           nread = read(0, buffer, 512);
           if (nread == 0)
               break;
           write(sockfd, buffer, nread);
       }
   }

void ReadFromSocket(int sockfd)
   {

       int             nread;
       char            buffer[512];
       for (;;) {
           nread = read(sockfd, buffer, 512);
           if (nread == 0)
               break;
           write(1, buffer, nread);
       }
   }

 void SIGhandler(int sig)
    {


 	   struct sockaddr_in  info;
 	   struct hostent *hp, *gethostbyname(const char *name);

 	   int sockfd = socket(AF_INET, SOCK_STREAM, 0);

 	   memset(&info, 0, sizeof (info));
 	   hp = gethostbyname("localhost");
 	   bcopy(hp->h_addr, &(info.sin_addr.s_addr), hp->h_length);

 	   info.sin_family = AF_INET;
 	   info.sin_addr.s_addr = htonl (INADDR_ANY);
 	   info.sin_port = htons (infoPort);



 	   psignal(sig, "\nRequesting list of people in chat");




    }
