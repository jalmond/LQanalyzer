import os,sys,getpass,datetime

an_jonpre="/data2/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    an_jonpre="/data4/"

def GetList():
    if os.path.exists( an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG* >  " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/check"):
        os.system("rm " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG* >  " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/check")    

    os.system("ls -l " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG* >  " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/check")
    print ""
    print "_"*100
    print "Checking JobIDs that are running currently or have been in the past hour are. To check these IDs run:"
    print "_"*100
    now = datetime.datetime.now()
    nowm =now.strftime("%m")
    nowd =now.strftime("%d")
    nowd_last = int(nowd) -1
    nowy =now.strftime("%Y")
    nowh =now.strftime("%H")
    nowh_last = int(nowh) -1
    if nowh_last< 0:
        nowh_last=23
    if nowd_last == 0:
        nowd_last = 30

    file_check = open( an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/check","r")
    path_checked=""
    running_job=[]
    for line in file_check:
        if  an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" in line:
            path_checked=line
        else:
            if  " "+nowd+" " in line and " "+nowh+":" in line:
                running_job.append(path_checked)
            if " "+nowd+" " in line and " "+str(nowh_last)+":" in line:
                running_job.append(path_checked)
            if nowh_last == 23:    
                if " "+str(nowd_last)+" " in line and " "+str(nowh_last)+":" in line:
                    running_job.append(path_checked)
    file_check.close()

    jobidlist=[]
    for line in running_job:
        jobid=line.replace( an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG","")
        jobid=jobid.replace( ":","")
        jobid=(jobid.split())[0]
        jobidexists=False
        for i in jobidlist:
            if  jobid == i:
                jobidexists=True
                
        if not jobidexists:
            jobidlist.append(jobid)

    for i in jobidlist:
        bkg_job_file_path=an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/output_bkg.txt"
        finished_path=an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/output_finished.txt"

        if not os.path.exists(bkg_job_file_path):
            if not os.path.exists(finished_path):
                continue
            else:
                print "Check job status using sktree_bkg_log -j "+ i

        else:
            if  os.path.exists(finished_path):
                print "Check job status using sktree_bkg_log -j "+ i
                continue

            skip=False
            os.system("ls " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/" + i +"/ " +  " > " + an_jonpre + "CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/check.txt")
            file_check= open(an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/check.txt","r")
            for line in file_check:
                line = line.replace(".txt","")
                sline = line.split()
                if len(sline) == 1:
                    file_id=an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + i + "/"+sline[0]+"jobid.txt"
                    if not os.path.exists(file_id):
                        skip=True
            file_check.close()
            if not skip:
                print "Check job status using sktree_bkg_log -j "+ i 
    return


output_jobinfo_only=False


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-j", "--job", dest="j", default="123",help="tag")
parser.add_option("-o", "--output", dest="o", default="False",help="tag")


(options, args) = parser.parse_args()
jobid=options.j
outinfo=options.o


if jobid == "123":
    print "use sktree_bkg_log -j <jobid>"
    GetList()
    sys.exit()

if outinfo == "False":
    output_jobinfo_only=False
else:
    output_jobinfo_only=True

bkg_job_file_path=an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + jobid + "/output_bkg.txt"
finished_path=an_jonpre+"/CAT_SKTreeOutput/"+getpass.getuser() +"/CLUSTERLOG" + jobid + "/output_finished.txt"

if not os.path.exists(bkg_job_file_path):
    if not os.path.exists(finished_path):
        print "Job ID " + jobid + " does not exist"
    else:
        print "Job ID " + jobid + " has finished running"
else:
    file_bkg_job_file_path = open(bkg_job_file_path,"r")
    
    nlines=0
    for line in file_bkg_job_file_path:
        nlines=nlines+1
        sline = line.split()
        if len(sline) == 0:
            continue
        outline =""
        for x in range(1,len(sline)):
            outline=outline+ " " + sline[x]
        if not "|" in outline:
            continue
        if "Terminal Output" in outline:    
            if output_jobinfo_only:
                file_bkg_job_file_path.close()
                sys.exit()
            print "\n"
            print outline    
        elif "Files:" in  outline:
            print "\n"
            print outline
        else:
            if not "Cum.Process" in outline:
                print outline 
            if "Code" in outline:
                print "_"*130
    file_bkg_job_file_path.close()
    if nlines < 2:
        print "****** JOB COMPLETE"
