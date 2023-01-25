#include <stdio.h>
#include <string.h>

#include "open_file.h"

#define money_addr 0x25f3

int change_money(const char *save_path, char money[6]) {
  FILE *file = open_file(save_path);

  if (!file)
    return 1;

  printf("[%s]\n", money);
  fseek(file, money_addr, SEEK_SET);

  int total_mov = strnlen(money, 6);

  // putting money value in the correct order
  // 35  = 000035, not 350000
  // 123 = 000123, not 123000, etc...
  if ( (total_mov >= 1) && (total_mov <= 6)) {

    // pointing to last valid char index
    int i = (total_mov - 1);

    // pointing to last index
    int j = 5;

    // moving chars to the right
    for (; i >= 0; i--, j--)
      money[j] = money[i];

    // cleaning the old chars
    for(; j >= 0; j--)
      money[j] = 48; // 48 == '0'

    /* debugging purposes XD
    for(i = 0; i <= 5; i++)
      printf("[%c]", money[i]);
    puts("");
    */

  }

  unsigned char i, j;
  for (i = 0, j = 1; (i >= 0) && (i <= 5); i += 2, j += 2) {
    printf("i:[%d] (%d) - j:[%d] (%d)\n", i, (money[i] - '0'), j,
           (money[j] - '0'));

    unsigned byte_parts;

    short temp_money[3] = {[2] = '\0'};

    // slicing the variable of the money into two parts, three times
    // 2        1        0
    // ([5][4]) ([3][2]) ([1][0])
    //
    temp_money[1] = money[i] - '0';
    temp_money[0] = money[j] - '0';

    //  transforming the value to an "equivalent" hexadecimal value
    //  for example: [decimal 88] to [hexadecimal 88].
    //
    byte_parts = (0x0000000f & (temp_money[0] - '0'));
    byte_parts |= (0x000000f0 & ((temp_money[1] - '0') << 4));

    fputc(byte_parts, file);
  }

  fclose(file);

  return 0;
}
