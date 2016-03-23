export CATVERSION=v7-6-3
### If there is a small bug/new code then new subtag is made
export tag_numerator='.5'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v7-6-3.5
fi

