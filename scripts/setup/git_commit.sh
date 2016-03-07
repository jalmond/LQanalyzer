if [[ $LQANALYZER_DIR == "" ]];
    then
    source $LQANALYZER_DIR/setup.sh
fi
####### commit with no tag name
cp $LQANALYZER_DIR/scripts/setup/branch_setup.sh $LQANALYZER_DIR/setup.sh
git commit -a
git push

cp $LQANALYZER_DIR/scripts/setup/tag_setup.sh $LQANALYZER_DIR/setup.sh

