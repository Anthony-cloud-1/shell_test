#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define LETLMT 1000 /* max letters */
#define CMDLMT 100 /* max commands */
/**
 * main - Simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char inputCommand[LETLMT], *parsedCommands[CMDLMT];
	char *parsedCommandsPiped[CMDLMT];
	int commandType = 0;

	while (1)
	{
		printf("$ ");

		if (takeInput(inputCommand))
			break;
		 /*
		 *  Process the input
		 */

		commandType = processInput(inputCommand, parsedCommands, parsedCommandsPiped);
		 /*
		 * commandType returns zero if there is no command
		 * or it is a built-in command,
		 * 1 if it is a simple command
		 * 2 if it is a command with a pipe.
		 */

		if (commandType == 1)
			executeCommand(parsedCommands);

		if (commandType == 2)
			executePipedCommands(parsedCommands, parsedCommandsPiped);
	}
	return (0);

}
