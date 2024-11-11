#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 50

int main(int argc, char **argv) 
{
	int sock;  
	int str_len, i;
	struct sockaddr_in serv_addr;
	int written_len;
	
	char msg1[BUFSIZE];
	char message[BUFSIZE];
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(sock == -1)
		perror("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	if( connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1 )
		perror("connect() error!");
       
        printf("송신> ");
        fgets(msg1, sizeof(msg1), stdin);	
	written_len = write(sock, msg1, strlen(msg1));
	msg1[written_len] = 0;

	sleep(3);

	str_len=read(sock, message, sizeof(message)-1);
	message[str_len]=0;
	printf("수신>  %s", message);
	
	close(sock);
	return 0;
}

