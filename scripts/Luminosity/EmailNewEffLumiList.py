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
    file_email.write('cat '+ os.getenv("LQANALYZER_DIR")+'/scripts/email.txt  | mail -s "' + catuser+ ': REPORT: Effective Luminosity file datasets_snu_CAT_mc_'+catversion+'.txt" ' + str(email_user)+'')
    file_email.close()

    filejobsummary = open(os.getenv("LQANALYZER_DIR")+"/scripts/email.txt","w")

    for x in message:
        filejobsummary.write(x)
    filejobsummary.write("\n")
    for eline in jobsummary:
        filejobsummary.write(eline)
    filejobsummary.close()
    os.system("source " + path_file_email)
    os.system("rm " + os.getenv('LQANALYZER_DIR')+"/scripts/email.sh")
    os.system("rm " + os.getenv('LQANALYZER_DIR')+"/scripts/email.txt")



##########################################################################################
##########################################################################################
############### Fill message for reason of making new sample                                                                                                                                                                                                           ##########################################################################################
########################################################################################## 

def EmailNewList(catversion, newsamplelist):
    message = []
   
    if not "v8" in catversion:
        catversion=os.getenv("CATVERSION")

    message.append("ADDITIONAL samples added to effective luminosity file for a new cattuple production["+catversion+"]\n")
    message.append("\n")
    message.append("")
    file_samplelist = open(samplelist,"r")
    for x in file_xseclist:
        message.append(x)
    file_samplelist.close()
    Copy_File=[]
    emaillist=GetCATAnalyzerMailList()
    
    SendEmail(catversion, os.getenv("USER"), message, Copy_File, emaillist)


def EmailNewXsecList(catversion, xseclist):
    message = []

    if not "v8" in catversion:
        catversion=os.getenv("CATVERSION")

    message.append("UPDATED xsec in effective luminosity file for a new cattuple production["+catversion+"]\n")
    message.append("\n")
    message.append("")
    file_xseclist = open(xseclist,"r")
    for x in file_xseclist:
        message.append(x)
    file_xseclist.close()    

    emaillist=GetCATAnalyzerMailList()

    Copy_File=[]
    SendEmail(catversion, os.getenv("USER"), message, Copy_File, emaillist)

def EmailNewSamples(catversion):
    message = []
    message.append("This file includes the following new samples: <samplename> \n")
    if not "v8" in catversion:
        catversion=os.getenv("CATVERSION")

    path_newefflumi="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/datasets_snu_CAT_mc_"+catversion +".txt"

    file_newefflumi=open(path_newefflumi,"r")

    Copy_File=[]
    Copy_File.append("This is a list of differenecs with respect to previous file")
    difflogpath = os.getenv("LQANALYZER_DIR")+"/scripts/difflog.txt"
    file_difflog = open(difflogpath,"r")
    for line in file_difflog:
        Copy_File.append(line)
    file_difflog.close()
    
    emaillist=GetCATAnalyzerMailList()
    SendEmail(catversion, os.getenv("USER"), message, Copy_File, emaillist)

