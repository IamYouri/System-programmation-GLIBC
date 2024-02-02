#include "mini_lib.h"

void mini_head(char* file, int n) {
    if (!test_name_file(file)) {
        mini_perror("Nom de fichier invalide");
        return;
    }

    MYFILE* fp = mini_fopen(file, 'r');
    if (fp == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char buffer[BUF_SIZE_SYS];
    int line_count = 0;

    // Lire le fichier ligne par ligne
    while (line_count < n && mini_fgets(buffer, BUF_SIZE_SYS, fp) != NULL) {
        mini_printf(buffer);
        line_count++;
    }
    mini_printf("\n");
    mini_fclose(fp);
}


int main (int argc, char *argv[]) {
    if (argc == 2) {
        mini_head(argv[1], 10);
    } else if (argc == 4 && mini_strcmp(argv[1], "-n") == 0) {
        mini_head(argv[3], mini_atoi(argv[2]));
    } else {
        mini_perror("Nombre d'arguments incorrect");
        mini_printf("Usage: mini_head [-n nb_lignes] <fichier>\n");
        mini_exit();
    }
    return 0;
}