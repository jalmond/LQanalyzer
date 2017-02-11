cd $ROCHDIR/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f librochcor2016.so ]] ;
    then
    rm librochcor2016.so
fi
cp $ROCHDIR/Root/librochcor2016.so librochcor2016.so

cd $LQANALYZER_DIR/LQAnalysis/AnalyzerTools/

if [[ $1 == "False" ]]; then
    make distclean
    make
fi
cd $LQANALYZER_DIR/

