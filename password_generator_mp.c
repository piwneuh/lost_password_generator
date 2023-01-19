#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <omp.h>
#include <time.h>

#define MAX_LEN 100
#define MAX_SPECIAL_CHARS 3

void permute(char *str, int start, int end, FILE *output) {
    int i;
    char c;

    #pragma omp parallel for private(i, c)
    for (i = start; i <= end; i++) {
        c = str[start];
        str[start] = str[i];
        str[i] = c;

        permute(str, start+1, end, output);

        c = str[start];
        str[start] = str[i];
        str[i] = c;
    }
}

void add_special_chars(char *str, int len, FILE *output) {
    int i, j, k;
    char special_chars[] = "!@#$";
    char new_str[MAX_LEN+MAX_SPECIAL_CHARS+1];

    #pragma omp parallel for private(j, k)
    for (i = 0; i < len; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < len; k++) {
                new_str[k] = (k == i) ? special_chars[j] : str[k];
            }
            new_str[len] = '\0';
            fprintf(output, "%s\n", new_str);
        }
    }
}

void check_capitalization(char *str, int len, int index, int *check, FILE *output) {
    int i;
    char new_str[MAX_LEN+1];
    if (index == len) {

        #pragma omp parallel for private(i)
        for (i = 0; i < len; i++) {
            new_str[i] = (check[i]) ? toupper(str[i]) : str[i];
        }
        new_str[len] = '\0';
        fprintf(output, "%s\n", new_str);
        add_special_chars(new_str, len, output);
        return;
    }
    check[index] = 1;
    check_capitalization(str, len, index + 1, check, output);
    check[index] = 0;
    check_capitalization(str, len, index + 1, check, output);
}

int main() {
    char str[MAX_LEN+1];
    int len;
    int check[MAX_LEN];
    FILE *input, *output;

    double start_time, end_time;
    start_time = omp_get_wtime();

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    while (fscanf(input, "%s", str) != EOF) {
        len = strlen(str);
        permute(str, 0, len-1, output);
        check_capitalization(str, len, 0, check, output);
    }
    fclose(input);
    fclose(output);

    end_time = omp_get_wtime();
    printf("Vreme izvrsavanja: %f s\n", end_time-start_time);
    return 0;
}