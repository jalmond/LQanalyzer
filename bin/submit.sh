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
use5312ntuples=$(makeParseVariable 'N' ${use5312ntuples})
use538ntuples=$(makeParseVariable 'M' ${use538ntuples})
LibList=$(makeParseVariable 'L' ${LibList})
useskim=$(makeParseVariable 'm' ${useskim})
runnp=$(makeParseVariable 'P' ${runnp})
runcf=$(makeParseVariable 'Q' ${runcf})
usebatch=$(makeParseVariable 'b' ${usebatch})

DEBUG=$(makeParseVariable 'D' ${DEBUG})
################                                                                                                                                                

#submit     

if [[ $1  == "" ]]; 
then
    for i in ${input_samples[@]}
    do
      python ${LQANALYZER_DIR}/python/localsubmit.py -p ${i} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} ${remove} ${loglevel} ${skipevent} ${nevents} ${totalev} ${xsec} ${targetlumi} ${efflumi} ${remove} ${skinput} ${runevent} ${use5312ntuples} ${use538ntuples} ${LibList} ${DEBUG} ${useskim} ${runnp} ${runcf} ${usebatch}
    done
  
elif [[ $1  == "--help"  || $1  == "--h" ]]; then                 
    echo "Checking options"
    python ${LQANALYZER_DIR}/python/localsubmit.py $1
else 
    for i in ${input_samples[@]}
    do
      python ${LQANALYZER_DIR}/python/localsubmit.py -p ${i} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} ${remove} ${loglevel} ${skipevent} ${nevents} ${totalev} ${xsec} ${targetlumi} ${efflumi} ${remove} ${skinput} ${runevent} ${use5312ntuples} ${use5314ntuples}  ${LibList} ${DEBUG} ${useskim} ${runnp} ${runcf} ${usebatch}
    done

fi

