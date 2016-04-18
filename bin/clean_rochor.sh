cd rochcor2012/conf/;
make clean -f Makefile.StandAlone;
if [[ -f ${LQANALYZER_LIB_PATH}/librochcor2012.so ]];
    then
    rm ${LQANALYZER_LIB_PATH}/librochcor2012.so
fi
cd $LQANALYZER_DIR

