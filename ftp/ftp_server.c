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
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
pthread_t thread1,thread2;
int listenfd = 0, connfd = 0,size=0;
struct sockaddr_in serv_addr; 
struct stat file;
char readBuff[100],*f;
char sendBuff[1025],command[100],filename[100];
int filehandle=0,a=0,filehandle1=0; 
int main(int argc, char *argv[])
{
   	listenfd = socket(AF_INET, SOCK_STREAM, 0);
   	memset(&serv_addr, '0', sizeof(serv_addr));
   	memset(sendBuff, '0', sizeof(sendBuff)); 
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5001); 
	
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	
    listen(listenfd, 10); 
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	while(1)
	{
		recv(connfd,readBuff,100,0);
		sscanf(readBuff,"%s%s",command,filename);
		if(!strcmp(command,"get"))
		{
			stat(filename,&file);
			filehandle = open(filename, O_RDONLY);
			size=file.st_size;
			printf("Size of file :%d\n",size);
			send(connfd, &size, sizeof(int),0);
			sendfile(connfd, filehandle, NULL, size);
			printf("Sucess\n");
		
		}
		else if(!strcmp(command,"ls"))
		{
			system("ls >ls.txt");
			stat("ls.txt",&file);
			filehandle=open("ls.txt",O_RDONLY);
			size=file.st_size;
			send(connfd,&size,sizeof(int),0);
			sendfile(connfd,filehandle,NULL,size);
			printf("ls sucessful\n");	
		}
		else if(!strcmp(command,"pwd"))
		{
			system("pwd >ls.txt");
			stat("ls.txt",&file);
			filehandle=open("ls.txt",O_RDONLY);
			size=file.st_size;
			send(connfd,&size,sizeof(int),0);
			printf("size: %d\n",size);
			sendfile(connfd,filehandle,NULL,size);
			printf("pwd sucessful\n");	
		}
	}
close(connfd);
return 0;
}






















	
