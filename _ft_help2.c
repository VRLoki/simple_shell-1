#include "hsh.h"


/**
 * _help_exit - help for builtin exit
 *
 * Return: Void
 */

void	_help_exit(void)
{
	_puts("exit: exit [n]\n\n");

	_puts("  Exit the shell.\n\n");

	_puts("  Exits the shell with a status of N. If N is omitted,\n");
	_puts("  the exit status is that of the last command executed\n");
}


/**
 * _help_cd - help for builtin cd
 *
 * Return: Void
 */

void	_help_cd(void)
{
	_puts("cd: cd [dir]\n\n");

	_puts("  Change the shell working directory. \n\n");

	_puts("  Change the current directory to DIR.  The default\n");
	_puts("  DIR is the value of the HOME shell variable.\n\n");

	_puts("  Exit Status:\n");
	_puts("  Returns 0 if the directory is changed; non-zero otherwise.\n");
}



/**
 * _help_alias - help for builtin alias
 *
 * Return: Void
 */

void	_help_alias(void)
{
	_puts("alias: alias [name[=value] ... ]\n\n");

	_puts("  Define or display aliases.\n\n");

	_puts("  Without arguments, `alias' prints the list of aliases\n");
	_puts("  in the reusable form `alias NAME=VALUE' on standard\n");
	_puts("  output. Otherwise, an alias is defined for each NAME\n");
	_puts("  whose VALUE is given. A trailing space in VALUE\n");
	_puts("  causes the next word to be checked for alias\n");
	_puts("  substitution when the alias is expanded.\n\n");

	_puts("  Exit Status:\n");
	_puts("    alias returns true unless a NAME is supplied for\n");
	_puts("    which no alias has been defined.\n");
}



/**
 * _help_unalias - help for builtin unalias
 *
 * Return: Void
 */

void	_help_unalias(void)
{
	_puts("unalias: unalias name [name ...]\n\n");

	_puts("  Remove each NAME from the list of defined aliases.\n\n");

	_puts("  Return success unless a NAME is not an existing alias.\n");
}



/**
 * _help_history - help for builtin history
 *
 * Return: Void
 */

void	_help_history(void)
{
	_puts("history: history\n\n");

	_puts("  Display the history list with line numbers.\n\n");

	_puts("  Exit Status:\n");
	_puts("    Returns success unless an invalid option is given\n");
	_puts("    or an error occurs.\n");
}
