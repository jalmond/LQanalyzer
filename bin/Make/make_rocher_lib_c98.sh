cd $LQANALYZER_DIR/rochcor2015/rochcor2015C98/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f librochcor2015.so ]] ;
    then
    rm librochcor2015.so
fi
cp $LQANALYZER_DIR/rochcor2015/rochcor2015C98/Root/librochcor2015.so librochcor2015.so

cd $LQANALYZER_DIR/LQAnalysis/

if [[ $1 == "False" ]]; then
    make distclean
    make
fi
cd $LQANALYZER_DIR/

