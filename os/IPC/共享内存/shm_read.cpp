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

    //打开共享内存
    shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
    if(shmid < 0){
        perror("shmget");
        exit(-1);
    }

    //映射
    shmadd = shmat(shmid, NULL, 0); //add = address, 获取映射的位置
    if(shmadd < 0){
        perror("shmat");
        exit(-1);
    }

    //读共享内存区
    printf("shm_read get \" %s \" ", shmadd);

    //分离共享内存与当前进程
    ret = shmdt(shmadd);
    if(ret < 0){
        perror("shmdt");
        exit(-1);
    }

    shmctl(shmid, IPC_RMID, NULL);
    printf("deleted shared_memory\n");
    
    //查看共享内存
    system("ipcs -m");
}

int main(){
    shm_write();
    return 0;
}