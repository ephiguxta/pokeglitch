#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "open_file.h"

#define init_check 0x2598
// TODO:
// why do you need to include the Tileset Type address?
#define final_check 0x3522

char checksum(const char *save_path) {
  //  calculate the cheksum of *.sav and return the value
  FILE *file;
  unsigned char check = 255;

  file = open_file(save_path);
  if (!file)
    return 1;

  //  the verification algorithm starts at the adress
  //  0x2598 to the 0x3522 and copy the result in
  //  0x3523
  fseek(file, init_check, SEEK_SET);

  for (int i = init_check; i <= final_check; i++)
    check -= fgetc(file);

  fclose(file);

  return (unsigned char)check;
}
