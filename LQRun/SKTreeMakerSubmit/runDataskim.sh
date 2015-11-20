source treemaker_5314_lepskim.sh DATA 
source  treemaker_5314_dilepskim.sh  DATA
python SendEmailData.py
cat emailData.txt | mail -s "New Data SKTrees available" jalmond@cern.ch
rm emailData.txt

