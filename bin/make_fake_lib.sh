cd HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
cp $LQANALYZER_DIR/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .
cd $LQANALYZER_DIR
make distclean
make