#!/bin/sh
############################################################                                                                                                                    
################# Do not change anything after this line                                                                                                                        
############################################################                                                                                                                    

if [ -z ${LQANALYZER_DIR} ]
    then
    setupLQANALYZER
fi

#### FULL LIST OF OPTIONS                                                                                                                                                       
stream=$(makeParseVariable 's' ${stream})
njobs=$(makeParseVariable 'j' ${njobs})
cycle=$(makeParseVariable 'c' ${cycle})
data_lumi=$(makeParseVariable 'd' ${data_lumi})
outputdir=$(makeParseVariable 'O' ${outputdir})
logstep=$(makeParseVariable 'o' ${logstep})
skipevent=$(makeParseVariable 'k' ${skipevent})
loglevel=$(makeParseVariable 'l' ${loglevel})
nevents=$(makeParseVariable 'n' ${nevents})
totalev=$(makeParseVariable 'e' ${totalev})
xsec=$(makeParseVariable 'x' ${xsec})
targetlumi=$(makeParseVariable 'T' ${targetlumi})
efflumi=$(makeParseVariable 'E' ${efflumi})
remove=$(makeParseVariable 'w' ${remove_workspace})
skinput=$(makeParseVariable 'S' ${skinput})
runevent=$(makeParseVariable 'R' ${runevent})
useCATv742ntuples=$(makeParseVariable 'N' ${useCATv742ntuples})
LibList=$(makeParseVariable 'L' ${LibList})
useskim=$(makeParseVariable 'm' ${useskim})
runnp=$(makeParseVariable 'P' ${runnp})
runcf=$(makeParseVariable 'Q' ${runcf})
catversion=$(makeParseVariable 'v' ${catversion})
skflag=$(makeParseVariable 'f' ${skflag})
DEBUG=$(makeParseVariable 'D' ${DEBUG})
usebatch=$(makeParseVariable 'b' ${usebatch})

################                                                                                                                                                

########## GET EMAIL                                                                                                                                                                                                              

cat_email=""
while read line
do
    prefix="email = "
    if [[ $line == $prefix* ]];
    then
        line=${line:${#prefix}}
        cat_email=$line
    fi
done < ${LQANALYZER_DIR}/bin/catconfig

runcommand=$1
if [[ $njobs == "-j 1" ]]; then
    runcommand="running single job"
fi


sample_list_string=""
for i in ${input_samples[@]}
do
    sample_list_string+="!!"$i 
done
samplelist=$sample_list_string

if [[ $runcommand  == "" ]]; 
then
    tagger=$RANDOM
    python   ${LQANALYZER_DIR}/python/SubmittionConfig.py  -p ${samplelist} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} ${remove} ${loglevel} ${skipevent} ${nevents} ${totalev} ${xsec} ${targetlumi} ${efflumi}  ${skinput} ${runevent} ${useCATv742ntuples} ${LibList} ${DEBUG} ${useskim} ${runnp} ${runcf} ${catversion} ${skflag} ${usebatch} -X ${tagger} -u $cat_email
    #done
elif [[ $runcommand  == "--help"  || $runcommand  == "--h" ]]; then                 
    echo "Checking options"
    python ${LQANALYZER_DIR}/python/localsubmit.py $1
else 
    for i in ${input_samples[@]}
    do
        tagger=$RANDOM
        statdir="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"$USER
        if [[ ! -d "${statdir}" ]]; then
            mkdir ${statdir}
        fi
	
        logfile=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/$USER/statlog_$i$tagger.txt
        logfile_time=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/$USER/statlog_time_$i$tagger.txt
        echo "user "$USER >> $logfile
        echo $cycle >> $logfile
        echo $catversion >> $logfile
        echo $stream >> $logfile
        echo $njobs >> $logfile
        echo $data_lumi >> $logfile
        echo "sample "$i >>  $logfile
        echo $useskim >> $logfile
        echo "cattag "$CATTAG >> $logfile
        date >> $logfile
        echo "############################" >> $logfile
        python ${LQANALYZER_DIR}/python/localsubmit.py -p ${i} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} ${remove} ${loglevel} ${skipevent} ${nevents} ${totalev} ${xsec} ${targetlumi} ${efflumi} ${remove} ${skinput} ${runevent} ${useCATv742ntuples} ${LibList} ${DEBUG} ${useskim} ${runnp} ${runcf} ${catversion} ${skflag} ${usebatch} -X ${tagger}
        #rm /data2/CAT_SKTreeOutput/${USER}/CLUSTERLOG${tagger)/${i}clust.txt
        rm $logfile_time
    done

fi

