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


#ifdef INCHI_LIB

#ifndef __INCHI_LIB_H__
#define __INCHI_LIB_H__


#include "mode.h"
#include "ichi.h"
#include "inpdef.h"
#include "dispstru.h"
#include "ichierr.h"
#include "ichimain.h"
#include "util.h"
#include "ichi_io.h"

#define NSTRLEN  64000

struct 	INChIParams
{
    unsigned long	ulDisplTime;
    long			fPtrStart, fPtrEnd;
    long			num_inp;
    int				nErrorCode, num_non_taut, num_taut;
    char			szSdfDataValue[MAX_SDF_VALUE+1];
    char *			pStr;
    /*FILE			*inp_file, *output_file, *log_file, *prb_file;*/
    INCHI_IOSTREAM  inp_file, output_file, log_file, prb_file; 
    PINChI2			*pINChI[INCHI_NUM];
    PINChI_Aux2		*pINChI_Aux[INCHI_NUM];

    INPUT_PARMS		inp_parms;
    ORIG_ATOM_DATA	OrigAtData;
    ORIG_ATOM_DATA  PrepAtData[2]; /* 0=> disconnected, 1=> reconnected */
    STRUCT_DATA     struct_data;
    char			szTitle[MAX_SDF_HEADER+MAX_SDF_VALUE+256];
    STRUCT_FPTRS	Fptrs;

};

enum {COMPONENT_ORIGINAL, COMPONENT_ORIGINAL_PREPROCESSED ,COMPONENT_BN, COMPONENT_BI, COMPONENT_TN, COMPONENT_TI };

struct DrawData
{
    int				nComponent; // 0 - original structure
    int				nType;       // should be 0 if nComponent == 0
    int				bReconnected; // 0=>main; 1=>reconnected
    MY_WINDOW_DATA*	pWindowData;
    char*			szTitle;
};

typedef struct DrawData * DRAW_DATA_AR[6];

#ifndef ALL_CPP
#ifdef  __cplusplus
extern "C" {
#endif
#endif

void FreeDrawData( struct DrawData * pDrawData );
MY_WINDOW_DATA * CreateWinData_( inp_ATOM *at, int num_at, int num_removed_H, int bAdd_DT_to_num_H, int num_removed_protons,
                                NUM_H *nNumRemovedProtonsIsotopic, int bIsotopic, int bTautomeric,
                                INChI **cur_INChI, INChI_Aux **cur_INChI_Aux,
                                int bAbcNumbers, DRAW_PARMS *dp, INCHI_MODE nMode );
MY_WINDOW_DATA * CreateWinDataComposite_( COMP_ATOM_DATA *composite_norm_data, int bIsotopic, int bTautomeric,
                                         PINChI2 *pINChI2, PINChI_Aux2 *pINChI_Aux2,
                                         int bAbcNumbers, DRAW_PARMS *dp, INCHI_MODE nMode);
MY_WINDOW_DATA * DupWinData( const MY_WINDOW_DATA * pWinData);

void CleanOneStructData_(struct INChIParams * ichi_params);
void CleanUp_(struct INChIParams * ichi_params);
int Initialize_(int argc, char * argv[], struct INChIParams * ichi_params );

#ifndef ALL_CPP
#ifdef  __cplusplus
 }
#endif
#endif


#endif

#endif
