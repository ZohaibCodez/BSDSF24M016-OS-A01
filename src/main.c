#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");

    char buf[100];
    printf("mystrlen(\"Hello\") = %d (expected 5)\n", mystrlen("Hello"));
    printf("mystrlen(\"\") = %d (expected 0)\n", mystrlen(""));

    int n = mystrcpy(buf, "Hello");
    printf("mystrcpy -> \"%s\", copied %d chars (expected 5)\n", buf, n);

    n = mystrcat(buf, ", World");
    printf("mystrcat -> \"%s\", new length %d (expected 12)\n", buf, n);

    char small[10];
    n = mystrncpy(small, "Operating", 4);
    small[4] = '\0';   // src was longer than n, so we must terminate it ourselves
    printf("mystrncpy(n=4) -> \"%s\", copied %d chars (expected Oper, 4)\n", small, n);

    printf("\n--- Testing File Functions ---\n");

    // Create a small test file so the program works from any folder
    const char* fname = "test_input.txt";
    FILE* fp = fopen(fname, "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Operating systems are fun\n");
    fprintf(fp, "linking is magic\n");
    fprintf(fp, "systems programming in C\n");
    fclose(fp);

    fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    int lines, words, chars;
    if (wordCount(fp, &lines, &words, &chars) == 0) {
        printf("wordCount: lines=%d words=%d chars=%d (expected 3, 11, 68)\n",
               lines, words, chars);
    }

    rewind(fp);   // wordCount read to the end; go back to the start

    char** matches = NULL;
    int count = mygrep(fp, "systems", &matches);
    printf("mygrep(\"systems\"): %d match(es) (expected 2)\n", count);
    for (int i = 0; i < count; i++) {
        printf("  %s", matches[i]);   // line already contains '\n'
        free(matches[i]);
    }
    free(matches);

    fclose(fp);
    remove(fname);   // delete the test file
    return 0;
}
