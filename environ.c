#include "shell.h"


/**
 * shellby_env - prints the current environment
 * @args: arguments passed to the command
 * @front: pointer to the front of the command
 *
 * Return: Always 0
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char newline = '\n';

	if (!environ)
		return (-1);

	i = 0;
	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &newline, 1);
		i++;
	}
	(void)args;
	return (0);
}

/**
 * shellby_setenv - Set or add value to environment variable.
 * @args: Array of arguments passed to shellby.
 * @front: Pointer to the head of the list.
 *
 * Return: On success, returns 0. On failure, returns -1.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int i = 0;

	/* Check if both arguments are provided */
	if (!args[0] || !args[1])
		return (create_error(args, -1));

	/* Create new value for environment variable */
	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	/* Check if environment variable exists and replace its value */
	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}

	/* Add new environment variable */
	size = 0;
	while (environ[size])
		size++;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	/* Copy existing environment variables to new_environ */
	i = 0;
	while (environ[i])
	{
		new_environ[i] = environ[i];
		i++;
	}

	/* Update environment with new variable */
	free(environ);
	environ = new_environ;
	environ[i] = new_value;
	environ[i + 1] = NULL;

	return (0);
}
/**
 * shellby_unsetenv - Remove an environment variable
 * @args: An array of arguments passed to the shell
 * @env_list: A pointer to the head of the list of environment variables
 *
 * Return: On success, returns 0. On failure, returns -1.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **env_list)
{
	char **env_var_ptr, **new_env_list;
	size_t size;
	int old_index, new_index;

	/* Check if an argument is provided */
	if (!args[0])
		return (create_error(args, -1));

	/* Get the environment variable */
	env_var_ptr = _getenv(args[0]);
	if (!env_var_ptr)
		return (0);

	/* Allocate memory for the new environment list */
	size = 0;
	while (env_list[size])
	{
		size++;
	}
	new_env_list = malloc(sizeof(char *) * size);
	if (!new_env_list)
		return (create_error(args, -1));

	/* Copy the existing environment list to the new environment*/
	old_index = 0;
	new_index = 0;
	while (env_list[old_index])
	{
		if (*env_var_ptr == env_list[old_index])
		{
			free(*env_var_ptr);
			env_var_ptr++;
			continue;
		}
		new_env_list[new_index] = env_list[old_index];
		old_index++;
		new_index++;
	}

	/* Update the environment */
	free(env_list);
	env_list = new_env_list;
	env_list[size - 1] = NULL;

	return (0);
}
