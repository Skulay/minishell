*This project has been created as part of the 42 curriculum by alehamad, tkhider.*

<div align="center">

# 🐚 minishell

**A small Bash-like Unix shell, written from scratch in C.**

![Language](https://img.shields.io/badge/language-C-00599C?style=flat-square&logo=c)
![School](https://img.shields.io/badge/school-42-000000?style=flat-square)
![Norm](https://img.shields.io/badge/norminette-passing-success?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux-FCC624?style=flat-square&logo=linux&logoColor=black)

[Overview](#-overview) •
[Features](#-features) •
[Getting started](#-getting-started) •
[Architecture](#-architecture) •
[Examples](#-examples) •
[Limitations](#-limitations) •
[Authors](#-authors)

</div>

---

## 📖 Overview

**minishell** is a reimplementation of a subset of **Bash**: an interactive prompt that reads a command line, splits it into tokens, builds a command list, expands variables, then runs it with pipes, redirections and heredocs, the same way a real shell does.

The goal of the project is to understand what happens between pressing <kbd>Enter</kbd> and seeing a program's output:

- how a command line is **lexed** and **parsed**
- how **quotes** and **`$VARIABLES`** are resolved
- how processes are created with **`fork` / `execve`** and synchronised with **`waitpid`**
- how file descriptors are wired together with **`pipe` / `dup2`**
- how **signals** behave differently at the prompt, in a heredoc, and while a child is running

Everything is written in C (Norm-compliant) on top of our own `libft`, with **GNU Readline** as the only external library for line editing and history.

---

## ✨ Features

### Command line

| Feature | Details |
|---|---|
| Interactive prompt | `minishell# ` prompt, line editing and history through `readline` / `add_history` |
| Non-interactive mode | Commands can be piped in (`echo "ls" \| ./minishell`); the prompt is skipped when stdin is not a TTY |
| Single quotes `'…'` | No interpretation of anything inside |
| Double quotes `"…"` | Everything is literal except `$` |
| Syntax checks | Unclosed quotes, missing redirection targets, dangling or doubled pipes |

### Expansion

| Feature | Details |
|---|---|
| `$VAR` | Replaced by its value from the shell's own environment |
| `$?` | Exit status of the last pipeline |
| Word splitting | Unquoted expansions are split on spaces (`export X="a b"` → `echo $X` gives 2 args) |
| Heredoc expansion | Variables are expanded in heredoc bodies, **unless** the delimiter is quoted (`<< 'EOF'`) |

### Redirections & pipes

| Operator | Meaning |
|---|---|
| `<  file` | Read stdin from `file` |
| `>  file` | Write stdout to `file` (truncate) |
| `>> file` | Write stdout to `file` (append) |
| `<< LIMIT` | Heredoc: read lines until `LIMIT` |
| `cmd1 \| cmd2 \| …` | Pipelines of any length, every command in its own process |

### Builtins

| Builtin | Supported |
|---|---|
| `echo` | with `-n` (including `-nnn` and repeated flags) |
| `cd` | relative or absolute path, updates `PWD` / `OLDPWD` |
| `pwd` | no options |
| `export` | with or without arguments; sorted listing, identifier validation |
| `unset` | no options |
| `env` | no options or arguments |
| `exit` | with an optional numeric status (wraps modulo 256, rejects non-numeric args) |

### Environment & signals

| Feature | Details |
|---|---|
| Own environment | `envp` is copied at startup; builtins modify the copy, not the parent's |
| `SHLVL` | Incremented at startup |
| Empty environment | `env -i ./minishell` still starts, with a minimal `PWD` / `SHLVL` |
| `PATH` resolution | Commands are searched in `$PATH`, or run directly when they contain a `/` |
| <kbd>Ctrl</kbd>+<kbd>C</kbd> | New prompt on a new line, `$?` set to `130` |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | Exits the shell (prints `exit`) |
| <kbd>Ctrl</kbd>+<kbd>\\</kbd> | Ignored at the prompt and inside heredocs |
| Exit statuses | `127` command not found, `126` not executable, `128 + n` when killed by a signal |

> Only **one global variable** is used, as required by the subject: it stores the number of the received signal.

---

## 🚀 Getting started

### Requirements

- Linux (or macOS)
- `cc` / `gcc` / `clang`
- `make`
- `git` and an internet connection on the first build (to fetch `libft`)
- GNU Readline development headers

```bash
# Debian / Ubuntu
sudo apt install build-essential libreadline-dev
```

### Build & run

```bash
git clone <repository-url> minishell
cd minishell
make
./minishell
```

The program takes **no arguments**.

> `libft` is not stored in this repository: on the first `make`, it is cloned automatically from [Skulay/libft](https://github.com/Skulay/libft) into `libft/`.

### Make rules

| Rule | Action |
|---|---|
| `make` / `make all` | Clone `libft` if missing, build `libft.a`, then `minishell` |
| `make clean` | Remove object files |
| `make fclean` | Remove object files, `libft.a` and the binary |
| `make re` | `fclean` then `all` |

---

## 🏗 Architecture

Each line typed at the prompt goes through the same pipeline before control comes back to the user:

```
                  ┌──────────────────────────────────────────────────────┐
                  │                     shell loop                       │
                  ▼                                                      │
  ┌──────────┐  ┌──────────┐  ┌───────────┐  ┌──────────┐  ┌──────────┐  │
  │ readline │─▶│  Lexer   │─▶│  Parser   │─▶│  Expand  │─▶│   Exec   │──┤
  └──────────┘  └──────────┘  └───────────┘  └──────────┘  └──────────┘  │
     raw line    t_token list   t_cmd list    $VAR, $?,     fork/execve  │
                 WORD, PIPE,    args + redirs quote removal pipes, dup2  │
                 REDIR_*, ...   syntax check  word split    heredocs     │
                                                                         │
                                                          ┌──────────┐   │
                                                          │ Clean up │◀──┘
                                                          └──────────┘
                                                          free tokens & cmds
```

### 1. Lexer — `src/lexer/`

Turns the raw line into a linked list of `t_token`, each tagged with a type:

```c
typedef enum e_type { WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC, ERROR } t_type;
```

Quotes are kept attached to their word so that the expander knows what to interpret later. Unclosed quotes and unsupported operators are reported here.

### 2. Parser — `src/parsing/`

Validates the token sequence (no pipe at either end, every redirection followed by a word, …) and groups the tokens into a linked list of commands, one per pipeline segment:

```c
typedef struct s_cmd
{
    char            **arg_cmd;  // argv for execve / builtins
    t_redir         *redir;     // ordered list of <, >, >>, <<
    struct s_cmd    *next;      // next command in the pipeline
}   t_cmd;
```

### 3. Expander — `src/expand/`

Walks each argument and redirection target with a small state machine (`NORMAL`, `SOLO_QUOTE`, `DUAL_QUOTE`):

- replaces `$VAR` and `$?`
- removes quotes
- splits unquoted expansion results into several arguments
- decides whether a heredoc body must be expanded

### 4. Executor — `src/exec/`, `src/redirections/`, `src/cmd/`

- **Heredocs** are all read *before* anything is forked, so <kbd>Ctrl</kbd>+<kbd>C</kbd> can cancel the whole line cleanly.
- A **single builtin** without a pipe runs in the shell process itself (so `cd`, `export`, `exit` affect the shell).
- Otherwise, every command of the pipeline is **forked**, its pipe ends and redirections are wired with `dup2`, and it runs either the builtin or `execve` on the path resolved from `$PATH`.
- The parent closes every fd it doesn't need, waits for all children, and stores the status of the **last** one in `$?`.

### 5. Signals — `src/signals/`

Three signal setups, swapped depending on context:

| Context | `SIGINT` (<kbd>Ctrl</kbd>+<kbd>C</kbd>) | `SIGQUIT` (<kbd>Ctrl</kbd>+<kbd>\\</kbd>) |
|---|---|---|
| Prompt | redraw a fresh prompt | ignored |
| Heredoc | abort the heredoc and the command | ignored |
| Child running | default (kills the child) | default (`Quit (core dumped)`) |

### 6. Clean up — `src/clean_up/`

Tokens and commands are freed after every line; the environment and Readline history are freed when the shell exits.

---

## 📂 Project structure

```
.
├── inc/
│   └── minishell.h          # all types and prototypes
├── libft/                   # our own C library, cloned by make (not versioned here)
├── makefile
└── src/
    ├── main/                # entry point and shell loop
    ├── lexer/               # tokenisation
    ├── parsing/             # syntax checks, t_cmd construction
    ├── expand/              # $VAR, $?, quotes, word splitting
    ├── exec/                # pipelines, fork/execve, PATH lookup, heredocs
    ├── redirections/        # <, >, >>, << wiring
    ├── cmd/                 # builtins: echo, cd, pwd, export, unset, env, exit
    ├── env/                 # environment copy, SHLVL
    ├── signals/             # signal handlers
    ├── struct/              # struct initialisation
    ├── clean_up/            # memory release
    └── debug/               # token / AST / env printers used during development
```

---

## 💻 Examples

```console
$ ./minishell
minishell# echo "Hello $USER" '$HOME is not expanded here'
Hello sku $HOME is not expanded here

minishell# export GREETING="hi there"
minishell# echo $GREETING | tr a-z A-Z > out.txt
minishell# cat < out.txt
HI THERE

minishell# cat << EOF | wc -l
> line one
> line two: $GREETING
> EOF
2

minishell# ls /nowhere
ls: cannot access '/nowhere': No such file or directory
minishell# echo $?
2

minishell# unknown_cmd
minishell: unknown_cmd: command not found
minishell# echo $?
127

minishell# exit 42
exit
$ echo $?
42
```

---

## 🚧 Limitations

This is the **mandatory part** of the subject only. Not implemented, on purpose:

- `&&`, `||` and parentheses for priorities *(bonus)*
- `*` wildcard expansion *(bonus)*
- `;` command separator and `\` escaping *(not required by the subject)*
- Subshells, job control, `$(…)` command substitution, aliases, shell scripts

---

## 🧪 Testing

The shell was tested by running the same inputs in `minishell` and in `bash` / `bash --posix` and comparing output and exit status, with:

- manual tests on edge cases (quotes, empty variables, invalid redirections, signals inside heredocs and pipelines)
- community minishell testers
- `valgrind` for leaks and unclosed file descriptors:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
```

*(Readline keeps some memory of its own until exit, which the subject explicitly allows. Only leaks coming from our code count.)*

---

## 📚 Resources

- `man 2` / `man 3` pages: `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `sigaction`, `open`, `access`
- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html), especially *Shell Operation*, *Quoting* and *Redirections*
- [GNU Readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- Bash, `bash --posix` and `dash` as reference behaviour

---

## 👥 Authors

| | Login | Main areas |
|---|---|---|
| 🧑‍💻 | **alehamad** | Lexer, parser, expander, environment |
| 🧑‍💻 | **tkhider** | Execution, pipes, redirections, builtins, signals |

<div align="center">

*Made with ☕ at 42*

</div>
