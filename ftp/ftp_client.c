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
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
int sockfd = 0,size=0, n = 0,size1=0,filehandle=0,filehandle1=0;
    char recvBuff[1024],filename[100];int temp;
    struct sockaddr_in serv_addr; 
	char sendBuff[100],*f,command[100];
int main(int argc, char *argv[])
{
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
    serv_addr.sin_port = htons(5001); 
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
	while(1)
	{
		printf(" put\tget\tls\tpwd\n");
		gets(sendBuff);
		send(sockfd,sendBuff,100,0);
		sscanf(sendBuff,"%s%s",command,filename);
		
		if(!strcmp(command,"put"))
		{
			recv(sockfd, &size, sizeof(int),0);
			printf("SIZE OF file %d::\n",size);
              		f = malloc(size);
			recv(sockfd,f,size,0);
			printf("STRING::%s\n",f);
    		  	filehandle = open("temp.txt", O_CREAT | O_EXCL | O_WRONLY, 0666);
    		  	write(filehandle, f, size);
			printf("SUCESS\n");
		}
		else if(!strcmp(command,"ls"))
		{
			recv(sockfd, &size, sizeof(int),0);
			printf("ls size: %d\n",size);
			f=malloc(size);
			recv(sockfd,f,size,0);
			printf("Directory is\n %s\n",f);
		}
		else if(!strcmp(command,"pwd"))
		{
			recv(sockfd, &size, sizeof(int),0);
			printf("pwd size: %d\n",size);
			f=malloc(size);
			recv(sockfd,f,size,0);
			printf("pwd is\n %s\n",f);
		}
	}
close(sockfd);
return 0;
}
