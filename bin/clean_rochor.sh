cd $LQANALYZER_DIR/rochcor2015/
if [[ -f RoccoR_cc.so ]];
    then
    rm RoccoR_cc.so
fi
if [[ -f rochor2015_cc.so ]];
    then
    rm rochor2015_cc.so
fi
if [[ -f ${LQANALYZER_LIB_PATH}/libRoccoR.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libRoccoR.so
fi
if [[ -f ${LQANALYZER_LIB_PATH}/librochcor2015.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/librochcor2015.so
fi
cd $LQANALYZER_DIR
source $LQANALYZER_DIR/bin/make_rocher_lib.sh

