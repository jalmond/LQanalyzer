#!/bin/sh


data=false
data_flav=false
data_syst=true

data_data=false
data_Vbb=false

if [[ $data  == "true" ]];
then
    source functions.sh
    cycle="CHMuJets_v3_sig"
    skinput="True"                            
    useskim=""
    njobs=100
#    nsubjobs=5
    data_lumi="AtoD" 
    loglevel="INFO"
#    runcf="True"                                            
    logstep=1000
#    nevents=1000 
#    declare -a input_samples=("CH110PU_pf" "CH140PU_pf" "CH150PU_pf" "CH120PU_pf" "CH100PU_pf" "CH90PU_pf")
#    declare -a input_samples=("st_tch_pf")
#   declare -a input_samples=("CH130PU_pf")
   declare -a input_samples=("ttbarMS_pf")
#    declare -a input_samples=("st_sch" )
   outputdir=$LQANALYZER_DIR"/data/output/CHMJ_nor_v3/"
            ### submit this configured job (uses bin/submit.sh)                                                                                            
    source submit.sh $1                                                                                                                                     
fi 

if [[ $data_syst  == "true" ]];                                                                    
then                                                                                              

    source functions.sh
    cycle="CHMuJets_v3_sig"
    skinput="True"                            
    useskim=""
    njobs=100
#    nsubjobs=5
    data_lumi="AtoD" 
    loglevel="INFO"
    runcf="True"                                            
    logstep=1000
   declare -a input_samples=("ttbarMSpowheg_pf" "ttbarMSscaleup_pf" "ttbarMSscaledown_pf" "ttbarMSmatchingdown_pf" "ttbarMSmatchingup_pf" "ttbarMSmass171_pf" "ttbarMSmass173_pf")

   outputdir=$LQANALYZER_DIR"/data/output/CHMJ_nor_v3/"
   source submit.sh $1
fi 

if [[ $data_flav  == "true" ]];
then
    source functions.sh
    cycle="CHMuJets_v3_sig_jecFlav"
    skinput="True"                            
    useskim=""
    njobs=100
#    nsubjobs=5
    data_lumi="AtoD" 
    loglevel="INFO"
#    runcf="True"                                            
    logstep=1000
    declare -a input_samples=("ttbarMS_pf")
   outputdir=$LQANALYZER_DIR"/data/output/CHMJ_nor_v3/"
            ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi 

if [[ $data_data  == "true" ]];
then
    source functions.sh
#    cycle="CHElJets_v2_sig"
    cycle="CHMuJets_v3_sig"
    skinput="True"
    runcf="True"
    useskim=""    
    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
#    nevents=100 
    
    declare -a input_samples=("A" "B" "C" "D")                                                                                                 
    stream="singleelectron_pf"
    outputdir=$LQANALYZER_DIR"/data/output/CHEJ_high_v2/"                                                                                                       
            ### submit this configured job (uses bin/submit.sh)                                                                         
    source submit.sh $1                                                                                                                       
    
fi                                                                                                                                             
   
if [[ $data_VJ  == "true" ]];                                                                                     
then                                                                                                               
                                                                                                                   
    source functions.sh                                                                                            
    cycle="CHMuJets_v2_VJ"                                                                           
    skinput="True"                                                                                       
    useskim=""                                                                                            
    njobs=100
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
    cycle="CHMuJets_v1_data_JESdown"                                                                                        \
                                                                                                                   
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

