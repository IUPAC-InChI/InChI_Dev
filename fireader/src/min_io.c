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

#include "min_io.h"








/* 
	Rosetta 
*/


char *next_line(struct line_reader *lr, size_t *len)
{
	size_t newsiz;
	int c;
	char *newbuf;
 
	*len = 0;			/* Start with empty line. */
	for (;;) {
		c = fgetc(lr->f);	/* Read next character. */
		if (ferror(lr->f))
			return NULL;
 
		if (c == EOF) {
			/*
			 * End of file is also end of last line,
		`	 * unless this last line would be empty.
			 */
			if (*len == 0)
				return NULL;
			else
				return lr->buf;
		} else {
			/* Append c to the buffer. */
			if (*len == lr->siz) {
				/* Need a bigger buffer! */
				newsiz = lr->siz + 4096;
				newbuf = realloc(lr->buf, newsiz);
				if (newbuf == NULL)
					return NULL;
				lr->buf = newbuf;
				lr->siz = newsiz;
			}
			lr->buf[(*len)++] = c;
 
			/* '\n' is end of line. */
			if (c == '\n')
				return lr->buf;
		}
	}
}




/* InChI */


/*	Init expandable buffer of type INCHI_IOSTREAM_STRING */
int inchi_strbuf_init( INCHI_IOSTREAM_STRING *buf, 
                       int start_size, 
                       int incr_size )
{ 
char *new_str=NULL; 
    memset( buf, 0, sizeof(*buf) );

    if ( start_size <= 0 )	start_size = INCHI_STRBUF_INITIAL_SIZE;
    if ( incr_size  <= 0 )	incr_size  = INCHI_STRBUF_SIZE_INCREMENT;

    new_str = (char *) inchi_calloc( start_size, sizeof(new_str[0]) );
    
    if ( !new_str )	return -1;
    
    buf->pStr = new_str;
    buf->nAllocatedLength = start_size;
    buf->nPtr = incr_size;
    
    return start_size;
}


int inchi_strbuf_create_copy( INCHI_IOSTREAM_STRING *buf2, INCHI_IOSTREAM_STRING *buf )
{ 
char *new_str=NULL; 

    new_str = (char *) inchi_calloc( buf->nAllocatedLength, sizeof(new_str[0]) );	

    buf2->pStr = new_str;
    if ( !new_str )	return -1;
    
    buf2->nAllocatedLength = buf->nAllocatedLength; 
    buf2->nUsedLength = buf->nUsedLength;
    buf2->nPtr = buf->nPtr;
    
    return 0;
}

/* Check size and if necessary expand string buffer in INCHI_IOSTREAM_STRING*/
int inchi_strbuf_update( INCHI_IOSTREAM_STRING *buf, int new_addition_size )
{
    int requsted_len;
    
    if ( !buf ) return -1;    

    if ( new_addition_size <= 0 ) return buf->nAllocatedLength;

    requsted_len = buf->nUsedLength + new_addition_size;

    if ( requsted_len >= buf->nAllocatedLength )
    {
        /* Expand */
        int  nAddLength = inchi_max( buf->nPtr, new_addition_size );
                                    /* buf->nPtr stores size increment for this buffer */
        char *new_str = 
                (char *) inchi_calloc( buf->nAllocatedLength + nAddLength, 
                                       sizeof(new_str[0]) );
        if ( !new_str ) 
            return -1; /* failed */
        if ( buf->pStr ) 
        {
            if ( buf->nUsedLength > 0 ) 
                memcpy( new_str, buf->pStr, sizeof(new_str[0])* buf->nUsedLength );
            inchi_free( buf->pStr );
        }
        buf->pStr = new_str;
        buf->nAllocatedLength += nAddLength;		
    }
    
    return buf->nAllocatedLength;
}


/* Add to the end of string in INCHI_IOSTREAM_STRING object,
    expanding buffer if necessary							*/
int inchi_strbuf_printf( INCHI_IOSTREAM_STRING *buf, const char* lpszFormat, ... )
{
int ret=0, max_len;
va_list argList;
    
    if ( !buf ) return -1;    

    my_va_start( argList, lpszFormat );
    max_len = GetMaxPrintfLength( lpszFormat, argList);
    va_end( argList );
    if ( max_len < 0 ) return 0;
    
    inchi_strbuf_update( buf, max_len );

    my_va_start( argList, lpszFormat );
    ret = vsprintf( buf->pStr + buf->nUsedLength, lpszFormat, argList );
    va_end(argList);
    if ( ret >= 0 ) 
        buf->nUsedLength += ret;

    return ret;
}


/*	Print to string in INCHI_IOSTREAM_STRING object 
    from specified position 'npos', expanding buffer if necessary.
    NB: be careful, intentionally no checks on where is 'npos'!		*/
int inchi_strbuf_printf_from( INCHI_IOSTREAM_STRING *buf, 
                              int npos, 
                              const char* lpszFormat, ... )
{
int ret=0, max_len;
va_list argList;
    
    if ( !buf ) return -1;    

    my_va_start( argList, lpszFormat );
    max_len = GetMaxPrintfLength( lpszFormat, argList);
    va_end( argList );
    if ( max_len < 0 ) return 0;
    
    max_len += npos;
    
    inchi_strbuf_update( buf, max_len );

    my_va_start( argList, lpszFormat );
    ret = vsprintf( buf->pStr + npos, lpszFormat, argList );
    va_end(argList);
    if ( ret >= 0 ) 
        buf->nUsedLength = npos + ret;
        
    return ret;
}


/*	Reset INCHI_IOSTREAM_STRING object holding an expandable buffer string
    (place '\0' at the start and do _not_ free memory).						*/
void inchi_strbuf_reset( INCHI_IOSTREAM_STRING *buf )
{
    if ( !buf ) return;
    if ( buf->pStr)
		buf->pStr[0] = '\0'; 
    buf->nUsedLength = buf->nPtr = 0;
}



/*	Close INCHI_IOSTREAM_STRING object holding an expandable buffer string, 
    free previously allocated sring memory									*/
void inchi_strbuf_close( INCHI_IOSTREAM_STRING *buf )
{
    if ( !buf )		 return;
    if ( buf->pStr ) inchi_free( buf->pStr );
    memset( buf, 0, sizeof(*buf) ); 
}



/*	Estimate printf string length.
   
    The code is based on Microsoft Knowledge Base article Q127038:
    "FIX: CString::Format Gives Assertion Failed, Access Violation"
    (Related to Microsoft Visual C++, 32-bit Editions, versions 2.0, 2.1) */
 
#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000

/* Formatting (using wsprintf style formatting)	*/
int GetMaxPrintfLength( const char *lpszFormat, va_list argList)
{
     /*ASSERT(AfxIsValidString(lpszFormat, FALSE));*/
     const char * lpsz;
     int nMaxLen, nWidth, nPrecision, nModifier, nItemLen;

     nMaxLen = 0;
     /* make a guess at the maximum length of the resulting string */
     for ( lpsz = lpszFormat; *lpsz; lpsz ++ )
     {
          /* handle '%' character, but watch out for '%%' */
          if (*lpsz != '%' || *( ++ lpsz ) == '%')
          {
               nMaxLen += 1;
               continue;
          }

          nItemLen = 0;

          /*  handle '%' character with format */
          nWidth = 0;
          for (; *lpsz; lpsz ++ )
          {
               /* check for valid flags */
               if (*lpsz == '#')
                    nMaxLen += 2;   /* for '0x' */
               else if (*lpsz == '*')
                    nWidth = va_arg(argList, int);
               else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0'
                        || *lpsz == ' ')
                           ;
               else /* hit non-flag character */
                          break;
          }
          /* get width and skip it */
          if (nWidth == 0)
          {
               /* width indicated by */
               nWidth = atoi(lpsz);
               for (; *lpsz && isdigit(*lpsz); lpsz ++ )
                     ;
          }
          /*ASSERT(nWidth >= 0);*/
          if ( nWidth < 0 )
              goto exit_error; /* instead of exception */

          nPrecision = 0;
          if (*lpsz == '.')
          {
               /* skip past '.' separator (width.precision)*/
               lpsz ++;

               /* get precision and skip it*/
               if (*lpsz == '*')
               {
                    nPrecision = va_arg(argList, int);
                    lpsz ++;
               }
               else
               {
                    nPrecision = atoi(lpsz);
                    for (; *lpsz && isdigit(*lpsz); lpsz ++)
                            ;
               }
              if ( nPrecision < 0 )
                  goto exit_error; /* instead of exception */
          }

          /* should be on type modifier or specifier */
          nModifier = 0;
          switch (*lpsz)
          {
          /* modifiers that affect size */
          case 'h':
               switch ( lpsz[1] ) {
               case 'd':
               case 'i':
               case 'o':
               case 'x':
               case 'X':
               case 'u':
                   /* short unsigned, short double, etc. -- added to the original MS example */
                   /* ignore the fact that these modifiers do affect size */
                   lpsz ++;
                   break;
               default:
                   nModifier = FORCE_ANSI;
                   lpsz ++;
                   break;
               }
               break;
          case 'l':
               switch ( lpsz[1] ) {
               case 'd':
               case 'i':
               case 'o':
               case 'x':
               case 'X':
               case 'u':
               case 'f': /* long float -- post ANSI C */
                   /* long unsigned, long double, etc. -- added to the original MS example */
                   /* ignore the fact that these modifiers do affect size */
                   lpsz ++;
                   break;
               default:
                   /*
                   nModifier = FORCE_UNICODE;
                   lpsz ++;
                   break;
                   */
                   goto exit_error;  /* no UNICODE, please */
               }
               break;
          /* modifiers that do not affect size */
          case 'F':
          case 'N':
          case 'L':
               lpsz ++;
               break;
          }

          /* now should be on specifier */
          switch (*lpsz | nModifier)
          {
          /* single characters*/
          case 'c':
          case 'C':
               nItemLen = 2;
               va_arg(argList, int);
               break;
          case 'c'|FORCE_ANSI:
          case 'C'|FORCE_ANSI:
               nItemLen = 2;
               va_arg(argList, int);
               break;
          case 'c'|FORCE_UNICODE:
          case 'C'|FORCE_UNICODE:
               goto exit_error;  /* no UNICODE, please */
               /*
               nItemLen = 2;
               va_arg(argList, wchar_t);
               break;
               */

          /* strings*/
          case 's':
          case 'S':
               nItemLen = (int) strlen(va_arg(argList, char*));
               nItemLen = inchi_max(1, nItemLen);
               break;
          case 's'|FORCE_ANSI:
          case 'S'|FORCE_ANSI:
               nItemLen = (int) strlen(va_arg(argList, char*));
               nItemLen = inchi_max(1, nItemLen);
               break;

          case 's'|FORCE_UNICODE:
          case 'S'|FORCE_UNICODE:
               goto exit_error;  /* no UNICODE, please */
               /*
               nItemLen = wcslen(va_arg(argList, wchar_t*));
               nItemLen = inchi_max(1, nItemLen);
               break;
               */

          }

          /* adjust nItemLen for strings */
          if (nItemLen != 0)
          {
               nItemLen = inchi_max(nItemLen, nWidth);
               if (nPrecision != 0)
                    nItemLen = inchi_min(nItemLen, nPrecision);
          }
          else
          {
               switch (*lpsz)
               {
               /* integers */
               case 'd':
               case 'i':
               case 'u':
               case 'x':
               case 'X':
               case 'o':
                    va_arg(argList, int);
                    nItemLen = 32;
                    nItemLen = inchi_max(nItemLen, nWidth+nPrecision);
                    break;

               case 'e':
               case 'f':
               case 'g':
               case 'G':
                    va_arg(argList, double);
                    nItemLen = 32;
                    nItemLen = inchi_max(nItemLen, nWidth+nPrecision);
                    break;

               case 'p':
                    va_arg(argList, void*);
                    nItemLen = 32;
                    nItemLen = inchi_max(nItemLen, nWidth+nPrecision);
                    break;

               /* no output */
               case 'n':
                    va_arg(argList, int*);
                    break;

               default:
                   /*ASSERT(FALSE);*/  /* unknown formatting option*/
                   goto exit_error; /* instead of exception */
               }
          }

          /* adjust nMaxLen for output nItemLen */
          nMaxLen += nItemLen;
     }
     return nMaxLen;

exit_error:
     return -1; /* wrong format */
} 


/*
	Reads the next line to growing str buf. 
	Returns n of read chars, -1 at end of file or at error.
 */
int inchi_strbuf_getline(INCHI_IOSTREAM_STRING *buf, FILE *f, int crlf2lf, int preserve_lf )
{
int len = 0, c;
	inchi_strbuf_reset( buf );
	while( 1 )
	{
		c= fgetc( f );
		if ( ferror( f ) )	return -1;		
		if ( c == EOF )		return -1;
		inchi_strbuf_printf( buf, "%c", c );
		if ( c == '\n' )		break;		
	}
	
	if ( crlf2lf )
	{
		if ( buf->nUsedLength > 2 ) 
		{
			if ( buf->pStr[ buf->nUsedLength - 2] == '\r' )
			{
				buf->pStr[ buf->nUsedLength - 2]	= '\n';
				buf->pStr[ --buf->nUsedLength ]		= '\0';
			}
		}
	}
	if ( !preserve_lf )	
	{
		buf->pStr[ --buf->nUsedLength ] = '\0';
	}

	return buf->nUsedLength;
}
