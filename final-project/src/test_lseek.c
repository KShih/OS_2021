#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <unistd.h>

#include <fcntl.h>
#include <time.h>

void main(int argc, char *argv[]){
    int fd = open("ubuntu.iso", O_RDWR);
    int times;
    sscanf(argv[1], "%d", &times);
    printf("%d", times);
    time_t startTime, endTime;
    startTime = time(NULL);
    for (int i=0; i < times; i++) {
        lseek(fd, 0, SEEK_END);
    }
    endTime = time(NULL);
    printf("time: %d", endTime - startTime);
}