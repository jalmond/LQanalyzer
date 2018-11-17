cd $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libHNCommonLeptonFakes$1.so ]];
    then
    rm libHNCommonLeptonFakes$1.so
fi
if [[ -f libHNCommonLeptonFakes.so ]];
    then
    rm libHNCommonLeptonFakes.so
fi
cp $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so libHNCommonLeptonFakes$1.so
cd $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/

make distclean 
make  

cd $LQANALYZER_DIR