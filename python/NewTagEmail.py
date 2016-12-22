import os

path_jobpre="/data1/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    path_jobpre="/data2/"

an_jonpre="/data2/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    an_jonpre="/data4/"


def SendEmail(cattag, email_user):


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

    path_file_email=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email.sh"
    file_email=open(path_file_email,"w")
    file_email.write('cat  '+an_jonpre+'/CAT_SKTreeOutput/' + os.getenv("USER")  + '/email.txt | mail -s "New Tag: ' + cattag + '" '+str(email_user)+'')
    file_email.close()

    filejobsummary = open(an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/email.txt","w")
    tagdiff = path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATTag/TagDiff_"+cattag+".txt"
    file_tagdiff=open(tagdiff,"r")
    for eline in file_tagdiff:
        filejobsummary.write(eline)
    filejobsummary.close()
    os.system("source " + path_file_email)



from optparse import OptionParser
parser = OptionParser()
parser.add_option("-t", "--t", dest="t", default="123",help="tag")

(options, args) = parser.parse_args()
cattag=options.t

SendEmail(cattag,)
