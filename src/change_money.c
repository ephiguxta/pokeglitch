#include <stdio.h>

#include "open_file.h"

#define money_addr 0x25f3

int change_money(char *save_path, char money[7]) {
    FILE *file = open_file(save_path);

    if(!file)
        return 1;

    fseek(file, money_addr, SEEK_SET);

    unsigned char i, j;
    for(i = 0, j = 1; (i >= 0) && (i <= 5); i += 2, j += 2) {
        printf("i:[%d] - j:[%d]\n", i, j);

        unsigned byte_parts;
        unsigned byte_sieve;

        short temp_money[3] = { [2] = '\0' }; 
        
        // slicing the money var in two parts, tree times
        // 2        1        0
        // ([5][4]) ([3][2]) ([1][0])
        //
        temp_money[1] = money[i] - '0';
        temp_money[0] = money[j] - '0';


        //  transforming the value to an "equivalent" hex value
        //  for example: [decimal 88] to [hexadecimal 88].
        //
        byte_parts  = (0x0000000f & (temp_money[0] - '0'));
        byte_parts |= (0x000000f0 & ((temp_money[1] - '0') << 4));

        byte_sieve = (unsigned char) byte_parts;

        fputc(byte_sieve, file);
    }

    fclose(file);

    return 0;
}
