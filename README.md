*This project has been created as part of the 42 curriculum by alehamad, tkhider.*

# Minishell

## Description

Minishell is a simplified Unix shell reproduction written in C as part of the 42 curriculum.

The objective of this project is to understand how a real shell works internally by implementing:

- An interactive prompt
- Lexing and parsing
- Environment variable expansion
- Builtin commands
- Pipes and redirections
- Process management
- Signal handling

The program runs in a loop, reading user input, analyzing it, executing the corresponding commands, and returning to the prompt until termination.

The project architecture is divided into five main components:

- **Lexing**
- **Parsing**
- **Expand**
- **Execution**
- **Clean Up**

---

## Instructions

### Compilation

```bash
make
```

### Launch

```bash
./minishell
```

The program must be executed without arguments.

---

## General Workflow

1. Display a prompt.
2. Read user input using `readline`.
3. Perform lexical analysis (tokenization).
4. Parse tokens into structured commands.
5. Expand environment variables.
6. Execute commands.
7. Free allocated memory and return to the prompt.

The loop stops when:
- The `exit` builtin is executed
- `Ctrl+D` is pressed

---

## Lexing

The lexer transforms raw user input into a list of tokens.

It identifies:

- Words
- Pipes (`|`)
- Redirections:
  - `>` (output)
  - `<` (input)
  - `>>` (append)
  - `<<` (heredoc)
- Environment variables (`$`)
- Quoted strings

This stage prepares structured data for the parser.

---

## Parsing

The parser:

- Validates syntax
- Detects errors
- Organizes tokens into command structures
- Associates arguments and redirections with each command

Parsing and execution logic are fully separated.

---

## Expand

The expand module handles:

- Environment variable expansion (`$VAR`)
- Special variables
- Argument adjustments after expansion
- Redirection expansion when required

Expansion is performed after parsing and before execution.

---

## Execution

The execution module is responsible for:

- Detecting and executing builtins
- Resolving command paths using `$PATH`
- Creating processes with `fork`
- Running external programs with `execve`
- Handling pipes with `pipe`
- Managing redirections with `dup` / `dup2`
- Waiting for child processes using `wait` / `waitpid`

It behaves similarly to an extended Pipex running in a loop.

---

## Clean Up

The clean up module ensures:

- Proper memory deallocation
- Freeing token lists
- Freeing command structures
- Preventing memory leaks
- Resetting the shell state between command executions

---

## Signal Handling

- `Ctrl+C` interrupts the current command and displays a new prompt.
- `Ctrl+D` exits the shell.
- `Ctrl+\` is ignored in interactive mode.

---

## Builtins Implemented

- `cd`
- `echo`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## Interactive Features

- Input handled with `readline`
- Command history with `add_history`
- Proper handling of `Ctrl+D`
- Signal management for interactive behavior

## Limitations

- This shell does not support logical operators such as `&&` and `||`.
- Wildcards (`*`) are not implemented (unless bonus).
- No support for subshells or job control.
- No support for command grouping with parentheses.

---

## Project Structure

```
.
├── inc
│	└── minishell.h
├── libft
├── makefile
└── src
	├── clean_up
	├── cmd
	├── debug
	├── env
	├── exec
	├── expand
	├── lexer
	├── main
	├── parsing
	├── redirections
	└── struct
```

> `libft/` contains the custom C standard library used by the project.

---

## System Functions Allowed

### Readline
`readline`, `add_history`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`

### Process Management
`fork`, `execve`, `wait`, `waitpid`, `wait3`, `wait4`, `exit`

### File Handling & Redirections
`open`, `close`, `read`, `write`, `access`, `dup`, `dup2`, `pipe`, `unlink`

### Signals
`signal`, `sigaction`, `kill`, `sigemptyset`, `sigaddset`

### Environment
`getenv`

### Directories
`opendir`, `readdir`, `closedir`

### File Metadata
`stat`, `lstat`, `fstat`

### Terminal / Termcap
`isatty`, `ttyname`, `ttyslot`, `ioctl`, `tcgetattr`, `tcsetattr`,
`tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Error Handling
`perror`, `strerror`

### Output
`printf`

### Memory Management
`malloc`, `free`

---

## Resources

- Unix manual pages (`man 2`, `man 3`)
- GNU Readline documentation
- POSIX signal documentation
- Shell architecture references
- Bash | Bash --posix | Dash
- Minishell tester and manual tests

### AI Usage

AI tools were used to:

- Quickly find documentation and information about allowed system functions
- Better understand how Bash behaves in specific cases through comparison and testing
- Accelerate research on shell behavior and edge cases
- Assist in structuring and writing this README

All implementation decisions and code were written and validated by the authors.
