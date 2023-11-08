#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "shell.h"

#define LETLMT 1000 /* max number of letters to be supported */
/**
 * splitBySpace - splits commands by space
 * @input: user input
 * @parsedTokens: parsed tokens
 *
 * Return: void
 */
void splitBySpace(char *input, char **parsedTokens)
{

	int i;

	for (i = 0; i < LETLMT; i++)
	{
		parsedTokens[i] = strsep(&input, " ");

		if (parsedTokens[i] == NULL)
			break;
		if (strlen(parsedTokens[i]) == 0)
			i--;
	}

}
