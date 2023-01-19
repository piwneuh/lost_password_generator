#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256

void generate_permutations(char** strings, int num_strings, int cur_index, char* cur_permutation, FILE* outfile) {
  if (cur_index == num_strings) {
    fprintf(outfile, "%s\n", cur_permutation);
    return;
  }
  
  //#pragma omp parallel for
  for (int i = 0; i < num_strings; i++) {
    strcat(cur_permutation, strings[i]);
    strcat(cur_permutation, " ");

    generate_permutations(strings, num_strings, cur_index + 1, cur_permutation, outfile);

    int cur_string_length = strlen(strings[i]);
    cur_permutation[strlen(cur_permutation) - cur_string_length - 1] = '\0';
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }

  FILE* infile = fopen(argv[1], "r");
  FILE* outfile = fopen(argv[2], "w");
  if (infile == NULL || outfile == NULL) {
    fprintf(stderr, "Error: could not open files\n");
    return 1;
  }

  //read from input
  char** strings = malloc(MAX_STRING_LENGTH * sizeof(char*));
  int num_strings = 0;
  char buffer[MAX_STRING_LENGTH];
  while (fscanf(infile, "%s", buffer) == 1) {
    strings[num_strings] = strdup(buffer);
    num_strings++;
  }

  //shuffle
  char cur_permutation[MAX_STRING_LENGTH] = "";
  generate_permutations(strings, num_strings, 0, cur_permutation, outfile);

  for (int i = 0; i < num_strings; i++) {
    free(strings[i]);
  }
  free(strings);
  fclose(infile);
  fclose(outfile);

  return 0;
}
