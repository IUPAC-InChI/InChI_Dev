# GetINCHI()

GetINCHI()
{...}

static int GetINCHI1( inchi_InputEx *extended_input,
                      inchi_Output *out,
                      int bStdFormat)
{

...
	set and populate 
		STRUCT_DATA *sd = &struct_data
		INPUT_PARMS *ip = &inp_parms
	  	CANON_GLOBALS CG
	    INCHI_CLOCK ic

	    inchi_ios_init(out_file, INCHI_IOSTREAM_TYPE_STRING, NULL);
	    inchi_ios_init(log_file, INCHI_IOSTREAM_TYPE_STRING, NULL);
	    inchi_ios_init(prb_file, INCHI_IOSTREAM_TYPE_STRING, NULL);


	ORIG_ATOM_DATA OrigAtData; /* 0=> disconnected, 1=> original */
    ORIG_ATOM_DATA *orig_inp_data = &OrigAtData;
    ORIG_ATOM_DATA PrepAtData[2]; /* 0=> disconnected, 1=> original */
    ORIG_ATOM_DATA *prep_inp_data = PrepAtData;

	clearing
		    /* clear original input structure */
	    memset( pINChI,     0, sizeof(pINChI    ) );
	    memset( pINChI_Aux, 0, sizeof(pINChI_Aux) );
	    memset( sd,         0, sizeof(*sd) );
	    memset( ip,         0, sizeof(*ip) );
	    memset( orig_inp_data     , 0,   sizeof( *orig_inp_data  ) );
	    memset( prep_inp_data     , 0, 2*sizeof( *prep_inp_data  ) );
	    memset( szSdfDataValue    , 0, sizeof( szSdfDataValue    ) );

	    memset( &CG, 0, sizeof(CG));
	    memset( &ic, 0, sizeof(ic));

	    if ( !out ) {
	        nRet = _IS_ERROR;
	        goto exit_function;
	    }
	    memset( out, 0, sizeof(*out) );

	    ..
	    	ReadCommandLineParms( argc, argv, ip, szSdfDataValue, &ulDisplTime, bReleaseVersion, log_file );

			/***************************************************
		    /*  Main cycle                                     */
		    /*  read input structures and create their INChI's */
		    ulTotalProcessingTime = 0;
  			if ( !sd->bUserQuit && !bInterrupted )
    		{
    			....

				nRet = ExtractOneStructure( sd,
                                    ip,
                                    szTitle,
                                    extended_input,
                                    log_file,
                                    out_file,
                                    prb_file,
                                    orig_inp_data,
                                    &num_inp );

				...
				/* Create INChI for each connected component of the structure and optionally display them */
        /* output INChI for the whole structure */
        nRet1 = ProcessOneStructureEx( &ic, &CG, sd, ip, szTitle,
                                       pINChI, pINChI_Aux,
                                       NULL, /* inp_file is not necessary as all input is already saved in 'ip' */
                                       log_file, out_file, prb_file,
                                       orig_inp_data, prep_inp_data,
                                       num_inp, strbuf,
                                       0 /* save_opt_bits */);

        /*  Free INChI memory */
        FreeAllINChIArrays( pINChI, pINChI_Aux, sd->num_components );

        /* Free structure data */
        FreeOrigAtData( orig_inp_data );
        FreeOrigAtData( prep_inp_data );
        FreeOrigAtData( prep_inp_data+1 );

        ulTotalProcessingTime += sd->ulStructTime;
        nRet = inchi_max(nRet, nRet1);
        switch ( nRet ) {
        case _IS_FATAL:
            /* num_err ++; */
            goto exit_function;
        case _IS_ERROR:
            ; /* num_err ++; */
#ifndef TARGET_API_LIB
            continue;
#endif
        }
    }

	exit_function:
		frees & clears...
		...
	    /* output */
	    produce_generation_output( out, sd, ip, log_file, out_file );

	translate_RetVal:

	    /* Close inernal I/O streams */
	    inchi_ios_close(log_file);
	    inchi_ios_close(out_file);
	    inchi_ios_close(prb_file);

	    switch (nRet)
	    {
			...
		}		

    		}
    
  
}





09:40 8%
09:41 17%
09:45 33%
10:00 76%


