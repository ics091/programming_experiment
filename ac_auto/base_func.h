//
// Created by icsri on 2019/11/21.
//

#ifndef AC_AUTO_BASE_FUNC_H
#define AC_AUTO_BASE_FUNC_H

#endif //AC_AUTO_BASE_FUNC_H

#include "stdlib.h"
#include "string.h"
#define MAX_PATTERNS 256
#define PATTERN_NUM 20

struct Pattern_ctn {
    char *pattern;
    int ctn;
};

struct global_stats{
    long long mem;
    long long cmp_num;
}global_stats;

void *bupt_malloc(size_t size){
    if(size <= 0){
        return NULL;
    }
    global_stats.mem += size;
    return (malloc(size));
}

int read_pattern(FILE *file, struct Pattern_ctn *patternCtn) {
    char p[MAX_PATTERNS];
    char c;
    int i = 0;
    int j = 0;
    while (1) {
        c = (char)fgetc(file);
        if (c == '\n' || c == EOF) {
            p[i] = '\0';
            strcpy(patternCtn[j].pattern, p);
            patternCtn[j].ctn = 0;
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

