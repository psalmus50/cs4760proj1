//Nicholas Kalinowski
//UMSL CS 4760
//Dr. Sanjiv Bhatia
//Project 1
//September 12 2023

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>

char usage_string[] = "Usage: reverse [-h] [-i inputfilename] [-o outputfilename]\n";

// child code
static void processOneItem(FILE* fileHandle, FILE* outFileHandle, int rowArg)
{

	int numberOfNumbers;

	fscanf(fileHandle, "%d", &numberOfNumbers);
	int reversedRow [numberOfNumbers];

	for(int i=1; i<(numberOfNumbers+1); i++)
	{
		int particularNumber;
		fscanf(fileHandle, "%d", &particularNumber);
		reversedRow[numberOfNumbers-i] = particularNumber;
	}

	fprintf(outFileHandle, "%d: ", getpid());
	for(int i=0; i<numberOfNumbers; i++)
	{
		fprintf(outFileHandle, "%d ", reversedRow[i]);
		printf("%d", reversedRow[i]);
	}
	fprintf(outFileHandle, "\n");
	fclose(fileHandle);
	fclose(outFileHandle);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {

	int opt;
	char input_filename[100] = "input.dat";
	char output_filename[100] = "output.dat";
	FILE* outputFileHandle;
	FILE* inputFileHandle;

	//argument processing

	while((opt = getopt(argc, argv, "hi:o:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("%s", usage_string);
				break;
			case 'i':
			//check if file exists
				strcpy(input_filename, optarg);	
				break;
			case 'o':
				strcpy(output_filename, optarg);
				break;
		}

	}

	// always make sure of input file

	inputFileHandle = fopen(input_filename, "r");
        if (inputFileHandle == NULL) {
		perror("reverse: Error: enter a valid file name.");
		return EXIT_FAILURE;
	}

	outputFileHandle = fopen(output_filename, "w");
	if (outputFileHandle == NULL) {
		perror("reverse: Error: enter a valid file name.");
		return EXIT_FAILURE;
	}	

	int numberOfSets = 0;
	fscanf(inputFileHandle, "%d", &numberOfSets);
//	printf("%d", numberOfSets);i
	

	for (int i=0; i<numberOfSets; i++)
	{
		int stat = 0;
		pid_t childPid = fork();
		if(childPid == 0)
		{
			printf("%s", "Calling process one item\n");
			processOneItem(inputFileHandle, outputFileHandle, i);
			exit(EXIT_SUCCESS);		
		}
		else
		{
			printf("%s", "Calling wait\n");
			childPid = wait(&stat);
			printf("parent PID %d", getpid());
		}
	}	
	return 0;
}
