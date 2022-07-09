#include <stdio.h>
#include <stdlib.h>

#include "open_file.h"

#define name_size 7
#define name_initial_addr 0x2598

int change_name(const char *save_path, char name[7]) {
  FILE *file;

  file = open_file(save_path);
  if (!file)
    return 1;

  //  the size of the name has 7 bytes
  char translated_name[name_size];

  //  it converts the ASCII character into the format used by Pokémon Red
  for (unsigned char j = 0; j <= name_size; j++) {
    //  0x41 == 'A' in ASCII
    if (name[j] >= 0x41 && name[j] <= 0x5A) {
      // mín: 0x80
      // max: 0x99
      translated_name[j] = (0x80 + (name[j] - 0x41));

      //  0x61 == 'a'
    } else if (name[j] >= 0x61 && name[j] <= 0x7A) {
      // mín: 0xa0
      // máx: 0xb9
      translated_name[j] = (0xA0 + (name[j] - 0x61));
      printf("[j - %x] - [old_letter: %x] - [new_letter: %02hhx]\n", j, name[j],
             translated_name[j]);
    }
  }

  // 0x80 == 0x41 ('A')
  // char j = 0x80;
  // 0xA0 == 0x61 ('a')
  // char k = 0xA0;
  /*
  //0x41 == 'A'
  //0x5A == 'Z'
  for(char i = 0x41; i <= 0x5A; i++) {
      //  it shows a j byte, as a fixed size of 2
      printf("[%c - %02hhx]", i, j++);

      //  the jump from 'A' to 'a' in the ASCII table result
      //  in 0x20 == 32 positions
      printf("[%c - %02hhx]\n", (i + 0x20), k++);
  }
  */

  fseek(file, name_initial_addr, SEEK_SET);

  for (unsigned char i = 0; i < 7; i++)
    fputc(translated_name[i], file);

  fclose(file);

  return 0;
}
