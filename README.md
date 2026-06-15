# Minishell

A small reimplementation of a Unix shell, written in C as part of the
[42](https://42.fr) curriculum. It reproduces a useful subset of `bash`'s
behaviour: an interactive prompt with line editing and history, command
execution through `PATH` lookup, pipes, redirections, here-documents,
environment-variable expansion, quote handling, signals, and the core
built-in commands.

The interactive prompt looks like this:

```
$_MINI_SHELL_$:
```

## Features

- **Interactive line editing & history** via GNU `readline`.
- **Command execution** by searching the directories in `PATH`, plus
  execution of absolute and relative paths.
- **Pipes** — chain commands with `|`.
- **Redirections**
  - `<`  — redirect input from a file
  - `>`  — redirect output (truncate)
  - `>>` — redirect output (append)
  - `<<` — here-document (read until a delimiter)
- **Environment-variable expansion** — `$VAR` and the last exit status, with
  expansion disabled inside single quotes.
- **Quoting** — single (`'`) and double (`"`) quotes.
- **Signals** — `Ctrl-C`, `Ctrl-D` and `Ctrl-\` behave like an interactive
  shell.
- **Built-in commands**: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`,
  `env`, `exit`.

## Requirements

- A C compiler (`gcc` or `clang`) and `make`.
- The **GNU readline** library (development headers).

> **Note on readline paths.** The `Makefile` was written for macOS with
> readline installed through Homebrew, so it points at
> `/Users/$USER/.brew/opt/readline`. On Linux (or a different Homebrew
> prefix) adjust the `LIB` and include flags in the `Makefile` to match your
> installation, e.g. `-lreadline` with the headers on the default include
> path, or `pkg-config --cflags --libs readline`.

## Build

```sh
make        # build ./minishell (also builds src/libft/libft.a)
make clean  # remove object files
make fclean # remove object files and the minishell binary
make re     # fclean + build
```

## Usage

```sh
./minishell
```

Then type commands at the `$_MINI_SHELL_$:` prompt:

```
$_MINI_SHELL_$: echo "hello $USER" | tr a-z A-Z
HELLO M4NTR4
$_MINI_SHELL_$: cat << EOF > out.txt
> line one
> line two
> EOF
$_MINI_SHELL_$: export GREETING=hi && env | grep GREETING
GREETING=hi
$_MINI_SHELL_$: exit
```

## Project structure

```
.
├── Makefile              # Top-level build (links against libft + readline)
├── includes/             # Public headers
│   ├── minishell.h       # Core structs (t_all, t_cmd, t_pipe…) and prototypes
│   └── libft.h
├── src/                  # Shell implementation
│   ├── main.c            # Entry point + REPL loop (readline → parse → exec)
│   ├── lexer.c           # Lexing / pre-parse driver
│   ├── lexer_utils.c
│   ├── tokens.c          # Operator tokenisation (| < > >> <<)
│   ├── split_parse.c     # Tokenising the input into words
│   ├── split_parse_utils.c
│   ├── split_utils.c
│   ├── parser_utils.c    # Command building + builtin detection
│   ├── checkers.c        # Syntax / quote validation
│   ├── checkers2.c
│   ├── expander.c        # $VAR and variable expansion
│   ├── find_replace.c    # String replacement used by the expander
│   ├── trim.c
│   ├── search.c          # PATH lookup for executables
│   ├── executor.c        # Process creation, piping, redirection
│   ├── executor2.c
│   ├── fd.c              # File-descriptor / here-doc handling
│   ├── builtins.c        # cd, pwd, exit
│   ├── builtins2.c       # echo, export, unset
│   ├── env.c / env2.c    # Environment table management
│   ├── signals.c         # Signal handlers
│   ├── init_structs.c    # State initialisation
│   ├── free.c            # Cleanup
│   ├── utils.c
│   ├── ft_split_delete.c
│   └── libft/            # 42 standard C library (vendored)
└── docs/                 # Reference material (bash manual, "Write your own shell")
```

## How it works

Each iteration of the read–eval–print loop in `src/main.c`:

1. **Read** a line with `readline`, and add non-empty lines to the history.
2. **Lex / parse** (`lexer.c`, `tokens.c`, `split_parse.c`, `checkers.c`) —
   split the line into words and operators, validate quotes and operator
   syntax, then build a list of `t_cmd` structures describing each command in
   the pipeline together with its arguments and redirections.
3. **Expand** (`expander.c`) — substitute environment variables.
4. **Execute** (`executor.c`, `fd.c`) — set up pipes and redirections, run
   built-ins in the parent when appropriate, otherwise `fork`/`execve` the
   external program found via `PATH` (`search.c`), and wait for children to
   collect the exit status.

## Authors

Built by **ahammoud** and **jvelasco** as a 42 group project.

## License

Educational project — no specific license. Feel free to read and learn from it.
