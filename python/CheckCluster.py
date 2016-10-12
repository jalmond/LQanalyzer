import os,sys,getpass

if not os.path.exists("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser()):
    os.system("mkdir  /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser())

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")
parser.add_option("-s", "--s", dest="s", default="123",help="tag")

(options, args) = parser.parse_args()
filetag=options.x
ssample=options.s
    

path_job="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/Cluster_" + ssample+filetag + ".txt"
path_log="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + getpass.getuser() + "/Cluster_" + ssample+filetag + ".log"

os.system("qstat -u '*' > " + path_log)

file_job=open(path_job,"w")
file_log=open(path_log,"r")

njobs=0
njobs_1=0
njobs_2=0
njobs_3=0
njobs_4=0
njobs_5=0
njobs_6=0
njobs_user=0
njobs_error=0
njobs_held=0

for line in file_log:
    splitline  = line.split()
    if len(splitline) < 6:
        continue
    if not "prior" in line:
        njobs=njobs+1
        if getpass.getuser() in line:
            njobs_user=njobs_user+1
        if "all.q@cms-0-1" in line:
            njobs_1=njobs_1+1
        if "all.q@cms-0-2" in line:
            njobs_2=njobs_2+1
        if "all.q@cms-0-3" in line:
            njobs_3=njobs_3+1
        if "all.q@cms-0-4" in line:
            njobs_4=njobs_4+1
        if "all.q@cms-0-5" in line:
            njobs_5=njobs_5+1
        if "all.q@cms-0-6" in line:
            njobs_6=njobs_6+1
                
        if "e" in splitline[4]:
            njobs_error=njobs_error+1
        if "E" in splitline[4]:
            njobs_error=njobs_error+1
        if "h" in splitline[4]:
            njobs_held=njobs_held+1
file_log.close()


file_job.write(getpass.getuser() + " njobs= " + str(njobs_user) + " njobs_1= " + str(njobs_1) + " njobs_2= " + str(njobs_2) + " njobs_3= " + str(njobs_3) + " njobs_4= " + str(njobs_4) + " njobs_5= " + str(njobs_5) + " njobs_6= " + str(njobs_6) + " error_jobs= " + str(njobs_error) + " held_jobs=  " + str(njobs_held) + "  total_jobs= " + str(njobs) + " \n")
file_job.close()

os.system("rm " + path_log)
