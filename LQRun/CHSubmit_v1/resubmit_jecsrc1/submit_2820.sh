#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_2820/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_2820/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_2820/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_2820/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_2820/runJob_2820.C 
echo "Ran macro 2" 
