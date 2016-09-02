
#!/bin/sh


data=true
data_VJ=false
data_Vbb=false
data_syst=false

if [[ $data  == "true" ]];                                                                    
then                                                                                              

    source functions.sh
    cycle="CHMuJets_v2_sig"                                                                                                
    skinput="True"                            
    useskim=""
    runcf="True"
    njobs=100
    data_lumi="AtoD" 
    loglevel="INFO"
    logstep=1000
    declare -a input_samples=("CH140_mt171.5_pf" "CH140_mt173.5_pf" "CH90PU_pf")
#    declare -a input_samples=("CH120PU_pf")

    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_high_v2/"                       
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

