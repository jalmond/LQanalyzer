#!/bin/sh 
function setup_rootfile(){
    declare -a fileList=("MyDataPileupHistogram.root" "Total_FRcorr60_51_bis.root") 
    for file in ${fileList[@]}
      do
      wget http://www.hep.man.ac.uk/u/john/CMS/rootfiles/$file
      mv $file $1
      echo "Copying file:"$file " to "$1
    done
}

function make_clean(){
    export currentdir = $PWD
    cd $MAINDIR/scripts/
    source cleanup.sh -a
    cd $currentdir   

}

function setup_rootfile_manual(){
    
    wget http://www.hep.man.ac.uk/u/john/CMS/rootfiles/MyDataPileupHistogram.root
    mv MyDataPileupHistogram.root $1
    
    wget http://www.hep.man.ac.uk/u/john/CMS/rootfiles/Total_FRcorr60_51_bis.root
    mv Total_FRcorr60_51_bis.root $1


}
