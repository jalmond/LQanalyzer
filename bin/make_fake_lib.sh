cd WRHNCommonLeptonFakes/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
ln -s $LQANALYZER_DIR/WRHNCommonLeptonFakes/Root/libWRHNCommonLeptonFakes.so .  
cd $LQANALYZER_DIR