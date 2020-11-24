#include "hsh.h"

/**
 * _ft_history - handle the history built_in
 *
 * @comm: command entered by the user
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_ft_history(char **comm, param_t *param)
{
	if (comm[0])
		return (_print_hist(param));
	return (0);
}




/**
 * _add_hist_line - add a command to the history list
 *
 * @string: command to add
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_add_hist_line(char *string, param_t *param)
{
	histl_t *head, *newnode, *tmp;

	newnode = (histl_t *)malloc(sizeof(histl_t));
	if (newnode == NULL)
		return (1);

	newnode->line = _strdup(string);
	free(string);
	newnode->next = NULL;
	head = param->hist;
	if (head == NULL)
	{
		param->hist = newnode;
		return (0);
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newnode;
	return (0);
}



/**
 * _print_hist - prints the current history
 *
 * @param: global parameters variable
 *
 * Return: 0
 */

int	_print_hist(param_t *param)
{
	int i = 0;
	histl_t *node;

	node = param->hist;
	if (node == NULL)
		_puts("\n");

	while (node)
	{
		_puts(_convert_base(i, 10, 0));
		_puts("  ");
		_puts(node->line);
		node = node->next;
		i++;
	}

	return (0);
}


/**
 * _str_concat_hist - concatenates two strings without the \n
 *
 * @s1 : first string
 * @s2 : second string
 *
 * Return: concatenated string
 */
char *_str_concat_hist(char *s1, char *s2)
{
	char *s;
	int i;
	int strsize1, strsize2;

	strsize1 = _strlennull(s1);
	if (s1[strsize1 - 1] == '\n')
		s1[strsize1 - 1] = ' ';
	strsize2 = _strlennull(s2);

	s = malloc((strsize1 + strsize2 + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	for (i = 0; i < strsize1; i++)
		s[i] = s1[i];
	for (i = 0; i < strsize2; i++)
		s[i + strsize1] = s2[i];
	s[strsize1 + strsize2] = '\0';
	return (s);
}
