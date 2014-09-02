cd Btag/
root -l -q -b BTagSFUtil.C+g
cd -
cd $LQANALYZER_LIB_PATH
rm BTagSFUtil_C.so
cp $LQANALYZER_DIR/Btag/BTagSFUtil_C.so .
cd $LQANALYZER_DIR
make distclean
make

