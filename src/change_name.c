#include <stdio.h>
#include <stdlib.h>

#include "open_file.h"

#define name_size 7
#define name_initial_addr 0x2598

int change_name(char *save_path, char name[7]) {
    FILE *file;

    file = open_file(save_path);
    if(!file)
        return 1;

    //o tamanho do nome tem o tamanho de 7 bytes
    char translated_name[name_size];

    //faz a conversão do caractere ASCII para o formato
    //usado no Pokémon Red.
    for(unsigned char j = 0; j <= name_size; j++){
        //0x41 == 'A' em ASCII
        if(name[j] >= 0x41 && name[j] <= 0x5A) {
            //mín: 0x80
            //max: 0x99
            translated_name[j] = (0x80 + (name[j] - 0x41));

        //0x61 == 'a'
        } else if(name[j] >= 0x61 && name[j] <= 0x7A) {
            //mín: 0xa0
            //máx: 0xb9
            translated_name[j] = (0xA0 + (name[j] - 0x61));
            printf("[j - %x] - [old_letter: %x] - [new_letter: %02hhx]\n", \
                    j, name[j], translated_name[j]);
        }
    }

    //0x80 == 0x41 ('A')
    //char j = 0x80;
    //0xA0 == 0x61 ('a')
    //char k = 0xA0;
    /*
    //0x41 == 'A'
    //0x5A == 'Z'
    for(char i = 0x41; i <= 0x5A; i++) {
        //mostrando um byte de j, com um tamanho fixo 2
        printf("[%c - %02hhx]", i, j++);

        //o salto de 'A' para 'a' na tabela ASCII resulta
        //em 0x20 == 32 posições
        printf("[%c - %02hhx]\n", (i + 0x20), k++);
    }
    */

    fseek(file, name_initial_addr, SEEK_SET);

    for(unsigned char i = 0; i < 7; i++)
        fputc(translated_name[i], file);

    fclose(file);

    return 0;
}
