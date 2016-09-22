export CATVERSION=v8-0-1
### If there is a small bug/new code then new subtag is made
export tag_numerator='.3'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v8-0-1.3
fi

