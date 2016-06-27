export CATVERSION=v7-6-5
### If there is a small bug/new code then new subtag is made
export tag_numerator='.2'
if [[ '-d' == branch ]];
    then
    export CATTAG=
else
    export CATTAG=v7-6-4.2
fi

