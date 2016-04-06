if [[ $CATVERSION ==  "v7-6-3" ]];
    then
    if [[ $CATTAG == "v7-6-3" ]];
	then
	echo "Since this tag has many changed please check out https://twiki.cern.ch/twiki/pub/CMS/SNULQNtuples/NewLQAnalyzerv763.pdf " >> email.txt
	
    fi
    if [[ $CATTAG == "v7-6-3.2" ]];
	then
	echo "Since this tag has many changed please check out https://twiki.cern.ch/twiki/pub/CMS/SNULQNtuples/NewLQAnalyzerv763.pdf " >> email.txt
	echo " "
    fi
    if [[ $CATTAG == "v7-6-3.3" ]];
    then
	echo "This tag has a fix in pileup weights" >> email.txt
    fi
    if [[ $CATTAG == "v7-6-3.5" ]];
	then
	echo "This tag includes trilepton skims. Prescale function. ID+RECO SFS for electrons, Trigger SFs">> email.txt
fi

fi





