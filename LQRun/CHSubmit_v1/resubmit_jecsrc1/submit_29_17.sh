#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_29/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_29/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_29/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2_sub/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_29/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_29/runJob_29_17.C 
echo "Ran macro 2" 
