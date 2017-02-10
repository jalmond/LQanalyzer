cd $LQANALYZER_DIR/LQAnalysis/Helpers/src/HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libHNCommonLeptonFakes.so ]];
    then
    rm libHNCommonLeptonFakes.so
fi
cp $LQANALYZER_DIR/LQAnalysis/Helpers/src/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .
cd $LQANALYZER_DIR/LQAnalysis/Helpers/
make distclean
make
cd $LQANALYZER_DIR