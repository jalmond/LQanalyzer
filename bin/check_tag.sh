#! /bin/sh                                                                                                                                                                                                                                                                      

while read line
do
    if [[ $line == $CATTAG* ]];
    then
        echo "Current tag is buggy. Please update to newer tag."
        exit
    fi
done < $buglist


export LIBTAG=""
if [[ $1 != "" ]];then

    export CHECKTAGFILE=/data1/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
    then
        export CHECKTAGFILE=/data2/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    else
        export CHECKTAGFILE=/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    fi
    if [[ ! -f $CHECKTAGFILE ]]; then
        export LQANALYZER_DIR=""
        echo $1 "is not allowed input. Use one of:"

        if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
        then
            source /data2/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh
        elif [ $HOSTNAME == "ui"* ];
        then
            source /cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh
        else
            source /data1/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh

        fi
        for ic in  ${list_of_catversions[@]};
        do
            echo $ic
        done
        return 1
    fi

    source $CHECKTAGFILE Tag
    export LIBTAG=$CATVERSION
fi
