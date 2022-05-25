#include <stdio.h>
#include <stdlib.h> // for exit() function
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;

    if (argc < 2) 
    {
        printf("Usage: %s <directory>\n", argv[0]);
        printf("The directory might exist or not.\n");
        exit(1);
    }

    fd = chdir(argv[1]); // changes the directory, argv[1] will contain a path to the directory
    // printf will output user's formatted string, while perror will output
    // the system error msg corresponding to errno
    if (fd != 0) 
    {
        printf("Changing to directory: \"%s\" failed.\n", argv[1]);
        perror(argv[1]);
    }

    else 
    {
        printf("Changing to directory: \"%s\" was successful.\n", argv[1]);
    }

    return 0;
}
