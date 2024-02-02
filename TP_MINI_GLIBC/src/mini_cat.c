#include "mini_lib.h"

void mini_cat(char* file) {

    if (test_name_file(file) == 0) {
        mini_perror("Nom de fichier invalide");
        return;
    }
    
    // Ouvrir le fichier en mode lecture
    MYFILE* fp = mini_fopen(file, 'r');
    if (fp == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Afficher le contenu du fichier
    char buffer[BUF_SIZE_SYS];
    int bytes_read;
    while ((bytes_read = mini_fread(buffer, 1, BUF_SIZE_SYS, fp)) > 0) {
        if (bytes_read == -1) {
            mini_perror("Erreur lors de la lecture du fichier");
            mini_fclose(fp);
            return;
        }
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            mini_perror("Erreur lors de l'écriture sur la sortie standard");
            mini_fclose(fp);
            return;
        }
    }

    // Fermer le fichier
    mini_fclose(fp);
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        mini_cat(argv[1]);
    } else {
        mini_perror("Nombre d'arguments incorrect");
        mini_printf("Usage: mini_cat <fichier>\n");
        mini_exit();
    }
    return 0;
}