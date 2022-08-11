function Main as String
Dim FileName as String
Dim FileName2 as String
Dim Count as Integer
Dim diagram as object
Dim Str as String
Dim Done as Boolean

	Count = ActiveDocument.ActivePage.Diagrams.Count
	FileName = GetTempFileName
	IF Count > 1 then
		Open FileName Access write as #1
		FileName2 = GetTempFileName
	      For Each diagram In ActiveDocument.ActivePage.Diagrams
			diagram.ExportToMol(FileName2)
			Open FileName2 Access read as #2
  			eof #2, Done
			while not Done
    				Read #2, Str, 128
    				eof #2, Done
    				if not Done	then Print #1, Str
  			end while
			close #2
			DeleteFile(FileName2)  
			Print #1, "$$$$"
	      Next diagram
		close #1		
		ExecApp("wIChI.exe " + Chr(34) + FileName + Chr(34) + " /merge", eaf_Normal OR eaf_Async)
		Main = "OK"
	else 
		IF Count > 0 then
	      	For Each diagram In ActiveDocument.ActivePage.Diagrams
				diagram.ExportToMol(FileName)  
		      Next diagram  
			ExecApp("wIChI.exe " + Chr(34) + FileName + Chr(34), eaf_Normal OR eaf_Async)
			Main = "OK"
		else
			Main = "Empty Page"
		endif
	endif	
End Function


