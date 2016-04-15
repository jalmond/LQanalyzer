if [[ ! -f ${LQANALYZER_LIB_PATH}/librochcor2015.so ]] ;
    then
    echo "Compiling rochcor2015 code" 
    cd $LQANALYZER_DIR/rochcor2015/
    if [[  -f rochcor2015_cc.d ]];
	then
	rm rochcor2015_cc.d
    fi
    if [[  -f RoccoR_cc.d ]];
	then
	rm RoccoR_cc.d
    fi
    if [[  -f rochcor2015_cc.so ]];
	then
	rm rochcor2015_cc.so
    fi
    if [[  -f RoccoR_cc.so ]];
	then
	rm RoccoR_cc.so
    fi

    source $LQANALYZER_DIR/rochcor2015/compile_rocher.sh
    cd -
    cd $LQANALYZER_LIB_PATH
    if [[  -f librochcor2015.so ]]; then
	rm librochcor2015.so  
	rm libRoccoR_cc.so
    fi
    cp $LQANALYZER_DIR/rochcor2015/rochcor2015_cc.so librochcor2015.so
    cp $LQANALYZER_DIR/rochcor2015/RoccoR_cc.so libRoccoR.so
    cd $LQANALYZER_DIR

else
    echo "$LQANALYZER_LIB_PATH}/librochcor2015.so exists"
fi