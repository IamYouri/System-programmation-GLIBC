#include"mini_lib.h"
#include<unistd.h>
#include<errno.h>

#define BUF_SIZE 1024 // taille du buffer

char *buffer; // buffer
int ind=-1; // indice du buffer

/**
 * Cette fonction, mini_printf, affiche une chaîne de caractères sur la sortie standard en utilisant un buffer.
 * 
 * @param str La chaîne de caractères à afficher.
 * @return void.
 */
void mini_printf(char *str) {
    if(ind==-1){
		buffer = mini_calloc(1,BUF_SIZE+1);
		if(buffer==NULL){
			mini_perror("calloc dans printf");
		}
		ind=0;    
	}
    // Parcourir la chaîne
    for (char *ptr = str; *ptr != '\0'; ++ptr) {
        // Si le buffer est plein ou si le caractère actuel est un saut de ligne
        if (ind >= BUF_SIZE || *ptr == '\n') {
            // Afficher le contenu du buffer à l'écran
            if ((write(STDOUT_FILENO, buffer, ind+1)) == -1) {
                mini_perror("write dans printf");
            }

            // Vider le buffer
            ind = -1;
            for(int i = 0; i < BUF_SIZE + 1; i++) {
                buffer[i] = '\0';
            }
        }
        ind++;
        // Ajouter le caractère au buffer
        buffer[ind] = *ptr;
    }
}


void  mini_exit_string(){
    if ((write(STDOUT_FILENO, buffer, ind+1)) == -1) {
        mini_perror("write dans string");
    }
}


/**
 * Cette fonction, mini_scanf, lit une chaîne de caractères depuis l'entrée standard en utilisant un buffer.
 * 
 * @param buff Le buffer dans lequel stocker la chaîne de caractères lue.
 * @param size_buffer La taille du buffer.
 * @return Le nombre de caractères lus.
 
*/
int mini_scanf(char *buff,int size_buffer){
	int i=0;
    char tmp;
	while(i < size_buffer)
	{
        if (read(STDIN_FILENO,&tmp,1) < 0){
            mini_perror("read impossible");
            break;
        }
		buff[i] = tmp;
        i++;
        if (tmp == '\n') {
            break;
        }
	}
    buff[size_buffer]='\0';
	return i;
}


/**
 * Calcule la longueur d'une chaîne de caractères.
 *
 * @param s La chaîne de caractères dont on veut calculer la longueur.
 * @return La longueur de la chaîne de caractères, ou -1 si la chaîne est NULL.
 */
int mini_strlen(char *s){

    if (s == NULL) { // test de l'arg
        return -1;
    }

    int taille = 0;
    while(*s != '\0'){
        taille++;
        s++;
    }
    return taille;
}
/**
 * Copie une chaîne de caractères dans une autre.
 *
 * @param s1 La chaîne de caractères source.
 * @param s2 La chaîne de caractères destination.
 * @return Le nombre de caractères copiés, ou -1 si les arguments sont nuls.
 */
int mini_strcpy(char* s1, char* s2)
{
    if (s1 == NULL && s2 == NULL) { // tests des args
        return -1;
    }
    int cpt = 0;
    while (*s1 != '\0')
    {
        *s2 = *s1;
        cpt++;
        s2++;
        s1++;
    }
    *s2 = '\0';
    return cpt;
}

// Fonction en plus pour le mini_shell
int mini_strncpy(char* s, char* d, int n) {
    if (s == NULL || d == NULL || n < 0) {
        return -1; // Cas d'erreur
    }

    int cmpt = 0;
    while (*s != '\0' && cmpt < n) {
        *d = *s;
        cmpt++;
        s++;
        d++;
    }
    *d = '\0';

    return cmpt; // nb caractères copiés
}


/**
 * Compare deux chaînes de caractères.
 *
 * Cette fonction compare les chaînes de caractères s1 et s2 et renvoie un entier
 * indiquant leur ordre lexicographique.
 *
 * @param s1 La première chaîne de caractères à comparer.
 * @param s2 La deuxième chaîne de caractères à comparer.
 * @return Un entier négatif si s1 est inférieure à s2, un entier positif si s1 est
 *         supérieure à s2, et 0 si les deux chaînes sont égales.
 */
int mini_strcmp(char* s1, char* s2)
{
    if (s1 == NULL && s2 == NULL) { // tests des args
        return -1;
    }

    while (*s1 != '\0' && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
/**
 * Cette fonction, mini_perror, affiche un message d'erreur sur la sortie standard.
 * 
 * @param mess Le message d'erreur à afficher.
 * @return void.
 */
void mini_perror(char *mess) {
    mini_printf(mess); // message d'erreur
}