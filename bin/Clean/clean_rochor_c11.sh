cd $LQANALYZER_DIR/rochcor2015/rochcor2015C11/conf/; 
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/librochcor2015.so  ]];
    then
    rm ${LQANALYZER_LIB_PATH}/librochcor2015.so
fi
cd $LQANALYZER_DIR