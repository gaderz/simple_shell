#include "shell.h"

/**
 * shellby_alias - handles the alias command in the shell
 * @args: array of arguments passed to the function
 * @front: pointer to the front of the list of history nodes
 *
 * Return: 0 on success, 1 on error
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, error_flag = 0;
	char *alias_value;

	if (!args[0])
	{
		for (temp = aliases; temp; temp = temp->next)
		{
			print_alias(temp);
		}
		return (error_flag);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		alias_value = _strchr(args[i], '=');
		if (!alias_value)
		{
			for (temp = aliases; temp; temp = temp->next)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
			}
			if (!temp)
				error_flag = create_error(args + i, 1);
		}
		else
			set_alias(args[i], alias_value);
	}
	return (error_flag);
}
/**
 * set_alias - sets or updates an alias in the list
 * @alias_name: the name of the alias to set or update
 * @alias_value: the value to set or update the alias to
 *
 * Return: void
 */
void set_alias(char *alias_name, char *alias_value)
{
	alias_t *temp_alias = aliases;
	int value_len, i = 0, j = 0;
	char *new_value;

	*alias_value = '\0';
	alias_value++;
	value_len = _strlen(alias_value) - _strspn(alias_value, "'\"");
	new_value = malloc(sizeof(char) * (value_len + 1));
	if (!new_value)
		return;
	while (alias_value[i])
	{
		if (alias_value[i] != '\'' && alias_value[i] != '"')
			new_value[j++] = alias_value[i];
		i++;
	}
	new_value[j] = '\0';
	for (; temp_alias; temp_alias = temp_alias->next)
	{
		if (_strcmp(alias_name, temp_alias->name) == 0)
		{
			free(temp_alias->value);
			temp_alias->value = new_value;
			break;
		}
	}
	if (!temp_alias)
		add_alias_end(&aliases, alias_name, new_value);
}
/**
 * print_alias - prints an alias in the format "alias name='value'\n"
 * @alias: pointer to alias to be printed
 *
 * Return: void
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int alias_string_len = _strlen(alias->name) + _strlen(alias->value) + 4;
	char *p;

	alias_string = malloc(sizeof(char) * (alias_string_len + 1));
	if (!alias_string)
		return;
	p = alias_string;
	p = _strcpy(p, alias->name);
	p = _strcat(p, "='");
	p = _strcat(p, alias->value);
	p = _strcat(p, "'\n");

	write(STDOUT_FILENO, alias_string, alias_string_len);
	free(alias_string);
}
/**
 * replace_aliases - replaces aliases in command args with their correspondin
 * values from the aliases linked list.
 * @args: an array of strings containing the command and its arguments
 *
 * Return: the modified array of strings, or NULL on failure
 */
char **replace_aliases(char **args)
{
	alias_t *current_alias;
	int arg_index = 0, index;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);

	while (args[arg_index])
	{
		current_alias = aliases;
		for (index = 0; current_alias; index++, current_alias = current_alias->next)
		{
			if (_strcmp(args[arg_index], current_alias->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(current_alias->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, current_alias->value);
				free(args[arg_index]);
				args[arg_index] = new_value;
				arg_index--;
				break;
			}
		}
		arg_index++;
	}

	return (args);
}
