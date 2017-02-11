import os 

os.system("git config user.github > log")
file_log=open("log","r")
gitname=""
for line in file_log:
    sline=line.split()
    if len(sline) == 1:
        gitname=line[0]
file_log.close()

if not gitname:
    print "No github name found. Please make sure ~/.gitconfig exists and user.github is set"
    sys.exit()

os.system("https://github.com/"+gitname+"/LQanalyzer > log")

file_log=open("log","r")
lqanalyzer_exists=True
for line in file_log:
    if "Not Found" in line:
        lqanalyzer_exists=False
file_log.close()

if not lqanalyzer_exists:
    print "LQanalyzer is not forked in https://github.com/"+gitname
    
