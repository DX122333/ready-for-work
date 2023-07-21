/*
消息队列通性原理：
key
消息队列标识符
消息类型
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

typedef struct _msg
{
    long mtype;
    char mtext[50];
} MSG;

void msg_write(){
    key_t key;
    int msgqid;
    MSG msg;

    key = ftok("./", 2015);//参数：路径名，项目ID；key值相当于消息队列所在的地址

    //创建消息队列
    msgqid = msgget(key, IPC_CREAT|0666);
    if(msgqid == -1){
        perror("msgget");
        exit(-1);
    }

    msg.mtype = 10; //消息类型
    strcpy(msg.mtext, "hello I'm msg_write"); //正文内容

    msgsnd(msgqid, &msg, sizeof(msg)-sizeof(long), 0);  //发送消息

}

int main(){
    msg_write();
    return 0;
}