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
    if "itag" in line:
        sline = line.split()
        if len(sline) == 2:
            sline = sline[1]
            sline = sline[1:-1]
            newtag= str(os.getenv("CATVERSION")) + str(sline)

file_newtag.close()

os.system("source " +  str(os.getenv("LQANALYZER_DIR" )) + "/scripts/setup/git_newtag.sh")

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
filejobsummary.write("New Tag:" + newtag +"\n")

filejobsummary.write("Changelog:\n")
path_log = "/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/TagDiff_"+newtag+".txt"
if not os.path.exists(path_log):
    print "Tag diff log " + path_log + " needs creating"
    sys.exit()
file_log = open(path_log,"r")
for line in file_log:
    filejobsummary.write(line+"\n")
file_log.close()
filejobsummary.write("\n")
filejobsummary.write("Latest file list: \n")
path_filelist = "/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_CAT_mc_"+os.getenv("CATVERSION") +".txt"
file_filelist = open(path_filelist,"r")
for line in file_filelist:
    filejobsummary.write(line+"\n")
file_filelist.close()
filejobsummary.write("\n")


filejobsummary.close()
os.system("source " + path_file_email)
    
