#include <stdio.h>
#include "bplus_tree.h"
#define WORD_NUM 986005
#define PATTERN_NUM 1280690
int main() {

    char **patterns;
    int patterns_c = 0;
    patterns = malloc(PATTERN_NUM * sizeof(char*));
    for (int k = 0; k < PATTERN_NUM; ++k) {
        patterns[k] = malloc(MAX_STRINGL * sizeof(char));
    }

    char **words;
    int words_c = 0;
    words = malloc(WORD_NUM * sizeof(char*));
    for (int i = 0; i < WORD_NUM; ++i) {
        words[i] = malloc(MAX_STRINGL * sizeof(char));
    }


    //读取patterns
    FILE *fl_patterns = fopen("patterns-127w.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    }

    read(fl_patterns,patterns);

    //读取words文件
    FILE *fl_words = fopen("words-98w.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }

    global_stats.words_num = read(fl_words, words);

    BPlusTree T;
    T = Initialize();
    char* c = (char *)malloc(MAX_STRINGL * sizeof(char));
    for (int i = 0; i < PATTERN_NUM; ++i) {
        T = Insert(T, patterns[i]);
    }
    global_stats.cmp_num = 0;

    FILE * result = fopen(".\\result.txt", "w");
    global_stats.words_success_num = 0;
    for (unsigned int j = 0; j < global_stats.words_num; ++j) {
        if (Search(T, words[j])){
            //hitCount++;
            global_stats.words_success_num ++;
            fprintf(result, "%s yes\n", words[j]);
        } else {
            fprintf(result, "%s no\n", words[j]);
        }
    }

    fprintf(result, "%lld %lld %lld %d %d\n",global_stats.nodenum, global_stats.mem/1024, global_stats.cmp_num/1000, global_stats.words_num, global_stats.words_success_num);
    fclose(result);
    Destroy(T);
    return 0;

}
