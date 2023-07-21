/*
共享内存通信原理：
共享内存允许两个或更多进程访问同一块内存，当一个进程改变了这块地址中的内容的时候，其他进程就会察觉到这个更改
特点：
1.进程间共享数据最快/效率最高的方法
2.多个进程之间对共享内存互斥访问，和信号量配合使用
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define BUFSZ 512

void shm_write(){
    int shmid;
    int ret;
    key_t key;
    void* shmadd;

    //创建key值
    key = ftok("./", 2015);
    if(key == -1){
        perror("ftok");
        exit(-1);
    }

    //创建共享内存
    shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
    if(shmid < 0){
        perror("shmget");
        exit(-1);
    }

    //查看共享内存
    printf("shmid = %d\n", shmid);
    system("ipcs -m");

    //映射
    shmadd = shmat(shmid, NULL, 0); //add = address, 获取映射的位置
    if(shmadd < 0){
        perror("shmat");
        exit(-1);
    }

    //拷贝数据到共享内存区
    printf("shm_write copy data to shared_memory \n");
    bzero(shmadd, BUFSZ);
    strcpy((char*)shmadd, "how are you, I'm shm_write. \n");
}

int main(){
    shm_write();
    return 0;
}


