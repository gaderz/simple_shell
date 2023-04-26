#include "shell.h"

/**
 * _realloc - Reallocates the memory block using malloc and free.
 * @ptr_in: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr_in.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr_in.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr_in, unsigned int old_size, unsigned int new_size)
{
	void *ptr_out;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr_in);

	if (ptr_in == NULL)
	{
		ptr_out = malloc(new_size);
		if (ptr_out == NULL)
			return (NULL);

		return (ptr_out);
	}

	if (new_size == 0 && ptr_in != NULL)
	{
		free(ptr_in);
		return (NULL);
	}

	ptr_copy = ptr_in;
	ptr_out = malloc(sizeof(*ptr_copy) * new_size);
	if (ptr_out == NULL)
	{
		free(ptr_in);
		return (NULL);
	}

	filler = ptr_out;
	while (index < old_size && index < new_size)
	{
		filler[index] = *ptr_copy++;
		index++;
	}
	free(ptr_in);
	return (ptr_out);
}
/**
 * assign_lineptr - function that Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL || *n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		size_t i = 0;

		while (i < b)
		{
			(*lineptr)[i] = buffer[i];
			i++;
		}
		free(buffer);
	}
}
/**
 * _getline - Reads input from a function stream.
 * @lineptr: A buffer to store the input taken
 * @n: The size of lineptr.
 * @stream: The stream to read from in the env
 *
 * Return: The number of bytes read in input
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	do {
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	} while (c != '\n');

	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
