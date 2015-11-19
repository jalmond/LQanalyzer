python RunSkim.py
python SendEmailMC.py
cat emailMC.txt | mail -s "New MC skims available" jalmond@cern.ch
cat emailMC.txt | mail -s "New MC skims available" Ferdinando.Giordano@cern.ch
python RunSkim_data.py
python SendEmailData.py
cat emailData.txt | mail -s "New Data skims available" jalmond@cern.ch
cat emailData.txt | mail -s "New Data skims available" Ferdinando.Giordano@cern.ch