#include"mini_lib.h"
void *malloc_list = NULL;

/**
 * Trouve un bloc libre dans la liste des allocations.
 *
 * Cette fonction recherche un bloc dans la liste des allocations qui est à la fois libre et a une taille supérieure ou égale à la taille spécifiée.
 *
 * @param last Un pointeur vers le pointeur du dernier élément dans la liste des allocations.
 * @param size La taille du bloc à allouer.
 * @return Un pointeur vers le bloc trouvé, ou NULL s'il n'y a aucun bloc approprié.
 */
struct malloc_element *find_free_block(struct malloc_element **last, size_t size) {
  struct malloc_element *current = malloc_list;
  while (current && !(current->free == 0 && current->size >= size)) {
    *last = current;
    current = current->next_malloc;
  }
  return current;
}


/**
 * Demande de l'espace mémoire au système d'exploitation.
 * Cette fonction alloue un bloc de mémoire de la taille spécifiée en paramètre.
 * 
 * @param last Le dernier élément de la liste des blocs alloués.
 * @param size La taille du bloc de mémoire à allouer.
 * @return Un pointeur vers le bloc de mémoire alloué, ou NULL en cas d'échec.
 */
struct malloc_element *request_space(struct malloc_element* last, size_t size) {
  
  struct malloc_element *block;
  block = sbrk(0);
  if (block == (void * ) -1 ) {
    return NULL; // sbrk a échoué
  }

  void *request = sbrk(size + META_SIZE);
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL à la première utilisation.
    last->next_malloc = block;
  }
  // On met toute la mémoire \0
  for(int i=0;i<size;i++){
    ((char*)block)[i]='\0';
  }

  // on set nos flags
  block->zone_alloue = block+1;// +1 car on pointe vers la zone du block après les meta_size
  block->size = size;
  block->next_malloc = NULL; // dernier élèment ajouté
  block->free = 1; // Est utilisé

  return block;
}

/**
 * Alloue un bloc de mémoire pour un tableau d'éléments, chacun d'eux étant de taille size_element octets,
 * et initialise tous ses bits à zéro.
 *
 * @param size_element La taille de chaque élément en octets.
 * @param number_element Le nombre d'éléments à allouer.
 * @return Un pointeur vers le bloc de mémoire alloué, ou NULL si l'allocation échoue.
 */
void* mini_calloc (int size_element, int number_element){  
    size_t size = size_element * number_element;
    struct malloc_element *block;

    if (size <= 0) {
        return NULL;// la taille ne peut être négative
    }

    if (!malloc_list) { // Premier element de la liste
        block = request_space(NULL, size);
        if (!block) {
          return NULL;
        }
        malloc_list = block;
    }
    else { // sinon
        struct malloc_element *last = malloc_list;
        block = find_free_block(&last, size);
        if (!block) { // Il n'y a pas de block libre
            block = request_space(last, size);
            if (!block) {
                return NULL;
            }
        }
        else { // Block libre trouvé
          block->free = 1;   
        }
    }
    return(block+1); // pareil on retourne la zone apres les méta-données.(sizeof(struct malloc_element)) 
}

/**
 * Récupère le pointeur de bloc correspondant à l'adresse donnée.
 *
 * Cette fonction prend en paramètre un pointeur vers une adresse mémoire allouée
 * et retourne le pointeur de bloc correspondant à cette adresse.
 *
 * @param ptr Le pointeur vers l'adresse mémoire allouée.
 * @return Le pointeur de bloc correspondant à l'adresse donnée.
 */
struct malloc_element *get_block_ptr(void *ptr) {
  return (struct malloc_element*)ptr - 1;
}

/**
 * free un bloc de mémoire en setant le flag free à 0
 * 
 * @param size La taille du bloc de mémoire à allouer.
 * @return Un pointeur vers le bloc de mémoire alloué, ou NULL en cas d'échec.
*/
void mini_free(void *ptr) {
    // On vérifie le pointeur donné
    if (ptr == NULL) {
        return;
    }
    struct malloc_element* block_ptr = get_block_ptr(ptr);
    block_ptr->free = 0; 
}


//fonction exit pour terminer le programme.
void mini_exit() {
    mini_exit_string();
    mini_exit_flush();
    _exit(0);
}


