python RunSkim.py
python SendEmailMC.py
cat emailMC.txt | mail -s "New MC skims available" jalmond@cern.ch
cat emailMC.txt | mail -s "New MC skims available" Ferdinando.Giordano@cern.ch
