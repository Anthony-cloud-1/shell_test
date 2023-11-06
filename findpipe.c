#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 *findPipe - findpipe
 * @input: input str
 * @pipedCommands: piped cmds
 *
 * Return: Always 0
 */
int findPipe(char *input, char **pipedCommands)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		pipedCommands[i] = strsep(&input, "|");
		if (pipedCommands[i] == NULL)
			break;
	}

	if (pipedCommands[1] == NULL)
		return (0);
	else
	{
		return (1);
	}
}
