import os,filecmp,sys

def SendEmail(localsummary, mastersummary):

    email_user=""
    configfile = os.getenv("LQANALYZER_DIR")+"/bin/catconfig"
    file_configfile = open(configfile,"r")
    for line in file_configfile:
        if "email" in line:
            sline = line.split()
            if len(sline) > 2:
                email_user= sline[2] 
    file_configfile.close()

    if not  os.getenv("USER") == "jalmond":
        if "jalmond" in email_user:
            print "Email could not be set since email address is not set correctly in bin/catconfig."
            return

    path_file_email="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email.sh"
    file_email=open(path_file_email,"w")
    file_email.write('cat /data2/CAT_SKTreeOutput/' + os.getenv("USER")  + '/email.txt | mail -s  "Update in selection file for 2016 Analysis:" '+str(email_user)+'') 
    file_email.close()

    filejobsummary = open("/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email.txt","w")

    titleline=""
    for line in localsummary:
        if "ID" in line:
            titleline=line
        nochange=False
        line2change=""
        sline = line.split()
        id1=""
        id2=""
        if len(sline) >1:
            id1=sline[1]
        for line2 in mastersummary:
            sline2 = line2.split()
            if len(sline2) >1:
                id2=sline[1]
            else:
                id2=""
            if id1 == id2:    
                line2change= line2
            if line == line2:
                nochange=True
        if not nochange:
            if not line2change:
                filejobsummary.write("New ID Added"+"\n")
                filejobsummary.write(titleline+"\n")
                filejobsummary.write(line+"\n")
                filejobsummary.write("\n")
                print "New ID Added"
                print line

            else:
                filejobsummary.write(titleline+"\n")
                filejobsummary.write("original selection:\n")
                filejobsummary.write(line2change+"\n")
                filejobsummary.write("changed to:\n")
                filejobsummary.write(line+"\n")
                filejobsummary.write("\n")
                print "original selection:"
                print line2change
                print "changed to:"
                print line
    filejobsummary.close()
    os.system("source " + path_file_email)
    


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-s", "--s", dest="s", default="123",help="tag")

(options, args) = parser.parse_args()
seltag=options.s

path_master = "/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/Selection/"
path_local= os.getenv("LQANALYZER_DIR") + "/CATConfig/SelectionConfig/"

selfile=""
if seltag == "electron":
    selfile="electrons.sel"
elif seltag == "muon":
    selfile="muons.sel"
elif seltag == "jet":
    selfile=jets.sel
else:
    print "invalid input. must be electron,jet or muon"

if not selfile:
    print "No input given: use -s 'electron' for example"
    sys.exit()

path_master = path_master+"/"+selfile
path_local = path_local + "/"+selfile

if not filecmp.cmp(path_master,path_local):

    localcopy=[]
    file_local = open(path_local,"r")
    for line in file_local:
        localcopy.append(line)
    file_local.close()
    
    mastercopy=[]
    file_master = open(path_master,"r")
    for line in file_master:
        mastercopy.append(line)
    file_master.close()

    os.system("cp " + path_local + " " + path_master)
    SendEmail(localcopy,mastercopy)
    print "Updating file " + path_master
else:
    print "No difference in files"
