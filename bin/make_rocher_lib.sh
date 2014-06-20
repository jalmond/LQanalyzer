cd rochcor2012/conf/
make -f Makefile.StandAlone
cd -
cd $LQANALYZER_LIB_PATH
rm librochcor2012.so  
cp $LQANALYZER_DIR/rochcor2012/Root/librochcor2012.so .
cd $LQANALYZER_DIR
make distclean
make