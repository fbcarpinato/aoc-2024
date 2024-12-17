#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main() {
  char line[MAX_LINE_LENGTH];

  FILE *file = fopen("./input.txt", "r");

  if (file == NULL) {
    perror("Error: could not open the file!");
    return EXIT_FAILURE;
  }

  int good = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *token = strtok(line, " ");

    int prev = 0;
    int increasing = -1;

    bool valid = true;

    while (token != NULL && valid) {
      int number = atoi(token);

      if (prev == 0) {
        prev = number;
        token = strtok(NULL, " ");
        continue;
      }

      if (increasing == -1) {
        increasing = (number > prev) ? 1 : 2;
      } else if ((increasing == 1 && number < prev) ||
                 (increasing == 2 && number > prev)) {
        valid = false;
        break;
      }

      if (prev && number) {
        int diff = abs(number - prev);

        if (diff < 1 || diff > 3) {
          valid = false;
          break;
        }
      }

      prev = number;
      token = strtok(NULL, " ");
    }

    if (valid) {
      good++;
    }
  }

  if (ferror(file)) {
    perror("Error reading file");
    fclose(file);
    return EXIT_FAILURE;
  }

  fclose(file);

  printf("Number of valid lines: %d\n", good);

  return EXIT_SUCCESS;
}
