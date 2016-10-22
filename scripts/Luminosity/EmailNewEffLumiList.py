import os

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
    
def SendEmail(catversion, catuser, message, jobsummary, maillist) :

    email_user=""
    for xmail in maillist:
        email_user=email_user+xmail+","
    email_user=email_user[:-1]
    path_file_email=os.getenv("LQANALYZER_DIR")+"/scripts/email.sh"
    file_email=open(path_file_email,"w")
    file_email.write('cat '+ os.getenv("LQANALYZER_DIR")+'/scripts/email.txt  | mail -s "' + catuser+ ': New Effective Luminosity file datasets_snu_CAT_mc_'+catversion+'.txt" ' + str(email_user)+'')
    file_email.close()

    filejobsummary = open("email.txt","w")

    for x in message:
        filejobsummary.write(x)
    filejobsummary.write("\n")
    for eline in jobsummary:
        filejobsummary.write(eline)
    filejobsummary.close()
    os.system("source " + path_file_email)
    os.system("rm email.sh")
    os.system("rm email.txt")



##########################################################################################
##########################################################################################
############### Fill message for reason of making new sample                                                                                                                                                                                                           ##########################################################################################
########################################################################################## 

NewList=True

message = []
if NewList:
    message.append("This is a new file for a new cattuple production\n")
else:
    message.append("This file includes the following new samples: <samplename> \n")
    #message.append("This file includes corrections to xsec for several samples\n")                                                                                                                                                                                     



    
from optparse import OptionParser
parser = OptionParser()
parser.add_option("-c", "--c", dest="c", default="123",help="cv")

(options, args) = parser.parse_args()
catversion=options.c

if not "v8" in catversion:
    catversion=os.getenv("CATVERSION")


path_newefflumi="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/datasets_snu_CAT_mc_"+catversion +".txt"

file_newefflumi=open(path_newefflumi,"r")

Copy_File=[]

if NewList:
    for line in file_newefflumi:
        Copy_File.append(line)
    file_newefflumi.close()
else:
    Copy_File.append("This is a list of differenecs with respect to previous file")
    difflogpath = os.getenv("LQANALYZER_DIR")+"/scripts/difflog.txt"
    file_difflog = open(difflogpath,"r")
    for line in file_difflog:
        Copy_File.append(line)
    file_difflog.close()


emaillist=GetCATAnalyzerMailList()

SendEmail(catversion, os.getenv("USER"), message, Copy_File, emaillist)

