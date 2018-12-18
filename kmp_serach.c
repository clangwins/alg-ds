//
// Created by 吴裕欣 on 2018/12/17.
//

#include "kmp_serach.h"

void get_next(char *p, int **next) {
    size_t len = strlen(p);
    *next = calloc(len, sizeof(char));
    (*next)[0] = -1;
    size_t i = 0;
    int j = -1;
    while (i < len) {
        if (j == -1 || *(p+i) == *(p+j)) {
            i++;
            j++;
            (*next)[i] = j;
        } else {
            j = (*next)[j];
        }
    }
}

int kmp(char *s, char *p) {
    int i = 0;
    int j = 0;
    int sLen = (int)strlen(s);
    int pLen = (int)strlen(p);
    int *next = NULL;
    get_next(p, &next);
    while (i < sLen && j < pLen)
    {
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]
            //next[j]即为j所对应的next值
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}


int main() {
    char *p = "ababc";
    int d = kmp("abcdfasdfasdfasdfasdfasdfasdfasdfafasdfababc", "ababc");
    printf("%d\n", d);

    return 0;
}