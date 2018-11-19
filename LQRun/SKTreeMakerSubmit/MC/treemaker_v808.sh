if [[ $1 == "" ]]; then
    #sktreemaker -a  SKTreeMaker -list all_sig  -c v8-0-8 -m "new samples with kisti tag" -SIG true
#   sktreemaker -a  SKTreeMaker -list all_sig  -c v8-0-8 -m "new samples with kisti tag"
    sktreemaker_80X -a  SKTreeMakerDiLep -list all_nonsig_mc  -c v8-0-8  -m "new samples with kisti tag"
else
    sktreemaker -a  SKTreeMaker -list all_mc  -c v8-0-8 -m "$1"
    sktreemaker -a  SKTreeMakerDiLep -list new_list  -c v8-0-8  -m "$1"
    sktreemaker -a  SKTreeMakerTriLep -list new_list  -c v8-0-8  -m "$1"
fi
