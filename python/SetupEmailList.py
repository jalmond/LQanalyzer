import os,sys


path_emailconfig = os.getenv("LQANALYZER_MOD") +"emailconfig.txt"                                                                                                               

path_catconfig= os.getenv("LQANALYZER_DIR") + "/bin/catconfig"

file_catconfig= open(path_catconfig,"r")
email_address=""
for line in file_catconfig:
    if "email" in line:
        splitline = line.split()
        if len(splitline) == 3:
            email_address=splitline[2]
        else:
            print "ERROR in email in bin/catconfig. Please Fix"
            sys.exit()
file_catconfig.close()
            

email_in_list=False
file_emailconfig = open(path_emailconfig,"r")
copy_email_list=[]
for line in file_emailconfig:
    copy_email_list.append(line)
    if email_address:
        if email_address in line:
            email_in_list=True

file_emailconfig.close()

if not email_in_list:
    print "Adding email address: " + email_address + " to CATAnalyzer emaillist"
    file_emailconfig = open(path_emailconfig,"w")
    for xline in copy_email_list:
        file_emailconfig.write(xline)
    file_emailconfig.write(email_address)
    file_emailconfig.close()
