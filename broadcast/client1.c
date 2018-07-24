#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
int sockfd = 0, n = 0;
    char recvBuff[1024];int temp;
    struct sockaddr_in serv_addr; 
	char sendBuff[100];
pthread_t thread1,thread2;
void *readd(void *arg)
{
	while(1){
	read(sockfd,recvBuff,100);
	printf("Server send:%s\n",recvBuff);
	}
}
void *writee(void *arg)
{
	while(1)
	{
		gets(sendBuff);
		write(sockfd,sendBuff,10);
	}
}	
int main(int argc, char *argv[])
{
	pthread_attr_t custom1,custom2;
	pthread_attr_init(&custom1);
    	pthread_attr_init(&custom2);
	int *p;
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 
	
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
	
    memset(&serv_addr, '0', sizeof(serv_addr)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
	printf("Server address used is: %s\n", argv[1]);
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
	
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
		printf("\n Error : Connect Failed \n");
		return 1;
    } 
	pthread_create(&thread1,&custom1,readd,(void *)p);
	pthread_create(&thread2,&custom2,writee,(void *)p);	
	pthread_join(thread2,NULL);
	pthread_join(thread1,NULL);
    return 0;
}
