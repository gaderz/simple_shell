#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - searches for the location of
 * a given command in PATH directories
 * @command: the command to search for
 *
 * Return: a pointer to the location of the command, or NULL if not found
 */
char *get_location(char *command)
{
	/* Declare variables */
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	/* Get the PATH environment variable */
	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	/* Split PATH into directories and create a linked list */
	dirs = get_path_dir(*path + 5);
	head = dirs;

	/* Loop through the directories in the linked list */
	for (; dirs; dirs = dirs->next)
	{
		/* Allocate memory for the full path to the command */
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		/* Check if the file at the full path exists */
		if (stat(temp, &st) == 0)
		{
			/* Free the linked list and return the full path */
			free_list(head);
			return (temp);
		}

		/* Free the memory allocated for the full path */
		free(temp);
	}

	/* Free the linked list */
	free_list(head);

	/* Return NULL if the command is not found */
	return (NULL);
}


/**
 * fill_path_dir - fills empty PATH directories with PWD
 * @path: the PATH environment variable
 *
 * Return: a pointer to a new string with
 * filled in directories, or NULL on failure
 */
char *fill_path_dir(char *path)
{
	/* Declare variables */
	int idx = 0, new_len = 0;
	char *path_copy, *pwd;

	/* Get the PWD environment variable */
	pwd = *(_getenv("PWD")) + 4;

	/* Calculate the length of the new string */
	while (path[idx])
	{
		if (path[idx] == ':')
		{
			if (path[idx + 1] == ':' || idx == 0 || path[idx + 1] == '\0')
				new_len += _strlen(pwd) + 1;
			else
				new_len++;
		}
		else
			new_len++;
		idx++;
	}

	/* Allocate memory for the new string */
	path_copy = malloc(sizeof(char) * (new_len + 1));
	if (!path_copy)
		return (NULL);

	/* Build the new string */
	idx = 0;
	path_copy[0] = '\0';
	while (path[idx])
	{
		if (path[idx] == ':')
		{
			if (idx == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[idx + 1] == ':' || path[idx + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			 _strncat(path_copy, &path[idx], 1);
		}
		idx++;
	}

	/* Return the new string */
	return (path_copy);
}
/**
* get_path_dir - creates a linked list of directories in the PATH variable
* @path: the PATH environment variable
*
* Return: a pointer to a new list_t struct, or NULL on failure
*/
list_t *get_path_dir(char *path)
{
	/* Declare variables */
	int index = 0;
	char **dirs = NULL, *path_copy = NULL;
	list_t *head = NULL;

	/* Fill in any empty directories in the PATH variable */
	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);

	/* Split the PATH variable into an array of directories */
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	/* Add each directory to the linked list */
	while (dirs[index]
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			/* If adding a node fails, free the list and return NULL */
			free_list(head);
			free(dirs);
			return (NULL);
		}
		index++;
	}

	free(dirs);

	/* Return the linked list */
	return (head);
}


