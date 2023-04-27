#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env -prints information on the shell  command environment.
 */
void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv - prints information on the shell command set_environment.
 */
void help_setenv(void)
{
        const char *msg = "setenv: setenv [VARIABLE] [VALUE]\n"
                          "\tInitializes a new environment variable, or modifies an existing one.\n\n"
                          "\tUpon failure, prints a message to stderr.\n";

        write(STDOUT_FILENO, msg, _strlen(msg));
}
/**
 * help_unsetenv - print information on the shell command
 * unset_environment.
*/
void help_unsetenv(void)
{
        const char *msg = "unsetenv: unsetenv [VARIABLE]\n"
                          "\tRemoves an environmental variable.\n\n"
                          "\tUpon failure, prints a message to stderr.\n";

        write(STDOUT_FILENO, msg, _strlen(msg));
}
