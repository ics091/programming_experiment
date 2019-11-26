#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PATTERN_NUM 1500
#define MAX_PATTERNS 256

struct Pattern_ctn {
    char *pattern;
    int ctn;
};

struct global_stats{
    long long mem;
    unsigned long long cmp_num;
}global_stats;

int str_cmp(const char *pattern, const char *string);
int read_pattern(FILE *file, struct Pattern_ctn *patternCtn);
int compare(struct Pattern_ctn *patternCtn, int i, int j);
void swap_pattern(struct Pattern_ctn *patternCtn, int i, int j);
void sort_2(struct Pattern_ctn *patternCtn, int l, int r);
void *bupt_malloc(size_t size);

int main() {
    int begintime, endtime;
    begintime = clock();
    //¶ÁÈ¡string.txtÎÄ¼þ
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

    FILE *fl_patterns = fopen("..\\pattern_bf_kmp.txt", "r");
    struct Pattern_ctn *patternCtn = bupt_malloc(PATTERN_NUM * sizeof(struct Pattern_ctn));
    for (int j = 0; j < PATTERN_NUM; ++j) {
        patternCtn[j].pattern = bupt_malloc(MAX_PATTERNS * sizeof(char));
    }

    int pattern_num = read_pattern(fl_patterns, patternCtn);

    printf("read %d patterns\n", pattern_num);
    //printf("%d",pattern_num);
    for (int k = 0; k < pattern_num; ++k) {
        patternCtn[k].ctn = str_cmp(patternCtn[k].pattern, string);
        //printf("%s %d\n", patternCtn[k].pattern, patternCtn[k].ctn);
    }

    printf("cmp finish\n");

    sort_2(patternCtn, 0, pattern_num - 1);

    printf("sort finish\n");

    FILE *result = fopen(".\\result.txt", "w+");
    for (int p = 0; p < pattern_num; ++p) {
        //printf("%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
        fprintf(result, "%s %d\n", patternCtn[p].pattern, patternCtn[p].ctn);
    }

    fprintf(result, "%lldKB %lldK´Î\n", global_stats.mem/1024, global_stats.cmp_num/1000);

    endtime = clock();
    printf("cost time:%dms\n", endtime - begintime);

    return 0;
}

int str_cmp(const char *pattern, const char *string) {
    int result = 0;
    int pos = 0;
    while (string[pos] != '\0'){
        int i = pos;
        int j = 0;
        while (pattern[j] != '\0') {
            if ((string[i] - pattern[j]) == 0) {
                i++;
                j++;
                global_stats.cmp_num++;
            } else {
                global_stats.cmp_num++;
                break;
            };

            if (pattern[j] == '\0') {
                result++;
                break;
            }
        }
        pos++;
    }
    return result;
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
            while (left < right && mid < right && compare(patternCtn, mid, right) > 0) {
                right--;
            }
            if (left < right && mid < right) {
                swap_pattern(patternCtn, left++, right);
                mid = right;
            }
            while (left < right && left < mid && compare(patternCtn, left, mid) > 0) {
                left++;
            }
            if (left < right && left < mid) {
                swap_pattern(patternCtn, left, right--);
                mid = left;
            }
        }
        swap_pattern(patternCtn, left, mid);

        // µÝ¹éµ÷ÓÃ
        sort_2(patternCtn, l, mid-1); // ÅÅÐòmid×ó±ß
        sort_2(patternCtn, mid + 1, r); // ÅÅÐòmidÓÒ±ß
    }
}

int compare(struct Pattern_ctn *patternCtn, int i, int j) {
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

void *bupt_malloc(size_t size){
    if(size <= 0){
        return NULL;
    }
    global_stats.mem += size;
    return (malloc(size));
}

