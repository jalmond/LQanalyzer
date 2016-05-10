if [[  $isSLC5 == "True" ]];
    then
    bash $LQANALYZER_DIR/bin/Make/make_rocher_lib_c98.sh False
    
else
    bash $LQANALYZER_DIR/bin/Make/make_rocher_lib_c11.sh False
fi