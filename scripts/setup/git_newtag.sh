if [[ $LQANALYZER_DIR == "" ]];
    then
    source $LQANALYZER_DIR/setup.sh
fi

itag=".3"
tagname=$CATVERSION$itag

rm $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "export CATVERSION="$CATVERSION >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "### If there is a small bug/new code then new subtag is made"  >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "tag_numerator='"$itag"'"  >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "if [[ '-d' == "branch" ]];"  >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "    then" >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "    export CATTAG=" >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "else" >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "    export CATTAG=$CATVERSION"$itag >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
echo "fi" >> $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh

sendemail=false

tag_exists=false
git tag>> gitcheck.txt
while read line
  do
  if [[ $line  == *$tagname* ]];
      then
      tag_exists=true
  fi
done < gitcheck.txt

echo $tag_exists
rm gitcheck.txt


cp $LQANALYZER_DIR/scripts/setup/tag_setup.sh $LQANALYZER_DIR/setup.sh
git commit -a

#"New Tag: "$tagname  

if [[ $1 == "" ]];
    then
    echo "Making new tag "$tagname
fi



if [[ $tag_exists == "true" ]];
    then
    echo "Deleting branch "$tagname
    git tag -d $tagname
    git push origin :refs/tags/$tagname
    
fi

if [[ $1 == "-e" ]];
    then
    sendemail=true;
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