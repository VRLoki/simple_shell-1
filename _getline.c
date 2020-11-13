#include "hsh.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char *buf;
	static int initbuf = 0;
	int bufflen = NULL;
	char *nextline;
	char *tmp;
	int nextchar;
	int fd;

	if (initbuf == 0)
	{
		initbuf = 1;
		fd = fileno(stream);
		printf("fd %u", fd);
		buf = malloc(sizeof(char) * 1024);
		if (buf == NULL)
			return (-1);
		bufflen = read(fd, buf, 1024);
		printf("bufflen %i", bufflen);
/*		if (_strlen(buf) == 0)
		{
			return (-1);
		}
		buf[bufflen] = '\0';
*/	}

	getline(lineptr, n, stream);
/*	if (bufflen == 0)
		return (EOF);

	nextchar = _strfindn(buf, '\n');
	nextline = malloc((nextchar + 1) * sizeof(char));
	if (nextline == NULL)
	{
		free(buf);
		return (-1);
	}

	*n = nextchar;
	_strncpy(nextline, buf, nextchar);
	nextline[nextchar + 1] = '\0';
	*lineptr = nextline;

	if (bufflen == nextchar)
	{
		free(buf);
		bufflen = 0;
	}
	else
	{
		tmp = malloc((bufflen - nextchar) * sizeof(char));
		tmp = (buf + nextchar);
		free(buf);
		buf = tmp;
		bufflen = bufflen - nextchar;
	}
	return(nextchar);
*/


}


/**
 * *_strfindn - locates a character in a string and return position
 *
 * @s : string where to search
 * @c : character to find
 *
 * Return: position of next character c, sizeof s if not found
 *
 */

int _strfindn(char *s, char c)
{
	int i = 0;

	while (*(s + i))
	{
		if (*(s + i) == c)
			return (i);
		i++;
	}

	return (i);
}


/**
 * *_strncpy - copies a string
 *
 * @dest : destination
 * @src : string source to be copied
 * @n : number of bytes from source
 *
 * Return: string concatenated
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, lensrc;

	lensrc = _strlen(src);

	for (i = 0; i <= lensrc && i < n; i++)
	{
		*(dest + i) = *(src + i);
	}

	for (; i < n; i++)
	{
		*(dest + i) = '\0';
	}
	return (dest);
}
