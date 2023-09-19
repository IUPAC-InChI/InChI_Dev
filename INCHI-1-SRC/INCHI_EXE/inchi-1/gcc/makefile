# This will create:
# 32-bit executable under 32-bit Windows and 32-bit Linux,
# or 64-bit executable under 64-bit Linux/AMD64
#
# To make 32-bit executable under 64-bit Linux/AMD64, use makefile32
#
#
#
ifndef C_COMPILER
	C_COMPILER   = gcc
endif
ifndef CPP_COMPILER
	CPP_COMPILER = g++
endif
ifndef LINKER
	LINKER = g++ -s
endif
ifndef INCHI_EXECUTABLE_NAME
	ifdef windir
		EXE = .exe
	else
		EXE =
	endif
	INCHI_EXECUTABLE_NAME = inchi-1$(EXE)
endif
 # === executable directory ===
ifndef BIN_DIR
  BIN_DIR = ../../bin/Linux
endif
INCHI_EXECUTABLE_PATHNAME = $(BIN_DIR)/$(INCHI_EXECUTABLE_NAME)
ifndef P_MAIN
	P_MAIN = ../src
endif
ifndef P_BASE
	P_BASE = ../../../INCHI_BASE/src
endif
#P_INCL = -I$(P_MAIN) -I$(P_BASE)
P_INCL = -I$(P_MAIN) -I$(P_BASE)
C_COMPILER_OPTIONS = $(P_INCL) -std=c11 -ansi -DCOMPILE_ANSI_ONLY -DTARGET_EXE_STANDALONE -O3 -c
#C_COMPILER_OPTIONS = -c $(P_INCL) -ansi -O3 -fsigned-char -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wall -pedantic -Wbad-function-cast -Wreturn-type -Wformat -Wuninitialized -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -Wunused-parameter -Wunused-label -Wcomment -Wcast-qual -Wconversion -Wimplicit-int -Wmissing-braces -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wsign-compare -Wfloat-equal -Wstrict-prototypes -Wwrite-strings -Wundef -Waggregate-return -Wchar-subscripts -Wformat-nonliteral -Wnested-externs -Wsequence-point -Wpointer-arith -mfancy-math-387 -mieee-fp -mno-soft-float
ifdef windir
# no -ansi option due to reported MinGw bug
	CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_EXE_STANDALONE -O3 -frtti -c
	#CPP_COMPILER_OPTIONS = -c $(P_INCL) -D_LIB -O3 -frtti -Wall -pedantic -Wreturn-type -Wformat -Wuninitialized -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -fsigned-char -Wcast-qual -Wconversion -Wmissing-braces -Wredundant-decls -Wsign-compare -Wfloat-equal -Wwrite-strings -mfancy-math-387 -mieee-fp -mno-soft-float
else
	CPP_COMPILER_OPTIONS = $(P_INCL) -D_LIB -DTARGET_EXE_STANDALONE -ansi -O3 -frtti -c
	#CPP_COMPILER_OPTIONS = -c $(P_INCL) -D_LIB -ansi -O3 -frtti -Wall -pedantic -Wreturn-type -Wformat -Wuninitialized -ffunction-sections -fexpensive-optimizations -fstack-check -fexceptions -Wcast-align -Wshadow -Wunused -Wunused-value -Wunused-variable -Wunused-function -fsigned-char -Wcast-qual -Wconversion -Wmissing-braces -Wredundant-decls -Wsign-compare -Wfloat-equal -Wwrite-strings -mfancy-math-387 -mieee-fp -mno-soft-float
endif
#LINKER_OPTIONS = -static-libgcc
#LINKER_OPTIONS = -Wall -Wunused -Wunused-function
INCHI_SRCS = $(P_BASE)/ichi_bns.c	\
$(P_BASE)/ichi_io.c	\
$(P_BASE)/ichican2.c	\
$(P_BASE)/ichicano.c	\
$(P_BASE)/ichicans.c	\
$(P_BASE)/ichierr.c	\
$(P_BASE)/ichiprt3.c	\
$(P_BASE)/ichiisot.c	\
$(P_BASE)/ichimake.c	\
$(P_BASE)/ichiqueu.c	\
$(P_BASE)/ichiring.c	\
$(P_BASE)/ichierr.c	\
$(P_BASE)/ichimap1.c	\
$(P_BASE)/ichimap2.c	\
$(P_BASE)/ichimap4.c	\
$(P_BASE)/ichimak2.c	\
$(P_BASE)/ichinorm.c	\
$(P_BASE)/ichiparm.c	\
$(P_BASE)/ichiprt1.c	\
$(P_BASE)/ichiprt2.c	\
$(P_BASE)/ichirvr1.c	\
$(P_BASE)/ichirvr2.c	\
$(P_BASE)/ichirvr3.c	\
$(P_BASE)/ichirvr4.c	\
$(P_BASE)/ichirvr5.c	\
$(P_BASE)/ichirvr6.c	\
$(P_BASE)/ichirvr7.c	\
$(P_BASE)/ichisort.c	\
$(P_BASE)/ichister.c	\
$(P_BASE)/ichitaut.c	\
$(P_BASE)/ikey_base26.c	\
$(P_BASE)/ikey_dll.c	\
$(P_BASE)/mol_fmt1.c	\
$(P_BASE)/mol_fmt2.c	\
$(P_BASE)/mol_fmt3.c	\
$(P_BASE)/mol_fmt4.c	\
$(P_BASE)/readinch.c	\
$(P_BASE)/runichi.c	\
$(P_BASE)/runichi2.c	\
$(P_BASE)/runichi3.c	\
$(P_BASE)/runichi4.c	\
$(P_BASE)/sha2.c	\
$(P_BASE)/strutil.c	\
$(P_BASE)/util.c	\
$(P_MAIN)/dispstru.c	\
$(P_BASE)/mol2atom.c	\
$(P_MAIN)/ichimain.c	\
$(P_BASE)/bcf_s.c
#
INCHI_OBJS = ichi_bns.o	\
ichi_io.o	\
ichicano.o	\
ichican2.o	\
ichicans.o	\
ichierr.o	\
ichiisot.o	\
ichimake.o	\
ichimak2.o	\
ichimap1.o	\
ichimap2.o	\
ichimap4.o	\
ichinorm.o	\
ichiprt1.o	\
ichiprt2.o	\
ichiprt3.o	\
ichiqueu.o	\
ichiring.o	\
ichisort.o	\
ichister.o	\
ichitaut.o	\
ichiparm.o	\
ichiread.o	\
ichirvr1.o	\
ichirvr2.o	\
ichirvr3.o	\
ichirvr4.o	\
ichirvr5.o	\
ichirvr6.o	\
ichirvr7.o	\
ikey_base26.o	\
ikey_dll.o	\
mol_fmt1.o	\
mol_fmt2.o	\
mol_fmt3.o	\
mol_fmt4.o	\
mol2atom.o	\
readinch.o	\
runichi.o	\
runichi2.o	\
runichi3.o	\
runichi4.o	\
sha2.o	\
strutil.o	\
util.o	\
dispstru.o	\
ichimain.o	\
bcf_s.o	  
$(INCHI_EXECUTABLE_PATHNAME) : $(INCHI_OBJS)
	$(LINKER) $(LINKER_OPTIONS) -o $(INCHI_EXECUTABLE_PATHNAME) $(INCHI_OBJS) -lm
%.o: $(P_BASE)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $<
%.o: $(P_MAIN)/%.c
	$(C_COMPILER) $(C_COMPILER_OPTIONS) $<
%.o: $(P_MAIN)/%.cpp
	$(CPP_COMPILER) $(CPP_COMPILER_OPTIONS) $<
