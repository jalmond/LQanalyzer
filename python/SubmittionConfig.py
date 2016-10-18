#############################################################    
### configure submisstion of CATANALYZER Jobs                                                                                                                                  ##################################################################    
import os, getpass, sys,ROOT,time,curses,datetime
from functions import *
from datetime import timedelta
from optparse import OptionParser


def SendEmail():
    print "Sending mail"


def CrashHelper(defcrashlog):
    
    crashmessage=[]
    for cline in defcrashlog:
        if "vector::_M_range_check" in cline:
            crashmessage=CrashHelpMessage(0)
        if "Did not find"  in cline:
            crashmessage=CrashHelpMessage(1)        
        if "Muon collection not found" in cline:
            crashmessage=CrashHelpMessage(2)
        if "Electron collection not found" in cline:
            crashmessage=CrashHelpMessage(3)
        if "Jet collection not found" in cline:
            crashmessage=CrashHelpMessage(4)
    for mline in crashmessage:
        print mline        
    return

def CrashHelpMessage(crashtype):
    crashmessage=[]
    if crashtype == 0:
        crashmessage.append("Crash likedly caused by attempt to access an element of a vector that does not exist")
        crashmessage.append("Check in your code places where you access any vector using vec.at(x) or vec[x] that x < vec.size()")
        crashmessage.append("i.e.,")
        crashmessage.append("std::vector muons = GetMuons()")
        crashmessage.append("if(muons.at(0).Pt() > 20.) ...  --> this would cause crash for events with no muons. You must require muons vector size > 0"  )
        crashmessage.append("__________________________")
        crashmessage.append("if(muons.size() > 0){ ")
        crashmessage.append("   if(muons.at(0).Pt() > 20.) ... This will not crash")
        return crashmessage
    if crashtype == 1: 
        crashmessage.append("Crash caused due to missing file. Check that file is located in $LQANALYZER_FILE_DIR directory (use ls $LQANALYZER_FILE_DIR).")
        crashmessage.append("If file is located in $LQANALYZER_FILE_DIR do:")
        crashmessage.append("cp $LQANALYZER_FILE_DIR/file  $FILEDIR")
        crashmessage.append("If file is not located in $LQANALYZER_FILE_DIR email jalmond@cern.ch with crash message")
    if crashtype == 2:
        crashmessage.append("Crash caused due to Error in GetMuons input string")
    if crashtype == 3:
        crashmessage.append("Crash caused due to Error in GetElectrons input string")
    if crashtype == 4:
        crashmessage.append("Crash caused due to Error in GetJets input string")

    return crashmessage

def GetPartualName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle):

    if defskim == "SKTree_NoSkim":
        defskim ="NoCut"
    elif defskim == "SKTree_LeptonSkim":
        defskim ="Lepton"
    elif defskim == "SKTree_DiLepSkim":
        defskim="DiLep"
    elif defskim == "SKTree_TriLepSkim":
        defskim="TriLep"
    
    output_catversion=str(os.getenv("CATVERSION"))
                                              
    if not ismc:
        if defskim == "Lepton":
            defchannel="SK" + defchannel
        else:
            if defskim == "NoCut":
                defchannel="SK" + defchannel + "_nocut"
            else:
                if defskim == "DiLep":
                    defchannel="SK" + defchannel + "_dilep"
                else:
                    if defskim == "TriLep":
                        defchannel="SK" + defchannel + "_trilep"
    else:
        if defskim == "Lepton":
            defsample="SK" + defsample
        else:
            if defskim == "NoCut":
                defsample="SK" + defsample + "_nocut"
            else:
                if defskim == "DiLep":
                    defsample="SK" + defsample + "_dilep"
                else:
                    if defskim == "TriLep":
                        defsample="SK" + defsample + "_trilep"

    outsamplename=""                        
    if ismc:
        outsamplename=defsample
    else:
        outsamplename="period"+defsample

    if defrunnp == "True":
        outsamplename = "nonprompt_" + outsamplename
    if defruncf == "True":
        outsamplename = "chargeflip_" + outsamplename
    if not ismc:
        outsamplename = outsamplename +  "_" + defchannel
        outsamplename = outsamplename + "_cat_" + str(output_catversion)
    else:
        outsamplename = outsamplename + "_cat_"+ str(output_catversion)

    if  "SKTreeMaker" in defcycle:
        outsamplename = outsamplename +  str(os.getenv("CATTAG"))

    return outsamplename
                        

def GetLogFilePath(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle):
    tmpname= GetPartualName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle)
    outlogname = str(os.getenv("LQANALYZER_LOG_PATH")) + "/" + tmpname + "/" + tmpname+"_Job_*"
    return outlogname

def GetOutFilName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle):
    tmpname= GetPartualName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle)
    outsamplename=""
    if ismc:
        outsamplename=  defcycle +"_"+tmpname + ".root"
    elif defrunnp == "True":
        output_catversion=str(os.getenv("CATVERSION"))
        skimtag=""
        if defskim == "DiLep":
            skimtag= "_dilep"
        elif defskim == "TriLep":
            skimtag= "_trilep"
        outsamplename=  defcycle + "_" + defchannel + "SKnonprompt_"+skimtag+ "_cat_" +  str(output_catversion)+ ".root"
    elif defruncf == "True":
        output_catversion=str(os.getenv("CATVERSION"))
        skimtag=""
        if defskim == "DiLep":
            skimtag= "_dilep"
        elif defskim == "TriLep":
            skimtag= "_trilep"
        outsamplename=  defcycle + "_" + defchannel + "SKchargeflip_"+skimtag+ "_cat_" +  str(output_catversion)+ ".root"
    
    else:
        output_catversion=str(os.getenv("CATVERSION"))
        outsamplename=  defcycle +"_data_"+ defchannel + "_cat_" +  str(output_catversion)+ ".root"
    return outsamplename    

def RoundMemory(mem):
    if not "MB" in str(mem):
        return str(mem)
    smem=str(mem)
    string_length= len(smem)
    float_only_mem= smem[:-2]
    unit_only_mem=  smem[(int(string_length)-2):]
    
    rounded_float= str(round(float(float_only_mem),2)) + unit_only_mem
    return rounded_float
    

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

#curses.resizeterm

job_time=0.

now = datetime.datetime.now()
diff = datetime.timedelta(days=7)
future = now + diff
future=future.strftime("%m/%d/%Y")


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

skim_print=useskim
if useskim == "SKTree_LeptonSkim":
    skim_print ="Lepton   "
elif useskim == "SKTree_DiLepSkim":
    skim_print="DiLep. "
elif useskim == "SKTree_TriLepSkim":
    skim_print="TriLep. "


sample = sample.replace(":", " ")
sample = sample.replace("!!", " ")
sample = sample.split()
istatus_message=2
winx = 5*len(sample) + 22 +  istatus_message
winy = 175

crash_output=[]
crash_outputjob=[]

start_time = time.time()

screen = curses.initscr()

#screen.border(0)
screen.refresh()
stdscr = curses.newwin(winx, winy)
curses.noecho()
curses.cbreak()

box_shift=0
summary_block0=4 + box_shift
summary_block1=summary_block0+ len(options.cycle) + 5
summary_block2=summary_block1+20
summary_block3=summary_block2+10
summary_block4=summary_block3+15
summary_block5=summary_block4+27
summary_block6=summary_block5+60

stdscr.addstr(0, box_shift,  "Job Summary:",curses.A_UNDERLINE)
stdscr.addstr(1, box_shift, "Job ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block0, "| Code Name                   ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block1, "| Sample Name                   ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block2, "| Skim    ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block3, "| Status                  ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block4, "| Cluster ID Range | njobs  ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block5, "| Cluster Progess                                            ",curses.A_STANDOUT)
stdscr.addstr(1, summary_block6, "|" ,curses.A_STANDOUT)
stdscr.refresh()


#### list 2 is more technical properties                                                                                                                                                                                                                                        
summary2_block0=4+box_shift
summary2_block1=summary2_block0+20
summary2_block2=summary2_block1+20
summary2_block3=summary2_block2+20
summary2_block4=summary2_block3+20
summary2_block5=summary2_block4+20


list2= istatus_message + 6 + len(sample)
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


remove_from_end= 3 

stdscr.addstr(list4,box_shift,  "Job Status (Summary of latest background process):" ,curses.A_UNDERLINE)
#### make a random number for the job ID. This will help make a directory to work in

stdscr.addstr(list3, box_shift,  "Job Terminal Output: (will be deleted "+ future +")" ,curses.A_UNDERLINE)
stdscr.addstr(list3b, box_shift,  "Log Files: (will be deleted "+ future +")" ,curses.A_UNDERLINE)
stdscr.addstr(list3c, box_shift,  "Output Files:" ,curses.A_UNDERLINE)

import random
job_tagger=random.random()

#### make working directorr
if not os.path.exists("/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)):
    os.system("mkdir " + "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))
else:
    print "Work directory " + "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger) + " already exists:"
    print "Removing old directory"
    os.system("rm " + "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))
    os.system("mkdir " + "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  +"/CLUSTERLOG" +str(tagger))

### Make directory for job stats
statdir="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ os.getenv("USER")
if not os.path.exists(statdir):
    os.system("mkdir " +statdir)

if channel == "":
    channel = NULL

#http://stackoverflow.com/questions/14300770/how-to-noutrefresh-the-multi-line-output-dynamically
### split sample and check cluster queue

#"/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/" + str(tagger)+ "/jobid.txt"
samples_inbackground=[]
samples_complete=[]
jobidcrash=[]
isample=-1

useskimtmp=""
ismctmp=  True
sampletmp=""
runnptmp=""
runcftmp=""
channeltmp=""

#### Loop over all samples in job
for s in sample:
    isample=isample+1
    
    isMC = len(s) > 1
    
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

        useskimtmp=useskim
        ismctmp=  len(sample[x])>1
        sampletmp=sample[x]
        runnptmp=runnp
        runcftmp=runcf
        channeltmp=channel

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


            if nrun_per == 0.:
                stdscr.addstr(int(x)+istatus_message, box_shift,  str(int(x+1)), curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block0, "| " +  cycle, curses.A_NORMAL )
                if isMC:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + sample[x], curses.A_NORMAL )
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block1, "| " + channel+"_"+sample[x], curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block2, "| " + skim_print, curses.A_NORMAL )
                stdscr.addstr(int(x)+istatus_message, summary_block3,"| Submitted " , curses.A_NORMAL) 
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
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2) + "    | " + str(1+int(jobid2)-int(jobid1)) , curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block5,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block6 ,"|    ",curses.A_BOLD)    
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
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + "   | " + str(1+int(jobid2)-int(jobid1)), curses.A_DIM)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block5,"| "  , curses.A_DIM)
 
                stdscr.addstr(int(x)+istatus_message, summary_block5,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM) 


                path_job="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/statlog_time_"+sample[x] + tagger + ".txt"
                if not os.path.exists(path_job):
                     stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                     stdscr.addstr(2+list2+int(x), summary2_block1 ,"| MERGING OUTPUT ", curses.A_BLINK)
                     continue

                crash_log= "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"

                if os.path.exists(crash_log):
                    jobidcrash.append(int(x))
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| JOB CRASHED    ", curses.A_BLINK)
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir)  +GetOutFilName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +":###CRASH###: No OutputFile for " + sample[x])
                    crash_output.append( logpath)
                    crash_outputjob.append(str(jobid1))

                else:
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block0 ,"| " + str(round(job_time,2)) + "[s]",curses.A_DIM) 
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
                    stdscr.addstr(2+list2+int(x), summary2_block2 ,"| " + RoundMemory(memoryusage_p),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block3 ,"| " + RoundMemory(memoryusage_v),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block4 ,"| " + str(outputfile_size),curses.A_DIM) 
                    stdscr.addstr(2+list2+int(x), summary2_block5 ,"| ",curses.A_DIM)
                    stdscr.addstr(int(x)+istatus_message, summary_block5 ,"|    ",curses.A_DIM) 

                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir)  +GetOutFilName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +": OutputFile for " + sample[x] + " = " + str(outfilepath))

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

    logfile="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/statlog_"+ s + tagger + ".txt"
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
    stdscr.addstr(list4+1, box_shift,  "Initialise:: sample " + s +  blankbuffer)
    stdscr.refresh()
    while checkqueue:
        os.system(command1)
        if not os.path.exists("/data2/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger):
            stdscr.addstr(list4+1, box_shift,  "Queue busy.. please wait")
            stdscr.refresh()
            #time.sleep(5.)
            
        else:
            os.system("rm -r /data2/CAT_SKTreeOutput/" + os.getenv("USER") +"/"+tagger)
            stdscr.addstr(list4+1, box_shift,  "Submitting sample to queue  " + s)
            stdscr.refresh()
            
            checkqueue=False
            if not os.path.exists("/data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger):
                os.system("mkdir  /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) +"/" + tagger)

            stdscr.addstr(list3 + 1+int(isample), box_shift,  "Running " + s + " in background: terminal output sent to /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" +  str(tagger) + "/" + tagger + "/" + s + ".txt")
            stdscr.refresh()
            stdscr.addstr(int(isample)+istatus_message, box_shift,  str(int(isample+1)) )
            stdscr.addstr(int(isample)+istatus_message, summary_block0,  "| " + cycle  )
            stdscr.addstr(int(isample)+istatus_message, summary_block1,  "| " + s  )
            stdscr.addstr(int(isample)+istatus_message, summary_block2,  "| " + skim_print  )
            stdscr.addstr(int(isample)+istatus_message, summary_block3,"| In Queue " , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_NORMAL)
            stdscr.addstr(int(isample)+istatus_message, summary_block5,"| Running[---------]   Complete[----------]   ")
            stdscr.addstr(int(isample)+istatus_message, summary_block6,"|    ")
            os.system(command2_background)
            samples_inbackground.append(s)


stdscr.refresh()
StillRunning=True
while StillRunning:
    StillRunning=False
    for x in range(0, len(sample)):
        sample_complete=False
        for finsamp in samples_complete:
            if sample[x] == finsamp:
                sample_complete=True
        if sample_complete:
            continue
        ## Need to sleep here so that cursor is not moving on screen too fast
        time.sleep(2.)
        
        useskimtmp=useskim
        ismctmp=  len(sample[x])>1
        sampletmp=sample[x]
        runnptmp=runnp
        runcftmp=runcf
        channeltmp=channel

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
            os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
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
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + "    | " + str(1+int(jobid2)-int(jobid1)), curses.A_BOLD)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|" , curses.A_BOLD)
                stdscr.addstr(int(x)+istatus_message, summary_block5,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_BOLD)
                
                stdscr.addstr(int(x)+istatus_message, summary_block6 ,"|    ",curses.A_BOLD)
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
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"| " + str(jobid1) + "-" + str(jobid2)  + "    | " + str(1+int(jobid2)-int(jobid1)), curses.A_DIM)
                else:
                    stdscr.addstr(int(x)+istatus_message, summary_block4,"|" + " "*18 + "|"  , curses.A_DIM)

                stdscr.addstr(int(x)+istatus_message, summary_block5,  "| Running   " + nscreen_run + " " + str(100*nrun_per)+ "%  Complete" + nscreen_fin + " " + str(100*nfin_per) + "%",curses.A_DIM)
                stdscr.addstr(int(x)+istatus_message, summary_block6 ,"|    ",curses.A_DIM)
                path_job="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/statlog_time_"+sample[x] + tagger + ".txt"
                ismerging=True
                while not os.path.exists(path_job):
                    if ismerging:
                        stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                        stdscr.addstr(2+list2+int(x), summary2_block1 ,"| MERGING OUTPUT ", curses.A_BLINK)
                        stdscr.refresh()
                        ismerging=False
                    continue

                crash_log= "/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + sample[x] +"_crash/crashlog.txt"
                if os.path.exists(crash_log):
                    jobidcrash.append(int(x))
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block1 ,"| JOB CRASHED      ", curses.A_BLINK)
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir)  +GetOutFilName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    stdscr.addstr(list3b + 1+int(x), box_shift,  str(1+int(x)) +": Log files for " + sample[x] + " found at " + str(logpath))
                    stdscr.addstr(list3c + 1+int(x), box_shift,   str(1+int(x)) +":###CRASH###: No OutputFile for " + sample[x])
                    crash_output.append(logpath)
                    crash_outputjob.append(jobid1)

                else:
                    stdscr.addstr(2+list2+int(x), box_shift , str(int(x+1)),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block0 ,"| " + str(round(job_time,2)) + "[s]",curses.A_DIM)
                    stdscr.refresh()
                
                    logpath=GetLogFilePath(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
                    outfilepath=str(Finaloutputdir) + GetOutFilName(useskimtmp, ismctmp , sampletmp, runnptmp, runcftmp, channeltmp , cycle)
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
                    stdscr.addstr(2+list2+int(x), summary2_block2 ,"| " + RoundMemory(memoryusage_p),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block3 ,"| " + RoundMemory(memoryusage_v),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block4 ,"| " + str(outputfile_size),curses.A_DIM)
                    stdscr.addstr(2+list2+int(x), summary2_block5 ,"| ",curses.A_DIM)


            stdscr.refresh()


            
    stdscr.refresh()


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
    
curses.echo()
curses.nocbreak()
curses.endwin()

print "\n"
for i in range(0, winx-remove_from_end):
    if "Job Terminal Output:" in mypad_contents[i]:
        print "*"*summary_block6
        print  "Job Terminal Output:(will be deleted "+ future +")" + " " *20
    elif  "Log Files:"  in mypad_contents[i]:
        print  "Log Files:(will be deleted "+ future +")" + " " *20
    else:
        print mypad_contents[i]
    if "PostJob " in mypad_contents[i]:
        print "_"*summary2_block5    
    elif "Cum.Process" in mypad_contents[i]:
        print "_"*summary2_block5
    elif "Terminal" in mypad_contents[i]:
        print "_"*40
    elif "Job " in mypad_contents[i]:
        print "_"*summary_block6
    if "Log Files:"  in mypad_contents[i]:
        print "_"*40
    if "Output Files" in mypad_contents[i]:
        print "_"*40

for s in sample:
    path_job="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/statlog_time_" +s + tagger + ".txt"
    os.system("rm " + path_job)


crashlog_printout=[]


if len(crash_output) > 0:
    print "\n"
    print "%"*summary_block6
    print "%"*summary_block6
    print "Crash Job Error Message:"
    print "_"*summary_block6
    jobids_failed=""
    for x in jobidcrash:
        jobids_failed=jobids_failed+str(x+1)+","
    jobids_failed= jobids_failed[:-1]    
    print "Job IDs " + jobids_failed + " failed with following error:"
    print "#"*summary_block6

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
            else:
                file_read_err = open(errlogpath,"r")
                for rline in file_read_err:
                    print rline    
                    crashlog_printout.append(rline)
                    found_crash=True
                    Crash_Printed=True
        print "#"*summary_block6

    CrashHelper(crashlog_printout)
        
    SendEmail()
    print " "*summary_block6
    print "Run the following command to help debug job error: command runs crashed job in terminal instead of on batch machine."  
    print "sktree -a " + cycle + " -i " + sample[jobidcrash[0]] + " -s " + useskim + " -d DEBUG -n 1"



##### CODE WRITEEN TO REMOVE DIRECTORY... THIS WILL BE KEPT UNLESS USER WISHES TO SET RDIR+TRUE

remdir=False

if remdir:
    njobs_in_total=0.
    path_clust_check2="/data2/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/clusterjobs.txt"
    os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check2)
    file_clust_check2=open(path_clust_check2,"r")
    for sline in file_clust_check2:
        ssline = sline.split()
        if len(ssline) < 1:
            continue
        line=ssline[0]
        njobs_in_total=njobs_in_total+1.

    file_clust_check2.close()
    
    if njobs_in_total == 0 :    
        os.system("rm -r /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG*")
    else:
        os.system("rm -r /data2/CAT_SKTreeOutput/"+os.getenv("USER")+"/CLUSTERLOG" + str(tagger) )

