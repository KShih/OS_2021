#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int getBlockCountInTenSeconds(char* filePath, int blockSize) {
    time_t start;
    int fd = open(filePath, O_RDONLY);
    unsigned char buffer[blockSize];
    int size;
    int blockCount = 0;
    start = time(NULL);
    while ((size = read(fd, buffer, sizeof(buffer))) > 0 && time(NULL) - start < 10){   
        blockCount += 1;
    }
    close(fd);
    return blockCount;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("%s", "invalid params\n");
        return -1;
    }
    char* path = argv[1];
    int blockSize;

    if (sscanf(argv[2], "%d", &blockSize) != 1){
        printf("%s", "bockSize and blockCount should be int");
        return -1;
    }
    time_t start, end;
    start = time(NULL);
    int blockCount = getBlockCountInTenSeconds(path, blockSize);
    end = time(NULL);
    printf("Run %f seconds\n", difftime(end, start));
    printf("Block Count: %d\n", blockCount);
    return 0;
}