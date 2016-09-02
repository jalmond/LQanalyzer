#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_78549_cmscluster.snu.ac.kr/Job_3265 / 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_78549_cmscluster.snu.ac.kr/Job_3265 / 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_78549_cmscluster.snu.ac.kr/Job_3265 / 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_78549_cmscluster.snu.ac.kr/Job_3265 / 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_78549_cmscluster.snu.ac.kr/Job_3265 /runJob_3265 .C 
echo "Ran macro 2" 
