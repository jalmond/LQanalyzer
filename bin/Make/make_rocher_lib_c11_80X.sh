cd $ROCHDIR80X/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f librochcor_80X.so ]] ;
    then
    rm librochcor_80X.so
fi
cp $ROCHDIR80X/Root/librochcor2016.so librochcor_80X.so

cd $LQANALYZER_DIR/LQAnalysis/80X/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean 
    make 
fi
cd $LQANALYZER_DIR/

