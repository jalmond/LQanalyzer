####################################################################
# Settings for User
####################################################################
InputDir="/data1/SNUData/Data/Electron/DoubleElectron/Nov13/periodA/"
sample="periodAelectron"
number_of_cores=1
print "Splitting job into " + str(number_of_cores)


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
output="/var/tmp/"+ getpass.getuser()+ "/" + sample + "/"
outputdir= output+ "/output/"
if not (os.path.exists(output)):
    os.system("mkdir " + output)
    print "Making tmp directory to run Job  : " + output

if(os.path.exists(outputdir)):
    os.system("rm " + outputdir + "/*.root")
    print "Emptying output directory as this should be empty for new job"
              
if not (os.path.exists(outputdir)):
        os.system("mkdir " + outputdir)
        

for i in range(0,number_of_cores):
    workdir =  output + "Job_" + str(i+1) + "/"
    if not (os.path.exists(workdir)):
            os.system("mkdir " + workdir)
            print "making work directory " + workdir
    

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
        configfile.write(makeConfigFile("ZTest", filelist, sample, count, outputdir)) #job, input, sample, ver, output
        

    if not nfiles % nfilesperjobs:
        print "File " + filelist + " contains " + str(nfiles_file) + " files"
        nfiles_file=0
        count+=1        
        fwrite.close()
        runscript = output+ "Job_" + str(count) + "/runJob_" + str(count) + ".C"
        filelist = output+ "Job_" + str(count) + "/" + sample + "_%s" % (count) + ".txt"
        fwrite = open(filelist, 'w')
        configfile=open(runscript,'w')
        configfile.write(makeConfigFile("ZTest", filelist, sample, count, outputdir))
        fwrite.write(line)
        filesprocessed+=1
        nfiles_file+=1
    else:
        fwrite.write(line)
        filesprocessed+=1
        nfiles_file+=1

    if nfiles == number_of_files :
        print "File " + filelist + " contains " + str(nfiles_file) + " files"
        print "last file added " + str(nfiles) + "/" + str(number_of_files)        
        fwrite.close()
fr.close()

print "Total number of files processed = " + str(filesprocessed)

###################################################
### Run each .C file in background
###################################################
print "Running LQAnalyzer jobs for: " + getpass.getuser()
for i in range(0,number_of_cores):
    script = output+ "Job_" + str(i+1) + "/runJob_" + str(i+1) + ".C"
    log = output+ "Job_" + str(i+1) + "/runJob_" + str(i+1) +".log"
    runcommand = "nohup root -q -b " +  script + "&> " +  log + "&"
    os.system(runcommand)   
    print "Running " + script + " . Log file --->  " + log 

os.system('rm inputlist.txt')

###################################################
## wait and do merging
###################################################

import thread,time
print "Waiting for all jobs to finish before Merging"

timeWait=60#
for i in range(0,number_of_cores):
    check_outfile = outputdir + sample +  "_" +  str(i+1) + ".root"
    if not (os.path.exists(check_outfile)):
        print "Output file " + check_outfile + " not yet ready. Wait " + str(timeWait) + " second..."
        time.sleep(timeWait)
        i = i-1
    if (os.path.exists(check_outfile)):
        print "Output file " + check_outfile + " READY" 
        
print "All sampless finished"        

        
