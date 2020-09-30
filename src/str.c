#include "str.h"
#include <string.h>
#include <ctype.h>

String* str_init() {
    String* string = (String*)malloc(sizeof(String));
    string->base = (char*)malloc(sizeof(char));
    string->len = 0;
    return string;
}

void str_print(String* string) {
    if (!string) return;
    for (int i = 0; i < string->len; i++)
        putchar(string->base[i]);
    putchar('\n');
}

String* str_create(char* s) {
    String* string = (String*)malloc(sizeof(String));
    string->len = 0;
    while (s[string->len])
        string->len++;
    string->base = (char*)malloc(string->len * sizeof(char));
    for (int i = 0; i < string->len; i++)
        string->base[i] = s[i];
    return string;
}

int str_insert(String* string, int pos, String* insert) {
    if (pos < 0 || pos > string->len)
        return 0;
    if (!string || !insert)
        return -2;
    string->base = realloc(string->base, (string->len + insert->len) * sizeof(char));
    if (!string->base)
        return -1;
    for (int i = string->len - 1; i >= pos; i--)
        string->base[i + insert->len] = string->base[i];
    for (int i = 0; i < insert->len; i++)
        string->base[i + pos] = insert->base[i];
    string->len += insert->len;
    return 1;
}

int str_compare(String* str1, String* str2) {
    for (int i = 0; i < str1->len && i < str2->len; i++)
        if (str1->base[i] != str2->base[i])
            return str1->base[i] - str2->base[i];
    return str1->len - str2->len;
}

void str_destroy(String** str) {
    free((*str)->base);
    free((*str));
    *str = NULL;
}

String* str_concat(String* str1, String* str2) {
    if (!str1 || !str2)
        return NULL;
    String* str = (String*)malloc(sizeof(String));
    str->len = str1->len + str2->len;
    str->base = (char*)malloc(str->len * sizeof(char));
    for (int i = 0; i < str1->len; i++)
        str->base[i] = str1->base[i];
    for (int i = 0; i < str2->len; i++)
        str->base[i + str1->len] = str2->base[i];
    return str;
}

String* str_sub(String* str, int pos, int len) {
    if (pos < 0 || pos >= str->len || pos + len - 1 >= str->len)
        return NULL;
    String* sub = (String*)malloc(sizeof(String));
    if (!sub) return NULL;
    sub->len = len;
    sub->base = (char*)malloc(len * sizeof(char));
    for (int i = 0; i < len; i++)
        sub->base[i] = str->base[i + pos];
    return sub;
}

int str_set(String* str, int pos, char ch) {
    if (pos < 0 || pos >= str->len)
        return 0;
    str->base[pos] = ch;
    return 1;
}

int str_find(String* str1, String* str2, int start) {
    for (int pos1 = start; pos1 <= str1->len - str2->len; pos1++) {
        int flag = 1;
        for (int pos2 = 0; pos2 < str2->len; pos2++) {
            if (str1->base[pos1 + pos2] != str2->base[pos2]) {
                flag = 0;
                break;
            }
        }
        if (flag)
            return 1;
    }
    return -1;
}

int str_find_nwords(String* str1, String* str2) {
    int n = 0;
    for (int pos1 = 0; pos1 <= str1->len - str2->len; pos1++) {
        int flag = 1;
        for (int pos2 = 0; pos2 < str2->len; pos2++) {
            if (str1->base[pos1 + pos2] != str2->base[pos2]) {
                flag = 0;
                break;
            }
        }
        if (flag &&
            (pos1 == 0 || !isalpha(str1->base[pos1 - 1])) &&
            (pos1 + str2->len == str1->len || !isalpha(str1->base[pos1 + str2->len])))
            n++;
    }
    return n;
}

static void kmp_next(String* str, int* next) {
    next[0] = -1;
    int k = -1, j = 0;
    while (j < str->len - 1) {
        if (k == -1 || str->base[j] == str->base[k]) {
            ++j, ++k;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

int str_kmp(String* str1, String* str2) {
    int i = 0, j = 0;
    int* next = (int*)malloc(sizeof(int) * str2->len);
    kmp_next(str2, next);
    while (i < str1->len && j < str2->len) {
        if (j == -1 || str1->base[i] == str2->base[j])
            i++, j++;
        else
            j = next[j];
    }
    free(next);
    if (j == str2->len)
        return i - j;
    else
        return -1;
}

void str_replace(String* str, String* origin, String* des) {
    int pos = -des->len;
    while ((pos = str_rep_fir(str, origin, des, pos + des->len)) != -1);
}

int str_rep_fir(String* str, String* ori, String* des, int start) {
    int pos = str_find(str, ori, start);
    if (pos == -1) return -1;
    if (ori->len == des->len)
        memcpy(str->base + pos, des->base, des->len);
    else if (ori->len > des->len) {
        memcpy(str->base + pos, des->base, des->len);
        memmove(str->base + pos + des->len, str->base + pos + ori->len, str->len - pos - ori->len);
        str->base = (char*)realloc(str->base, (str->len + des->len - ori->len) * sizeof(char));
    } else {
        str->base = (char*)realloc(str->base, (str->len + des->len - ori->len) * sizeof(char));
        memmove(str->base + pos + des->len, str->base + pos + ori->len, str->len - pos - ori->len);
        memcpy(str->base + pos, des->base, des->len);
    }
    str->len += des->len - ori->len;
    return pos;
}
