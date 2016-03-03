root -b -l <<EOF
.L GetEffectiveLuminosity.C+g
GetEffectiveLuminosity("$1");
.q;
EOF
bash cleanup.sh
