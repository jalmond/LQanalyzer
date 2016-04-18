cd $LQANALYZER_DIR/Btag/
if [[ -f BTagSFUtil_C.so ]];
then
    rm BTagSFUtil_C.so
fi
if [[ -f BTagSFUtil_C.d ]];
then
    rm BTagSFUtil_C.d
fi

root -l -q -b BTagSFUtil.C+g
cd -
cd $LQANALYZER_LIB_PATH
if [[ -f BTagSFUtil_C.so ]];
then
    rm BTagSFUtil_C.so
fi
cp $LQANALYZER_DIR/Btag/BTagSFUtil_C.so .
cd $LQANALYZER_DIR


