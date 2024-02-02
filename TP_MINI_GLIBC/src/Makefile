# Makefile
CC = gcc
CFLAGS = -g -Wall 
LDFLAGS =
OBJ = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o main.o
OBJ3 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_cat.o
OBJ4 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_cp.o
OBJ5 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_touch.o
OBJ6 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_echo.o
OBJ7 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_grep.o
OBJ8 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_tail.o
OBJ9 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_clean.o
OBJ10 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o wc.o
OBJ11 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_head.o
OBJ12 = mini_memory.o mini_string.o mini_io.o mini_itoa.o mini_complement.o mini_shell.o


all: main mini_cat mini_cp mini_touch mini_echo mini_grep mini_tail mini_clean wc mini_head mini_shell

main: $(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o main

mini_cat: $(OBJ3)
		$(CC) $(OBJ3) $(LDFLAGS) -o mini_cat

mini_cp: $(OBJ4)
		$(CC) $(OBJ4) $(LDFLAGS) -o mini_cp

mini_touch: $(OBJ5)
		$(CC) $(OBJ5) $(LDFLAGS) -o mini_touch

mini_echo: $(OBJ6)
		$(CC) $(OBJ6) $(LDFLAGS) -o mini_echo

mini_grep: $(OBJ7)
		$(CC) $(OBJ7) $(LDFLAGS) -o mini_grep

mini_tail: $(OBJ8)
		$(CC) $(OBJ8) $(LDFLAGS) -o mini_tail

mini_clean: $(OBJ9)
		$(CC) $(OBJ9) $(LDFLAGS) -o mini_clean

wc: $(OBJ10)
		$(CC) $(OBJ10) $(LDFLAGS) -o wc

mini_head: $(OBJ11)
		$(CC) $(OBJ11) $(LDFLAGS) -o mini_head

mini_shell: $(OBJ12)
		$(CC) $(OBJ12) $(LDFLAGS) -o mini_shell

#mes fichiers objets
mini_memory.o: mini_memory.c mini_lib.h
mini_string.o: mini_string.c mini_lib.h 
mini_io.o: mini_io.c mini_lib.h
mini_itoa.o: mini_itoa.c mini_lib.h
mini_complement.o: mini_complement.c mini_lib.h

#mes fichiers mains
mini_cat.o:mini_cat.c mini_lib.h # /* Ce fichier utilise la fonction cat */
mini_cp.o:mini_cp.c mini_lib.h # /* Ce fichier utilise la fonction cp */
mini_touch.o:mini_touch.c mini_lib.h # /* Ce fichier utilise la fonction touch */
mini_echo.o:mini_echo.c mini_lib.h # /* Ce fichier utilise la fonction echo */
mini_grep.o:mini_grep.c mini_lib.h # /* Ce fichier utilise la fonction grep */
mini_tail.o:mini_tail.c mini_lib.h # /* Ce fichier utilise la fonction tail */
mini_clean.o:mini_clean.c mini_lib.h # /* Ce fichier utilise la fonction clean */
wc.o:wc.c mini_lib.h # /* Ce fichier utilise la fonction wc */
mini_head.o:mini_head.c mini_lib.h # /* Ce fichier utilise la fonction head */
mini_shell.o:mini_shell.c mini_lib.h # /* Ce fichier utilise la fonction shell */
main.o:main.c mini_lib.h # /* Ce fichier test tout.. */

clean :
		rm -f *.o