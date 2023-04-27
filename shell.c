#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * sig_handler - Signal handler function for SIGINT
 * @sig: The signal integer
 *
 * Description: This function is called when the user enters a SIGINT signal (usually by pressing Ctrl-C).
 * It prints a new prompt on a new line and resumes waiting for user input.
 */
void sig_handler(int sig)
{
        char *new_prompt = "\n#cisfun$ ";
       /*	New prompt to be displayed*/

        (void)sig;
	/*Suppress unused parameter warning*/
        signal(SIGINT, sig_handler);
	/*Reinstall the signal handler*/
        write(STDIN_FILENO, new_prompt, 10);
	/* Write the new prompt to the standard output */
}
/**
 * execute - executes a command
 * @args: list of arguments to the command
 * @front: pointer to the first node of the linked list
 *
 * Return: integer value indicating success or failure of the execution
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}
/**
 * main - Entry point for shell program
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
    int exe_ret_val = 0, retn_val;
    int *exe_ret = &retn_val;
    char *promt = "#cisfun$ ", *new_ln = "\n";

    name = argv[0];
    hist = 1;
    aliases = NULL;
    signal(SIGINT, sig_handler);

    *exe_ret = 0;
    environ = _copyenv();
    if (!environ)
        exit(-100);

    if (argc != 1)
    {
        exe_ret_val = proc_file_commands(argv[1], exe_ret);
        free_env();
        free_alias_list(aliases);
        return (*exe_ret);
    }

    if (!isatty(STDIN_FILENO))
    {
        do {
            exe_ret_val = handle_args(exe_ret);
        } while (exe_ret_val != END_OF_FILE && exe_ret_val != EXIT);
        free_env();
        free_alias_list(aliases);
        return (*exe_ret);
    }

    for (;;)
    {
        write(STDOUT_FILENO, promt, 10);
        exe_ret_val = handle_args(exe_ret);
        if (exe_ret_val == END_OF_FILE || exe_ret_val == EXIT)
        {
            if (exe_ret_val == END_OF_FILE)
                write(STDOUT_FILENO, new_ln, 10);
            free_env();
            free_alias_list(aliases);
            return (*exe_ret);
        }
    }

    free_env();
    free_alias_list(aliases);
    return (*exe_ret);
}
