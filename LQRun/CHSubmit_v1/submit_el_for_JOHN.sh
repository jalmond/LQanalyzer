#!/bin/sh


data=true
data_VJ=true

if [[ $data  == "true" ]];                                                                    
then                                                                                              

    source functions.sh
    cycle="CHElJets_v2_sig_jecSrc" 
    skinput="True"                   
    useskim=""                                                                  
    njobs=100
    nsubjobs=20
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000   
    remove_workspace="False"
#    nevents=1000

    declare -a input_samples=("stbar_sch_pf" "CH130PU_pf" "CH140PU_pf" "CH150PU_pf" "CH120PU_pf" "CH110PU_pf" "CH100PU_pf"  "CH90PU_pf" "ttbarMS_pf" "ttW_pf" "ttZ_pf" "ttH_pf" "stbar_tch_pf" "stbar_tW_pf" "st_sch_pf" "st_tch_pf" "st_tW_pf" "WW_py_pf" "ZZ_py_pf" "WZ_py_pf")

#    declare -a input_samples=("st_sch_pf")

    outputdir=$LQANALYZER_DIR"/data/output/CHEJ_high_v2/"
    
    source submit.sh $1
fi 

if [[ $data_VJ  == "true" ]];
then
    source functions.sh
    cycle="CHElJets_v2_VJ_jecSrc"
    skinput="True"
    useskim=""
    njobs=100
    nsubjobs=10
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000   
    nevents=-1
    remove_workspace="False"
    declare -a input_samples=("Wjets_pf" "DY10to50_pf" "DY50plus_pf")
    outputdir=$LQANALYZER_DIR"/data/output/CHEJ_high_v2/"
    source submit.sh $1 
fi  

