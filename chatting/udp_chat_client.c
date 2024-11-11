#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#define MAXBUF  256 

int main(int argc, char** argv)
{
	int ssock;
	int slen;
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF];

	int written_len, read_len;

	if(argc != 3){
		printf("IP Address Port를 입력하세요");
		exit(1);
	}

	printf("송신 > ");
	fgets(buf, sizeof(buf), stdin);

	if ((ssock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket error : ");
		exit(1);
	}

	memset(&server_addr,0, sizeof(server_addr));
	server_addr.sin_family 	= AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port 	= htons(atoi(argv[2]));

	written_len = sendto(ssock, (void*)buf, MAXBUF, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

	buf[written_len] = '\0';	
	
	slen = sizeof(server_addr);

	read_len = recvfrom(ssock, (void *)buf, MAXBUF, 0, (struct sockaddr*)&server_addr, &slen);

	buf[read_len] = '\0';
	printf("수신>  %s", buf);		 

	
	close(ssock);

	return 0;
}

