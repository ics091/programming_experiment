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
    //�ڵ��failָ��
    struct Node *fail;
    //���ӽڵ� 256��
    struct Node **child;
    //�Ƿ�һ�����ʽ�β
    int a_finish;
    //���е�nextָ��
    struct Node *next_node;
};

typedef struct Queue {
    struct Node *front;
    struct Node *rear;
}Queue;

//��ʼ������
Queue *Init_queue() {
    Queue *q =  (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

//�ж��Ƿ��
int Qisempty(Queue *q) {
    return q->front == NULL;
}

//���
void Q_insert(Queue *q, struct Node *node) {
    //Q_node *node = (Q_node *)malloc(sizeof(Q_node));
    if (node == NULL)
        return;
    //node->data = data;
    node->next_node = NULL;//β�巨������Ԫ��ָ���
    if(q->rear == NULL)
    {
        q->front = node;
        q->rear = node;
    }
    else{
        q->rear->next_node = node;//��n��Ϊ��ǰ��β���ڵ���һ�ڵ�
        q->rear= node;//β��ָ��ָ��n
    }
}
//����
struct Node *Q_pop(Queue *q) {
    struct Node *node = q->front;
    if (node == NULL)
        return NULL;
    if(q->front == q->rear)//�Ƿ�ֻ��һ��Ԫ��
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
        //�ӵ�ǰ�ڵ����
        //�����ǰ�ڵ�Ķ�Ӧpos���ӽڵ�Ϊ�� ��Ϊ�½ڵ����
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
        //�����ڵ�Ϊ�ýڵ�ĵ�������1
        return node;
        printf("------\n");
    }
}

//����failָ��
void build_fail(struct Node *trie) {
    struct Node *root = trie;
    Queue *queue = Init_queue();
    printf("queue init\n");
    //���ڶ�����ֵĽڵ����
    for (int i = 0; i < 255; ++i) {
        if (root->child[i] != NULL) {
            //�����ڵ�ĺ��ӽڵ��failָ��ָ����ڵ�
            root->child[i]->fail = root;
            //���
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
                //���
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

        // �ݹ����
        sort_2(patternCtn, l, mid-1); // ����mid���
        sort_2(patternCtn, mid + 1, r); // ����mid�ұ�
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
