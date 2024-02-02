#include "mini_lib.h"

#define RUNS 100000

int main() {
    
    //test du mini_calloc
   
   /*
   char * str = mini_calloc(10,1);
	char * str2 = mini_calloc(10,1);
	char * str3 = mini_calloc(10,1);


	mini_free(str);
	mini_free(str2);
	mini_free(str3);


	str = mini_calloc(10,1);
	str2 = mini_calloc(10,1);
	str3 = mini_calloc(10,1);
    */


    /*
    int *ptr = mini_calloc(sizeof(int),1);
    if (ptr == NULL) { 
        mini_printf("Failed to mini_calloc a single int\n");
        return 1;
    }

    *ptr = 1;
    *ptr = 100;

    mini_free(ptr);

    mini_printf("mini_calloc'd an int, assigned to it, and mini_free'd it\n");

    int *ptr2 = mini_calloc(sizeof(int),1);
    if (ptr2 == NULL) { 
        mini_printf("Failed to mini_calloc a single int\n");
        return 1;
    }

    *ptr2 = 2;
    *ptr2 = 200;

    mini_free(ptr2);
    mini_printf("mini_calloc'd an int, assigned to it, and mini_free'd it #2\n");

    mini_calloc(sizeof(int),1); // Screw up alignment.

    int *ptr3 = mini_calloc(sizeof(int),1);
    if (ptr3 == NULL) { 
        mini_printf("Failed to mini_calloc a single int\n");
        return 1;
    }

    *ptr3 = 3;
    *ptr3 = 300;

    mini_free(ptr3);
    mini_printf("mini_calloc'd an int, assigned to it, and mini_free'd it #3\n");
    */

   /*
        mini_calloc(sizeof(int),1);

        int i;
        int **arr = mini_calloc(sizeof(int *),RUNS);

        if (arr == NULL) {
           mini_printf("Memory failed to allocate!\n");
            return 1;
        }

        for (i = 0; i < RUNS; i++) {
            arr[i] = mini_calloc(sizeof(int),1);
            if (arr[i] == NULL) {
           mini_printf("Memory failed to allocate!\n");
            return 1;
            }
            
            *(arr[i]) = i+1;
        }

        for (i = 0; i < RUNS; i++) {
            if (*(arr[i]) != i+1) {
           mini_printf("Memory failed to contain correct data after many allocations!\n");
            return 2;
            }
        }

        for (i = 0; i < RUNS; i++) {
            mini_free(arr[i]);
        }
        
        mini_free(arr);
       mini_printf("Memory was allocated, used, and mini_freed!\n");	
   */

   // Exercice 17 : Test du mini_printf
    /*char *str_1 = "Hello World ! \n";
    mini_printf("1) test avec '\\n' : \n");
    mini_printf(str_1);
    
    char *str_2 = "Hello world 2 ?";
    mini_printf("2) SANS '\\n' : \n");
    mini_printf(str_2);*/
	

    // Exercice 20 : Test du mini_scanf

    /*int BUFFER_SIZE=6;
    char str[BUFFER_SIZE];
    mini_printf("Entrez qlq chose : \n");
    int result = mini_scanf(str, BUFFER_SIZE);
    char str_int[10]; mini_itoa(result, str_int, 10);
    if (result != -1) {
        mini_printf("Saisie : ");
        mini_printf(str); mini_printf("\n");
        mini_printf("Nb caracètre lu : "); mini_printf(str_int);
    } else {
        mini_printf("Erreur lors de la saisie.\n");
    }*/

    
    // Exo 21 :test mini_strlen et mini_strcpy et mini_strcmp

    
    // Test de strlen
   /* 
    char str1[] = "Hello, World!";
    mini_printf("Longueur de la chaine "); mini_printf(str1); mini_printf(" : "); mini_printf(mini_strlen(str1)); mini_printf("\n");

    // Test de strcmp
    char str2[] = "Hello, World!";
    int result = mini_strcmp(str1, str2);
    if (result < 0) {
        mini_printf("Les chaines "); mini_printf(str1); mini_printf(" et "); mini_printf(str2); mini_printf(" sont différentes. Resultat de strcmp : "); mini_printf(result); mini_printf("\n");
    } else if (result > 0) {
        // printf("Les chaînes \"%s\" et \"%s\" sont différentes. Résultat de strcmp : %d\n", str1, str2, result);
        mini_printf("Les chaines "); mini_printf(str1); mini_printf(" et "); mini_printf(str2); mini_printf(" sont différentes. Resultat de strcmp : "); mini_printf(result); mini_printf("\n");
    } else {
        mini_printf("Les chaines "); mini_printf(str1); mini_printf(" et "); mini_printf(str2); mini_printf(" sont identiques. Resultat de strcmp : "); mini_printf(result); mini_printf("\n"); 
    }

    // Test de strcpy
    char destination[20];
    char source[100] = "Copy me! and hope their is enough space";
    mini_strcpy(source, destination);
    mini_printf("Contenu de la destination après strcpy : "); mini_printf(destination); mini_printf("\n");
    */
    
    // Exo 23 : test mini_perror
    /* int fd = open("abcdefg.txt", O_RDONLY);
    if (fd == -1) {
        // appel à mini_perror
        mini_perror("open() exo 23 ");
    }
    mini_printf(" ----> errno == 2 \n"); */

    // Exo 24 : test mini_fopen et mini_fclose et mini_fflush et mini_fwrite et mini_fread
    /*char data_to_write[] = "Hello, World!";
    char buffer_read[50];

    // Test de mini_fopen en écriture
    MYFILE* file_write = mini_fopen("test_file.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.");
        return 1;
    }

    // Test de mini_fwrite
    int elements_written = mini_fwrite(data_to_write, sizeof(char), sizeof(data_to_write), file_write);
    if (elements_written == -1) {
        mini_perror("Erreur lors de l'écriture dans le fichier.");
        mini_fclose(file_write);
        return 1;
    }

    // Test de mini_fflush
    if (mini_fflush(file_write) == -1) {
        mini_perror("Erreur lors du flush du buffer d'écriture.");
        mini_fclose(file_write);
        return 1;
    }

    // Fermer le fichier en écriture
    mini_fclose(file_write);

    // Test de mini_fopen en lecture
    MYFILE* file_read = mini_fopen("test_file.txt", 'r');
    if (file_read == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en lecture.");
        return 1;
    }

    // Test de mini_fread
    int elements_read = mini_fread(buffer_read, sizeof(char), sizeof(buffer_read), file_read);
    if (elements_read == -1) {
        mini_perror("Erreur lors de la lecture du fichier.");
        mini_fclose(file_read);
        return 1;
    }

    // Afficher le contenu lu
    mini_printf("Contenu lu : "); mini_printf(buffer_read);

    // Fermer le fichier en lecture
    mini_fclose(file_read);*/
    
    // Exo 25 : test mini_fgetc et mini_fputc
    /*
    MYFILE* file_write = mini_fopen("test_file.txt", 'w');
    if (file_write == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en écriture.");
        return 1;
    }

    // Test de mini_fputc
    char character_to_write = 'A';
    if (mini_fputc(file_write, character_to_write) == -1) {
        mini_perror("Erreur lors de l'écriture d'un caractère avec mini_fputc.");
        mini_fclose(file_write);
        return 1;
    }

    // Fermer le fichier en écriture
    mini_fclose(file_write);

    // Test de mini_fopen en lecture
    MYFILE* file_read = mini_fopen("test_file.txt", 'r');
    if (file_read == NULL) {
        mini_perror("Erreur lors de l'ouverture du fichier en lecture.");
        return 1;
    }

    // Test de mini_fgetc
    int read_character = mini_fgetc(file_read);
    if (read_character == MINI_EOF) {
        mini_perror("Erreur lors de la lecture d'un caractère avec mini_fgetc.");
        mini_fclose(file_read);
        return 1;
    }

    // Afficher le caractère lu
    mini_printf((char)read_character);

    // Fermer le fichier en lecture
    mini_fclose(file_read);

    */

   // test mini_fgets

    /*MYFILE* fd = mini_fopen("mini_fread_test.txt", 'r');
    if (fd == NULL) {
        mini_perror("mini_fopen");
        return -1;
    }*/

    // Exercice 39 : Test du mini_touch
    // Test avec un fichier qui n'existe pas
    /*char* filename1 = "mini_touch_test.txt";
    mini_touch(filename1);

    // Test avec un fichier qui existe déjà
    char* filename2 = "mini_touch_test.txt";
    mini_touch(filename2);*/

   // test mini_cp
    /*char source[] = "mini_fread_test.txt";
    char destination[] = "mini_fwrite_test.txt";
    mini_cp(source, destination);*/

    // Test mini_echo :
    /*char message[] = "Hello, world ! \n";
    mini_echo(message);*/


    // Test de mini_cat :
    /*char* filename = "mini_fread_test.txt";
    mini_cat(filename);*/


    // Test de mini_head :
    /*char* filename = "mini_fread_test.txt";
    mini_head(filename, 0); // affiche rien
    mini_head(filename, 1); // affiche la 1er ligne
    mini_head(filename, 2); // affiche la 2e ligne
    mini_head(filename, 3); */

    // Test de mini_tail :
    /*char* filename = "mini_fread_test.txt";
    mini_tail(filename, 0); // affiche rien
    mini_tail(filename, 1); // affiche la 1er dernière ligne
    mini_tail(filename, 2); // affiche la 2e ligne */

    // Test de mini_clean :
    /*char* filename_new = "mini_clean_test_new.txt";
    char* filename_exist = "mini_clean_test_new.txt"; // un .txt avec des données dedans

    // Tester la fonction mini_clean
    mini_clean(filename_new); // va créer un fichier vide "test_mini_clean_new.txt"
    mini_clean(filename_exist); // va remettre à 0 le fichier "test_mini_clean_exist.txt" */

    // Test de mini_grep :
    // char* mot = "mini_shell";  // Mot à rechercher
    // char* filename = "test_grep.txt";  // Nom du fichier à traiter
    // mini_grep(mot, filename);

    // Test de mini_wc :
    /*char* filename = "test_grep.txt"; 
    mini_wc(filename);*/

    // Test du mini_shell 
    //mini_shell();
    
    mini_exit();
    return 0;
}
