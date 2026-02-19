# Minishell - @42Paris
### 🐚 About the project
Minishell is a 42 school group project that consists of creating a simple shell. It is a deep dive into processes, system calls, and the inner workings of a command-line interpreter.

The goal was to recreate a miniature version of Bash, focusing on process synchronization, environment variable management, and redirection handling.

### 🚀 Features
#### Core Functionality
* Interactive Prompt: Displays a prompt while waiting for a new command.

* Command Execution: Search and launch executables based on the PATH variable or relative/absolute paths.

* History: Working command history (up and down arrows).

* Quotes Handling: * Single quotes (' '): Prevent the shell from interpreting meta-characters.

* Double quotes (" "): Prevent interpreting meta-characters except for $ (environment variables).

#### Redirections & Pipes
* Pipes (|): Connect the output of one command to the input of the next.

* Input Redirection (<): Redirect file content to stdin.

* Output Redirection (>): Redirect stdout to a file (overwrite).

* Append Redirection (>>): Redirect stdout to a file (append).

* Here-doc (<<): Read input until a line containing the delimiter is seen.

#### Built-ins
I have implemented the following essential built-in commands:

* echo (with option -n)

* cd (relative or absolute paths)

* pwd

* export

* unset

* env

* exit

### 🛠️ Implementation Details
#### The Pipeline
* Lexer: Breaks the input string into tokens (words, pipes, redirections).

* Parser: Organizes tokens into a command structure (simple command list).

* Expander: Handles environment variables (e.g., $USER) and removes quotes.

* Executor: Handles fork(), pipe(), dup2(), and waitpid() to run the commands in the correct order.

#### Signal Handling
* Ctrl-C: Displays a new prompt on a newline.

* Ctrl-D: Exits the shell.

* Ctrl-\: Does nothing (matches Bash behavior).

### 💻 Usage
Compilation
The project requires the readline library.
```Bash
# Compile the programme
make

# Execution
./minishell
```

### 📬 Contact
* Login: qsomarri

* School: 42 Paris
