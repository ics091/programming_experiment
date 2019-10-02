#include <stdio.h>
#include "hash_construction.h"

struct Global_stats global_stats;

int main() {

    global_stats.mem = 0;
    global_stats.cmp_num = 0;
    int words_ct = 0;
    int patterns_ct = 0;
    int words_match = 0;

    struct Hash_table *table;
    table = bupt_malloc(PATTERN_NUM);
    unsigned int length = 249997;
    table->length = length;
    table->chain = bupt_malloc(length);
    for (unsigned int i = 0; i < length; ++i) {
        table->chain[i] = (struct Chain_Node *)bupt_malloc(1);
        if (table->chain[i] == NULL) {printf("error...");}
        else{
            //头结点
            table->chain[i]->string = malloc(MAX_PATTERNS* sizeof(char));
            table->chain[i]->next_node = NULL;
        }
    }

    FILE *fl_patterns = fopen("patterns-127w_2.txt", "r");
    if (fl_patterns == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_patterns)){

        //给新节点分配存储空间
        struct Chain_Node *node = bupt_malloc(1);
        node->string = malloc(MAX_PATTERNS*sizeof(char));

        fscanf(fl_patterns, "%s", node->string);
        //printf("%d %s\n", Hash_fun(node, table->length), node->string);

        //添加新结点到链表
        char *n_word = node->string;
        unsigned int p = Hash_fun_l(n_word, length);
        if (table->chain[p]->next_node != NULL){
            //链表非空------产生冲突
            node->next_node = table->chain[p]->next_node;
            table->chain[p]->next_node = node;
            //printf("%d %s %s\n", p, node->string, "crash");
        } else{ //链表为空表
            table->chain[p]->next_node = node;
            node->next_node = NULL;
            //printf("%d %s %s\n", p, node->string, "empty");
        }
    }

    //比对
    char **words;
    words = malloc(WORD_NUM * sizeof(char*));
    for (int i = 0; i < WORD_NUM; ++i) {
        words[i] = malloc(MAX_WORD* sizeof(char));
    }

    //从文件读取words
    FILE *fl_words = fopen("words-98w.txt", "r");
    if (fl_words == 0){
        printf("open fail...\n");
        return 0;
    }
    while (!feof(fl_words)){
        fscanf(fl_words,"%s",*(words+(words_ct++)));
        //printf("%s\n", words[words_ct-1]);
    }

    //在hash表中查找比对
    int c_yes = 0;
    int c_no = 0;
    FILE *result = fopen("result.txt", "w+");
    struct Chain_Node *p;
    for (int j = 0; j < words_ct-1; ++j) {
        unsigned int pstn = Hash_fun_l(words[j], length);
        int res = 0;
        p = table->chain[pstn];
        while (p != NULL){
            res = byte_cmp_pls(p->string, words[j]);
            if (res == 1) break;
            else p = p->next_node;
        }
        if (res == 1) {
            words_match++;
            fprintf(result, "%s %s\n",words[j], "yes");
        }
        else {
            fprintf(result, "%s %s\n",words[j], "no");
        }
    }

    fprintf(result, "%lld %lld %d %d\n",(MAX_PATTERNS*global_stats.mem)/1024, global_stats.cmp_num, words_ct, words_match);

    free(table);
    return 0;
}