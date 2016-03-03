echo "Dear User " >> email.txt
echo " " >> email.txt
echo "A new tag named "$CATVERSION" is now available in LQanalyzer." >> email.txt
echo " " >> email.txt
echo "git checkout -b  CatAnalyzer_13TeV<tagname> <tagname>" >> email.txt
echo "i.e, git checkout -b CatAnalyzer_13TeV_"$CATVERSION " "$CATVERSION  >> email.txt
echo " " >> email.txt
echo "Thanks," >> email.txt
echo "John" >> email.txt