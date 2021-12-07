#include <stdio.h>

#include <unistd.h>

#include <fcntl.h>

#include <errno.h>

#include <string.h>

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

    int blockSize, blockCount;
    char* path = argv[1];
    char* mode = argv[2];
    // char* blockSize = argv[3];
    // char* blockCount = argv[4];
    // printf("%s\n", path);
    // printf("%s\n", mode);
    // printf("%s\n", blockSize);
    // printf("%s\n", blockCount);
    if (sscanf(argv[3], "%d", &blockSize) != 1 || sscanf(argv[4], "%d", &blockCount) != 1){
        printf("%s", "bockSize and blockCount should be int");
        return -1;
    }

    if (strcmp(mode, "-r") == 1) {

    } else if (strcmp(mode, "-w") == 1) {
        writeToFile(path, blockSize, blockCount);
    } else {
        printf("%s", "only accept [-r | -w]");
        return -1;
    }

    return 0;
}