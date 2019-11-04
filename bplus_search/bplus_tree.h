//
// Created by icsri on 2019/10/29.
//

#ifndef BPLUS_SEARCH_BPLUS_TREE_H
#define BPLUS_SEARCH_BPLUS_TREE_H

#endif //BPLUS_SEARCH_BPLUS_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "base_func.h"
#define M (4)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)
typedef struct BPlusNode *BPlusTree,*Position;
typedef char* KeyType;
struct BPlusNode{
    int KeyNum;
    KeyType Key[M + 1];
    BPlusTree Children[M + 1];
    BPlusTree Next;
};

KeyType Unavailable = " ";

BPlusTree MallocNewNode(){
    BPlusTree NewNode;
    int i;
    NewNode = bupt_malloc(sizeof(struct BPlusNode));
    global_stats.nodenum++;
    if (NewNode == NULL)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < M + 1){
        NewNode->Key[i] = (char *)bupt_malloc(128 * sizeof(char));;
        NewNode->Children[i] = NULL;
        i++;
    }
    NewNode->Next = NULL;
    NewNode->KeyNum = 0;
    return NewNode;
}

//初始化

BPlusTree Initialize(){
    BPlusTree T;
    if (M < (3)){
        exit(EXIT_FAILURE);
    }
    T = MallocNewNode();
    return T;
}

Position InsertElement(int isKey, Position Parent,Position X,KeyType Key,int i,int j){
    int k;
    if (isKey){
        /* ²åÈëkey */
        k = X->KeyNum - 1;
        while (k >= j){
            strcpy(X->Key[k + 1],X->Key[k]);
            //X->Key[k + 1] = X->Key[k];
            k--;
        }
        strcpy(X->Key[j],Key);
        //X->Key[j] = Key;
        if (Parent != NULL)
            strcpy(Parent->Key[i],X->Key[0]);
        //Parent->Key[i] = X->Key[0];
        X->KeyNum++;
    }else{
        if (X->Children[0] == NULL){
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }
        k = Parent->KeyNum - 1;
        while (k >= i){
            Parent->Children[k + 1] = Parent->Children[k];
            strcpy(Parent->Key[k + 1],Parent->Key[k]);
            //Parent->Key[k + 1] = Parent->Key[k];
            k--;
        }
        strcpy(Parent->Key[i],X->Key[0]);
        //Parent->Key[i] = X->Key[0];
        Parent->Children[i] = X;
        Parent->KeyNum++;
    }
    return X;
}


BPlusTree SplitNode(Position Parent,Position X,int i){
    int j,k,Limit;
    Position NewNode;
    NewNode = MallocNewNode();
    k = 0;
    j = X->KeyNum / 2;
    Limit = X->KeyNum;
    while (j < Limit){
        if (X->Children[0] != NULL){
            NewNode->Children[k] = X->Children[j];
            X->Children[j] = NULL;
        }
        strcpy(NewNode->Key[k],X->Key[j]);
        //NewNode->Key[k] = X->Key[j];
        strcpy(X->Key[j],Unavailable);
        //X->Key[j] = Unavailable;
        NewNode->KeyNum++;X->KeyNum--;
        j++;k++;
    }
    if (Parent != NULL)
        InsertElement(0, Parent, NewNode, Unavailable, i + 1, Unavailable);
    else{
        /* Èç¹ûÊÇXÊÇ¸ù£¬ÄÇÃ´´´½¨ÐÂµÄ¸ù²¢·µ»Ø */
        Parent = MallocNewNode();
        InsertElement(0, Parent, X, Unavailable, 0, Unavailable);
        InsertElement(0, Parent, NewNode, Unavailable, 1, Unavailable);
        return Parent;
    }
    return X;
}

BPlusTree RecursiveInsert(BPlusTree T,KeyType Key,int i,BPlusTree Parent){
    int j,Limit;
    /* ²éÕÒ·ÖÖ§ */
    j = 0;
    while (j < T->KeyNum && str_cmp(Key ,T->Key[j]) >= 0){
        /* ÖØ¸´Öµ²»²åÈë */
        if (str_cmp(Key ,T->Key[j]) == 0)
            return T;
        j++;
    }
    if (j != 0 && T->Children[0] != NULL) j--;
    /* Ê÷Ò¶ */
    if (T->Children[0] == NULL)
        T = InsertElement(1, Parent, T, Key, i, j);
        /* ÄÚ²¿½Úµã */
    else
        T->Children[j] = RecursiveInsert(T->Children[j], Key, j, T);
    /* µ÷Õû½Úµã */
    Limit = M;
    if (T->KeyNum > Limit){
        T = SplitNode(Parent, T, i);
    }
    if (Parent != NULL)
        strcpy(Parent->Key[i], T->Key[0]);
    //Parent->Key[i] = T->Key[0];
    return T;
}

BPlusTree Insert(BPlusTree T,KeyType Key){
    return RecursiveInsert(T, Key, 0, NULL);
}

BPlusTree Destroy(BPlusTree T){
    int i,j;
    if (T != NULL){
        i = 0;
        while (i < T->KeyNum + 1){
            Destroy(T->Children[i]);i++;
        }
        free(T);
        T = NULL;
    }
    return T;
}


int Search(BPlusTree T, char * e)
{
    if(!T)
    {
        return 0;
    }
    else{
        int j = 0;
        while(j < T->KeyNum && str_cmp(e, T->Key[j]) >= 0){
            if(str_cmp(e, T->Key[j]) == 0){
                return 1;
            }
            j++;
        }
        if (j != 0 && T->Children[0] != NULL) j--;
        if(j >= T->KeyNum){
            return 0;
        }
        else {
            return Search(T->Children[j], e);
        }
    }
}
