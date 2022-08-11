# 2019-09-29 InChI diary



### Проверка на отс-ие side effects in s2i && i2s mode of inchi-1



### i2i

OK!





#### 2019-09-26 was

**1051: 'Structure: 21947683 Syntax error (-2) in FIXED_H_SP2 (20)'**



INCHI #102093: THE TWO LINES DIFFER : {pcs.n16.1051.out.log#102093}  {/home/ipl/_ipl/INCHI/ref/data/struct2inchi/pubchem/Pubchem.2019-07/Substance/calc/105/pcs.n16.105.out.log#102093}

'16720735: ; *Conversion failed*'
'16720735: 

; *Conversion failed on component(s) 1(C116H82N10S2)'

110000     INCHI #114857: THE TWO LINES DIFFER : {pcs.n16.1051.out.log#114857}  {/home/ipl/_ipl/INCHI/ref/data/struct2inchi/pubchem/Pubchem.2019-07/Substance/calc/105/pcs.n16.105.out.log#114857}

''

'21952598:  Problems/mismatches: Mobile-H( Hydrogens: Number; Mobile-H groups: Falsely present, Attachment points; Charge(s): Do not match)'







INCHI #114858: THE TWO LINES DIFFER : {pcs.n16.1051.out.log#114858}  {/home/ipl/_ipl/INCHI/ref/data/struct2inchi/pubchem/Pubchem.2019-07/Substance/calc/105/pcs.n16.105.out.log#114858}
'Structure: 21947683 Syntax error (-2) in FIXED_H_SP2 (20)'
'21961256:  Problems/mismatches: Mobile-H( Hydrogens: Number; Mobile-H groups: Falsely present, Attachment points; Charge(s): Do not match)'
INCHI #114859: THE TWO LINES DIFFER : {pcs.n16.1051.out.log#114859}  {/home/ipl/_ipl/INCHI/ref/data/struct2inchi/pubchem/Pubchem.2019-07/Substance/calc/105/pcs.n16.105.out.log#114859}

'21952598:  Problems/mismatches: Mobile-H( Hydrogens: Number; Mobile-H groups: Falsely present, Attachment points; Charge(s): Do not match)'
'21968181:  Problems/mismatches: Mobile-H( Hydrogens: Number; Mobile-H groups: Falsely present, Attachment points; Charge(s): Do not match; Proton balance: Does not match)'





PubChem Subst (PubChem.2019-07)

s2i

`ipl:105#nohup ./idiff -v pcs.n16.105.out /nvme/INCHI/tmp/pcs.n16.1051.out >idiff.pcs.n16.105-1051.txt &`

`276550000     idiff: compare InChI (and only InChI) strings in 2 files.`

`File-1:  'pcs.n16.105.out'`
`File-2:/nvme/INCHI/tmp/pcs.n16.1051.out'`

`All 276556800 InChI lines are identical.`







