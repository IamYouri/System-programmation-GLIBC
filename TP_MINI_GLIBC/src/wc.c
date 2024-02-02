#include "mini_lib.h"


// wc : prend en paramètre un nom de fichier, affiche le nombre de mots du fichier
void wc(char* file) {
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
    int word_count = 0;
    int newline_count = 0; 
    int char_count = 0;

    // Lire le fichier caractère par caractère
    while (1) {
        int read_char = mini_fgetc(fp);
        if (read_char == MINI_EOF) {
            // La fin du fichier est atteinte
            break;
        }
        if (read_char == -1) {
            mini_perror("Erreur lors de la lecture du fichier");
            mini_fclose(fp);
            return;
        }

        char_count++;

        if (read_char == '\n') {
            newline_count++;
        }

        if (read_char == ' ' || read_char == '\n' || read_char == '\t') {
            word_count++;
        }
    }

    mini_printf("Nombre de mots : "); mini_printf(mini_itoa(word_count, buffer, 10)); mini_printf("\n");
    mini_printf("Nombre de lignes : "); mini_printf(mini_itoa(newline_count, buffer, 10)); mini_printf("\n");
    mini_printf("Nombre de caractères : "); mini_printf(mini_itoa(char_count, buffer, 10)); mini_printf("\n");
    mini_printf("\n");
    mini_fclose(fp);
}

 
int main (int argc, char *argv[]) {
	if (argc == 2) {
		wc(argv[1]);
	} else {
		mini_perror("Nombre d'arguments incorrect");
		mini_printf("Usage: wc <fichier>\n");
		mini_exit();
	}
	return 0;
}