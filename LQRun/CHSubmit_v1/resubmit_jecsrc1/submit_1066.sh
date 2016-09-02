#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781721_cmscluster.snu.ac.kr/Job_1066/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781721_cmscluster.snu.ac.kr/Job_1066/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781721_cmscluster.snu.ac.kr/Job_1066/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781721_cmscluster.snu.ac.kr/Job_1066/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781721_cmscluster.snu.ac.kr/Job_1066/runJob_1066.C 
echo "Ran macro 2" 
