cd HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f libHNCommonLeptonFakes.so ]];
    then
    rm libHNCommonLeptonFakes.so
fi
cp $LQANALYZER_DIR/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .
cd $LQANALYZER_DIR
make distclean
make