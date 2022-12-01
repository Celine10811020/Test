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


	FILE *output;
	int i, temp;
	int fileNum = 1;
	char fileName[7];
	char filePath[20];
	int fileSize;

	while(1)
	{
		struct sockaddr_in csin;
		socklen_t csinlen = sizeof(csin);
		char buf[32768] = {};
		int rlen;

		if((rlen = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &csin, &csinlen)) < 0) {
			perror("recvfrom");
			break;
		}

		//printf("receive: %s\n", buf);

		if(rlen > 0)
		{
			fileName[0] = '0';
			fileName[1] = '0';
			fileName[2] = '0';
			fileName[3] = buf[0];
			fileName[4] = buf[1];
			fileName[5] = buf[2];
			fileName[6] = '\0';

			fileSize = 	(int)buf[6]*16777216 + (int)buf[5]*65536 + (int)buf[4]*256 + (int)buf[3];

			//strcat(filePath, argv[1]);
			//strcat(filePath, fileName);

			char *p = buf;
			char *pp = p + 7;

			//printf("buf[0]: %p, buf[7]: %p\nbuf: %s\tp: %s(%p)\n", &buf[0], &buf[7], buf, pp, pp);

			output = fopen(fileName, "ab+");
			//output = fopen(filePath, "ab+");

			fwrite(pp, fileSize, 1, output);

			fclose(output);
		}

		sendto(s, buf, rlen, 0, (struct sockaddr*) &csin, sizeof(csin));
	}

	close(s);
}
