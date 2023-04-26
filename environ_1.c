#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
* _copyenv - make a copy of the env.
*
* Return: on error - NULL.
*         O/w - a pointer to the new copy.
*/
char **_copyenv(void)
{
	char **new_environ;
	size_t i;
	int index;

	i = 0;
	while (environ[i])
		i++;

	new_environ = malloc(sizeof(char *) * (i + 1));
	if (!new_environ)
		return (NULL);

	index = 0;
	while (environ[index])
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			while (--index >= 0)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
		index++;
	}
	new_environ[index] = NULL;

	return (new_environ);
}
/**
* free_env - Frees the the copied env.
*/
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
* _getenv - Gets an env var from the PATH.
* @var: pointer to nvironmental variable.
*
* Return: If the env var is not found  - NULL.
*         Otherwise - a pointer to the env var
*/

char **_getenv(const char *var)
{
	int index = 0, lenght = _strlen(var);

	while (environ[index])
	{
		if (_strncmp(var, environ[index], lenght) == 0)
			return (&environ[index]);
		index++;
	}

	return (NULL);
}
