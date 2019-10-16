#include <stdio.h>
#include "createbtree.h"

#define WORD_NUM 11
int main() {

    char **words;
    int words_c = 0;
    words = malloc(WORD_NUM * sizeof(char*));
    for (int i = 0; i < WORD_NUM; ++i) {
        words[i] = malloc(MAX_STRINGL * sizeof(char));
    }

    //¶ÁÈ¡wordsÎÄ¼þ
    FILE *fl_words = fopen("D:\\CLionProjects\\btree_search\\words_test.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }

    read(fl_words, words);
    for (int j = 0; j < WORD_NUM; ++j) {
        printf("%s\n", words[j]);
    }
    return 0;
}