cd $LQANALYZER_DIR/BTag/BTagC11/conf/; 
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/libBTagSFUtil.so  ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libBTagSFUtil.so
fi
cd $LQANALYZER_DIR