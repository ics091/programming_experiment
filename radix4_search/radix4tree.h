//
// Created by icsri on 2019/11/2.
//

#ifndef RADIX4_SEARCH_RADIX4TREE_H
#define RADIX4_SEARCH_RADIX4TREE_H

#endif //RADIX4_SEARCH_RADIX4TREE_H

#include "base_func.h"
#include "bits_.h"

//定义radix_tree 节点类型
struct rt_node {
    int node_type;
    struct rt_node *parent;
    struct rt_node *child_0;
    struct rt_node *child_1;
    struct rt_node *child_2;
    struct rt_node *child_3;
    int a_finish;
};

struct rt_node *Init_rdx_tree() {
    struct rt_node *headnode = bupt_malloc(sizeof(struct rt_node));
    headnode->node_type = -1;
    headnode->parent = NULL;
    headnode->child_0 = NULL;
    headnode->child_1 = NULL;
    headnode->child_2 = NULL;
    headnode->child_3 = NULL;
    headnode->a_finish = 0;
    return headnode;
}

struct rt_node *new_node_init(struct rt_node *node) {
    node->node_type = -1;
    node->parent = NULL;
    node->child_0  = NULL;
    node->child_1  = NULL;
    node->child_2  = NULL;
    node->child_3  = NULL;
    node->a_finish = 0;
    global_stats.node_num ++;
    return node;
}

struct rt_node *Insert(struct rt_node *node, struct Bits *b) {
    if (b->length <= 0) return node;
    if (b->start <= b->length - 2) {
        int x = two_bits_get(b, b->start);
        //printf("pre node_type: %d ", node->node_type);
        switch (x) {
            case 0:
                //放到当前节点的child0节点
                //printf("in 00 ");
                if (node->child_0 == NULL) {
                    //如果当前节点的child0节点为空
                    //printf("null\n");
                    struct rt_node *new_node = bupt_malloc(sizeof(struct rt_node));
                    new_node = new_node_init(new_node);
                    new_node->parent = node;
                    new_node->node_type = 0;
                    node->child_0 = new_node;
                    //bits的读取位置移动2位
                    b->start += 2;
                    //printf("%d", b->start);
                    //从新节点开始插入
                    Insert(node->child_0, b);
                } else { //如果存在，继续从child0节点插入，bits的读取位置移动2位
                    //printf("not null\n");
                    b->start += 2;
                    //printf("%d", b->start);
                    Insert(node->child_0, b);
                }
                break;
            case 1:
                //放到当前节点的child1节点
                //printf("in 01 ");
                if (node->child_1 == NULL) {
                    //如果当前节点的child1节点为空
                    //printf("null\n");
                    struct rt_node *new_node = bupt_malloc(sizeof(struct rt_node));
                    new_node = new_node_init(new_node);
                    new_node->parent = node;
                    new_node->node_type = 1;
                    node->child_1 = new_node;
                    //bits的读取位置移动2位
                    b->start += 2;
                    //printf("%d", b->start);
                    //从新节点开始插入
                    Insert(node->child_1, b);
                } else { //如果存在，继续从child0节点插入，bits的读取位置移动2位
                    //printf("not null\n");
                    b->start += 2;
                    //printf("%d", b->start);
                    Insert(node->child_1, b);
                }
                break;
            case 2:
                //放到当前节点的child2节点
                //printf("in 10 ");
                if (node->child_2 == NULL) {
                    //如果当前节点的child2节点为空
                    //printf("null\n");
                    struct rt_node *new_node = bupt_malloc(sizeof(struct rt_node));
                    new_node = new_node_init(new_node);
                    new_node->parent = node;
                    new_node->node_type = 2;
                    node->child_2 = new_node;
                    //bits的读取位置移动2位
                    b->start += 2;
                    //printf("%d", b->start);
                    //从新节点开始插入
                    Insert(node->child_2, b);
                } else { //如果存在，继续从child2节点插入，bits的读取位置移动2位
                    //printf("not null\n");
                    b->start += 2;
                    //printf("%d", b->start);
                    Insert(node->child_2, b);
                }
                break;
            case 3:
                //printf("in 11 ");
                //放到当前节点的child3节点
                if (node->child_3 == NULL) {
                    //如果当前节点的child3节点为空
                    //printf("null\n");
                    struct rt_node *new_node = bupt_malloc(sizeof(struct rt_node));
                    new_node = new_node_init(new_node);
                    new_node->parent = node;
                    new_node->node_type = 3;
                    node->child_3 = new_node;
                    //bits的读取位置移动2位
                    b->start += 2;
                    //printf("%d", b->start);
                    //从新节点开始插入
                    Insert(node->child_3, b);
                } else { //如果存在，继续从child3节点插入，bits的读取位置移动2位
                    //printf("not null\n");
                    b->start += 2;
                    //printf("%d", b->start);
                    Insert(node->child_3, b);
                }
                break;
            default:
                printf("error ");
                break;
        }
    } else {
        node->a_finish = 1;
        //printf("end\n");
    }
    return node;
}


int Search(struct rt_node *node, struct Bits *b) {
    if (b->length <= 0) return -1;
    int x = two_bits_get(b, b->start);
    if (b->start <= b->length - 2) {
        switch (x) {
            case 0:
                global_stats.cmp_num++;
                if (node->child_0 == NULL) return -1;
                else {
                    b->start += 2;
                    Search(node->child_0, b);
                }
                break;
            case 1:
                global_stats.cmp_num++;
                if (node->child_1 == NULL) return -1;
                else {
                    b->start += 2;
                    Search(node->child_1, b);
                }
                break;
            case 2:
                global_stats.cmp_num++;
                if (node->child_2 == NULL) return -1;
                else {
                    b->start += 2;
                    Search(node->child_2, b);
                }
                break;
            case 3:
                global_stats.cmp_num++;
                if (node->child_3 == NULL) return -1;
                else {
                    b->start += 2;
                    Search(node->child_3, b);
                }
                break;
            default:
                printf("error");
                break;
        }
    } else {
        if (node->a_finish == 1) return 1;
        else return -1;
    };
}

