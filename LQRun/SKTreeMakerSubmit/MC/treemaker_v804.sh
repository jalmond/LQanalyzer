if [[ $1 == "" ]]; then
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "fix MET shift down"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "fix MET shift down"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "fix MET shift down"
else
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "$1"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "$1"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "$1"
fi