export CATVERSION=v7-6-6
### If there is a small bug/new code then new subtag is made
export tag_numerator='.11'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v7-6-6.11
fi

