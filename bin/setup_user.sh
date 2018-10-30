#! /bin/sh                                                                                                                                                                                                                                                                      
function killbkg {
    python $LQANALYSER_DIR/python/killbkg.py -i $1
}
alias make_sktree='make -j 5'


if [[ $USER == "jalmond" ]]; then
    alias cat_path_analysis_ls='ll -rth /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/ '
    if [ $LQANALYZER_DIR ]; then
        echo "Running on batch"
    fi
    function cat_path_analysis_ls {
        ll -rth  /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/${1}
    }
    function cat_path_analysis {
        cd /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/${1}
    }
fi


