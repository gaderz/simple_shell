#include "shell.h"

/**
 * error_env - returns an error message string
 * @args: argument list
 *
 * Return: pointer to error message string or NULL on failure
 */
char *error_env(char **args)
{
	char *errMsg, *histStr;
	int msgLen;

	histStr = _itoa(hist);
	if (!histStr)
		return (NULL);

	args--;
	msgLen = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 45;
	errMsg = malloc(sizeof(char) * (msgLen + 1));
	if (!errMsg)
	{
		free(histStr);
		return (NULL);
	}

	_strcpy(errMsg, name);
	_strcat(errMsg, ": ");
	_strcat(errMsg, histStr);
	_strcat(errMsg, ": ");
	_strcat(errMsg, args[0]);
	_strcat(errMsg, ": Unable to add/remove from environment\n");

	free(histStr);
	return (errMsg);
}
/**
 * error_1 - returns an error message string when an alias is not found
 * @args: argument list
 *
 * Return: pointer to error message string or NULL on failure
 */
char *error_1(char **args)
{
	char *errMsg;
	int msgLen;

	msgLen = _strlen(name) + _strlen(args[0]) + 13;
	errMsg = malloc(sizeof(char) * (msgLen + 1));
	if (!errMsg)
		return (NULL);

	_strcpy(errMsg, "alias: ");
	_strcat(errMsg, args[0]);
	_strcat(errMsg, " not found\n");

	return (errMsg);
}
/**
 * error_2_exit - returns an error message string
 * when the exit status is invalid
 * @args: argument list
 *
 * Return: pointer to error message string or NULL on failure
 */
char *error_2_exit(char **args)
{
	char *errMsg, *histStr;
	int msgLen;

	histStr = _itoa(hist);
	if (!histStr)
		return (NULL);

	msgLen = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 27;
	errMsg = malloc(sizeof(char) * (msgLen + 1));
	if (!errMsg)
	{
		free(histStr);
		return (NULL);
	}

	_strcpy(errMsg, name);
	_strcat(errMsg, ": ");
	_strcat(errMsg, histStr);
	_strcat(errMsg, ": exit: Illegal number: ");
	_strcat(errMsg, args[0]);
	_strcat(errMsg, "\n");

	free(histStr);
	return (errMsg);
}
/**
 * error_2_cd - creates an error message for cd command
 * @args: array of arguments passed to cd
 *
 * Return: pointer to a string containing error message, or NULL on failure
 */
char *error_2_cd(char **args)
{
	char *errMsg, *histStr;
	int msgLen;

	histStr = _itoa(hist);
	if (!histStr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';

	msgLen = _strlen(name) + _strlen(histStr) + _strlen(args[0]) + 24;
	errMsg = malloc(sizeof(char) * (msgLen + 1));
	if (!errMsg)
	{
		free(histStr);
		return (NULL);
	}

	_strcpy(errMsg, name);
	_strcat(errMsg, ": ");
	_strcat(errMsg, histStr);
	if (args[0][0] == '-')
		_strcat(errMsg, ": cd: Illegal option ");
	else
		_strcat(errMsg, ": cd: can't cd to ");
	_strcat(errMsg, args[0]);
	_strcat(errMsg, "\n");

	free(histStr);
	return (errMsg);
}

/**
 * error_2_syntax - creates an error message for syntax errors
 * @args: command and argument(s) that caused the error
 *
 * Return: pointer to the error message string, or NULL if malloc fails
 */
char *error_2_syntax(char **args)
{
	char *error_msg, *hist_str;
	int msg_len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	msg_len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error_msg = malloc(sizeof(char) * (msg_len + 1));
	if (!error_msg)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error_msg, name);
	_strcat(error_msg, ": ");
	_strcat(error_msg, hist_str);
	_strcat(error_msg, ": Syntax error: \"");
	_strcat(error_msg, args[0]);
	_strcat(error_msg, "\" unexpected\n");

	free(hist_str);
	return (error_msg);
}
