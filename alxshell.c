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
 * @argc: argc
 * @argv[]: argv
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char inputCommand[LETLMT], *parsedCommands[CMDLMT];
	char *parsedCommandsPiped[CMDLMT];
	int commandType = 0;

	FILE *inputFile = stdin; /* Use stdin by default for interactive mode */

	if (argc > 1 && strcmp(argv[1], "-i") != 0)
	{
	/*
	 * Non-interactive mode: open the file specified as an argument
	 */
		inputFile = fopen(argv[1], "r+");
		if (inputFile == NULL)
		{
			perror("fopen");
			return (1);
		}
	}

	while (1)
	{
		/*
		 * printf("$ ");
		 */

		if (isatty(fileno(inputFile)))
		{
			printf("$ ");
		}

		if (takeInput(inputCommand, inputFile))
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
			executeCommand(parsedCommands, argv[0]);

		if (commandType == 2)
			executePipedCommands(parsedCommands, parsedCommandsPiped);
	}

	if (inputFile != stdin)
	{
		fclose(inputFile); /* Close the file in non-interactive mode */
	}

	return (0);

}
