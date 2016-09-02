#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_18/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_18/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_18/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2_sub/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_18/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7152116_cmscluster.snu.ac.kr/Job_18/runJob_18_6.C 
echo "Ran macro 2" 
