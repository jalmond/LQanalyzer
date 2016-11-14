if [[ $1 == "" ]]; then
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-2 -m "First set of cuts with 802 cattuples"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-2  -m "First set of cuts with 802 cattuples"
else
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-2 -m "$1"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-2  -m "$1"
fi