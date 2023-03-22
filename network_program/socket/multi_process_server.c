#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include "wrap.h"
#include <arpa/inet.h>
#include <ctype.h>
#define SRV_PORT 8080

int main(int argc, char *argv[])
{
	int lfd, cfd;
	pid_t pid;
	struct sockaddr_in srv_addr, clt_addr;
	socklen_t clt_addr_len;
	char buf[BUFSIZ];
	int ret, i;

	//memset(&srv_addr, 0, sizeof(srv_addr)); //将地址结构清零
	bzero(&srv_addr, sizeof(srv_addr));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(SRV_PORT);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	lfd = Socket(AF_INET, SOCK_STREAM, 0);

	Bind(lfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

	Listen(lfd, 128);

	clt_addr_len = sizeof(clt_addr);

		cfd = Accept(lfd, (struct sockaddr *)&clt_addr, &clt_addr_len);

		pid = fork();
		if(pid < 0){
			perr_exit("fork error");
		} else if(pid == 0) {
			close(lfd);
		} else {
			close(lfd);
			close(cfd);
			while(1);
			return 0;
		}

	if(pid == 0){
		for(;;){
			ret = Read(cfd, buf, sizeof(buf));
			if(ret == 0){
				close(cfd);
				exit(1);
			}

			for(i = 0; i < ret; i++)
				buf[i] = toupper(buf[i]);

			write(cfd, buf, ret);
			write(STDOUT_FILENO, buf, ret);
		}
	}
	return 0;
}
