#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttH  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_79820_cmscluster.snu.ac.kr/Job_47/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_79820_cmscluster.snu.ac.kr/Job_47/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_79820_cmscluster.snu.ac.kr/Job_47/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_79820_cmscluster.snu.ac.kr/Job_47/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_79820_cmscluster.snu.ac.kr/Job_47/runJob_47.C 
echo "Ran macro 2" 
