/* spwd.c: a simplified version of pwd
 *
 *	starts in current directory and recursively
 *	climbs up to root of filesystem, prints top part
 *	then prints current part
 *
 *	uses readdir() to get info about each thing
 *
 *      bug: prints an empty string if run from "/"
 **/
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<dirent.h>
#include	<stdlib.h>
#include	<string.h>
//Added #include	<stdlib.h> and #include    <string.h>

ino_t	get_inode(char *);
void    printpathto(ino_t, int *);
//Modified void    printpathto(ino_t); to void    printpathto(ino_t, int *);
void    inum_to_name(ino_t , char *, int );

int main()
{
	int x = 0;

	printpathto( get_inode( "." ), &x );	/* print path to here	*/
	//printpathto now includes &x
	putchar('\n');				/* then add newline	*/
	return 0;
}

void printpathto( ino_t this_inode, int *x )
/*
 *	prints path leading down to an object with this inode
 *	kindof recursive
 */
{
	ino_t	my_inode ;
	char	its_name[BUFSIZ];

	if ( get_inode("..") != this_inode )
	{
		chdir( ".." );				/* up one dir	*/

		inum_to_name(this_inode,its_name,BUFSIZ);/* get its name*/

		my_inode = get_inode( "." );		/* print head	*/

		while (*x <= 1)
		{
			*x = *x + 1;
			printpathto(my_inode, x);		/* recursively	*/
			//printpathto now passes both my_inode and x
		}
		printf("/%s", its_name);		/* now print	*/
								/* name of this	*/
	}
}

void inum_to_name(ino_t inode_to_find , char *namebuf, int buflen)
/*
 *	looks through current directory for a file with this inode
 *	number and copies its name into namebuf
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */

	dir_ptr = opendir( "." );
	if ( dir_ptr == NULL ){
		perror( "." );
		exit(1);
	}

	/*
	 * search directory for a file with specified inum
	 */

	while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		if ( direntp->d_ino == inode_to_find )
		{
			strncpy( namebuf, direntp->d_name, buflen);
			namebuf[buflen-1] = '\0';   /* just in case */
			closedir( dir_ptr );
			return;
		}
	fprintf(stderr, "error looking for inum %d\n", inode_to_find);
	exit(1);
}

ino_t get_inode( char *fname )
/*
 *	returns inode number of the file
 */
{
	struct stat info;

	if ( stat( fname , &info ) == -1 ){
		fprintf(stderr, "Cannot stat ");
		perror(fname);
		exit(1);
	}
	return info.st_ino;
}
