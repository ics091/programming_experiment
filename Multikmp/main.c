#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PATTERN_NUM 20
#define MAX_PATTERNS 256

struct Pattern_ctn {
    char *pattern;
    int ctn;
    int pattern_len;
    int *next;
};

struct global_stats{
    long long mem;
    unsigned long long cmp_num;
}global_stats;

void *bupt_malloc(size_t size);
int read_pattern(FILE *file, struct Pattern_ctn *patternCtn);
void next_set(struct Pattern_ctn p);
int KMP(char *string, struct Pattern_ctn p);
void sort_2(struct Pattern_ctn *patternCtn, int l, int r);
void swap_pattern(struct Pattern_ctn *patternCtn, int i, int j);
int compare(struct Pattern_ctn *patternCtn, int j, int i);

int main() {
    //¶ÁÈ¡string.txtÎÄ¼þ
    FILE *fl_str = fopen("D:\\CLionProjects\\Multikmp\\string-kmp-test.txt", "r");
    char *string = bupt_malloc(880 * 1024 * 1024 * sizeof(char));
    char c;
    int k = 0;
    while (1) {
        c = (char)fgetc(fl_str);
        if (c == EOF) break;
        else {
            string[k++] = c;
        }
    }

    FILE *fl_patterns = fopen("D:\\CLionProjects\\Multikmp\\pattern-kmp-test.txt", "r");
    struct Pattern_ctn *patternCtn = bupt_malloc(PATTERN_NUM * sizeof(struct Pattern_ctn));
    for (int j = 0; j < PATTERN_NUM; ++j) {
        patternCtn[j].pattern = bupt_malloc(MAX_PATTERNS * sizeof(char));
    }

    int pattern_num = read_pattern(fl_patterns, patternCtn);

    for (int i = 0; i < pattern_num; ++i) {
        next_set(patternCtn[i]);
        /*
        printf("%s-next ",patternCtn[i].pattern);
        for (int j = 0; j < patternCtn[i].pattern_len; ++j) {
            printf("%d ",patternCtn[i].next[j]);
        }
        printf("\n");
         */
        //printf("%s %d\n",patternCtn[i].pattern, KMP(string,patternCtn[i]));
        patternCtn[i].ctn = KMP(string,patternCtn[i]);
    }

    /*
    for (int j = 0; j < patternCtn[11].pattern_len; ++j) {
        printf("%d ",patternCtn[11].next[j]);
    }
    printf("\n");
    printf("%d", KMP(string,patternCtn[11]));
     */
    sort_2(patternCtn,0,pattern_num - 1);

    FILE *result = fopen(".\\result.txt", "w+");
    for (int p = 0; p < pattern_num; ++p) {
        //printf("%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
        fprintf(result, "%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
    }

    fprintf(result, "%lld %lld\n", global_stats.mem/1024, global_stats.cmp_num/1000);
}

int read_pattern(FILE *file, struct Pattern_ctn *patternCtn) {
    char p[MAX_PATTERNS];
    char c;
    int i = 0;
    int j = 0;
    while (1) {
        c = (char)fgetc(file);
        if (c == '\n' || c == EOF) {
            p[i] = '\0';
            strcpy(patternCtn[j].pattern, p);
            patternCtn[j].ctn = 0;
            patternCtn[j].pattern_len = i;
            patternCtn[j].next = bupt_malloc(i * sizeof(int));
            j++;
            i = 0;
            p[0] = '\0';
        } else{
            p[i++] = c;
        }
        if (c == EOF) break;
    }
    return j;
}

void *bupt_malloc(size_t size){
    if(size <= 0){
        return NULL;
    }
    global_stats.mem += size;
    return (malloc(size));
}

void next_set(struct Pattern_ctn p) {
    int i = 0, j = -1;
    p.next[0] = -1;
    while (i < p.pattern_len) {
        if (j == -1 || p.pattern[i] == p.pattern[j]) {
            i++;
            j++;
            p.next[i] = j;
        } else
            j = p.next[j];
    }
}

int KMP(char *string, struct Pattern_ctn p) {
    int len1 = strlen(string), len2 = p.pattern_len, pos = 0;
    //printf("%lld %lld\n", len1, len2);
    while (pos <= len1 - len2) {
        int i = pos;
        int j = 0;

        while (i < len1 && j < len2) {
            //printf("------\n");
            //printf("%d %d\n", i, j);
            //printf("%d %d\n", string[i], p.pattern[j]);
            if (j==-1 || string[i] == p.pattern[j]) {
                i++;
                j++;
                global_stats.cmp_num++;
            } else
                j = p.next[j];
            //printf("%d %d\n", len1, len2);
            //printf("%d %d\n", i, j);
            //printf("______\n");
        }

        //printf("%d %d\n",i < len1, j < len2);
        //printf("%d %d\n", len1, len2);
        //printf("%d %d\n", i, j);
        if (j >= len2) {
            p.ctn++;
            //printf("match once\n");
            //printf("%d\n", p.ctn);
            pos = i - p.next[j-1] - 1;
        } else {
            pos = i-1;
        }
    }
    return p.ctn;
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

        // µÝ¹éµ÷ÓÃ
        sort_2(patternCtn, l, mid-1); // ÅÅÐòmid×ó±ß
        sort_2(patternCtn, mid + 1, r); // ÅÅÐòmidÓÒ±ß
    }
}

int compare(struct Pattern_ctn *patternCtn, int j, int i) {
    return patternCtn[i].ctn - patternCtn[j].ctn;
}

void swap_pattern(struct Pattern_ctn *patternCtn, int i, int j) {
    int tmp = patternCtn[i].ctn;
    int tmp_len = patternCtn[i].pattern_len;
    char *tmp_p = patternCtn[i].pattern;
    int *tmp_next = patternCtn[i].next;
    patternCtn[i].ctn = patternCtn[j].ctn;
    patternCtn[i].pattern_len = patternCtn[j].pattern_len;
    patternCtn[i].pattern = patternCtn[j].pattern;
    patternCtn[i].next = patternCtn[j].next;
    patternCtn[j].ctn = tmp;
    patternCtn[j].pattern_len = tmp_len;
    patternCtn[j].pattern = tmp_p;
    patternCtn[j].next = tmp_next;
}