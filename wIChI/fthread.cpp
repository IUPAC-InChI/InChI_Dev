#include "stdafx.h"
#include "fthread.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


UINT ThreadFunction(void * data)
{

	ThreadData * pThreadData = (ThreadData *) data;
	if( pThreadData->pf )
		pThreadData->pf(THREAD_STARTED);
	int nRet = ProcessOneStructureEx( &pThreadData->pINChIParams->struct_data, &pThreadData->pINChIParams->inp_parms, pThreadData->pINChIParams->szTitle,
                         pThreadData->pINChIParams->pINChI, pThreadData->pINChIParams->pINChI_Aux,
                         &pThreadData->pINChIParams->inp_file, &pThreadData->pINChIParams->log_file, &pThreadData->pINChIParams->output_file, &pThreadData->pINChIParams->prb_file,
                         &pThreadData->pINChIParams->OrigAtData,pThreadData->pINChIParams->PrepAtData,
                         pThreadData->pINChIParams->num_inp, pThreadData->pINChIParams->pStr, NSTRLEN, 0 ); 
	
	
	if( pThreadData->pf )
		pThreadData->pf(THREAD_FINISHED);

	return nRet;
}

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
		nRet = GetOneStructure( &pThreadData->pINChIParams->struct_data, &pThreadData->pINChIParams->inp_parms, 
			pThreadData->pINChIParams->szTitle, &pThreadData->pINChIParams->inp_file, 
			&pThreadData->pINChIParams->log_file, &pThreadData->pINChIParams->output_file, 
			&pThreadData->pINChIParams->prb_file, &pThreadData->pINChIParams->OrigAtData, 
			&pThreadData->pINChIParams->num_inp, pThreadData->pINChIParams->pStr, NSTRLEN, NULL);

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
		nRet = ProcessOneStructureEx( &pThreadData->pINChIParams->struct_data, &pThreadData->pINChIParams->inp_parms, pThreadData->pINChIParams->szTitle,
                         pThreadData->pINChIParams->pINChI, pThreadData->pINChIParams->pINChI_Aux,
                         &pThreadData->pINChIParams->inp_file, &pThreadData->pINChIParams->log_file, &pThreadData->pINChIParams->output_file, &pThreadData->pINChIParams->prb_file,
                         &pThreadData->pINChIParams->OrigAtData,pThreadData->pINChIParams->PrepAtData,
                         pThreadData->pINChIParams->num_inp, pThreadData->pINChIParams->pStr, NSTRLEN, 0 ); 

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
