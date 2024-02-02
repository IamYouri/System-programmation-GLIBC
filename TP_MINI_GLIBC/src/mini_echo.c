#include "mini_lib.h"

void mini_echo(char* chaine) {
    if (chaine == NULL) {
        mini_exit();
    }
    mini_printf(chaine);mini_printf("\n");
    mini_printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        mini_echo(argv[1]);
    } else {
        mini_perror("Nombre d'arguments incorrect\n");
        mini_printf("Usage: mini_echo <chaine>\n");
        mini_exit();
    }
    return 0;
}