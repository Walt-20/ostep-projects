#include <stdio.h>

int main(int argc, char *argv[]) {
  // loop through multiple user input
  int i;
  for (i = 1; i < argc; i++) {
    // open the file with fopen()
    FILE *fp = fopen(argv[i], "r");
    // check for errors in reading file
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      return 1;
    }
    // fgets
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      printf("%s", buffer);
    }
    fclose(fp);
  }
  return 0;
}
