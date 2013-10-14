#!/bin/bash

list=/uscms_data/d2/fgior8/LQntuple_09/CMSSW_5_3_4_LQ/src/code/DataSetList/SingleMu.txt
a=0
little=little
txt=SM.txt
b=0
for line in `cat $list`
do
#  echo "ciao $line"
  echo "$line" >> $little$b$txt
  a=$(($a+1))
#  echo $a
  if [ $a -eq 50 ]
  then
#    echo "condor_submit condor $little$b$txt SingleMu_FR_$b"

    cat > simulator<<EOF

    universe = vanilla
    Executable = rotto.sh
    Requirements = Memory >= 199 &&OpSys == "LINUX"&& (Arch != "DUMMY" )&& Disk > 1000000
    Should_Transfer_Files = YES
    WhenToTransferOutput = ON_EXIT
    Output = sleep_FR_40_job\$(Cluster).stdout
    Error = sleep_FR_40_job\$(Cluster).stderr
    Log = sleep_FR_40_job\$(Cluster).log
    notify_user = ferdinando.giordano@email.ucr.edu
    notification= Never
    arguments = \$(Cluster) $little$b$txt $b
    Queue 1

EOF

    condor_submit simulator

    a=0
    #rm "$little$b$txt"
    b=$(($b+1))
  fi
done
#echo "condor_submit condor $little$b$txt SingleMu_FR_$b"

    cat > simulator<<EOF

    universe = vanilla
    Executable = rotto.sh
    Requirements = Memory >= 199 &&OpSys == "LINUX"&& (Arch != "DUMMY" )&& Disk > 1000000
    Should_Transfer_Files = YES
    WhenToTransferOutput = ON_EXIT
    Output = sleep_FR_40_job\$(Cluster).stdout
    Error = sleep_FR_40_job\$(Cluster).stderr
    Log = sleep_FR_40_job\$(Cluster).log
    notify_user = ferdinando.giordano@email.ucr.edu
    notification= Never
    arguments = \$(Cluster) $little$b$txt $b
    Queue 1

EOF

    condor_submit simulator

#rm "$little$b$txt"
exit 0

