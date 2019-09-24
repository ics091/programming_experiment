#include <stdio.h>
#include "statistics.h"

struct Global_stats global_stats;
#define MAX_WORD 30
#define MAX_PATTERNS 30
#define WORD_NUM 987000
#define PATTERN_NUM 1380000

int main() {
    global_stats.mem = 0;
    global_stats.cmp_num = 0;
    int words_ct = 0;
    int patterns_ct = 0;


    char **words;
    words = malloc(WORD_NUM * sizeof(char*));
    for (int i = 0; i < WORD_NUM; ++i) {
        words[i] = bupt_malloc(MAX_WORD);
    }
    char **patterns;
    patterns = malloc((PATTERN_NUM * sizeof(char*)));
    for (int j = 0; j < PATTERN_NUM; ++j) {
        patterns[j] = bupt_malloc(MAX_PATTERNS);
    }

    //读取words文件
    FILE *fl_words = fopen("D:\\CLionProjects\\C_Test\\words-98w.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_words)){
        fscanf(fl_words,"%s",*(words+(words_ct++)));
        //printf("%s\n", words[words_ct-1]);
    }
    //读取patterns文件
    FILE *fl_patterns = fopen("D:\\CLionProjects\\C_Test\\patterns-127w.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_patterns)){
        fscanf(fl_patterns, "%s", *(patterns+(patterns_ct++)));
        //printf("%s\n", patterns[patterns_ct-1]);
    }
    printf("%d %d", words_ct, patterns_ct);

    /*for (int k = 0; k < words_ct; ++k) {
        int in_pattern = 0;
        for (int p = 0; p < patterns_ct; ++p) {
            //in_pattern|=  byte_cmp_pls(words[k], patterns[p]);
          in_pattern = byte_cmp_pls(words[k], patterns[p]);
          if (in_pattern) break;

        }
        if (in_pattern){
            printf("%s %s\n", words[k], "YES");
        } else{
            printf("%s %s\n", words[k], "NO");
        }
    }*/

    fclose(fl_patterns);
    fclose(fl_words);
    //free(patterns);
    //free(words);

    return 0;
}