#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "checksum.h"

int main(int argc, char *argv[]) {
  //o checksum da geração 1 é um valor de 8 bits
  char check;

  //salvando o caminho, para não ficar operando em
  //argv o tempo todo.
  char path_size = strlen(argv[1]);
  char save_path[32];

  //copiando argv[1] em save_path
  strncpy(save_path, argv[1], path_size);

  check = checksum(save_path);

  printf("%02hhx\n", check);

  return 0;
}
