#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <getopt.h>
#include "irpc.dsc.h"
#include "irpc_common.h"

#define SEND_BUF_SIZE 1024
#define SERVER_PORT 10201
#define DEFAULT_SERVER_IP_ADDRESS "192.168.229.1"

static char g_serverip[16] = {0};

struct option long_opts[] = {
	{"ip", no_argument, NULL, 'i'},
	{"cmd_name", no_argument, NULL, 'c'},
	{"paras", no_argument, NULL, 'p'},
    {"serverip", no_argument, NULL, 's'},
	{NULL, 0, NULL, 0}
};

int send_cmd(const char *cmd, int len)
{
    int sock_fd = 0;
    char sendbuf[SEND_BUF_SIZE] = {0};
    struct sockaddr_in ser_addr;

    if(cmd == NULL || *cmd == 0 || len <= 0 || len >= sizeof(sendbuf))
    {
        irpc_log("input wrong\n");
        return -1;
    }

    //irpc_log("cmd:[%s]\n", cmd);

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;

    if(strlen(g_serverip) > 0)
    {
        inet_aton(g_serverip, (struct in_addr *)&ser_addr.sin_addr);
    }
    else
    {
        inet_aton(DEFAULT_SERVER_IP_ADDRESS, (struct in_addr *)&ser_addr.sin_addr);
    }
    ser_addr.sin_port = htons(SERVER_PORT);
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        irpc_log( " create socket failed");
        return -1;
    }
    if(connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
    {
        irpc_log( " connect socket failed");
        return -1;
    }
    //irpc_log("connect success\n");

    snprintf(sendbuf, sizeof(sendbuf) - 1, "%s", cmd);

    //send data
    send(sock_fd, sendbuf, strlen(sendbuf) + 1, 0);
    close(sock_fd);
    return 0;
}

int main(int argc, char **argv) {
    IRPC_CONF conf;
    char buf[1024] = {0};
    int buf_len = sizeof(buf) - 1;

    DSCINIT_IRPC_CONF(&conf);

    while (1) {
		char c = getopt_long(argc, argv, "i:c:p:a:s:", long_opts, NULL);
		if (c == EOF)
			break;
		switch (c) {
			case 'i':
                IRPC_STRCPY_S(conf.client_ip_str, optarg);
                //irpc_log("input ip is [%s]\n", optarg);
				break;
			case 'c':
                IRPC_STRCPY_S(conf.cmd_name, optarg);
                //irpc_log("input cmd_name is [%s]\n", optarg);
				break;
            case 'p':
                IRPC_STRCPY_S(conf.paras, optarg);
                //irpc_log("get para is [%s]\n", optarg);
				break;
            case 's':
                IRPC_STRCPY_S(g_serverip, optarg);
                break;
			default:
                irpc_log("parse args error\n");
				exit(1);
		}
	}

    memset(buf, 0, sizeof(buf));
    if(DSCSERIALIZE_JSON_IRPC_CONF(&conf, NULL, buf, &buf_len) != 0) {
        irpc_log("generate json str failed\n");
        return -1;
    }
    //irpc_log("get json str is [%s]\n", buf);
    send_cmd(buf, strlen(buf));

    return 0;
}
