# C - Simple Shell

## Objectifs

The objectif was to code a Shell (sh) and add a few more features, in C.

Our Shell is name hsh and it's handle all the system call.

We reprogramme some of the builtin functions :

1. exit
	Exit the programme with the error code given.
	Example: exit [STATUS ERROR]
	- exit 14 /* Exit the programme with the error code 14. */

2. env
	Display all the environment variables.
	Example: env
	- env

3. setenv
	Set an environment variable with the value given. You can precise, if the variable already exit, overwrite it, or not.
	Example: setenv [VARIABLE] [VALUE] [OVERWRITE]
	- setenv NEWENV /home/vagrant/simple\_shell /* Create a new variable in the environment name NEWENV. /*
	- setenv NEWENV /home/vagrant/ 0 /* Create a new variable if it doesn't exist in the environment. */
	- setenv NEWENV /home/vagrant/ 1 /* Create a new variable named NEWENV if it doesn't exist in the environment, or setup the variable NEWENV is it exist with the value. */

4. unsetenv
	Delete an environment variable.
	Exemple: unsetenv [VARIABLE]
	- unsetenv NEWENV /* Delete the variable NEWENV in the environment. */

5. alias
	Create or set a new alias, if the alias already exist it will be overwrite.
	Exemple: alias [VARIABLE]='[VALUE]'
	- alias l='ls -la' /* Create a new alias named l with the value ls -la. */
	- alias l='ls' /* Set the variable l to ls. */

6. unalias
	Delete an alias.
	Exemple: unalias [VARIABLE]
	- unalias l /* The alias l is delete. */

7. cd
	Switch to the specified directory (default HOME).
	Exemple: cd [DIRECTORY]
	- cd /* Switch to HOME. */
	- cd - /* Brings you to the previous directory */
	- cd . /* Keeps you on the same directory */
	- cd /my\_dir/my\_sub\_dir /* Switch to my_sub_dir directory */

If you want more details on our hsh you can check the man: man ./man\_hsh


## Conditions of developpement

This Shell has been code from the 10/11/2020 to 25/11/2020 by 2 wonderful people.

Everything was done remotely.


## How to use it

Clone this repository.

You can compile with:
```
gcc -Wall -pedantic -Werror -Wextra \*.c -o hsh
```
or
```
gcc -Wall -pedantic -Werror -Wextra _exec_fct.c  _ft_unalias.c _putfct.c _strtow.c _ft_alias.c _listfct1.c _builtin.c _ft_cd.c _getline.c main.c _strfct1.c _dollar_parse.c _ft_env.c _get_parsestruc2.c _operators.c _strfct2.c _env_fct.c _ft_exit.c _get_parsestruc.c _parse_string.c _strtow2.c -o hsh
```

Execute: ./hsh


## Author

Matt Scetbun *a.k.a* [@matt969696](https://github.com/matt969696 "The best bro for coding a project <3").

Gautier Chuinard *a.k.a* [@gchuinard](https://github.com/gchuinard "Just me :D").
