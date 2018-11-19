cd $ROCHDIR94X/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f librochcor_94X.so ]] ;
    then
    rm librochcor_94X.so
fi
cp $ROCHDIR94X/Root/librochcor2016.so librochcor_94X.so

cd $LQANALYZER_DIR/LQAnalysis/94X/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean 
    make
fi
cd $LQANALYZER_DIR/

