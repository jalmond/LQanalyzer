#!/bin/sh
source functions.sh
###########################################################

declare -a periods=( "A")

stream="egamma"
njobs=10

############################################################
################# Do not change anything after this line
############################################################

if [ -z ${LQANALYZER_DIR} ]
    then 
    setupLQANALYZER
fi



stream=$(makeParseVariable 's' ${stream})
njobs=$(makeParseVariable 'j' ${njobs})

################
#submit
for i in ${periods[@]}
  do
  python ${LQANALYZER_DIR}/LQRun/submit/localsubmit.py -p ${i} ${stream} ${njobs}
done

################
echo ""
echo "Done"