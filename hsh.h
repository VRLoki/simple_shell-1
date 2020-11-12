#ifndef HSH_H
#define HSH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define SEP " \n\a\t\v\r"


extern char **environ;

/* _putfct.c */
int _putchar(char c);
int _puts(char *s);

/* _strfct1.c */
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);

/* _example.c */
int _exec_func(char *comm, char **commarg, char **en);


/* _parse_string.c */
char **_parse_string(char *string, int *nbw);
void _free_grid(char **grid, int height);

/*_exec_fct.c */
int _exec_func(char *comm, char **commarg, char **en);


#endif
