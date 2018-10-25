##################################################################
###configure Job
####################################################################
###timeWait=1#

###################################################
### Make Input File
####################################################
import os, getpass, sys,ROOT
from functions import *
from batch_function import *
from functions_submit import *

isKisti = ("ui" in str(os.getenv("HOSTNAME")))

DEBUGMODE=False

### submit_vardef sets variables from parser                                                                                                                                                               
from submit_vardef import *
if tmp_filename == "None":
    tmp_filename=""


###### New for 801.7 tag  
ClusterStatFile = os.getenv("LQANALYZER_DIR")+ "/python/CheckCluster.py"
os.system("python " + ClusterStatFile + " -x " + tagger + " -s " + sample)


if not skflag == "":
    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    print "skflag = " + skflag 

new_channel = channel.replace(":", "")

original_channel = new_channel

path_jobpre="/data1/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    path_jobpre="/data2/"

if  isKisti:
    path_jobpre="/cms/scratch/SNU/CATAnalyzer/"

    
    
### get command for batch queue
queue_list  = QUEUECOMMAND(queue,path_jobpre)
queue = queue_list[0]
queue_command=queue_list[1]


memoryusage_v=0
memoryusage_p=0

list_of_extra_lib = GetExtraLibNames(tmplist_of_extra_lib)

if DEBUG == "True":
    print "In debug mode"

print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
print "Running : " + cycle

useskim = UpdateSkimName(useskim)


if useskinput == "True": 
    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    print "Using SKTrees as input."
elif useskinput == "true":
    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    print "Using SKTrees as input."
else:
    print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    print "Using CATntuples as input"    


###########################################################################################
###########################################################################################
### DEFAULT  settings for runnning in batch mode. True for cmscluster.snu.ac.kr
running_batch=False

if number_of_cores == 1:
    print "running_batch = False  (default if njobs = 1)"
else:
    running_batch=True
    
if str(usebatch) == "NULL":
    if str(running_batch) == "True":
        print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
        print "Running batch job:"
        print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    else:
        print "Running standard root interactive job:"
else:
    if str(usebatch) == "False":
        running_batch=False
    elif  str(usebatch) == "false":
        running_batch=False
        


### In functions_submit
Printuseskinput(cycle, useskinput)


workoutput_mounted="/data2"
sktreeoutput=workoutput_mounted + "/DATA"
if len(sample)>1:
    if  sample == "H_v2" or sample == "H_v3":
        workoutput_mounted="/data7/DATA"
        sktreeoutput= "/data7/DATA"

merge_mounted="/data8/DATA"

 

if isKisti:
    merge_mounted = "/xrootd_user/"+getpass.getuser()+"/xrootd/"                                                                      
    workoutput_mounted="/cms/scratch/SNU/CATAnalyzer/"
    sktreeoutput="/xrootd_user/"+getpass.getuser()+"/xrootd/"

                    
##########################################################
### Make tmp directory for job
############################################################

tmpwork = MakeDir(workoutput_mounted+"/CAT_SKTreeOutput/"+ getpass.getuser() + "/")
mergetmpwork = MakeDir(merge_mounted+"/CAT_SKTreeOutput/")
mergetmpwork = MakeDir(merge_mounted+"/CAT_SKTreeOutput/"+ getpass.getuser() + "/")

timestamp_dir= MakeIterDir(tmpwork + "/" + cycle + "_joboutput_" +now() +"_" +os.getenv("HOSTNAME")+"_"+os.getenv("CATVERSION"))
mergetmpwork = MakeDir(timestamp_dir+"/job_output/")
local_sub_dir= MakeDir(timestamp_dir + "/job_output/"  + sample + '_' + new_channel + '_' + now())

##################################################################################################################
#### HARD CODE THE MAXIMUM number of subjobs
##################################################################################################################

ncore_def=number_of_cores
import platform

nj_def=1000    
debug_sktree = False

if number_of_cores > 0:
    print "Setting ncores to max if sktreemaker"
    if "SKTreeMaker" in cycle:
        number_of_cores=nj_def
    print "number_of_cores  = " + str(number_of_cores)
else:
    debug_sktree=True
    number_of_cores=1

##################################################################################################################            
##### FINISHED CONFIGURATION
##################################################################################################################
singlejob = number_of_cores==1            

if "SKTreeMaker" in cycle:
    if debug_sktree:
        singlejob=True
        running_batch=False
    else:
        singlejob=False
        running_batch=True

#### determine if input is data/mc
mc = len(sample)>1
if sample == "H_v2" or sample == "H_v3":
    mc= False

if mc:
    datatype="mc"

else:
    datatype="data"

if datatype == "mc":
    timeWait=10


##################################################################################################################
### Make a list of input samples: at the moment this is useless. Will add code to include * options in input
##################################################################################################################
list = []
import re
if ("*" in sample) and mc:
    print "ADD code"
else:
    list.append(sample)
#list has only size ==1 currently

##################################################################################################################
##### Specify if the job is running on SKTrees or CATNtuples
##################################################################################################################
original_sample = sample

if mc:
    sample = GetChannelName(useskinput, mc, useskim,sample, new_channel)
else:
    new_channel = GetChannelName(useskinput, mc, useskim,sample, new_channel)

            
##################################################################################################################
#Find the DS name (and lumi if MC) from txt/datasets.txt
##################################################################################################################

inDS = ""
inDS_pre = ""
filechannel=""

catversions = ["v8-0-8"]

sample_catversion = ""
output_catversion=os.getenv("CATVERSION")

#### Check latest tag/version for DS.
iversion=0
ktag=''

from Signal import IsSignal

datasetfile =  InputFileName(ktag,  IsSignal(sample))

while inDS == "":

    version="_CAT"
    sample_catversion = catversions[iversion]
    
    if catversion != "":
        sample_catversion = catversion
        output_catversion = catversion

    print "Using CAT " +sample_catversion + " ntuples"
    if mc:
        filename = os.getenv("LQANALYZER_RUN_PATH") + '/txt/'+datasetfile +sample_catversion +  '.txt'

    else:
        filename = os.getenv("LQANALYZER_RUN_PATH") + '/txt/datasets_snu_CAT'+ktag+'_data_'  +sample_catversion +'.txt'

             

    print "Using " + filename    
    if not mc:
        print "Running on data "
        print new_channel + " " + sample
        if not (os.path.exists(filename)):
            iversion = iversion +1
            continue
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    if new_channel ==entries[0] and sample == entries[1]:
                        inDS = entries[2]
                if len(entries)==2:
                    if "kisti_cat" == entries[0] and isKisti:
                        inDS_pre= entries[1]
                    if "tamsa_cat" == entries[0] and not isKisti:
                        inDS_pre= entries[1]


        sample = "period"+sample
        eff_lumi=1.
        tar_lumi=1.
        filechannel = new_channel+"_"
    else:
        print "Running on MC"
        if not (os.path.exists(filename)):
            iversion = iversion +1
            continue
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==6:
                    if sample == entries[0]:
                        eff_lumi = entries[4]
                        inDS = entries[5]

                if len(entries)==2:
                    if "kisti_cat" == entries[0] and isKisti:
                        inDS_pre= entries[1]
                    if "tamsa_cat" == entries[0] and not isKisti:
                        inDS_pre= entries[1]

    iversion = iversion +1                
    if inDS == "":
        if catversion != "":
            print "Input dataset is not available in specifies catversion: Exiting"
            sys.exit()
        print "LQAnalyzer :: WARNING :: Sample is not available in " + filename + "."
        print "Will look in previous compatable version. Need input from user if this is ok or a mistake."
        update = raw_input("This is likely because you have not changed the name of the input file. Since CATVERSION v7-6-3 these were changed. Is using anolder version of catuples ok for what you are doing? If you wish to use an older sample type Y. If not change input. run 'sktree -l' for options" )
        if not  update == "Y":
            sys.exit()
        if iversion == len(catversions):
            print "LQAnalyzer :: ERROR :: Input dataset is not available: Exiting"
            sys.exit()


#### inDS is path of input dataset  (inDS_pre is prefix for each machine)
inDS = inDS_pre +  inDS
InputDir = inDS    

#### listOfFile is list of inpit files
listOfFile = os.listdir(inDS)
InputDirList =[]

for entry in listOfFile:
    if ".root" in entry:
        InputDirList.append(inDS)
        break
    InputDirList.append(inDS+"/"+entry)


##################################################################################################################
#for x in InputDirList:
 #   print "Input directory= " + x    ## now have defined what dur contains input files

##################################################################################################################                    


############################################################
############################################################
###### RUN JOB
############################################################
############################################################

listx=0
for x in InputDirList:
    if listx==0:
        os.system("ls " + x + "/*.root > " + local_sub_dir + "/inputlist.txt")
        listx=listx+1
    else:
        os.system("ls " + x + "/*.root >> " + local_sub_dir + "/inputlist.txt")

 
fr = open(local_sub_dir + '/inputlist.txt', 'r')
fr_update = open(local_sub_dir + '/inputlist_updated.txt', 'w')


### Update list for kisti so batch can read file path
### inputlist_updated.txt now has updated paths
for line in fr:    
    if isKisti:
        newline = line.replace("/xrootd_user/"+str(os.getenv("USER"))+"/xrootd","root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/"+str(os.getenv("USER")))
        fr_update.write(newline)
    else:
        fr_update.write(line)
fr.close()
fr_update.close()




############################################################
## Get number of files in Input directory
############################################################
isfile = os.path.isfile
join = os.path.join
number_of_files = 0
for x in InputDirList:    
    number_of_files = number_of_files+ sum(1 for item in os.listdir(x) if isfile(join(x, item)))


### Print number of files 
print "number_of_files = " + str(number_of_files)


if number_of_files == 1 and not setnumber_of_cores:
    singlejob=False
    running_batch=True
if number_of_files == 1 and submit_allfiles:
    singlejob=False
    running_batch=True



if DEBUG == "True":
    print "Job has " + str(number_of_files) + " files to process:"


cluster = False


if not "SKTreeMaker" in cycle: 
    if ncore_def == 1:
        number_of_cores = 1
############################################################
### Correct user if ncores is > nfiles
############################################################
if number_of_cores > number_of_files:
    number_of_cores = number_of_files
print "Splitting job into " + str(number_of_cores) + " subjobs"



############################################################
### set number of files per job
############################################################
nfilesperjobs= 0
for i in range(1,number_of_files):
    if not i%number_of_cores:
        nfilesperjobs+=1

if number_of_cores == 1:
    nfilesperjobs = number_of_files

if nfilesperjobs == 0:
    nfilesperjobs=1
    
files_torun = (nfilesperjobs*number_of_cores)
remainder = number_of_files - (nfilesperjobs*number_of_cores)

if DEBUG == "True":
    print "Each job will process  " + str(nfilesperjobs) + "/" + str(nfilesperjobs+1) + " files"


###################################################
## counters
###################################################
nfiles=0
count=0
total_nsamples=0
filesprocessed=0
nfiles_file=0
n_remainder_files=-1
check_array = []

###################################################
# Setup work area on var tmp
###################################################

    
workspace = MakeDir(workoutput_mounted+"/CAT_SKTreeOutput/"+ getpass.getuser() +"/")
out_end=sample


output=workspace + sample + "_" + now() + "_" + os.getenv("HOSTNAME")  + "/"
output_tag=2
while os.path.exists(output):
    output=workspace + sample + "_" + now() + "_" + os.getenv("HOSTNAME")  + "v" +str(output_tag) +"/"
    output_tag=output_tag+1

mergeoutputdir = mergetmpwork + sample + "_" + now() + "_" + os.getenv("HOSTNAME")  + "/"
merge_tags=2
while os.path.exists(mergeoutputdir):
    mergeoutputdir=mergetmpwork + sample + "_" + now() + "_" + os.getenv("HOSTNAME")  +"v" +str(merge_tags)+"/"
    merge_tags=merge_tags+1


if not mc:
    output=workspace + new_channel+ "_"+ sample + "_" + now() + "_" + os.getenv("HOSTNAME") + "/" 
    mergeoutputdir = mergetmpwork + new_channel+ "_"+ sample + "_" + now() + "_" + os.getenv("HOSTNAME") + "/"
    merge_tags=2
    while os.path.exists(mergeoutputdir):
        mergeoutputdir = mergetmpwork + new_channel+ "_"+ sample + "_" + now() + "_" + os.getenv("HOSTNAME") + "v" +str(merge_tags)+"/"


outputdir    = MakeDir(output)
outputdir    = MakeDir(output+ "output/")
outputdir_tmp= MakeDir(output+ "output_tmp/")
mergeoutputdir = MakeDir(mergeoutputdir)


###################################################
## Make subjob directories
###################################################
printedworkdir =  output + "Job_[" + str(1) + "-" + str(number_of_cores) + "]/"

number_of_batch_jobs= number_of_cores 
if  isKisti:
    number_of_batch_jobs = 1

for i in range(0,number_of_batch_jobs):
    workdir =  output + "Job_" + str(i) + "/"    
    if  isKisti:
        workdir =  output + "Job_000/"
        
    if not (os.path.exists(workdir)):
            os.system("mkdir " + workdir)
            if i==1:
                if DEBUG == "True":
                    print "making sub work directories " + printedworkdir


####################################################
## Creat separate input lists/macros for each subjob
####################################################

### read inputlist.txt which contains all input files
fr = open(local_sub_dir + '/inputlist_updated.txt', 'r')

outsamplename = sample
if runnp == "True":
    outsamplename = "nonprompt_" + outsamplename
    print "sample --> " + outsamplename
if runcf == "True":
    outsamplename = "chargeflip_" + outsamplename
    print "sample --> " + outsamplename
if not mc:
    outsamplename = outsamplename +  "_" + new_channel

    
##### add catversion to output name
outsamplename = outsamplename + "_cat_" + output_catversion


if  "SKTreeMaker" in cycle:            
    outsamplename = outsamplename +  os.getenv("CATTAG")

if tmp_filename != "":
    outsamplename = outsamplename +"_"+tmp_filename

### specify the location of the macro for the subjob     
printedrunscript = output+ "Job_[1-" + str(number_of_cores)  + "]/runJob_[1-" + str(number_of_cores)  + "].C"

for line in fr:
    if nfiles < files_torun:
        if nfiles == 0 :

            countstr=''
            if count < 10:
                countstr = '00'+str(count)
            elif count < 100:
                countstr = '0'+str(count)
            else:
                countstr = str(count)

            runscript = output+ "Job_" + str(count) + "/runJob_" + countstr + ".C"
            filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
            
            if  isKisti:
                runscript = output+ "Job_000/runJob_" + countstr + ".C"
                filelist = output+ "Job_000/" + sample + "_%s" % (count) + ".txt"

            fwrite = open(filelist, 'w')
            configfile=open(runscript,'w')
            configfile.write(makeConfigFile(loglevel, outsamplename, filelist, tree, cycle, count, outputdir_tmp, outputdir, number_of_events_per_job, logstep, skipev, datatype, original_channel, data_lumi, totalev, xsec, tar_lumi, eff_lumi, useskinput, runevent, list_of_extra_lib, runnp,runcf,runtau, skflag,tagger,useskim, countstr)) #job, input, sample, ver, output
            configfile.close()
            if DEBUG == "True":
                print "Making file : " + printedrunscript
            fwrite.write(line)
            filesprocessed+=1
            nfiles_file+=1            
            nfiles+=1
            if files_torun == 1:
                fwrite.close()
            continue

        #End of file
        if not nfiles % nfilesperjobs:
            if not nfiles == number_of_files :
                # set counters
                nfiles_file=0
                count+=1        
                # close files
                fwrite.close()
                ### Make next set of scripts
                countstr=''
                if count < 10:
                    countstr = '00'+str(count)
                elif count < 100:
                    countstr = '0'+str(count)
                else:
                    countstr = str(count)
           
                if  isKisti:
                    runscript = output+ "Job_000/runJob_" + countstr + ".C"
                    filelist = output+ "Job_000/" + sample + "_%s" % (count) + ".txt"
                else:
                    runscript = output+ "Job_" + str(count) + "/runJob_" + countstr + ".C"
                    filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"

                fwrite = open(filelist, 'w')
                configfile=open(runscript,'w')
                configfile.write(makeConfigFile(loglevel,outsamplename, filelist, tree, cycle, count, outputdir_tmp,outputdir, number_of_events_per_job, logstep, skipev, datatype , original_channel, data_lumi, totalev, xsec, tar_lumi, eff_lumi, useskinput, runevent,list_of_extra_lib, runnp, runcf,runtau, skflag,tagger,useskim,countstr))
                configfile.close()
                fwrite.write(line)
                filesprocessed+=1
                nfiles_file+=1
                
            else:
                ### this means number of files is multiplr of njobs, but its not the last file in list
                fwrite.write(line)
                filesprocessed+=1
                nfiles_file+=1
                if DEBUG == "True":
                    print "File " + filelist + " contains " + str(nfiles_file) + " files"            
                
        else:
            fwrite.write(line)
            filesprocessed+=1
            nfiles_file+=1

        if nfiles == number_of_files-1 :
            fwrite.close()

    else:
        n_remainder_files+=1

        if count < 10:
            countstr = '00'+str(count)
        elif count < 100:
            countstr = '0'+str(count)
        else:
            countstr = str(count)
        if  isKisti:
            filelist = output+ "Job_000/" + sample + "_%s" % (n_remainder_files) + ".txt"
        else:
            filelist = output+ "Job_" + str(n_remainder_files) + "/" + sample + "_%s" % (n_remainder_files) + ".txt"

        fwrite = open(filelist, 'a')
        fwrite.write(line)
        filesprocessed+=1
        fwrite.close()        
    nfiles+=1        
fr.close()

#### make .C tar file:
if  isKisti:
    cwd = os.getcwd()
    os.chdir(workdir)
    os.system('tar -czf runFile.tar.gz run*.C')
    os.chdir(cwd)



#################################################################### 
### Check Final input files have no duplicates
#################################################################### 
no_duplicate=False
for check in range(0,number_of_batch_jobs):
    
    if  isKisti:
        filelist = output+ "Job_000/" + sample + "_%s" % (check) + ".txt"
    else:
        filelist = output+ "Job_" + str(check) + "/" + sample + "_%s" % (check) + ".txt"

    fcheck = open(filelist, 'r')
    nsamples=0
    for line in fcheck:
        nsamples+=1
        total_nsamples+=1
        no_duplicate= True
        for s in check_array:
            if s == line :
                print "DUPLICATE file : " + s
                no_duplicate=False
                sys.exit()
        check_array.append(line)
    if DEBUG == "True":
        print  "File " + filelist + " contains " + str(nsamples) + " files"
    fcheck.close()
if DEBUG == "True":
    print "Total Number of input files = " + str(total_nsamples)     

if no_duplicate:
    #print "Checking for duplicates: "
    #print "Checking for duplicates:...... "
    if DEBUG == "True":
        print "Checking for duplicates: NONE found"
else:
     #print "Checking for duplicates: "
     #print "Checking for duplicates:...... "
     print "Checking for duplicates: Duplicate files found. Check script "
            
if DEBUG == "True":
    print "Total number of files processed = " + str(filesprocessed)

###################################################
### Run each .C file in background
###################################################
import thread,time
start_time = time.time()
start_running_time=0.
job_time=0
last_job_time=0
wait_sub = 1
if number_of_cores < 10:
    wait_sub = 5


if DEBUG == "True":
    print "Running CATAnalyzer jobs for: " + getpass.getuser()

array_batchjobs = []

for i in range(0,number_of_batch_jobs):

    if  isKisti:
        batchscript =  output+ "Job_000/runJob"+str(tagger)+".sh"
        make_kistibatch_script(batchscript)

    else:
        batchscript =  output+ "Job_" + str(i) + "/runJob_" + str(i) + ".sh"
        batchfile=open(batchscript,'w')
        batchfile.write(make_batch_script(output+ "Job_" + str(i) , outsamplename+ "_Job_" + str(i),str(os.getenv("LQANALYZER_DIR")),"runJob_" + str(i) + ".C",cluster))
        batchfile.close()


    kisti_batchscript =  output+ "Job_000/submit.jds"
    if  isKisti:
        kisti_batchfile = open(kisti_batchscript,'w')
        kisti_batchfile.write('executable = runJob'+str(tagger)+'.sh\n')
        kisti_batchfile.write('universe   = vanilla\n')
        kisti_batchfile.write('arguments  = $(Process)\n')
        kisti_batchfile.write('requirements = OpSysMajorVer == 6\n')
        kisti_batchfile.write('log = condor.log\n')
        kisti_batchfile.write('getenv     = True\n')
        kisti_batchfile.write('should_transfer_files = YES\n')
        kisti_batchfile.write('when_to_transfer_output = ON_EXIT\n')
        kisti_batchfile.write('output = job_$(Process).log\n')
        kisti_batchfile.write('error = job_$(Process).err\n')
        kisti_batchfile.write('transfer_input_files = '+output+'Job_000/runFile.tar.gz\n')
        kisti_batchfile.write('use_x509userproxy = true\n')
        kisti_batchfile.write('transfer_output_remaps = "hists.root = output/hists_$(Process).root"\n')
        kisti_batchfile.write('queue '+str(number_of_cores)+' \n')
        kisti_batchfile.close()

    
    #### script is for single job use only
    script = output+ "Job_" + str(i) + "/runJob_" + str(i) + ".C"
    log = output+ "Job_" + str(i) + "/runJob_" + str(i) +".log"
    if  isKisti:
        script = output+ "Job_000/runJob_000.C"
        log = output+ "Job_000/runJob_" + str(i) +".log"

    logbatch="Job_" + str(i) + "/"+outsamplename+ "_Job_" + str(i)+".o[batchID]"  

    runcommand = "nohup root.exe -l -q -b " +  script + "&>" + log + "&"
    if running_batch:
        if queue == "":
            if  isKisti:
                runcommand = "condor_submit " + kisti_batchscript + "&>" + log   
            else:
                runcommand = "qsub -V " + queue_command +" "+ batchscript   + "&>" + log 
        else:
            if  isKisti:
                runcommand = "condor_submit " + kisti_batchscript + "&>" + log

    jobID=0
    first_jobid=0


    if singlejob:
        print "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
        print "Running single job " + script 
        runcommand = "root.exe -l -q -b " +  script 
        os.system(runcommand)
    else:
        if i== number_of_cores:
            if running_batch:
                print "Running " + script + " . Log file --->  " + logbatch
            else:
                print "Running " + script + " . Log file --->  " + log

        elif i==1:
            if running_batch:
                print "Running " + script + " . Log file --->  " + logbatch
            else:
                print "Running " + script + " . Log file --->  " + log

        elif i==2:
            print "......"
        if isKisti:
            cwd = os.getcwd()
            os.chdir(workdir)
            os.system(runcommand)
        else:
            os.system(runcommand)
        if running_batch and (not isKisti):
            for line in open(log, 'r'):
                entries = line.split()
                if len(entries) > 0:
                    if jobID ==0:
                        first_jobid= entries[2]
                    jobID=entries[2]
                    array_batchjobs.append(jobID)
                    k_batchscript =  output+ "JobKill.sh"
                    if i==1:
                        k_batchfile=open(k_batchscript,'w')
                        k_batchfile.write("qdel  " +str(jobID) +';')
                    else:
                        k_batchfile=open(k_batchscript,'a')
                        k_batchfile.write("qdel  " +str(jobID)+';')
                    k_batchfile.close()

        if running_batch and isKisti:
            for line in open(log, 'r'):
                if "submitted to cluster" in line:
                    entries = line.split()
                    if len(entries) > 0:
                        jobID= entries[5]
                        for xi in range(0, number_of_cores):
                            array_batchjobs.append(entries[5]+str(xi))
                        k_batchscript =  output+ "JobKill.sh"
                        k_batchfile=open(k_batchscript,'w')
                        k_batchfile.write("condor_rm  " +str(entries[5]).replace(".",""))
                        k_batchfile.close()

if running_batch: 
    
    if not os.path.exists(workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/"):
        os.system("mkdir " + workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/")
    

    print "@@@@@@@@@@@@@@@@@@@@@@@@@"
    path_jobids = workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + original_sample + "jobid.txt"

    file_jobids = open(path_jobids,"w")
    for ijob in array_batchjobs:
        file_jobids.write(ijob + "\n")
        print "Job ["+str(ijob)+"] added to list......."
    file_jobids.close()    
    print "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
    print "In case user wants to kill job do : source " + output+ "JobKill.sh"
    print "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"




##########################################################
## wait and do merging (also remove old log file/rootfiles
##########################################################
check_log= os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename + "/"
if number_of_cores > 1:
    if (os.path.exists(check_log)):
        if sum(1 for item in os.listdir(check_log) if isfile(join(check_log, item))) > 0:
            os.system("rm " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename + "/*.o*")

if DEBUG == "True":
    print "Waiting for all jobs to finish before Merging."

ncomplete_files=0
JobSuccess=False
JobOutput=True
CompletedJobs=[]
doMerge=False

print "Checking Job status:"

if singlejob:    
    check_outfile = outputdir + outsamplename +  "_1.root"
    if (os.path.exists(check_outfile)):
        JobSuccess=True;
else:        
    sys.stdout.write('\r'+ '0% of events processed...' )
    sys.stdout.flush()

low_cpu=0
ncycle=0
file_iterator=0
files_done= []
clear_line='                                                                          '
failed_macro=""
failed_log=""

JobCrash=False
checkJob=True
n_cms1_6=""

if DEBUGMODE:
    sys.stdout.write('\r TEST: submit_terminal checking job success... \n')

from submit_terminal import *

while not JobSuccess:
    if DEBUGMODE:
        sys.stdout.write('\r TEST: checking job success... \n')

    filename = local_sub_dir +'/log'
    running = False

    if running_batch == False:
        running = CheckRunningNonBatch(filename, low_cpu )

    elif isKisti:

        ### check in batch_function CheckRunningKistiBatch, checks if jobs are running on batch and if HELD deletes all jobs
        running =CheckRunningKistiBatch(filename,  array_batchjobs[0],output, -100, "initial")
        sys.stdout.write('\r running = ' + str(running) + '\n')

    else:

        ### check in batch_function CheckRunningSNUBatch, checks if jobs are running on batch and if HELD deletes all jobs                                                                                                                                                    
        running    = CheckRunningSNUBatch(filename,  array_batchjobs,output)
        n_cms1_6   = CheckMachinesSNUBatch(filename,  array_batchjobs,output )
        

    if not running == 1:

        ###  if running = False, then jobs should be finished and output files should exist
        check_outfile = outputdir + outsamplename +  "_1.root"
        sys.stdout.write('\r check_outfile = ' + check_outfile + '\n')


        if not (os.path.exists(check_outfile)):
            ###  if running = False and output files does not exist then jobs crashed or some other issue occurred, 
            ### in this case, JobSuccess is set True but the output is set false
            JobSuccess=True
            JobOutput=False
            if DEBUGMODE:
                sys.stdout.write('\r TEST: JobSuccess = True, JobOutput=False \n')
        else: 
            if DEBUGMODE:
                sys.stdout.write('\r TEST: output file found: file ' + check_outfile + '\n')
                

    #### this loop loops over all subjobs, and checks each output file is present in outputdir, IF it is not already in CompletedJobs array
    #### CompletedJobs array is filled after each output file is present, so
    ###  job_time is set to the time that the last job is completed 
    ### ncomplete_files is increased by one for each output file 
    for i in range(1,number_of_cores+1):
        skipcheck=False
        for check in CompletedJobs:
            if i== check: skipcheck=True
        if not skipcheck:
            if checkJob:
                if sum(1 for item in os.listdir(outputdir) if isfile(join(outputdir, item))) > 0:
                    if not start_running_time == 0.:
                        job_time = time.time()
                        checkJob=False
            check_outfile = outputdir + outsamplename +  "_" +  str(i) + ".root"   
            if isKisti:
                check_outfile = outputdir + outsamplename +  "_" + str(i-1)+".root"

            
            if (os.path.exists(check_outfile)):
                CompletedJobs.append(i)
                ncomplete_files+=1
                files_done.append("Job [" + str(i) + "] completed. Output ="  + check_outfile)
                sys.stdout.write('\r Job [' + str(i) + '] completed. Output ='  + check_outfile + '\n')


    if DEBUGMODE:
        sys.stdout.write('\r ncomplete_files = ' + str(ncomplete_files) + ' number_of_cores = ' + str(number_of_cores) + '\n')


    ### check that the number of output files (ncomplete_files) is equal to the number of subjobs (number_of_cores)
    if ncomplete_files== number_of_cores :
        last_job_time = time.time()
        ### last_job_time is set as the time the job is considered finished.
        sys.stdout.write('\r' + clear_line)
        sys.stdout.flush()
        sys.stdout.write('\r'+ '100% of events processed. \n' )
        sys.stdout.flush()
        print "Job finished"

        ### set doMerge, so the script knows that the job successfully ran and the output files are ok to merge
        doMerge=True


        ###   catch rare case of bug that runs jobs but produces exmpty output
        if ncycle == 0:
            print "Job ran in less than 10 seconds. Assumed bug:"
            if number_of_cores == 1:
                JobOutput=True
            else:
                JobOutput=False

        #### set JobSuccess as True, since all conditions were met
        JobSuccess=True
                                    
    else:

        ##### THIS IS ENTERED IF THE JOB IS STILL RUNNING, AND SOME OR ALL SUBJOBS ARE STILL RUNNING
        ##### IN THIS CASE THE JOBS ARE MONITORED AND THE TERMINAL SCREEN INFORMATION IS UPDATED

        #### These doubles are used to estimate how much of the job is left to process
        nevents_total=0.
        nevent_processed=0.


        if running_batch:

            ### print jobs running/in queue .... once all running print % completeion
            for i in range(1,number_of_cores+1):
                check_outfile = CHECK_OUTLOGFILE(isKisti,output, i, outsamplename, array_batchjobs)
                
                ### if first sub job set the start time
                start_running_time = SetStartTime(start_running_time, i)

                while not os.path.exists(check_outfile):
                    #### This while loop holds up the script until log file exists and job is running, at this stage the start_running_time is set
                    if i == 1:
                        start_running_time = time.time()

                    #### update output using submit_terminal.py function
                    UpdateJobsRunning(clear_line, i, number_of_cores)

                    if checkJob:
                        ### Check if job is running successfuly by looking if output dir has files in
                        if sum(1 for item in os.listdir(outputdir) if isfile(join(outputdir, item))) > 0:
                            job_time = time.time()
                            checkJob=False
                    time.sleep(1.)
            if ncycle == 0:
                UpdateJobsRunnigFirstRun(clear_line, number_of_cores)


            #### check job is running. Halted or suspended and if not running is output file missing?

            filename = local_sub_dir +'/log'
            #CheckBatch(isKisti, filename)
            
            for i in range(1,number_of_cores+1):
                if not JobOutput:
                    break
                job_finished=True
                running_status = CheckRunningBatch(isKisti, filename, array_batchjobs, i, output) 
                job_id_c=array_batchjobs[i-1]

                sys.stdout.write('\r running = ' + str(running_status) + '\n')

                if running_status == 2:
                    number_of_cores=0
                    JobSuccess=True
                    JobOutput=False
                if running_status == 1:
                    job_finished = False
                    
                if job_finished:
                    ### job id not in batch output. Check if rootfile is missing. If so kill job
                    
                    sys.stdout.write('\r  job id not in batch output. Check if rootfile is missing. If so kill job\n')
                    sys.stdout.flush()
                    print "job id not in batch output. Check if rootfile is missing. If so kill job"
                
                    check_outfile = outputdir + outsamplename +  "_" + str(i)+".root"
                    if isKisti:
                        check_outfile = outputdir + outsamplename +  "_" + str(i-1)+".root"
                        sys.stdout.write('\r check_outfile = ' + check_outfile + ' i = ' + str(i-1) + ' str(job_id_c) = ' + str(job_id_c) + '\n')


                    it_file_check=0
                    while not (os.path.exists(check_outfile)):
                        it_file_check=it_file_check+1
                        if it_file_check == 3:
                            break
                        out_check= outputdir + outsamplename
                        tmpout_check= out_check.replace("output/","output_tmp/")
                        os.system("ls "+ tmpout_check + "*")
                        os.system("ls "+ out_check + "*")
                        if  (os.path.exists(check_outfile)):
                            sys.stdout.write('\r ' + check_outfile + ' exists \n')
                        else:
                            sys.stdout.write('\r ' + check_outfile + ' does not exist \n')
                            time.sleep(10)
                            


                    if not (os.path.exists(check_outfile)):
                        if  (os.path.exists(check_outfile)):
                            sys.stdout.write('\r ' + check_outfile + ' fail:exists \n')
                        else:
                            sys.stdout.write('\r ' + check_outfile + ' fail:does not exist \n')
                            

                        failed_macro = GetFailedMacroName(isKisti, output, i)
                        failed_log = GetFailedLogName(isKisti, output, i, array_batchjobs)
                        
                        JobSuccess=True
                        JobOutput=False
                        print "Job " + str(job_id_c) + " is not running or in queue. Output " + str(check_outfile)+ " is missing."
                        print "Most likely a crash occurred.  So killing all jobs." 
                        sys.stdout.write('\r check_outfile = ' + check_outfile + ' i = ' + str(i-1) + ' str(job_id_c) = ' + str(job_id_c) + '\n')
                        
                        os.system("source " + output+ "JobKill.sh")

                        check_error_outfile = output + "/Job_000/job_0.err"
                        print "Error file for job ["+str(job_id_c)+"] shows:"
                        for line in open(check_error_outfile, 'r'):
                            print line
                        print "Run in non-batch mode by setting njobs = 1 in submit.sh file and retry" 
                        JobCrash=True
                        
            os.system("rm  " + local_sub_dir + "/log")
            
        ##### Run over log to get % completion                    

        processed_numbers = CheckPercentComplete(isKisti,number_of_cores,output,outsamplename, array_batchjobs, local_sub_dir,running_batch)
        nevent_processed = processed_numbers[0]
        nevents_total = processed_numbers[1]


        ## calculate time left to run jobs    
        end_time = time.time()
        remaining = (end_time - start_time)
        if nevent_processed !=0:
            remaining*= (1./nevent_processed)
            remaining*= ( nevents_total  - nevent_processed)
            b = str(round(float(100.*nevent_processed/nevents_total), 2)) + "% of events processed. Estimated cpu time remaining =  " + str(round(remaining,2)) + "[s]" 
            sys.stdout.write('\r' + clear_line)
            sys.stdout.flush()
            sys.stdout.write('\r'+b)            
            sys.stdout.flush()
        else:
            mess="Job Initialising 0% of events processed."
            if JobOutput:
                sys.stdout.write('\r' + clear_line)
                sys.stdout.flush()
                sys.stdout.write('\r'+mess)
                sys.stdout.flush()
                time.sleep(1.)
        if ncomplete_files > file_iterator:
            file_iterator=ncomplete_files
        time.sleep(1.)
        ncycle+=1

if not JobOutput:

    if not running_batch:
        failed_macro = GetFailedMacroName(isKisti, output, 0)
        failed_log   = GetFailedLogName(isKisti, outsamplename, 1, array_batchjob)
        
   
    print ""
    print "Job Failed...."
    if not os.path.exists(os.getenv("LQANALYZER_LOG_PATH")):
        os.system("mkdir " + os.getenv("LQANALYZER_LOG_PATH"))
    if not os.path.exists(os.getenv("LQANALYZER_LOG_PATH")+ "/" + outsamplename):
        os.system("mkdir " + os.getenv("LQANALYZER_LOG_PATH")+ "/" + outsamplename)
        
    if not number_of_cores == 1:
        os.system("mv "+ output + "/*/*.o* " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename)    
        os.system("mv "+ output + "/*/*.e* " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename)    
    print "###########################################################################################################"
    print "Check crash by running root -q -b " + failed_macro 
    print "after typing: export cat_version=$CATVERSION"
    print 'export CATAnalyzerPeriod="B"'
    print "Logfile of failed job is can be found at " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename   + failed_log 
    print "###########################################################################################################"
    JobCrash=True
    
else:

    for line in files_done:
        if DEBUG == "True":
            print line

        
    
    if "SKTreeMaker" in cycle:
        from sktree_submitfunction import *
        Finaloutputdir = SetupSKTree(isKisti,sktreeoutput, workoutput_mounted, sample_catversion, mc,original_channel, cycle)
        doMerge=False
                
        if not os.path.exists(Finaloutputdir):
            os.system("mkdir " + Finaloutputdir)


    outfile = cycle + "_" + filechannel + outsamplename + ".root"

    if doMerge:
        print "doing merge:"
        if not mc:
            outfile = cycle + "_" + outsamplename + ".root"
        if os.path.exists(Finaloutputdir + outfile):
            os.system("rm  "  +  Finaloutputdir   + outfile)
        os.system("mv " +outputdir + "*.root" + " " + mergeoutputdir)

        os.system("hadd " + mergeoutputdir +  outfile  + " "+ mergeoutputdir + "*.root")
        
        if mc:
            hist_pre =  "/data2/CAT_SKTreeOutput/"
            if isKisti:
                hist_pre ="/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/"
            if not os.path.exists( hist_pre+os.getenv("USER")+"/Histdir" + tagger ):
                os.system("mkdir " +  hist_pre+os.getenv("USER")+"/Histdir" + tagger)
            os.system("source "+os.getenv("LQANALYZER_DIR")+"/scripts/Counter.sh " + mergeoutputdir +  outfile + " > "+hist_pre+os.getenv("USER")+"/Histdir" + tagger + "/"+original_sample+"Hist.txt"   )
            os.system("source "+os.getenv("LQANALYZER_DIR")+"/scripts/CutFlow.sh " + mergeoutputdir +  outfile + " > " + hist_pre+os.getenv("USER")+"/Histdir" + tagger + "/"+original_sample+"CutFlow.txt"   )  


        os.system("mv " + mergeoutputdir +  outfile + " "  + Finaloutputdir)

        os.system("ls -lh " + Finaloutputdir +  outfile + " > " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/filesize_" + original_sample+ tagger +".txt")
        f = ROOT.TFile(Finaloutputdir +  outfile)
        t = f.Get("CycleInfo/CycleVirtualMemoryUsage")
        t2 = f.Get("CycleInfo/CyclePhysicalMemoryUsage")
        memoryusage_v=(t.GetBinContent(8)/ number_of_cores)
        memoryusage_p=(t2.GetBinContent(8)/ number_of_cores)
        f.Close()
        print "Merged output :" + Finaloutputdir + outfile

    else:

        print "not doing merge"
        
        if not mc:
            outfile = cycle + "_" + outsamplename + ".root"
        if number_of_cores == 1 and setnumber_of_cores:
            if not isKisti:
                os.system("mv " + outputdir + outsamplename + "_1.root " + Finaloutputdir + outfile )
            else:
                os.system("mv " + outputdir + outsamplename + "_0.root " + Finaloutputdir + outfile )
            os.system("ls -lh " + Finaloutputdir +   outfile + " > " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/filesize" + tagger+".txt")
            f = ROOT.TFile(Finaloutputdir +  outfile)
            t = f.Get("CycleInfo/CycleVirtualMemoryUsage")
            t2 = f.Get("CycleInfo/CyclePhysicalMemoryUsage")
            memoryusage_v=(t.GetBinContent(8)/ number_of_cores)
            memoryusage_p=(t2.GetBinContent(8)/ number_of_cores)
            f.Close()
            
        else:
            os.system("rm " + Finaloutputdir + "/*.root")
            os.system("mv " + outputdir + "*.root " + Finaloutputdir )
            os.system("chmod -R 777 " + Finaloutputdir )
            os.system("ls -lh " + Finaloutputdir +  outsamplename + "_1.root > " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/filesize_" + original_sample+ tagger+".txt")
            f = ROOT.TFile(Finaloutputdir +  outsamplename + "_1.root")
            t = f.Get("CycleInfo/CycleVirtualMemoryUsage")
            t2 = f.Get("CycleInfo/CyclePhysicalMemoryUsage")
            memoryusage_v=(t.GetBinContent(8)/ number_of_cores)
            memoryusage_p=(t2.GetBinContent(8)/ number_of_cores)
            f.Close()

        if DEBUG == "True":
            print "Non merged output :" +Finaloutputdir
    
    if remove_workspace == "True":
        if not os.path.exists(os.getenv("LQANALYZER_LOG_PATH")):
            os.system("mkdir " + os.getenv("LQANALYZER_LOG_PATH"))
            
        if not os.path.exists(os.getenv("LQANALYZER_LOG_PATH")+ "/" + outsamplename):
            os.system("mkdir " + os.getenv("LQANALYZER_LOG_PATH")+ "/" + outsamplename)
        
        if not number_of_cores == 1:    
            os.system("mv "+ output + "/*/*.o* " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename)
        os.system("rm -r " + output)
        os.system("rm -r " + local_sub_dir)
        os.system("rm -r " + timestamp_dir)
        print "Log files are sent to  --> "  + os.getenv("LQANALYZER_LOG_PATH")+ "/" + outsamplename
        if doMerge:
            print "All sampless finished: OutFile:"  + cycle + "_" + filechannel + outsamplename + ".root -->" + Finaloutputdir
        else:
            if number_of_cores == 1:
                print "All sampless finished: OutFiles "+ outsamplename + "_1.root -->" + Finaloutputdir + outfile
            else:
                print "All sampless finished: OutFiles "+ outsamplename + "*.root -->" + Finaloutputdir
            
    else:
        print "TMP directory " + output + "is not removed. "
        os.system("rm -r " + local_sub_dir)
        
if os.path.exists(local_sub_dir):
    os.system("rm -r " + local_sub_dir)
    os.system("rm -r " + timestamp_dir)
end_time = time.time()
total_time=end_time- start_time
print "Using " + str(number_of_cores) + " cores: Job time = " + str(total_time) +  " s"
print ""

if True:
    statfile=path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/" + str(tagger) + "/statlog_"+ original_sample + tagger +".txt"
    statfile_time=path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/" + str(tagger) + "/statlog_timetmp_"+original_sample+tagger +".txt"
    statfile_time_complete=path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/" + str(tagger) + "/statlog_time_"+original_sample+tagger +".txt"
    
    if not os.path.exists(path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() ):
        os.system("mkdir " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser())
    if not os.path.exists(path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/" + str(tagger)):
        print "mkdir " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()+ "/" + str(tagger)
    os.system("mkdir " + path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()+ "/" + str(tagger))

    statwrite = open(statfile, 'r')
    statwrite_time = open(statfile_time, 'w')
    for line in statwrite:
        statwrite_time.write(line)
    statwrite.close()

    statwrite_time.write("time " + str(total_time) + " \n")
    statwrite_time.write("job_time  " + str(job_time-start_running_time)  + " \n")
    statwrite_time.write("last_job_time  " + str(last_job_time-start_running_time)  + " \n")
    print "time " + str(total_time)
    print "job_time  " + str(job_time)
    print "start_running_time " + str(start_running_time)
    print "last_job_time " + str(last_job_time)
    
    pathfilesize=path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/filesize_"+original_sample + tagger +".txt"

    if os.path.exists(pathfilesize):
        readfilesize = open(pathfilesize, "r")
        for line in readfilesize:
            splitline = line.split()
            if len(splitline) == 9:
                statwrite_time.write("outputfile_size " + str(splitline[4])  + " \n")
        readfilesize.close()
        os.system("rm " + pathfilesize)
    else:
        statwrite_time.write("outputfile_size 0.0 \n")

    statwrite_time.write("Njobs " +  str(number_of_cores) + " \n") 
    statwrite_time.write("NFiles " + str(number_of_files)  + " \n")
    
    statwrite_time.write("ClusterIDs " + n_cms1_6 + " \n")

    statwrite_time.write("memoryusage_v " + str(memoryusage_v/1000)  + "MB \n") 
    statwrite_time.write("memoryusage_p " + str(memoryusage_p/1000)  + "MB \n") 
    if JobCrash:
        statwrite_time.write("Success= False \n")
        if not os.path.exists(workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/"):
            os.system("mkdir " + workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/")
        os.system("mkdir " + workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + original_sample+"_crash")
        crash_log= workoutput_mounted+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + original_sample+"_crash/crashlog.txt"
        writecrashlog = open(crash_log,"w")
        writecrashlog.write("###########################################################################################################")
        writecrashlog.write("Check crash by running root -q -b " + failed_macro)
        writecrashlog.write("Logfile of failed job is can be found at " + os.getenv("LQANALYZER_LOG_PATH") + "/" + outsamplename   + failed_log)
        writecrashlog.write("###########################################################################################################")
        writecrashlog.close()
    else:
        statwrite_time.write("Success= True \n")
        
    statwrite_time.close()
    print "mv " + statfile_time + " " + statfile_time_complete
    
    os.system("mv " + statfile_time + " " + statfile_time_complete)

    GeneralStatFile = os.getenv("LQANALYZER_DIR")+ "/python/StatFile.py"

    number_of_jobs_for_statfile=number_of_cores

    if number_of_events_per_job > 0:
        number_of_jobs_for_statfile = 1
    if skipev > 0:
        number_of_jobs_for_statfile = 1
    if JobCrash:
        number_of_jobs_for_statfile = 1

        
    print "python " + GeneralStatFile + " -x " + tagger + " -s " + original_sample + " -n " + str(number_of_jobs_for_statfile)

    os.system("python " + GeneralStatFile + " -x " + tagger + " -s " + original_sample + " -n " + str(number_of_jobs_for_statfile))
