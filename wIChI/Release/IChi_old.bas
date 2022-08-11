function Main as String
Dim FileName as String
	IF ActiveDocument.ActivePage.Diagrams.Count > 0 then
		FileName = GetTempFileName
		Open FileName Access write as #1
		ExportPage(ActiveDocument.ActivePage) 
		Close #1
		ExecApp("wIChI.exe " + Chr(34) + FileName + Chr(34), eaf_Normal OR eaf_Async)
		Main = "OK"
	else
		Main = "Empty Page"
	endif
End Function


sub ExportPage(CurPage as object)
Dim Bond, Atom1, Atom2 as object
Dim Atoms, Mol, Conf, Struct, Diag as object
Dim Atoms1, Struct1 as object
Dim DiagNum as integer
Dim TempStr, RecStr as string
Dim i as integer
Dim MolWeight as double	

	DiagNum = CurPage.Diagrams.Count
	Atoms = Assemblies.AddEmpty
	Mol = Atoms.Molecules.AddEmpty
	Conf = Atoms.Conformations.AddEmpty
	Struct = Atoms.Structures.Derive(Mol,Conf)
	
	
	For Each Diag in CurPage.Diagrams
		Atoms1 = Assemblies.AddFromCS(Diag)
		if Atoms1 <> NULL then
			Struct1 = Atoms1.Structures.Derive(Atoms1.Molecules.Item(1), Atoms1.Conformations.Item(1))
			Atoms.Merge(Struct1)
		end if
	next Diag

	Mol = Atoms.Molecules.Item(1)
	Conf = Atoms.Conformations.Item(1)
	
	'Open FName Access write as 1
	RecStr = ""
	print #1, RecStr
	RecStr = "  -ICHI-"
	print #1, RecStr
	RecStr = ""
	print #1, RecStr
	RecStr = BuildCountsLine(Atoms)
	print #1, RecStr
	BuildAtomBlock(Atoms)
	BuildBondBlock(Atoms, Mol)
	BuildPropertiesBlock(Atoms)
	
	Kill(Atoms)
	Kill(Atoms1)
end sub

function BuildCountsLine(Atoms as object) as String
Dim Mol as object
Dim TempStr as string
Dim i, NProp as integer
Dim Atom as object
	
	TempStr = ""
	TempStr = TempStr + AddSpaces(Str(Atoms.Count), 3)
	Mol = Atoms.Molecules.Item(1)
	TempStr = TempStr + AddSpaces(Str(Mol.Count), 3)
	TempStr = TempStr + "  0  0  0  0  0  0  0  0"
	NProp = 0
	'NProp - 
	for each Atom in Atoms
		if Atom.GetCharge <> 0 then NProp = 1
	next Atom
	TempStr = TempStr + AddSpaces(Str(NProp), 3)

	BuildCountsLine = TempStr
end function

function AddSpaces(ByVal s as string,ByVal n as integer)as string
Dim i as integer
Dim TempStr as string
	TempStr = ""
	for i = 1 to n-Len(s)
		TempStr = TempStr + " "
	next i
	AddSpaces = TempStr + s
end function

function GetTypeOfCharge(ByVal Charge as integer) as integer
Dim n as integer
	select case Charge
		case 3
			n = 1
		case 2
			n = 2
		case 1
			n = 3
		case -1
			n = 5
		case -2
			n = 6
		case -3
			n = 7
		case else
		n = 0
	end select
	GetTypeOfCharge = n
end function 

sub BuildAtomBlock(Atoms as object)
Dim Conf, Mol as object
Dim RecStr as string
Dim Point as object
Dim x, y, z as double
Dim n as integer
Dim TempStr as string
Dim Charge as integer
	Conf = Atoms.Conformations.Item(1)
	for each Point in Atoms
		
		Conf.GetAtomXYZ(Point, x, y, z)
		TempStr = FStr(x, 10, 4) + FStr(y, 10, 4) + FStr(z, 10, 4)
		'TempStr = AddSpaces(FStr(x, 10, 4), 10)
	      'TempStr = TempStr + AddSpaces(FStr(y, 10, 4), 10) + AddSpaces(Str(z), 10)
		TempStr = TempStr + AddSpaces(Point.ElSymbol, 3)
		'MessageBox(FStr(x, 10, 4) + Chr(13) + FStr(y, 10, 4) + Chr(13) + FStr(z, 10, 4), "x,y,z=",MBB_OK)
		
		'MessageBox(Point.ElSymbol + Chr(13), "",MBB_OK)
		TempStr = TempStr + "  0"
		Charge = GetTypeOfCharge(Point.GetCharge)
		TempStr = TempStr + AddSpaces(Str(Charge), 3)
		RecStr = TempStr + "  0  0  0"
		'MessageBox(TempStr, "RecStr=", MBB_OK)
		print #1, RecStr
	next Point
	

end sub

sub BuildBondBlock(Atoms as object, Mol as object)
Dim Bond as object
Dim i, n1, n2 as integer
Dim TempStr as string
Dim Atom1, Atom2 as object
Dim RecStr as string
	
	
	for each Bond in Mol
		Atom1 = Bond.Atom1
		Atom2 = Bond.Atom2
		n1 = Atoms.Index(Atom1)
		n2 = Atoms.index(Atom2)
		'MessageBox(Str(n1) + Chr(13) + Str(n2), "n1, n2 =", MBB_OK)
		TempStr = AddSpaces(Str(n1), 3) + AddSpaces(Str(n2), 3)
		TempStr = TempStr + AddSpaces(Str(Bond.GetBondOrder), 3) + "  0"
		if Mol.IsRing(Bond) then
			TempStr = TempStr + AddSpaces(Str(1), 3)
		else
			TempStr = Tempstr + AddSpaces(Str(2), 3)
		end if
		RecStr = TempStr + "  0  0"
		print #1, RecStr
	next Bond
end sub


sub BuildPropertiesBlock(Atoms as object)
Dim Atom as object
Dim CHGStr, tstr as string
Dim i as integer
	tstr = ""
	CHGStr = ""
	i = 0
	for each Atom in Atoms
		if Atom.GetCharge <> 0 then
			tstr = tstr + AddSpaces(Str(Atoms.Index(Atom)), 4) + AddSpaces(Str(Atom.GetCharge), 4)
			i = i+1
		end if
	next Atom
	if i <> 0 then
		CHGStr = "M  CHG" + AddSpaces(Str(i), 3) + tstr
	end if
	if CHGStr <> "" then print #1, CHGStr
end sub
