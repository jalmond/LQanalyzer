###################################################                                                                                                                                                         
# set time related variables                                                                                                                                                                                
###################################################                                                                                                                                                         
import datetime
from datetime import timedelta

job_time=0.
now = datetime.datetime.now()
diff = datetime.timedelta(days=3)
diffweek = datetime.timedelta(days=7)
future = now + diff
future_week = now + diffweek
future=future.strftime("%m/%d/%Y")
future_week=future_week.strftime("%m/%d/%Y")


##################### ##########                                                                                                                                                                            
##### configure email warnings                                                                                                                                                                              
##################### ##########                                                                                                                                                                            

large_memory_check=800
large_file_size=100
file_increase_warning=2.
time_increase_warning=2.
######## set 10 process time for which email is sent                                                                                                                                                        
email_time_limit=600.


def SetUpParser():

    from optparse import OptionParser
    
    parser = OptionParser()
    parser.add_option("-p", "--period", dest="period", default="A",help="which data period or mc sample")
    parser.add_option("-s", "--stream", dest="stream", default="NULL", help="Which data channel- ee,or mumu?")
    parser.add_option("-j", "--jobs", dest="jobs", default=1, help="Name of Job")
    parser.add_option("-c", "--cycle", dest="cycle", default="Analyzer", help="which cycle")
    parser.add_option("-t", "--tree", dest="tree", default="ntuple/event", help="What is input tree name?")
    parser.add_option("-g", "--tmpfilename", dest="tmpfilename", default="", help="")
    parser.add_option("-o", "--logstep", dest="logstep", default=-1, help="How many events betwene log messages")
    parser.add_option("-d", "--data_lumi", dest="data_lumi", default="A", help="How much data are you running on/ needed to weight mc?")
    parser.add_option("-l", "--loglevel", dest="loglevel", default="INFO", help="Set Log output level")
    parser.add_option("-n", "--nevents", dest="nevents", default=-1, help="Set number of events to process")
    parser.add_option("-k", "--skipevent", dest="skipevent", default=-1, help="Set number of events to skip")
    parser.add_option("-a", "--datatype", dest="datatype", default="", help="Is data or mc?")
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
    parser.add_option("-G", "--runtau", dest="runtau", default="runtau", help="Run only tausmode for bkg?")
    parser.add_option("-Q", "--runcf", dest="runcf", default="runcf", help="Run fake mode for np bkg?")
    parser.add_option("-q", "--queue", dest="queue", default="", help="Which queue to use?")
    parser.add_option("-J", "--setnjobs", dest="setnjobs", default="False", help="user sets njobs?")
    parser.add_option("-v", "--catversion", dest="catversion", default="NULL", help="What cat version?")
    parser.add_option("-f", "--skflag", dest="skflag", default="NULL", help="add input flag?")
    parser.add_option("-b", "--usebatch", dest="usebatch", default="usebatch", help="Run in batch queue?")
    parser.add_option("-u", "--useremail", dest="useremail", default="", help="Set user email")
    parser.add_option("-B", "--bkg", dest="bkg", default="False", help="run in bkg")
    parser.add_option("-A","--drawhists",dest="drawhists",default="False", help="draw nothing")
    parser.add_option("-F","--submitallfiles",dest="submitallfiles",default="False", help="force n=1000")
    parser.add_option("-H","--sendmail",dest="sendmail",default="False", help="force n=1000")

    return parser
