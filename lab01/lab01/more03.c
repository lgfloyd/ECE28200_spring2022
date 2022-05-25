/*  more03.c  - version 0.3 of more
 *	read and print 24 lines then pause for a few special commands
 *      feature of version 0.3: reads from /dev/tty for commands
 */
#include <stdio.h>
#include <stdlib.h>

#define	PAGELEN	24
#define	LINELEN	512

void do_more(FILE *);
int see_more(FILE *);
void readFile();
void writeFile();

int main(int ac, char *av[])
{
	FILE *fp;
	
	readFile();
	writeFile();

	if (ac == 1)
		do_more(stdin);
	else
		while (--ac)
			if ((fp = fopen(*++av ,"r")) != NULL)
			{
				do_more(fp) ; 
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}

void do_more(FILE *fp)
/*
 *  read PAGELEN lines, then call see_more() for further instructions
 */
{
	char line[LINELEN];
	int num_of_lines = 0;
	int see_more(FILE *), reply;
	FILE *fp_tty;

	fp_tty = fopen("/dev/tty", "r");	   /* NEW: cmd stream   */
	if (fp_tty == NULL)			   /* if open fails     */
		exit(1);                           /* no use in running */

	while (fgets(line, LINELEN, fp)){		/* more input	*/
		if (num_of_lines == PAGELEN) {	/* full screen?	*/
			reply = see_more(fp_tty);  /* NEW: pass FILE *  */
			if (reply == 0)		/*    n: done   */
				break;
			num_of_lines -= reply;		/* reset count	*/
		}
		if (fputs(line, stdout) == EOF)	/* show line	*/
			exit(1);			/* or die	*/
		num_of_lines++;				/* count it	*/
	}
}

int see_more(FILE *cmd)				   /* NEW: accepts arg  */
/*
 *	print message, wait for response, return # of lines to advance
 *	q means no, space means yes, CR means one line
 */
{
	int c;

	printf("\033[7m more? \033[m");		/* reverse on a vt100	*/
	while((c=getc(cmd)) != EOF)		/* NEW: reads from tty  */
	{
		if (c == 'q')			/* q -> N		*/
			return 0;
		if (c == ' ')			/* ' ' => next page	*/
			return PAGELEN;		/* how many to show	*/
		if (c == '\n')		/* Enter key => 1 line	*/
			return 1;		
	}
	return 0;
}

void readFile()
{
   FILE *pFile;
   char mystring [256];

   pFile = fopen ("longfile" , "r");
   if (pFile == NULL) perror ("Error opening file");
   else {
     if (fgets (mystring, 256, pFile) != NULL)  // IF data is read from the input stream (pFile), THEN
       puts (mystring);  // print the characters read to the standard output
     fclose (pFile);
   }
}

void writeFile()
{
   FILE *pFile;
   char sentence [256];

   printf ("Enter sentence to append: ");
   fgets (sentence,256,stdin); // Read 256 characters from the given input stream (stdin), and store it in the buffer (sentence)
   pFile = fopen ("out.txt","a"); // Open a file in append mode. The cursor will be placed at the end of the file.
   fputs (sentence,pFile); // Write the contents of the buffer (sentence) into the file
   fclose (pFile);
}
