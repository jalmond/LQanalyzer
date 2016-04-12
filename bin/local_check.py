import os

binDir = os.getenv("LQANALYZER_DIR")+ "/bin/"
fr = open(binDir + 'Branch.txt', 'r')
sline=0
for line in fr:
    if sline ==0:
        print "Local code uses LQanalyser version : " +  line
        print "Look up code at https://github.com/jalmond/LQanalyzer/tree/" + line
    if sline == 1:
        print "..."
    sline=sline+1
   

if os.path.exists("LQRun/Macros/"):
    print "Cleaning up directory that failed to be removed by git merge"
    os.system("rm -r LQRun/Macros/")
if os.path.exists("LQRun/job_output/"):
    print "Cleaning up directory that failed to be removed by git merge"
if os.path.exists("LQRun/ExampleSubmit/job_output/"):
    print "Cleaning up directory job_output/"
    os.system("rm -r LQRun/*/job_output/")
if os.path.exists("LQRun/runJob_1.C"):
    print "Cleaning up file that failed to be removed by git merge"
    os.system("rm LQRun/runJob_1.C")
if os.path.exists("LQCycle/"):
    print "Cleaning up directory that failed to be removed by git merge"
    os.system("rm -r LQCycle/")

###### LIB DIRECTORIES
april16dir = os.getenv("LQANALYZER_LIB_PATH")+ "/April16/"
libpath=os.getenv("LQANALYZER_LIB_PATH")
####### FILE DIR
localfiledir = os.getenv("LQANALYZER_FILE_DIR")
snufiledir = os.getenv("FILEDIR")
old_lib_slc5=os.getenv("LQANALYZER_DIR")+ "/LQLib/slc5/"
old_lib_slc6=os.getenv("LQANALYZER_DIR")+ "/LQLib/slc6/"

output_mounted="/data2/"
if "cmscluster.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    output_mounted="/data4/"


if not os.path.exists(april16dir):
    
    if os.path.exists(libpath):
        os.system("rm -r " + libpath)
        os.system("mkdir  " +libpath)
        
    os.system("mkdir " + april16dir)

    print "Copying all latest rootfiles for use in analysis:"

    os.system("cp " + localfiledir + "* " + snufiledir )
      
    logdir =  os.getenv("LQANALYZER_LOG_8TeV_PATH")
    if os.path.exists(logdir):
        print "Deleting old logfile directory.... since this is redundant"

        os.system("rm -r "+logdir)
    old_out=os.getenv("LQANALYZER_DIR")+"/data/output/"
    new_out=output_mounted + "/LQ_SKTreeOutput/JobOutPut/"+os.getenv("USER")
    print "cleaning up home directory:"
    if not os.path.exists(new_out):
        os.system("mkdir " + new_out)
    new_out=output_mounted + "/LQ_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/"
    if not os.path.exists(new_out):
        os.system("mkdir " + new_out)
        new_out=output_mounted + "/LQ_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/"
        os.system("mkdir " + new_out)
        new_out=output_mounted + "/LQ_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/output/"
        os.system("mkdir " + new_out)
        if os.path.exists(old_out):
            os.system("mv "+ old_out + "/* " + new_out)
        print "Recommend output not to be in /home/ dir:"
        print "$LQANALYZER_OUTPUT_PATH now set to: " + str(os.getenv("LQANALYZER_OUTPUT_PATH")) 
        print "Moving output file to " + new_out


        if os.path.exists(old_out):
            os.system("rm -r " + os.getenv("LQANALYZER_DIR")+"/data/output/")

    if os.path.exists(old_lib_slc5):
        os.system("rm -r " + old_lib_slc5)
    if os.path.exists(old_lib_slc6):
        os.system("rm -r " + old_lib_slc6)
            

    print "using branch for first time: All codes are being recompiled"
    
    os.system("source bin/make/make_clean_newbranch.sh")

else:
    fakelib = os.getenv("LQANALYZER_LIB_PATH") + "/libHNCommonLeptonFakes.so"

    if not os.path.exists(fakelib):
        print "For some reason libHNCommonLeptonFakes.so is missing from lib path. Will recompile code:"
        os.system("source bin/make/make_fake_lib.sh")

    btaglib = os.getenv("LQANALYZER_LIB_PATH") + "/BTagSFUtil_C.so"
    if not os.path.exists(btaglib):
        print "For some reason BTagSFUtil_C.so is missing from lib path. Will recompile code:"
        os.system("source bin/make/make_clean_newbranch.sh")


    rocherlib = os.getenv("LQANALYZER_LIB_PATH") + "/librochcor2012.so"

    if not os.path.exists(rocherlib):
        print "For some reason librochcor2012  is missing from lib path. Will recompile code:"
        os.system("source bin/make/make_rocher_lib.sh")
