#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

int readFile(char* filePath) {
    int blockSize = 32768;
    unsigned int result = 0;

    int fd = open(filePath, O_RDONLY);
    int buffer[blockSize / 4];

    int size = read(fd, buffer, sizeof(buffer));
    while (size > 0){   
        for (int i = 0; i < size / 4; i++) {
            result ^= buffer[i];
        }
        size = read(fd, buffer, sizeof(buffer));
    }
    printf("%08x\n", result);
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    char* path = argv[1];
    time_t start, end;
    start = time(NULL);
    readFile(path);
    end = time(NULL);
    printf("Run %f seconds\n", difftime(end, start));
    return 0;
}
