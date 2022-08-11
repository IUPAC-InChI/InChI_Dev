#pragma warning( disable : 4996 )

#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

#include <time.h>

#include "fireader.h"
#include "min_io.h"




/* 
	Demo
*/




void print_help(void)
{
    fprintf( stderr, "Usage: \n");
    fprintf( stderr, "fireader file\n");
    /* TODO: list available options */
#if 0
	fprintf( stderr, "Options:\n");
    fprintf( stderr, "\tSTART:n - start from SDF record n\n");
    fprintf( stderr, "\tEND:n   - end when reached SDF record n\n");
	fprintf( stderr, "\tRECORD:n   - process only SDF record n\n");
    fprintf( stderr, "\tNOINCHI - do not print InChI itself\n");
    fprintf( stderr, "\tKEY     - calc and print InChIKey\n");
    fprintf( stderr, "\tBENCHMARK - collect timing\n");
    fprintf( stderr, "\tNSHUFFLE:n - reorder atoms n times and repeat\n");
    fprintf( stderr, "\tTSHUFFLE:t - do not repeat runs of t sec or longer\n");
    fprintf( stderr, "\tVERBOSE:n  - > 0 means more output\n");
    fprintf( stderr, "\t[common InChI API options]\n");
#endif
}


void print_time(void)
{
time_t tt;
char st[36]="";
    tt = time(&tt); 
    strncat(st,(char *) ctime(&tt), 32);
    fprintf( stderr, "%-s",st);
}


/*******************************************************************************/
int main(int argc, char *argv[])
{
int retcode=0, result=0, nerrs=0, k;
char *fname=NULL;	
FILE *f=NULL;
char *text=NULL; 
char *out=NULL, *log=NULL;

time_t begin; 

#if defined(_WIN32)
const char *platform="Windows";
#else
const char *platform="Linux";
#endif

    char banner[255];

	
	INCHI_IOSTREAM_STRING temp_string_container;
    INCHI_IOSTREAM_STRING *strbuf = &temp_string_container;
    memset( strbuf, 0, sizeof(strbuf) );
	
	
	sprintf( banner, "%s\n%-s Build of %-s %-s%s\n",          
              APP_DESCRIPTION,
              platform, __DATE__, __TIME__,
              RELEASE_IS_FINAL?"":" *** pre-release, for evaluation only ***"); 

    /*	Parse command line. Assume that the first item 
		is input filename, all the others are switches						
	*/

    fprintf( stderr, "%-s\n", banner);
    if ( argc < 2 )
    {
        print_help();
        retcode = 1;
        goto finish;
    }

    fname = argv[1];
    f = fopen(fname,"rb");
    if ( !f )
    {
        retcode = 2;
        goto finish;
    }

	fprintf( stderr, "Started at ");
    ctime(&begin);
    print_time();
	fprintf( stderr, "by the following command line:\n\"");
	for(k=0; k<argc-1; k++)
        fprintf( stderr, "%-s ",argv[k]);
	fprintf( stderr, "%-s\"\n", argv[argc-1]);

	if ( 0 >= inchi_strbuf_init( strbuf, INCHI_STRBUF_INITIAL_SIZE, INCHI_STRBUF_SIZE_INCREMENT ) )
    {
        fprintf( stderr, "No RAM!\n" );
        goto finish;
    }
	else
	{
		int crlf2lf = 1, preserve_lf = 0;
		while ( inchi_strbuf_getline( strbuf, f, crlf2lf, preserve_lf ) != EOF )
		{
			fprintf( stdout, "%s\n", strbuf->pStr );
		}
	}

finish:

	inchi_strbuf_close( strbuf );
	
	if ( f )
		fclose( f );
	return 0;
}


