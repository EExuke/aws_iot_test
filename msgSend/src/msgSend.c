/**************************************************************************** **
 * Copyright (C) 2001-2020 Inhand Networks, Inc.
 **************************************************************************** **/

/* ************************************************************************** **
 *     MODULE NAME            : system
 *     LANGUAGE               : C
 *     TARGET ENVIRONMENT     : Any
 *     FILE NAME              : msgSend.c
 *     FIRST CREATION DATE    : 2020/08/06
 * --------------------------------------------------------------------------
 *     Version                : 1.0
 *     Author                 : EExuke
 *     Last Change            : 2020/08/06
 *     FILE DESCRIPTION       :
** ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

struct msg_st
{
	long int msg_type;
	char msg[64];
};

/****************************************************************************
 *  Function Name : main
 *  Description   : The Main Function.
 *  Input(s)      : argc - The numbers of input value.
 *                : argv - The pointer to input specific parameters.
 *  Output(s)     : NULL
 *  Returns       : 0
 ****************************************************************************/
int main(int argc, const char *argv[])
{
	struct msg_st msg_ptr;
	char buffer[64];
	int msgid = -1;

	// 建立or获取消息队列
	msgid = msgget((key_t)9970, 0777);
	if (msgid == -1)
	{
		fprintf(stderr, "msgget failed error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	// 向消息队里中写消息，直到写入end
	while (1)
	{
		printf("Enter some text: \n");
		fgets(buffer, sizeof(msg_ptr.msg), stdin);
		msg_ptr.msg_type = 1; // 注意2
		strcpy(msg_ptr.msg, buffer);

		// 向队列里发送数据
		if (msgsnd(msgid, (void *)&msg_ptr, sizeof(msg_ptr.msg), 1) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}

		// 输入end结束输入
		if (strncmp(buffer, "end", 3) == 0)
		{
			break;
		}

		sleep(1);
	}

	exit(EXIT_SUCCESS);
}

