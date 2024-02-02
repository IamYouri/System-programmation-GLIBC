#ifndef MINI_LIB_H
#define MINI_LIB_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MINI_EOF -1
#define META_SIZE sizeof(struct malloc_element)

#define BUF_SIZE_SYS 2048 // taille du buffer

#pragma GCC diagnostic ignored "-Wdeprecated-declarations" 

struct malloc_element {
  void * zone_alloue;
  size_t size;
  int free;// Le statut libre == 0 else 1
  struct malloc_element *next_malloc;
};
struct malloc_element *get_block_ptr(void *ptr);
struct malloc_element *request_space(struct malloc_element* last, size_t size);
struct malloc_element *find_free_block(struct malloc_element **last, size_t size);

void *mini_calloc(int size_element, int number_element);

char* int_to_char(int value, char* buffer, int base);


void mini_exit_string();
void mini_exit_flush();
void mini_exit();
void mini_free(void* ptr);
void mini_printf(char *msg);
int mini_scanf(char *buffer,int size_buffer);
int mini_strlen(char *s);
int mini_strcpy(char *s,char *d);
int mini_strcmp(char* s1,char* s2);
void mini_perror(char *message);


typedef struct MYFILE{
        int fd;
        void *buffer_read;
        void *buffer_write;
        int ind_read;
        int ind_write;
	struct MYFILE *next_file;
} MYFILE;


//fonction de gestion de fichier
MYFILE* mini_fopen(char* file, char mode);
int mini_fread(void* buffer,int size_element, int number_element, MYFILE* file);
int mini_fwrite(void* buffer,int size_element, int number_element, MYFILE* file);
int mini_fflush(MYFILE* file);
int mini_fclose(MYFILE* file);
int mini_fgetc(MYFILE *file);
int mini_fputc(MYFILE* file, char c);

//fonction utilitaire
char * mini_fgets(char *s, int size, MYFILE *file);
int test_name_file(char* chaine);
int mini_strncmp(const char *s1,const char *s2, size_t n);
char *mini_strstr(char *haystack, char *needle);
int mini_feof(MYFILE *file);
char* mini_itoa(int value, char* buffer, int base);
int mini_strncpy(char* s, char* d, int n);
int mini_atoi(const char *str);
void mini_execvp(const char *command, char *const argv[]);
void concat_path(char *result, const char *path, const char *command);

// fonction système
void mini_touch(char* file);
void mini_cp(char* src, char* dst);
void mini_echo(char* chaine);
void mini_cat(char* file);
void mini_head(char * file, int nb_lignes);
void mini_tail(char * file, int nb_lignes);
void mini_clean(char* file);
void mini_grep(char* regexp,char* file);
void wc(char* file);


#endif
