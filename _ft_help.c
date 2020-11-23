#include "hsh.h"

/**
 * _ft_help - handle the help built_in
 *
 * @comm: command entered by the user
 * @param: global parameters of the shell.
 *
 * Return: 0 or if fail 1
 */

int	_ft_help(char **comm, param_t *param)
{

	if (comm[1] == NULL)
	{
		_help_all();
		return (0);
	}
	if (_strcmp(comm[1], "help") == 0)
		_help_help();
	else if (_strcmp(comm[1], "env") == 0)
		_help_env();
	else if (_strcmp(comm[1], "setenv") == 0)
		_help_setenv();
	else if (_strcmp(comm[1], "unsetenv") == 0)
		_help_unsetenv();
	else if (_strcmp(comm[1], "exit") == 0)
		_help_exit();
	else if (_strcmp(comm[1], "cd") == 0)
		_help_cd();
	else if (_strcmp(comm[1], "alias") == 0)
		_help_alias();
	else if (_strcmp(comm[1], "unalias") == 0)
		_help_unalias();
	else if (_strcmp(comm[1], "history") == 0)
		_help_history();
	else
	{
		_help_error(comm[1], param);
		return (1);
	}
	return (0);
}


/**
 * _help_help - help for builtin help
 *
 * Return: Void
 */

void	_help_help(void)
{
	_puts("help: help [PATTERN]\n\n");

	_puts("  Display information about builtin commands.\n\n");

	_puts("  Displays brief summaries of builtin commands. If\n");
	_puts("  PATTERN is specified, gives detailed help on all\n");
	_puts("  commands matching PATTERN, otherwise the list of help\n");
	_puts("  topics is printed.\n\n");

	_puts("  Arguments:\n");
	_puts("    PATTERN: Pattern specifiying a help topic\n\n");

	_puts("  Exit Status:\n");
	_puts("    Returns success unless PATTERN is not found or an\n");
	_puts("    invalid option is given.\n");
}


/**
 * _help_env - help for builtin env
 *
 * Return: Void
 */

void	_help_env(void)
{
	_puts("env: env  [-]\n\n");

	_puts("  Prints out the current environment\n\n");

	_puts("  Exit Status:\n");
	_puts("  Returns success unless an invalid option is given\n");
	_puts("  or an error occurs.\n");
}



/**
 * _help_setenv - help for builtin setenv
 *
 * Return: Void
 */

void	_help_setenv(void)
{
	_puts("setenv: setenv [VARIABLE] [VALUE]\n\n");

	_puts("  The setenv() built-in adds the variable name to the\n");
	_puts("  environment with the value value, if name does not\n");
	_puts("  already exist. If name does exist in the environment\n");
	_puts("  , then its value is changed to value if overwrite is\n");
	_puts("  nonzero; if overwrite is zero, then the value of name\n");
	_puts("  is not changed. This function makes copies of the\n");
	_puts("  strings pointed to by name and value.\n\n");

	_puts("  VARIABLE:\n");
	_puts("    VARIABLE: the name of the variable to be set\n");
	_puts("    VALUE: the value of the variable as either a single\n");
	_puts("           word or a quoted string\n\n");

	_puts("  Exit Status:\n");
	_puts("    The setenv builtin returns zero on success, or -1\n");
	_puts("    on error, with errno set to indicate the cause of\n");
	_puts("    the error.\n");
}



/**
 * _help_unsetenv - help for builtin unsetenv
 *
 * Return: Void
 */

void	_help_unsetenv(void)
{
	_puts("unsetenv: unsetenv [VARIABLE]\n\n");

	_puts("  The unsetenv() built-in deletes the variable name\n");
	_puts("  from the environment. If name does not exist in the\n");
	_puts("  environment, then the functionsucceeds, and the\n");
	_puts("  environment is unchanged.\n\n");

	_puts("  VARIABLE:\n");
	_puts("    VARIABLE: the name of the variable to be set]\n\n");

	_puts("  Exit Status:\n");
	_puts("    The unsetenv builtin returns 1 on success, or -1 on\n");
	_puts("    error, with errno set to indicate the cause of the\n");
	_puts("    error.\n");
}
