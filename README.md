# SIMPLE SHELL

Simple shell is a fundamental command line user interface where you wich provides all basic built-in commands.
This project is our own simple shell with basic commands that was created based on SH. Simple shell handle environment

-----
## INSTALLATION

1. Git clone this repository

```bash
 $ git clone https://github.com/gchuinard/simple_shell.git
```

2. Compile all files to get executable file

```bash
 $ gcc *.c -o hsh
```

3. Execute

```bash
 $ ./hsh
```

-----
## USAGE

### INTERACTIVE MODE

Interactive mode allows you to enter as many commands as you want.
Also allows you to exit in two ways, press ```CTRL + D``` or
exit built-in command. ```$ exit ```

To run simple shell just execute the command below

```bash
 $ ./hsh
```

It will display this screen that means you are inside our shell
```bash
 $:
```
```bash
 $ ./hsh
 $: echo display something
 display something
 $:
```

### NON INTERACTIVE MODE

Non interactive mode allows you to run a simple command.

```bash
 $ echo "the command you want to run" | ./hsh
```

```bash
 $ echo "pwd" | ./hsh
*Display your current directory*
```

### FILE MODE

File mode allows you to enter many commands as you want with the intermediary of a file. You can write in your file one command by line. The shell will execute them one by one. You don't need to exit at the end.

Create a file "my\_file"

Write the commands you want to execute
```
ls
pwd
echo Hello
```

Execute the file mode:
```bash
 $ ./hsh my_file
*Display files and directories in your current directory*
*Display the path to your current directory*
Hello
 $
```

-----
## BUILT-IN COMMANDS

More information about each command use help. ```$: help built-in_command```


```bash
 $: ./hsh
 $: help exit
 exit: exit [n]

 Exit the shell.

    Exits the shell with a status of N.  If N is omitted, the exit status
    is that of the last command executed.
 $:
```

| Command | Description  |
| ------- | --- |
| exit | Exit simple shell|
| help | Display help of built-in command |
| env | Display environment variables |
| cd | Change directory |
| setenv | Set environment variable value or create a new one |
| unsetenv | Delete environment variable |
| alias | Set an alias or create a new one |
| unalias | Delete an alias |
| history | Display previous commands |

-----
## EXIT STATUS

There are different posible exit status, this deppende on the success of the last command.

0: Success exit.<br>
2: Error execute command. <br>
126: Permission denied.<br>
127: not found.


-----
## EXAMPLES

### INTERACTIVE MODE

```bash
 $ ./hsh
 $: ls -l
 -rwxrw-r-- 1 vagrant vagrant    25 Nov 20 00:00 hsh
 $:
```
```bash
 $ ./custom_name_shell
 $: echo 123
 123
 $:
```

```bash
 $ ./hsh
 $: cd /tmp
 $: pwd
 /tmp
 $:
```

### NON INTERACTIVE MODE

```bash
 $ echo "/bin/ls -l" | ./hsh
 -rwxrw-r-- 1 vagrant vagrant    25 Nov 20 00:00 hsh
 $
 ```
```bash
 $ echo "pwd" | ./hsh
 /root/simple_shell
 $
```

```bash
 $ echo "exit 7" | ./hsh
 $ echo $?
 7
 $
```

### FILE MODE

Create a file "my\_file"

Write the commands you want to execute
```
ls
pwd
echo Hello
```

Execute the file mode:
```bash
 $ cat my_file | ./hsh
*Display files and directories in your current directory*
*Display the path to your current directory*
Hello
 $
```
-----
## FILES


Help_files: Directory containing help files of built-in commands.

## Authors

Matt Scetbun *a.k.a* [@matt969696](https://github.com/matt969696 "The best bro for coding a project <3"). <br>
Gautier Chuinard *a.k.a* [@gchuinard](https://github.com/gchuinard "Just me :D").
