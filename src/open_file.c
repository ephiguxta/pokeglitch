#include <stdio.h>

FILE* open_file(char *save_path) {

    FILE *file = fopen(save_path, "r+b");

    if(!file) {
        fprintf(stderr, "Não pôde abrir o arquivo!\n");
        fprintf(stderr, "Caminho '%s' inexistente\n", \
        save_path);

        return NULL;
    }

    return file;
}
