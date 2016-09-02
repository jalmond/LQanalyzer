#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttH  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_713118_cmscluster.snu.ac.kr/Job_36/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_713118_cmscluster.snu.ac.kr/Job_36/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_713118_cmscluster.snu.ac.kr/Job_36/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_713118_cmscluster.snu.ac.kr/Job_36/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_713118_cmscluster.snu.ac.kr/Job_36/runJob_36.C 
echo "Ran macro 2" 
