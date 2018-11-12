cd $LQANALYZER_DIR/scripts/
root -b -l <<EOF
.L MakeInputListForSubmitScript_kisti.C+g
MakeInputListForSubmitScript_kisti();
.q;
EOF
cd -