#include "mini_lib.h"

void mini_touch(char* file) {
    if (!test_name_file(file)) {
        mini_perror("Nom de fichier invalide\n");
        mini_exit();
    }

    MYFILE *fp = mini_fopen(file, 'r');
    if (fp != NULL) {
        // Le fichier existe déjà
        mini_printf("Le fichier existe déjà.\n");
        mini_fclose(fp);
    } else {
        // Créer un nouveau fichier
        fp = mini_fopen(file, 'w');
        if (fp == NULL) {
            mini_perror("Erreur lors de la création du fichier\n");
            mini_fclose(fp);
            mini_exit();
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        mini_touch(argv[1]);
    } else {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_touch <nom_fichier>\n");
        mini_exit();
    }
    return 0;
}