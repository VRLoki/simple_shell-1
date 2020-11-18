#include "hsh.h"


/**
 * _add_nodealias -  adds a new node at the beginning of an alias list
 *
 * @head : current head of the list
 * @var : name of the variable
 *
 * Return: 0
 */

int _add_nodealias(aliasl_t **head, char *var)
{

	aliasl_t *new;

	new = malloc(sizeof(aliasl_t));
	if (new == NULL)
		return (1);

	new->var = _strdup(var);
	new->next = *head;
	*head = new;

	return (0);
}


/**
 * _is_nodeal -  check if var is already in the list
 *
 * @head : current head of the list
 * @var : name of the variable to search
 *
 * Return: 1 if in the list, else 0
 */

int _is_nodeal(aliasl_t *head, char *var)
{
	while (head)
	{
		if (_strcmp2(var, head->var) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}



/**
* _strcmp2 - compares two strings
*
* @s1 : first string
* @s2 : second string
*
* Return: 0 if same, else 1
*/

int _strcmp2(char *s1, char *s2)
{
	int i = 0;
	int lens1 = _strlen(s1);
	int lens2 = _strlen(s2);

	if (lens1 != lens2)
		return (1);

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}

	return (0);
}
