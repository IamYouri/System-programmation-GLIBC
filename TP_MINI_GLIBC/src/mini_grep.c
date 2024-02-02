#include "mini_lib.h"

// mini_grep : prend en paramètre un mot et un nom de fichier, affiche toutes les lignes contenant ce mot
void mini_grep(char *regexp, char *file) {
    MYFILE *fp = mini_fopen(file, 'r');
    int i = 0;
    if (fp == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    char line[1024];  // Ajustez la taille selon vos besoins
    int line_number = 0;

    // Ajout d'une vérification de la fin du fichier pour éviter la boucle infinie
    while (1) {
    line_number++;
    // Lire une ligne
    int read_char = mini_fgetc(fp);

    if (read_char == MINI_EOF) {
        // La fin du fichier est atteinte
        mini_printf("Fin du fichier atteinte.\n");
        break;
    }

    // Vérifier si l'expression régulière est présente dans la ligne
    if (read_char == -1) {
        mini_perror("Erreur lors de la lecture de la ligne\n");
        mini_printf("Erreur lors de la lecture de la ligne.\n");
        break;
    }

    line[i] = (char)read_char;

    if (line[i] == '\n') {
        line[i + 1] = '\0';  // Terminer la chaîne avec '\0'
        // mini_printf("Ligne lue :"); mini_printf(line);mini_printf("\n");

        // Vérifier si l'expression régulière est présente dans la ligne
        char *found = mini_strstr(line, regexp);
        if (found != NULL) {
        mini_printf(file); mini_printf("  Ligne lue : "); mini_printf(line);
        }
        i = 0;  // Réinitialiser l'indice pour la ligne suivante
    } else {
        i++;
    }
}
    mini_fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_grep <mot> <fichier>\n");
        mini_exit();
    }

    mini_grep(argv[1], argv[2]);
    return 0;
}