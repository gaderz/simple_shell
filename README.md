# Simple Shell

* This is a simple Unix shell program written in C. It supports basic commands, such as ls, cd, and exit, as well as simple piping and redirection.

## Getting Started

* Prerequisites

* To build and run this program, you'll need a Unix-like operating system (e.g., Linux, macOS) and a C compiler (e.g., gcc). You can check if you have a C compiler installed by running gcc --version.

## Building

* To build the program, simply run make in the root directory of the project. This will compile the source files and create an executable called simple_shell.

## Running

* To run the program, simply execute the simple_shell binary. This will start the shell and display a prompt ($ ) indicating that it's ready to accept commands.

## Testing

* To run the tests, you'll need to have the check unit testing framework installed. You can install it on Ubuntu or Debian-based systems by running sudo apt-get install check.

* Once you have check installed, run make test to build and run the tests.

# Features

* This simple shell supports the following features:

* Command execution: You can execute any command that's available in your system's $PATH.
* Piping: You can pipe the output of one command to another command, e.g., ls | grep foo.
* Redirection: You can redirect the output of a command to a file, e.g., ls > files.txt.
* Background execution: You can run a command in the background by appending & to the command, e.g., sleep 10 &.
* Environment variables: You can read and set environment variables using the export command, e.g., export MYVAR=hello.
* Built-in commands: The shell supports a few built-in commands, such as cd, pwd, and exit.
