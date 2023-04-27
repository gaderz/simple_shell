#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - Prints error message when unable to open a file
 * @file_path: The path of the file that could not be opened
 *
 * Return: Always returns 127
 */
int cant_open(char *file_path)
{
        char *err_msg, *hist_str;
        int err_len;

        hist_str = _itoa(hist);
        if (!hist_str)
                return (127);

        err_len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
        err_msg = malloc(sizeof(char) * (err_len + 1));
        if (!err_msg)
        {
                free(hist_str);
                return (127);
        }

        _strcpy(err_msg, name);
        _strcat(err_msg, ": ");
        _strcat(err_msg, hist_str);
        _strcat(err_msg, ": Can't open ");
        _strcat(err_msg, file_path);
        _strcat(err_msg, "\n");

        free(hist_str);
        write(STDERR_FILENO, err_msg, err_len);
        free(err_msg);
        return (127);
}
/**
 * proc_file_commands - Executes commands from a file
 *
 * @file_path: path to the file
 * @exe_ret: exit status to return
 *
 * Return: exit status
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
    ssize_t fd, bytes_read, i;
    unsigned int line_size = 0;
    unsigned int max_size = 120;
    char *line, **args, **front;
    char buffer[120];
    int exit_status;

    hist = 0;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        *exe_ret = cant_open(file_path);
        return (*exe_ret);
    }

    line = malloc(sizeof(char) * max_size);
    if (!line)
        return (-1);

    bytes_read = read(fd, buffer, 119);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        line_size += bytes_read;
        line = _realloc(line, max_size, line_size);
        _strcat(line, buffer);
        max_size = line_size;
        bytes_read = read(fd, buffer, 119);
    }

    i = 0;
    while (line[i] == '\n')
    {
        line[i] = ' ';
        i++;
    }

    i = 0;
    while (i < line_size)
    {
        if (line[i] == '\n')
        {
            line[i] = ';';
            i++;
            while (i < line_size && line[i] == '\n')
            {
                line[i] = ' ';
                i++;
            }
        }
        else
            i++;
    }

    variable_replacement(&line, exe_ret);
    handle_line(&line, line_size);
    args = _strtok(line, " ");
    free(line);

    if (!args)
        return (0);

    if (check_args(args) != 0)
    {
        *exe_ret = 2;
        free_args(args, args);
        return (*exe_ret);
    }

    front = args;

    i = 0;
    while (args[i])
    {
        if (_strncmp(args[i], ";", 1) == 0)
        {
            free(args[i]);
            args[i] = NULL;
            exit_status = call_args(args, front, exe_ret);
            args = &args[++i];
            i = 0;
        }
        else
            i++;
    }

    exit_status = call_args(args, front, exe_ret);

    free(front);
    return (exit_status);
}
