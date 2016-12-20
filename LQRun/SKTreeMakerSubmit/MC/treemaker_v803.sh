if [[ $1 == "" ]]; then
    sktree -a  SKTreeMaker -list tmpall_mc  -c v8-0-3 -m "First set of cuts with 803 cattuples"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-3  -m "First set of cuts with 803 cattuples"
else
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-3 -m "$1"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-3  -m "$1"
fi