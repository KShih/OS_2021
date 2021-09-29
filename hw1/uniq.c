#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void uniq(int fd, char *name) {
    int i, n;
    char *prev;
    char *cur;
    int line = 0;
    int start = 0;
    int w = 0;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (i = 0; i < n; i++) {
            w += 1;
            if (buf[i] == '\n') {
                line += 1;
                cur = (char *) malloc(w);
                int index = 0;
                int end = start + w;
                while (start < end) {
                    cur[index] = buf[start];
                    index ++;
                    start ++;
                }
                w = 0;
                if(line == 1 || strcmp(prev, cur) != 0){
                    printf(1, "%s", cur);
                }
                prev = (char *) malloc(sizeof(cur));
                strcpy(prev, cur);
                free(cur);
            }
            
        }
        start = 0;
    }
    free(prev);
    
    if (n < 0) {
        printf(1, "wc: read error\n");
        exit();
    }
//   printf(1, "%d %d %d %s\n", l, w, c, name);
}

int main(int argc, char *argv[]) {
    int fd, i;

    if (argc <= 1) {
        uniq(0, "");
        exit();
    }

    for (i = 1; i < argc; i++) {
        if ((fd = open(argv[i], 0)) < 0) {
        printf(1, "uniq: cannot open %s\n", argv[i]);
        exit();
        }
        uniq(fd, argv[i]);
        close(fd);
    }
    exit();
}
