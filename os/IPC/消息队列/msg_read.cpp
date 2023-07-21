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

void msg_read(){
    key_t key;
    int msgqid;

    key = ftok("./", 2015);//参数：路径名，项目ID；key值相当于消息队列所在的地址

    //创建消息队列
    msgqid = msgget(key, IPC_CREAT|0666);
    if(msgqid == -1){
        perror("msgget");
        exit(-1);
    }

    MSG msg;
    memset(&msg, 0, sizeof(msg));

    msgrcv(msgqid, &msg, sizeof(msg)-sizeof(long), (long)10, 0);    //取出消息队列中消息类型10的消息放入msg
    printf("msg_read get \" %s \" \n", msg.mtext);

    msgctl(msgqid, IPC_RMID, NULL); //删除消息队列
}

int main(){
    msg_read();
    return 0;
}