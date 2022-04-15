#include <stdio.h>
#include <stdlib.h>

#define name_size 7
#define name_initial_addr 0x2598

int change_name(char *save_path, char name[7]) {
    FILE *file;

    file = fopen(save_path, "r+b");

    if(!file) {
        fprintf(stderr, "Não pôde abrir o arquivo!\n");
        fprintf(stderr, "Caminho '%s' inexistente\n", \
                save_path);

        return 1;
    }

    //o tamanho do nome tem o tamanho de 7 bytes
    char translated_name[name_size];

    //(a-z) e (A-Z)
    unsigned char lower[25], upper[25];

    for(unsigned char i = 0; i <= 25; i++) {
        upper[i] = (unsigned char) (0x80 + i);
        lower[i] = (unsigned char) (0xA0 + i);
    }

    //faz a conversão do caractere ASCII para o formato
    //usado no Pokémon Red.
    for(unsigned char j = 0; j <= name_size; j++){
        //0x41 == 'A' em ASCII
        if(name[j] >= 0x41 && name[j] <= 0x5A) {
            translated_name[j] = upper[j];

        //0x61 == 'a'
        } else if(name[j] >= 0x61 && name[j] <= 0x7A) {
            translated_name[j] = lower[j];
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

    return 0;
}
