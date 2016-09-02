#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781350_cmscluster.snu.ac.kr/Job_292/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781350_cmscluster.snu.ac.kr/Job_292/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781350_cmscluster.snu.ac.kr/Job_292/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781350_cmscluster.snu.ac.kr/Job_292/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_781350_cmscluster.snu.ac.kr/Job_292/runJob_292.C 
echo "Ran macro 2" 
