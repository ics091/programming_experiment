//
// Created by icsri on 2019/10/29.
//

#ifndef BPLUS_SEARCH_BASE_FUNC_H
#define BPLUS_SEARCH_BASE_FUNC_H

#include <string.h>
#endif //BPLUS_SEARCH_BASE_FUNC_H

#define MAX_STRINGL 256

struct global_stats{
    long long mem;
    unsigned long long cmp_num;
    unsigned int words_num;
    unsigned int words_success_num;
    long long nodenum;
}global_stats;

int byte_cmp(char a, char b){
    global_stats.cmp_num ++;
    return a - b;
}
/*
int str_cmp(char *a, char *b){
    char *a_tmp = a;
    char *b_tmp = b;
    while(*a_tmp != '\0' || *b_tmp != '\0'){
        if (byte_cmp(*a_tmp, *b_tmp) == 0){
            a_tmp ++;
            b_tmp ++;
        }
        else if(byte_cmp(*a_tmp, *b_tmp) > 0){
            //若前面的字符大于后面的字符则返回1
            return 1;
        }
        else{
            //若前面的字符小于后面的字符则返回-1
            return -1;
        }
    }
    // 若这两个字符串相等则返回0
    return 0;
}
 */
int str_cmp(const char * str1, const char * str2)
{
    char * a = str1;
    char * b = str2;
    while(*a != '\0' && *b != '\0')
    {
        int result = byte_cmp(*a, *b);
        if(result == 0)
        {
            a++;
            b++;
        }
        else if(result > 0){
            return 1;
        }
        else {
            return -1;
        }
    }
    if (*a == '\0' && *b == '\0')
    {
        return 0;
    } else if(*a == '\0'){
        return -1;
    } else {
        return 1;
    }
}

void* bupt_malloc(size_t size){
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