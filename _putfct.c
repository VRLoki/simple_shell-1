#include "hsh.h"


/**
 * _putchar - writes the character c to stdout
 *
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}




/**
 * _puts - writes a string in stdout
 *
 * @s: The string to print
 * Return: On length of characters written
 */
int _puts(char *s)
{
	int length = 0;

	while (*(s + length) != 0)
	{
		_putchar(*(s + length));
		length++;
	}
	return (length);
}



/**
 * _prompt - display promter
 *
 * @param: parameter variable
 */

void _prompt(param_t *param)
{
	if (param->mode == 0)
		_puts("$: ");
}





/**
 * _prompt2 - display prompter for extra line
 *
 * @param: parameter variable
 */

void _prompt2(param_t *param)
{
	if (param->mode == 0)
		_puts("> ");
}
