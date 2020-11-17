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




/**
 * struct error_mess - use to display proper error message
 *
 * @nbr_error: error number from execve
 * @n_err_sh: error number to return
 * @m_error: text message
 *
 * Description: store the error message
 */
typedef struct  error_mess
{
	int     nbr_error;
	int     n_err_sh;
	char    *m_error;
}       error_mess_t;



/**
 * struct aliasl - linked list on the alias variables
 *
 * @var: variable
 * @value: variable value
 * @next: next node
 *
 * Description: store the alias
 */
typedef struct aliasl
{
	char *var;
	char *value;
	struct aliasl *next;
} aliasl_t;



/**
 * struct envl - linked list on the ENV variables
 *
 * @var: variable
 * @value: variable value
 * @next: next node
 *
 * Description: store the environment
 */
typedef struct envl
{
	char *var;
	char *value;
	struct envl *next;
} envl_t;



/**
 * struct histl - linked list on the history
 *
 * @line: history line
 * @next: next node
 *
 * Description: store the history
 */
typedef struct histl
{
	char *line;
	struct histl *next;
} histl_t;



/**
 * struct paraml - central structure containing all information
 * and parameters needed to execute Shell
 *
 * @bashname: name of the bash for error message display
 * @count: number of lines of command
 * @pid: pid of the current shell process
 * @lastval: last return value from executed commands
 * @envlist: head of linked list on the environment variables
 * @alias: head of linked list on the alias variable
 * @hist: head of linked list on the history
 * @fdnb : file descriptor to read from (NOT USED)
 * @mode : 0 for Interactive, 1 for Noninter, 2 for FileMode
 * @parsed : parsed string to work from (NOT USED)
 *
 * Description: store the environment
 */


typedef struct paraml
{
	char *bashname;
	int count;
	char *pid;
	int lastval;
	envl_t *envlist;
	aliasl_t *alias;
	histl_t *hist;
	int fdnb;
	int mode;
	char **parsed;
} param_t;





extern char	**environ;

/* _builtin.c */
int	_isbuiltin(char *comm);
int	_get_builtin_fct(char **comm, param_t *param);

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
int _launchShell(param_t *param);
void _siginthandler(int signum);

/* _parse_string.c */
char	**_parse_string(char *string, int *nbw);
void	_free_grid(char **grid, int height);
char **_parse_string2(char *string, int *nbw);

/* _exec_fct.c */
int	_exec_fct(char **parsed, param_t *param);
char	*_getfullpath(char *name, char *mypath);
int	_error_fct(int errnb, char *command, param_t *param);
int	_error_open(int errnb, char *command, param_t *param);

/* _getline.c */
int	_strfindn(char *s, char c);
char	*_strncpy(char *dest, char *src, int n);
ssize_t	_getlinefile(char **lineptr, size_t *n, int fd);

/* _ft_exit.c */
int		_ft_exit(char *s, param_t *param);
bool		_check_zero(char *s);
unsigned char	_atoi_exit(char *s);
int     _error_exit(char *command, param_t *param);

/* _env_fct.c */
param_t	*_initParam(char **av, char **env);
envl_t	*_getEnvList(char **env);
char	**_getEnvChar(envl_t *head);

/* _strtow.c */
int _isdelim(char c, const char *del);
int _nbword(const char *s, const char *del);
char *_mydup(const char *str, int size);
char **_strtow(const char *str, const char *del);

/* _strtow2.c */
int _nbword2(const char *s, const char *del);
char **_strtow2(const char *str, const char *del);


#endif
