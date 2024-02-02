#include "mini_lib.h"


void mini_cp(char* src, char* dst) {
    // encore une fonction qui a relevé pleins de bugs dans mon programme ~6h de debug dans tout mon code :/

    // Vérifier la validité du nom du fichier de destination
    if (!test_name_file(dst)) {
        mini_printf("Nom de fichier destination invalide.\n");
        return;
    }

    // Ouvrir le fichier source en mode lecture
    MYFILE* src_file = mini_fopen(src, 'r');
    if (src_file == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    // Ouvrir le fichier de destination en mode écriture
    MYFILE* dst_file = mini_fopen(dst, 'w');
    if (dst_file == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier destination");
        mini_fclose(src_file); // Fermer le fichier source avant de sortir
        return;
    }
    
    int c;
    while ((c = mini_fgetc(src_file)) != MINI_EOF) {
        mini_fputc(dst_file, c);
    }

    mini_fflush(dst_file);

    // Fermer les deux fichiers
    mini_fclose(src_file);
    mini_fclose(dst_file);

}

int main(int argc, char *argv[]) {
    if (argc >= 3  ) {
        mini_cp(argv[1],argv[2]);
    } else {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_cp source destination \n");
        mini_exit();
    }
    return 0;
}