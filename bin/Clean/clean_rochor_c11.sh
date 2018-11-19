cd $LQANALYZER_DIR/LQAnalysis/$1/AnalyzerTools/rochcor2016/conf/;
make clean -f Makefile.StandAlone; 
if [[ -f ${LQANALYZER_LIB_PATH}/librochcor_$1.so  ]];
    then
    rm ${LQANALYZER_LIB_PATH}/librochcor_$1.so
fi
cd $LQANALYZER_DIR