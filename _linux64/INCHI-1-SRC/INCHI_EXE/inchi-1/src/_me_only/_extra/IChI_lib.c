/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.04
 * September 9, 2011
 *
 * The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST. Modifications and additions by IUPAC 
 * and the InChI Trust.
 *
 * IUPAC/InChI-Trust Licence for the International Chemical Identifier (InChI) 
 * Software version 1.0.
 * Copyright (C) IUPAC and InChI Trust Limited
 * 
 * This library is free software; you can redistribute it and/or modify it under the 
 * terms of the IUPAC/InChI Trust Licence for the International Chemical Identifier 
 * (InChI) Software version 1.0; either version 1.0 of the License, or 
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
 * See the IUPAC/InChI Trust Licence for the International Chemical Identifier (InChI) 
 * Software version 1.0 for more details.
 * 
 * You should have received a copy of the IUPAC/InChI Trust Licence for the 
 * International Chemical Identifier (InChI) Software version 1.0 along with 
 * this library; if not, write to:
 * 
 * The InChI Trust
 * c/o FIZ CHEMIE Berlin
 * Franklinstrasse 11
 * 10587 Berlin
 * GERMANY
 * 
 */
  

#ifndef INCHI_LIB
#define INCHI_LIB 1
#endif

#include "mode.h"
#include "ichi_io.h"

#ifdef INCHI_LIB

#include <stdlib.h>
#include <stdio.h>
#include "ichi_lib.h"
#include "strutil.h"
#if( ADD_CMLPP == 1 )
#include "readcml.hpp"
#endif

void FreeDrawData( struct DrawData * pDrawData )
{
    if( pDrawData )
    {
        if( pDrawData->pWindowData )
        {
            FreeWinData(pDrawData->pWindowData);
            inchi_free(pDrawData->pWindowData);
        }
        if( pDrawData->szTitle )
            inchi_free(pDrawData->szTitle);
    }
}

///////////////////////////////////////////////////////////////////
MY_WINDOW_DATA * CreateWinData_( inp_ATOM *at, int num_at, int num_removed_H, int bAdd_DT_to_num_H, int num_removed_protons,
                                 NUM_H *nNumRemovedProtonsIsotopic, int bIsotopic, int bTautomeric,
                                 INChI **cur_INChI, INChI_Aux **cur_INChI_Aux,
                                 int bAbcNumbers, DRAW_PARMS *dp, INCHI_MODE nMode)
{
    MY_WINDOW_DATA * pWinData = (MY_WINDOW_DATA *)inchi_calloc(1,sizeof(MY_WINDOW_DATA));
    if( pWinData == NULL )
        return NULL;

    if ( !CreateInfoAtomData( &pWinData->inf_at_data, num_at, 1 ) )
    {
        inchi_free(pWinData); 
        return NULL;
    }
    FillOutInfAtom( at, &pWinData->inf_at_data, num_at,  num_removed_H, bAdd_DT_to_num_H, num_removed_protons,
                    nNumRemovedProtonsIsotopic, bIsotopic,
                    cur_INChI?cur_INChI[bTautomeric]:NULL,
                    cur_INChI_Aux?cur_INChI_Aux[bTautomeric]:NULL, bAbcNumbers,nMode);

    FillTableParms( &dp->sdp, cur_INChI, cur_INChI_Aux, nMode, bIsotopic, bTautomeric );

    pWinData->at0   =(inp_ATOM *)inchi_calloc(num_at+1, sizeof(pWinData->at0[0]));
    pWinData->at1   =(inp_ATOM *)inchi_calloc(num_at+1, sizeof(pWinData->at1[0]));
    pWinData->nFontSize = dp->sdp.nFontSize;
    if ( !pWinData->at0 || !pWinData->at1 ) {
        FreeWinData( pWinData );
        inchi_free(pWinData);
        return NULL;
    }
    memcpy( pWinData->at0, at, sizeof(at[0])*num_at );
    memcpy( pWinData->at1, at, sizeof(at[0])*num_at );

    pWinData->num_at      = num_at;
    pWinData->bOrigAtom   = dp->sdp.bOrigAtom;
    pWinData->nTimerId    = 0;
    pWinData->ulDisplTime = dp->sdp.ulDisplTime;
    if ( dp->sdp.tdp ) {
        pWinData->tdp = *dp->sdp.tdp;
    }
    pWinData->szTitle = NULL;
    return pWinData;
}
///////////////////////////////////////////////////////////////////
MY_WINDOW_DATA * CreateWinDataComposite_( COMP_ATOM_DATA *composite_norm_data, int bIsotopic, int bTautomeric,
                                         PINChI2 *pINChI2, PINChI_Aux2 *pINChI_Aux2,
                                         int bAbcNumbers, DRAW_PARMS *dp, INCHI_MODE nMode)
{
    MY_WINDOW_DATA * pWinData = (MY_WINDOW_DATA *)inchi_calloc(1,sizeof(MY_WINDOW_DATA));
    inp_ATOM *at;
    int       num_at, num_components;

    if( pWinData == NULL )
        return NULL;

    at             = composite_norm_data[bTautomeric].at;
    num_at         = composite_norm_data[bTautomeric].num_at;
    num_components = composite_norm_data[bTautomeric].num_components;

    if ( !CreateInfoAtomData( &pWinData->inf_at_data, num_at, num_components ) ) {
        FreeWinData( pWinData );
        inchi_free(pWinData);
        return NULL;
    }

    if ( !FillOutCompositeCanonInfAtom(composite_norm_data, &pWinData->inf_at_data,
                                 bIsotopic, bTautomeric,
                                 pINChI2, pINChI_Aux2, bAbcNumbers, nMode) ) {
        FreeWinData( pWinData );
        inchi_free(pWinData);
        return NULL;
    }
    if ( bTautomeric == TAUT_INI ) {
        /*
        FillOutInfAtom( at, &pWinData->inf_at_data, num_at,
                        (composite_norm_data+bTautomeric)->num_removed_H,
                        (composite_norm_data+bTautomeric)->nNumRemovedProtons,
                        bAdd_DT_to_num_H,
                        (composite_norm_data+bTautomeric)->nNumRemovedProtonsIsotopic, bIsotopic,
                        NULL, NULL, bAbcNumbers, nMode);
         */
    } else {
        /* real check for tautomeric components 02-04-2005 */
        int m, nNumTautComponents = 0;
        if ( 1 == bTautomeric ) {
            for ( m = 0; m < composite_norm_data[TAUT_YES].num_components; m ++ ) {
                if ( !pINChI2[m][TAUT_YES] )
                    continue;
                if ( pINChI2[m][TAUT_YES]->bDeleted || pINChI2[m][TAUT_YES]->lenTautomer > 0 )
                    nNumTautComponents ++;
            }
        }
        FillCompositeTableParms( &dp->sdp, pWinData->inf_at_data.StereoFlags, nMode, bIsotopic, nNumTautComponents );
    }

    pWinData->at0   =(inp_ATOM *)inchi_calloc(num_at+1, sizeof(pWinData->at0[0]));
    pWinData->at1   =(inp_ATOM *)inchi_calloc(num_at+1, sizeof(pWinData->at1[0]));
    pWinData->nFontSize = dp->sdp.nFontSize;
    if ( !pWinData->at0 || !pWinData->at1 ) {
        FreeWinData( pWinData );
        inchi_free(pWinData);
        return NULL;
    }
    memcpy( pWinData->at0, at, sizeof(pWinData->at0[0])*num_at );
    memcpy( pWinData->at1, at, sizeof(pWinData->at0[0])*num_at );

    pWinData->num_at      = num_at;
    pWinData->bOrigAtom   = dp->sdp.bOrigAtom;
    pWinData->nTimerId    = 0;
    pWinData->ulDisplTime = dp->sdp.ulDisplTime;
    if ( dp->sdp.tdp ) {
        pWinData->tdp = *dp->sdp.tdp;
    }
    pWinData->szTitle = NULL;

    return pWinData;
}
//////////////////////////////////////////////////////////////////////
MY_WINDOW_DATA * DupWinData( const MY_WINDOW_DATA * pWinData)
{
    int nSize;
    MY_WINDOW_DATA * pNewData = NULL;
    if( pWinData == NULL )
        return NULL;

    pNewData = (MY_WINDOW_DATA *) inchi_malloc(sizeof(MY_WINDOW_DATA));
    *pNewData = *pWinData;

    nSize = pWinData->num_at*sizeof(inp_ATOM);
    pNewData->at0 = (inp_ATOM *) inchi_malloc(nSize);
    pNewData->at1 = (inp_ATOM *) inchi_malloc(nSize);
#if( DISPLAY_EQU_COMPONENTS == 1 )
    if ( pWinData->nEquLabels ) {
        int nSizeEqu = (pWinData->num_at + 1) * sizeof(AT_NUMB);
        if ( pNewData->nEquLabels = (AT_NUMB *)inchi_malloc( nSizeEqu ) ) {
            memcpy( pNewData->nEquLabels, pWinData->nEquLabels, nSizeEqu - sizeof(AT_NUMB));
            pNewData->nEquLabels[pWinData->num_at] = 0;
        }
    }
#endif
    memcpy(pNewData->at0, pWinData->at0, nSize);
    memcpy(pNewData->at1, pWinData->at1, nSize);

    //memset(&pNewData->inf_at_data, 0, sizeof(pNewData->inf_at_data));
    DuplicateInfoAtomData( &pNewData->inf_at_data, &pWinData->inf_at_data);
    if ( pWinData->szTitle ) {
        pNewData->szTitle = _strdup(pWinData->szTitle);
    }

    return pNewData;

}


////////////////////////////////////////////////////////////////////////////
int Initialize_(int argc, char * argv[], struct INChIParams * ichi_params )
{
//	int i,k;

//	memset(ichi_params, 0, sizeof(struct INChIParams));


    inchi_ios_init(&ichi_params->inp_file, INCHI_IOSTREAM_FILE, NULL);
    inchi_ios_init(&ichi_params->output_file, INCHI_IOSTREAM_FILE, NULL);
    inchi_ios_init(&ichi_params->log_file, INCHI_IOSTREAM_FILE, NULL);
    inchi_ios_init(&ichi_params->prb_file, INCHI_IOSTREAM_FILE, NULL);
    
     

    ReadCommandLineParms( argc, (const char **)argv, &ichi_params->inp_parms, ichi_params->szSdfDataValue, &ichi_params->ulDisplTime, 1, NULL );




    if ( !OpenFiles( &ichi_params->inp_file.f, &ichi_params->output_file.f, &ichi_params->log_file.f, &ichi_params->prb_file.f, &ichi_params->inp_parms ) ) {
        goto error;
    }
    if ( ichi_params->inp_parms.bNoStructLabels ) {
        ichi_params->inp_parms.pSdfLabel = NULL;
        ichi_params->inp_parms.pSdfValue = NULL;
    } else
    if ( ichi_params->inp_parms.nInputType == INPUT_INCHI_XML || ichi_params->inp_parms.nInputType == INPUT_INCHI_PLAIN || ichi_params->inp_parms.nInputType == INPUT_CMLFILE ) {
        if ( !ichi_params->inp_parms.pSdfLabel ) 
            ichi_params->inp_parms.pSdfLabel  = ichi_params->inp_parms.szSdfDataHeader;
        if ( !ichi_params->inp_parms.pSdfValue )
            ichi_params->inp_parms.pSdfValue  =ichi_params->szSdfDataValue;
    }

    PrintInputParms( &ichi_params->log_file, &ichi_params->inp_parms );
    
    if ( !(ichi_params->pStr = (char*)inchi_malloc(NSTRLEN))) {
        /*my_fprintf( ichi_params->log_file, "Cannot allocate output buffer. Terminating\n");*/
        inchi_ios_print(&ichi_params->log_file, "Cannot allocate output buffer. Terminating\n");
        goto error;
    }
    return 1;
error:
    CleanUp_(ichi_params);
    return 0;
}

void CleanOneStructData_(struct INChIParams * ichi_params)
{
    if(ichi_params == NULL)
        return;
    FreeAllINChIArrays( ichi_params->pINChI, ichi_params->pINChI_Aux, ichi_params->struct_data.num_components );
    FreeOrigAtData( &ichi_params->OrigAtData );
    FreeOrigAtData(  &ichi_params->PrepAtData[0] );
    FreeOrigAtData(  &ichi_params->PrepAtData[1] );

}

void CleanUp_(struct INChIParams * ichi_params)
{
    int i;


    if(ichi_params == NULL)
        return;


    if ( (ichi_params->inp_parms.bINChIOutputOptions & INCHI_OUT_XML) != 0 && ichi_params->struct_data.bXmlStructStarted > 0 ) {
        if ( !OutputINChIXmlStructEndTag( &ichi_params->output_file, ichi_params->pStr, NSTRLEN, 1 ) ) {
            /* my_fprintf( ichi_params->log_file, "Cannot create end xml tag for structure #%ld%s%s%s%s. Terminating.\n", ichi_params->num_inp, SDF_LBL_VAL(ichi_params->inp_parms.pSdfLabel,ichi_params->inp_parms.pSdfValue) ); */
            inchi_ios_print( &ichi_params->log_file, "Cannot create end xml tag for structure #%ld%s%s%s%s. Terminating.\n", ichi_params->num_inp, SDF_LBL_VAL(ichi_params->inp_parms.pSdfLabel,ichi_params->inp_parms.pSdfValue) );
            ichi_params->struct_data.bXmlStructStarted = -1; // do not repeat same message
        }
    }

    if ( (ichi_params->inp_parms.bINChIOutputOptions & INCHI_OUT_XML) != 0 && ichi_params->inp_parms.bXmlStarted ) {
        OutputINChIXmlRootEndTag( &ichi_params->output_file );
        ichi_params->inp_parms.bXmlStarted = 0;
    }


//    FreeAllINChIArrays( ichi_params->pINChI, ichi_params->pINChI_Aux, ichi_params->struct_data.num_components );
//    FreeOrigAtData( &ichi_params->OrigAtData );
//    FreeOrigAtData(  &ichi_params->PrepAtData[0] );
//    FreeOrigAtData(  &ichi_params->PrepAtData[1] );
    CleanOneStructData_(ichi_params);
#if( ADD_CMLPP == 1 )
        /* BILLY 8/6/04 */
       /* free CML memory */
        FreeCml ();
        FreeCmlDoc( 1 );
#endif
    if( ichi_params->Fptrs.fptr != NULL )
        inchi_free(ichi_params->Fptrs.fptr);

    if ( ichi_params->inp_file.f ) {
        fclose ( ichi_params->inp_file.f );
    }
    if ( ichi_params->prb_file.f ) {
        fclose ( ichi_params->prb_file.f );
    }
    if ( ichi_params->output_file.f && ichi_params->output_file.f != stdout ) {
        fclose( ichi_params->output_file.f );
    }
/*
    { // block
        int hours, minutes, seconds, mseconds;
        SplitTime( ulTotalProcessingTime, &hours, &minutes, &seconds, &mseconds );
        my_fprintf( log_file, "Finished processing %d structure%s: %ld error%s, processing time %d:%02d:%02d.%02d\n",
                                num_inp, num_inp==1?"":"s",
                                num_err, num_err==1?"":"s",
                                hours, minutes, seconds,mseconds/10);
    }
*/
    if ( ichi_params->log_file.f && ichi_params->log_file.f != stderr ) {
        fclose( ichi_params->log_file.f );
    }

    if ( ichi_params->pStr ) {
        inchi_free( ichi_params->pStr );
    }

    for ( i = 0; i < MAX_NUM_PATHS; i ++ ) {
        if ( ichi_params->inp_parms.path[i] ) {
            inchi_free( (void*) ichi_params->inp_parms.path[i] ); // cast removes 'const'
            ichi_params->inp_parms.path[i] = NULL;
        }
    }

}


#endif /* INCHI_LIB */


