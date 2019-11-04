//
// Created by icsri on 2019/11/2.
//

#ifndef RADIX4_SEARCH_BASE_FUNC_H
#define RADIX4_SEARCH_BASE_FUNC_H

#endif //RADIX4_SEARCH_BASE_FUNC_H

#include <stdlib.h>
#include <string.h>

#define MAX_STRINGL 256

struct global_stats{
    long long mem;
    unsigned long long cmp_num;
    unsigned int words_num;
    unsigned int words_success_num;
    long long node_num;
}global_stats;

void *bupt_malloc(size_t size){
    if(size <= 0){
        return NULL;
    }
    global_stats.mem += size;
    return (malloc(size));
}

int read(FILE *file, char **string) {
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
    return j;
}