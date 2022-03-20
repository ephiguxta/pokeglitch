#include <stdio.h>
#include <stdlib.h>

#define init_check 0x2598
#define final_check 0x3522

int main(int argc, char *argv[]) {
  FILE *file;
  //o checksum da geração 1 é um valor de 8 bits
  char checksum = 255;

  file = fopen("../data/pokemon_red.sav", "r+b");
  if(!file){
    fprintf(stderr, "Não pôde abrir o arquivo!");
    return 1;
  }

  fseek(file, init_check, SEEK_SET);
  for(int i = init_check; i <= final_check; i++)
    checksum -= fgetc(file);

  printf("checksum: 0x%x\n", checksum);

  return 0;
}
