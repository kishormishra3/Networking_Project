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
pthread_t thread[10];
int listenfd = 0, connfd[10] = {0};
struct sockaddr_in serv_addr; 
char readBuff[100];
char sendBuff[1025];
int temp; 
void *readd(void *arg)
{
	int j;
	int *p=(int *)arg;
	while(1)
	{
		read(*p,readBuff,200);
		printf("Client send:%s\n",readBuff);
		for(j=0;j<3;j++)
		{
			write(connfd[j],readBuff,10);
		}
		
		
	}
}
int main(int argc, char *argv[])
{
	pthread_attr_t custom1,custom2;
	pthread_attr_init(&custom1);
	pthread_attr_init(&custom2);
	int *p,i,*ptr;
   	listenfd = socket(AF_INET, SOCK_STREAM, 0);
   	memset(&serv_addr, '0', sizeof(serv_addr));
   	memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10);
	for(i=0;i<2;i++){ 
	connfd[i]= accept(listenfd, (struct sockaddr*)NULL, NULL);
	} 
	for(i=0;i<2;i++){
	pthread_create(&thread[i],&custom1,&readd,&connfd[i]);
	//pthread_create(&thread[i+1],&custom1,writee,&(i));
	}
	for(i=0;i<2;i++){
       	pthread_join(thread[i],NULL);
	}
	for(i=0;i<2;i++)
        close(connfd[i]);
return 0;
}
