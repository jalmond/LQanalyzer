#! /bin/sh                                                                                                                                                                                                                                                                      
export LQANALYZER_MOD="/data1/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    export LQANALYZER_MOD="/data2/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
fi

if [ $HOSTNAME == "ui10.sdfarm.kr" ];
then
    export LQANALYZER_MOD="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
fi

##### Check that this is not the branch and a tag was checked out                                                                                                                                                                                                               

export CHECKTAGFILE=$LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
source $CHECKTAGFILE Tag
source $LQANALYZER_DIR/bin/CheckTag.sh


#### check for buggy tags                                                                                                                                                                                                                                                       
buglist=/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/BuggyTag.txt
if [ $HOSTNAME == "ui10.sdfarm.kr" ];
then
    buglist=/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATTag/BuggyTag.txt
fi

while read line
do
    if [[ $line == $CATTAG* ]];
    then
        echo "Current tag is buggy. Please update to newer tag."
        exit
    fi
done < $buglist

