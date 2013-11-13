#!/bin/bash

directory=/pnfs/cms/WAX/11/store/user/fgior8/Summer12LQ_09/$1
destination=/uscms_data/d2/fgior8/LQntuple_09/CMSSW_5_3_4_LQ/src/code/DataSetList
TEXT=$1.txt

for file in `ls -S $directory`
do
  a=`echo $file | awk -F_ '{print $4}'`
  copiedfiles[$a]=0
done  

for file in `ls -S $directory`
do
  b=`echo $file | awk -F_ '{print $4}'`
  echo $b
  if [ ${copiedfiles[$b]} -eq 1 ]
  then
    echo "Duplicate"
    continue
  fi
  echo "ok"
#  echo "$destination/$file" >> $destination/$TEXT
  echo "dcache:$directory/$file" >> $destination/$TEXT
#  dccp  $directory/$file $destination/$file
  copiedfiles[$b]=1
done                                  

exit 0
