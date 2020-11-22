# C - Simple Shell

## Objectifs

The objectif was to code a Shell (sh) and add a few more features, in C.

Our Shell is name hsh and it's handle all the system call.

We reprogramme some of the builtin functions :
1. exit
2. env
3. setenv
4. unsetenv
5. alias
6. unalias
7. cd

If you want more details on our hsh you can check the man: man ./man\_hsh


## Conditions of developpemtent

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
