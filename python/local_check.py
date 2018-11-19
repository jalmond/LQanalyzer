import os

def MakeDirectory(dirpath):
    predir=dirpath
    predir=predir.replace(os.getenv("yeartag"),"")
    if not os.path.exists(predir):
        os.system("mkdir " + predir)
    if not os.path.exists(dirpath):
        os.system("mkdir " + dirpath)


#### setup env variables
binDir = os.getenv("LQANALYZER_DIR")+ "/bin/"

### check branch info
fr = open(binDir + 'Branch.txt', 'r')
sline=0
for line in fr:
    if sline ==0:
        print "Local code uses CATAnalyser version : " +  line
        print "Look up code at https://github.com/jalmond/LQanalyzer/tree/" + line
    if sline == 1:
        print "..."
    sline=sline+1

print "Running on git tag : " +  os.getenv("CATTAG")    
   

tag_dir  = os.getenv("LQANALYZER_LIB_PATH")+ "/" + os.getenv("CATTAG");

localfiledir = os.getenv("LQANALYZER_FILE_DIR")

txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"

if not os.path.exists(tag_dir):

    ####  NEW GIT TAG
    
    libpath=os.getenv("LQANALYZER_LIB_PATH")

    if os.path.exists(libpath):
        os.system("rm -r " + libpath)
        os.system("mkdir  " +libpath)

    MakeDirectory(tag_dir)
            
    if "cms.snu.ac.kr" in str(os.getenv("HOSTNAME")):
        MakeDirectory("/data8/DATA/CAT_SKTreeOutput/" + os.getenv("USER"))
        MakeDirectory("/data7/DATA/CAT_SKTreeOutput/" + os.getenv("USER"))

    else:
        MakeDirectory("/cms/scratch/SNU/CATAnalyzer/" + os.getenv("USER"))
        MakeDirectory("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/" + os.getenv("USER"))
        MakeDirectory(os.getenv("LQANALYZER_BATCHLIB_PATH"))
    

    print "Copying all latest rootfiles for use in analysis"


    if not os.path.exists(os.getenv("LQANALYZER_DIR")+ "/data/Luminosity/80X/") or not os.path.exists(os.getenv("LQANALYZER_DIR")+ "/data/Luminosity/76X/"):
        os.system("rm -r " + os.getenv("LQANALYZER_DIR")+ "/data/")

    MakeDirectory((os.getenv("LQANALYZER_DIR")+ "/data/"))
    
    yeartags = ["80X", "94X"]
    
    for yt in yeartags:
        snulumifiledir = os.getenv("LQANALYZER_DIR")+ "/data/Luminosity/"+yeartag
        snufakefiledir = os.getenv("LQANALYZER_DIR")+ "/data/Fake/"+yeartag
        snutriggerfiledir = os.getenv("LQANALYZER_DIR")+ "/data/Trigger/"+yeartag
        snupileupfiledir= os.getenv("LQANALYZER_DIR")+ "/data/Pileup/"+yeartag
        snuidfiledir= os.getenv("LQANALYZER_DIR")+ "/data/ID/"+yeartag
        snubtagfiledir = os.getenv("LQANALYZER_DIR")+ "/data/BTag/"+yeartag
        rochdir=os.getenv("LQANALYZER_DIR")+ "/data/rochester/"+yeartag
        localfiledir = os.getenv("LQANALYZER_FILE_DIR")
        samples_version = str(os.getenv("CATVERSION"))

        if yt == "94X":
            localfiledir = os.getenv("LQANALYZER_FILE2017_DIR")
            samples_version= "v9-4-9v2"



        MakeDirectory(snulumifiledir)
        os.system("cp " + localfiledir + "/Luminosity/*"+samples_version+".txt " + snulumifiledir)
        MakeDirectory(snufakefiledir)
        os.system("cp " + localfiledir + "/Fake/*.root " + snufakefiledir)
        MakeDirectory(snutriggerfiledir)
        os.system("cp " + localfiledir + "/Trigger/*.root " + snutriggerfiledir)
        os.system("cp " + localfiledir + "/Trigger/*.txt " + snutriggerfiledir)
        MakeDirectory(snupileupfiledir)
        os.system("cp " + localfiledir + "/Pileup/*.root "+ snupileupfiledir)
        MakeDirectory(snuidfiledir)
        os.system("cp " + localfiledir + "/ID/*.root " + snuidfiledir)
        if os.path.exists(snubtagfiledir):
            os.system("rm -r " + snubtagfiledir)
        MakeDirectory(snubtagfiledir)
        os.system("cp " + localfiledir + "/BTag/*.csv " + snubtagfiledir)
        MakeDirectory(rochdir)
        os.system("cp -r " + localfiledir + "/rochester/rcdata.2016.v3/ " + rochdir) 



    
    mount_name="/data2/DATA/"

    if  "ui" in str(os.getenv("HOSTNAME")):
        mount_name="/cms/scratch/SNU/CATAnalyzer"



    new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")
    print "cleaning up home directory"
    print new_out
    if not os.path.exists(new_out):
        os.system("mkdir " + new_out)

    if not "cmscluster.snu.ac.kr" in str(os.getenv("HOSTNAME")):
        if "cms.snu.ac.kr" in str(os.getenv("HOSTNAME")):
            MakeDirectory("/data7/DATA/CAT_SKTreeOutput/"+os.getenv("USER"))
            MakeDirectory("/data8/DATA/CAT_SKTreeOutput/"+os.getenv("USER"))

    new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/"
    if not os.path.exists(new_out):
        MakeDirectory(new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/"
        MakeDirectory(new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/output/"
        MakeDirectory(new_out)
        new_out=mount_name+"/CAT_SKTreeOutput/JobOutPut/"+os.getenv("USER")+"/LQanalyzer/data/output/CAT/"
        MakeDirectory(new_out)

    print "using branch for first time: All codes are being recompiled"
    os.system("source bin/Make/make_clean_newbranch.sh")
    


fakelib = os.getenv("LQANALYZER_LIB_PATH") + "/libHNCommonLeptonFakes80X.so"
if not os.path.exists(fakelib):
    print "source bin/Make/make_fake_lib.sh 80X"
    os.system("source bin/Make/make_fake_lib.sh 80X")

fakelib = os.getenv("LQANALYZER_LIB_PATH") + "/libHNCommonLeptonFakes94X.so"
if not os.path.exists(fakelib):
    print "source bin/Make/make_fake_lib.sh 94X"
    os.system("source bin/Make/make_fake_lib.sh 94X")



