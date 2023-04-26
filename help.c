#include "shell.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);

/**
* get_args - Reads input from standard input and processes it.
* @line: Pointer to a buffer containing the input.
* @exe_ret: Pointer to an integer where the exit status is stored.
*
* Return: Pointer to a string containing the processed input.
*/
char *get_args(char *line, int *exe_ret)
{
	size_t buffer_size = 0;
	ssize_t read_len;
	char *prompt = "$ ";

	if (line)
		free(line);

	read_len = _getline(&line, &buffer_size, STDIN_FILENO);
	if (read_len == -1)
		return (NULL);
	if (read_len == 1)
	{
	hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read_len - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read_len);

	return (line);
}
/**
* call_args - Function that receives an array of arguments and executes them.
* @args: Array of arguments to execute.
* @front: First element of the history list.
* @exe_ret: Pointer to the exit status.
* Return: Return 0 on success or an error code otherwise.
*/
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, i = 0;

	if (!args[0])
		return (*exe_ret);

	while (args[i])
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				while (args[++i])
					free(args[i]);
				return (ret);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				while (args[++i])
					free(args[i]);
				return (ret);
			}
		}
		i++;
	}

	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
*run_args - Executes a command with arguments
*@args: List of arguments
*@front: Front of the linked list of environments
*@exe_ret: Exit value to be set after execution
*Return: Exit value of the command
*/
int run_args(char **args, char **front, int *exe_ret)
{
int exit_val, index;
int (*builtin)(char **args, char **front);

builtin = get_builtin(args[0]);

if (builtin)
{
exit_val = builtin(args + 1, front);
if (exit_val != EXIT)
*exe_ret = exit_val;
}
else
{
*exe_ret = execute(args, front);
exit_val = *exe_ret;
}

hist++;

index = 0;
while (args[index])
{
free(args[index]);
index++;
}

return (exit_val);
}
/**
 * handle_args - Handles shell arguments and executes commands
 * @exe_ret: Exit value to be set after execution
 *
 * Return: Exit value of the command
 */
int handle_args(int *exe_ret)
{
	int result = 0, index = 0;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (result);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	while (args[index])
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			result = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
		else
		{
			index++;
		}
	}
	if (args)
		result = call_args(args, front, exe_ret);

	free(front);
	return (result);
}
/**
* check_args - Checks if arguments are valid
* @args: List of arguments
*
* Return: 0 if valid, otherwise the error code
*/
int check_args(char **args)
{
	size_t index = 0;
	char *current, *next;

	while (args[index])
	{
		current = args[index];
		if (current[0] == ';' || current[0] == '&' || current[0] == '|')
		{
			if (index == 0 || current[1] == ';')
				return (create_error(&args[index], 2));
			next = args[index + 1];
			if (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
				return (create_error(&args[index + 1], 2));
		}
		index++;
	}
	return (0);
}
