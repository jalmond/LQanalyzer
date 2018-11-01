import os ,sys, getpass
import time


def  CheckRunningNonBatch(filename, low_cpu):

    running = 0

    #sys.stdout.write('\r TEST: running on local machine....')
    os.system("ps ux &> " +filename)
    #sys.stdout.write('\r TEST: log sent to ' + filename)
    for line in open(filename, 'r'):
        if "root.exe" in line:
            running = 1
            splitline  = line.split()
            if splitline[2] < 0.1:
                low_cpu+=1
    if low_cpu > 3:
        running = 2

    os.system("rm  " + filename)
    return running


def CheckRunningKistiBatch(filename,job_id, output,i,  messagelog):
    
    
    running = 0
    
    #sys.stdout.write('\r TEST: running on kisti batch machine....' +messagelog+' \n')
    if i > 0:
        os.system("condor_q "+ str(job_id) +" > " + filename)
    else:
        os.system("condor_q "+ str(os.getenv("USER")) +" > " + filename)

    #sys.stdout.write('\r TEST: log sent to ' + filename+'\n')
    
    
    
    sys.stdout.write('\r ' + job_id  + '\n')
    job_id_global   = job_id.replace("."," ")
    sjob_id_global  = job_id_global.split()
    job_id_global   = sjob_id_global[0]
    n_held=11
    for line in open(filename, 'r'):
        if job_id_global  in line:
            sys.stdout.write('\r ' + job_id_global + ' : ' + line + '\n')
            running = 1
            entries = line.split()
                #### check if job is held, if so kill job
            if len(entries) ==  11:
                if not entries[8]  == "-":
                    print "Job " + str(job_id) + " is in held state: killing all jobs"
                    os.system("source " + output+ "JobKill.sh")
                    running = 2
        else:
            entries = line.split()
            if len(entries) ==  14 and "held" in line:
                if not str(entries[10])  == "0":
                    print "Job " + str(job_id) + " is in held state: killing all jobs"
                    os.system("source " + output+ "JobKill.sh")
                    running = 2



    os.system("rm  " + filename)
    
    #sys.stdout.write('\r CheckRunningKistiBatch = ' + str(running) + '\n') 

    return running


def CheckMachinesSNUBatch(filename, array_batchjobs, output):

    ##### this function is for stat use only, check which machines arfe used for certain jobs

    check_cluster="_"


    n_cms1=0
    n_cms2=0
    n_cms3=0
    n_cms4=0
    n_cms5=0
    n_cms6=0
    
    

    os.system("qstat -u '*' > " +  filename)
    #sys.stdout.write('\r TEST: log sent to ' + filename)

    for line in open(filename, 'r'):
        for job_id in array_batchjobs:
            if job_id in line:
                entries = line.split()
                    ### Check the job is not held/suspended                                                                                                                                                                                                                    \                                                                                                                                       

                if len(entries) ==  9:
                    idcheck="_"+job_id+"_"
                    if not idcheck in check_cluster:
                        if "cms-0-1" in entries[7]:
                            n_cms1+=1
                        if "cms-0-2" in entries[7]:
                            n_cms2+=1
                        if "cms-0-3" in entries[7]:
                            n_cms3+=1
                        if "cms-0-4" in entries[7]:
                            n_cms4+=1
                        if "cms-0-5" in entries[7]:
                            n_cms5+=1
                        if "cms-0-6" in entries[7]:
                            n_cms6+=1

                    check_cluster=check_cluster+job_id+"_"

                    if entries[4] == "h":
                        print "Job " + str(job_id) + " is in held state: killing all jobs"
                        os.system("source " + output+ "JobKill.sh")

                    if entries[4] == "s":
                        print "Job " + str(job_id) + " is in suspended state: killing all jobs"
                        os.system("source " + output+ "JobKill.sh")


    os.system("rm  " + filename)
                
    return (str(n_cms1) + ":" + str(n_cms2) + ":"+ str(n_cms3) + ":"+ str(n_cms4) + ":"+ str(n_cms5) + ":"+ str(n_cms6))
    
    


def CheckRunningSNUBatch(filename, array_batchjobs, output):

    check_cluster="_"

    running = 0
    
    os.system("qstat -u '*' > " +  filename)

    
    for line in open(filename, 'r'):
        for job_id in array_batchjobs:
            if job_id in line:
                running = 1
                entries = line.split()
                    ### Check the job is not held/suspended                                                                                                                                                                                                                    \
                        
                if len(entries) ==  9:
                    
                    if entries[4] == "h":
                        print "Job " + str(job_id) + " is in held state: killing all jobs"
                        os.system("source " + output+ "JobKill.sh")
                        running = 2
                    if entries[4] == "s":
                        print "Job " + str(job_id) + " is in suspended state: killing all jobs"
                        os.system("source " + output+ "JobKill.sh")
                        running = 2


    os.system("rm  " + filename)
    return running




def CheckBatch(isKisti, filename):

    if not isKisti:
        os.system("qstat -u " + getpass.getuser()  + " > " + filename)
    else:
        os.system("condor_q " + getpass.getuser()  + " > " + filename)



def CHECK_OUTLOGFILE(isKisti, output, i, outsamplename, array_batchjobs):

    ### This function sets the path of the log files used to see if sub job "i" is running
    
    check_outfile=""
    if not isKisti:
        check_outfile = output + "/Job" +  "_" +  str(i) + "/" + outsamplename + "_Job_"+ str(i) +".o"+array_batchjobs[i-1]
    else:
        check_outfile = output + "/Job_000/job_"+str(i-1)+".log"

    return check_outfile




def SetStartTime(start_time, i):
    
    if start_time == 0.:
        if i == 1:
            start_time = time.time()
    return start_time

def CheckRunningBatch(isKisti, filename, array_batchjobs, i, output):
    
    if isKisti:
        return CheckRunningKistiBatch(filename, array_batchjobs[i-1], output, i, "secondary")
    else:
        return CheckRunningSNUBatch(filename, array_batchjobs, output)


def GetFailedMacroName(isKisti, output, i):
    if not isKisti:
        return output+ "Job_" + str(i) + "/runJob_" + str(i) + ".C"
    else:
        return output+ "Job_000/runJob_000.C"


def GetFailedLogName(isKisti, outsamplename, i, array_batchjob):
    if not isKisti:
        return outsamplename+ "_Job_" + str(i)+".o"+str(array_batchjobs[i-1])
    else:
        return  "job_0.log"


def CheckPercentComplete(isKisti,number_of_cores,output,outsamplename, array_batchjobs, local_sub_dir,running_batch):
    
    results_complete =[]
    nevent_processed=0
    nevents_total=0

    if isKisti:
        results_complete.append(1)
        results_complete.append(1)
        return results_complete
    

    for i in range(1,number_of_cores+1):
            check_outfile = output + "/Job" +  "_" +  str(i) + "/runJob_"+ str(i) +".log"
            if running_batch == True:
                check_outfile = output + "/Job" +  "_" +  str(i) + "/" + outsamplename + "_Job_"+ str(i) +".o"+array_batchjobs[i-1]

            os.system('tail -100 ' + check_outfile + ' > ' + local_sub_dir + '/outlog.txt')
            nevent_processed_i=0.
            nevents_total_i=0.
            for line in open(local_sub_dir + '/outlog.txt', 'r'):
                if "Processing entry" in line:
                    if "LQCycleController" not in line:
                        entries = line.split()
                        if len(entries)> 7:                        
                            num = entries[7]
                            lineok=False
                            if "/" in num:
                                lineok=True
                            s = num.replace("/", " ")
                            event_split = s.split()
                            if len(event_split) < 2:
                                print "Warning [2002] " + s

                                os.system("cp " + local_sub_dir + '/outlog.txt ~/error_log_'+str(array_batchjobs[i-1]))
                            if lineok:
                                nevent_processed_i = float(event_split[0])
                                nevents_total_i= float(event_split[1])
            nevent_processed+=nevent_processed_i                
            nevents_total+=nevents_total_i
    results_complete.append(nevent_processed)
    results_complete.append(nevents_total)
    return results_complete





def QUEUECOMMAND(queue,path_jobpre):

    queuepath=path_jobpre +"LQAnalyzer_rootfiles_for_analysis/CattupleConfig/QUEUE/ForceQueue.txt"
    file_queuepath = open(queuepath,"r")
    for line in file_queuepath:
        if "#" in line:
            continue
        sline = line.split()
        for s in sline:
            if "@" in s or "fast" in s or "all" in s or "long" in s:
                queue= s
    file_queuepath.close()


    queue_command = ''
    qlist=[]

    
    if queue == "None":
        queue = "fastq"


    queueok=False
    if queue:
        queue_command=' -q '
    if queue == "allq":
        queue_command=''
        queueok=True
    if queue == "fastq":
        queue_command=queue_command+ ' fastq '
        queueok=True
    if queue == "longq":
        queue_command=queue_command+ ' longq '
        queueok=True
    queue=queue.replace("all.q@cms-0-","node")
    queue=queue.replace(".local","")
    if "node1" in queue:
        qlist.append(1)
    if "node2" in queue:
        qlist.append(2)
    if "node3" in queue:
        qlist.append(3)
    if "node4" in queue:
        qlist.append(4)
    if "node5" in queue:
        qlist.append(5)
    if "node6" in queue:
        qlist.append(6)
    if "node" in queue:
        queue_command=queue_command+ ' "'
    for q in qlist:
        queue_command=queue_command+"all.q@cms-0-"+str(q)+".local,"
    if len(qlist) > 0    :
        queueok=True
        queue_command=queue_command[:-1]
        queue_command=queue_command+'" '

    if queue == "None":
        queue=""
    if not  queue:
        queue=""

    queue_list = []
    queue_list.append(queue)
    queue_list.append(queue_command)
    return queue_list


def GetExtraLibNames(tmplist_of_extra_lib):

    list_of_extra_lib=[]
    libname=''
    
    for lib in tmplist_of_extra_lib:
        if '"' in libname:
            libname=""
        if ',' in libname:
            libname=""

        libname+=lib
        if ".so" in libname:
            list_of_extra_lib.append(libname)
            libname=""

    if libname != "NULL":
        if len(list_of_extra_lib) ==0:
            print "Name of library has to contain .so."

    for lib in list_of_extra_lib:
        print "Adding " + lib + " to list of Libraies to Load"

    return list_of_extra_lib


def UpdateSkimName(useskim):

    if useskim == "SKTree_NoSkim":
        useskim ="NoCut"
    elif useskim == "SKTree_LeptonSkim":
        useskim ="Lepton"
    elif useskim == "SKTree_DiLepSkim":
        useskim="DiLep"
    elif useskim == "SKTree_HNDiLepSkim":
        useskim="HNDiLep"
    elif useskim == "SKTree_HNFakeSkim":
        useskim="HNFake"
    elif useskim == "SKTree_HNFatJetSkim":
        useskim="HNFatJet"
    elif useskim == "SKTree_TriLepSkim":
        useskim="TriLep"
        
    return useskim
