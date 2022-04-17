#include <stdio.h>
#include <stdlib.h>

#define checksum_addr 0x3523

int apply_patch(char *save_path, unsigned char checksum) {
    FILE *file;
    
    file = fopen(save_path, "r+b");

    if(!file) {
        fprintf(stderr, "Não pôde abrir o arquivo!\n");
        fprintf(stderr, "Caminho '%s' inexistente\n", \
                save_path);

        return 1;
    }

    //vai até o endereço do checksum e insere o valor
    fseek(file, checksum_addr, SEEK_SET);

    fputc(checksum, file);

    fclose(file);

    return 0;
}
