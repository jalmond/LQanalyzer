todelete=""
sendemail=false

if [[ $1 == "" ]];
    then
    echo "Need to specify -d (which deletes tag if committed by mistake) and or -e (sends email about new tag)"
    exit 1
fi

if [[ $1 == "-d" ]];
    then
    git tag -d $CATVERSION
    git push origin :refs/tags/$CATVERSION
    
    if [[ $2 ==  "-e" ]];
	then
	sendemail=true;
    fi
fi

if [[ $1 == "-e" ]];
    then
    sendemail=true;
    if [[ $2 == "-d" ]];
    then
	git tag -d $CATVERSION
	git push origin :refs/tags/$CATVERSION
    fi
fi


git commit -a
git push
git tag $CATVERSION
git push --tags

if [[ $sendemail == "true" ]];
    then

    declare -a list_users=( "jalmond@cern.ch" ) 
    
    for i in  ${list_users[@]};
      do
      
      source mail_tag.sh $i
      cat email.txt | mail -s "New LQAnalyzer Tag Ready" jalmond@cern.ch
      rm email.txt
    done
fi