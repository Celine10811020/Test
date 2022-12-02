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

	FILE *output;
	char path[] = "./files/000\0";
	int i, temp;

	for(i=0; i<1000; i++)
	{
		char fileName[4] = {};
		char filePath[20] = {};
		sprintf(fileName, "%03d", i);

		strcat(filePath, path);
		strcat(filePath, fileName);

		output = fopen(filePath, "w");
		fclose(output);
	}

	int data, name, location;
	char checksum;
	unsigned int mask = 0x000000ff;

	i = 1;
	while(1)
	{
		struct sockaddr_in csin;
		socklen_t csinlen = sizeof(csin);
		unsigned char buf[5] = {};
		int rlen;

		if((rlen = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &csin, &csinlen)) < 0)
		{
			perror("recvfrom");
			break;
		}else
		{
			printf("receive: %x %x\n", buf[1]&mask, buf[0]&mask);
		}

		if(rlen > 0)
		{
			checksum = buf[0] ^ buf[1] ^ buf[2] ^ buf[3];

			if(buf[5] == checksum)
			{
				data = ((int)buf[3]&mask)*16777216 + ((int)buf[2]&mask)*65536 + ((int)buf[1]&mask)*256 + ((int)buf[0]&mask);

				name = data / 32768;
				location = data % 32768;

				char fileName[4] = {};
				char filePath[20] = {};
				sprintf(fileName, "%03d", name);

				strcat(filePath, path);
				strcat(filePath, fileName);

				output = fopen(filePath, "rb+");
				fseek(output, location, SEEK_SET);
				fwrite(&buf[4], 1, 1, output);
				fclose(output);
			}
		}
	}

	close(s);
}
