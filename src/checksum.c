#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define init_check 0x2598
#define final_check 0x3522

int main(int argc, char *argv[]) {
  //Pega o caminho do arquivo que contém o
  //arquivo *.sav, calcula o checksum dele
  //e retorna o valor em formato 0xNN

  FILE *file;
  //o checksum da geração 1 é um valor de 8 bits
  char checksum = 0xff;

  //salvando o caminho, para não ficar operando em
  //argv o tempo todo.
  char path_size = strlen(argv[1]);
  char save_path[32];

  //copiando argv[1] em save_path
  strncpy(save_path, argv[1], path_size);

  file = fopen(save_path, "r+b");
  if(!file){
    fprintf(stderr, "Não pôde abrir o arquivo!\n");
    fprintf(stderr, "Caminho '%s' inexistente\n", \
        save_path);

    return 1;
  }

  //o algorítmo de verificação começa no endereço
  //0x2598 até o 0x3522 e copia o resultado em
  //0x3523
  fseek(file, init_check, SEEK_SET);
  for(int i = init_check; i <= final_check; i++)
    checksum -= fgetc(file);

  printf("checksum: 0x%02hhx\n", checksum);

  return 0;
}
