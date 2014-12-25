#ifndef COMMONS_H
#define COMMONS_H

#include <arpa/inet.h>
/*
	for:
		htons()
		htonl()
		ntohs()
		inet_aton()
		inet_ntoa()
*/

#include <netinet/in.h>
/*
	for:
		inet_aton()
		inet_ntoa()
*/

#include <sys/types.h>
/*
	for:
		socket()
		bind()
		recvfrom()
		sendto()
		stat()
*/

#include <sys/socket.h>
/*
	for:
		socket()
		bind()
		recvfrom()
		sendto()
		inet_aton()
		inet_ntoa()
		AF_INET
		SOCK_DGRAM
*/

#include <errno.h>
/*
	for:
		return type of system calls
*/

#include <stdio.h>
/*
	for:
		printf()
		sprintf()
		fflush()
		perror()
*/

#include <stdlib.h>
/*
	for:
		exit()
		malloc()
*/

#include <string.h>
/*
	for:
		memset()
		strlen()
		strcpy()
*/

#include <unistd.h>
/*
	for:
		close()
		sleep()
		stat()
*/

#include <dirent.h>

#define	DEBUG		1

#define	PORTSERVER	8487
#define CONTROLPORT	PORTSERVER      //控制连接的端口
#define DATAPORT	(PORTSERVER + 1)   // 数据连接的端口

enum TYPE
	{
		REQU,
		DONE,
		INFO,  
		TERM,
		DATA,
		EOT
	};

#define	NP		0
#define	HP		1
//根据errno=x和字符串e 展现错误信息
#define	er(e, x)					\
	do						\
	{						\
		perror("ERROR IN: " #e "\n");		\
		fprintf(stderr, "%d\n", x);		\
		exit(-1);				\
	}						\
	while(0)

#define	LENBUFFER	504		// so as to make the whole packet well-rounded ( = 512 bytes)
// packet的大小是512B 
struct packet
{
	short int conid;
	short int type;
	short int comid;
	short int datalen;
	char buffer[LENBUFFER];
};

void set0(struct packet*);

struct packet* ntohp(struct packet*);
struct packet* htonp(struct packet*);

void printpacket(struct packet*, int);

// 制定协议
#define NCOMMANDS 19
enum COMMAND
	{
		GET,
		PUT,
		MGET,
		MPUT,
		CD,
		LCD,
		MGETWILD,
		MPUTWILD,
		DIR_,		// _ to avoid conflict with directory pointer DIR
		LDIR,
		LS,
		LLS,
		MKDIR,
		LMKDIR,
		RGET,
		RPUT,
		PWD,
		LPWD,
		EXIT
	};			// any change made here should also be \
				replicated accordingly in the commandlist \
				2D array in client_ftp_fucntions.c

#endif

