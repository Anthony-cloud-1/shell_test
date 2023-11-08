#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * handleInternalCommands - handle internal shell cmds
 * @parsedInput: parsed input
 *
 * Return: Always 0
 */
int handleInternalCommands(char **parsedInput)
{
	int  i, commandMatch = 0;
	char *internalCommands[4];

	internalCommands[0] = "exit";
	internalCommands[1] = "cd";
	internalCommands[2] = "help";

	for (i = 0; i < 3; i++)
	{
		if (strcmp(parsedInput[0], internalCommands[i]) == 0)
		{
			commandMatch = i + 1;
			break;
		}
	}

	switch (commandMatch)
	{
		case 1:
			/*
			 *printf("exit\n");
			exit(0);
			*/
			if (parsedInput[1] != NULL)
			{
				int exitStatus = atoi(parsedInput[1]);
				exit(exitStatus);
			} 
			else
			{
				exit(0);  /* Exit with a default status of 0 */
			}

		case 2:
			chdir(parsedInput[1]);
			return (1);
		case 3:
			shellHelp();
			return (1);
		default:
			break;
	}

	return (0);
}
