#!/bin/sh

### setup paths to be used in analysis code
export MAINDIR=$PWD/../
export ANALYSISDIR=$PWD/../src/
export INCLUDEDIR=$PWD/../include/
export INCLUDEDIR_snu=$PWD/../SNUTree/include/
export OUTDIR=$PWD/../output/

dir_to_clean=$1

if [[ dir_to_clean = "--h*" ]]
    then    
    echo "source cleanup.sh : remove all temp files only"
    echo "source cleanup.sh --dl : remove all dependency files and lib files"

    
else
    if [[ dir_to_clean   = "--dl" ]] 
	then 
	
	cd $MAINDIR
	rm */*~
	rm */*.d       
	rm */*_cc*
	rm */*_C*
	cd -
    else 
	cd $MAINDIR
        rm */*~
	cd -
    fi
fi
