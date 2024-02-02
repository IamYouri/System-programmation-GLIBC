#include "mini_lib.h"

//  prend en paramètre un fichier ; crée un fichier vide si il n’existe pas, ou le remet à zéro si il existe déjà
void mini_clean(char* file){
    if (!test_name_file(file)) {
        mini_perror("Nom de fichier invalide\n");
        return;
    }
    if (mini_fopen(file, 'r') == NULL) {
        // Le fichier n'existe pas, on le crée
        MYFILE* fp = mini_fopen(file, 'w');
        if (fp == NULL) {
            mini_perror("Erreur lors de la création du fichier\n");
            return;
        }
        mini_fclose(fp);
    } else {
        // Le fichier existe, on le remet à zéro
        MYFILE* fp = mini_fopen(file, 'w');
        if (fp == NULL) {
            mini_perror("Erreur lors de l'ouverture du fichier\n");
            return;
        }
        mini_fclose(fp);
    }
}

int main (int argc, char *argv[]) {
    if (argc == 2) {
        mini_clean(argv[1]);
    } else {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_clean <fichier>\n");
        mini_exit();
    }
    return 0;
}