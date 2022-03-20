#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define init_check 0x2598
#define final_check 0x3522

char checksum(char *save_path) {
  // calcula o cheksum do *.sav e retorna o valor
  FILE *file;
  char check = 0;

  file = fopen(save_path, "r+b");
  if(!file){
    fprintf(stderr, "Não pôde abrir o arquivo!\n");
    fprintf(stderr, "Caminho '%s' inexistente\n", \
        save_path);

    return 1;
  }

  // o algorítmo de verificação começa no endereço
  // 0x2598 até o 0x3522 e copia o resultado em
  // 0x3523
  fseek(file, init_check, SEEK_SET);
  for(int i = init_check; i <= final_check; i++)
    check -= fgetc(file);

  fclose(file);

  return check;
}
