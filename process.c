#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define CMDLMT 100 /* max commands */
/**
 * processInput - processes user input
 * @input: user input
 * @parsed: parsed input
 * @parsedPipe: parsed pipe
 *
 * Return: Always 0
 */
int processInput(char *input, char **parsed, char **parsedPipe)
{
	char *pipedCommands[2];
	int hasPipe = 0;

	hasPipe = findPipe(input, pipedCommands);

	if (hasPipe)
	{
		splitBySpace(pipedCommands[0], parsed);
		splitBySpace(pipedCommands[1], parsedPipe);
	}
	else
	{
		splitBySpace(input, parsed);
	}

	if (handleInternalCommands(parsed))
		return (0);
	else
		return (1 + hasPipe);
}
