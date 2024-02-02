#include "mini_lib.h"

void mini_tail(char * file, int n){
    if (!test_name_file(file)) {
        mini_perror("Nom de fichier invalide");
        return;
    }

    MYFILE* myfile = mini_fopen(file, 'r');
    if (myfile == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Utilise fseek pour se déplacer à la fin du fichier
    if (lseek(myfile->fd, 0, SEEK_END) == -1) {
        mini_perror("Erreur lors du déplacement à la fin du fichier");
        mini_fclose(myfile);
        return;
    }

    // Détermine la taille totale du fichier
    long int file_size = lseek(myfile->fd, 0, SEEK_CUR);
    if (file_size == -1) {
        mini_perror("Erreur lors de la détermination de la taille du fichier");
        mini_fclose(myfile);
        return;
    }

    // Parcourt le fichier à l'envers en comptant les nouvelles lignes
    int newline_count = 0;
    char buffer[BUF_SIZE_SYS];
    for (long int i = file_size - 1; i >= 0; i--) {
        if (lseek(myfile->fd, i, SEEK_SET) == -1) {
            mini_perror("Erreur lors du déplacement dans le fichier");
            mini_fclose(myfile);
            return;
        }

         if ((read(myfile->fd, buffer, 1)) == -1) {
            mini_perror("Erreur lors de la lecture du fichier");
            mini_fclose(myfile);
            return;
        }

        if (buffer[0] == '\n') {
            newline_count++;
            if (newline_count >= n + 1) {
                break;
            }
        }
    }
    // Affiche les lignes à partir de la fin du fichier
        while (1) {
            ssize_t read_size = read(myfile->fd, buffer, BUF_SIZE_SYS);

            if (read_size == -1) {
                mini_perror("Erreur lors de la lecture du fichier");
                mini_fclose(myfile);
                return;
            }

            if (read_size == 0) {
                write(1, buffer, read_size);
                // Fin du fichier
                break;
            }
            write(1, buffer, read_size);
        }
    mini_fclose(myfile);
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        mini_tail(argv[1], 10);
    } else if (argc == 4 && mini_strcmp(argv[1], "-n") == 0) {
        mini_tail(argv[3], mini_atoi(argv[2]));
    } else {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_tail [-n nb_lignes] <fichier>\n");
        mini_exit();
    }
    return 0;
}