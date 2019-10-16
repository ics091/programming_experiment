//
// Created by icsri on 2019/10/14.
//

#ifndef BTREE_SEARCH_CREATEBTREE_H
#define BTREE_SEARCH_CREATEBTREE_H

#endif //BTREE_SEARCH_CREATEBTREE_H

#define MAX_STRINGL 256
#include <stdlib.h>
#include <string.h>

//文件读取函数
void read(FILE *file, char **string) {
    char p[MAX_STRINGL];
    char c;
    int i = 0;
    int j = 0;
    while (1) {
        c = (char)fgetc(file);
        if (c == '\n' || c == EOF) {
            p[i] = '\0';
            strcpy(*(string+j), p);
            j++;
            i = 0;
            p[0] = '\0';
        } else{
            p[i++] = c;
        }
        if (c == EOF) break;
    }
    printf("%d \n", j);
}



