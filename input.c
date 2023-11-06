#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_LENGTH 1024
/**
 * takeInput - take user input
 * @userInput: user input
 *
 * Return: Always 0
 */
int takeInput(char *userInput)
{
	char inputBuffer[MAX_INPUT_LENGTH];

	printf("\n$ ");

	if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
	{
		/*
		 * Handle the "end of file" condition (Ctrl+D)
		 */
		printf("\nexit\n");
		exit(EXIT_SUCCESS);
	}

	/*
	 * Remove the newline character from the input
	 */
	inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

	if (strlen(inputBuffer) != 0)
	{
		strcpy(userInput, inputBuffer);
		return (0);
	}
	else
	{
		return (1);
	}
}