#!/bin/sh

### setup paths to be used in analysis code
export MAINDIR=$PWD/../
export ANALYSISDIR=$PWD/../src/
export INCLUDEDIR=$PWD/../
export INCLUDEDIR_snu=$PWD/../SNUTree/include/
export OUTDIR=$PWD/../output/

dir=rootfiles/
export FILEDIR=$ANALYSISDIR/$dir

echo "Running analysis from" $HOSTNAME " in directory " $ANALYSISDIR
source setup_rootfiles.sh 


ls $FILEDIR/*.root > /dev/null
if [ $? -ne 0 ]
    then
    mkdir $FILEDIR

    $(setup_rootfile_manual $FILEDIR)
    echo "Made directory "  $ANALYSISDIR/$dir " and copied necessary rootfiles for running cms analysis"
    echo ""
else
    echo "... found."
fi
