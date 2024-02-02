#include "mini_lib.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 12

char* mini_strchr(const char* str, int character) {
    while (*str != '\0') {
        if (*str == (char)character) {
            return (char*)str;
        }
        str++;
    }

    return NULL;  // Caractère non trouvé
}


char* mini_strtok(char* str, const char* delimiters) {
    static char* saved_str = NULL;

    // Si l'appel se fait sur une nouvelle chaîne
    if (str != NULL) {
        saved_str = str;
    }

    // Si la chaîne sauvegardée est nulle, on a fini
    if (saved_str == NULL || *saved_str == '\0') {
        return NULL;
    }

    // Trouver le début du token (sauter les délimiteurs)
    while (*saved_str != '\0' && mini_strchr(delimiters, *saved_str) != NULL) {
        saved_str++;
    }

    // Si on est à la fin de la chaîne, on a fini
    if (*saved_str == '\0') {
        return NULL;
    }

    // Sauvegarder le début du token
    char* token_start = saved_str;

    // Trouver la fin du token (trouver le prochain délimiteur)
    while (*saved_str != '\0' && mini_strchr(delimiters, *saved_str) == NULL) {
        saved_str++;
    }

    // Si on a atteint un délimiteur, le remplacer par '\0' pour terminer le token
    if (*saved_str != '\0') {
        *saved_str = '\0';
        saved_str++;
    }

    return token_start;
}

void mini_help(char* function_name) {
    if(mini_strcmp(function_name, "") == 0 || mini_strcmp(function_name, " ") == 0) {
        mini_printf("-- AIDE POUR LES FONCTIONS DU MINI_SHELL --\n");
        
        mini_printf("Utilisation de 'mini_echo' : \n");
        mini_printf(">-->--> mini_echo chaine1 chaine2 ... chaineN \n"); 

        mini_printf("Utilisation de 'mini_touch' : \n");
        mini_printf(">-->--> mini_touch nom_fichier \n");

        mini_printf("Utilisation de 'mini_cat' : \n");
        mini_printf(">-->--> mini_cat nom_fichier \n");

        mini_printf("Utilisation de 'mini_tail' : \n");
        mini_printf(">-->--> mini_tail N_dernières_lignes nom_fichier \n");

        mini_printf("Utilisation de 'mini_head' : \n");
        mini_printf(">-->--> mini_head N_premières_lignes nom_fichier \n");

        mini_printf("Utilisation de 'mini_clean' : \n");
        mini_printf(">-->--> mini_clean nom_fichier \n");

        mini_printf("Utilisation de 'mini_grep' : \n");
        mini_printf(">-->--> mini_grep mot_cherché nom_fichier \n");

        mini_printf("Utilisation de 'mini_wc' : \n");
        mini_printf(">-->--> mini_wc nom_fichier \n");

        mini_printf("Pour QUITTER le mini_shell : exit \n");

        mini_printf("--> Pour obtenir de l'aide sur une fonction <-- \n");
        mini_printf("----> mini_help nom_fonction \n");
    }

    else if(mini_strcmp(function_name, "mini_echo") == 0) {
        mini_printf("Utilisation de 'mini_echo' : \n");
        mini_printf("----> mini_echo chaine1 chaine2 ... chaineN \n");
    }
    else if(mini_strcmp(function_name, "mini_touch") == 0) {
        mini_printf("Utilisation de 'mini_touch' : \n");
        mini_printf("----> mini_touch nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_cat") == 0) {
        mini_printf("Utilisation de 'mini_cat' : \n");
        mini_printf("----> mini_cat nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_tail") == 0) {
        mini_printf("Utilisation de 'mini_tail' : \n");
        mini_printf("----> mini_tail N_dernières_lignes nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_head") == 0) {
        mini_printf("Utilisation de 'mini_head' : \n");
        mini_printf("----> mini_head N_premières_lignes nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_clean") == 0) {
        mini_printf("Utilisation de 'mini_clean' : \n");
        mini_printf("----> mini_clean nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_grep") == 0) {
        mini_printf("Utilisation de 'mini_grep' : \n");
        mini_printf("----> mini_grep mot_cherché nom_fichier \n");
    }
    else if(mini_strcmp(function_name, "mini_wc") == 0) {
        mini_printf("Utilisation de 'mini_wc' : \n");
        mini_printf("----> mini_wc nom_fichier \n");
    }
}

// fait mal son taffe
void parse_command(char* input_command, char** command, char*** arguments) {
    char* token;
    int arg_count = 0;

    *command = (char*)mini_calloc(MAX_COMMAND_LENGTH, 1);
    *arguments = (char**)mini_calloc(MAX_ARGUMENTS, sizeof(char*));

    if (*command == NULL || *arguments == NULL) {
        mini_perror("Erreur d'allocation mémoire");
        mini_exit();
    }

    token = mini_strtok(input_command, " ");
    mini_strcpy(*command, token);

    token = mini_strtok(NULL, " ");
    while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
        (*arguments)[arg_count] = (char*)mini_calloc(mini_strlen(token) + 1, 1);
        if ((*arguments)[arg_count] == NULL) {
            mini_perror("Erreur d'allocation mémoire");
            mini_exit();
        }
        mini_strcpy((*arguments)[arg_count], token);

        token = mini_strtok(NULL, " ");
        arg_count++;
    }

    (*arguments)[arg_count] = NULL;
}

void concat_path(char *result, const char *path, const char *command) {
    while (*path != '\0') {
        *result = *path;
        ++result;
        ++path;
    }

    if (*(result - 1) != '/') {
        *result = '/';
        ++result;
    }

    while (*command != '\0') {
        *result = *command;
        ++result;
        ++command;
    }
    *result = '\0';
}

void mini_execvp(const char *command, char *const argv[]) {
    // Liste des chemins à vérifier (ajoutez les chemins nécessaires)
    const char *paths[] = {"/bin", "/usr/bin", "."};

    // Taille de la liste des chemins
    size_t num_paths = sizeof(paths) / sizeof(paths[0]);

    for (size_t i = 0; i < num_paths; ++i) {
        // Construit le chemin complet
        char full_path[1024];
        concat_path(full_path, paths[i], command);

        // Essaie d'exécuter la commande avec execve
        execve(full_path, argv, NULL);
    }

    // Si aucune exécution réussie, affiche une erreur
    mini_perror("mini_execvp");
    mini_exit();
}

void mini_shell() {
    char input_command[MAX_COMMAND_LENGTH];
    char *command;
    char **arguments;



    while (1) {
        mini_printf("mini_shell> \n");
        if (mini_scanf(input_command, sizeof(input_command)) == -1) {
            mini_perror("Erreur lors de la lecture de la commande");
            return;
        }

        size_t command_length = mini_strlen(input_command);
        if (command_length > 0 && input_command[command_length - 1] == '\n') {
            input_command[command_length - 1] = '\0';
        }

        parse_command(input_command, &command, &arguments);

        mini_printf(command);mini_printf("\n");

        if (mini_strcmp(command, "exit") == 0) {
            mini_printf("Arrêt du mini-shell.\n");
            break;
        }

        pid_t child_pid = fork();

        if (child_pid < 0) {
            mini_perror("Erreur lors de la création du processus fils");
        } else if (child_pid == 0) {
            // Code du processus fils

            // appeler la fonction getcwd pour récuperer le chemin actuel et le concatener avec le nom de l'executable qui est le même que  command
            char full_path[1024];
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                mini_perror("Erreur lors de la récupération du répertoire de travail");
                mini_exit();
            }
            concat_path(full_path, cwd, command);

            mini_printf(full_path);mini_printf("\n");

            char *exec_args[] = {full_path, command, *arguments, NULL};
            if (execvp(full_path, exec_args) == -1) {
                mini_perror("Erreur lors de l'exécution de la commande");
                mini_exit();
            }
        } else {
            // Code du processus père
            int status;
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status)) {
                char buffer[1024];
                mini_itoa(WEXITSTATUS(status), buffer, 10);
                mini_printf("Le processus fils s'est terminé avec le code de sortie "); mini_printf(buffer); mini_printf(".\n");
            } else {
                mini_printf("Le processus fils ne s'est pas terminé normalement.\n");
            }
        }

        mini_free(command);
        for (int i = 0; arguments[i] != NULL; i++) {
            mini_free(arguments[i]);
        }
        mini_free(arguments);
    }
}

int main(int argc, char** argv) {
    mini_shell();
    return 0;
}