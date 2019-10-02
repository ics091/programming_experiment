//
// Created by icsri on 2019/9/21.
//

#ifndef C_TEST_STATISTICS_H
#define C_TEST_STATISTICS_H

#endif //C_TEST_STATISTICS_H

#include <stdlib.h>

struct Global_stats {
    long long mem;
    long long cmp_num;
};

extern struct Global_stats global_stats;

void* bupt_malloc(int size){
    if (size <= 0) return NULL;
    global_stats.mem += size;
    return malloc(size* (MAX_PATTERNS*sizeof(char) + 8*sizeof(char*)));
}

int byte_cmp(char a,char b){
    ++global_stats.cmp_num;
    if ((a-b) == 0) return 1;
    else return 0;
}

int byte_cmp_pls(char *a, char *b){
    int _match = 0;
    while (byte_cmp(*a, *b)){
        a++;
        b++;
        if (byte_cmp(*a, *b) == 1 && *a == '\0' && *b == '\0') {
            _match = 1;
            break;
        }
        global_stats.cmp_num ++;
    }
    return _match;
}


