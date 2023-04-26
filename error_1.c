#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
* error_126 -make an error message for permission denied failures.
* @args: double pointers array of arguments passed to the command.
*
* Return: The error string.
*/
char *error_126(char **args)
{
	char *error, *hist_str;
	int pos;
	int len, name_len, hist_str_len, args_len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	name_len = _strlen(name);
	hist_str_len = _strlen(hist_str);
	args_len = _strlen(args[0]);
	len = name_len + hist_str_len + args_len + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	pos = 0;
	_strcpy(error + pos, name);
	pos += name_len;
	_strcpy(error + pos, ": ");
	pos += 2;
	_strcpy(error + pos, hist_str);
	pos += hist_str_len;
	_strcpy(error + pos, ": ");
	pos += 2;
	_strcpy(error + pos, args[0]);
	pos += args_len;
	_strcpy(error + pos, ": Permission denied\n");

	free(hist_str);
	return (error);
}
/**
* error_127 - generate an error message for command not found failures.
* @args: bouble pointer array of arguments passed to the command.
*
* Return: The error string.
*/

char *error_127(char **args)
{
	char *error, *hist_str;
	char *error_ptr;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
	free(hist_str);
	return (NULL);
	}

	error_ptr = error;
	error_ptr = _strcpy(error_ptr, name);
	error_ptr = _strcat(error_ptr, ": ");
	error_ptr = _strcat(error_ptr, hist_str);
	error_ptr = _strcat(error_ptr, ": ");
	error_ptr = _strcat(error_ptr, args[0]);
	error_ptr = _strcat(error_ptr, ": not found\n");
	*error_ptr = '\0';

	free(hist_str);
	return (error);
}
