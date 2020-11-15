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
#include <err.h>
#include <stdbool.h>

#define SEP " \n\a\t\v\r"
#define ATOI(c) ((c == '\t' || c == '\n' || c == '\r' || c == '\v' || c  == '\f' || c == ' ')  && c != '\0')





extern char	**environ;

/* _builtin.c */
int	_isbuiltin(char *comm);
void	(*_get_builtin_fct(int built_nbr))(char *);

/* _putfct.c */
int	_putchar(char c);
int	_puts(char *s);

/* _strfct1.c */
int	_strlen(char *s);
char	*_strcat(char *dest, char *src);
int	_strcmp(char *s1, char *s2);
char	*_strcpy(char *dest, char *src);
char	*_strdup(char *str);

/* _strfct2.c */
int	_strlennull(char *s);
char	*_str_concat(char *s1, char *s2);
char	*_getenv(char *name, char **env);
char	*_strrev(char *str);
char	*_convert_base(unsigned long int nbr, int base, int cap);

/* main.c */
void	_interactive(int ac, char **av, char **env);
void	_noninteractive(int ac, char **av, char **env);
void	_filemode(int ac, char **av, char **env);



/* _parse_string.c */
char	**_parse_string(char *string, int *nbw);
void	_free_grid(char **grid, int height);

/* _exec_fct.c */
int	_exec_func(char **parsed, char **en, int count);
char	*_getfullpath(char *name, char *mypath);
int	_error_func(int errnb, char*command, int count, char **env);
int	_error_open(int errnb, char *command, int count, char **env);

/* _getline.c */
ssize_t	_getline(char **lineptr, size_t *n);
int	_strfindn(char *s, char c);
char	*_strncpy(char *dest, char *src, int n);
ssize_t	_getlinefile (char **lineptr, size_t *n, int fd);

/* _ft_exit.c */
void		_ft_exit(char *status);
bool		_check_zero(char *s);
unsigned char	_atoi_exit(char *s);

/* _ft_env.c */
void	_ft_env(char *status);

#endif
