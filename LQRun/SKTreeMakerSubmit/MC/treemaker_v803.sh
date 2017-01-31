if [[ $1 == "" ]]; then
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-3 -m "Fix in jet number"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-3  -m "Fix in jet number"
else
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-3 -m "$1"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-3  -m "$1"
fi