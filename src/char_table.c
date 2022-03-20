#include <stdio.h>

int main(void) {

  //0x80 == 0x41 ('A')
  char j = 0x80;

  //0xA0 == 0x61 ('a')
  char k = 0xA0;

  //0x41 == 'A'
  //0x51 == 'Z'
  for(char i = 0x41; i <= 0x5A; i++) {
    //mostrando um byte de j, com um tamanho fixo 2
    printf("[%c - %02hhx]", i, j++);

    //o salto de 'A' para 'a' na tabela ASCII resulta
    //em 0x20 == 32 posições
    printf("[%c - %02hhx]\n", (i + 0x20), k++);
  }

  return 0;
}
