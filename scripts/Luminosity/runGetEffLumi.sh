lumidir="/data2/LQ_SKTreeOutput/Lumi/"${USER}
if [[ ! -d "${lumidir}" ]]; then
    mkdir $lumidir
fi
root -b -l <<EOF
.L GetEffectiveLuminosity.C+g
GetEffectiveLuminosity("$1","$2","$3");
.q;
EOF
bash cleanup.sh
#python EmailNewEffLumiList.py