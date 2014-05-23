cd HNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
ln -s $LQANALYZER_DIR/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .  
cd $LQANALYZER_DIR