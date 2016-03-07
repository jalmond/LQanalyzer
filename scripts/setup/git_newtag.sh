if [[ $LQANALYZER_DIR == "" ]];
    then
    source $LQANALYZER_DIR/setup.sh
fi
source $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh Tag

itag=".3"
tagname=$CATVERSION$itag

echo "export CATVERSION="$CATVERSION >> SetBrachAndTag.sh
echo "### If there is a small bug/new code then new subtag is made"  >> SetBrachAndTag.sh
echo "tag_numerator='"$itag"'"  >> SetBrachAndTag.sh
echo "if [[ $1 == "" ];"  >> SetBrachAndTag.sh
echo "    then" >> SetBrachAndTag.sh
echo "    export CATTAG=" >> SetBrachAndTag.sh
echo "else" >> SetBrachAndTag.sh
echo "    export CATTAG=$CATVERSION$tag_numerator" >> SetBrachAndTag.sh
echo "fi" >> SetBrachAndTag.sh

todelete=""
sendemail=false

####### commit with no tag name
cp $LQANALYZER_DIR/scripts/setup/branch_setup.sh $LQANALYZER_DIR/setup.sh
git commit -a
git push

cp $LQANALYZER_DIR/scripts/setup/tag_setup.sh $LQANALYZER_DIR/setup.sh

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


git tag $tagname
git push --tags

if [[ $sendemail == "true" ]];
    then

    declare -a list_users=( "jalmond@cern.ch" "jae.sung.kim@cern.ch" "junho.choi@cern.ch") 
    
    for i in  ${list_users[@]};
      do
      
      source mail_tag.sh $i
      cat email.txt | mail -s "New LQAnalyzer Tag Ready" $i -c jalmond@cern.ch
      rm email.txt
    done
fi