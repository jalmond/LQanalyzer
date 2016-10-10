###################################################################    
### configure submisstion of CATANALYZER Jobs                                                                                                                                  ###################################################################    

import os, getpass, sys,ROOT,time
from functions import *

import curses



from optparse import OptionParser

#Import parser to get options                                                                                                                                                  
parser = OptionParser()
parser.add_option("-p", "--period", dest="period", default="A",help="which data period or mc sample")
parser.add_option("-s", "--stream", dest="stream", default="NULL", help="Which data channel- ee,or mumu?")
parser.add_option("-j", "--jobs", dest="jobs", default=1, help="Name of Job")
parser.add_option("-c", "--cycle", dest="cycle", default="Analyzer", help="which cycle")
parser.add_option("-t", "--tree", dest="tree", default="ntuple/event", help="What is input tree name?")
parser.add_option("-o", "--logstep", dest="logstep", default=-1, help="How many events betwene log messages")
parser.add_option("-d", "--data_lumi", dest="data_lumi", default="A", help="How much data are you running on/ needed to weight mc?")
parser.add_option("-l", "--loglevel", dest="loglevel", default="INFO", help="Set Log output level")
parser.add_option("-n", "--nevents", dest="nevents", default=-1, help="Set number of events to process")
parser.add_option("-k", "--skipevent", dest="skipevent", default=-1, help="Set number of events to skip")
parser.add_option("-a", "--datatype", dest="datatype", default="mc", help="Is data or mc?")
parser.add_option("-e", "--totalev", dest="totalev", default=-1, help="How many events in sample?")
parser.add_option("-x", "--xsec", dest="xsec", default=-1., help="How many events in sample?")
parser.add_option("-X", "--tagger", dest="tagger", default="123", help="random number string?")
parser.add_option("-T", "--targetlumi", dest="targetlumi", default=-1., help="How many events in sample?")
parser.add_option("-E", "--efflumi", dest="efflumi", default=-1., help="How many events in sample?")
parser.add_option("-O", "--outputdir", dest="outputdir", default="${LQANALYZER_DIR}/data/output/", help="Where do you like output to go?")
parser.add_option("-w", "--remove", dest="remove", default=True, help="Remove the work space?")
parser.add_option("-S", "--skinput", dest="skinput", default=True, help="Use SKTree as input?")
parser.add_option("-R", "--runevent", dest="runevent", default=True, help="Run Specific Event?")
parser.add_option("-N", "--useCATv742ntuples", dest="useCATv742ntuples", default=True, help="' to run on these samples")
parser.add_option("-L", "--LibList", dest="LibList", default="NULL", help="Add extra lib files to load")
parser.add_option("-D", "--debug", dest="debug", default=False, help="Run submit script in debug mode?")
parser.add_option("-m", "--useskim", dest="useskim", default="Lepton", help="Run submit script in debug mode?")
parser.add_option("-P", "--runnp", dest="runnp", default="runnp", help="Run fake mode for np bkg?")
parser.add_option("-Q", "--runcf", dest="runcf", default="runcf", help="Run fake mode for np bkg?")
parser.add_option("-v", "--catversion", dest="catversion", default="NULL", help="What cat version?")
parser.add_option("-f", "--skflag", dest="skflag", default="NULL", help="add input flag?")
parser.add_option("-b", "--usebatch", dest="usebatch", default="usebatch", help="Run in batch queue?")

stdscr = curses.initscr()
curses.noecho()
curses.cbreak()

start_time = time.time()
job_time=0.


###################################################                                                                                                                            
#set the local variables using options                                                                                                                                         
###################################################                                                                                                                            
(options, args) = parser.parse_args()
number_of_cores = int(options.jobs)
sample = options.period
channel = options.stream
cycle = options.cycle
logstep = int(options.logstep)
loglevel = options.loglevel
runnp = options.runnp
runcf = options.runcf
tagger= options.tagger
### THESE ARE OPTIONS THAT CAN BE INCLUDED but not in example                                                                                                                  
tree = options.tree
number_of_events_per_job= int(options.nevents)
skipev = int(options.skipevent)
dataType = options.datatype
totalev = int(options.totalev)
xsec = float(options.xsec)
tar_lumi = float(options.targetlumi)
eff_lumi = float(options.efflumi)
data_lumi = options.data_lumi
catversion = options.catversion
Finaloutputdir = options.outputdir
remove_workspace=options.remove
useskinput=options.skinput
runevent= options.runevent
useCATv742ntuples = options.useCATv742ntuples
tmplist_of_extra_lib=options.LibList
DEBUG = options.debug
useskim = options.useskim
skflag = options.skflag
usebatch =options.usebatch



summary_block0=len(options.cycle) + 5
summary_block1=summary_block0+30
summary_block2=summary_block1+20
summary_block3=summary_block2+20
summary_block4=summary_block3+60
summary_block5=summary_block4+30

stdscr.addstr(0, 0,  "Job Summary:",curses.A_UNDERLINE)
stdscr.addstr(1, 0, "Code Name                    ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block0, "Sample Name                    ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block1, "| Status             ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block2, "| Cluster ID Range   ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block3, "| Cluster Progess                                           ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block4, "| Processing Time              ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block5, "|" ,curses.A_STANDOUT)

stdscr.refresh()
istatus_message=2

sample = sample.replace(":", " ")
sample = sample.replace("!!", " ")
sample = sample.split()

stdscr.addstr(len(sample)+4, 0,  "Job Status (Summary of latest background process):" ,curses.A_UNDERLINE)
#### make a random number for the job ID. This will help make a directory to work in

stdscr.addstr(len(sample)+11, 0,  "Job Screens:" ,curses.A_UNDERLINE)

import random
job_tagger=random.random()

#### make working directorr
if not os.path.exists("/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)):
    os.system("mkdir " + "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))

### Make directory for job stats
statdir="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ os.getenv("USER")
if not os.path.exists(statdir):
    os.system("mkdir " +statdir)

if channel == "":
    channel = NULL

#http://stackoverflow.com/questions/14300770/how-to-refresh-the-multi-line-output-dynamically
### split sample and check cluster queue

#"/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/" + str(tagger)+ "/jobid.txt"
samples_inbackground=[]
samples_complete=[]
isample=-1

#### Loop over all samples in job
for s in sample:
    isample=isample+1

    #### if sample is submitted this for loop will check job process on cluster and update the screen/terminal
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

        ### if sample has been submitted to cluster backgroundsamples will be True        
        if backgroundsamples:
            #### in case the job id file is not yet filled add while condition
            jobid_exists=True
            while jobid_exists:        
                path_job_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt" 
                if  os.path.exists(path_job_check):
                    jobid_exists=False
            jobid1=0
            jobid2=0
            file_job_check=open(path_job_check ,"r")
            #### check status of job on cluster
            njobs_finished=0.
            nrunning=0.
            nqueue=0.
            njobs_in_total=0.  ### should equal three above
            path_clust_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            os.system("qstat -u '*'> " +  path_clust_check)
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
                ### line == job ID
                ijob=ijob+1.
                njobs_in_total=njobs_in_total+1.
                file_clust_check=open(path_clust_check,"r")
                job_inqueue=False
                for cline in file_clust_check:
                    splitline  = cline.split()
                    if len(splitline) < 6:
                        continue
                    if not os.getenv("USER")  in cline:
                        continue
                    if line == splitline[0]:
                        job_inqueue=True
                        if splitline[4] == "r":
                            nrunning = nrunning + 1.
                        else:
                            nqueue = nqueue + 1.
                if not job_inqueue:
                    njobs_finished=njobs_finished+1.
                file_clust_check.close()
            path_clust_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
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


            #stdscr.addstr(int(x)+istatus_message, 0,  sample[x] + " Running" + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
            if nrun_per == 0.:
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block0, sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Submitted " , curses.A_NORMAL) 
            else:
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x], curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Running    " , curses.A_BLINK) 
                if not jobid1 == 0:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| " + str(jobid1) + "--" + str(jobid2) , curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| "  , curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block3,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block4 ,"|    ",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block5 ,"|    ",curses.A_BOLD)    
            if nfin_per == 1.:
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x], curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Complete " , curses.A_DIM) 
                job_time = time.time() - start_time
                if not jobid1 == 0:    
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| " + str(jobid1) + "--" + str(jobid2) , curses.A_DIM)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| "  , curses.A_DIM)
 
                stdscr.addstr(int(x)+istatus_message, summary_block3,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM) 
                stdscr.addstr(int(x)+istatus_message, summary_block4 ,"|" + str(round(job_time,2)) + "[s]",curses.A_DIM) 
                stdscr.addstr(int(x)+istatus_message, summary_block5 ,"|    ",curses.A_DIM) 
        else:
            stdscr.addstr(int(x)+istatus_message, 0,  cycle )
            stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x] )
            stdscr.addstr(int(x)+istatus_message, summary_block1,"| In Queue " )
            stdscr.addstr(int(x)+istatus_message, summary_block2,"| " )
            stdscr.addstr(int(x)+istatus_message, summary_block3,"|    ")
            stdscr.addstr(int(x)+istatus_message, summary_block4,"|    ")
            stdscr.addstr(int(x)+istatus_message, summary_block5,"|    ")


    logfile="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/statlog" + tagger + ".txt"
    logfile_time="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ os.getenv("USER")+"/statlog_time"+tagger + ".txt"
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
    blankbuffer = "         "
    command1= "python  " +  os.getenv("LQANALYZER_DIR")+  "/python/CATConfig.py -p " + s + "  -s " + str(channel) + "  -j " + str(number_of_cores) + " -c  " + str(cycle)+ " -o " + str(logstep)+ "  -d " + str(data_lumi) + " -O " + str(Finaloutputdir) + "  -w " + str(remove_workspace)+ " -l  " + str(loglevel) + "  -k " + str(skipev) + "  -n " + str(number_of_events_per_job) + "  -e " + str(totalev) + "  -x " + str(xsec) + "  -T " + str(tar_lumi) + " -E " + str(eff_lumi) + "  -S " + str(useskinput) + " -R " + str(runevent)+ "  -N " + str(useCATv742ntuples) + " -L " + str(tmplist_of_extra_lib) + " -D " + str(DEBUG) + " -m " + str(useskim) + " -P  " + str(runnp) + " -Q " + str(runcf) + " -v " + str(catversion) + " -f " + str(skflag) + " -b " + str(usebatch) + "  -X " + str(tagger)
    command2=command1
    command2 = command2.replace("CATConfig.py", "localsubmit.py")
    command2_background=command2 + "&>  /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger + "/" + s+".txt&"
    checkqueue=True
    while checkqueue:
        stdscr.addstr(len(sample)+5, 0,  "Initialise:: sample " + s +  blankbuffer)
        stdscr.refresh()
        os.system(command1)
        if not os.path.exists("/data2/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger):
            stdscr.addstr(len(sample)+5, 0,  "Queue busy.. please wait")
            stdscr.refresh()
            #os.system(command2)        
        else:
            os.system("rm -r /data2/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger)
            stdscr.addstr(len(sample)+5, 0,  "Submitting sample to queue  " + s)
            stdscr.refresh()
            
            checkqueue=False
            if not os.path.exists("/data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger):
                os.system("mkdir  /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger)
            stdscr.addstr(len(sample)+12 + int(isample), 0,  "Running " + s + " in background: terminal output sent to /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" +  str(tagger) + "/" + tagger + "/" + s + ".txt")
            stdscr.refresh()
            stdscr.addstr(int(isample)+istatus_message, 0,  cycle  )
            stdscr.addstr(int(isample)+istatus_message, summary_block0,  s  )
            stdscr.addstr(int(isample)+istatus_message, summary_block1,"| In Queue " , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block2,"| "  , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block3,"| Running[---------]   Complete[----------]   ")
            stdscr.addstr(int(isample)+istatus_message, summary_block4,"|    ")
            stdscr.addstr(int(isample)+istatus_message, summary_block5,"|    ")

            #stdscr.addstr(int(isample)+istatus_message, 0,  s + " Running[---------]   Complete[----------]" ,curses.A_BOLD)
            os.system(command2_background)
            samples_inbackground.append(s)

stdscr.refresh()
StillRunning=True
while StillRunning:
    StillRunning=False
    for x in range(0, len(sample)):
        time.sleep(1.)
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
        if backgroundsamples:
            jobid_exists=True
            while jobid_exists:
                path_job_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "jobid.txt"
                if  os.path.exists(path_job_check):
                    jobid_exists=False

            file_job_check=open(path_job_check ,"r")
            njobs_finished=0.
            nrunning=0.
            nqueue=0.
            njobs_in_total=0.
            path_clust_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            os.system("qstat -u '*'> " +  path_clust_check)
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
                ijob=ijob+1.
                njobs_in_total=njobs_in_total+1.
                file_clust_check=open(path_clust_check,"r")
                job_in_queue=False
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
            path_clust_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] + "clust.txt"
            os.system("rm " + path_clust_check)
        

            if njobs_in_total         == 0.:
                continue
            file_job_check.close()
            stdscr.addstr(40,0, "Current Job status",curses.A_UNDERLINE)
            stdscr.addstr(42, 0,  sample[x]+ "          complete jobs=    " + str(njobs_finished) + "             ")
            stdscr.addstr(41, 0,  sample[x]+ "          total jobs=    " + str(njobs_in_total) + "             ")
            stdscr.addstr(43, 0,  sample[x]+ "          running jobs=    " + str(nrunning) + "             ")
            stdscr.refresh()
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
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Submitted " , curses.A_NORMAL)
            else:
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x], curses.A_BOLD )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Running    " , curses.A_BLINK)
                if not jobid1 == 0:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| " + str(jobid1) + "--" + str(jobid2) , curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| "  , curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block3,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block4 ,"|    ",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block5 ,"|    ",curses.A_BOLD)
            if nfin_per == 1.:
                stdscr.addstr(int(x)+istatus_message, 0,  cycle, curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block0,  sample[x], curses.A_DIM )
                stdscr.addstr(int(x)+istatus_message, summary_block1,"| Complete " , curses.A_DIM)
                job_time = time.time() - start_time
                if not jobid1 == 0:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| " + str(jobid1) + "--" + str(jobid2) , curses.A_DIM)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block2,"| "  , curses.A_DIM)

                stdscr.addstr(int(x)+istatus_message, summary_block3,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM)
                stdscr.addstr(int(x)+istatus_message, summary_block4 ,"| " + str(round(job_time,2)) + "[s]    ",curses.A_DIM)
                stdscr.addstr(int(x)+istatus_message, summary_block5 ,"|    ",curses.A_DIM)


            #stdscr.addstr(int(x)+istatus_message, 0,  sample[x] + " Running" + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
            stdscr.refresh()
            time.sleep(1.)
            #path_clust_check="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/" + str(tagger)+ "/" + sample[x] + "clust.txt"
            #os.system("rm " + path_clust_check)

    stdscr.refresh()


curses.echo()
curses.nocbreak()
curses.endwin()
#os.system("rm -r /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/" + tagger )
os.system("rm -r /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) )
