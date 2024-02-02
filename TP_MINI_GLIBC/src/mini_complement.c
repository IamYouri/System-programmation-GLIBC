#include "mini_lib.h"


int test_name_file(char* chaine) {
    int bool = 1;
    if (chaine == NULL) {
        bool =  0; // Chaîne nulle
    }

    int len = mini_strlen(chaine);
    if (len == 0 || len > 255) {
        bool =  0; // Longueur invalide
    }

    if (chaine[0] == '.') {
        bool =  0; // Commence par un point
    }

    for (int i = 0; i < len; i++) {
        if (!((chaine[i] >= 'a' && chaine[i] <= 'z') ||
              (chaine[i] >= 'A' && chaine[i] <= 'Z') ||
              (chaine[i] >= '0' && chaine[i] <= '9') ||
              chaine[i] == '_' || chaine[i] == '.')) {
            bool =  0; // Caractère non autorisé
        }
    }
    if (bool == 0) {
        mini_printf("Nom de fichier invalide : caractères autorisés : [Aa-Zz] [0-9] ['_' et '.']\n");
        return 0; // Nom de fichier invalide
    }
    return bool; // Nom de fichier valide
}

// Fonction qui imite partiellement le comportement de la fonction strstr
char *mini_strstr(char *haystack,char *needle) {
    size_t needle_len = mini_strlen(needle);

    while (*haystack) {
        if (mini_strncmp(haystack, needle, needle_len) == 0) {
            return (char *)haystack;
        }
        haystack++;
    }

    return NULL;
}

// Fonction qui imite partiellement le comportement de la fonction strncmp
int mini_strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }

        if (s1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

int mini_feof(MYFILE *file) {
    return file->ind_read < 0;
}

