/*
 * 
 */


#ifndef _MIN_IO_H_
#define _MIN_IO_H_




/* 
	Rosetta 
*/


struct line_reader 
{
	/* All members are private. */
	FILE	*f;
	char	*buf;
	size_t	 siz;
};

char *next_line(struct line_reader *lr, size_t *len);




/* InChI */



#define INCHI_STRBUF_INITIAL_SIZE 4000
#define INCHI_STRBUF_SIZE_INCREMENT 4000

typedef struct tagOutputString 
{
    char *pStr;
    int  nAllocatedLength;
    int  nUsedLength;
    int  nPtr;	/* if the struct is used as expanding string buffer, 
                   this field will store an expansion increment */
} INCHI_IOSTREAM_STRING;

typedef struct tagOutputStream 
{
    /* output is directed either to resizable string buffer: */
    INCHI_IOSTREAM_STRING s;
    /* or to the plain file: */
    FILE* f;
    int type;
} INCHI_IOSTREAM;

/* INCHI_IOSTREAM.type values */
#define INCHI_IOSTREAM_TYPE_NONE 0
#define INCHI_IOSTREAM_TYPE_STRING 1
#define INCHI_IOSTREAM_TYPE_FILE 2

#define inchi_calloc calloc
#define inchi_free free


#define inchi_max(a,b)  (((a)>(b))?(a):(b))
#define inchi_min(a,b)  (((a)<(b))?(a):(b))

#if ( defined(__GNUC__) && defined(__MINGW32__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ == 0 && defined(_WIN32) ) 

#define my_va_start(A,B) ((A)=(va_list)__builtin_next_arg(lpszFormat))
#else
#define my_va_start va_start
#endif


int GetMaxPrintfLength( const char *lpszFormat, va_list argList);
int inchi_strbuf_init( INCHI_IOSTREAM_STRING *buf, 
                       int start_size, 
                       int incr_size );
void inchi_strbuf_close( INCHI_IOSTREAM_STRING *buf );
void inchi_strbuf_reset( INCHI_IOSTREAM_STRING *buf );
int inchi_strbuf_getline(INCHI_IOSTREAM_STRING *buf, FILE *f, int crlf2lf, int preserve_lf );


#endif _MIN_IO_H_
