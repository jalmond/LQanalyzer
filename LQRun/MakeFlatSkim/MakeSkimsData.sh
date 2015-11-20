python RunSkim_data.py
python SendEmailData.py
cat emailData.txt | mail -s "New Data skims available" jalmond@cern.ch
cat emailData.txt | mail -s "New Data skims available" Ferdinando.Giordano@cern.ch
rm emailData.txt