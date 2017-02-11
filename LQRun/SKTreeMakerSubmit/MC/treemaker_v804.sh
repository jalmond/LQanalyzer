if [[ $1 == "" ]]; then
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "comment"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "comment"
    sktree -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "comment"
else
    sktree -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "$1"
    sktree -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "$1"
    sktree -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "$1"
fi