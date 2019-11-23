#include <stdio.h>
#include "trie.h"
int main() {
    /*
    char pat[128] = "ac自动机";
    int l;
    int *list = Create_ASCIIList(pat,&l);
    for (int i = 0; i < 8; ++i) {
        printf("%d ", list[i]);
    }
     */
    struct Node *trie = init_x();

    FILE *fl_patterns = fopen("D:\\CLionProjects\\ac_auto\\pattern-kmp-test.txt", "r");
    struct Pattern_ctn *patternCtn = malloc(PATTERN_NUM * sizeof(struct Pattern_ctn));
    for (int i = 0; i < PATTERN_NUM; ++i) {
        patternCtn[i].pattern = bupt_malloc(MAX_PATTERNS * sizeof(char));
    }

    //node数组
    struct Node **node_list = malloc(PATTERN_NUM * sizeof(struct Node*));

    int pattern_num = read_pattern(fl_patterns, patternCtn);
    //printf("%d",pattern_num);
    for (int j = 0; j < pattern_num; ++j) {
        int len;
        int *list = Create_ASCIIList(patternCtn[j].pattern, &len);
        node_list[j] = Insert_trie(trie, list, len, 0);
        printf("%p\n", node_list[j]);
    }

    //读取string
    //读取string.txt文件
    FILE *fl_str = fopen("D:\\CLionProjects\\ac_auto\\string-kmp-test.txt", "r");
    char *string = bupt_malloc(880 * 1024 * 1024 * sizeof(char));
    char c;
    int i = 0;
    while (1) {
        c = (char)fgetc(fl_str);
        if (c == EOF) break;
        else {
            string[i++] = c;
        }
    }
    //建立fail指针
    build_fail(trie);
    //查找
    struct Node *root = trie;
    struct Node *p = root;
    int len = strlen(string);
    for (int k = 0; k < len; ++k) {
        int ascii = postion(string[k]);
        global_stats.cmp_num++;
        while (p->child[ascii] == NULL && p != root) {
            p = p->fail;
            global_stats.cmp_num++;
        }
        if (p->child[ascii] != NULL) {
            p = p->child[ascii];
            struct Node *now = p;
            while (now != root){
                ++now->a_finish;
                now = now->fail;
                global_stats.cmp_num++;
            }
        }
    }

    //输出
    for (int p = 0; p < pattern_num; ++p) {
        //printf("%s %d\n", patternCtn[p].pattern, node_list[p]->a_finish);
        patternCtn[p].ctn = node_list[p]->a_finish;
    }

    sort_2(patternCtn, 0, pattern_num - 1);
    //输出
    FILE *result = fopen("..\\result.txt", "w+");
    for (int p = 0; p < pattern_num; ++p) {
        //printf("%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
        fprintf(result, "%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
    }

    fprintf(result, "%lld %lld\n", global_stats.mem/1024, global_stats.cmp_num/1000);
    return 0;
}