_This project has been created as part of the 42 curriculum by flink, mprokope._

# Minishell

A lightweight, custom UNIX command interpreter written in C that mimics core behaviors of Bash.

## Description

The goal of this project is to create a functional shell from scratch, gaining a deep understanding of processes, system calls, file descriptors, and command parsing in C.

### Key Features

- **Prompt & History:** Displays an interactive prompt and supports command history using GNU Readline
- **Command Execution:** Finds and runs system executables via absolute paths, relative paths, or by searching the `$PATH` environment variable
- **Built-in Commands:**
  - `echo` (with `-n` option)
  - `cd` (with relative or absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- **Redirections & Pipelines:**
  - `<` (redirect input), `>` (redirect output)
  - `<<` (heredoc with delimiter), `>>` (append mode output)
  - `|` (inter-process communication via pipes)
- **Expansions & Quotes:**
  - Single quotes `' '` to inhibit all metacharacter interpretation
  - Double quotes `" "` to inhibit metacharacters except for environment variable expansion (`$`)
  - `$VAR` environment variable expansion and `$?` exit status expansion
- **Signal Handling:** Bash-like handling of `Ctrl-C` (new prompt), `Ctrl-D` (exit), and `Ctrl-\` (ignored) in interactive mode.

## Instructions

### Prerequisites

- A C compiler (`cc`, `clang`, or `gcc`)
- GNU `make`
- `readline` library (headers and runtime library)

### Compilation

To build the mandatory version of the shell, run:

```bash
make
```

To clean object files or perform a full recompile:
```
make clean   # Remove object files
make fclean  # Remove object files and the executable
make re      # Rebuild the project from scratch
```
They all can be combined with this options:
```bash
DEBUG=1 # Adds -g
DEBUG=2 # Adds -g + -fsanitize=address \
-Wconversion -Wsign-conversion \
-fsanitize=undefined -Warray-bounds \
-Wnull-dereference
```
### Execution
Run the executable directly from the terminal:
```
./minishell
```
### Usage
We don't perform split on Enviremental variables
We don't do cd -
Variables longer then 42000 characters are considerd ilegal
ANSI-C Quoting is out of the scope
Export printing env variables is UB according to posix manual

### Additional
Readline suppresion file for Valgrind
```
{
   readline_leaks
   Memcheck:Leak
   ...
   fun:readline
}
{
   readline_leaks2
   Memcheck:Leak
   ...
   fun:add_history
}
{
   rl_clear_history
   Memcheck:Leak
   ...
   fun:rl_clear_history
}
```

### Resources
#### References & Documentation
• GNU Bash Reference Manual
• GNU Readline Library Documentation
• Advanced Programming in the UNIX Environment by W. Richard Stevens
• Manual pages: man 2 fork, man 2 execve, man 2 pipe, man 2 dup2, man 2 waitpid, man 3 readline
AI Usage
• Planning & Architecture: Used to brainstorm and visualize process flows (AST/token parsing trees and pipe file descriptor routing).
• Testing & Edge Cases: Generated test matrices for edge cases (unclosed quotes, consecutive pipes, variable expansion edge cases).
• Debugging Guidance: Assisted in explaining system call error codes and signal handling constraints.
