todelete=$1

if [[ $todelete == "-d" ]];
    then
    git tag -d $CATVERSION
    git push origin :refs/tags/$CATVERSION
fi

git commit -a
git push
git tag $CATVERSION
git push --tags

