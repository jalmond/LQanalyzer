import os,sys,getpass

from decimal import *
getcontext().prec = 2

path_master="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION") +".txt"
path_skel_master="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFileSkeleton.txt"

if not os.path.exists(path_master):
    os.system("cp /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFileSkeleton_newversion.txt " + path_master )

if not os.path.exists("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()):
    os.system("mkdir  /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser())

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filetag=options.x
    
path_job="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/statlog_time" + filetag + ".txt"
path_tmpmaster="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/MasterFile_tmp" + filetag + ".txt"

os.system("cp " + path_master + " " + path_tmpmaster)


file_job=open(path_job,"r")
file_tmpmaster=open(path_tmpmaster,"r")

path_cluster="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/Cluster_" + filetag + ".txt"



time=0.
ntimes=0.
pretime=0.
jobtime=0.
lastjobtime=0.
cycle=""
sample=""
username=""
catversion=""
skim=""
cattag=""
day=""
month=""
year=""
date=""
ptime=""
stream=""
jobcrash=""
filesize=""
njobs=""
nfiles=""
memoryusage_p=""
memoryusage_v=""
nclusterjobs=""
clusterid=""
for line in file_job:
    splitline  = line.split()
    if len(splitline) < 2:
        continue
    if "user" == splitline[0]:
        username= splitline[1]
    if "-c" == splitline[0]:    
        cycle=splitline[1]
    if "outputfile_size" == splitline[0]:
        filesize=splitline[1]
    if "ClusterIDs" == splitline[0]:
        clusterid=splitline[1]
    if "-v" == splitline[0]:
        catversion=splitline[1]
    if "-s" == splitline[0]:
        stream=splitline[1]
    if "time"  == splitline[0]:
        time=float(splitline[1])
    if "job_time"  == splitline[0]:
        jobtime=float(splitline[1])
    if "last_job_time"  == splitline[0]:
        lastjobtime=float(splitline[1])
    if "sample" ==  splitline[0]:
        sample=splitline[1]
    if "-m" ==  splitline[0]:
        skim=splitline[1]
    if "cattag" ==  splitline[0]:
        cattag=splitline[1]  
    if "Success=" ==  splitline[0]:
        jobcrash=splitline[1]
    if "Njobs" ==  splitline[0]:
        njobs=splitline[1]
    if "NFiles" ==  splitline[0]:
        nfiles=splitline[1]
        
    if "memoryusage_p" ==  splitline[0]:        
        memoryusage_p=splitline[1]
    if "memoryusage_v" ==  splitline[0]:
        memoryusage_v=splitline[1]
    if "201" in line:
        if "time" not in line:
            entries = line.split()
            month=entries[1]
            day=entries[0]
            date=entries[2]
            ptime=entries[3] 
            year=entries[5]
file_job.close()


file_cluster=open(path_cluster,"r")
for line in file_cluster:
    splitline = line.split()
    nclusterjobs=splitline[4]+":"+splitline[6]+":"+splitline[8]+":"+splitline[10]+":"+splitline[12]+":"+splitline[14]+":"+splitline[16]+":"+splitline[18]+":"+splitline[20]



path_jobinfo="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+month+"_"+year+".txt"
if not os.path.exists(path_jobinfo):
    with open(path_jobinfo, "w") as myfile:
          myfile.write("Summary of CatAnalyzer Processes: month="+month+" year=" +year+"\n")
    os.system("chmod 775 " + path_jobinfo)

if len(sample) < 2:
    sample=stream+"_"+sample

with open(path_jobinfo, "a") as myfile:
    myfile.write(username+" "+str(cycle)+" cv: "+str(catversion)+" "+str(cattag)+" sample: "+str(sample)+" skim: "+str(skim)+" njobs: " + str(njobs) + " nfiles: " + str(nfiles) + " start_time: "+str(day)+" : "+str(month)+" : "+str(year)+" : "+str(ptime)+" proc.time: "+str(time)+ " job_time: "+str(jobtime)+ " last_job_time: " + str(lastjobtime)+ " output_file_size: " + str(filesize) + " mem_p: " + str(memoryusage_p) + " mem_v: " + str(memoryusage_v)+ " job_complete= "+ jobcrash + " cluster_info: " + nclusterjobs+ " job_cluster: " + str(clusterid) + "\n")

os.system("rm " + path_cluster)

if "SKTree_LeptonSkim" in skim:
    sample +="_lepton"
if "SKTree_DiLepSkim"in skim:
    sample +="_dilepton"

if username != getpass.getuser():
    print "Issue with username"
    sys.exit()
    


correctuser=False
correctCode=False

newsample=True
newUser=True
newCycle=True
for line in file_tmpmaster:
    if "USER" in line:
        if username in line:
            correctuser=True
            newUser=False
        else:
            correctuser=False
    if "Code:" in line:
        if cycle in line:
            correctCode=True
            newCycle=False
        else:
            correctCode=False
    if correctuser:
        if correctCode:
            if sample in line:
                splitline  = line.split()
                if len(splitline) > 2:
                    ntimes = float(splitline[2])
                    pretime = float(splitline[3])
                    newsample=False

file_tmpmaster.close()


sample_len=len(sample)
sample_title="Sample name   :"
sample_title_len=len(sample_title)
gap1=" "
#while len(gap1) < (len(str(sample_title_len)) - len(str(sample_len))):
#    gap1+=" "


nproc_len=len(str(int(ntimes)+1))
nproc_title=" Number of times processed :"
nproc_title_len=len(nproc_title)
gap2=" "
#while len(gap2) < (len(str(nproc_title_len)) - len(str(nproc_len))):
#    gap2+=" "

time_title=" Average processing time :"
filesize_title=" Average file size"


if newsample:
    print "Processing sample " + sample + " for the first time"
if newUser:
    print "User is being add to statistics file: Now all jobs stats are saved."
    file_newuser_master=open(path_master,"w")
    file_tmpmaster3=open(path_tmpmaster,"r")

    for line in file_tmpmaster3:
        file_newuser_master.write(line)
    file_tmpmaster3.close()
    file_newuser_master.write("%%%%%%%%%%%%%%%%%%%%%%%% USER  " + username + " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n")
    file_newuser_master.write("########  Code:  " + cycle +"#################################################\n")
    file_newuser_master.write("################ CatVersion : "+ catversion +" \n")
    file_newuser_master.write("################ " + sample_title + nproc_title + time_title + filesize_title +"\n")
    file_newuser_master.write("################\n")
    file_newuser_master.write("####################################################################################\n")
    file_newuser_master.close()
    os.system("cp " + path_master + " " + path_tmpmaster)
elif newCycle:
    file_newuser_master=open(path_master,"w")
    file_tmpmaster3=open(path_tmpmaster,"r")

    for line in file_tmpmaster3:
        if username in line:
            file_newuser_master.write(line)
            file_newuser_master.write("########  Code:  " + cycle + "   #################################################\n")
            file_newuser_master.write("################ CatVersion : "+ catversion +" \n")
            file_newuser_master.write("################ " + sample_title + nproc_title + time_title + filesize_title + "\n")
            file_newuser_master.write("################\n")
            file_newuser_master.write("####################################################################################\n")
        else:
            file_newuser_master.write(line)

    file_tmpmaster3.close()
    file_newuser_master.close()
    os.system("cp " + path_master + " " + path_tmpmaster)


file_master=open(path_master,"w")
    
newtime= (time+ (pretime*ntimes)) / (ntimes+1)



correctuser=False
correctCode=False


file_tmpmaster2=open(path_tmpmaster,"r")


for line in file_tmpmaster2:
    if "USER" in line:
        if username in line:
            correctuser=True
        else:
            correctuser=False
    if correctuser:
        if "Code:" in line:
            if cycle in line:
                correctCode=True
            else:
                correctCode=False
        if correctCode:
             if newsample:
                 if sample_title in line:
                     file_master.write("################ " + sample_title + nproc_title + time_title + filesize_title+" \n")
                     file_master.write("################ "+ sample+ gap1 + str(int(ntimes)+1) + gap2 + str(newtime) + " " + str(filesize) + "  \n")
                 else:
                    file_master.write(line)
             else:
                 if sample in line:
                     file_master.write("################ "+sample+ gap1 + str(int(ntimes)+1) + gap2 + str(newtime) + " " + str(filesize) + "  \n")
                 else:
                     file_master.write(line)
        else:
            file_master.write(line)
    else:
        file_master.write(line)


os.system("rm " + path_tmpmaster)
file_tmpmaster2.close()
file_master.close()

