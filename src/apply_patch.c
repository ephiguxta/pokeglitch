#include <stdio.h>
#include <stdlib.h>

#include "open_file.h"

#define checksum_addr 0x3523

int apply_patch(char *save_path, unsigned char checksum) {
    FILE *file;
    
    file = open_file(save_path);

    if(!file)
        return 1;

    //vai até o endereço do checksum e insere o valor
    fseek(file, checksum_addr, SEEK_SET);

    fputc(checksum, file);

    fclose(file);

    return 0;
}
