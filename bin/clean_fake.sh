cd $LQANALYZER_DIR/HNCommonLeptonFakes/conf/;
if [[ -f $LQANALYZER_DIR/HNCommonLeptonFakes/StandAlone/libHNCommonLeptonFakes.so ]];
then
    rm $LQANALYZER_DIR/HNCommonLeptonFakes/StandAlone/libHNCommonLeptonFakes.so
    rm $LQANALYZER_DIR/HNCommonLeptonFakes/Root/*o
fi
make clean -f Makefile.StandAlone;
if [[ -f ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes.so
fi
cd $LQANALYZER_DIR

