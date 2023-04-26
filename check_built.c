#include "shell.h"


/**
 * help_all - Displays all possible builtin shellby commands.
 */
void help_all(void)
{
	char *msg1 = "Shellby\nThese shell commands are defined internally.\n";
	char *msg2 = "Type 'help' to see this list.\nType 'help name' to find ";
	char *msg3 = "out more about the function 'name'.\n\n";
	char *msg4 = "  alias   \talias [NAME[='VALUE'] ...]\n";
	char *msg5 = "  cd      \tcd [DIRECTORY]\n";
	char *msg6 = "  exit    \texit [STATUS]\n";
	char *msg7 = "  env     \tenv\n";
	char *msg8 = "  setenv  \tsetenv [VARIABLE] [VALUE]\n";
	char *msg9 = "  unsetenv\tunsetenv [VARIABLE]\n";

	write(STDOUT_FILENO, msg1, _strlen(msg1));
	write(STDOUT_FILENO, msg2, _strlen(msg2));
	write(STDOUT_FILENO, msg3, _strlen(msg3));
	write(STDOUT_FILENO, msg4, _strlen(msg4));
	write(STDOUT_FILENO, msg5, _strlen(msg5));
	write(STDOUT_FILENO, msg6, _strlen(msg6));
	write(STDOUT_FILENO, msg7, _strlen(msg7));
	write(STDOUT_FILENO, msg8, _strlen(msg8));
	write(STDOUT_FILENO, msg9, _strlen(msg9));
}
/**
 * help_alias - print information on the shell builtin command 'alias'.
 */
void help_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));

	msg = "\nPrints a list of all aliases, one per line, in the format NAME='VALUE':\n\talias\n";
	write(STDOUT_FILENO, msg, _strlen(msg));

	msg = "Prints the aliases name, name2, etc. one per line, in the form NAME='VALUE':\n\talias name [name2 ...]\n";
	write(STDOUT_FILENO, msg, _strlen(msg));

	msg = "Defines an alias for each NAME whose VALUE is given. If NAME is already an alias, replace its value with VALUE:\n\talias NAME='VALUE' [...]\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
/**
 * help_cd - Prints help information for the cd command
 */
void help_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the "
		"process to DIRECTORY.\n\n\tIf no argument is given, the "
		"command is interpreted as cd $HOME. If the argument '-' is "
		"given, the command is interpreted as cd $OLDPWD.\n\n\t"
		"The environment variables PWD and OLDPWD are updated "
		"after a change of directory.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_exit - print information on the shell builtin command 'exit'.
 */
void help_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_help - print information on the shell builtin command 'help'.
 */
void help_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
