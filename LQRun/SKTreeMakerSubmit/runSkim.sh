source treemaker_lepskim_13TeV.sh
source treemaker_dilepskim_13TeV.sh
python SendEmailMC.py
cat emailMC.txt | mail -s "New MC SKTrees available" jalmond@cern.ch
rm emailMC.txt