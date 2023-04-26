#include "shell.h"


/**
 * add_alias_end - Adds a new alias node at the end of a linked list of aliases
 * @head: A pointer to the head of the linked list
 * @name: The name of the alias
 * @value: The value of the alias
 *
 * Return: A pointer to the newly created alias node
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_alias_node = malloc(sizeof(alias_t));
	alias_t *node;

	if (!new_alias_node)
		return (NULL);

	new_alias_node->next = NULL;
	new_alias_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_alias_node->name)
	{
		free(new_alias_node);
		return (NULL);
	}
	new_alias_node->value = value;
	_strcpy(new_alias_node->name, name);

	if (*head)
	{
		for (node = *head; node->next != NULL; node = node->next)
		{}
		node->next = new_alias_node;
	}
	else
		*head = new_alias_node;

	return (new_alias_node);
}

/**
 * add_node_end - Adds a new node at the end of a linked list
 * @head: A pointer to the head of the linked list
 * @dir: The directory to add to the linked list
 *
 * Return: A pointer to the newly created node
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last_node;

	if (!new_node)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last_node = *head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}
/**
 * free_alias_list - Frees a linked list of aliases
 * @head: A pointer to the head of the linked list
 */
void free_alias_list(alias_t *head)
{
	alias_t *current;
	alias_t *temp;

	for (current = head; current; current = current->next)
	{
		temp = current;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
/**
 * free_list - Frees a linked list of directories
 * @head: A pointer to the head of the linked list
 */
void free_list(list_t *head)
{
	list_t *next_node;

	for (; head; head = next_node)
	{
		next_node = head->next;
		free(head->dir);
		free(head);
	}
}
