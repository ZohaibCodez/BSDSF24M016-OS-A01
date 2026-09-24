#include <stdio.h>
#include "../include/myfilefunctions.h"
#include "../include/mystrfunctions.h"
#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // strstr
#include <ctype.h>    // isspace

// Helper: free a list of strings. 'static' means only this file can see it.
static void free_list(char** list, int count) {
    for (int i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL || lines == NULL || words == NULL || chars == NULL) return -1;

    *lines = 0;
    *words = 0;
    *chars = 0;

    int c;            // int, not char, because EOF is -1
    int in_word = 0;  // are we currently inside a word?

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') {
            (*lines)++;
        }
        if (isspace(c)) {
            in_word = 0;                 // a space ends the current word
        } else if (in_word == 0) {
            in_word = 1;                 // first letter of a new word
            (*words)++;
        }
    }
    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL || matches == NULL) return -1;

    char line[1024];
    char** list = NULL;
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, search_str) != NULL) {
            // grow the array by one slot
            char** tmp = realloc(list, (count + 1) * sizeof(char*));
            if (tmp == NULL) {
                free_list(list, count);
                return -1;
            }
            list = tmp;

            // make our own copy of the line (line[] gets overwritten next loop)
            list[count] = malloc(mystrlen(line) + 1);   // +1 for '\0'
            if (list[count] == NULL) {
                free_list(list, count);
                return -1;
            }
            mystrcpy(list[count], line);
            count++;
        }
    }

    *matches = list;   // hand the array back to the caller
    return count;
}
