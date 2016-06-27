root -b -l <<EOF
.L CountGenWeights.C+g
CountGenWeights("$1","$2", "$3");
.q;
EOF