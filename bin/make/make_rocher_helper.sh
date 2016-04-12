if [[ ! -f ${LQANALYZER_LIB_PATH}/librochcor2012.so ]] ;
    then
    
    if [[  -f $LQANALYZER_DIR/rochcor2012/Root/librochcor2012.so ]];
    then
	rm $LQANALYZER_DIR/rochcor2012/Root/librochcor2012.so
    fi
    if [[  -f $LQANALYZER_DIR/rochcor2012/Root/rochcor2012jan22.o  ]];
    then
	rm $LQANALYZER_DIR/rochcor2012/Root/rochcor2012jan22.o
    fi
    if [[  -f $LQANALYZER_DIR/rochcor2012/StandAlone/librochcor2012.so ]];
    then
	rm $LQANALYZER_DIR/rochcor2012/StandAlone/librochcor2012.so
    fi
    
    
    cd $LQANALYZER_DIR/rochcor2012/conf/
    
    make -f Makefile.StandAlone
    cd -
    cd $LQANALYZER_LIB_PATH
    
    cp $LQANALYZER_DIR/rochcor2012/Root/librochcor2012.so .
    cd $LQANALYZER_DIR
    
fi
