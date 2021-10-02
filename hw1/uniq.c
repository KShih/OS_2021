#include "types.h"
#include "stat.h"
#include "user.h"
#include "stddef.h"

#define SIZE 10000
char buf[512];

///////////////////// HashMap implementation ////////////////////////
struct DataItem {
   int data;   
   char *key;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(char *str) {
    int key = 0;
    while (*str) {
        key += (int)*str;
        str ++;
    }
   return key % SIZE;
}

struct DataItem *search(char *key) {
   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      ++hashIndex;
		
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(char *key,int data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;  
   item->key = key;

   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL && strcpy(hashArray[hashIndex]->key, "") != 0) {
      ++hashIndex;
		
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

void update(char *key,int data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;  
   item->key = key;

   int hashIndex = hashCode(key);
	
   hashArray[hashIndex] = item;
}

void display() {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(1, "(%s,%d)\n",hashArray[i]->key,hashArray[i]->data);
   }
}
/////////////////////////////////////////////////

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
        printf(1, "uniq: read error\n");
        exit();
    }
}

void uniqDup(int fd, char *name) {
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
                if((item = search(cur)) != NULL){
                    if (item->data != 2) {
                        printf(1, "%s", cur);
                        update(cur, 2);
                    }
                } else {
                    insert(cur, 1);
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
        printf(1, "uniq: read error\n");
        exit();
    }
}

void uniqCnt(int fd, char *name) {
    int i, n;
    char *prev;
    char *cur;
    int line = 0;
    int start = 0;
    int prevCnt = 0;
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
                if(line != 1 && strcmp(prev, cur) != 0){
                    printf(2, "%d %s", prevCnt, prev);
                    prevCnt = 1;
                } else {
                    prevCnt ++;
                }
                prev = (char *) malloc(sizeof(cur));
                strcpy(prev, cur);
                free(cur);
            }
            
        }
        start = 0;
    }
    printf(2, "%d %s", prevCnt, prev);
    free(prev);
    
    if (n < 0) {
        printf(1, "uniq: read error\n");
        exit();
    }
}

int compareNoSens(char* str1, char* str2){
    int index = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 != len2){
        return -1;
    }
    while(index < len1) {
        if(str1[index] == str2[index]) {
            index ++;
        }else if(str1[index] > str2[index]){
            if(str1[index] >= 'a' && str1[index] <= 'z' && str2[index] >= 'A' && str2[index] <= 'Z'
            && str1[index] - str2[index] == 32){
                index ++;
            }else{
                return -1;
            }
        }else if(str1[index] < str2[index]){
            if(str1[index] >= 'A' && str1[index] <= 'Z' && str2[index] >= 'a' && str2[index] <= 'z'
            && str2[index] - str1[index] == 32){
                index ++;
            }else{
                return -1;
            }
        }
    }
    return 1;

}

void uniqCombine(int fd, char *name) {
    int i, n;
    char *prev;
    char *cur;
    int line = 0;
    int start = 0;
    int prevCnt = 0;
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
                if(line != 1 && compareNoSens(prev, cur) != 1){
                    printf(2, "%d %s", prevCnt, prev);
                    prevCnt = 1;
                } else {
                    prevCnt ++;
                }
                prev = (char *) malloc(sizeof(cur));
                strcpy(prev, cur);
                free(cur);
            }
            
        }
        start = 0;
    }
    printf(2, "%d %s", prevCnt, prev);
    free(prev);
    
    if (n < 0) {
        printf(1, "uniq: read error\n");
        exit();
    }
}

void uniqNoSens(int fd, char* name){
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
                if(line == 1 || compareNoSens(prev, cur) != 1){
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
        printf(1, "uniq: read error\n");
        exit();
    }
}

int main(int argc, char *argv[]) {
    int fd, i;
    char c;

    dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
    dummyItem->data = -1;  
    dummyItem->key = "";

    if (argc <= 1) {
        uniq(0, "");
        exit();
    }

    if ((++argv)[0] && argv[0][0] == '-') {
        if(argc == 4) {
            argv += 2;
            if ((fd = open(*argv, 0)) < 0) {
                printf(1, "uniq: cannot open %s\n", argv[3]);
                exit();
            }
            uniqCombine(fd, *argv);
            close(fd);
            exit();
        }
        while(argv[0][0] == '-')
        {
            while((c = *++argv[0]))
            {
                switch(c) {
                    case 'i':
                        for (i = 1; i < argc-1; i++) {
                            if ((fd = open(argv[i], 0)) < 0) {
                                printf(1, "uniq: cannot open %s\n", argv[i]);
                                exit();
                            }
                            uniqNoSens(fd, argv[i]);
                            close(fd);
                        }
                        break;
                    case 'c':
                        for (i = 1; i < argc-1; i++) {
                            if ((fd = open(argv[i], 0)) < 0) {
                                printf(1, "uniq: cannot open %s\n", argv[i]);
                                exit();
                            }
                            uniqCnt(fd, argv[i]);
                            close(fd);
                        }
                        break;
                    case 'd':
                        for (i = 1; i < argc-1; i++) {
                            if ((fd = open(argv[i], 0)) < 0) {
                                printf(1, "uniq: cannot open %s\n", argv[i]);
                                exit();
                            }
                            uniqDup(fd, argv[i]);
                            close(fd);
                        }
                        break;
                }
                exit();
            }
        }
    }
    else {
        for (i = 0; i < argc-1; i++) {
                if ((fd = open(argv[i], 0)) < 0) {
                    printf(1, "uniq: cannot open %s\n", argv[i]);
                    exit();
                }
                uniq(fd, argv[i]);
                close(fd);
        }
    }

    exit();
}