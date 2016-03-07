export CATVERSION=v7-6-3
### If there is a small bug/new code then new subtag is made
tag_numerator=".2"
if [[ $1 == "branch" ]];
    then
    export CATTAG=
else
    export CATTAG=$CATVERSION$tag_numerator
fi