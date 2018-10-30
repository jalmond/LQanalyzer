if [ ! -d ${LQANALYZER_OLDLIB_PATH} ]; then
    echo Directory ${LQANALYZER_OLDLIB_PATH} does not exist ... creating it
    mkdir ${LQANALYZER_OLDLIB_PATH}
fi

if [ ! -d ${LQANALYZER_LIB_PATH} ]; then
    echo Directory ${LQANALYZER_LIB_PATH} does not exist ... creating it
    mkdir ${LQANALYZER_LIB_PATH}
    file="${LQANALYZER_OLDLIB_PATH}/libAnalysisCore.so"
    if [ -f "$file" ]; then
        echo Old lib dir ${LQANALYZER_OLDLIB_PATH} is redundant. Will remove these library
        rm  ${LQANALYZER_OLDLIB_PATH}/*.so
        rm  ${LQANALYZER_OLDLIB_PATH}/*map
        rm  ${LQANALYZER_CORE_PATH}/*/obj/*.o
        rm -r ${LQANALYZER_CORE_PATH}/*/obj/dep/
        rm  ${LQANALYZER_ANALYSIS_PATH}/*/obj/*.o
        rm -r ${LQANALYZER_ANALYSIS_PATH}/*/obj/dep/
    fi
fi
