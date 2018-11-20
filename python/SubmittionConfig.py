############################################################    
### configure submisstion of CATANALYZER Jobs                                                                                                        #################################################################    
import os, getpass, sys,ROOT,time,curses,math

from functions import *
from optparse import OptionParser
from QuickHistCheck import *
from functions_submit import *
from functions_config import *

path_jobpre="/data1/"  ###  pre-path for input files for job runnig
an_jobpre="/data2/DATA/"   ####  pre-path for job output

isKisti = ("ui" in str(os.getenv("HOSTNAME")))
    
if isKisti:
    path_jobpre="/cms/scratch/SNU/CATAnalyzer/"
    an_jobpre="/cms/scratch/SNU/CATAnalyzer/"

#Import parser to get options                                                                                                                                                 
#parser = SetUpParser()
 
###################################################                                                                                                                            
#set the local variables using options                                                                                                                                         
###################################################                                                                                                                            

### submit_vardef sets variables from parser 
from submit_vardef import *


queuepath=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/QUEUE/ForceQueue.txt"

file_queuepath = open(queuepath,"r")
QueueForced=False
for line in file_queuepath:
    if "#" in line:
        continue
    sline = line.split()
    for s in sline:
        if "@" in s:
            queue= s
            QueueForced=True
file_queuepath.close()

if isKisti:
    queue =  "KISTIBATCH"


### printedqueue is queue outpit to screen, 
printedqueue=queue
printedqueue=printedqueue.replace("all.q@cms-0-","node")
printedqueue=printedqueue.replace(".local","")
printedqueue=printedqueue.replace("node","")
if printedqueue == "None":
    printedqueue = "fastq"
    queue = "fastq"


#### DoSendEmail sets whether email is to be sent about job status
DoSendEmail=False
if sendmail=="True":
    DoSendEmail=True

###  run_in_bkg True means no cursor used and no job status is printed to screen
run_in_bkg=False
if runinbkg == "True":
    run_in_bkg=True
    DoSendEmail=True
    print "Running in background"
    if not  os.getenv("USER") == "jalmond":
        if "jalmond" in useremail:
            print "Email could not be sent since email address is not set correctly in bin/catconfig."
            print "Please set email address and resubmit job"
            sys.exit()


###  set screen skim string
skim_print= SKIMNAME(useskim)


###### check if sample name is given in string
sample = sample.replace(":", " ")
sample = sample.replace("!!", " ")
sample = sample.split()

for s in sample:
    if not s:
        sys.exit()

################################################
################################################
################################################
####
###
###  setup online screening of job config
###
####
################################################
################################################


istatus_message=2

##### x and y coordinate of cursor window
winx = 5*len(sample) + 22 +  istatus_message
winy = 180

#####  output lists 

crash_output=[]
crash_outputjob=[]
output_bkg=[]

for out_x in range(1,winx):
    output_bkg.append(" "*170)   ### fill list with empty strings that will be replaced for lines with output messages
    

start_time = time.time()  
screen = curses.initscr()
screen.refresh()

stdscr = curses.newwin(winx, winy)
if not run_in_bkg:
    curses.noecho()
    curses.cbreak()

box_shift=0
summary_block0=4 + box_shift
summary_block1=summary_block0+ len(cycle) + 5
summary_block2=summary_block1+20
summary_block3=summary_block2+10
summary_block4=summary_block3+15
summary_block5=summary_block4+27
summary_block6=summary_block5+8
summary_block7=summary_block6+60

stdscr.addstr(0, box_shift,  "Job[" + str(tagger)+"] Summary:",curses.A_UNDERLINE)
stdscr.addstr(1, box_shift, "Job ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block0, "| Code Name                   ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block1, "| Sample Name                   ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block2, "| Skim    ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block3, "| Status                  ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block4, "| Cluster ID Range | njobs  ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block5, "| Queue  ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block6, "| Cluster Progess                                            ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block7, "|" ,curses.A_STANDOUT)
stdscr.addstr(0, summary_block2, "SubmittionConfig.py L147" ,curses.A_STANDOUT)

stdscr.refresh()


#### list 2 is more technical properties                                                                                                                                                                                                                                        
summary2_block0=4+box_shift
summary2_block1=summary2_block0+20
summary2_block2=summary2_block1+20
summary2_block3=summary2_block2+20
summary2_block4=summary2_block3+20
summary2_block5=summary2_block4+20


list2= istatus_message + 2 + len(sample)
stdscr.addstr(list2, box_shift,  "PostJob Summary:",curses.A_UNDERLINE)
stdscr.addstr(1+list2, box_shift, "Job ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block0, "| Cum.Process. Time  ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block1, "| Job Process. Time  ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block2, "| Physical Memory             ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block3, "| Virtual Memory         ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block4, "| OutputFile Size    ",curses.A_STANDOUT)
stdscr.addstr(1+list2, summary2_block5, "|",curses.A_STANDOUT)

list3=2*len(sample)+11 + istatus_message 
list3b=3*len(sample)+16 + istatus_message 
list3c=4*len(sample)+18 + istatus_message 
list4=5*len(sample)+20 + istatus_message 

python_logger=0


remove_from_end= 3 

stdscr.addstr(list4,box_shift,  "Job Status (Summary of latest background process):" ,curses.A_UNDERLINE)
#### make a random number for the job ID. This will help make a directory to work in

stdscr.addstr(list3, box_shift,  "Job Terminal Output: (will be deleted "+ future +")" ,curses.A_UNDERLINE)
stdscr.addstr(list3b, box_shift,  "Log Files: (will be deleted "+ future_week +")" ,curses.A_UNDERLINE)
stdscr.addstr(list3c, box_shift,  "Output Files:" ,curses.A_UNDERLINE)
stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L185" ,curses.A_STANDOUT)




for nsample in range(0, len(sample)):
    s=sample[nsample]

    ###  data has single le

    isMC = ISMC(s)
    if not isMC:
        if not isKisti:
            an_jobpre="/data7/DATA/"
            ####
            #### change dir of workspace to same as where data is  stored


#### make working directorr
if not os.path.exists(an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)):
    os.system("mkdir " + an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))
else:
    os.system("rm -r " + an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))
    os.system("mkdir " + an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))


### Make directory for job stats
statdir=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ os.getenv("USER")
if not os.path.exists(statdir):
    os.system("mkdir " +statdir)


if channel == "":
    channel = NULL

if not os.path.exists(path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"):
    os.system("cp  " + path_jobpre +"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFileSkeleton.txt " + path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt")


jobinfo_file_master = path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"
jobinfo_file= path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/PreMasterFile_"+os.getenv("CATVERSION")+ str(tagger)+".txt"
os.system("cp " + jobinfo_file_master + " " + jobinfo_file)


#http://stackoverflow.com/questions/14300770/how-to-noutrefresh-the-multi-line-output-dynamically
### split sample and check cluster queue

#an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/" + str(tagger)+ "/jobid.txt"
samples_inbackground=[]
samples_complete=[]
jobidcrash=[]
isample=-1

useskimtmp=""
ismctmp=  True
sampletmp=""
runnptmp=""
runtautmp=""
runcftmp=""
channeltmp=""

output_warning=[]

#### Loop over all samples in job
quickdraw=False
if quick_draw == "True":
    quickdraw=True

fileoutputlist=[]

for s in sample:
    if not s:
        continue
    ncopies=0
    for s2 in sample:
        if s == s2:
            ncopies=ncopies+1
    if ncopies > 1:
        if not run_in_bkg:
            curses.echo()
            curses.nocbreak()
            curses.endwin()
        print "%"*45
        print "List of samples contains duplicates. Please fix list"
        print "%"*45
        sys.exit()

runningData=False
longestjob=0.
njobfiles=0.
nlongestjobfiles=0.
nlongjobfiles=0.
reodered_samplelist=[]
sample_times=[]
tmpnjobs_for_submittion=0

### rundebug=True will not submit any jobs and debug.txt file will be produced in ./
rundebug=False
if rundebug:
    file_debug = open("debug.txt","w")
    file_debug.write("DEBUG \n")
    file_debug.close()

islongjob = []
isvfastjob = []
queuelist = []
for s in sample:
    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L292" ,curses.A_STANDOUT)



    stime=float(GetAverageTime(True, tagger, s, cycle,useskim,rundebug))
    if rundebug:
        file_debug = open("debug.txt","a")
        file_debug.write(s + " " + str(stime) + "\n")
        file_debug.close()
    s_nfile=int(GetNFiles(tagger, s, cycle,useskim))
    njobfiles+=s_nfile

    ### 90000 is 20 minutes for 25 job
    ### time of previous job is > 90000 then this job is sent to longq
    ### if jobs is > 10000 then number of jobs sent to batch queue is > 10, and chosen so that the time is similar to longest expected job
    if stime > 900000.:
        nlongjobfiles=nlongjobfiles+int(GetNFiles(tagger, s, cycle,useskim))
        ### will be true if 25 jobs take > 20 minutes OR the job is a new job
        islongjob.append(True)
    else:
        islongjob.append(False)
    if stime < 5000:
        isvfastjob.append(True)
    else:
        isvfastjob.append(False)
        
    sample_times.append(stime)        
    
    if stime > longestjob:
        nlongestjobfiles=s_nfile
        longestjob=stime

expected_jobs_to_submit=[]
nmediumjobs=0
job_summary=[]

for nsample in range(0, len(sample)):
    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L329" ,curses.A_STANDOUT)

    s=sample[nsample]
    if not islongjob[nsample]:
        nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
        dnjobs=int(DetermineNjobs(job_summary,njobfiles,longestjob,number_of_cores, tagger, s, cycle,useskim, printedqueue, nfreeqall, submit_allfiles, rundebug , -999, -999))
        expected_jobs_to_submit.append(dnjobs)
        if rundebug:
            file_debug = open("debug.txt","a")
            file_debug.write("dnjobs = " + str(dnjobs)+"\n")
            file_debug.close()

        tmpnjobs_for_submittion+=dnjobs
        if not isvfastjob[nsample]:
            nmediumjobs+=1
    else:
        expected_jobs_to_submit.append(0.)



sort_bytime=False
if sort_bytime:
    orig_sample_times=sample_times
    sample_times.sort()
    sorted_times=[]
    for t in range(0, len(sample_times)):
        sorted_times.append(sample_times[len(sample_times) -t-1])

    sorted_samples=[]
    for s in  range(0, len(sorted_times)):
        if rundebug:
            file_debug = open("debug.txt","a")
            file_debug.write(str(sorted_times[s])+"\n")
            file_debug.close()
        
        sorted_time = sorted_times[s]
        for s1 in  range(0, len(sample)):
            if rundebug:
                file_debug = open("debug.txt","a")
                file_debug.write("st " + str(sample_times[s1])+"\n")
                file_debug.close()
            stime=orig_sample_times[s1]
            if stime== sorted_time:
                sorted_samples.append(sample[s1])
                if rundebug:
                    file_debug = open("debug.txt","a")
                    file_debug.write(sample[s1]+"\n")
                    file_debug.close()
                
    if not (len(sorted_samples) == len(sample)):
        sorted_samples=sample

    sample = sorted_samples

if rundebug:
    for nsample in range(0, len(sample)):
        s=sample[nsample]
        sample_islongjob= islongjob[nsample]
        file_debug = open("debug.txt","a")
    if sample_islongjob:
        file_debug.write(s + " run on longq\n" )
    else:
        file_debug.write(s + " run on fastq\n" )
    file_debug.close()
                                

### reset jobsummary
job_summary=[]

tmpqueue=queue
## log what jobs are running                                                                                                                                                                                                                                        
jobs_running =[]
for nsample in range(0, len(sample)):
    jobs_running.append(0.)


for nsample in range(0, len(sample)):
    
    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L407" ,curses.A_STANDOUT)
    
    s=sample[nsample]
    sample_islongjob= islongjob[nsample]
    sample_isfastjob= isvfastjob[nsample]
    #if "SKTreeMaker" in cycle:
    #sample_islongjob=True
        
    #### Get number of subjobs from DetermineNjobs function. Unless number_of_cores is set to 1 this will check the processing time of the cycle and batch queue to determin the number of jobs to run
    if rundebug:
        file_debug = open("debug.txt","a")
    
    ## queue is set to default or that requested by user
    queue=tmpqueue
    printedqueue=tmpqueue
    
    if sample_islongjob:
        printedqueue="longq"
        queue="longq"

    ### FreeSpaceInQueue returns number of places in queue requested by user/default
        
    if rundebug:
        file_debug.write("Checking number of free spaces in queue\n")

    nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
    if rundebug:
        file_debug.write("sample: "+ s + "\n")
        file_debug.write("queue = " + queue + "\n")
        file_debug.write("printedqueue = " + printedqueue +"\n")
        file_debug.write("nfreeqall = " + str(nfreeqall) +"\n")

    ## change queue if default is almost full
    if queue == "fastq" and nfreeqall < 5:
        if rundebug:
            file_debug.write("fastq is busy \n")
        queue="longq"
        printedqueue="longq"
        if rundebug:
            file_debug.write("Checking number of free spaces in long queue\n")
        nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
        if rundebug:
            file_debug.write("longq: nfreeqall = " + str(nfreeqall) +"\n")
        
        ### check that second queue is almost not full. If so move back to default queue 
        if queue == "longq" and nfreeqall < 50:
            if rundebug:
                file_debug.write("longq is busy \n")
            queue="fastq"
            printedqueue="fastq"
            if rundebug:
                file_debug.write("Checking number of free spaces in fast  queue\n")

            nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
    elif queue == "longq" and nfreeqall < 5 and not sample_islongjob:
        if rundebug:
            file_debug.write("longq is busy \n")
        queue="fastq"
        printedqueue="fastq"
        if rundebug:
            file_debug.write("Checking number of free spaces in fast queue\n")
        nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
        if rundebug:
            file_debug.write("fastq: nfreeqall = " + str(nfreeqall) +"\n")
        ### check that second queue is almost not full. If so move back to default queue                                                                                        
        if queue == "fast" and nfreeqall < 5:
            if rundebug:
                file_debug.write("fastq is busy \n")
            queue="longq"
            printedqueue="long"
            if rundebug:
                file_debug.write("Checking number of free spaces in long queue\n")
            nfreeqall=FreeSpaceInQueue(printedqueue,  tagger)
            
    if rundebug:            
        file_debug.close()
        

    correctedtmpnjobs_for_submittion = tmpnjobs_for_submittion
    for ijobcheck in range(0, len(jobs_running)):
        for bs in samples_inbackground:
            if bs == sample[ijobcheck]:
                correctedtmpnjobs_for_submittion -= expected_jobs_to_submit[ijobcheck]*GetRunning(tagger,sample[ijobcheck])
        
    njobs_for_submittion=int(DetermineNjobs(job_summary,njobfiles,longestjob,number_of_cores, tagger, s, cycle,useskim, printedqueue, nfreeqall, submit_allfiles, rundebug,correctedtmpnjobs_for_submittion, nmediumjobs))

    
    if rundebug:
        file_debug = open("debug.txt","a")
        file_debug.write("njobs = " + str(njobs_for_submittion) + "\n")
        file_debug.close()

    if not sample_islongjob:
        if not sample_isfastjob:
            nmediumjobs = nmediumjobs-1


    if setnumber_of_cores and submit_allfiles:
        njobs_for_submittion=number_of_cores

    if number_of_cores == -311:
        njobs_for_submittion=-311
    if not QueueForced:
        newqueue = ChangeQueue(job_summary,printedqueue, njobs_for_submittion, tagger,rundebug)
        if rundebug:
            file_debug = open("debug.txt","a")
            file_debug.write("newqueue = " + str(newqueue) + "\n")
            file_debug.close()

        printedqueue=newqueue
        queue=newqueue
    
        ### If job is known to last longer than 90000 (if n=1 in submittion) seconds then send job to longq
        if sample_islongjob:
            printedqueue="longq"
            queue="longq"


            
    isample=isample+1
    queuelist.append(printedqueue)
    ## set MC bool from the sample length. This is the letter of the data period for data
    isMC = ISMC(s)

    runningData= not isMC
    
    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L533" ,curses.A_STANDOUT)


    if run_in_bkg:
        del output_bkg[:]
        for out_x in range(1,winx):
            output_bkg.append(stdscr.instr(out_x, 0))
        UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")    
    #### if sample is submitted this for loop will check job process on cluster and update the screen/terminal
    for x in range(0, len(sample)):
        stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
        stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L543" ,curses.A_STANDOUT)

        if run_in_bkg:
            del output_bkg[:]
            for out_x in range(1,winx):
                output_bkg.append(stdscr.instr(out_x, 0))
            UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")

        ### check if sample is already complet. Only update terminal for samples not complete
        sample_complete=False
        for finsamp in samples_complete:
            if sample[x] == finsamp:
                sample_complete=True
        if sample_complete:
            continue
        
        #### Check that the sample is running. Do not update terminal for samples that are not submitted to batch queue
        backgroundsamples=False
        for bs in samples_inbackground:
            if bs == sample[x]:
                backgroundsamples=True
        ### the following variables are used to print the output sample name that is determined in the localsubmit.py

        useskimtmp=useskim

        ismctmp = ISMC(sample[x])

        sampletmp=sample[x]
        runnptmp=runnp
        runtautmp=runtau
        runcftmp=runcf
        channeltmp=channel

        ### if sample has been submitted to cluster backgroundsamples will be True        
        if backgroundsamples:
            #### in case the job id file is not yet filled add while condition
            jobid_exists=True
            while jobid_exists:        
                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L581" ,curses.A_STANDOUT)

                if rundebug:
                    file_debug = open("debug.txt","a")
                    file_debug.write("Checking " +  an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt\n")
                    file_debug.close()
                path_job_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt"  
                if  os.path.exists(path_job_check):
                    jobid_exists=False
            if rundebug:
                file_debug = open("debug.txt","a")
                file_debug.write(an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt exists\n")
                file_debug.close()
                
            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L595" ,curses.A_STANDOUT)


            #CheckRunningStatus(an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + sample[x] +".txt")

            file_job_check=open(path_job_check ,"r")
            jobid1=0
            jobid2=0
            #### check status of job on cluster
            njobs_finished=0.
            nrunning=0.
            nqueue=0.
            njobs_in_total=0.  ### should equal three above
            path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            if not  isKisti:
                os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
            else:
                os.system("condor_q " + os.getenv("USER") + " > " +  path_clust_check)


                
            ijob=0

            ### loop over job IDS
            for sline in file_job_check:
                ssline = sline.split()
                if len(ssline) < 1:
                    continue
                line=ssline[0]
                if jobid1 == 0:
                    jobid1=line
                jobid2=line    
                jobid1=jobid1.replace(".","")
                jobid2=jobid2.replace(".","")

                if  isKisti:
                    os.system("condor_q " + line + " > " +  path_clust_check)


                ijob=ijob+1.
                njobs_in_total=njobs_in_total+1.
                file_clust_check=open(path_clust_check,"r")
                job_in_queue=False
                if  isKisti:
                    for cline in file_clust_check:
                        if not os.getenv("USER")  in cline:
                            continue
                        job_in_queue=True
                        splitline  = cline.split()
                        if splitline[6] ==  "1":
                            nrunning = nrunning + 1.
                        elif splitline[5] ==  "1":
                            job_in_queue=False
                        else:
                            nqueue = nqueue + 1.
                    if not job_in_queue:
                        njobs_finished=njobs_finished+1.

                else:
                    for cline in file_clust_check:
                        splitline  = cline.split()
                        if len(splitline) < 6:
                            continue
                        if not os.getenv("USER")  in cline:
                            continue
                        if line == splitline[0]:
                            job_in_queue=True
                            if splitline[4] == "r":
                                nrunning = nrunning + 1.
                            else:
                                nqueue = nqueue + 1.
                    if not job_in_queue:
                        njobs_finished=njobs_finished+1.

            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L669" ,curses.A_STANDOUT)
            stdscr.refresh()



            path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            os.system("rm " + path_clust_check)
    
            if njobs_in_total == 0:
                continue
            file_job_check.close()
            if njobs_finished == njobs_in_total:
                samples_complete.append(sample[x])
                
            ### add finished jobs to running jobs status since they have ran    
            nrunning = nrunning + njobs_finished    
            nrun_per = round( (nrunning/float(njobs_in_total)), 2)
            nfin_per = round( (njobs_finished/float(njobs_in_total)), 2)
            if nrunning > 0:
                jobs_running[x] = nrun_per

            nscreen_run= "["
            nscreen_fin= "["
            for xsr in range(0, 9):
                if nrun_per > float(xsr)* 0.1:
                    nscreen_run+="#"
                else:
                    nscreen_run+="-"
            if nrun_per == 1.:
                nscreen_run+="#"
            else:
                nscreen_run+="-"
            nscreen_run+="]"
            for xsr in range(0, 9):
                if nfin_per > float(xsr)* 0.1:
                    nscreen_fin+="#"
                else:
                    nscreen_fin+="-"
            if nfin_per == 1.:
                nscreen_fin+="#"
            else:
                nscreen_fin+="-"
            nscreen_fin+="]"


            if nrun_per == 0.:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block0, "| " +  cycle, curses.A_NORMAL )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + sample[x], curses.A_NORMAL )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block2, "| " + skim_print, curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Submitted " , curses.A_NORMAL) 
                stdscr.refresh()
            else:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_BOLD )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_BOLD )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )

                stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Running    " , curses.A_BLINK) 
                if not jobid1 == 0:
                    nblanks=2*(8-len(str(jobid2)))
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2) + " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)) , curses.A_BOLD)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_BOLD)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block6,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block7 ,"|    ",curses.A_BOLD)    
                stdscr.refresh()
                if run_in_bkg:
                    del output_bkg[:]
                    for out_x in range(1,winx):
                        output_bkg.append(stdscr.instr(out_x, 0))
                        UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")
            if nfin_per == 1.:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_DIM )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_DIM )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )

                stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Complete " , curses.A_DIM) 
                job_time = time.time() - start_time
                if not jobid1 == 0:    
                    nblanks=2*(8-len(str(jobid2)))
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)), curses.A_DIM)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " +queuelist[x] , curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block6,"| "  , curses.A_DIM)
 
                stdscr.addstr(int(x)+istatus_message, summary_block6,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM) 
                stdscr.refresh()

                path_job=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/" + str(tagger)+ "/statlog_time_"+sample[x] + tagger + ".txt"
                ismerging=True
            
                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L755 "+ path_job ,curses.A_STANDOUT)
                stdscr.refresh()

                while not os.path.exists(path_job):
                    if rundebug:
                        file_debug = open("debug.txt","a")
                        file_debug.write("Checking for " + path_job + " \n")
                        file_debug.close()
                    if ismerging:
                        stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                        stdscr.addstr(2+list2+int(x), summary2_block1 ,"| MERGING OUTPUT ", curses.A_BLINK)
                        stdscr.refresh()
                        ismerging=False
                    check_crash_stat=True
                    if check_crash_stat:
                        check_crashfile=an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + sample[x] +".txt"
                        if not os.path.exists(check_crashfile):
                            continue
                        file_check_crashfile=open(check_crashfile,"r")
                        crash_in_job=False
                        crashlog=[]
                        for line in file_check_crashfile:
                            if " No such file or directory:" in line:
                                crash_in_job=True
                                crashlog.append(line)
                        file_check_crashfile.close()
                        if crash_in_job:
                            crash_log= an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"
                            if os.path.exists(crash_log):
                                file_crash=open(crash_log,"a")
                                for linex in  crashlog:
                                    file_crash.write(linex)
                                file_crash.close()
                            else:
                                os.system("mkdir " + an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/")
                                file_crash=open(crash_log,"w")
                                for linex in  crashlog:
                                    file_crash.write(linex)
                                file_crash.close()
                            break

                    continue
                
                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L811" ,curses.A_STANDOUT)
                stdscr.refresh()


                crash_log= an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"

                if os.path.exists(crash_log):
                    jobidcrash.append(int(x))
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| JOB CRASHED    ", curses.A_BLINK)
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir)  +GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                    fileoutputlist.append(outfilepath)
                    if "SKTreeMaker" in cycle:
                        outfilepath=GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +":###CRASH###: No OutputFile for " + sample[x])
                    crash_output.append( logpath)
                    crash_outputjob.append(str(jobid1))
                    stdscr.refresh()
                else:
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block0 ,"| " + str(round(job_time,2)) + "[s]",curses.A_DIM) 
                    stdscr.refresh()
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir) + GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                    fileoutputlist.append(outfilepath)
                    if "SKTreeMaker" in cycle:
                        outfilepath=GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)

                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +": OutputFile for " + sample[x] + " = " + str(outfilepath))
                    stdscr.refresh()
                    
                    filesize=0.
                    memoryusage_p=0.
                    memoryusage_v=0.
                    outputfile_size=0.
                    first_job_time=0.
                    last_job_time=0.
                    file_job=open(path_job,"r")
                    for line in file_job:
                        splitline  = line.split()
                        if len(splitline) < 2:
                            continue
                        if "job_time"  == splitline[0]:
                            first_job_time=float(splitline[1])
                        if "last_job_time"  == splitline[0]:
                            last_job_time=float(splitline[1])
                        if "outputfile_size" == splitline[0]:
                            outputfile_size=splitline[1]
                        if "memoryusage_p" ==  splitline[0]:
                            memoryusage_p=splitline[1]    
                        if "memoryusage_v" ==  splitline[0]:
                            memoryusage_v=splitline[1]
                    file_job.close()
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| " + str(round(first_job_time,2)) + "-" +  str(round(last_job_time,2)) + "[s]   ",curses.A_DIM) 

                    if LargeMemory(memoryusage_p,large_memory_check):
                        output_warning.append("WARNING:: Physical memory of job " + sample[x]+ "  is excess of " + str(large_memory_check) + " MB.")
                    if LargeMemory(memoryusage_v,large_memory_check):
                        output_warning.append("WARNING:: Virtual memory of job " + sample[x] + " is excess of " + str(large_memory_check) + " MB.")

                    if isMC:
                        if LargePhysicalMemoryIncrease(memoryusage_p,sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Physical memory of job " + sample[x] + " is " + RoundMemory(memoryusage_p) + " compared to previous jobs " + GetPhysicalMemoryUsage(sample[x], cycle,tagger,useskim) + ". This is likely a memory leak introduced recently")
                        if LargeVirtualMemoryIncrease(memoryusage_v,sample[x], cycle,tagger,useskim):
                                output_warning.append("WARNING:: Virtual memory of job " + sample[x] + " is " + RoundMemory(memoryusage_v) + " compared to previous jobs " + GetVirtualMemoryUsage(sample[x], cycle,tagger,useskim) + ". This is likely a memory leak introduced recently")    
                        if LargeFileSize(outputfile_size,large_file_size):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " greater than " + str(large_file_size) + " MB")
                        if LargeFileSizeIncrease(outputfile_size,sample[x], cycle,tagger,useskim,file_increase_warning):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " compared to previous jobs " + GetFileSize(sample[x], cycle,tagger,useskim))
                        if TimeIncrease(first_job_time,sample[x], cycle,tagger,useskim,time_increase_warning):
                            output_warning.append("WARNING:: Job time per input file increased for " + sample[x] + "  from " + str(first_job_time) + " compared to previous job time " + GetTime(sample[x], cycle,tagger,useskim))
                    else:
                        if LargePhysicalMemoryIncrease(memoryusage_p,channel + "_" + sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Physical memory of job " + sample[x] + " is " + RoundMemory(memoryusage_p) + " compared to previous jobs " + GetPhysicalMemoryUsage(channel + "_" + sample[x], cycle,tagger,useskim) + ". This is likely a memory leak introduced recently")
                        if LargeVirtualMemoryIncrease(memoryusage_v,channel + "_" + sample[x], cycle,tagger,useskim):
                                output_warning.append("WARNING:: Virtual memory of job " +sample[x] +" is " + RoundMemory(memoryusage_v) + " compared to previous jobs " + GetVirtualMemoryUsage(channel + "_" + sample[x], cycle,tagger,useskim) + ". This is likely a memory leak introduced recently")
                        if LargeFileSize(outputfile_size,large_file_size):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " greater than " + str(large_file_size) + " MB")
                        if LargeFileSizeIncrease(outputfile_size,channel + "_" + sample[x], cycle,tagger,useskim,file_increase_warning):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " compared to previous jobs " + GetFileSize(channel + "_" + sample[x], cycle,tagger,useskim))
                        if TimeIncrease(first_job_time,channel + "_" + sample[x], cycle,tagger,useskim,time_increase_warning):
                            output_warning.append("WARNING:: Job time per input file for  " + sample[x] + " increased from " + str(first_job_time) + " compared to previous job time " + GetTime(sample[x], cycle,tagger,useskim))
     
                        
                    stdscr.addstr(2+list2+int(x), summary2_block2 ,"| " + RoundMemory(memoryusage_p),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block3 ,"| " + RoundMemory(memoryusage_v),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block4 ,"| " + str(outputfile_size),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block5 ,"| ",curses.A_DIM)
                    stdscr.refresh()


        else:
            stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)) )
            stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle )
            if isMC:
                stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x] )
            else:
                stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
            stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print )
            stdscr.addstr(int(x)+istatus_message, summary_block3,"| In Queue " )
            stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|" )
            stdscr.addstr(int(x)+istatus_message, summary_block5,"|    ")
            stdscr.addstr(int(x)+istatus_message, summary_block6,"|    ")
            stdscr.addstr(int(x)+istatus_message, summary_block7,"|    ")
            stdscr.refresh()
            
            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L920" ,curses.A_STANDOUT)
            stdscr.refresh()
        
    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L922" ,curses.A_STANDOUT)
    stdscr.refresh()


    ##### New Code looks at submittnig jobs to batch queue        
    logfile=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/" + str(tagger)+ "/statlog_"+ s + tagger + ".txt"
    if not os.path.exists(path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/" + str(tagger)):
        os.system("mkdir " + path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/" + str(tagger))

    filestatlog=open(logfile,"w")
    filestatlog.write("user " +  os.getenv("USER")+ " \n")
    filestatlog.write(" -c " + cycle + " \n")
    filestatlog.write(" -v " + catversion + " \n")
    filestatlog.write(" -s " + channel + " \n")
    filestatlog.write(" -d " + data_lumi + " \n")
    filestatlog.write("sample "+ s + " \n")
    filestatlog.write(" -m " + useskim + " \n")
    filestatlog.write("cattag " + os.getenv("CATTAG") + " \n")
    filestatlog.write(time.strftime("%c")  + " \n")
    filestatlog.write("############################" + " \n")
    filestatlog.close()
    blankbuffer = "         "
    if not queue:
        queue="None"
    command1= "python  " +  os.getenv("LQANALYZER_DIR")+  "/python/CATConfig.py -p " + s + "  -s " + str(channel) + "  -j " + str(njobs_for_submittion) + " -c  " + str(cycle)+ " -o " + str(logstep)+ "  -d " + str(data_lumi) + " -O " + str(Finaloutputdir) + "  -w " + str(remove_workspace)+ " -l  " + str(loglevel) + "  -k " + str(skipev) + "  -n " + str(number_of_events_per_job) + "  -e " + str(totalev) + "  -x " + str(xsec) + "  -T " + str(tar_lumi) + " -E " + str(eff_lumi) + "  -S " + str(useskinput) + " -R " + str(runevent)+ "  -N " + str(useCATv742ntuples) + " -L " + str(tmplist_of_extra_lib) + " -D " + str(DEBUG) + " -m " + str(useskim) + " -P  " + str(runnp) + " -Q " + str(runcf) + " -v " + str(catversion) + " -f " + str(skflag) + " -b " + str(usebatch) + "  -X " + str(tagger) +" -q " + str(queue) + " -J " + str(setjobs) + " -G " + str(runtau) + " -F " + str(tmpsubmit_allfiles) + " -g " + str(tmp_filename)
    command2=command1
    command2 = command2.replace("CATConfig.py", "localsubmit.py")
    command2_background=command2 + "&>  "+an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + s+".txt&"
    checkqueue=True
    stdscr.addstr(list4+1, box_shift,  "Initialise:: sample " + s +  blankbuffer)
    stdscr.refresh()

    while checkqueue:
        stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
        stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L962 checking batch queue for "+ s ,curses.A_STANDOUT)
        
        stdscr.refresh()

        os.system(command1)

        if not os.path.exists(an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger):
            stdscr.addstr(list4+1, box_shift,  "Queue busy.. please wait")
            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L970 Queue busy.. please wait "+ s ,curses.A_STANDOUT)

            stdscr.refresh()
            
            for x in range(0, len(sample)):
                sample_complete=False
                for finsamp in samples_complete:
                    if sample[x] == finsamp:
                        sample_complete=True
            if sample_complete:
                continue
            backgroundsamples=False
            for bs in samples_inbackground:
                if bs == sample[x]:
                    backgroundsamples=True
            useskimtmp=useskim
            ismctmp= ISMC(sample[x])

            sampletmp=sample[x]
            runnptmp=runnp
            runcftmp=runcf
            channeltmp=channel
            if backgroundsamples:
                jobid_exists=True
                while jobid_exists:
                    path_job_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt"
                    if  os.path.exists(path_job_check):
                        jobid_exists=False
                file_job_check=open(path_job_check ,"r")
                jobid1=0
                jobid2=0
                njobs_finished=0.
                nrunning=0.
                nqueue=0.
                njobs_in_total=0.  ### should equal three above                                                                                                                                                                                                       
                path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
                if not isKisti:
                    os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
                else:
                    os.system("condor_q " + os.getenv("USER") + " > " +  path_clust_check)

                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1011 "+ s+ " checking " + sample[x] ,curses.A_STANDOUT)
    
                ijob=0

                for sline in file_job_check:
                    ssline = sline.split()
                    if len(ssline) < 1:
                        continue
                    line=ssline[0]
                    if jobid1 == 0:
                        jobid1=line
                    jobid2=line
                    jobid1=jobid1.replace(".","")
                    jobid2=jobid2.replace(".","")


                    if  isKisti:
                        os.system("condor_q " + line + " > " +  path_clust_check)


                    ijob=ijob+1.
                    njobs_in_total=njobs_in_total+1.
                    file_clust_check=open(path_clust_check,"r")
                    job_in_queue=False
                    if  isKisti:
                        for cline in file_clust_check:
                            if not os.getenv("USER")  in cline:
                                continue
                            job_in_queue=True
                            splitline  = cline.split()
                            if splitline[6] ==  "1":
                                nrunning = nrunning + 1.
                            elif splitline[5] ==  "1":
                                job_in_queue=False
                            else:
                                nqueue = nqueue + 1.
                        if not job_in_queue:
                            njobs_finished=njobs_finished+1.


                    else:
                        for cline in file_clust_check:
                            splitline  = cline.split()
                            if len(splitline) < 6:
                                continue
                            if not os.getenv("USER")  in cline:
                                continue
                            if line == splitline[0]:
                                job_in_queue=True
                                if splitline[4] == "r":
                                    nrunning = nrunning + 1.
                                else:
                                    nqueue = nqueue + 1.
                        if not job_in_queue:
                            njobs_finished=njobs_finished+1.


                    file_clust_check.close()


                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)                    
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1062" ,curses.A_STANDOUT)
                
                stdscr.refresh()

                path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
                os.system("rm " + path_clust_check)
                if njobs_in_total == 0:
                    continue
                file_job_check.close()
                if njobs_finished == njobs_in_total:
                    samples_complete.append(sample[x])
                nrunning = nrunning + njobs_finished
                nrun_per = round( (nrunning/float(njobs_in_total)), 2)
                nfin_per = round( (njobs_finished/float(njobs_in_total)), 2)
                nscreen_run= "["
                nscreen_fin= "["
                for xsr in range(0, 9):
                    if nrun_per > float(xsr)* 0.1:
                        nscreen_run+="#"
                    else:
                        nscreen_run+="-"
                if nrun_per == 1.:
                    nscreen_run+="#"
                else:
                    nscreen_run+="-"
                nscreen_run+="]"
                for xsr in range(0, 9):
                    if nfin_per > float(xsr)* 0.1:
                        nscreen_fin+="#"
                    else:
                        nscreen_fin+="-"
                if nfin_per == 1.:
                    nscreen_fin+="#"
                else:
                    nscreen_fin+="-"
                nscreen_fin+="]"
                
                if nrun_per == 0.:
                    stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_NORMAL )
                    stdscr.addstr(int(x)+istatus_message, summary_block0, "| " +  cycle, curses.A_NORMAL )
                    if isMC:
                        stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + sample[x], curses.A_NORMAL )
                    else:
                        stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                    stdscr.addstr(int(x)+istatus_message, summary_block2, "| " + skim_print, curses.A_NORMAL )
                    stdscr.addstr(int(x)+istatus_message, summary_block3,"| Submitted " , curses.A_NORMAL)
                    stdscr.refresh()
                else:
                    stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_BOLD )
                    stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_BOLD )
                    if isMC:
                        stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_BOLD )
                    else:
                        stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )

                    stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_BOLD )
                    stdscr.addstr(int(x)+istatus_message, summary_block3,"| Running    " , curses.A_BLINK)
                    if not jobid1 == 0:
                        nblanks=2*(8-len(str(jobid2)))
                        stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2) +  " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)) , curses.A_BOLD)
                        stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x] , curses.A_BOLD)
                                            
                    else:
                        stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_BOLD)
                        stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_BOLD)

                    stdscr.addstr(int(x)+istatus_message, summary_block6,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                    stdscr.addstr(int(x)+istatus_message, summary_block7 ,"|    ",curses.A_BOLD)
                    stdscr.refresh()
                if nfin_per == 1.:
                    stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_DIM )
                    stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_DIM )
                    if isMC:
                        stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_DIM )
                    else:
                        stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                    stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_DIM )
                    stdscr.addstr(int(x)+istatus_message, summary_block3,"| Complete " , curses.A_DIM)
                    if run_in_bkg:
                        del output_bkg[:]
                        for out_x in range(1,winx):
                            output_bkg.append(stdscr.instr(out_x, 0))
                            UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")
                    job_time = time.time() - start_time
                    if not jobid1 == 0:
                        nblanks=2*(8-len(str(jobid2)))
                        stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)), curses.A_DIM)
                        stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_DIM)

                    else:
                        stdscr.addstr(int(x)+istatus_message, summary_block6,"| "  , curses.A_DIM)
                        
                    stdscr.refresh()
                    
        else:

            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1167 Submitting sample to queue  " + s ,curses.A_STANDOUT)

            stdscr.refresh()

            os.system("rm -r "+an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger)
            stdscr.addstr(list4+1, box_shift,  "Submitting sample to queue  " + s)
            stdscr.refresh()
            
            checkqueue=False
            
            if not os.path.exists(an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger):
                os.system("mkdir  "+an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger)

            stdscr.addstr(list3 + 1+int(isample), box_shift,  "Running " + s + " in background: terminal output sent to "+an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" +  str(tagger) + "/" + tagger + "/" + s + ".txt")
            stdscr.refresh()
            stdscr.addstr(int(isample)+istatus_message, box_shift,  str(int(isample+1)) )
            stdscr.addstr(int(isample)+istatus_message, summary_block0,  "| " + cycle  )
            stdscr.addstr(int(isample)+istatus_message, summary_block1,  "| " + s  )
            stdscr.addstr(int(isample)+istatus_message, summary_block2,  "| " + skim_print  )
            stdscr.addstr(int(isample)+istatus_message, summary_block3,"| In Queue " , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block5,"|    ")
                        
            stdscr.addstr(int(isample)+istatus_message, summary_block6,"| Running[---------]   Complete[----------]   ")
            stdscr.addstr(int(isample)+istatus_message, summary_block7,"|    ")

            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1193 " +  an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + s+".txt" ,curses.A_STANDOUT)
            stdscr.refresh()
            os.system(command2_background)
            samples_inbackground.append(s)
            if run_in_bkg:
                del output_bkg[:]
                for out_x in range(1,winx):
                    output_bkg.append(stdscr.instr(out_x, 0))
                    UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")

stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1203 All samples submitted" ,curses.A_STANDOUT)

stdscr.refresh()

StillRunning=True
while StillRunning:
    StillRunning=False

    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1211" ,curses.A_STANDOUT)
    
    stdscr.refresh()

    if run_in_bkg:
        del output_bkg[:]
        for out_x in range(1,winx):
            output_bkg.append(stdscr.instr(out_x, 0))
        UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")

    for x in range(0, len(sample)):
        sample_complete=False
        for finsamp in samples_complete:
            if sample[x] == finsamp:
                sample_complete=True
        if sample_complete:
            continue
        ## Need to sleep here so that cursor is not moving on screen too fast
        time.sleep(2.)
        
        stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
        stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1220" ,curses.A_STANDOUT)
        
        stdscr.refresh()

        useskimtmp=useskim
        ismctmp= ISMC(sample[x])
        sampletmp=sample[x]
        runnptmp=runnp
        runcftmp=runcf
        channeltmp=channel

        if run_in_bkg:
            del output_bkg[:]
            for out_x in range(1,winx):
                output_bkg.append(stdscr.instr(out_x, 0))
            UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")

        backgroundsamples=False
        for bs in samples_inbackground:
            if bs == sample[x]:
                backgroundsamples=True
        if backgroundsamples:

            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1243" ,curses.A_STANDOUT)
            
            stdscr.refresh()

            jobid_exists=True
            while jobid_exists:
                path_job_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt"
                stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1248 : Checking " + path_job_check + " exists" ,curses.A_STANDOUT)
                stdscr.refresh()
        
                if  os.path.exists(path_job_check):
                    jobid_exists=False                    


            len_blank = len(path_job_check)
            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1254" + " "*(len_blank +20) ,curses.A_STANDOUT)
            stdscr.refresh()

            file_job_check=open(path_job_check ,"r")
            njobs_finished=0.
            nrunning=0.
            nqueue=0.
            njobs_in_total=0.
            path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            if not  isKisti:
                os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
            else:
                os.system("condor_q " + os.getenv("USER") + " > " +  path_clust_check)
                

            ijob=0
            jobid1=0
            jobid2=0
            for sline in file_job_check:
                ssline = sline.split()
                if len(ssline) < 1:
                    continue
                line=ssline[0]
                if jobid1==0:
                    jobid1=line
                jobid2=line
                jobid1=jobid1.replace(".","")
                jobid2=jobid2.replace(".","")
                
                if  isKisti:
                    os.system("condor_q " + line + " > " +  path_clust_check)
                    
                    
                ijob=ijob+1.
                njobs_in_total=njobs_in_total+1.
                file_clust_check=open(path_clust_check,"r")
                job_in_queue=False
                if  isKisti:
                    for cline in file_clust_check:
                        if not os.getenv("USER")  in cline:
                            continue
                        job_in_queue=True
                        splitline  = cline.split()
                        if splitline[6] ==  "1":
                            nrunning = nrunning + 1.
                        elif splitline[5] ==  "1":
                            job_in_queue=False
                        else:
                            nqueue = nqueue + 1.
                    if not job_in_queue:
                        njobs_finished=njobs_finished+1.


                else:
                    for cline in file_clust_check:
                        splitline  = cline.split()
                        if len(splitline) < 6:
                            continue
                        if not os.getenv("USER")  in cline:
                            continue
                        if line == splitline[0]:
                            job_in_queue=True
                            if splitline[4] == "r":
                                nrunning = nrunning + 1.
                            else:
                                nqueue = nqueue + 1.
                    if not job_in_queue:
                        njobs_finished=njobs_finished+1.
                    
                file_clust_check.close()

            stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
            stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1324" ,curses.A_STANDOUT)
            stdscr.refresh()

            path_clust_check=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            os.system("rm " + path_clust_check)
        

            if njobs_in_total         == 0.:
                continue
            file_job_check.close()
            if njobs_finished == njobs_in_total:
                samples_complete.append(sample[x])
            else:
                StillRunning=True

            nrunning = nrunning + njobs_finished    
            nrun_per = round( (nrunning/float(njobs_in_total)), 2)
            nfin_per = round( (njobs_finished/float(njobs_in_total)), 2)
            
            nscreen_run= "["
            nscreen_fin= "["
            for xsr in range(0, 9):
                if nrun_per > float(xsr)* 0.1:
                    nscreen_run+="#"
                else:
                    nscreen_run+="-"
            if nrun_per == 1.:
                nscreen_run+="#"
            else:
                nscreen_run+="-"
            nscreen_run+="]"
            for xsr in range(0, 9):
                if nfin_per > float(xsr)* 0.1:
                    nscreen_fin+="#"
                else:
                    nscreen_fin+="-"
            if nfin_per == 1.:
                nscreen_fin+="#"
            else:
                nscreen_fin+="-"
            nscreen_fin+="]"
            
            if nrun_per == 0.:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_NORMAL )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " +  sample[x], curses.A_NORMAL )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block2, "| " +  skim_print, curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Submitted " , curses.A_NORMAL)
                stdscr.refresh()
            else:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_BOLD )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_BOLD )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Running    " , curses.A_BLINK)
                if not jobid1 == 0:
                    nblanks=2*(8-len(str(jobid2)))
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)), curses.A_BOLD)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_BOLD)

                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|" , curses.A_BOLD)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x]  , curses.A_BOLD)

                stdscr.addstr(int(x)+istatus_message, summary_block6,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                
                stdscr.addstr(int(x)+istatus_message, summary_block7 ,"|    ",curses.A_BOLD)
                stdscr.refresh()
            if nfin_per == 1.:
                if run_in_bkg:
                    del output_bkg[:]
                    for out_x in range(1,winx):
                        output_bkg.append(stdscr.instr(out_x, 0))
                        UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")

                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  "| " + cycle, curses.A_DIM )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1,  "| " + sample[x], curses.A_DIM )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block2,  "| " + skim_print, curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Complete " , curses.A_DIM)
                job_time = time.time() - start_time
                if not jobid1 == 0:
                    nblanks=2*(8-len(str(jobid2)))
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + " "*nblanks +   "| " + str(1+int(jobid2)-int(jobid1)), curses.A_DIM)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x], curses.A_BOLD)

                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_DIM)
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| " + queuelist[x] , curses.A_BOLD)

                stdscr.addstr(int(x)+istatus_message, summary_block6,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM)
                stdscr.addstr(int(x)+istatus_message, summary_block7 ,"|    ",curses.A_DIM)
                stdscr.refresh()
                path_job=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()  + "/" + str(tagger)+ "/statlog_time_"+sample[x] + tagger + ".txt"
                ismerging=True
                
                while not os.path.exists(path_job):
                    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
                    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1430" + path_job ,curses.A_STANDOUT)
                    
                    stdscr.refresh()

                    if ismerging:
                        stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                        stdscr.addstr(2+list2+int(x), summary2_block1 ,"| MERGING OUTPUT ", curses.A_BLINK)
                        stdscr.refresh()
                        ismerging=False
                        
                    check_crash_stat=False
                    if check_crash_stat:
                        check_crashfile=an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + sample[x] +".txt"    
                        if not os.path.exists(check_crashfile):
                            continue
                        file_check_crashfile=open(check_crashfile,"r")
                        crash_in_job=False
                        crashlog=[]
                        for line in file_check_crashfile:
                            if " No such file or directory:" in line:
                                crash_in_job=True
                                crashlog.append(line)
                        file_check_crashfile.close()
                        if crash_in_job:
                            crash_log= an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"
                            if os.path.exists(crash_log):
                                file_crash=open(crash_log,"a")
                                for linex in  crashlog:
                                    file_crash.write(linex)
                                file_crash.close()
                            else:
                                file_crash=open(crash_log,"w")
                                for linex in  crashlog:
                                    file_crash.write(linex)
                                file_crash.close()
                            break

                    continue

                crash_log= an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"
                if os.path.exists(crash_log):
                    jobidcrash.append(int(x))
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| JOB CRASHED      ", curses.A_BLINK)
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir)  +GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                    fileoutputlist.append(outfilepath)

                    if "SKTreeMaker" in cycle:
                        outfilepath=GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)

                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +":###CRASH###: No OutputFile for " + sample[x])
                    crash_output.append(logpath)
                    crash_outputjob.append(jobid1)
                    stdscr.refresh()
                    if run_in_bkg:
                        del output_bkg[:]
                        for out_x in range(1,winx):
                            output_bkg.append(stdscr.instr(out_x, 0))
                            UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")
                else:
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block0 ,"| " + str(round(job_time,2)) + "[s]",curses.A_DIM)
                    stdscr.refresh()
                
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir) + GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                    fileoutputlist.append(outfilepath)
                    if "SKTreeMaker" in cycle:
                        outfilepath=GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,False)
                        

                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +": OutputFile for " + sample[x] + " = " + str(outfilepath))

                    filesize=0.
                    memoryusage_p=0.
                    memoryusage_v=0.
                    outputfile_size=0.
                    first_job_time=0.
                    last_job_time=0.
                    file_job=open(path_job,"r")
                    for line in file_job:
                        splitline  = line.split()
                        if len(splitline) < 2:
                            continue
                        if "job_time"  == splitline[0]:
                            first_job_time=float(splitline[1])
                        if "last_job_time"  == splitline[0]:
                            last_job_time=float(splitline[1])
                        if "outputfile_size" == splitline[0]:
                            outputfile_size=splitline[1]
                        if "memoryusage_p" ==  splitline[0]:
                            memoryusage_p=splitline[1]
                        if "memoryusage_v" ==  splitline[0]:
                            memoryusage_v=splitline[1]
                    file_job.close()
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| " + str(round(first_job_time,2)) + "-" +  str(round(last_job_time,2)) + "[s]     ",curses.A_DIM) 


                    if LargeMemory(memoryusage_p,large_memory_check):
                        output_warning.append("WARNING:: Physical memory of job " + sample[x] + "  is excess of " + str(large_memory_check) + " MB.")
                    if LargeMemory(memoryusage_v,large_memory_check):
                        output_warning.append("WARNING:: Virtual memory of job " + sample[x] + "  is excess of " + str(large_memory_check) + " MB.")

                    if isMC:
                        if LargePhysicalMemoryIncrease(memoryusage_p,sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Physical memory of job " + sample[x] + "  is " + RoundMemory(memoryusage_p) + " compared to previous jobs " + GetPhysicalMemoryUsage(sample[x], cycle,tagger,useskim))
                        if LargeVirtualMemoryIncrease(memoryusage_v,sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Virtual memory of job " + sample[x] + "  is " + RoundMemory(memoryusage_v) + " compared to previous jobs " + GetVirtualMemoryUsage(sample[x], cycle,tagger,useskim))
                        if LargeFileSize(outputfile_size,large_file_size):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " greater than " + str(large_file_size) + " MB")
                        if LargeFileSizeIncrease(outputfile_size,sample[x], cycle,tagger,useskim,file_increase_warning):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " compared to previous jobs " + GetFileSize(sample[x], cycle,tagger,useskim))
                        if TimeIncrease(first_job_time,sample[x], cycle,tagger,useskim,time_increase_warning):
                            output_warning.append("WARNING:: Job time per input file for " +  sample[x] +"  increased from " + str(first_job_time) + " compared to previous job time " + GetTime(sample[x], cycle,tagger,useskim))
                    else:
                        if LargePhysicalMemoryIncrease(memoryusage_p,channel + "_" +sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Physical memory of job " + sample[x] + "  is " + RoundMemory(memoryusage_p) + " compared to previous jobs " + GetPhysicalMemoryUsage(channel + "_" +sample[x], cycle,tagger,useskim))
                        if LargeVirtualMemoryIncrease(memoryusage_v,channel + "_" +sample[x], cycle,tagger,useskim):
                            output_warning.append("WARNING:: Virtual memory of job " + sample[x] + "  is " + RoundMemory(memoryusage_v) + " compared to previous jobs " + GetVirtualMemoryUsage(channel + "_" +sample[x], cycle,tagger,useskim))
                        if LargeFileSize(outputfile_size,large_file_size):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " greater than " + str(large_file_size) + " MB")
                        if LargeFileSizeIncrease(outputfile_size,channel + "_" +sample[x], cycle,tagger,useskim,file_increase_warning):
                            output_warning.append("WARNING:: Size of output rootfile for " + sample[x] + " is " + str(outputfile_size) + " compared to previous jobs " + GetFileSize(channel + "_" +sample[x], cycle,tagger,useskim))
                        if TimeIncrease(first_job_time,channel + "_" +sample[x], cycle,tagger,useskim,time_increase_warning):
                            output_warning.append("WARNING:: Job time per input file " + sample[x] +" increased from " + str(first_job_time) + " compared to previous job time " + GetTime(channel + "_" +sample[x], cycle,tagger,useskim))
               

                    stdscr.addstr(2+list2+int(x), summary2_block2 ,"| " + RoundMemory(memoryusage_p),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block3 ,"| " + RoundMemory(memoryusage_v),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block4 ,"| " + str(outputfile_size),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block5 ,"| ",curses.A_DIM)
                    stdscr.refresh()
                    if run_in_bkg:
                        del output_bkg[:]
                        for out_x in range(1,winx):
                            output_bkg.append(stdscr.instr(out_x, 0))
                            UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")
            stdscr.refresh()
            if run_in_bkg:
                del output_bkg[:]
                for out_x in range(1,winx):
                    output_bkg.append(stdscr.instr(out_x, 0))
                    UpdateOutput(output_bkg,an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt")


    stdscr.addstr(python_logger, summary_block2, " "*50  ,curses.A_STANDOUT)
    stdscr.addstr(python_logger, summary_block2, "SubmittionConfig.py L1578" ,curses.A_STANDOUT)
            
    stdscr.refresh()

#del output_bkg[:]

#for out_x in range(1,winx):
#    output_bkg.append(stdscr.instr(out_x, 0))


############## END OF JOB ################3
mypad_contents = []
for i in range(0, winx - remove_from_end):
    mypad_contents.append(stdscr.instr(i, 0))

redopad=False
if redopad:
    time.sleep(5.)
    for i in range(0, winx-remove_from_end):
        stdscr.addstr(i,0, mypad_contents[i])
        stdscr.refresh()
    time.sleep(5.)
if not run_in_bkg:    
    curses.echo()
    curses.nocbreak()
    curses.endwin()


iplotsample=-1
listofplots=[]

collist=[]
#fcol    870       
#zcol    64
#wcol    92
#wwcol   68
#zzcol   80
#wzcol   74
#ttvcol  88
#tcol    88 
#ttcol   97
collist.append(64) 
collist.append(92) 
collist.append(68) 

if quickdraw:
    plotallhist(fileoutputlist,an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/"+ str(tagger)  + "_hist.pdf", collist, tagger)
    if not DoSendEmail:
        os.system("display " + an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/"+ str(tagger)  + "_hist.pdf&")
    listofplots.append(an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/"+ str(tagger) + "_hist.pdf")

mergedoutfilepath=""
if not ismctmp:
    if runnptmp == "True":
        datadir=str(Finaloutputdir)
        datadir=datadir.replace("Fake/","")
        mergedoutfilepath=str(datadir) + GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,True)
    elif runcftmp == "True":
        datadir=str(Finaloutputdir)
        datadir=datadir.replace("CF/","")
        mergedoutfilepath=str(datadir) + GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,True)
    else:
        datadir=str(Finaloutputdir)
        datadir=datadir.replace("Data/","")
        mergedoutfilepath=str(datadir) + GetOutFileName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle,True)

        
#job_summary=[]
print "\n"
for i in range(0, winx-remove_from_end):
    if "Job Terminal Output:" in mypad_contents[i]:
        job_summary.append("*"*summary_block6+"\n")
        print "*"*summary_block6
        print  "Job Terminal Output:(will be deleted "+ future +")" + " " *20
        job_summary.append("Job Terminal Output:(will be deleted "+ future +")\n")
    elif  "Log Files:"  in mypad_contents[i]:
        print  "Log Files:(will be deleted "+ future_week +")" + " " *20
        job_summary.append("Log Files:(will be deleted "+ future_week +")\n")
    elif "Output Files:" in mypad_contents[i]:
        print mypad_contents[i]
        job_summary.append(mypad_contents[i]+"\n")
        if not ismctmp:
            if data_lumi== "ALL":
                print "Merged output = " +mergedoutfilepath
                job_summary.append("Merged output = " + mergedoutfilepath+"\n")
    else:
        print mypad_contents[i]
        job_summary.append(mypad_contents[i]+"\n")
    if "PostJob " in mypad_contents[i]:
        print "_"*summary2_block5    
        job_summary.append("_"*summary2_block5+"\n")
    elif "Cum.Process" in mypad_contents[i]:
        print "_"*summary2_block5
        job_summary.append("_"*summary2_block5+"\n")
    elif "Terminal" in mypad_contents[i]:
        print "_"*50
        job_summary.append("_"*50+"\n")
    elif "Job " in mypad_contents[i]:
        print "_"*summary_block6
        job_summary.append("_"*summary_block6+"\n")
    if "Log Files:"  in mypad_contents[i]:
        print "_"*40
        job_summary.append("_"*40+"\n")
    if "Output Files" in mypad_contents[i]:
        print "_"*40
        job_summary.append("_"*40+"\n")


time.sleep(10.)
path_stat_dir=path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()  + "/" + str(tagger)+ "/"
os.system("rm -r " + path_stat_dir)


end_job_time = time.time() - start_time

email_subject=""
if end_job_time > email_time_limit:
    DoSendEmail=True
    email_subject=email_subject+"Job time>600s "

if run_in_bkg:
    os.system("mv "+an_jobpre+"CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_bkg.txt "+an_jobpre+"CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/output_finished.txt")
if runningData:
    if tmp_filename == "None":
        MergeData(runnp,runcf,data_lumi, Finaloutputdir, catversion, useskim, cycle, channel, "",tagger,skflag)
    else:
        MergeData(runnp,runcf,data_lumi, Finaloutputdir, catversion, useskim, cycle, channel, tmp_filename,tagger,skflag)

if len(output_warning) > 0:
    print "\n"
    print "The job produced the following WARNING MESSAGES:"
    job_summary.append( "\n")
    job_summary.append("The job produced the following WARNING MESSAGES:")
    DoSendEmail=True
    email_subject=email_subject+"Job WARNING "
    for s in output_warning:
        print s
        job_summary.append(s + "\n")

if runningData and  not "SKTreeMaker" in cycle:

    file_read_counter = open("/data2/DATA//CAT_SKTreeOutput/"+os.getenv("USER")+"/Histdir" + tagger + "/Hist.txt","r")
    nhists=0
    for rc_line in file_read_counter:

        if  "=" in rc_line or "Path" in rc_line:
            if nhists==0:
                print "#"*40
                print rc_line
            
                print "List of cuts : Integral counter = "
                job_summary.append("List of cuts  : Integral counter = \n")
            else:
                job_summary.append("#"*40+ "\n")
                job_summary.append(rc_line+"\n")
                

            nhists=nhists+1
        print rc_line
        job_summary.append(rc_line + "\n")

    file_read_counter.close()    
    if nhists> 0:
        print "#"*40
        job_summary.append("#"*40+ "\n")

        
    hist_pre =  "/data2/DATA/CAT_SKTreeOutput/"
    if isKisti:
        hist_pre ="/cms/scratch/SNU/CATAnalyzer/"

    cffile_read_counter = open(hist_pre+os.getenv("USER")+"/Histdir" + tagger + "/CutFlow.txt","r")
    cfnhists=0
    for rc_line in cffile_read_counter:

        if  "Path" in rc_line:
            print rc_line
            job_summary.append(rc_line+"\n")

        if cfnhists==0:
            print "#"*40
            print "List of histograms/cutflow : Integral counter = "
            job_summary.append("#"*40+ "\n")
            job_summary.append("List of histograms/cutflow : Integral counter = \n")    
        cfnhists=cfnhists+1
        print rc_line
        job_summary.append(rc_line + "\n")
        
    cffile_read_counter.close()

elif  not "SKTreeMaker" in cycle:
                              
    cuts =[]
    print " "
    print "%%%%%%%%%%%%%%"*4
    file_read_counter = open("/data2/DATA/CAT_SKTreeOutput/"+os.getenv("USER")+"/Histdir" + tagger + "/"+sample[0]+"Hist.txt","r")
    for rc_line in file_read_counter:
        src_line = rc_line.split()
        if  "=" in rc_line :
            for sl in range(0,len(src_line)):
                if sl == 0:
                    cuts.append(src_line[sl])
    file_read_counter.close()
                          
    for c in cuts:
        print "Cut : " + str(c)
        job_summary.append("Cut : " + str(c)+"\n")
        samplename=[]
        sample_sum=[]
        sample_err=[]
        for hs in sample:
            hist_pre =  "/data2/DATA/CAT_SKTreeOutput/"
            if isKisti:
                hist_pre ="/cms/scratch/SNU/CATAnalyzer/"
            file_read_counter = open(hist_pre+os.getenv("USER")+"/Histdir" + tagger + "/"+hs+"Hist.txt","r")
            for rc_line in file_read_counter:
                cut_line=False
                src_line = rc_line.split()
                if  "=" in rc_line :
                    for sl in range(0,len(src_line)):
                        if sl == 0:
                            if src_line[sl] == c:
                                cut_line=True
                        if cut_line:
                            if sl == 2:
                                samplename.append(hs + ((40 - len(hs))*" ") )
                                sample_sum.append(float(src_line[sl]))
                            if sl == 3:
                                sample_err.append(float(src_line[sl]))
                    
        file_read_counter.close()

        print "#"*50
        job_summary.append("#"*50)
        total_sum=0.
        total_err=0.;

        if len(samplename) == len(sample_sum):
            for sn in range(0,len(samplename)):
                print samplename[sn] +  str(sample_sum[sn])
                job_summary.append(samplename[sn] +  str(sample_sum[sn]))
                total_sum=total_sum+float(sample_sum[sn])
                total_err = total_err + float(sample_err[sn])*float(sample_err[sn])
                if total_err > 0:
                    total_err = math.sqrt(total_err)
            print "-"*50    
            print "Total = " +(31)*" " +  str(total_sum) + "+/-" + str(total_err)
            print "-"*50    
            job_summary.append("-"*50+ "\n")
            job_summary.append("Total = "  +(31 *len("Total = "))*" " +  str(total_sum)+ "+/-$" + str(total_err)+"\n")
            job_summary.append("-"*50+ "\n")




crashlog_printout=[]


if len(crash_output) > 0:
    print "\n"
    print "%"*summary_block6
    print "%"*summary_block6
    print "Crash Job Error Message:"
    print "_"*summary_block6
    job_summary.append("\n")
    job_summary.append("%"*summary_block6+"\n")
    job_summary.append("%"*summary_block6+"\n")
    job_summary.append("Crash Job Error Message:\n")
    job_summary.append("_"*summary_block6+"\n")
    jobids_failed=""
    for x in jobidcrash:
        jobids_failed=jobids_failed+str(x+1)+","
    jobids_failed= jobids_failed[:-1]    
    print "Job IDs " + jobids_failed + " failed with following error:"
    print "#"*summary_block6
    job_summary.append("Job IDs " + jobids_failed + " failed with following error:\n")
    job_summary.append("#"*summary_block6+"\n")
    Crash_Printed=False
    for c in crash_output:
        if Crash_Printed:
            continue
        index_crash=0
        found_crash=False
        njobs_tried=-1
        while not found_crash:
            njobs_tried=njobs_tried+1
            errlogpath=c
            errlogpath=errlogpath.replace("Job_*","Job_"+str(njobs_tried+1) +".e"+str(int(crash_outputjob[index_crash])+njobs_tried))
            while not os.path.exists(errlogpath):
                index_crash=index_crash+1
                if index_crash == len(crash_outputjob):
                    break
                errlogpath=errlogpath.replace("Job_*","Job_" + str(njobs_tried+1) +".e"+str(int(crash_outputjob[index_crash])+njobs_tried))

            if not os.path.exists(errlogpath):
                found_crash=True
                print "Error in locating log file " + errlogpath + ". Could not print out error message from batch jobs"
                job_summary.append("Error in locating log file " + errlogpath + ". Could not print out error message from batch jobs\n")
            else:
                file_read_err = open(errlogpath,"r")
                for rline in file_read_err:
                    print rline    
                    job_summary.append(rline+"\n")
                    crashlog_printout.append(rline)
                    found_crash=True
                    Crash_Printed=True
        print "#"*summary_block6
        job_summary.append("#"*summary_block6+"\n")
    list_crash=CrashHelper(crashlog_printout)
    for linecrash in list_crash:
        job_summary.append(linecrash+"\n")
    
    print " "*summary_block6
    print "Run the following command to help debug job error: command runs crashed job in terminal instead of on batch machine."  
    print "sktree -a " + cycle + " -i " + sample[jobidcrash[0]] + " -s " + useskim + " -d DEBUG -n 1"
    job_summary.append(" "*summary_block6+"\n")
    job_summary.append("Run the following command to help debug job error: command runs crashed job in terminal instead of on batch machine.\n")
    job_summary.append("sktree -a " + cycle + " -i " + sample[jobidcrash[0]] + " -s " + useskim + " -d DEBUG -n 1 \n")
    email_subject=email_subject+"Job CRASH "
    DoSendEmail=True

if DoSendEmail:
    SendEmail(job_summary,tagger,email_subject,useremail,quickdraw, listofplots)

    
if os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tagger) :
    print "Removing tmp library directory for job ["+os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tagger+"]"
    os.system("rm -r "+ os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tagger)
        


##### CODE WRITEEN TO REMOVE DIRECTORY... THIS WILL BE KEPT UNLESS USER WISHES TO SET RDIR+TRUE

remdir=False

if remdir:
    njobs_in_total=0.
    path_clust_check2=an_jobpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/clusterjobs.txt"
    if not  "ui" in str(os.getenv("HOSTNAME")):
        os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
    else:
        os.system("condor_q " + os.getenv("USER") + " > " +  path_clust_check)

    file_clust_check2=open(path_clust_check2,"r")
    for sline in file_clust_check2:
        ssline = sline.split()
        if len(ssline) < 1:
            continue
        line=ssline[0]
        njobs_in_total=njobs_in_total+1.

    file_clust_check2.close()
    
    if njobs_in_total == 0 :    
        os.system("rm -r "+an_jobpre+"/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG*")
    else:
        os.system("rm -r "+an_jobpre+"CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) )


