/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.05 (pre-release)
 * September 29, 2016
 *
 * The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST. 
 * Modifications and additions by IUPAC and the InChI Trust.
 * Some portions of code were developed/changed by external contributors
 * (either contractor or volunteer) which are listed in the file 
 * 'External-contributors' included in this distribution.
 *
 * IUPAC/InChI-Trust Licence No.1.0 for the 
 * International Chemical Identifier (InChI) 
 * Copyright (C) IUPAC and InChI Trust Limited
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the IUPAC/InChI Trust InChI Licence No.1.0, 
 * or any later version.
 * 
 * Please note that this library is distributed WITHOUT ANY WARRANTIES 
 * whatsoever, whether expressed or implied.  
 * See the IUPAC/InChI-Trust InChI Licence No.1.0 for more details.
 * 
 * You should have received a copy of the IUPAC/InChI Trust InChI 
 * Licence No. 1.0 with this library; if not, please write to:
 * 
 * The InChI Trust
 * 8 Cavendish Avenue
 * Cambridge CB1 7US
 * UK
 *
 * or e-mail to alan@inchi-trust.org
 * 
 */


/* 
	Shuffle atoms and change related data in input MOL text.
	
	Quick and dirty implementation; intended only for V3000 (made from PDB with openbabel).

	Used generic shuffle code from: http://rosettacode.org/wiki/Knuth_shuffle#C

*/


#pragma warning( disable : 4996 )

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "shuffler.h"
#include "moreitil.h"


#define BYTE(X) ((unsigned char *)(X)) 


/* Local */
int replace_num_in_atom_line( char *str, char *line, long num );
int replace_nums_in_bond_line( char *str, char *line, int shuffled_numbers[] );
int back_map_shuffled( int k, int shuffled_numbers[] );



/******************************************************/
int rrand(int m)
{
    return 
        (int)((double)m * ( rand() / (RAND_MAX+1.0) ));
}
/******************************************************/
void shuffle(void *obj, size_t nmemb, size_t size)
{
  void *temp = malloc(size);
  size_t n = nmemb;
  while ( n > 1 ) 
  {
    size_t k = rrand( (int) n--);
    memcpy(temp, BYTE(obj) + n*size, size);
    memcpy(BYTE(obj) + n*size, BYTE(obj) + k*size, size);
    memcpy(BYTE(obj) + k*size, temp, size);
  }
  free(temp);
} 

/*****************************************************************/
MFLines* new_mflines( char *instring, M2I_NUM nat, M2I_NUM nbonds )
{
int c, cc;
char *inp=NULL, *prev_line=NULL;
size_t i, n;

    MFLines *mfl = calloc(sizeof(MFLines), 1);

    mfl->nlines = 0;

    mfl->nat = nat;
    mfl->nbonds = nbonds;


    mfl->base_string = strdup( instring ); 
		/* Will soon be mangled for convenience */
    if ( !mfl->base_string )
        return NULL;

    mfl->textlen = strlen( mfl->base_string );

    /* Count lines & replace '\n' with '\0') */
    n = 0;
    inp = mfl->base_string;
    while ( c=*inp )
    {
        n++;
        if ( c=='\n' ) 
        {
            *inp = '\0';	/* mangling */
            mfl->nlines++;
        }
        inp++;
    }

    /* Form the array of pointers to source lines */
    mfl->lines = (char **) calloc( mfl->nlines, sizeof(char*) );
    inp = prev_line = mfl->base_string;
    cc = '\0';
    i = 0;
    while ( n-- )
    {
        c=*inp;
        if ( !c ) 
        {
            if ( cc )
            {
                mfl->lines[i++] = prev_line;
                prev_line = inp;
            }
            else
                mfl->lines[i++] = inp;
        }
        else
        {
            if ( !cc )
                prev_line = inp;
        }
        cc = c;
        inp++;
    }

    for (i=0; i<mfl->nlines; i++)
    {
        if ( !own_memicmp( mfl->lines[i], "M  V30 BEGIN ATOM", 17 ) )
        {
            mfl->iat0 = i+1;
            break;
        }

    }
    for (i=mfl->iat0+mfl->nat; i<mfl->nlines; i++)
    {
        if ( !own_memicmp( mfl->lines[i], "M  V30 BEGIN BOND", 17 ) )
        {
            mfl->ibonds0 = i+1;
            break;
        }
    }

    return mfl;
}


/****************************************************************************/
char* shuffled_mflines( MFLines* mfl, M2I_NUM shuffled_numbers[] )
{
char *new_text_string=NULL;
char *p;
char modif_line[4096];
size_t i, j, nc, ncopied;

    new_text_string = calloc( mfl->textlen+4096, sizeof(char)); 
						/* Shuffled lines will go there (+ reserve some extra space) */
    if ( NULL==new_text_string )
        return NULL;

    p = new_text_string;

	/* NB: this is only for MOL V3000 (made from PDB with openbabel) */
        
	/* Beginning of MOL */
    for ( i=0; i<mfl->iat0; i++)
    {
        /* Copy untouched lines */
        nc = strlen(mfl->lines[i]);
        memmove( p , mfl->lines[i], nc );
        if ( i < mfl->nlines-1 )
        {
            p[nc]='\n';
            p+= nc+1;
        }
        else
            p[nc]='\0';
    }
	/* Write atoms info */
    for ( i=mfl->iat0; i<mfl->iat0 + mfl->nat; i++)
    {
        /* Copy shuffled lines */
        M2I_NUM num;
        j = shuffled_numbers[ i - mfl->iat0 ] + mfl->iat0;
        /* 0->300 */
        num = (M2I_NUM) i - (M2I_NUM) mfl->iat0 + 1;
        ncopied = replace_num_in_atom_line( mfl->lines[j], modif_line, num );
        nc = strlen( modif_line );
        memmove( p , modif_line, nc );
        p[nc]='\n';
        p+= nc+1;
    }
    /* Write nonds and other info */
    for ( i=mfl->iat0 + mfl->nat; i<mfl->nlines; i++)
    {
        if ( (i >=  mfl->ibonds0) && (i < mfl->ibonds0 + mfl->nbonds) )
        {
            /* Copy after changing atom numbers */
            ncopied = replace_nums_in_bond_line( mfl->lines[i], modif_line, shuffled_numbers );
            nc = strlen( modif_line );
            memmove( p , modif_line, nc );
            p[nc]='\n';
            p+= nc+1;
        }
        else
        {
            /* Copy untouched */
            nc = strlen(mfl->lines[i]);
            memmove( p , mfl->lines[i], nc );
            if ( i < mfl->nlines-1 )
            {
                p[nc]='\n';
                p+= nc+1;
            }
            else
                p[nc]='\0';
        }
    }
    return
        new_text_string;
}


/****************************************************************************/
void del_mflines( MFLines* mfl )
{
    if ( mfl==NULL ) 
        return;
    if ( mfl->base_string )
        free( mfl->base_string );
    if ( mfl->lines )
        free( mfl->lines );
    free( mfl );
    mfl = NULL;
}


/****************************************************************************/
int back_map_shuffled( int k, int shuffled_numbers[] )
{
size_t i, n;
    n = PERMAXATOMS;
    for (i=0; i<n; i++)
        if ( shuffled_numbers[i]==k )
            return (int) i;
    return -1;
}


/****************************************************************************/
#define CBUFL 4096

int replace_num_in_atom_line( char *str, char *line, long num )
{
char *p; 
size_t ncopied;   
char buf[CBUFL];

    if (str==NULL)
        return -1;
    if (strlen(str)<1)
        return -1;

    p = get_substr_in_between(str, "M  V30 ", " ", buf, CBUFL-2, &ncopied);
    if ( !ncopied)
        return -1;
    --p;
    p = get_substr_in_between( p, " ", "", buf, CBUFL-2, &ncopied);
    if ( !ncopied)
        return -1;
    sprintf( line, "M  V30 %-ld %-s", num, buf);
    
    return 0;
}


/****************************************************************************/
int replace_nums_in_bond_line( char *str, char *line, int shuffled_numbers[] )
{
char *p; 
size_t ncopied;
long a1=0, a2=0;
int b1, b2;
char entry[8][32];

    if (str==NULL)
        return -1;
    if (strlen(str)<1)
        return -1;
    
    p = get_substr_in_between(str, "M  V30 ", " ", entry[0], CBUFL-2, &ncopied);
    if ( ncopied)
    {
        p = get_substr_in_between( --p, " ", " ", entry[1], CBUFL-2, &ncopied);
        if ( ncopied)
        {
            p = get_substr_in_between( --p, " ", " ", entry[2], CBUFL-2, &ncopied);
            if ( ncopied)
            {
                p = get_substr_in_between( --p, " ", "", entry[3], CBUFL-2, &ncopied);
                a1 = atol(entry[2]);
                a2 = atol(entry[3]);
            }
        }
    }

    if ( (a1>0) && (a2>0) )
    {
        /*
        b1 =  shuffled_numbers[a1-1] + 1;
        b2 =  shuffled_numbers[a2-1] + 1;
        */
        b1 =  back_map_shuffled( a1-1, shuffled_numbers )  + 1;
        b2 =  back_map_shuffled( a2-1, shuffled_numbers )  + 1;

        sprintf( line, "M  V30 %-s %-s %-d %-d", entry[0], entry[1], b1, b2 );
    }

    return 0;
}
