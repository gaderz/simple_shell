#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - returns the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
    /* Declare variables */
    int len = 0;

    /* Handle edge case of NULL string */
    if (!s)
        return (len);

    /* Iterate through the string and count its characters */
    while (s[len] != '\0')
        len++;

    /* Return the length of the string */
    return (len);
}
/**
 * _strcpy - copies a string to a buffer
 * @dest: pointer to the buffer to copy the string into
 * @src: pointer to the string to copy
 *
 * Return: pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
    /* Declare variables */
    size_t j = 0;

    /* Copy each character of the source string to the destination buffer */
    while (src[j] != '\0')
    {
        dest[j] = src[j];
        j++;
    }

    /* Append null terminator to the destination buffer */
    dest[j] = '\0';

    /* Return a pointer to the destination buffer */
    return dest;
}

/**
 * _strcat - concatenates two strings
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 *
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, const char *src)
{
    /* Declare variables */
    char *dest_ptr = dest;
    const char *src_ptr = src;

    /* Move dest_ptr to the end of the destination string */
    while (*dest_ptr)
        dest_ptr++;

    /* Append the source string to the destination string */
    for (; *src_ptr; dest_ptr++, src_ptr++)
        *dest_ptr = *src_ptr;

    /* Add a null terminator to the end of the resulting string */
    *dest_ptr = '\0';

    /* Return a pointer to the resulting string */
    return dest;
}
/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
/**
 * _strncat - appends a string of at most n characters to a buffer
 * @dest: pointer to the buffer to append the string to
 * @src: pointer to the string to append
 * @n: maximum number of characters to append
 *
 * Return: pointer to the destination buffer
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    /* Declare variables */
    size_t dest_length = _strlen(dest);
    size_t index = 0;

    /* Append each character of the source string to the destination buffer
       until n characters have been copied or the end of the source string
       is reached */
    while (index < n && src[index] != '\0')
    {
        dest[dest_length + index] = src[index];
        index++;
    }

    /* Append null terminator to the end of the destination buffer */
    dest[dest_length + index] = '\0';

    /* Return a pointer to the destination buffer */
    return dest;
}
