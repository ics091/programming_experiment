#include <stdio.h>
#include "radix4tree.h"

#define WORD_NUM 986005
#define PATTERN_NUM 1280690

int main() {
    //初始化一棵radix_tree
    struct rt_node *T = Init_rdx_tree();

    //读取words
    char **words;
    words = malloc(WORD_NUM * sizeof(char*));
    for (int i = 0; i < WORD_NUM; ++i) {
        words[i] = malloc(MAX_STRINGL* sizeof(char));
    }

    FILE *fl_words = fopen("D:\\CLionProjects\\radix4_search\\words-98w.txt","r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    } else {
        global_stats.words_num = read(fl_words, words);
    }

    //读取patterns
    char **patterns;
    patterns = malloc(PATTERN_NUM * sizeof(char*));
    for (int k = 0; k < PATTERN_NUM; ++k) {
        patterns[k] = malloc(MAX_STRINGL * sizeof(char));
    }
    FILE *fl_patterns = fopen("D:\\CLionProjects\\radix4_search\\patterns-127w.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    } else {
        read(fl_patterns, patterns);
    }

    //插入patterns到radix_tree
    for (int j = 0; j < PATTERN_NUM; ++j) {
        struct Bits *bits = init_bits(patterns[j]);
        //for (int i = 0; i < bits->length; ++i) {
        //    printf("%d", bits_get(bits, i));
        //}
        //printf("\n%d\n", bits->length);
        Insert(T, bits);
    }

    FILE *result = fopen("..\\result.txt", "w+");
    //匹配words
    for (int m = 0; m < global_stats.words_num; ++m) {
        struct Bits *word_bits = init_bits(words[m]);
        int r = Search(T, word_bits);
        if (r == 1) {
            global_stats.words_success_num ++;
            //printf("%s yes\n", words[m]);
            fprintf(result, "%s %s\n",words[m], "yes");
        } else {
            //printf("%s no\n", words[m]);
            fprintf(result, "%s %s\n",words[m], "no");
        }
    }
    fprintf(result, "%lld %lld %lld %d %d\n",global_stats.node_num, global_stats.mem/1024, global_stats.cmp_num/1000, global_stats.words_num, global_stats.words_success_num);
    return 0;
}
