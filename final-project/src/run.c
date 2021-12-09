#include <stdio.h>

#include <unistd.h>

#include <fcntl.h>

#include <errno.h>

#include <string.h>

#include <time.h>

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

int readFromFile(char* filePath, int blockSize, int blockCount) {

    if (blockSize % 4 != 0) {
        printf("%s\n", "BlockSize should be times of 4.");
        return -1;
    }
    
    unsigned int result = 0;

    int fd = open(filePath, O_RDONLY);
    int buffer[blockSize/4];

    // int size = read(fd, buffer, sizeof(buffer));
    // while (size > 0){   
    //     for (int i = 0; i < size / 4; i++) {
    //         result ^= buffer[i];
    //     }
    //     size = read(fd, buffer, sizeof(buffer));
    // }
    // printf("%08x\n", result);

    int size = read(fd, buffer, sizeof(buffer));
    blockCount -= 1;
    while (size > 0 && blockCount > 0){   
        // for (int i = 0; i < size / 4; i++) {
        //     result ^= buffer[i];
        // }
        size = read(fd, buffer, sizeof(buffer));
        blockCount -= 1;
    }
    // printf("%08x\n", result);
    close(fd);
    return 0;
}

int writeToFile(char * outPath, int blockSize, int blockCount) {
    int out = open(outPath, O_CREAT | O_WRONLY | O_APPEND, 0777);
    int i = 0;
    blockSize /= 4;
    while (i < blockCount) {
        int buffer[blockSize];
        for (int j = 0; j < blockSize; j++) {
            buffer[j] = 5;
        }
        int res = write(out, buffer, sizeof(buffer));
        i += 1;
    }
    close(out);
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("%s", "invalid params");
        return -1;
    }

    long long blockSize, blockCount;
    char* path = argv[1];
    char* mode = argv[2];
    // char* blockSize = argv[3];
    // char* blockCount = argv[4];
    // printf("%s\n", path);
    // printf("%s\n", mode);
    // printf("%s\n", blockSize);
    // printf("%s\n", blockCount);
    if (sscanf(argv[3], "%lld", &blockSize) != 1 || sscanf(argv[4], "%lld", &blockCount) != 1){
        printf("%s", "bockSize and blockCount should be int");
        return -1;
    }
    time_t startTime, endTime;
    startTime = time(NULL);
    if (strcmp(mode, "-r") == 0) {
        readFromFile(path, blockSize, blockCount);
    } else if (strcmp(mode, "-w") == 0) {
        writeToFile(path, blockSize, blockCount);
    } else {
        printf("%s", "only accept [-r | -w]");
        return -1;
    }
    endTime = time(NULL);
    double fileSize = blockCount/1024*blockSize/1024;
    double timeSpend = endTime-startTime;
    printf("fileSize: %f\n", fileSize);
    printf("timeSpend: %f\n", timeSpend);
    printf("speed: %f MB/s\n", fileSize / timeSpend);

    return 0;
}