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

print "Running on tag : " +  os.getenv("CATTAG")    
   

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

tag_dir  = os.getenv("LQANALYZER_LIB_PATH")+ "/" + os.getenv("CATTAG");

localfiledir = os.getenv("LQANALYZER_FILE_DIR")
snufiledir = os.getenv("FILEDIR")
txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"
old_lib_slc5=os.getenv("LQANALYZER_DIR")+ "/LQLib/slc5/"
old_lib_slc6=os.getenv("LQANALYZER_DIR")+ "/LQLib/slc6/"


if not os.path.exists(tag_dir):
    libpath=os.getenv("LQANALYZER_LIB_PATH")
    if os.path.exists(libpath):
        os.system("rm -r " + libpath)
        os.system("mkdir  " +libpath)
    os.system("mkdir " + tag_dir)

    print "Copying all latest rootfiles for use in analysis"
    os.system("cp " + localfiledir + "/*.root " + snufiledir )
    os.system("cp " + localfiledir + "/*.csv " + snufiledir )
    #os.system("cp " + localfiledir + "/*cat*.txt " + snufiledir )
    
    logdir =  os.getenv("LQANALYZER_LOG_8TeV_PATH")
    if os.path.exists(logdir):
        os.system("rm -r "+logdir)

    old_out=os.getenv("LQANALYZER_DIR")+"/data/output/CAT/"

    
    mount_name="/data2"
    if "cmscluster.snu.ac.kr" in str(os.getenv("HOSTNAME")):
        mount_name="/data4"

    new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")
    print "cleaning up home directory"
    if not os.path.exists(new_out):
        os.system("mkdir " + new_out)

    new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/"
    if not os.path.exists(new_out):
        os.system("mkdir " + new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/"
        os.system("mkdir " + new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/output/"
        os.system("mkdir " + new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/output/CAT/"
        os.system("mkdir " + new_out)
        os.system("mv "+ old_out + "/* " + new_out)
        print "Moving output to " + new_out
        if os.path.exists(old_out):
            os.system("rm -r " + os.getenv("LQANALYZER_DIR")+"/data/output/")
            
        
    if os.path.exists(old_lib_slc5):
        os.system("rm -r " + old_lib_slc5)
    if os.path.exists(old_lib_slc6):
        os.system("rm -r " + old_lib_slc6)
    
    print "using branch for first time: All codes are being recompiled"
    os.system("source bin/Make/make_clean_newbranch.sh")
    

fakelib = os.getenv("LQANALYZER_LIB_PATH") + "/libHNCommonLeptonFakes.so"

if not os.path.exists(fakelib):
    os.system("source bin/Make/make_fake_lib.sh")



