#!/bin/sh

echo "Runninh DY and DiMuon period A samples" 

root -l -q -b compile.C

function runCode(){    
    rm log/$2
    nohup root -l -q -b $1 &> log/$2 &
    echo "running script runDataDiMuonPeriodA.C. . Output log to " log/$2 
 
}

runCode runDataDiMuonPeriodA.C dimuon_data.log 
runCode runDYlowmass.C DYlowmass.log
runCode runDYhighmass.C DYhighmass.log

