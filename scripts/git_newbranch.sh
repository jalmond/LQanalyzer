todelete=""
sendemail=false

itag=".2"
tagname=$CATVERSION$itag

if [[ $1 == "" ]];
    then
    echo "Making new tag "$tagname
fi

if [[ $1 == "-d" ]];
    then
    git tag -d $tagname
    git push origin :refs/tags/$tagname
    
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
	git tag -d $tagname
	git push origin :refs/tags/$tagname
    fi
fi


git commit -a
git push
git tag $tagname
git push --tags

if [[ $sendemail == "true" ]];
    then

    declare -a list_users=( "jalmond@cern.ch" "jae.sung.kim@cern.ch" ) 
    
    for i in  ${list_users[@]};
      do
      
      source mail_tag.sh $i
      cat email.txt | mail -s "New LQAnalyzer Tag Ready" $i
      rm email.txt
    done
fi