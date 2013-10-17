#!/bin/sh

echo "Runninh DY and DiMuon period A samples" 

root -l -q -b compile.C

function runCode(){    
    nohup root -l -q -b $1 &> log/$2 &
}

runCode runDataDiMuonPeriodA.C dimuon_data.log 
runCode runDYlowmass.C DYlowmass.log
runCode runDYhighmass.C DYhighmass.log

