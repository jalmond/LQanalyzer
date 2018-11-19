cd $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/HNCommonLeptonFakes/conf/; 
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes$1.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes$1.so
fi
cd $LQANALYZER_DIR