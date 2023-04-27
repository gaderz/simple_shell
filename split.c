#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
* token_len - finds the length of a token in a string
* @str: the string to search
* @delim: the delimiter character
* Return: the length of the token
*/
int token_len(char *str, char *delim)
{
	int i = 0, length = 0;

	for (i = 0; *(str + i) && *(str + i) != *delim; i++)
	{
		length++;
	}

	return (length);
}
/**
* count_tokens - Count the number of tokens in a string
* @str: The string to count tokens from
* @delim: The delimiter to split the string by
*
* Return: The number of tokens in the string
*/
int count_tokens(char *str, char *delim)
{

	int i, num_tokens = 0, str_len = 0;

	while (*(str + str_len))
		str_len++;
	for (i = 0; i < str_len; i++)
	{
		if (*(str + i) != *delim)
		{
			num_tokens++;
			i += token_len(str + i, delim);
		}
	}

	return (num_tokens);
}
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, num_tokens, t = 0, len, l;

	num_tokens = count_tokens(line, delim);
	if (num_tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (num_tokens + 2));
	if (!ptr)
		return (NULL);

	while (t < num_tokens)
	{
		while (line[i] == *delim)
			i++;

		len = token_len(line + i, delim);
		ptr[t] = malloc(sizeof(char) * (len + 1));
		if (!ptr[t])
		{
			l = t - 1;
			while (l >= 0)
			{
				free(ptr[l]);
				l--;
			}
			free(ptr);
			return (NULL);
		}

		l = 0;
		while (l < len)
		{
			ptr[t][l] = line[i];
			i++;
			l++;
		}

		ptr[t][l] = '\0';
		t++;
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
