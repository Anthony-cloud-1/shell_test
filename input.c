#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define MAX_INPUT_LENGTH 1024
/**
 * takeInput - take user input
 * @userInput: user input
 * @inputFile: input file
 * Return: Always 0
 */
int takeInput(char *userInput, FILE *inputFile)
{
	char inputBuffer[MAX_INPUT_LENGTH];

	/*
	printf("$ ");
	*/

	if (fgets(inputBuffer, sizeof(inputBuffer), inputFile) == NULL)
	{
		/*
		* Handle the "end of file" condition (Ctrl+D)
		*
		printf("exit\n");
		
		exit(EXIT_SUCCESS);
		*/
		return (1);
	}

	if (inputBuffer[0] == '#')
	{
	/*Skip/commented line
	 */
		return(1);
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
