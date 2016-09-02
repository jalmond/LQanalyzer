#!/bin/sh


data=false
data2=true
data3=false
data_VJ=true
data_jesdown=false
data_jerup=false
data_jerdown=false


if [[ $data  == "true" ]];  
then   
    source functions.sh
    cycle="CHMuJets_v2_sig_jecSrc" 
    skinput="True"                   
    useskim=""
    njobs=100   
    nsubjobs=20
#    njobs=1
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000   
    nevents=-1
    declare -a input_samples=("ttbarMS_pf" "stbar_sch_pf" "stbar_tch_pf" "stbar_tW_pf" "st_tch_pf" "st_tW_pf" "WW_py_pf" "ZZ_py_pf" "WZ_py_pf" "ttW_pf" "ttZ_pf" )
#    declare -a input_samples=("st_sch_pf")
    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"
   ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi 

if [[ $data2  == "true" ]];                                                                    
then
    source functions.sh
    cycle="CHMuJets_v2_sig_jecSrc" 
#    cycle="CHElJets_v2_sig_jecFlav" 
    skinput="True"                   
    useskim=""
    njobs=100   
    nsubjobs=20
#    njobs=1
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000   
    nevents=-1    
    declare -a input_samples=("ttbarMS_pf" "stbar_sch_pf" "stbar_tch_pf" "stbar_tW_pf" "st_sch_pf" "st_tch_pf" "st_tW_pf" "WW_py_pf" "ZZ_py_pf" "WZ_py_pf" "ttW_pf" "ttZ_pf" "ttH_pf" "CH120PU_pf" "CH130PU_pf" "CH140PU_pf" "CH150PU_pf" "CH90PU_pf" "CH100PU_pf" "CH110PU_pf" )
#    declare -a input_samples=("ttbarMS_pf" "st_sch" "st_tch" "st_tW" "WW_py" "ZZ_py" "WZ_py" "ttW" "ttZ" "ttH")
#   declare -a input_samples=("CH120PU_pf" "CH140PU_pf" "CH150PU_pf" "CH130PU_pf" "ttbarMS_pf")
#   declare -a input_samples=("ttbarMS_pf")

# "CH130PU_pf" "CH140PU_pf" "CH150PU_pf")
#    declare -a input_samples=("WW_py_pf")
#    declare -a input_samples=("ttW_pf")
#    declare -a input_samples=("st_sch_pf")

    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"    
            ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi 

if [[ $data3  == "true" ]];                                                                
then
    source functions.sh
    cycle="CHElJets_v2_sig_jecSrc3" 
#    cycle="CHElJets_v2_sig_jecFlav" 
    skinput="True"                   
    useskim=""
#    njobs=100   
    njobs=1
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000   
    nevents=1000

#    declare -a input_samples=("ttbarMS_pf" "CH120PU_pf" "CH130PU_pf" "CH140PU_pf" "CH150PU_pf" "stbar_sch_pf" "stbar_tch_pf" "stbar_tW_pf" "st_sch_pf" "st_tch_pf" "st_tW_pf" "WW_py_pf" "ZZ_py_pf" "WZ_py_pf" "ttW_pf" "ttZ_pf" "ttH_pf")
    declare -a input_sample=("CH120PU_pf")
    outputdir=$LQANALYZER_DIR"/data/output/CHEJ_high_v2/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi 


if [[ $data_VJ  == "true" ]];
then
    source functions.sh 
    cycle="CHMuJets_v2_VJ_jecSrc"

    skinput="True"
    useskim=""
    njobs=100
    nsubjobs=10  
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    nevents=-1                                                                  
    declare -a input_samples=("Wjets_pf" "DY10to50_pf" "DY50plus_pf")
    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/" 
    source submit.sh $1

fi  

if [[ $data_jesdown  == "true" ]];                                                                                     
then                                                                                                               
                                                                                                                   
    source functions.sh                                                                                            
    cycle="CHMuJets_v1_data_JESdown"  
    skinput="True"
    useskim="" 
    njobs=60 
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000                                                               
    nevents=-1 
    declare -a input_samples=("Wjets_pf" "DY10to50_pf" "DY50plus_pf" "Wbb_pf" "Zbb_pf")
    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1                                                         
                                                                                                                   
fi  

if [[ $data_jerup  == "true" ]];                                                                                     
then                                                                                                               
                                                                                                                   
    source functions.sh                                                                                            
    cycle="CHMuJets_v1_data_JERup"                                                                                        \
                                                                                                                   
    skinput="True"                                                                                                \
                                                                                                                   
    useskim=""                                                                                                    \
                                                                                                                   
    njobs=60                                                                                                      \
                                                                                                                   
    data_lumi="AtoD"                                                                                               
    loglevel="INFO"                                                                                               \
                                                                                                                   
    logstep=1000                                                                                                   
    nevents=-1                                                                                                    \
                                                                                                                  \
                                                                                                                   
    declare -a input_samples=("Wjets_pf" "DY10to50_pf" "DY50plus_pf" "Wbb_pf" "Zbb_pf")                           \
                                                                                                                   
    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"                                                   
                                                                                                                   
            ### submit this configured job (uses bin/submit.sh)                                                   \
                                                                                                                   
    source submit.sh $1                                                                                           \
                                                                                                                   
fi  

if [[ $data_jerdown  == "true" ]];                                                                                     
then                                                                                                               
                                                                                                                   
    source functions.sh                                                                                            
    cycle="CHMuJets_v1_data_JERdown"                                                                                        \
                                                                                                                   
    skinput="True"                                                                                                \
                                                                                                                   
    useskim=""                                                                                                    \
                                                                                                                   
    njobs=60                                                                                                      \
                                                                                                                   
    data_lumi="AtoD"                                                                                               
    loglevel="INFO"                                                                                               \
                                                                                                                   
    logstep=1000                                                                                                   
    nevents=-1                                                                                                    \
                                                                                                                  \
                                                                                                                   
    declare -a input_samples=("Wjets_pf" "DY10to50_pf" "DY50plus_pf" "Wbb_pf" "Zbb_pf")                           \
                                                                                                                   
    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"                                                   
                                                                                                                   
            ### submit this configured job (uses bin/submit.sh)                                                   \
                                                                                                                   
    source submit.sh $1                                                                                           \
                                                                                                                   
fi  

