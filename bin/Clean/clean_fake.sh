cd $LQANALYZER_DIR/LQAnalysis/src/HNCommonLeptonFakes/conf/; 
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes.so
fi
cd $LQANALYZER_DIR