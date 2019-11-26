#include <stdio.h>
#include "trie.h"
#include <time.h>
int main() {

    int begintime, endtime;
    begintime = clock();

    struct Node *trie = init_x();


    FILE *fl_patterns = fopen("..\\pattern.txt", "r");
    struct Pattern_ctn *patternCtn = bupt_malloc(PATTERN_NUM * sizeof(struct Pattern_ctn));
    for (int i = 0; i < PATTERN_NUM; ++i) {
        patternCtn[i].pattern = bupt_malloc(MAX_PATTERNS * sizeof(char));
        //patternCtn[i].ctn = bupt_malloc(MAX_PATTERNS * sizeof(int));
    }

    //node数组
    struct Node **node_list = bupt_malloc(PATTERN_NUM * sizeof(struct Node*));

    //读取patterns
    int pattern_num = read_pattern(fl_patterns, patternCtn);

    printf("read %d patterns\n", pattern_num);
    //printf("%d",pattern_num);
    for (int j = 0; j < pattern_num; ++j) {
        int len;
        int *list = Create_ASCIIList(patternCtn[j].pattern, &len);
        node_list[j] = Insert_trie(trie, list, len, 0);
    }


    //读取string
    //读取string.txt文件
    FILE *fl_str = fopen("..\\string.txt", "r");
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
    printf("read string finish\n");
    //建立fail指针
    build_fail(trie);
    printf("bulid fail finish\n");
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

    printf("search finish\n");

    //输出
    for (int p = 0; p < pattern_num; ++p) {
        //printf("%s %d\n", patternCtn[p].pattern, node_list[p]->a_finish);
        patternCtn[p].ctn = node_list[p]->a_finish;
    }

    printf("set ctn num\n");

    sort_2(patternCtn, 0, pattern_num - 1);

    printf("sort finish\n");

    //输出
    FILE *result = fopen(".\\result.txt", "w+");
    for (int k = 0; k < pattern_num; ++k) {
        //printf("%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
        fprintf(result, "%s %d\n", patternCtn[k].pattern, patternCtn[k].ctn);
    }

    fprintf(result, "%lldKB %lldK次\n", global_stats.mem/1024, global_stats.cmp_num/1000);
    endtime = clock();
    printf("cost %dms",endtime - begintime);
    /*

    char a[24] = "a";
    int ctn = 0;
    for (int k = 0; k < pattern_num; ++k) {
        if (byte_cmp_pls(a, patternCtn[k].pattern) == 1) ctn++;
    }
    printf("%d",ctn);
     */
    return 0;
}