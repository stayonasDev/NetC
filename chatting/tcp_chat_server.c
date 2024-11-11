#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 100 

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	char message[BUFSIZE];
	int read_len, written_len;
	char msg[50];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock == -1)
		perror("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if( bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		perror("bind() error"); 
	
	if( listen(serv_sock, 5)==-1 ) 
		perror("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);    
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		perror("accept() error");
	
	sleep(5);

	read_len = read(clnt_sock, message, BUFSIZE);
	message[read_len] = 0;
	printf("수신> %s", message);
	
	printf("송신 >");
	fgets(msg, sizeof(msg), stdin);
	written_len = write(clnt_sock, msg, sizeof(msg));
	message[written_len] = 0;
	
	close(clnt_sock);
	return 0;
}
