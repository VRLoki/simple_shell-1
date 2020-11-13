#include "hsh.h"

/**
 * _getline - get the next line of the input.
 *
 * @lineptr: the adress where stock the next line.
 * @n: number of character return.
 * @stream: the source.
 *
 * Return: the position of the next EOL or -1 if fail
 */

ssize_t _getline(char **lineptr, size_t *n)
{
	static char *buf;
	static int initbuf;
	static int bufflen;
	char *nextline;
	char *tmp;
	int nextchar;
	int fd;

	if (initbuf == 0 || bufflen == 0)
	{
		initbuf = 1;
		buf = (char *)malloc(sizeof(char) * 1024);
		bufflen = read(STDIN_FILENO, buf, 1024);
		if (bufflen == -1)
		{
			return (-1);
		}
		buf[bufflen] = '\0';
	}

	if (bufflen == 0)
		return (EOF);

	nextchar = _strfindn(buf, '\n');
	nextline = malloc((nextchar) * sizeof(char));
	if (nextline == NULL)
	{
		free(buf);
		return (-1);
	}
	*n = nextchar;
	_strncpy(nextline, buf, nextchar);
	nextline[nextchar] = '\0';
       	*lineptr = _strdup(nextline);
	free(nextline);
//	printf("lineptr %s", *lineptr);

	if (bufflen == nextchar)
	{
		free(buf);
		bufflen = 0;
	}
	else
	{
//		printf("bufflen %i - nextchar %i\n", bufflen, nextchar);
		//tmp = malloc((bufflen - nextchar) * sizeof(char));
		tmp = _strdup((buf + nextchar));
//		printf("Tmp is %s\n", tmp);
		free(buf);
		buf = malloc((bufflen - nextchar) * sizeof(char));
		buf = _strdup(tmp);
		bufflen = _strlen(buf);
//		printf("Now buf is %s and bufflen %i\n", buf, bufflen);
	}
	return (nextchar);
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
			return (i + 1);
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







/**
 * _getline - get the next line of the input.
 *
 * @lineptr: the adress where stock the next line.
 * @n: number of character return.
 * @stream: the source.
 *
 * Return: the position of the next EOL or -1 if fail
 */

ssize_t _getlinefile(char **lineptr, size_t *n, int fd)
{
	static char *buf;
	static int initbuf;
	static int bufflen;
	char *nextline;
	char *tmp;
	int nextchar;

	if (initbuf == 0 || bufflen == 0)
	{
		initbuf = 1;
		buf = (char *)malloc(sizeof(char) * 1024);
		bufflen = read(fd, buf, 1024);
		if (bufflen == -1)
		{
			return (-1);
		}
		buf[bufflen] = '\0';
	}

	if (bufflen == 0)
		return (EOF);

	nextchar = _strfindn(buf, '\n');
	nextline = malloc((nextchar) * sizeof(char));
	if (nextline == NULL)
	{
		free(buf);
		return (-1);
	}
	*n = nextchar;
	_strncpy(nextline, buf, nextchar);
	nextline[nextchar] = '\0';
       	*lineptr = _strdup(nextline);
	free(nextline);
//	printf("lineptr %s", *lineptr);

	if (bufflen == nextchar)
	{
		free(buf);
		bufflen = 0;
	}
	else
	{
//		printf("bufflen %i - nextchar %i\n", bufflen, nextchar);
		//tmp = malloc((bufflen - nextchar) * sizeof(char));
		tmp = _strdup((buf + nextchar));
//		printf("Tmp is %s\n", tmp);
		free(buf);
		buf = malloc((bufflen - nextchar) * sizeof(char));
		buf = _strdup(tmp);
		bufflen = _strlen(buf);
//		printf("Now buf is %s and bufflen %i\n", buf, bufflen);
	}
	return (nextchar);
}
