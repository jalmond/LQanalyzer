#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_79315_cmscluster.snu.ac.kr/Job_111/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_79315_cmscluster.snu.ac.kr/Job_111/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_79315_cmscluster.snu.ac.kr/Job_111/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_79315_cmscluster.snu.ac.kr/Job_111/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_79315_cmscluster.snu.ac.kr/Job_111/runJob_111.C 
echo "Ran macro 2" 
