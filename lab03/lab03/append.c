#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int twoArguments, char* fileContents[])
{
	if (twoArguments != 3)
	{
		if (twoArguments == 2 && !strcmp(fileContents[1], "--help"))\
		{
			printf("./append <destination file> <source file>\n");
			printf("Appends the contents of the source file to the destination file.\n");
		}

		else
		{
			printf("Error! ./append --help for instructions.\n");
		}
	}

	else
	{
		FILE* destinationFile = fopen(fileContents[1], "a");
		FILE* sourceFile = fopen(fileContents[2], "r");
		
		char chAppend;

		if (sourceFile == NULL)
		{
			printf("File %s does not exist.\n", fileContents[2]);

			fclose(destinationFile);

			exit(-1);
		}

		while ((chAppend = fgetc(sourceFile)) != EOF)
		{
			fputc(chAppend, destinationFile);
		}

		printf("Append completed successfully!\n");

		fclose(destinationFile);
		fclose(sourceFile);
	}

	return 0;
}
