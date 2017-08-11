export CATVERSION=v7-6-6
### If there is a small bug/new code then new subtag is made
export tag_numerator='.12'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v7-6-6.12
fi

