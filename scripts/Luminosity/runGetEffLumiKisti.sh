lumidir="/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/"${USER}
if [[ ! -d "${lumidir}" ]]; then
    mkdir $lumidir
fi
cd $LQANALYZER_DIR/scripts/Luminosity/
root -b -l <<EOF
.L GetEffectiveLuminosity_kisti.C+g
GetEffectiveLuminosity_kisti("$1","$2","$3");
.q;
EOF
#bash cleanup.sh
cd -
#python EmailNewEffLumiList.py