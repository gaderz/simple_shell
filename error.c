#include "shell.h"

int num_len(int number);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - length of integers.
 * @number: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int number)
{
	unsigned int num_abs;
	int length = 1;
	int i;

	if (number < 0)
	{
		length++;
		num_abs = number * -1;
	}
	else
	{
		num_abs = number;
	}

	for (i = 1; num_abs / 10 > 0; i++)
	{
		num_abs /= 10;
	}

	length += i - 1;

	return (length);
}
/**
 * _itoa - function that Converts an integer to a string.
 * @num: The integer to be converted
 *
 * Return: The string converted
 */
char *_itoa(int num)
{
	char *buffer;
	int i;
	int len = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	for (i = len - 1; i >= 0; i--)
	{
		buffer[i] = (num1 % 10) + '0';
		num1 /= 10;
	}

	return (buffer);
}
/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 * Return: success
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			/* Handle error for environmental variable */
			error = error_env(args);
			break;
		case 1:
			/* Handle error for command not found */
			error = error_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				/* Handle error for exit command */
				error = error_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				/* Handle error for syntax */
				error = error_2_syntax(args);
			else
				/* Handle error for changing directory */
				error = error_2_cd(args);
			break;
		case 126:
			/* Handle error for permission denied */
			error = error_126(args);
			break;
		case 127:
			/* Handle error for command not found */
			error = error_127(args);
			break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);
}
