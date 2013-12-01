#################################################################### 
### configure run
#################################################################### 
timeWait=60#

###################################################
### Make Input File
###################################################

import os, getpass, sys
from functions import *
from optparse import OptionParser

#Import parser to get options
parser = OptionParser()
parser.add_option("-p", "--period", dest="period", default="A",help="which data period")
parser.add_option("-s", "--stream", dest="stream", default="", help="Which data channel- ee,or mumu?")
parser.add_option("-j", "--jobs", dest="jobs", default="", help="Which data channel- ee,or mumu?")
parser.add_option("-c", "--cycle", dest="cycle", default="Analyzer", help="which cycle")
parser.add_option("-l", "--logstep", dest"logstep", default="10000", help="How many events betwene log messages")
parser.add_option("-d", "--data_lumi", dest="data_lumi", default="", help="How much data are you weighting?")


(options, args) = parser.parse_args()

number_of_cores = int(options.jobs)
sample = options.period
stream = options.stream
cycle = options.cycle
logstep = options.logstep

### THESE ARE OPTIONS THAT CAN BE INCLUDED
number_of_events_per_job=-1
skipev = -1
datatype = ""
totalev = -1
xsec = -1.
tar_lumi = -1.
eff_lumi = -1.
output_step=-1
totalmc = -1.

print "Splitting job into " + str(number_of_cores) + " subjobs"

mc = len(sample)>1
if mc:
    dataType="mc"
else:
    dataType="data"
    
if sample == "AtoD":
    dataType="data"
    

list = []
import re
if ("*" in sample) and mc:
    print "ADD code"
else:
    list.append(sample)
    period = sample
    
#Find theq DS name 
inDS = ""
mcLumi = 1.0

if not mc:
    filename = 'txt/datasets.txt'
    for line in open(filename, 'r'):
        if not line.startswith("#"):
            entries = line.split()
            if len(entries)==3:
                if stream ==entries[0] and sample == entries[1]:
                    inDS = entries[2]
    sample = "period"+sample                
else:
    filename = 'txt/datasets.txt'
    for line in open(filename, 'r'):
        if not line.startswith("#"):
            entries = line.split()
            if len(entries)==3:
                if sample == entries[0]:
                    eff_lumi = entries[1]
                    inDS = entries[2]
                    
InputDir = inDS    
print InputDir

    
os.system("ls " + InputDir + "/*.root > inputlist.txt")
isfile = os.path.isfile
join = os.path.join

## Get numnber of files in Input directory
number_of_files = sum(1 for item in os.listdir(InputDir) if isfile(join(InputDir, item)))
print str(number_of_files) + " files to process"

#import numpy as np
nfilesperjobs= 0
for i in range(1,number_of_files):
    if not i%number_of_cores:
        nfilesperjobs+=1
    if number_of_cores == 1:
        nfilesperjobs = number_of_files
files_torun = (nfilesperjobs*number_of_cores)
remainder = number_of_files - (nfilesperjobs*number_of_cores)

print "Each job will process at most " + str(nfilesperjobs+1) + " files"


###################################################
## counters
###################################################
nfiles=0
count=1
total_nsamples=0
filesprocessed=0
nfiles_file=0
n_remainder_files=0
check_array = []

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


printedworkdir =  output + "Job_[" + str(1) + "-" + str(number_of_cores) + "]/"
for i in range(1,number_of_cores+1):
    workdir =  output + "Job_" + str(i) + "/"

    if not (os.path.exists(workdir)):
            os.system("mkdir " + workdir)
            if i==1:
                print "making sub work directories " + printedworkdir

####################################################
## Creat separate input lists/macros for each subjob
####################################################
fr = open('inputlist.txt', 'r')

printedrunscript = output+ "Job_[1-" + str(number_of_cores)  + "]/runJob_[1-" + str(number_of_cores)  + "].C"
for line in fr:
    
    # Deal with remaining files
    if nfiles < files_torun :
        if nfiles == 0 :        
            runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
            filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
            fwrite = open(filelist, 'w')
            configfile=open(runscript,'w')
            configfile.write(makeConfigFile(sample, filelist, fullfilelist, cycle, count, outputdir, number_of_events_per_job, output_step, skipev, datatype, channel, period, totalmc, xsec, tar_lumi, eff_lumi)) #job, input, sample, ver, output
            configfile.close()
            print "Making file : " + printedrunscript
            fwrite.write(line)
            filesprocessed+=1
            nfiles_file+=1            
            nfiles+=1
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
                runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
                filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
                fwrite = open(filelist, 'w')
                configfile=open(runscript,'w')
                configfile.write(makeConfigFile(sample, filelist, fullfilelist, cycle, count, outputdir, number_of_events_per_job, output_step, skipev, datatype , channel, period, totalmc, xsec, tar_lumi, eff_lumi))
                configfile.close()
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
            print "Completed " + str(nfiles) + "/" + str(number_of_files)        
            fwrite.close()

    else:
        n_remainder_files+=1
        filelist = output+ "Job_" + str(n_remainder_files) + "/" + sample + "_%s" % (n_remainder_files) + ".txt"
        fwrite = open(filelist, 'a')
        fwrite.write(line)
        filesprocessed+=1
        fwrite.close()        
        
    nfiles+=1        
fr.close()

#################################################################### 
### Check Final input files have no duplicates
#################################################################### 

for check in range(1, number_of_cores+1):
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
        check_array.append(list)
    print  "File " + filelist + " contains " + str(nsamples) + " files"
    fcheck.close()
print "Total Number of input files = " + str(total_nsamples)     

if no_duplicate:
    print "Checking for duplicates: "
    print "Checking for duplicates:...... "
    print "Checking for duplicates: NONE found"
else:
     print "Checking for duplicates: "
     print "Checking for duplicates:...... "
     print "Checking for duplicates: Duplicate files found. Check script "
            
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
    runcommand = "nohup root -l -q -b " +  script + "&>" + log + "&"
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
        
