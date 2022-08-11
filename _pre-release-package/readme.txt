/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.05 (pre-release)
 * December 20, 2016
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


This package contains InChI Software version 1.05 (Fall 2016) pre-release.

In this version:
+	support for chemical element numbers 113-118 was newly added;
+	experimental support of InChI/InChIKey for simple regular single-strand polymers was implemented;
+	experimental support of large molecules containing up to 32767 atoms was added;
+	ability to read necessary for large molecules input files in Molfile V3000 format was added;
+   	provisional support for extended features of Molfile V3000 was added;
+	InChI API Library was significantly updated; in particular, a novel API procedure for direct 
	conversion of Molfile input to InChI has been added; 
	a whole new set of API procedures for both low and high-level operations 
	(InChI extensible interface, IXA) has been added;
+	the source code was significantly modified in order to ensure multi-thread execution safety of 
	the InChI Library; several minor bugfixes/changes were made and several convenience options 
	were added to the inchi-1 executable.

InChI Software binaries are placed in the file/directory INCHI-1-BIN. 
Example data files are placed in the file/directory INCHI-1-TEST.  
Documentation is placed in the file/directory INCHI-1-DOC. 
InChI Software source codes are placed in the file/directory INCHI-1-SRC. 
This file/directory also contains examples of InChI API usage