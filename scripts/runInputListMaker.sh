cd $LQANALYZER_DIR/scripts/
root -b -l <<EOF
.L MakeInputListForSubmitScript.C+g
MakeInputListForSubmitScript();
.q;
EOF
cd -