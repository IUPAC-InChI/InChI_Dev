# Generic algorithm for polymers in InChI

## 0. Concepts, terms, scope and limitations

We call 'letftnost' and 'rightmost' atoms of polymer unit '*SRU ends*' and their terminals - which lie outside unut - '*SRU caps*'.

The algorithm below is for a single structure.

This applies to:

* inchi-1 code
  	from within CalcAndPrintINCHIAndINCHIKEY()

* InChI API (classic) functions 
  	GetINCHIEx() and GetINCHI()

* InChI API function
  	MakeINCHIFromMolfileText()

* InChI API function
  	IXA_INCHIBUILDER_GetInChI()

InChI "classic modularized" (step-by-step generation, INCHIGEN-based) API does not support polymers.

## 1. Generic stetting up

Note that all code roads (classic GetINCHI API, IXA API, mol2inchi API, and inchi-1 monolite code) related to Structure --> InChI generation  lead to the 
`ProcessOneStructureEx()`

The one and only exception is classic 'modularized' API which does not handle polymers at all, intentionally (too much effort is necessary to adjust this case to polymers).

The function 

### Legacy way of v. 1.05 

 *(as it is implemented in POLYMERS105 mode as of 2020-02-02)*

* In `ProcessOneStructureEx()`

    Make preliminary check  for valid polymer data:

  * check if `orig_inp_data->polymer !=NULL`
  * check if `ip->bPolymers!=0`  and set 
    `orig_inp_data->valid_polymer` correspondingly


* Call `ProcessOneStructureExWorker()` which is a real worker, and there check if we  have to mind_polymers or mind_pseudoelements;

  if yes, do in `OAD_ValidatePolymerAndPseudoElementData()`
  { 

  * Assign polymer type and subunits type and polymer data for self-consistency 

  * Check each CRU
    * Check if unit data are consistent
    * By calling function
      `OAD_PolymerUnit_FindEndAtomsAndCaps()`
      * Reveal and store CRU caps and ends ('stars and partners')
      * Also set there
        `unit->cap1_is_undef`, `unit->cap2_is_undef`, 
        `unit->cyclizable`
    * Set possibly missing unit parameters
  * Call `OAD_ValidateAndSortOutPseudoElementAtoms()` where
    * Make more polymer and pseudoatom data checks
    * Convert both "*" and "Zz" temporarily to "Zy" (polymer-unrelated internal pseudoatoms)
    * If applicable, check each CRU and back-convert "Zy" to "Zz" (polymer-related pseudoelement atoms) if they are for valid biundef-end CRU
  * Make more polymer and pseudoatom data checks
    * Check if non-polymer-related Zz/star atoms enabled 
  * Allocate polymer-related pseudoatoms memory
    `orig_at_data->polymer->pzz`
  * Specifically, check copolymers and ensure that COP includes > 1 SRU
  * Call `OAD_Polymer_GetRepresentation()`
  * Make more polymer data checks and perform some corrections
    For each CRU
    * Check that there are no H end groups
    * Ensure that caps of polymer unit lie outside it
    * Set CRU closure type `u->cyclizable` 
      **(repeatingly?!? and where is check for bi-undef here?!)** 
      and allocate PS (frame-shiftable) bonds `u->links`

  }  `OAD_ValidatePolymerAndPseudoElementData()` ends here
  
* If applicable,  analyze and modify canonical CRU using InChI's cano nums  via `OAD_Polymer_CyclizeCloseableUnits()`
  
* Call `ProcessOneStructure()`

* In `ProcessOneStructure()`

  * If polymer structure is being restored from InChI string
  * if CRUs were pre-cyclized, re-open them in preferred forms here, calling `OAD_Polymer_SmartReopenCyclizedUnits()`
  * `OrigAtData_SaveMolfile()`
  * `OrigAtData_StoreNativeInput()`
  * Create INChI for the whole disconnected or original structure
    `CreateOneStructureINChI()`
  * If we create InChI from polymer-containing structure 
    * `OAD_Polymer_GetRepresentation()`
    * `OAD_Polymer_CollectLinksInAllUnits()`
      For each cyclizable CRU
      * Collect all bonds of main chain(s), side chains being ignored (these bonds potentially may be involved in SRU's frame shift). Call the function `OAD_PolymerUnit_CollectLinks()`
        * `subgraf_new()`
        * `subgraf_pathfinder_new()`
        * `subgraf_pathfinder_run()`
      * `OAD_PolymerUnit_DelistIntraRingLinks()`
      * `OAD_PolymerUnit_DelistHighBondOrderLinks()`
      * `subgraf_free()`
      * `subgraf_pathfinder_free()`
*  Create INChI for the whole metal-reconnected structure 
    `CreateOneStructureINChI()`
  * If we create InChI from polymer-containing structure 
    * `OAD_Polymer_CollectLinksInAllUnits()`
  * `SortAndPrintINChI()`
    * `OutputINChI2()`
      * `OutputINChI1()`
        * Analyze layers, make adjustments and fixes, etc.
        * Make InChI string
          * ...
          * `OutputINCHI_PolymerLayer()`
          * ...
        * Make AuxInfo
          * ...
      * `EditINCHI_HidePolymerZz()`
    * 
  * `DisplayOrigAndResultStructuresAndComponents()`
  * `SaveOkProcessedMolfile()`





Assign CRU types, their atoms, etc.

For bistar-CRU
{ 
	select ends, their caps
}

For bistar-CRU
{ 
	connect ends, disconnect stars and make them Zz
}

Calculate InChI for non-polymeric skeleton

Print InChI with added polymer /z layer
In /z layer
{ 
	hide ZZ
}

, for bistar-SRU
{
	sort all links in min-at-number order using `IsBondAtomNumsLesser()`
}

### Current way of v. 1.06



1.1 

if we are within GetINCHIEx() function
	forcibly supply to code below the option options '*LargeMolecules*', '*Polymers*'
    if no Zz-related option is supplied, supply to code below the option '*ZZ106*' 
if we are within GetINCHI function()
	supply to code below the option '*ZZNo*' 
	and do not supply options '*LargeMolecules*', '*Polymers*'
	(to ensure compatibiliy with <= v. 1.04)

1.2

now, in any context, check these option switches and set corresponding flags 

...

## 2. Preprocess pseudoelement and polymer stuff

check if there are  *Zy*  atoms 
	(which are disabled externally, on any input;
	we may not postpone this check to the code below, as to that moment *Zy*'s
	may legally appear due to conversion from non-polymeric *Zz*)
{
	if they are present
		signal on error and exit
}

check if there are  * or *Zz*  atoms
if they are present
{
	if *ZZFlag* is '*ZzNo*' 
		signal on error and exit
	convert all * to *Zz*
}

for each *Zz* 
{
	if *PolymerFlag* is OFF
	{
		if *ZZFlag* is not *ZZ106* (or *ZZYes*)
			signal on error and exit
		else
			convert this  *Zz* to *Zy* 
			(i.e., we will treat any pseudoatom as generic placeholder 
			ignoring its polymer context)
	}
	else (here *PolymerFlag* is ON)
		only if current *Zz* does not sit at polymer bracket
			convert this  *Zz* to *Zy*
}

Now *Zz*  marks polymer-related pseudoatoms, and *Zy* - generic placeholders.

Calculate total numbers *nZz* and *nZy*.

if  *PolymerFlag* is OFF and *nZz*>0 
		signal on error and exit
		(we should not get there)

## 3. Calculate a preliminary non-polymeric InChI (may have Zz, Zy)

## 4. Prepare and make SRU simplification(s)

if applicable
TODO
(Sayle issue#1)


for each eligible SRU
{

### 	4.1. Prepare SRU simplification

### 	4.2. Edit input structure: make SRU simplification

}

## 5. Re-calculate a preliminary InChI, if necessary



## 6. Prepare and make frame shift(s) for double-ZZ SRU's

6.1. if *nZz*<1
			skip this step

### 6.2. Analyze frame shift possibilities

for each polymer unit having two *Zz* ends
{
	check unit type 
   {
		select main chain from left to right end 
			*how this chain is defined and how it is searched for??*
		if the chain is of 1 atom 
			mark this (it is a special case: no frame shift is applicable) 
			goto processing the next eligible polymer unit
		if the chain is of 2 atoms
			mark this (it is a special case: no frame shift is applicable)
			goto processing the next eligible polymer unit
		else
		{
			select breakable bonds - they are the bonded atoms which may be 
			alternative to current (input one) pair of SRU end atoms
			...
		}

​		...
​	
​	}

​	...
} 

### 6.3. Make frame shift(s)

for each eligible SRU
{

#### 	6.3.1. Edit polymer-related part of structure

#### 	6.3.2. Make frame shift

}

## 7. Calculate interim InChI (no polymeric stuff involved directly), if applicable

## 8. Prepare and make frame shift(s) for def-end SRU's

TODO
(Sayle issue#2)

...

## 998. Produce and output final InChI string 

SortAndPrintINChI --> OutputINChI2 --> OutputINChI1 

--> OutputINCHI_PolymerLayer

with polymer-related post-processing if applicable

for each polymer unit which does not have two *Zz* ends
{
		...
}

for each polymer unit having two *Zz* ends
{
		...
}

for each *Zz* in output InChI string 
	convert *Zy* to *Zz* 

update brutto-formula correspondingly



## 999. Produce and output final AuxInfo string

for each polymer unit which does not have two *Zz* ends
{
		...
}

for each polymer unit having two *Zz* ends
{
		...
}

## 