#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>
pthread_t thread1,thread2;
int listenfd = 0, connfd = 0;
struct sockaddr_in serv_addr; 
char readBuff[100];
char sendBuff[1025];
int temp; 
void *readd(void *arg)
{
	while(1)
	{
		read(connfd,readBuff,200);
		printf("Client send:%s\n",readBuff);
		/*if(strcmpi(readBuff,"Bye")!=0)
		{
			close(connfd);
		}*/
	}
}
void *writee(void *arg)
{
	while(1)
	{
		gets(sendBuff);
		write(connfd,sendBuff,10);
		/*if(strcmpi(readBuff,"Bye")!=0)
		{
			close(connfd);
		}*/
	}
}	
int main(int argc, char *argv[])
{
	pthread_attr_t custom1,custom2;
	pthread_attr_init(&custom1);
	pthread_attr_init(&custom2);
	int *p;
   	listenfd = socket(AF_INET, SOCK_STREAM, 0);
   	memset(&serv_addr, '0', sizeof(serv_addr));
   	memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10); 
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	pthread_create(&thread1, &custom1,readd,(void *)p);
	pthread_create(&thread2, &custom2,writee,(void *)p);
       	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
        close(connfd);
}
