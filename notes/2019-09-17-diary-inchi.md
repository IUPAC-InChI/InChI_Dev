# 2019-09-17 InChI diary



### Проверка наново - все already fixed GAF cases

!--artifacts_138348357 



++artifacts_122005605

++artifacts_121309563

++artifacts_121366318

++artifacts_135166097

++artifacts_135243886

++artifacts_135324276

++artifacts_135743168

++artifacts_68416606

++artifacts_68416629

++artifacts_71433868

++artifacts_121241443

++artifacts_121242394

++artifacts_121411204

++artifacts_122094700

++artifacts_135242226

++artifacts_135364611

++artifacts_135667733

++artifacts_121177317

++artifacts_121177636

++artifacts_121178023

++artifacts_121178205



artifacts_121178328

artifacts_121188025

artifacts_121239214

artifacts_121306931

artifacts_121309788

artifacts_121310254

artifacts_121369168

artifacts_121413238

artifacts_121413377

artifacts_121440590

artifacts_121467906

artifacts_121468096

artifacts_122000973

artifacts_122003711

artifacts_122030138

artifacts_122030749

artifacts_122031871

artifacts_122222822

artifacts_122250109

artifacts_122772838

artifacts_122873684

artifacts_123172724

artifacts_123199585

artifacts_123460889

artifacts_123656154

artifacts_124247429

artifacts_124289468

artifacts_129177091

artifacts_135165948

artifacts_135165968

artifacts_135170448

artifacts_135243949

artifacts_135318361

artifacts_135323798

artifacts_135366724

artifacts_135367768

artifacts_135415153

artifacts_135492702

artifacts_135493387

artifacts_135507254

artifacts_135595875

artifacts_135595884

artifacts_135596185

artifacts_135667951

artifacts_135670214

artifacts_135742406

artifacts_135742601

artifacts_135828123

artifacts_135828898

artifacts_138428153

artifacts_68417098

artifacts_68417312

artifacts_68499099

artifacts_71433866

artifacts_71467641

artifacts_71467645



### Проверка на отс-ие side effect in i2s mode of inchi-1

run-i2s-1051.cmd 

inchi-1.exe pcs_ran5m.n16.1051.out /inchi2struct /FixedH /RecMet

then

idiff -v -n pcs_ran5m.n16.1051.out.txt pcs_ran5m.n16.105.out.txt 



@ 12:45 Fixed fixes FIX_GAF_71433868 FIX_GAF_122005605 which caused side effects in i2s mode of inchi-1









### Поиск источника side effects in i2s mode of inchi-1

Это 

++++ FIX_GAF_71433868 (7584)

++++ FIX_GAF_122005605 (8295)





==========================







ichirvr1

---- FIX_GAF_138348357



ichimak2

---- FIX_GAF_138348357

ichiread

++++ FIX_GAF_71433868 (7584)

++++ FIX_GAF_122005605 (8295)





---- (no cure) CHECK_STRTOL_ATNUMB

---- DISABLE_READ_COMPRESSED_INCHI

-- FIX_GAF_122001779

-- FIX_GAF_135667733_GAF_121241443

-- FIX_GAF_121411204

-- FIX_GAF_68416606_GAF_135367768

--FIX_GAF_122094700 (5821)

-- FIX_GAF_68416629_GAF_121242394_GAF_135364611 (5906)

-- FIX_GAF_122005605 (6207)

-- FIX_GAF_121366318_GAF_135324276 (6329)

----FIX_GAF_135743168 (7870)

-- FIX_GAF_135242226_GAF_121309563_GAF_135166097 (8897)



