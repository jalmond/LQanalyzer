####################################################################
# Settings for User
####################################################################
InputDir="/data1/SNUData/Data/Electron/DoubleElectron/Nov13/periodA/"
sample="periodAelectron"
number_of_cores=1
number_of_events_per_job=200000
print "Splitting job into " + str(number_of_cores) + " subjobs"

### configure run
timeWait=20#

###################################################
### Make Input File
###################################################
from functions import *
import os,getpass
os.system("ls " + InputDir + "/*.root > inputlist.txt")
isfile = os.path.isfile
join = os.path.join

## Get numnber of files in Input directory
number_of_files = sum(1 for item in os.listdir(InputDir) if isfile(join(InputDir, item)))
print str(number_of_files) + " files to process"

#import numpy as np
nfilesperjobs=0
for i in range(0,number_of_files):
    if not i%number_of_cores:
        nfilesperjobs+=1



print "Each job will process at most " + str(nfilesperjobs) + " files"
###################################################
## counters
###################################################
nfiles=0
count=1

###################################################
# Setup work area
###################################################
workspace = "/var/tmp/"+ getpass.getuser() + "/"
if not (os.path.exists(workspace)):
        os.system("mkdir " + workspace)
output=workspace + sample + "_" + now() + "/"
outputdir= output+ "output/"
if not (os.path.exists(output)):
    os.system("mkdir " + output)
    print "Making tmp working directory to run Job  : " + output

if(os.path.exists(outputdir)):
    number_of_outputfiles = sum(1 for item in os.listdir(outputdir) if isfile(join(outputdir, item)))
    if  not number_of_outputfiles ==0:
       os.system("rm " + outputdir + "/*.root")
       print "Emptying output directory as this should be empty for new job"
              
if not (os.path.exists(outputdir)):
        os.system("mkdir " + outputdir)
        

for i in range(1,number_of_cores+1):
    workdir =  output + "Job_" + str(i) + "/"
    if not (os.path.exists(workdir)):
            os.system("mkdir " + workdir)
            if i==1:
                print "making sub work directory " + workdir
            elif i==number_of_cores:
                print "making sub work directory " + workdir
            elif i==2:
                print "......."

####################################################
## Creat separate input lists/macros for each subjob
####################################################
fr = open('inputlist.txt', 'r')

filesprocessed=0
nfiles_file=0
for line in fr:
    nfiles+=1        
    runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
    filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"

#    print "Input File[" + str(nfiles) + "] : " + line + " --> " + filelist 

    if nfiles == 1 :        
        runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
        filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
        fwrite = open(filelist, 'w')
        configfile=open(runscript,'w')
        configfile.write(makeConfigFile("ZTest", filelist, sample, count, outputdir, number_of_events_per_job)) #job, input, sample, ver, output
        print "Making file : " + runscript
    

    if not nfiles % nfilesperjobs:
        if not nfiles == number_of_files :
            print "File " + filelist + " contains " + str(nfiles_file) + " files"
            # set counters
            nfiles_file=0
            count+=1        
            # close files
            configfile.close()
            fwrite.close()
            ### Make next set of scripts
            runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
            filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
            fwrite = open(filelist, 'w')
            configfile=open(runscript,'w')
            configfile.write(makeConfigFile("ZTest", filelist, sample, count, outputdir, number_of_events_per_job))
            fwrite.write(line)
            filesprocessed+=1
            nfiles_file+=1
        else:
            fwrite.write(line)
            filesprocessed+=1
            nfiles_file+=1
            print "File " + filelist + " contains " + str(nfiles_file) + " files"            
            
    else:
        fwrite.write(line)
        filesprocessed+=1
        nfiles_file+=1

    if nfiles == number_of_files :
        print "File " + filelist + " contains " + str(nfiles_file) + " files"
        print "Completed " + str(nfiles) + "/" + str(number_of_files)        
        configfile.close()
        fwrite.close()
fr.close()

print "Total number of files processed = " + str(filesprocessed) + " check this is correct"

###################################################
### Run each .C file in background
###################################################
import thread,time
start_time = time.time()

print "Running LQAnalyzer jobs for: " + getpass.getuser()
for i in range(1,number_of_cores+1):
    script = output+ "Job_" + str(i) + "/runJob_" + str(i) + ".C"
    log = output+ "Job_" + str(i) + "/runJob_" + str(i) +".log"
    runcommand = "nohup root -q -b " +  script + "&> " +  log + "&"
    os.system(runcommand)   
    if i==1:
        print "Running " + script + " . Log file --->  " + log 
    elif i== number_of_cores:
        print "Running " + script + " . Log file --->  " + log
    elif i==2:
         print "......"
os.system('rm inputlist.txt')

###################################################
## wait and do merging
###################################################

print "Waiting for all jobs to finish before Merging"


ncomplete_files=0
JobSuccess=False
CompletedJobs=[]
print "Checking Job status:"
while not JobSuccess:
    for i in range(1,number_of_cores+1):
        skipcheck=False
        for check in CompletedJobs:
            if i== check: skipcheck=True
        while not skipcheck:
            skipcheck=True
#            print "Checking " + str(i)
            check_outfile = outputdir + sample +  "_" +  str(i) + ".root"   
            if (os.path.exists(check_outfile)):
                CompletedJobs.append(i)
                ncomplete_files+=1
                print "Job [" + str(i) + "] completed. Output ="  + check_outfile
        
    if ncomplete_files== number_of_cores :
        print "Job finished"
        JobSuccess=True
    else:
        print str(ncomplete_files) + "/" + str(number_of_cores) + " completed. Wait " + str(timeWait) + " second..."
        
        time.sleep(timeWait)
         
print "All sampless finished"        
end_time = time.time()
total_time=end_time- start_time
print "Using " + str(number_of_cores) + " cores: Job time = " + str(total_time) +  " s"
        
