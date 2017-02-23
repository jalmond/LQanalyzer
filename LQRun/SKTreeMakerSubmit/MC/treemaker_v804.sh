if [[ $1 == "" ]]; then
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "fix jetsmearing in sktreemaker + fill rochester branch"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "smear met for mc in sktrees (store original met as new value + save metx/y in sktree). Add function to correct met for rochester correction"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "smear met for mc in sktrees (store original met as new value + save metx/y in sktree). Add function to correct met for rochester correctiony"
else
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "$1"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "$1"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "$1"
fi