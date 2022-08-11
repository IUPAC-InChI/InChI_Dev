# Features of v. 1.06

Chiefly, it is a maintenance release which accumulates changes to v. 1.05 of 2017.

1. The most significant functionality enhancement is adding (experimental) support
   of pseudoelement “Zz” atoms. 

   These atoms may be used to mark undefined-nature end groups
   in polymeric repeat units, or they may serve just as generic placeholders
   outside CRU-ends polymeric context, (in this case exact meaning
   of Zz atoms, as well as the rules of treating them, is up to application
   chemist/programmer). 

2. Polymer treatment is updated to fix bugs and
   account for feature requests  (e.g., support of presence of both source-based
   and structure-based subunits in copolymer unit, etc.), as well as to accommodate Zz atoms.

3. Number of less significant functionality extensions has been
   added. 

   For example, added, by users request,  a new
   InChI structure-perception option *LooseTSACheck* relaxes the strictness
   of tetrahedral stereo ambiguity check, for in-ring atoms, thus getting stereo
   descriptor instead of undefined mark ‘?’.  Added, by users request,  new switch *WMnumber* for InChI Library/inchi-1 which sets
   InChI calculation timeout in milliseconds (strictly requires long int number),
   thus adding finer granularity necessary for long runs on multi-million input
   databases. ...

4. Fixed a number of security issues and crashes reported by Google which may have appear on InChI2Struct conversion of illegal (fake) InChI input strings.

5. Many other minor bugfixes and changes are
   introduced. Improved multi-threading support.





