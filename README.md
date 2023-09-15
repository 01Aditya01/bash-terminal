# 2023201009_Assignment2

## Execution
run the following commands on shell
```
make
./a.out
```
### Description
following files are present, which are run together
- main.cpp - contains main function that tokenises the input with semi colon as delimiter
- pipeline.cpp - contains pipeline function which takes care of pipes in a given command
- redirection.cpp - redirection function handles the presence of I/O redirection
- detectCommand.cpp - checks which specific commands are present
- echo.cpp - implements echo command
- pwd.cpp - implements pwd command
- chdirectory.cpp - implements cd command using chdir system call
- ls.cpp - implements ls command
- bg.cpp - implements background process using execvo
- rest.cpp - implements commands not custom implemented, using execvp
- printCurrentDir.cpp - prints current directory path on shell
- pinfo.cpp - prints process information
- search.cpp - finds if a particular file/directory is present in current directory (recursive search)
- history.cpp - writes the command entered to .history.txt file. And reads from same file when 'history' command is typed.
- header.h - conatins all header files and function declarations
- makefile - to compl=ile all the files together