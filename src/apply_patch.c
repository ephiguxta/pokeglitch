#include <stdio.h>
#include <stdlib.h>

#include "open_file.h"

#define checksum_addr 0x3523

int apply_patch(const char *save_path, unsigned char checksum) {
    FILE *file;
    
    file = open_file(save_path);

    if(!file)
        return 1;

    //  it goes to the checksum address and inserts the value
    fseek(file, checksum_addr, SEEK_SET);

    fputc(checksum, file);

    fclose(file);

    return 0;
}
