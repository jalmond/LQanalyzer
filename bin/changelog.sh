if [[ $CATVERSION == "v7-6-3" ]];
    then
    
    
    echo "Since this tag has many changed please check out https://twiki.cern.ch/twiki/pub/CMS/SNULQNtuples/NewLQAnalyzerv763.pdf " >> email.txt
    echo " "
    echo "Difference with revious tag:"
    echo "This tag has a fix in pileup weights"
fi