#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_7111724_cmscluster.snu.ac.kr/Job_95/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_7111724_cmscluster.snu.ac.kr/Job_95/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_7111724_cmscluster.snu.ac.kr/Job_95/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_7111724_cmscluster.snu.ac.kr/Job_95/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_7111724_cmscluster.snu.ac.kr/Job_95/runJob_95.C 
echo "Ran macro 2" 
