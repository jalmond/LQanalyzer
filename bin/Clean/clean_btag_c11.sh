cd $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/BTag/BTagC11/conf/; 
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/libBTagSFUtil$1.so  ]];
    then
    rm ${LQANALYZER_LIB_PATH}/libBTagSFUtil$1.so
fi
cd $LQANALYZER_DIR