/*
 * International Chemical Identifier (InChI)
 * Version 1
 *
 *
 * InChI Library caller example
 *
 * This is a simplistic example of InChI API usage
 *
 *
 *
 * main
 *
 *
 */

/*	
 *	The program reads SD/MOL file and generates InChI/InChIKey's
 *  using the following InChI API calls
 *
 *		- MakeInputForINCHI		read the next available molecular data block from SD/MOL
 *								and creates InChI input data structure
 *
 *		- GetINCHI				creates InChI string from InChI input data 
 *
 *		- GetINCHIKeyFromINCHI	creates InChIkey from InChI string 
 *
 *
 *
 *
 *	PSEUDOCODE 
 *
 *	- Preparatory work
 *
 *
 *	- Main processing loop starts
 *	
 *		-- Clean previous-iteration stuff
 *
 *		-- Get the new structure from SD file record/MOL file
 *
 *		-- Check return code;
 *		   if EOF occurred, exit
 *
 *		-- Process the structure
 *		
 *			--- Create InChI		
 *			--- Optionally create InChIKey
 *	
 *	- Main processing loop ends
 *	
 *
 *	- Final printout
 *	
 *	- Final Cleanup
 *
 */



#if 0

#if( defined( WIN32 ) && defined( _CONSOLE ) && defined(_MSC_VER) && _MSC_VER >= 800 )
#define ADD_WIN_CTLC   /* detect Ctrl-C under Win-32 and Microsoft Visual C ++ */
#endif

#if( defined( WIN32 ) && defined( _CONSOLE ) && defined(_MSC_VER) && _MSC_VER >= 800 && defined(ADD_WIN_CTLC) && !(defined(__STDC__) && __STDC__ == 1) )
#include <windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>



#include "../../../../INCHI_BASE/src/mode.h"
#include "../../../../INCHI_BASE/src/inchi_api.h"

#include "e_ctl_data.h"


/* Local */


static int OpenAllFiles( INPUT_PARMS *ip,
						 FILE **inp_file, 
						 FILE **out_file, 
						 FILE **log_file, 
						 FILE **prb_file );
				


				
/****************************************************************************/
int main( int argc, char *argv[ ] )
{
	
	
	
	
INPUT_PARMS input_params, *ip = &input_params;

FILE *inp_file, /* MOL/SD file */
	 *out_file, /* InChI/InChIKey strings */
	 *log_file, /* warnings/errors */
	 *prb_file; /* copy of inappropriate records */

inchi_Input  inchi_inp, *pInp = &inchi_inp;
inchi_Output inchi_out, *pOut = &inchi_out;



int retcode;
long num_err=0;


	/* - Preparatory work */


	/* Command line */

	retcode = GetInputParams( ip );

	if ( ! retcode )
		goto exit_function;


	/* Files */

	retcode = OpenAllFiles( ip, &inp_file, &out_file, &log_file, &prb_file );
	
	if ( ! retcode )
		goto exit_function;

	
    /*  original input structure */
    memset( pInp, 0, sizeof(*pInp) );
    memset( pOut, 0, sizeof(*pOut) );
   


	/* - Main processing loop starts */

	retcode = 0;

	while ( (retcode!=inchi_Ret_EOF) &&  (retcode!=inchi_Ret_BREAK) )	
	{

		/* -- Clean previous-iteration stuff */
		FreeINCHI ( pOut );
		
		pInp->szOptions = szInchiCmdLine;


		/* -- Get the new structure from SD file record/MOL file */


		retcode = MakeINCHIInputFromMolfile( inp_file, pInp );


		if ( retcode==inchi_Ret_EOF ) 
			goto exit_function;
		else if ( retcode==inchi_Ret_SKIP )
			continue;
		else if ( retcode==inchi_Ret_FATAL || retcode==inchi_Ret_ERROR )
			num_err++;
		else
			;
 
		
		retcode = GetINCHI( pInp, pOut );
		


#if 0

  while ( !sd->bUserQuit && !bInterrupted ) 
    {
    
        if ( ip->last_struct_number && num_inp >= ip->last_struct_number ) 
        {
            nRet = _IS_EOF; /*  simulate end of file */
            goto exit_function;
        }

        /*  read one structure from input and display optionally it */

        nRet = GetOneStructure( sd, ip, szTitle, inp_file, plog, pout, pprb,
                                orig_inp_data, &num_inp, pStr, nStrLen, pStructPtrs );
        inchi_ios_flush2(plog, stderr);


        if ( pStructPtrs ) 
            pStructPtrs->cur_fptr ++;

        if ( sd->bUserQuit ) 
            break;

        switch ( nRet ) 
        {
            case _IS_FATAL:
                num_err ++;
            case _IS_EOF:
                goto exit_function;
            case _IS_ERROR:
                num_err ++;
            case _IS_SKIP:
                continue;
        }

        /* create INChI for each connected component of the structure and optionally display them */
        /* output INChI for the whole structure */
        
        nRet1 = ProcessOneStructure( sd, ip, szTitle, pINChI, pINChI_Aux,
                                     inp_file, plog, pout, pprb,
                                     orig_inp_data, prep_inp_data,
                                     num_inp, pStr, nStrLen,
                                     0 /* save_opt_bits */);        
        inchi_ios_flush2(plog, stderr);

#endif /* 0 */


		/* -- Check return code; if EOF occurred, exit */

		if ( retcode == inchi_Ret_EOF )
			goto exit_function;

		else if ( retcode==inchi_Ret_FATAL )
			num_err++;
		else if ( retcode==inchi_Ret_ERROR )
			num_err++;
		else if ( retcode==inchi_Ret_SKIP )
			continue;
		else
		{
			; /* do nothing ... */
		}



		/* -- Process the structure */


			/* --- Create InChI */

/*		nRet = ProcessOneStructure( &pThreadData->pINChIParams->struct_data, &pThreadData->pINChIParams->inp_parms, pThreadData->pINChIParams->szTitle,
                         pThreadData->pINChIParams->pINChI, pThreadData->pINChIParams->pINChI_Aux,
                         &pThreadData->pINChIParams->inp_file, &pThreadData->pINChIParams->log_file, &pThreadData->pINChIParams->output_file, &pThreadData->pINChIParams->prb_file,
                         &pThreadData->pINChIParams->OrigAtData,pThreadData->pINChIParams->PrepAtData,
                         pThreadData->pINChIParams->num_inp, pThreadData->pINChIParams->pStr, NSTRLEN, 0 ); 
*/

		retcode = GetINCHI( pInp, pOut );



		/* --- Optionally create InChIKey */


	/* - Main processing loop ends */
	}	





	/* - Final printout */


	/* - Final cleanup */




#if 0




        ulTotalProcessingTime += pThreadData->pINChIParams->struct_data.ulStructTime;

        switch ( nRet ) {
        case _IS_FATAL:
			num_err++;
            goto exit_function;
        case _IS_ERROR:
			num_err++;
            continue;
        }

		msg.Format("Processing structure #%d",pThreadData->pINChIParams->num_inp);
		SetStatusText(msg);
 
	 } /* eof main 'while' processing loop */


#endif



exit_function:
	
	 return  retcode;
}


/****************************************************************************/
int OpenAllFiles( INPUT_PARMS *ip,
				  FILE **inp_file, 
				  FILE **out_file, 
				  FILE **log_file, 
				  FILE **prb_file )
{
/*
  -- Files --
  ip->path[0] => Input
  ip->path[1] => Output (INChI)
  ip->path[2] => Log
  ip->path[3] => Problem structures
*/


    /*  Logfile (open as early as possible) */

    if ( !ip->path[2] || !ip->path[2][0] ) 
    {
        fprintf( stderr, "%s version %s%s%s\n", INCHI_NAME, INCHI_VERSION, TARGET_ID_STRING, bRELEASE_VERSION? "":""); /* (Pre-release, for evaluation purposes only)" ); */
        fprintf( stderr, "Log file not specified. Using standard error output.\n");
        *log_file = stderr;
    } 
    else if ( !(*log_file = fopen( ip->path[2], "w" ) ) ) 
    {
        fprintf( stderr, "%s version %s%s%s\n", INCHI_NAME, INCHI_VERSION, TARGET_ID_STRING, bRELEASE_VERSION? "":""); /* (Pre-release, for evaluation purposes only)" );*/
        fprintf( stderr, "Cannot open log file '%s'. Using standard error output.\n", ip->path[2] );
        *log_file = stderr;
    } 
    else 
    {
        fprintf( *log_file, "%s version %s%s%s\n", INCHI_NAME, INCHI_VERSION, TARGET_ID_STRING, bRELEASE_VERSION? "":""); /* (Pre-release, for evaluation purposes only)" );*/
        fprintf( *log_file, "Opened log file '%s'\n", ip->path[2] );
    }


    /* Input file */

    if ( ( ip->num_paths > 0 ) &&
		 ( ip->nInputType==INPUT_MOLFILE || ip->nInputType==INPUT_SDFILE ) ) 
    {
        const char *fmode = NULL;

#if ( defined(_MSC_VER)&&defined(_WIN32) || defined(__GNUC__)&&defined(__MINGW32__)&&defined(_WIN32) )
        /* compilers that definitely allow fopen "rb" (binary read) mode */
        fmode = "rb";
        if ( !ip->path[0] || !ip->path[0][0] || !(*inp_file = fopen( ip->path[0], "rb" ) ) ) 
        {
            fprintf( *log_file, "Cannot open input file '%s'. Terminating.\n", 
					  ip->path[0]? ip->path[0] : "<No name>" );
            goto ret_err;
        } 
        else 
			fprintf( *log_file, "Opened input file '%s'\n", ip->path[0] );
#else
        if ( !ip->path[0] || !ip->path[0][0] || !(*inp_file = fopen( ip->path[0], "r" ) ) ) 
		{
            fprintf( *log_file, "Cannot open input file '%s'. Terminating.\n", ip->path[0]? ip->path[0] : "<No Name>" );
            goto ret_err;
        } 
		else 
		{
            fprintf( *log_file, "Opened input file '%s'\n", ip->path[0] );
        }
        fmode = "r";
#endif /* ( defined(_MSC_VER)&&defined(_WIN32) || defined(__BORLANDC__)&&defined(__WIN32__) || defined(__GNUC__)&&defined(__MINGW32__)&&defined(_WIN32) ) */

    } 
    else if ( (ip->nInputType != INPUT_MOLFILE && 
               ip->nInputType != INPUT_SDFILE && 
               ip->nInputType != INPUT_CMLFILE && 
               ip->nInputType != INPUT_INCHI && 
               /*^^^ post-1.02b */ 
               ip->nInputType != INPUT_INCHI_PLAIN ) ) 
    {
        fprintf( *log_file, "Input file type not specified. Terminating.\n");
        goto ret_err;
    } 
    else 
    {
        fprintf( *log_file, "Input file not specified. Using standard input.\n");
        *inp_file = stdin;
    }
    

    /*  Output file */
    
    if ( !ip->path[1] || !ip->path[1][0] ) 
    {
        fprintf( *log_file, "Output file not specified. Using standard output.\n");
        *out_file = stdout;
    } 
    else 
    {
        if ( !(*out_file = fopen( ip->path[1], "w" ) ) ) 
        {
            fprintf( *log_file, "Cannot open output file '%s'. Terminating.\n", ip->path[1] );
            goto ret_err;
        } 
        else 
        {
            fprintf( *log_file, "Opened output file '%s'\n", ip->path[1] );
            if ( (ip->bINChIOutputOptions & (INCHI_OUT_PLAIN_TEXT)) &&
                  *inp_file != stdin &&
                  !(ip->bINChIOutputOptions & INCHI_OUT_SDFILE_ONLY) &&
                  !ip->bNoStructLabels &&
                  !(ip->bINChIOutputOptions & INCHI_OUT_TABBED_OUTPUT)) 
            {
                 PrintFileName( "* Input_File: \"%s\"\n", *out_file, ip->path[0] );
             }
        }
    }

    
    /*  Problem file */

    if ( ip->path[3] && ip->path[3][0] ) 
    {
        const char *fmode = "w";

#if ( defined(_MSC_VER)&&defined(_WIN32) || defined(__BORLANDC__)&&defined(__WIN32__) || defined(__GNUC__)&&defined(__MINGW32__)&&defined(_WIN32) )

        if ( ip->nInputType != INPUT_CMLFILE ) {
            fmode = "wb";
        }

#endif

        if ( !(*prb_file = fopen( ip->path[3], fmode ) ) ) 
        {
            fprintf( *log_file, "Cannot open problem file '%s'. Terminating.\n", ip->path[3] );
            goto ret_err;
        } 
        else 
        {
             fprintf( *log_file, "Opened problem file '%s'\n", ip->path[3] );
        }
    }

    
	return 0;  /*  success */


ret_err:

	/* failed */
    return 1;	
}



#endif