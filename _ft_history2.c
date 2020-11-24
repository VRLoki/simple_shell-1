#include "hsh.h"



/**
 * _pull_hist - pull the hist from file
 *
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_pull_hist(param_t *param)
{
	int fd, nbr;
	char *path, *home, *buf, *line = NULL;

	home = _get_env_val("HOME", param->envlist);
	if (home == NULL)
		return (1);
	path = _str_concat(home, "/.simple_shell_history");
	fd = open(path, O_RDWR);
	if (fd <= 0)
		return (1);

	buf = malloc(sizeof(char) * 1024);
	if (buf == NULL)
		return (1);

	while ((nbr = read(fd, buf, 1024)) != 0)
	{
		if (nbr < 1024)
			buf[nbr] = '\n';
		if (line == NULL)
			line = _strdup(buf);
		else
			line = _str_concat(line, buf);
	}
	close(fd);
	_populate_hist(line, param);

	return (0);
}


/**
 * _populate_hist - push the list to linked list
 *
 * @line : line of the history file
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_populate_hist(char *line, param_t *param)
{
	char **list;
	char *push;
	int i;

	list = _strtow(line, "\n");
	i = 0;
	while (list[i])
	{
		push = _str_concat(list[i], "\n");
		_add_hist_line(push, param);
		i++;
	}

	return (0);
}






/**
 * _push_hist - push the hist to file
 *
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_push_hist(param_t *param)
{
	int fd, nbr, nblines = 0, k = 0;
	char *path, *home;
	histl_t *node;

	home = _get_env_val("HOME", param->envlist);
	if (home == NULL)
		return (1);
	path = _str_concat(home, "/.simple_shell_history");
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd <= 0)
		return (1);
	node = param->hist;
	while (node)
	{
		nblines++;
		node = node->next;
	}
	node = param->hist;
	while (node)
	{
		if (k > nblines - 4096)
		{
			nbr = write(fd, node->line, _strlen(node->line));
			if (nbr < _strlen(node->line))
			{
				close(fd);
				return (1);
			}
		}
		node = node->next;
		k++;
	}
	close(fd);
	return (0);
}
