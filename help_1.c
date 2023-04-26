#include "shell.h"


/**
 * handle_line - read line from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char prev_char, curr_char, next_char;
	size_t i = 0, j = 0;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;

	new_line = malloc(new_len + 1);
	if (!new_line)
		return;

	old_line = *line;
	while (old_line[i] != '\0')
	{
		curr_char = old_line[i];
		next_char = old_line[i + 1];
		if (i != 0)
		{
			prev_char = old_line[i - 1];

			if (curr_char == ';')
			{
				if (next_char == ';' && prev_char != ' ' && prev_char != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					i++;
					continue;
				}
				else if (prev_char == ';' && next_char != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					i++;
					continue;
				}

				if (prev_char != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';

				if (next_char != ' ')
					new_line[j++] = ' ';
				i++;
				continue;
			}
			else if (curr_char == '&')
			{
				if (next_char == '&' && prev_char != ' ')
				{
					new_line[j++] = ' ';
					i++;
					continue;
				}
				else if (prev_char == '&' && next_char != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					i++;
					continue;
				}
			}
			else if (curr_char == '|')
			{
				if (next_char == '|' && prev_char != ' ')
				{
					new_line[j++] = ' ';
					i++;
					continue;
				}
				else if (prev_char == '|' && next_char != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					i++;
					continue;
				}
			}
		}
		else if (curr_char == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next_char != ' ' && next_char != ';')
				new_line[j++] = ' ';
			i++;
			continue;
		}

		new_line[j++] = old_line[i++];
	}

	new_line[j] = '\0';

	free(*line);
	*line = new_line;
}
/**
 * get_new_len - Computes the new length of a given line after parsing.
 * @line: The input line to compute the new length for.
 *Return: The new length of the input line after parsing.
 */
ssize_t get_new_len(char *line)
{
	size_t index = 0;
	ssize_t new_length = 0;
	char current_char, next_char;

	while (line[index])
	{
		current_char = line[index];
		next_char = line[index + 1];

		if (current_char == '#')
		{
			if (index == 0 || line[index - 1] == ' ')
			{
				line[index] = '\0';
				break;
			}
		}
		else if (index != 0)
		{
			if (current_char == ';')
			{
				if (next_char == ';' && line[index - 1] != ' ' && line[index - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[index - 1] == ';' && next_char != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[index - 1] != ' ')
					new_length++;
				if (next_char != ' ')
					new_length++;
			}
			else
				logical_ops(&line[index], &new_length);
		}
		else if (current_char == ';')
		{
			if (index != 0 && line[index - 1] != ' ')
				new_length++;
			if (next_char != ' ' && next_char != ';')
				new_length++;
		}
		new_length++;
		index++;
	}
	return (new_length);
}
/**
 * logical_ops - count the length of logical operations in a line
 * @line: pointer to the current line
 * @new_len: pointer to the length of the new line
 *
 * Return: void
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev_char, current_char, next_char;

	prev_char = *(line - 1);
	current_char = *line;
	next_char = *(line + 1);

	if (current_char == '&')
	{
		if (next_char == '&' && prev_char != ' ')
			(*new_len)++;
		else if (prev_char == '&' && next_char != ' ')
			(*new_len)++;
	}
	else if (current_char == '|')
	{
		if (next_char == '|' && prev_char != ' ')
			(*new_len)++;
		else if (prev_char == '|' && next_char != ' ')
			(*new_len)++;
	}
}
