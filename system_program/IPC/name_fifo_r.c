#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void sys_err(const char *str){
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int fd, len;
	char buf[4096];

	if (argc < 2){
		printf("./a.out fifoname\n");
		return -1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		sys_err("open");
	while(1){
		len = read(fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, len);
		sleep(3);
	}
	close(fd);
	return 0;
}
