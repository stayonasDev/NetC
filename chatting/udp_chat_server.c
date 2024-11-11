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
	int clen;
	struct sockaddr_in client_addr, server_addr;
	char buf[MAXBUF];

	int read_len, written_len;

	if(argc != 2){
		printf("Port를 입력하세요");
		exit(1);
	}

	if ((ssock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("socket error : ");
		exit(1);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family 	= AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port 	= htons(atoi(argv[1]));

	if (bind(ssock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("bind error : ");
		exit(1);
	}

	clen = sizeof(client_addr);

	read_len =	recvfrom(ssock, (void *)buf, MAXBUF, 0, (struct sockaddr*)&client_addr, &clen);

	buf[read_len] = '\0';
	printf("수신>  %s", buf);		


	printf("송신> ");
	fgets(buf, sizeof(buf), stdin);

	written_len = sendto(ssock, (void*)buf, MAXBUF, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

	buf[written_len] = '\0';
	close(ssock);
	return 0;
}

