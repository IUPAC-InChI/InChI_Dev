/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.06
 * December 15, 2020
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
 * Copyright (C) IUPAC and InChI Trust
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
 * Licence No. 1.0 with this library; if not, please e-mail:
 *
 * info@inchi-trust.org
 *
 */


#include "stdafx.h"
#include "fthread.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
UINT ThreadFunction(void * data)
{

	ThreadData * pThreadData = (ThreadData *) data;
	if( pThreadData->pf )
		pThreadData->pf(THREAD_STARTED);

	int nRet = 
		ProcessOneStructureEx( pThreadData->pINChIParams->ic,
									pThreadData->pINChIParams->pCG,
									&pThreadData->pINChIParams->struct_data, 
									&pThreadData->pINChIParams->inp_parms, 
									pThreadData->pINChIParams->szTitle,
									pThreadData->pINChIParams->pINChI, 
									pThreadData->pINChIParams->pINChI_Aux,
									&pThreadData->pINChIParams->inp_file, 
									&pThreadData->pINChIParams->log_file, 
									&pThreadData->pINChIParams->output_file, 
									&pThreadData->pINChIParams->prb_file,
									&pThreadData->pINChIParams->OrigAtData,
									pThreadData->pINChIParams->PrepAtData,
									pThreadData->pINChIParams->num_inp, 
									pThreadData->pINChIParams->strbuf, 
									0 ); 


	if ( pThreadData->pINChIParams->output_file.f ) 
			fflush( pThreadData->pINChIParams->output_file.f );
		if ( pThreadData->pINChIParams->log_file.f )	
			fflush( pThreadData->pINChIParams->log_file.f );
		if ( pThreadData->pINChIParams->prb_file.f )	
			fflush( pThreadData->pINChIParams->prb_file.f );

	if( pThreadData->pf )
		pThreadData->pf(THREAD_FINISHED);

	return nRet;
}

/////////////////////////////////////////////////////////////////////////////
UINT ThreadBatchFunction(void * data)
{
	CString msg;
	int nRet, num_err;
	unsigned long ulTotalProcessingTime;
	void (*pf)(DrawData * pDrawData) = DRAWDATA;
	DRAWDATA = NULL;

	ThreadData * pThreadData = (ThreadData *) data;
	if( pThreadData->pf )
		pThreadData->pf(THREAD_STARTED);

    ulTotalProcessingTime = 0;
	num_err = 0;

    while ( 1 ) {

        // read one structure from input and display optionally it
		CleanOneStructData_(pThreadData->pINChIParams);
		nRet = GetOneStructure( pThreadData->pINChIParams->ic,
								&pThreadData->pINChIParams->struct_data, 
								&pThreadData->pINChIParams->inp_parms, 
								pThreadData->pINChIParams->szTitle, 
								&pThreadData->pINChIParams->inp_file, 
								&pThreadData->pINChIParams->log_file, 
								&pThreadData->pINChIParams->output_file, 
								&pThreadData->pINChIParams->prb_file, 
								&pThreadData->pINChIParams->OrigAtData, 
								&pThreadData->pINChIParams->num_inp, 
								NULL);


        switch ( nRet ) {
        case _IS_FATAL:
			num_err++;
        case _IS_EOF:
            goto exit_function;
        case _IS_ERROR:
			num_err++;
        case _IS_SKIP:
            continue;
        }

        /* create INChI for each connected component of the structure and optionally display them */
        /* output INChI for the whole structure */
		nRet = ProcessOneStructureEx( pThreadData->pINChIParams->ic,
									pThreadData->pINChIParams->pCG,
									&pThreadData->pINChIParams->struct_data, 
									&pThreadData->pINChIParams->inp_parms, 
									pThreadData->pINChIParams->szTitle,
									pThreadData->pINChIParams->pINChI, 
									pThreadData->pINChIParams->pINChI_Aux,
									&pThreadData->pINChIParams->inp_file, 
									&pThreadData->pINChIParams->log_file, 
									&pThreadData->pINChIParams->output_file, 
									&pThreadData->pINChIParams->prb_file,
									&pThreadData->pINChIParams->OrigAtData,
									pThreadData->pINChIParams->PrepAtData,
									pThreadData->pINChIParams->num_inp, 
									pThreadData->pINChIParams->strbuf, 
									0 ); 

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
    }

exit_function:

    if ( pThreadData->pINChIParams->log_file.f ) 
    { // block
        int hours, minutes, seconds, mseconds;
        SplitTime( ulTotalProcessingTime, &hours, &minutes, &seconds, &mseconds );
        inchi_ios_print( &pThreadData->pINChIParams->log_file, "Finished processing %d structure%s: %d error%s, processing time %d:%02d:%02d.%02d\n",
                                pThreadData->pINChIParams->num_inp, pThreadData->pINChIParams->num_inp==1?"":"s",
                                num_err, num_err==1?"":"s",
                                hours, minutes, seconds,mseconds/10);
    }

	DRAWDATA = pf;
	if( pThreadData->pf )
		pThreadData->pf(THREAD_FINISHED);

	return nRet;
}
