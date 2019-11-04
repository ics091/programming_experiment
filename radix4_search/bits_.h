//
// Created by icsri on 2019/11/2.
//

#ifndef RADIX4_SEARCH_BITS__H
#define RADIX4_SEARCH_BITS__H

#endif //RADIX4_SEARCH_BITS__H

#include <stdlib.h>
#include <string.h>

struct Bits {
    char *value;
    unsigned int start;
    unsigned int length;
};

struct Bits *init_bits(char *str) {
    struct Bits *bits = malloc(sizeof(struct Bits));
    bits->value = str;
    bits->start = 0;
    //bits数组需要的长度
    bits->length = strlen(bits->value) * 8;
    return bits;
}

int bits_get(struct Bits *bits, unsigned int postion) {
    char *str = bits->value;
    if (postion >= bits->length) return -1;
    else {
        return (str[postion / 8] >> (postion % 8)) & 1;
    }
}

int two_bits_get(struct Bits *bits, unsigned int postion) {
    int r;
    //char *str = bits->value;
    if (postion >= bits->length) return -1;
    else {
        if (bits_get(bits, postion) == 0 && bits_get(bits, postion + 1) == 0) r = 0;
        else if (bits_get(bits, postion) == 0 && bits_get(bits, postion + 1) == 1) r = 1;
        else if (bits_get(bits, postion) == 1 && bits_get(bits, postion + 1) == 0) r = 2;
        else if (bits_get(bits, postion) == 1 && bits_get(bits, postion + 1) == 1) r = 3;
        else r = -1;
    }
    return r;
}
