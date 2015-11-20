source treemaker_5314_lepskim.sh MC 
source  treemaker_5314_dilepskim.sh  MC
python SendEmailMC.py
cat emailMC.txt | mail -s "New MC SKTrees available" jalmond@cern.ch
rm emailMC.txt