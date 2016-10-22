import os, random,string,sys


def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

def SendEmail(catversion, catuser, rand_string, mailadd):

    email_user=mailadd
    path_file_email=os.getenv("LQANALYZER_DIR")+"/scripts/email.sh"
    file_email=open(path_file_email,"w")
    file_email.write('cat '+ os.getenv("LQANALYZER_DIR")+'/scripts/email.txt  | mail -s "Initialising email for user ' + str(catuser) +' in CATANALYZER" ' + str(email_user)+'')
    file_email.close()

    filejobsummary = open(os.getenv("LQANALYZER_DIR")+"/scripts/email.txt","w")
    filejobsummary.write("Dear User\n")
    filejobsummary.write("You are recieving this email since you are using setting up catanalyzer tag: and your email address is being add to the CatAnalyzer email list\n")
    filejobsummary.write("Please user the confirmation ID: " + rand_string +"\n" )
    filejobsummary.write("\n")
    filejobsummary.close()
    os.system("source " + path_file_email)
    os.system("rm " + os.getenv("LQANALYZER_DIR")+"/scripts/email.sh")
    os.system("rm " + os.getenv("LQANALYZER_DIR")+"/scripts/email.txt")


def AddEmailToConfig(mail_add):
    path_config=os.getenv("LQANALYZER_DIR")+"/bin/catconfig"
    file_config = open(path_config,"r")
    
    config_content=[]
    for line in file_config:
        config_content.append(line)
    file_config.close()
    file_config = open(path_config,"w")
    for xline in config_content:
        file_config.write(xline)
        if "editor" in xline:
            file_config.write("email = " + mail_add+"\n")
    file_config.close() 

path_config=os.getenv("LQANALYZER_DIR")+"/bin/catconfig"

LQANALYZER_MOD="/data1/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
if not os.path.exists(path_config):
    os.system("cp " + LQANALYZER_MOD + "/catconfig   " +  path_config)
    print "File " + path_config + " does not exist. Remaking file"


file_config = open(path_config,"r")

emal_is_setup=False
for line in file_config:
    if "email" in line:
        emal_is_setup=True

file_config.close()

cattag=os.getenv("CATTAG")

if not emal_is_setup:
    rand_string=id_generator()
    email_Address = raw_input("No email setup in CATANALZER: Type email address: ")
    email_Address2 = raw_input("confirm email address: ")
    if email_Address == email_Address2:
        SendEmail(cattag, os.getenv("USER"),rand_string,email_Address)
        incorrectID=True
        tries =0 
        while incorrectID:
            confID = raw_input("Enter confirmation ID sent to above email address: ")
            tries = tries + 1
            if not confID == rand_string:
                if tries == 3:
                    sys.exit()
                tries_left= 3 - tries
                print "Incorrect confirmation ID. " + str(tries_left) + " left"
            else:
                incorrectID=False
    
        AddEmailToConfig(email_Address)        
    else:
        print "Email address confirmation does not agree with original email address."
        sys.exit()

