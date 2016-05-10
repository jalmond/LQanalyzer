cd $LQANALYZER_DIR/BTag/BTagC11/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libBTagSFUtil.so ]] ;
    then
    rm libBTagSFUtil.so
fi
cp $LQANALYZER_DIR/BTag/BTagC11/Root/libBTagSFUtil.so libBTagSFUtil.so

cd $LQANALYZER_DIR/LQAnalysis/

if [[ $1 == "False" ]]; then
    make distclean
    make
fi
cd $LQANALYZER_DIR/

