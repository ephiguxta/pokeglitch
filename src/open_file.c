#include <stdio.h>

FILE *open_file(const char *save_path) {

  FILE *file = fopen(save_path, "r+b");

  if (!file) {
    fprintf(stderr, "Unable to open the file!\n");
    fprintf(stderr, "Path '%s' doesn't exist\n", save_path);

    return NULL;
  }

  return file;
}
