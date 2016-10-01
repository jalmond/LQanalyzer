if [[ $1 == "" ]]; then
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-1 -m "First set of cuts with 2016"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-1  -m "First set of cuts with 2016"
else
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-1 -m "$1"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-1  -m "$1"
fi