//
// Created by icsri on 2019/9/23.
//

#ifndef HASH_SEARCH_HASH_CONSTRUCTION_H
#define HASH_SEARCH_HASH_CONSTRUCTION_H

#endif //HASH_SEARCH_HASH_CONSTRUCTION_H

#define MAX_WORD 256
#define MAX_PATTERNS 256
#define WORD_NUM 986000
#define PATTERN_NUM 1271000

#include "statistics.h"

 struct Chain_Node {
    char *string;
    struct Chain_Node *next_node;
};

 struct Hash_table {
    unsigned int length;
    struct Chain_Node **chain;
};

//hash函数
unsigned int Hash_fun_l(const char *words, unsigned int length) {
    unsigned int b=378551 ;
    unsigned int a=63689 ;
    unsigned int hash=0 ;

    const char *c = words;

    while(*c)
    {
        hash=(((hash*a)%length)+(*c))%length;
        a=(a*b)%length ;
        ++c;
    }
    return(hash % length);
}

//RSHash function