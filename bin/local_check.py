import os

binDir = os.getenv("LQANALYZER_DIR")+ "/bin/"
fr = open(binDir + 'Branch.txt', 'r')
sline=0
for line in fr:
    if sline ==0:
        print "Local code uses CATAnalyser version : " +  line
        print "Look up code at https://github.com/jalmond/LQanalyzer/tree/" + line
    if sline == 1:
        print "..."
    sline=sline+1
    
   

if os.path.exists("LQRun/Macros/"):
    os.system("rm -r LQRun/Macros/")
if os.path.exists("LQRun/job_output/"):
    print "Cleaning up directory that failed to be removed by git merge"
    os.system("rm -r LQRun/job_output/")
if os.path.exists("LQRun/runJob_1.C"):
    print "Cleaning up file that failed to be removed by git merge"
    os.system("rm LQRun/runJob_1.C")
if os.path.exists("LQCycle/"):
    print "Cleaning up directory that failed to be removed by git merge"
    os.system("rm -r LQCycle/")


march16dir2 = os.getenv("LQANALYZER_LIB_PATH")+ "/March16v2/"
march16dir = os.getenv("LQANALYZER_LIB_PATH")+ "/March16/"
oct15dir  = os.getenv("LQANALYZER_LIB_PATH")+ "/Oct15/"
april15dir = os.getenv("LQANALYZER_LIB_PATH")+ "/April15/"

localfiledir = os.getenv("LQANALYZER_FILE_DIR")
snufiledir = os.getenv("FILEDIR")
txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"

if not os.path.exists(march16dir2):
    os.system("mkdir " + march16dir2)
    if os.path.exists(march16dir):
        os.system("rm -r " + march16dir)
    if os.path.exists(oct15dir):    
        os.system("rm -r " + oct15dir)
    if os.path.exists(april15dir):
        os.system("rm -r " + april15dir)
    print "Copying all latest rootfiles for use in analysis"
    os.system("cp " + localfiledir + "/*.root " + snufiledir )
    
    print "using branch for first time: All codes are being recompiled"
    os.system("source bin/make_clean_newbranch.sh")
    

fakelib = os.getenv("LQANALYZER_LIB_PATH") + "libHNCommonLeptonFakes.so"

if not os.path.exists(fakelib):
    os.system("source bin/make_fake_lib.sh")

