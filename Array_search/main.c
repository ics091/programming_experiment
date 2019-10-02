#include <stdio.h>
#include "statistics.h"

#define MAX_WORD 256
#define MAX_PATTERNS 256
#define WORD_NUM 986000
#define PATTERN_NUM 1271000

struct Global_stats global_stats; //统计结构体

int main() {
    global_stats.mem = 0;
    global_stats.cmp_num = 0;
    int words_ct = 0;
    int patterns_ct = 0;
    int words_match = 0;

    //分配patterns数组和words数组的内存
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
    FILE *fl_words = fopen(".\\words-98w.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_words)){
        fscanf(fl_words,"%s",*(words+(words_ct++)));
        //printf("%s\n", words[words_ct-1]);
    }
    //读取patterns文件
    FILE *fl_patterns = fopen(".\\patterns-127w_2.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_patterns)){
        fscanf(fl_patterns, "%s", *(patterns+(patterns_ct++)));
        //printf("%s\n", patterns[patterns_ct-1]);
    }
    //printf("%d %d %d", words_ct, patterns_ct, global_stats.mem/1024);

    FILE *result = fopen(".\\result.txt", "w+");
    for (int k = 0; k < words_ct; ++k) {
        int in_pattern = 0;
        for (int p = 0; p < patterns_ct; ++p) {
            //in_pattern|=  byte_cmp_pls(words[k], patterns[p]);
          in_pattern = byte_cmp_pls(words[k], patterns[p]);
          if (in_pattern) break;

        }
        if (in_pattern){
            words_match++;
            fprintf(result, "%s %s\n",words[k], "yes");
        } else{
            fprintf(result, "%s %s\n",words[k], "no");
        }
    }

    //最后一行输出
    fprintf(result, "%lld %lld %d %d\n",global_stats.mem/1024, global_stats.cmp_num, words_ct, words_match);

    fclose(fl_patterns);
    fclose(fl_words);
    free(patterns);
    free(words);
    return 0;
}