cd $BTAGDIR80X/conf
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libBTag80XSFUtil.so ]] ;
    then
    rm libBTag80XSFUtil.so
fi
cp $BTAGDIR80X/Root/libBTagSFUtil.so libBTag80XSFUtil.so

cd $LQANALYZER_DIR/LQAnalysis/80X/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean 
    make
fi
cd $LQANALYZER_DIR/

