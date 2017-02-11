import os

inputm =""
while  not inputm == "Y":
    inputm = raw_input("Have you created trigger/lumi files? Y/N")
    if not inputm == "Y":
        print "Run LumiByTrigger.py and LumiSplitter.py in SKTreeLumi repository (2016  dir). Edit Setup.py first"
        

inputm =""
while  not inputm == "Y":
    inputm = raw_input("Have any new branches in cattuples been added to sktrees? Y/N")
    

inputm =""
while  not inputm == "Y":
    inputm = raw_input("have you editted scripts/setup/SetBrachAndTag.sh Y/N")

inputm =""
while  not inputm == "Y":
    inputm = raw_input("have you added CATConfig/CattupleConfig/corrections_v... file  Y/N" )


inputm =""
while  not inputm == "Y":
     inputm = raw_input("have you added CATConfig/CattupleConfig/vXXX.conf file Y/N")

inputm =""
while  not inputm == "Y":
     inputm = raw_input("have you editted bin/submit_setup.sh to make sure dataperiod arrays are up to date Y/N"

 
