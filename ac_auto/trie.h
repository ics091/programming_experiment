//
// Created by icsri on 2019/11/21.
//

#ifndef AC_AUTO_TRIE_H
#define AC_AUTO_TRIE_H

#endif //AC_AUTO_TRIE_H

#include "base_func.h"
#include "string.h"
#include "memory.h"
int postion(int ascii);
int compare(struct Pattern_ctn *patternCtn, int j, int i);
void swap_pattern(struct Pattern_ctn *patternCtn, int i, int j);
struct Node {
    int ascii;
    //节点的fail指针
    struct Node *fail;
    //孩子节点 256叉
    struct Node **child;
    //是否一个单词结尾
    int a_finish;
    //队列的next指针
    struct Node *next_node;
};

typedef struct Queue {
    struct Node *front;
    struct Node *rear;
}Queue;

//初始化队列
Queue *Init_queue() {
    Queue *q =  (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

//判断是否空
int Qisempty(Queue *q) {
    return q->front == NULL;
}

//入队
void Q_insert(Queue *q, struct Node *node) {
    //Q_node *node = (Q_node *)malloc(sizeof(Q_node));
    if (node == NULL)
        return;
    //node->data = data;
    node->next_node = NULL;//尾插法，插入元素指向空
    if(q->rear == NULL)
    {
        q->front = node;
        q->rear = node;
    }
    else{
        q->rear->next_node = node;//让n成为当前的尾部节点下一节点
        q->rear= node;//尾部指针指向n
    }
}
//出队
struct Node *Q_pop(Queue *q) {
    struct Node *node = q->front;
    if (node == NULL)
        return NULL;
    if(q->front == q->rear)//是否只有一个元素
    {
        q->front = NULL;
        q->rear = NULL;
        return node;
    }
    else{
        q->front = q->front->next_node;
        return node;
    }
}


struct Node *init_x() {
    struct Node *node = bupt_malloc(sizeof(struct Node));
    node->ascii = 256;
    node->fail = NULL;
    node->a_finish = 0;
    node->next_node = NULL;
    node->child = bupt_malloc(256 * sizeof(struct Node*));
    memset(node->child,0,256 * sizeof(struct Node*));
    return node;
}
struct Node *Insert_trie(struct Node *node, const int *ascii_list, int len, int i) {

    if (i < len) {
        int _ascii = ascii_list[i];
        int pos = postion(_ascii);
        //从当前节点插入
        //如果当前节点的对应pos孩子节点为空 作为新节点插入
        if (node->child[pos] == NULL) {
            node->child[pos] = init_x();
            node->child[pos]->ascii = _ascii;
            i++;
            printf("%d %d %d\n",_ascii, node->child[pos]->ascii, i-1);
            Insert_trie(node->child[pos], ascii_list, len, i);
        } else {
            i++;
            printf("%d %d %d exist\n",_ascii, node->child[pos]->ascii, i-1);
            Insert_trie(node->child[pos], ascii_list, len, i);
        }
    } else {
        //结束节点为该节点的单词数加1
        return node;
        printf("------\n");
    }
}

//构建fail指针
void build_fail(struct Node *trie) {
    struct Node *root = trie;
    Queue *queue = Init_queue();
    printf("queue init\n");
    //将第二层出现的节点入队
    for (int i = 0; i < 255; ++i) {
        if (root->child[i] != NULL) {
            //将根节点的孩子节点的fail指针指向根节点
            root->child[i]->fail = root;
            //入队
            Q_insert(queue, root->child[i]);
            printf("%d ", root->child[i]->ascii);
        }
    }

    printf("\n");

    while (!Qisempty(queue)) {
        printf("------\n");
        printf("start bulid %d\n", queue->front->ascii);
        struct Node *now = queue->front;
        Q_pop(queue);

        for (int j = 0; j < 256; ++j) {
            if (now->child[j] != NULL) {
                struct Node *f = now->fail;
                while (f != NULL) {
                    if (f->child[j] != NULL) {
                        now->child[j]->fail = f->child[j];
                        break;
                    }
                    f = f->fail;
                }
                if (f == NULL) now->child[j]->fail = root;
                //入队
                Q_insert(queue, now->child[j]);
            }
        }
        printf("finish\n");
    }
}

int *Create_ASCIIList(char *string, int *l) {
    int len = (int)strlen(string);
    int *list = malloc(len * sizeof(int));
    *l = len;
    for (int i = 0; i < len; ++i) {
        list[i] = string[i];
    }
    return list;
}

int postion(int ascii) {
    if (ascii < 0) return 256 + ascii;
    else return ascii;
}

void sort_2(struct Pattern_ctn *patternCtn, int l, int r) {
    if (l < r) {
        int left = l;
        int right = r;
        int mid = l;

        int a = compare(patternCtn, l, r), b = compare(patternCtn, l, (l + r) / 2),
                c = compare(patternCtn, (l + r) / 2, r);
        if (a == b && b == c) {
            mid = (l + r) / 2;
        } else if (a == c) {
            mid = l;
        } else {
            mid = r;
        }

        while (left < right) {
            while (left < right && mid < right && compare(patternCtn, right, mid) >= 0) {
                right--;
            }
            if (left < right) {
                swap_pattern(patternCtn, left++, right);
                mid = right;
            }
            while (left < right && left < mid && compare(patternCtn, left, mid) < 0) {
                left++;
            }
            if (left < right && left < mid) {
                swap_pattern(patternCtn, right--, left);
                mid = left;
            }
        }
        // swap(left, mid);

        // 递归调用
        sort_2(patternCtn, l, mid-1); // 排序mid左边
        sort_2(patternCtn, mid + 1, r); // 排序mid右边
    }
}

int compare(struct Pattern_ctn *patternCtn, int j, int i) {
    return patternCtn[i].ctn - patternCtn[j].ctn;
}

void swap_pattern(struct Pattern_ctn *patternCtn, int i, int j) {
    int tmp = patternCtn[i].ctn;
    char *tmp_p = patternCtn[i].pattern;
    patternCtn[i].ctn = patternCtn[j].ctn;
    patternCtn[i].pattern = patternCtn[j].pattern;
    patternCtn[j].ctn = tmp;
    patternCtn[j].pattern = tmp_p;
}
