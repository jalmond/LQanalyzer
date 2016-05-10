export CATVERSION=v7-6-4
### If there is a small bug/new code then new subtag is made
export tag_numerator='.1'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v7-6-4.1
fi

