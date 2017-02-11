cd $LQANALYZER_DIR/LQAnalysis/AnalyzerTools/rochcor2016/conf/;
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/librochcor2016.so  ]];
    then
    rm ${LQANALYZER_LIB_PATH}/librochcor2016.so
fi
cd $LQANALYZER_DIR