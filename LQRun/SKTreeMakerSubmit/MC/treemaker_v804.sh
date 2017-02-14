if [[ $1 == "" ]]; then
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "apply jetsmearing in sktreemaker + fill rochester branch"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "apply jetsmearing in sktreemaker + fill rochester branch"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "apply jetsmearing in sktreemaker + fill rochester branch"
else
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-4 -m "$1"
    sktreemaker -a  SKTreeMakerDiLep -list all_mc  -c v8-0-4  -m "$1"
    sktreemaker -a  SKTreeMakerTriLep -list all_mc  -c v8-0-4  -m "$1"
fi