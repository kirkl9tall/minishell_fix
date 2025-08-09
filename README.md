Minishell
A minimal UNIX shell implementation written in C, inspired by Bash.
It handles commands, pipes, redirections, environment variables, and more — all in compliance with the 42 school project requirements.

📌 Features
Prompt that waits for user commands

Execution of commands from $PATH or using absolute/relative paths

Built-in commands:

echo with -n option

cd with relative/absolute paths

pwd (current working directory)

export and unset (environment variables)

env (print environment variables)

exit

Redirections:

> (output redirection)

>> (append output)

< (input redirection)

<< (heredoc)

Pipes (|) to chain commands

 the schema  of the minishell is in this link  : that will  show you the flow of this program  : 
https://roadmap.sh/r/minishell-execution.
Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)

Error handling with descriptive messages
