#! /bin/sh                                                                                                                                                                                                                                                                      
export LQANALYZER_FILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
export LQANALYZER_FILE2017_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2017/"
export LQANALYZER_DATASETFILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
export LQANALYZER_DATASETFILE2017_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists2017/AnalysisFiles/"
export LQANALYZER_DATASET_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/"
export LQANALYZER_DATASET2017_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists2017/"
export LQANALYZER_SKTreeLOG_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
export CATTAGDIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/"

if [[ $HOSTNAME == "ui"* ]];
then
    export LQANALYZER_FILE_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
    export LQANALYZER_DATASETFILE_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
    export LQANALYZER_DATASET_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/DataSetLists/"
    export LQANALYZER_SKTreeLOG_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
    export CATTAGDIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATTag/"
fi


# Modify to describe your directory structure.                                                                                                                                                                                                                                  
# all directories are below the LQAnalyser base directory specified above                                                                                                                                                                                                       
### setup paths to be used in analysis code                                                                                                                                                                                                                                     
export LQANALYZER_ANALYSIS_PATH=${LQANALYZER_DIR}/LQAnalysis/
export LQANALYZER_SRC_PATH=${LQANALYZER_DIR}/LQAnalysis/Analyzers/src/
export LQANALYZER_INCLUDE_PATH=${LQANALYZER_DIR}/LQAnalysis/Analyzersinclude/
export LQANALYZER_CORE_PATH=${LQANALYZER_DIR}/LQCore/

export BTAGDIR80X=${LQANALYZER_DIR}/LQAnalysis/80X/AnalyzerTools/BTag/BTagC11/
export BTAGDIR94X=${LQANALYZER_DIR}/LQAnalysis/94X/AnalyzerTools/BTag/BTagC11/

export ROCHDIR80X=${LQANALYZER_DIR}/LQAnalysis/80X/AnalyzerTools/rochcor2016/
export ROCHDIR94X=${LQANALYZER_DIR}/LQAnalysis/94X/AnalyzerTools/rochcor2016/

if [[ $HOSTNAME == "ui"* ]];
then
    export OBJ=obj/kisti$LIBTAG
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/kisti$LIBTAG/
    export LQANALYZER_BATCHLIB_PATH=${LQANALYZER_DIR}/LQLib/batch/

else
    export OBJ=obj/cms2
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cms21$LIBTAG/
    export LQANALYZER_BATCHLIB_PATH=${LQANALYZER_DIR}/LQLib/batch/

fi

export LQANALYZER_OLDLIB_PATH=${LQANALYZER_DIR}/LQLib/
export LQANALYZER_RUN_PATH=${LQANALYZER_DIR}/LQRun/
export LQANALYZER_CLUSTER_TXT_PATH=${LQANALYZER_DIR}/LQRun/txt/Cluster/
export LQANALYZER_BIN_PATH=${LQANALYZER_DIR}/bin/
### set SKTree path                                                                                                                                                                                                                                                             
export SKTREE_INCLUDE_PATH=${LQANALYZER_DIR}/LQCore/SKTree/include/
## setup directory to store analysis rootfiles                                                                                                                                                                                                                                  
export FILEDIR=${LQANALYZER_DIR}/data/rootfiles/
export IDFILEDIR=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/ID/
export LUMIFILEDIR=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/Luminosity/
export TRIGGERFILEDIR=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/Trigger
export BTAGFILEDIR=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/BTag/
export PILEUPFILEDIR=/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/Pileup/

export LQANALYZER_OUTPUT_PATH=/data2/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/

export LQANALYZER_LOG_PATH=/data2/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
export LQANALYZER_LOG_8TeV_PATH=${LQANALYZER_DIR}/data/logfiles/

if [[ $HOSTNAME == "ui"* ]];
then
    export LQANALYZER_OUTPUT_PATH=/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/
    export LQANALYZER_LOG_PATH=/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
fi

