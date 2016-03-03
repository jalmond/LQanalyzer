git commit -a
git push
git tag $CATVERSION
git push --tags

todelete=$1
echo $todelete
if [[ $1 == "-d" ]] then
    
    git tag -d $CATVERSION 
    git push origin :refs/tags/$CATVERSION
fi