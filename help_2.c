#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
void variable_replacement(char **args, int *exe_ret);
char *get_env_value(char *name, int len);

/**
* free_args - Frees up memory consumed  by arguments.
* @args: A null-terminated double pointer containing commands/arguments.
* @front: A double pointer to the beginning of argumentss.
*/
void free_args(char **args, char **front)
{
	size_t idx = 0;

	while (args[idx] || args[idx + 1])
	{
		free(args[idx]);
		idx++;
	}
	free(args[idx]);
	free(front);
}
/**
* get_pid - Gets the current process ID of shell.
* Description: Opens the stat file, a space-delimited file containing
*              information about the current process. The PID is the
*              first word in the file. The function reads the PID into
*              a buffer and replace the space at the end with a \0 byte.
*
* Return: The current process ID or NULL on failure to execute.
*/
char *get_pid(void)
{
	size_t index = 0;
	char *buffer;
	ssize_t file;
	int read_result;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read_result = read(file, buffer, 120);
	close(file);

	if (read_result == -1)
	{
		free(buffer);
		return (NULL);
	}

	do {
		index++;

	} while (buffer[index] != ' ');

	buffer[index] = '\0';

	return (buffer);
}
/**
* get_env_value - Gets the value corresponding to an environmental variable.
* @beginning: The environmental variable to search for.
* @len: The length of the environmental variable to search for.
*
* Return: If the variable is not found - an empty string.
*         Otherwise - the value of the environmental variable.
*
* Description: Variables are stored in the format VARIABLE=VALUE.
*/
char *get_env_value(char *name, int len)
{
	char **env_var;
	char *value = NULL, *tmp, *var_name;

	var_name = malloc(len + 1);
	if (!var_name)
	return (NULL);
	var_name[0] = '\0';
	_strncat(var_name, name, len);

	env_var = _getenv(var_name);
	free(var_name);
	if (env_var)
	{
	tmp = *env_var;
	do {
		tmp++;
	} while (*tmp != '=');

	value = malloc(_strlen(tmp + 1) + 1);
	if (value)
	_strcpy(value, tmp + 1);
	}

	return (value);
}
/**
* variable_replacement -function that  Handles variable replacement.
* @line: A double pointer containing the command and arguments.
* @exe_ret: A pointer to the return value of the last executed command.
*
* Description: Replaces $$ with the current PID, $? with the return value
*              of the last executed program, and envrionmental variables
*              preceded by $ with their corresponding value.
*/

void variable_replacement(char **line, int *exe_ret)
{
	int var_start, var_end = 0, var_len;
	char *var_value = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	while (old_line[var_end])
	{
		var_start = var_end;
		if (old_line[var_start] == '$' && old_line[var_start + 1] &&
			old_line[var_start + 1] != ' ')
		{
			if (old_line[var_start + 1] == '$')
			{
				var_value = get_pid();
				var_end = var_start + 2;
			}
			else if (old_line[var_start + 1] == '?')
			{
				var_value = _itoa(*exe_ret);
				var_end = var_start + 2;
			}
			else if (old_line[var_start + 1])
			{
				/* extract the variable name to search for */
				for (var_end = var_start + 1; old_line[var_end] &&
						old_line[var_end] != '$' &&
						old_line[var_end] != ' '; var_end++)
					;
				var_len = var_end - (var_start + 1);
				var_value = get_env_value(&old_line[var_start + 1], var_len);
			}
			new_line = malloc(var_start + _strlen(var_value)
						+ _strlen(&old_line[var_end]) + 1);
			if (!new_line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, var_start);
			if (var_value)
			{
				_strcat(new_line, var_value);
				free(var_value);
				var_value = NULL;
			}
			_strcat(new_line, &old_line[var_end]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			var_end = 0;
		}
		else
		{
			var_end++;
		}
	}
}
