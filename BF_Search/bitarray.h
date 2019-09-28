//
// Created by icsri on 2019/9/26.
//

#ifndef BF_SEARCH_BITARRAY_H
#define BF_SEARCH_BITARRAY_H

#define MAX_WORD 256
#define WORD_NUM 986000

#endif //BF_SEARCH_BITARRAY_H

#include "stdlib.h"
#include <limits.h>

//一个字符占 1 byte = 8 bit = CHAR_BIT
const unsigned char A_BYTE = CHAR_BIT;
//掩码
const unsigned char MASK_1 = 1;       //位模式 00000001

#define M  249997
#define M1 1000001
#define M2 0xF0000000

const int prime[] = {9999901, 9999907, 9999929, 9999931, 9999937,
                     9999943, 9999971, 9999973, 9999991};

long long compare_number = 0;

struct BitArray {
    unsigned char *byte_array;  //用字符数组模拟位数组

    unsigned long max_bits;     //最大的位数

    unsigned long length;       //字符数组长度

};

struct BitArray *bitArray_create(unsigned long bits) {

    struct BitArray *bitArray = NULL;
    if (bits == 0 || (bits%A_BYTE != 0)) return NULL;
    bitArray = malloc(sizeof(struct BitArray));
    //if (bitArray = NULL) return NULL;

    //计算byte_array数组的长度，即所需Byte数
    unsigned long length = 0;
    length = bits/A_BYTE;
    //为字符数组分配空间
    bitArray->byte_array = calloc(length, sizeof(unsigned char));
    if (bitArray->byte_array == NULL) {
        free(bitArray);
        return NULL;
    }
    bitArray->length = length;
    bitArray->max_bits = bits;
    return bitArray;
}

//设置位数组相应位置为一（7次hash出来的数）
int bitArray_set_1(struct BitArray *target_ar, unsigned long bit) {
    //检查参数
    if(target_ar == NULL)
        return -1;
    if(bit >= target_ar->max_bits)
        return -2;
    //定位在char数组元素中的位置
    unsigned long index = target_ar->length - 1 -(bit/A_BYTE);
    //定位在所在char数组元素中的位置
    unsigned  int  pos = bit % A_BYTE;  //求余
    // |= MASK_1<< j 构造一个其余位为 0 ，j位置为 1 的掩码
    target_ar->byte_array[index] |= MASK_1<< pos;
    //printf("%d\n", target_ar->byte_array[index]);
    //成功 返回 1
    return 1;
}

//设置位数组相应位置为 0（7次hash出来的数）
int bitArray_set_0(struct BitArray *target_ar, unsigned long bit) {
    //检查参数
    if(target_ar == NULL)
        return -1;
    if(bit >= target_ar->max_bits)
        return -2;
    //定位在char数组元素中的位置
    unsigned long index = target_ar->length - 1 -(bit/A_BYTE);
    //定位在所在char数组元素中的位置
    unsigned  int  pos = bit % A_BYTE;  //求余
    // &= ~(MASK_1<< j)将第j位置位0
    target_ar->byte_array[index] &= ~(MASK_1<< pos);
    //成功 返回 1
    return 1;
}

//这个函数传入的bit，应该是由word[]数组中的字符串hash出来的
int bitArray_test_bit(struct BitArray *target_ar, unsigned long bit) {
    //检查参数
    if(target_ar == NULL)
        return -1;
    if(bit >= target_ar->max_bits)
        return -2;
    //定位在char数组元素中的位置
    unsigned long index = target_ar->length - 1 -(bit/A_BYTE);
    //定位在所在char数组元素中的位置
    unsigned  int  pos = bit % A_BYTE;  //求余
    //测试位状态
    if(target_ar->byte_array[index] & (MASK_1<< pos) )
        return 1;
    else
        return 0;
}

//7个哈希函数
// RS Hash Function
unsigned int RSHash(char*str)
{
    unsigned int b=378551 ;
    unsigned int a=63689 ;
    unsigned int hash=0 ;

    while(*str)
    {
        hash=hash*a+(*str++);
        a*=b ;
    }

    return(hash);
}

// JS Hash Function
unsigned int JSHash(char*str)
{
    unsigned int hash=1315423911 ;

    while(*str)
    {
        hash^=((hash<<5)+(*str++)+(hash>>2));
    }

    return(hash);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(char*str)
{
    unsigned int BitsInUnignedInt=(unsigned int)(sizeof(unsigned int)*8);
    unsigned int ThreeQuarters=(unsigned int)((BitsInUnignedInt*3)/4);
    unsigned int OneEighth=(unsigned int)(BitsInUnignedInt/8);
    unsigned int HighBits=(unsigned int)(0xFFFFFFFF)<<(BitsInUnignedInt-OneEighth);
    unsigned int hash=0 ;
    unsigned int test=0 ;

    while(*str)
    {
        hash=(hash<<OneEighth)+(*str++);
        if((test=hash&HighBits)!=0)
        {
            hash=((hash^(test>>ThreeQuarters))&(~HighBits));
        }
    }

    return(hash);
}

// ELF Hash Function
unsigned int ELFHash(char*str)
{
    unsigned int hash=0 ;
    unsigned int x=0 ;

    while(*str)
    {
        hash=(hash<<4)+(*str++);
        if((x=hash&0xF0000000L)!=0)
        {
            hash^=(x>>24);
            hash&=~x ;
        }
    }

    return(hash);
}

// BKDR Hash Function
unsigned int BKDRHash(char*str)
{
    unsigned int seed=131 ;// 31 131 1313 13131 131313 etc..
    unsigned int hash=0 ;

    while(*str)
    {
        hash=hash*seed+(*str++);
    }

    return(hash);
}

// SDBM Hash Function
unsigned int SDBMHash(char*str)
{
    unsigned int hash=0 ;

    while(*str)
    {
        hash=(*str++)+(hash<<6)+(hash<<16)-hash ;
    }

    return(hash);
}

// DJB Hash Function
unsigned int DJBHash(char*str)
{
    unsigned int hash=5381 ;

    while(*str)
    {
        hash+=(hash<<5)+(*str++);
    }

    return(hash);
}

int compare_char(char a, char b) {
    ++compare_number;
    if (a == b) return 1;
    else return 0;
}

unsigned long long hash(int type, char *s, unsigned long long limit) {
    unsigned long long code = 0;
    char * ptr = s;
    int param = 1;
    int p = prime[8 - type];
    while (!compare_char(*ptr, '\0')) {
        code = (code + (param * (*ptr)));
        param = (param * p);
        ++ptr;
    }
    code = (code ^ 9999901) % limit;
    return code;
}

