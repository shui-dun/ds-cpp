#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *base;
	int len;
}String;

String *str_init();

void str_print(String *string);

String *str_create(char *s);

int str_insert(String *string, int pos, String *insert);

int str_compare(String *str1, String *str2);

void str_destroy(String **str);

String *str_concat(String *str1, String *str2);

String *str_sub(String *str, int pos, int len);

int str_set(String *str, int pos, char ch);

int str_find(String *str1, String *str2, int start);

int str_find_nwords(String * str1, String * str2);

int str_kmp(String *str1, String *str2);

void str_replace(String *str, String *origin, String *des);

int str_rep_fir(String *str, String *origin, String *des,int start);