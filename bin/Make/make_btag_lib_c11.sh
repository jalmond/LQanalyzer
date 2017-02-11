cd $BTAGDIR/conf
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libBTagSFUtil.so ]] ;
    then
    rm libBTagSFUtil.so
fi
cp $BTAGDIR/Root/libBTagSFUtil.so libBTagSFUtil.so

cd $LQANALYZER_DIR/LQAnalysis/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean
    make
fi
cd $LQANALYZER_DIR/

