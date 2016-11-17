import os,sys

def GetCATAnalyzerMailList():
    maillist=[]
    path_emailconfig = "/data1/LQAnalyzer_rootfiles_for_analysis/CATMOD/emailconfig.txt"
    file_emailconfig = open(path_emailconfig,"r")
    for line in file_emailconfig:
        splitline=line.split()
        if len(splitline) > 1:
            print "error in mail list for user " + line
            sys.exit(1)
        else:
            maillist.append(splitline[0])
    return maillist


path_newtag =  str(os.getenv("LQANALYZER_DIR" )) + "/scripts/setup/git_newtag.sh"
file_newtag= open(path_newtag,"r")

newtag=""
for line in file_newtag:
    if "itag=" in line:
        sline = line.split()
        if len(sline) == 1:
            sline = sline[0]
            sline = sline[6:-1]
            newtag= str(os.getenv("CATVERSION")) + str(sline)

file_newtag.close()

#os.system("source " +  str(os.getenv("LQANALYZER_DIR" )) + "/scripts/setup/git_newtag.sh")

if not  os.getenv("USER") == "jalmond":
    if "jalmond" in email_user:
        print "Email could not be set since email address is not set correctly in bin/catconfig."
        sys.exit()


email_user=""
maillist = GetCATAnalyzerMailList()
for xmail in maillist:
    email_user=email_user+xmail+","
email_user=email_user[:-1]
    

path_file_email="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email_newtag.sh"
file_email=open(path_file_email,"w")
file_email.write('cat /data2/CAT_SKTreeOutput/' + os.getenv("USER")  + '/email_newtag.txt | mail -s "New CATANALYZER tag ' + newtag + '" ' +str(email_user)+'')
file_email.close()

filejobsummary = open("/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email_newtag.txt","w")
filejobsummary.write("CATAnalyzer Tag Name: " + newtag +"\n")
filejobsummary.write("\n")
filejobsummary.write("_"*60+"\n")
filejobsummary.write("Summary/Definition:\n")
filejobsummary.write("\n")
filejobsummary.write("Data: Periods A-G\n")
os.system("bash " + os.getenv("LQANALYZER_DIR")+"/bin/submitSKTree.sh -D " + os.getenv("CATVERSION") + "> log")
logfile_cv = open("log","r")
printout=False
for line in logfile_cv:
    if "bunchCrossing" in line:
        printout=True
    if printout:
        if "pileup" in line:
            sline=line.split()
            if len(sline) == 2:
                filejobsummary.write(sline[0]+" " + sline[1]+" [1]\n")
        else:
            filejobsummary.write(line)
logfile_cv.close()
os.system("rm log")
filejobsummary.write("\n")
filejobsummary.write("_"*60+"\n")
filejobsummary.write("\n")
filejobsummary.write("New Git Checkout:\n") 
filejobsummary.write("#"*50+"\n")
filejobsummary.write("git clone https://github.com/jalmond/LQAnalyzer CATanalyzer\n")
filejobsummary.write("cd CATanalyzer\n")
filejobsummary.write("git checkout -b CatAnalyzer_13TeV_"+newtag + " " + newtag+"\n")
filejobsummary.write("source setup.sh\n")
filejobsummary.write("#"*50+"\n")
filejobsummary.write("\n")
filejobsummary.write("Git Merge(alternative to checking out new directory for each tag):\n")
filejobsummary.write("#"*55+"\n")
filejobsummary.write("cd $LQANALYZER_DIR\n")
filejobsummary.write("git commit -a \n")
filejobsummary.write("git checkout -b CatAnalyzer_13TeV_"+newtag + " " + newtag+"\n")
filejobsummary.write("git checkout <originalbranchname>\n")
filejobsummary.write("git merge  CatAnalyzer_13TeV_"+newtag +"\n")
filejobsummary.write("source setup.sh\n")
filejobsummary.write("#"*55+"\n")
filejobsummary.write("\n")
filejobsummary.write("_"*60+"\n")
filejobsummary.write("Instructions for flatcatuple production can be found at:\n")
filejobsummary.write("https://twiki.cern.ch/twiki/bin/viewauth/CMS/SNULQNtuples#v8_0_2\n")
filejobsummary.write("\n")
filejobsummary.write("_"*60)
filejobsummary.write("\n")
filejobsummary.write("Useful Twikis:")
filejobsummary.write("\n")
filejobsummary.write("[1] https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2016Analysis\n")
filejobsummary.write("CATTUPLE("+os.getenv("CATVERSION")+") GOOGLEDOC https://docs.google.com/spreadsheets/d/1rWM3AlFKO8IJVaeoQkWZYWwSvicQ1QCXYSzH74QyZqE/edit?alt=json#gid=1895591332\n")
filejobsummary.write("XSEC https://twiki.cern.ch/twiki/bin/view/CMS/GenXsecTaskForce\n")
filejobsummary.write("XSEC https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns\n")
filejobsummary.write("XSEC https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive\n")

filejobsummary.write("\n")
filejobsummary.write("_"*60+"\n")
filejobsummary.write("CATANALYZER TAG CHANGELOG::\n")
path_log = "/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/TagDiff_"+newtag+".txt"
if not os.path.exists(path_log):
    print "Tag diff log " + path_log + " needs creating"
    sys.exit()
file_log = open(path_log,"r")
for line in file_log:
    filejobsummary.write(line)
file_log.close()
filejobsummary.write("\n")
filejobsummary.write("_"*60+"\n")
filejobsummary.write("\n")
filejobsummary.write("Latest file list (used by sktree in CATANALYZER): \n")

path_filelist = "/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_CAT_mc_"+os.getenv("CATVERSION") +".txt"
file_filelist = open(path_filelist,"r")
for line in file_filelist:
    filejobsummary.write(line)
file_filelist.close()
filejobsummary.write("\n")


filejobsummary.close()
os.system("source " + path_file_email)
    
