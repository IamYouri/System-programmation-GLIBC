#include "mini_lib.h"

char* mini_itoa(int value, char* buffer, int base) {
    // Vérifier la base
    if (base < 2 || base > 36) {
        *buffer = '\0';
        return buffer;
    }

    char* ptr = buffer;
    int quotient = value;

    // Gérer le cas où la valeur est zéro
    if (value == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return buffer;
    }

    // Gérer le cas où la valeur est négative
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        quotient = -value;
    }

    // Convertir la valeur en chaîne de caractères
    while (quotient != 0) {
        int remainder = quotient % base;
        *ptr++ = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
        quotient /= base;
    }

    // Inverser la chaîne de caractères
    *ptr-- = '\0';
    while (buffer < ptr) {
        char temp = *buffer;
        *buffer++ = *ptr;
        *ptr-- = temp;
    }

    return buffer;
}


int mini_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Gestion du signe
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Conversion des chiffres
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            // En cas de caractère non valide, retourne 0
            return 0;
        }
        i++;
    }

    return result * sign;
}
