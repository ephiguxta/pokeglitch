#include <stdio.h>
#include <stdlib.h>

#include "open_file.h"

#define pokedex_seen_addr 0x25b6

int pokedex_seen_owned(const char *save_path, unsigned char pokenum) {
  FILE *file = open_file(save_path);

  // it is 0-based
  pokenum--;

  if(!file)
    return 1;

  // get the offset bit of the pokémon in savegame
  int pokedex_addr;
  
  // 001 = Bulbasaur
  // ...
  // 151 = Mew
  if(pokenum <= 151){
    // where byte part this pokémon is located?
    // dividing by 8 we can view the byte index from him
    pokedex_addr = pokedex_seen_addr + (pokenum / 8);

    printf("pokedex_addr = %x\n", pokedex_addr);

  } else {
    return 1;
  }

  // moving file pointer to the offset byte that
  // the pokémon is localized
  fseek(file, pokedex_addr, SEEK_SET);

  unsigned char save_byte_part = fgetc(file);

  // enabling the right bit in this byte,
  // without change the old seen pokémons.
  save_byte_part |= (0x01 << (pokenum % 8)); 

  fseek(file, pokedex_addr, SEEK_SET);
  printf("save_byte_part = %x\n", save_byte_part);

  fputc(save_byte_part, file);

  fclose(file);

  return 0;
}
