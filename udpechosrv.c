/*
 * Lab problem set for INP course
 * by Chun-Ying Huang <chuang@cs.nctu.edu.tw>
 * License: GPLv2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>

#define err_quit(m) { perror(m); exit(-1); }

int main(int argc, char *argv[])
{
	int s;
	struct sockaddr_in sin;

	if(argc < 2) {
		return -fprintf(stderr, "usage: %s ... <port>\n", argv[0]);
	}

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(strtol(argv[argc-1], NULL, 0));

	if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		err_quit("socket");

	if(bind(s, (struct sockaddr*) &sin, sizeof(sin)) < 0)
		err_quit("bind");

	int status;
	status = mkdir("/home/files", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	//status = mkdir("/files", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	struct timeval start;
    struct timeval end;
    unsigned long timer;
		gettimeofday(&start, NULL);

	int i, temp;
	//char fileContent[1000][32768] = {};
	char fileContent[32768] = {};
	int data;
	int location;
	float diff;

	i = 1;
	while(1)
	{
		gettimeofday(&end, NULL);
		timer = (end.tv_sec - start.tv_sec);
printf("timer: %ld\n", timer);
		if(timer > 290)
		{
			break;
		}
//printf("123\n");
		struct sockaddr_in csin;
		socklen_t csinlen = sizeof(csin);
		char buf[5] = {};
		int rlen;
//printf("456\n");
		if((rlen = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &csin, &csinlen)) < 0) {
			perror("recvfrom");
			break;
		}else
		{
			printf("receive: %s\n", buf);
		}
//printf("789\n");

		if(rlen > 0)
		{
			location = (int)buf[3]*16777216 + (int)buf[2]*65536 + (int)buf[1]*256 + (int)buf[0];
//printf("147\n");
			fileContent[location] = buf[4];
//printf("258\n");
		}
	}

	FILE *output;

	char filePath[] = "./files/000008\0";

	output = fopen(filePath, "wb+");
	fwrite(fileContent, strlen(fileContent), 1, output);
	fclose(output);

	close(s);
}
