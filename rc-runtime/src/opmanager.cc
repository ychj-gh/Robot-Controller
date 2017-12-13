#include "opmanager.hh"

/*
int connfd;     // 与示教盒连接socket描述符

#define PORTNUMBER 8899


int teach_conn_init(){
    int sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	char buffer[2048];

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		fprintf(stderr, "Socker error: %s\n", strerror(errno));
		return -1;
	}

	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORTNUMBER);

	if(bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1){
		fprintf(stderr, "Bind error: %s\n\a", strerror(errno));
		return -2;
	}

	if(listen(sockfd, 5) == -1){
		fprintf(stderr, "Listen error: %s\n\a", strerror(errno));
		return -3;
	}

    int sin_size = sizeof(struct sockaddr_in);
	if((connfd = accept(sockfd, (struct sockaddr*)(&client_addr),(socklen_t*)&sin_size)) == -1){
		fprintf(stderr, "Accept error: %s\n\a", strerror(errno));
		return -4;
	}
    return 0;
}
*/


int rc_core_init(){
    rc_core.status = STATUS_STOP;
    rc_core.mode = OP_TEACH;
    SHM_RC_MODE_CLR(rc_shm);
    // rc_shm->rc_mode = OP_TEACH;
    // rc_core.mode = OP_RUN;
    // rc_shm->rc_mode = OP_RUN;
    rc_core.startup = 0;			// 启动运行
    rc_core.stepflag = 1;			// 设置为单步模式以使程序停在开始处
    rc_core.cur_linenum = 0;
}
