cd $BTAGDIR94X/conf
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libBTag94XSFUtil.so ]] ;
    then
    rm libBTag94XSFUtil.so
fi
cp $BTAGDIR94X/Root/libBTagSFUtil.so libBTag94XSFUtil.so

cd $LQANALYZER_DIR/LQAnalysis/94X/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean 
    make 
fi
cd $LQANALYZER_DIR/

