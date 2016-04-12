if [[ -f $LQANALYZER_DIR/HNCommonLeptonFakes/StandAlone/libHNCommonLeptonFakes.so ]];
then
    rm $LQANALYZER_DIR/HNCommonLeptonFakes/StandAlone/libHNCommonLeptonFakes.so
    rm $LQANALYZER_DIR/HNCommonLeptonFakes/Root/*o
fi
cd $LQANALYZER_DIR/HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libHNCommonLeptonFakes.so ]];
    then
    rm libHNCommonLeptonFakes.so
fi
cp $LQANALYZER_DIR/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .
cd $LQANALYZER_DIR