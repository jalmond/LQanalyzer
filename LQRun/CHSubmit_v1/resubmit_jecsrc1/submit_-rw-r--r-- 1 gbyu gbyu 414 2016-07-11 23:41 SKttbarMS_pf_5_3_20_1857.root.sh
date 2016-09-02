#!/bin/sh
#$ -S /bin/bash 
#$ -N CHttbarMS  
#$ -wd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root/ 
#$ -o /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root/ 
#$ -e /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root/ 
echo "Job started at " `date` 
cd /share/apps/root_v5_34_32/root/ 
. bin/thisroot.sh 
cd /data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/
source setup.sh 
echo "PWD= "$PWD 
cd /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root/ 
root -l -q -b /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_711228_cmscluster.snu.ac.kr/Job_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root/runJob_-rw-r--r-- 1 gbyu gbyu 414 2016-07-11 23:41 SKttbarMS_pf_5_3_20_1857.root.C 
echo "Ran macro 2" 
