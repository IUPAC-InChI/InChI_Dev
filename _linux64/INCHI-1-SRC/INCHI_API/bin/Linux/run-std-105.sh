for s1 in *.sdf.gz; nohup do gunzip -c $s1 >s0; ./mol2inchi s0 -AuxNone >$s1.std01-mol2inchi-105.out 2>$s1.std01-mol2inchi-105.log &; done
#for s1 in *.sdf.gz; do gunzip -c $s1 >s0; ./inchi-1 s0 $s1.std02.out $s1.std02.log NUL -AuxNone  -NEWPSOFF -NoLabels; done
#for s1 in *.sdf.gz; do gunzip -c $s1 >s0; ./inchi-1 s0 $s1.std03.out $s1.std03.log NUL -AuxNone  -SNon -NoLabels; done
#for s1 in *.sdf.gz; do gunzip -c $s1 >s0; ./inchi-1 s0 $s1.std04.out $s1.std04.log NUL -AuxNone  -DoNotAddH -NoLabels; done
#for s1 in *.sdf.gz; do gunzip -c $s1 >s0; ./inchi-1 s0 $s1.std05.out $s1.std05.log NUL -AuxNone  -SNon -DoNotAddH -NoLabels; done

