#include"mini_lib.h"
#include <fcntl.h>
#include <unistd.h>


int IOBUFFER_SIZE = 2048;   // Taille du buffer de lecture/écriture
MYFILE *first_file = NULL; // Pointeur vers le premier fichier ouvert

/**
 * Fonction qui ouvre un fichier dans le mode spécifié.
 *
 * \param file Le nom du fichier à ouvrir.
 * \param mode Le mode d'ouverture du fichier ('r' pour lecture, 'w' pour écriture, 'b' pour lecture/écriture, 'a' pour ajout à la fin du fichier).
 * \return Un pointeur vers une structure MYFILE représentant le fichier ouvert, ou NULL en cas d'erreur.
 */
MYFILE* mini_fopen(char *file,char mode){

    MYFILE *current_file = mini_calloc(sizeof(MYFILE),1); // On alloue la mémoire pour la structure MYFILE
    if (current_file == NULL) {
        mini_perror("calloc");
        return NULL;
    }
	MYFILE *f=mini_calloc(sizeof(MYFILE),1); // On alloue la mémoire pour la structure MYFILE
    if (f == NULL) {
        mini_perror("calloc");
        return NULL;
    }

    // On ouvre le fichier en fonction du mode
	switch(mode) {
        case 'r': // Ouverture en lecture
            f->fd = open(file, O_RDONLY);
            break;
        case 'w': // Ouverture en écriture
            f->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            // f->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC );
            break;
        case 'b': // Ouverture en lecture/écriture
            f->fd = open(file, O_RDWR);
            break;
        case 'a': // Ouverture en ajout à la fin du fichier
            f->fd = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            // f->fd = open(file, O_WRONLY | O_APPEND | O_CREAT);
            break;
        default :
            // Affiche un message d'erreur si le mode n'est pas valide et libère la mémoire allouée
            mini_printf("Le mode n'est pas valide !");
            mini_free(f);
            return NULL;
    }
    // On vérifie si l'ouverture du fichier a réussi
    if (f->fd == -1) {
        mini_perror("open()");
        mini_free(f);
        return NULL;
    }
 
	f->ind_read=-1; // On initialise les index de lecture et d'écriture à -1
	f->ind_write=-1; // On initialise les index de lecture et d'écriture à -1
    f->buffer_read = NULL; // On initialise les buffers à NULL
    f->buffer_write = NULL; // On initialise les buffers à NULL
    f->next_file = NULL; // On initialise le pointeur vers le prochain fichier à NULL

	if(first_file == NULL){ // On est dans le premier fichier.
    	first_file = f;
    }
	else{ // + d'un fichier existant on parcourt jusqu'a la fin et on append
        current_file = first_file;
        while(current_file->next_file != NULL){
        	current_file = current_file->next_file;
        }
        current_file->next_file = f;
        }
	return f;
}

/**
 * Lit des données à partir d'un fichier dans un tampon.
 *
 * @param buffer Le tampon de destination pour les données lues.
 * @param size_element La taille de chaque élément à lire.
 * @param number_element Le nombre d'éléments à lire.
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le nombre d'éléments lus avec succès, ou -1 en cas d'erreur.
 */

int mini_fread(void* buffer,int size_element, int number_element, MYFILE* file)
{
	int buffer_size = size_element * number_element;
	int i = 0;
    int nb_lus;

	if(file->ind_read == -1){
		file->buffer_read = mini_calloc(IOBUFFER_SIZE,1); // On alloue la mémoire pour le buffer de lecture
		if (file->buffer_read == NULL){
			mini_perror("initialisation du buffer dans fread");
		}
		file->ind_read=0; // On initialise l'index de lecture à 0
	}

	while (i < buffer_size) { // On lit le fichier par blocs de IOBUFFER_SIZE octets
        
        if (file->ind_read == IOBUFFER_SIZE){
            file -> ind_read = 0;
        }

        if (file->ind_read == 0) {
            // On utilise read pour lire IOBUFFER_SIZE éléments dans le buffer de lecture
            nb_lus = read(file->fd, file->buffer_read, IOBUFFER_SIZE);
            if ( nb_lus == -1) { 
                // En cas d'erreur lors de la lecture, retourne -1
                return -1;
            }
            if (nb_lus == 0){
                return i;
            }
        }

        // Copie de l'élément du buffer de lecture vers le buffer de destination
        ((char*)buffer)[i] = ((char*)file->buffer_read)[file->ind_read];
        
        if ( ((char*)buffer)[i] == '\0') {
            return i;
        }

        // Incrémentation de l'index de lecture
        file->ind_read++;
        // Incrémentation de l'index dans le buffer de destination
        i++;
    }
	return i;
}

/**
 * Cette fonction écrit un bloc de données dans un fichier.
 *
 * @param buffer Le pointeur vers le bloc de données à écrire.
 * @param size_element La taille en octets de chaque élément du bloc.
 * @param number_element Le nombre d'éléments à écrire.
 * @param file Le pointeur vers la structure de fichier MYFILE.
 * @return Le nombre d'éléments écrits avec succès, ou -1 en cas d'erreur.
 */
int mini_fwrite(void* buffer,int size_element, int number_element, MYFILE* file)
{
	int buffer_size = size_element * number_element;
    int i = 0;
    if(file->ind_write==-1){
        if ((file->buffer_write = mini_calloc(IOBUFFER_SIZE,1)) < 0){
			mini_perror("write");
		}
    	file->ind_write=0;
    }

	while(i < buffer_size){
        if(file->ind_write == IOBUFFER_SIZE){
            if((write(file->fd,file->buffer_write,IOBUFFER_SIZE)) == -1){
                return -1;
			}
        	file->ind_write=0;
        }

		((char*)file->buffer_write)[file->ind_write] = ((char*)buffer)[i];
        file->ind_write++;
        i++;
    }

    return i;
}

/**
 * Cette fonction vide le tampon d'écriture du fichier spécifié et écrit les données non écrites dans le fichier.
 * 
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le nombre d'octets écrits dans le fichier en cas de succès, -1 en cas d'erreur lors de l'écriture, 0 si aucune donnée n'a été écrite.
 */
int mini_fflush(MYFILE* file) {
    if (file->ind_write > 0) {
        // Si des données non écrites sont présentes dans buffer_write
        lseek(file->fd, -1, SEEK_CUR);
        int bytes_written = write(file->fd, file->buffer_write, file->ind_write);
        
        if (bytes_written == -1) {
            return -1; // En cas d'erreur lors de l'écriture
        }
        file->ind_write = 0; // set l'indice d'écriture après l'écriture
        
        // on clear le buffer
        for(int i=0; i < IOBUFFER_SIZE; i++) {
            ((char*)file->buffer_write)[i] = '\0';
        }
        return bytes_written;
    }
    return 0;
}

/**
 * Ferme un fichier ouvert avec mini_fopen.
 * 
 * Cette fonction ferme le fichier spécifié par le pointeur `file`.
 * Elle effectue également un flush du tampon de sortie avant de fermer le fichier.
 * 
 * @param file Le pointeur vers la structure MYFILE représentant le fichier à fermer.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int mini_fclose(MYFILE *file){
    if(mini_fflush(file)==-1 && close(file->fd)==-1)  // On flush le fichier et on le ferme
        return-1;
    return 0;
}

/**
 * Lit un caractère à partir du fichier spécifié.
 *
 * @param file Le pointeur vers la structure MYFILE représentant le fichier.
 * @return Le caractère lu en tant qu'entier, ou -1 en cas d'erreur.
 */
int mini_fgetc(MYFILE *file) {
    // On lit un caractère
    // char *c = mini_calloc(sizeof(char), 1);
    // int nb_lus = mini_fread(c, sizeof(char), 1, file);
    // // j'ai passé + de 5 heures à corriger tout mon code à cause de cette fonction
    // // et j'ai du tout ré-analyser pour déduire les deux conditions suivantes. 
    // if (nb_lus == -1) { 
    //     mini_printf("Erreur lors de la lecture");
    //     return -1;
    // }
    // if (nb_lus == 0){
    //     mini_printf("Aucun caractère lus");//mais retourne qd même -1
    //     return -1;
    // }
    // int result = (int)(*c); 
    // return result;
    char c;

    if (mini_fread(&c, sizeof(char), 1, file) == 1) {
        return (int)c;
    } else {
        return MINI_EOF;
    }
}

/**
 * Cette fonction écrit un caractère dans un fichier.
 *
 * @param file Le pointeur vers le fichier.
 * @param c Le caractère à écrire.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int mini_fputc(MYFILE* file, char c){
    if(mini_fwrite((void *)&c,sizeof(char),1,file)==-1)
        return-1;
    return 0;
}

/**
 * Fonction pour vider les tampons de sortie avant de quitter.
 *
 * Cette fonction parcourt tous les fichiers ouverts et effectue un flush sur chacun d'eux.
 * Ensuite, elle ferme chaque fichier après le flush.
 * Enfin, elle libère la mémoire associée à chaque fichier.
 */
void mini_exit_flush(){
    // Flush tous les fichiers ouverts avant de quitter
    MYFILE *current = first_file;
    while (current != NULL) {
        if (mini_fflush(current) == -1) {
            mini_printf("Erreur lors du flush du fichier\n");
        }
        mini_fclose(current); // Fermer le fichier après le flush
        current = current->next_file;
    }

    // Libérer la mémoire associée aux fichiers
    current = first_file;
    while (current != NULL) {
        MYFILE *next = current->next_file;
        mini_free(current);
        current = next;
    }
}

char *mini_fgets(char *s, int size, MYFILE *file) {
    int i = 0;
    int c;

    while (i < size - 1 && (c = mini_fgetc(file)) != MINI_EOF) {
        s[i++] = (char)c;

        if (c == '\n') {
            break;
        }
    }
    s[i] = '\0';
    return s;
}

