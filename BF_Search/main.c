#include <stdio.h>
#include "bitarray.h"

int main() {
    struct BitArray *bitArray;
    const unsigned long long bit_length = 1 << 26;
    bitArray = bitArray_create(bit_length);
    //读取patterns文件
    char *now_p;
    //FILE *fl_patterns = fopen("D:\\CLionProjects\\BF_Search\\p_test.txt", "r");
    FILE *fl_patterns = fopen("D:\\CLionProjects\\BF_Search\\patterns-127w_2.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_patterns)){
        now_p = malloc(MAX_WORD* sizeof(char));
        fscanf(fl_patterns, "%s", now_p);
        /*bitArray_set_1(bitArray, RSHash(now_p));
        bitArray_set_1(bitArray,JSHash(now_p));
        bitArray_set_1(bitArray,PJWHash(now_p));
        bitArray_set_1(bitArray,BKDRHash(now_p));
        bitArray_set_1(bitArray,DJBHash(now_p));
        bitArray_set_1(bitArray,ELFHash(now_p));
        bitArray_set_1(bitArray,SDBMHash(now_p));*/
        for (int i = 0; i < 8; ++i) {
            bitArray_set_1(bitArray, hash(i, now_p, bit_length));
            //printf("%lld %s", hash(i, now_p, bit_length), now_p);
        }
        //printf("\n");
        free(now_p);
    }

    //for(int j=0;j<(2<<20);j++)
        //printf("%d",bitArray_test_bit(bitArray,j));//按64位每行打印

    //检索word
    int ct = 0;
    char *now_w;
    //FILE *fl_words = fopen("D:\\CLionProjects\\BF_Search\\w_test.txt", "r");
    FILE *fl_words = fopen("D:\\CLionProjects\\BF_Search\\words-98w.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_words)){
        now_w = malloc(MAX_WORD*sizeof(char));
        fscanf(fl_words, "%s", now_w);
        /*if (bitArray_test_bit(bitArray, RSHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray, JSHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray,PJWHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray,BKDRHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray,DJBHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray,ELFHash(now_w)) == 1 &&
                bitArray_test_bit(bitArray,SDBMHash(now_w)) == 1 ) {
            //ct++;
            printf("%s %s\n", now_w, "YES");
        } else {

            printf("%s %s\n", now_w, "NO");
        }*/
        if (bitArray_test_bit(bitArray, hash(1, now_w, bit_length)) == 1&&
                bitArray_test_bit(bitArray, hash(2, now_w, bit_length)) == 1&&
                bitArray_test_bit(bitArray, hash(3, now_w, bit_length)) == 1&&
                bitArray_test_bit(bitArray, hash(4, now_w, bit_length)) == 1&&
                bitArray_test_bit(bitArray, hash(5, now_w, bit_length)) == 1&&
                bitArray_test_bit(bitArray, hash(6, now_w, bit_length)) == 1) {
            //printf("%s %s\n", now_w, "YES");
            ct++;
        }
        free(now_w);
    }
    printf("%d", ct);
    return 0;
}