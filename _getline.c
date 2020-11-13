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

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
<<<<<<< HEAD
	static char *buf;
	static int initbuf = 0;
	int bufflen = NULL;
||||||| merged common ancestors
	static char *buf = NULL;
	static int initbuf = 0;
	int bufflen;
=======
	static char *buf;
	static int initbuf;
	static int bufflen;
>>>>>>> 900100368e7088f81a3bd430056addd7b701809c
	char *nextline;
	char *tmp;
	int nextchar;
	int fd;

<<<<<<< HEAD
	if (initbuf == 0)
||||||| merged common ancestors

	if (initbuf == 0)
=======
	//printf("bufflen = [%i]\n", bufflen);
	if (initbuf == 0 || bufflen == 0)
>>>>>>> 900100368e7088f81a3bd430056addd7b701809c
	{
		initbuf = 1;
		fd = fileno(stream);
<<<<<<< HEAD
		printf("fd %u", fd);
		buf = malloc(sizeof(char) * 1024);
		if (buf == NULL)
			return (-1);
||||||| merged common ancestors
=======
		buf = (char *)malloc(sizeof(char) * 1024);
>>>>>>> 900100368e7088f81a3bd430056addd7b701809c
		bufflen = read(fd, buf, 1024);
		printf("bufflen %i", bufflen);
/*		if (_strlen(buf) == 0)
		{
			return (-1);
		}
		buf[bufflen] = '\0';
<<<<<<< HEAD
*/	}

	getline(lineptr, n, stream);
/*	if (bufflen == 0)
||||||| merged common ancestors
	}
	if (bufflen == 0)
=======
	}
//	printf("buf = [%s]", buf);
	if (bufflen == 0)
>>>>>>> 900100368e7088f81a3bd430056addd7b701809c
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
	printf("nextline = [%s]", nextline);
	printf("lineptr = [%s]", *lineptr);
	*lineptr = _strdup(nextline);
	free(nextline);
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
<<<<<<< HEAD
	return(nextchar);
*/


||||||| merged common ancestors
	return(nextchar);



=======
	return (nextchar);
>>>>>>> 900100368e7088f81a3bd430056addd7b701809c
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
