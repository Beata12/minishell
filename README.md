# Minishell

## Description

Minishell is a project which is creating a simple shell in C, reproducing the behavior of bash. The shell provides a prompt, handles commands, and supports various features including command history, redirection, and pipes. This project is a collaborative effort, and we are currently focused on tokenization, parsing, and execution. We have implemented built-in commands and are working to ensure their correct functionality.
This project is being developed on the Linux operating system.

## Features

- Prompt Display: Displays a prompt while waiting for user input.
- History: Maintains a history of commands entered.
- Executable Search and Launch: Searches for and launches the correct executable based on the PATH variable or a given relative/absolute path.
- Signal Handling: Uses a single global variable to indicate received signals, ensuring signal handlers do not access main data structures.

## Quote Handling:

- Single quotes (') prevent interpretation of metacharacters.
- Double quotes (") prevent interpretation of metacharacters except for the dollar sign ($).

## Redirections:

- '<' redirects input.
- '>' redirects output.
- '<<' reads input until a given delimiter line.
- '>>' appends redirected output.

## Pipes (|):

- Connects the output of one command to the input of the next.

## Environment Variables:

- Expands variables prefixed with $ to their values.

## Exit Status ($?):

- Expands to the exit status of the most recently executed foreground pipeline.

## Interactive Mode:

- ctrl-C: Displays a new prompt on a new line.
- ctrl-D: Exits the shell.
- ctrl-\: Does nothing.

## Built-in Commands

- echo with -n option
- cd with a relative or absolute path
- pwd without options
- export without options
- env without options or arguments
-
-
-
- exit without options
