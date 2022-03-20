#include <stdio.h>

int main(void) {

  //0x80 == 0x41 ('A')
  char j = 0x80;

  //0x41 == 'A'
  //0x51 == 'Z'
  for(char i = 0x41; i <= 0x5A; i++) {
    //mostrando um byte de j, com um tamanho fixo 2
    printf("[%c - %02hhx]\n", i, j++);
  }

  return 0;
}
