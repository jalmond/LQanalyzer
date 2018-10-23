import os 
isKisti = ("ui" in str(os.getenv("HOSTNAME")))



def InputFileName(ktag, is_signal):
    
    if is_signal:
        return "datasets_snu_sig_CAT"+ktag+"_mc_"
    else:
        return "datasets_snu_nonsig_CAT"+ktag+"_mc_"



def ISMC( sname):
    
    ### sname = sample name
    ### in 2016 data is B,C,D,E,F,G, H_v2, H_v3
    
    isMC = len(sname) > 1
    if sname == "H_v2" or sname == "H_v3":
        isMC= False
    return  isMC


def MakeDir(dirpath):
    if not (os.path.exists(dirpath)):
        os.system("mkdir " + dirpath)

    return dirpath

def MakeIterDir(dirpath):


    while  (os.path.exists(dirpath)):
        app_dir=1
        dirpath= dirpath + "_v" + str(app_dir)
        app_dir = app_dir+1
    if not (os.path.exists(dirpath)):
        os.system("mkdir " + dirpath)
    return dirpath


def GetChannelName(useskinput, mc, useskim,sample, new_channel):
    if useskinput == "true":
        if not mc:
            if useskim == "Lepton":
                new_channel="SK" + new_channel
            else:
                if useskim == "NoCut":
                    new_channel="SK" + new_channel + "_nocut"
                else:
                    if useskim == "DiLep":
                        new_channel="SK" + new_channel + "_dilep"
                    else:
                        if useskim == "HNDiLep":
                            new_channel="SK" + new_channel + "_hndilep"
                        else:
                            if useskim == "HNFake":
                                new_channel="SK" + new_channel + "_hnfake"
                            else:
                                if useskim == "HNFatJet":
                                    new_channel="SK" + new_channel + "_hnfatjet"
                                    
                                else:
                                    if useskim == "TriLep":
                                        new_channel="SK" + new_channel + "_trilep"
                                        
                                        
        else:
            if useskim == "Lepton":
                sample="SK" + sample
            else:
                if useskim == "NoCut":
                    sample="SK" + sample + "_nocut"
                else:
                    if useskim == "DiLep":
                        sample="SK" + sample + "_dilep"
                    else:
                        if useskim == "HNDiLep":
                            sample="SK" + sample + "_hndilep"
                        else:
                            if useskim == "HNFake":
                                sample="SK" + sample + "_hnfake"
                            else:
                                if useskim == "HNFatJet":
                                    sample="SK" + sample + "_hnfatjet"
                                else:
                                    if useskim == "TriLep":
                                        sample="SK" + sample + "_trilep"
                                        


    elif useskinput == "True":

        if not mc:
            if useskim == "Lepton":
                new_channel="SK" + new_channel
            else:
                if useskim == "NoCut":
                    new_channel="SK" + new_channel + "_nocut"
                else:
                    if useskim == "DiLep":
                        new_channel="SK" + new_channel + "_dilep"
                    else:
                        if useskim == "HNDiLep":
                            new_channel="SK" + new_channel + "_hndilep"
                        else:
                            if useskim == "HNFake":
                                new_channel="SK" + new_channel + "_hnfake"
                            else:
                                if useskim == "HNFatJet":
                                    new_channel="SK" + new_channel + "_hnfatjet"
                                    
                                else:
                                    if useskim == "TriLep":
                                        new_channel="SK" + new_channel + "_trilep"
                                        
        else:
            if useskim == "Lepton":
                sample="SK" + sample
            else:
                if useskim == "NoCut":
                    sample="SK" + sample + "_nocut"
                else:
                    if useskim == "DiLep":
                        sample="SK" + sample + "_dilep"
                    else:
                        if useskim == "HNDiLep":
                            sample="SK" + sample + "_hndilep"
                        else:
                            if useskim == "HNFake":
                                sample="SK" + sample + "_hnfake"
                            else:
                                if useskim == "HNFatJet":
                                    sample="SK" + sample + "_hnfatjet"
                                else:
                                    if useskim == "TriLep":
                                        sample="SK" + sample + "_trilep"
                                        
    print "Input sample = " + sample
    if not mc:
        print "Input channel = " + new_channel

    if not mc: 
        return new_channel
    else:
        return sample


def   MergeData(defrunnp,defruncf,defdata_lumi, defFinaloutputdir,  defcatversion, defuseskim, defcycle, defchannel, deftmp_filename,deftagger,skflag):

    defoutput_file_skim_tag=defchannel

    versiontag = "_cat_"+defcatversion
    if True:
        #### can be used to change version 
        versiontag = "" + versiontag
 
    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if defuseskim == "FLATCAT":
        defoutput_file_skim_tag=defoutput_file_skim_tag+ versiontag
    if defuseskim == "SKTree_LeptonSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+ versiontag
    if defuseskim == "SKTree_DiLepSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_dilep" + versiontag
    if defuseskim == "SKTree_HNDiLepSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hndilep" + versiontag
    if defuseskim == "SKTree_HNFakeSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfake" + versiontag
    if defuseskim == "SKTree_HNFatJetSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfatjet" + versiontag


    if defuseskim == "SKTree_TriLepSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_trilep" + versiontag
    if defuseskim == "SKTree_NoSkim" :
        defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_nocut" + versiontag

    if defrunnp == "True":
        defoutput_file_skim_tag=defchannel
        foutname="nonprompt"
        if defuseskim == "FLATCAT":
            defoutput_file_skim_tag=defoutput_file_skim_tag+ versiontag
            foutname=foutname+ versiontag
        if defuseskim == "SKTree_LeptonSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+ versiontag
            foutname="SK"+foutname+ versiontag
        if defuseskim == "SKTree_DiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_dilep" + versiontag
            foutname="SK"+foutname+"_dilep" + versiontag
        if defuseskim == "SKTree_HNDiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hndilep" + versiontag
            foutname="SK"+foutname+"_hndilep" + versiontag
 
        if defuseskim == "SKTree_HNFakeSkim":
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfake" + versiontag
            foutname="SK"+foutname+"_hnfake" + versiontag
        if defuseskim == "SKTree_HNFatJetSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfatjet" + versiontag
            foutname="SK"+foutname+"_hnfatjet" + versiontag


        if defuseskim == "SKTree_TriLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_trilep" + versiontag
            foutname="SK"+foutname+"_trilep" + versiontag


        defFinaloutputdirMC=""

        if "/Fake/" in defFinaloutputdir:
            defFinaloutputdirMC=defFinaloutputdir
            defFinaloutputdirMC=defFinaloutputdirMC.replace("Fake/","")

        if defdata_lumi == "ALL" or defdata_lumi==os.getenv("catdatatag"):
            if not  "SKTreeMaker" in cycle:
                os.system("source hadd.sh " + defFinaloutputdir + " "+defcycle+"_"+defoutput_file_skim_tag+".root "+defFinaloutputdir+"/"+defcycle+"'*'"+defoutput_file_skim_tag+"'*'")
                os.system("mv "  + defFinaloutputdir+ "/"+ defcycle+"_"+defoutput_file_skim_tag+".root " + defFinaloutputdirMC+ "/"+defcycle+ "_"+defchannel+"_"+foutname+deftmp_filename+".root")

                hist_pre =  "/data2/CAT_SKTreeOutput/"

                if isKisti:
                    hist_pre ="/cms/scratch/SNU/CATAnalyzer/"

                if not os.path.exists( hist_pre+os.getenv("USER")+"/Histdir" + deftagger ):
                    os.system("mkdir " +  hist_pre+os.getenv("USER")+"/Histdir" + deftagger)
                os.system("source "+os.getenv("LQANALYZER_DIR")+"/scripts/Counter.sh " + defFinaloutputdirMC+ "/"+defcycle+ "_"+defchannel+"_"+foutname+deftmp_filename+".root > "+hist_pre+str(os.getenv("USER"))+"/Histdir" + str(deftagger) + "/Hist.txt"   )
                os.system("source "+os.getenv("LQANALYZER_DIR")+"/scripts/CutFlow.sh " + defFinaloutputdirMC+ "/"+defcycle+ "_"+defchannel+"_"+foutname+deftmp_filename+".root > "+hist_pre+str(os.getenv("USER"))+"/Histdir" + str(deftagger) + "/CutFlow.txt"   )




    elif defruncf == "True":
        defoutput_file_skim_tag=defchannel
        foutname="chargeflip"
        if defuseskim == "FLATCAT":
            defoutput_file_skim_tag=defoutput_file_skim_tag+ versiontag
            foutname=foutname+ versiontag
        if defuseskim == "SKTree_LeptonSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+ versiontag
            foutname="SK"+foutname+ versiontag
        if defuseskim == "SKTree_DiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_dilep" + versiontag
            foutname="SK"+foutname+"_dilep" + versiontag
        if defuseskim == "SKTree_HNDiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hndilep" + versiontag
            foutname="SK"+foutname+"_hndilep" + versiontag
        if defuseskim == "SKTree_HNFakeSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfake" + versiontag
            foutname="SK"+foutname+"_hnfake" + versiontag
        if defuseskim == "SKTree_HNFatJetSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfatjet" + versiontag
            foutname="SK"+foutname+"_hnfatjet" + versiontag

        if defuseskim == "SKTree_TriLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_trilep" + versiontag
            foutname="SK"+foutname+"_trilep" + versiontag

    else:
        defoutput_file_skim_tag=defchannel
        if defuseskim == "FLATCAT":
            defoutput_file_skim_tag=defoutput_file_skim_tag+ versiontag
        if defuseskim == "SKTree_NoSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_nocut" + versiontag
        if defuseskim == "SKTree_LeptonSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+ versiontag
        if defuseskim == "SKTree_DiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_dilep" + versiontag
        if defuseskim == "SKTree_HNDiLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hndilep" + versiontag
        if defuseskim == "SKTree_HNFakeSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfake" + versiontag
        if defuseskim == "SKTree_HNFatJetSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_hnfatjet" + versiontag

        if defuseskim == "SKTree_TriLepSkim" :
            defoutput_file_skim_tag="SK"+defoutput_file_skim_tag+"_trilep" + versiontag

        defFinaloutputdirMC=""

        if "/Data/" in defFinaloutputdir:
            defFinaloutputdirMC=defFinaloutputdir
            defFinaloutputdirMC=defFinaloutputdirMC.replace("Data/","")
        else:
            return


        output_datafile=defFinaloutputdirMC+"/"+defcycle+"_data_cat_"+ defcatversion+".root"
        print "MergeData: " + defdata_lumi + " " + defdata_lumi
        if defdata_lumi == "ALL" or defdata_lumi==os.getenv("catdatatag"):
            if not "SKTreeMaker" in defcycle:

                print "MergeDataL "

                os.system("source hadd.sh " + defFinaloutputdir + " "+defcycle+"_data" + versiontag+".root "+defFinaloutputdir+"/"+defcycle+"'*'"+defoutput_file_skim_tag+"'*'")
                os.system("mv "  + defFinaloutputdir+ "/"+defcycle+"_data" + versiontag+".root  " + defFinaloutputdirMC+ "/"+defcycle+"_data_" + defchannel+ versiontag+deftmp_filename+".root")

                hist_pre =  "/data2/CAT_SKTreeOutput/"
                if isKisti:
                    hist_pre ="/cms/scratch/SNU/CATAnalyzer/"


                print "MergeData: "+ hist_pre
                if not os.path.exists( hist_pre+os.getenv("USER")+"/Histdir" + deftagger ):
                    os.system("mkdir " +  hist_pre+os.getenv("USER")+"/Histdir" + deftagger)
                    print "MergeData: " + hist_pre+os.getenv("USER")+"/Histdir" + deftagger
                os.system("source "+str(os.getenv("LQANALYZER_DIR"))+"/scripts/Counter.sh " + defFinaloutputdirMC+ "/"+defcycle +"_data_" + defchannel+ versiontag+deftmp_filename+".root  > "+hist_pre+str(os.getenv("USER"))+"/Histdir" + str(deftagger) + "/Hist.txt" )
                os.system("source "+str(os.getenv("LQANALYZER_DIR"))+"/scripts/CutFlow.sh " + defFinaloutputdirMC+ "/"+defcycle +"_data_" + defchannel+ versiontag+deftmp_filename+".root  > "+hist_pre+str(os.getenv("USER"))+"/Histdir" + str(deftagger) + "/CutFlow.txt"   )




def UpdateOutput(outputlist,outputlist_path):
    out_file = open(outputlist_path,"w")
    for x in outputlist:
        out_file.write(x+"\n")
    out_file.close()

def GetListOld():

    ### List of tags with stst logging but no memeory values in the Master File                                                                                                                             
    clist=[]
    clist.append("v8-0-1.7")
    clist.append("v8-0-1.6")
    return clist

def GetListNew():

    ### change in format (add memory of jobs since v8-0-1.8)                                                                                                                                                
    ### This new format allows job to output WARNING if jobs are using more memory than previously.                                                                                                         
    ### This should help fix any possible memory leaks when the happen                                                                                                                                      
    clist=[]
    clist.append("v8-0-1.8")
    clist.append("v8-0-2")### this will take care of all 802 tags                                                                                                                                           
    return clist

def GetList():

    clist=GetListNew() + GetListOld()
    #for ct in GetListNew():                                                                                                                                                                                
    return clist

def NewForat(ct):

    clist = GetListNew()
    for ctag in clist:
        if ct == ctag:
            return True
        if ctag in ct:
            return True
    return False


def GetNFiles( deftagger,defsample,defcycle,defskim):


    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        return 1

    if not os.path.exists(path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"):
        return 1000.

    nit=2
    if "SKTreeMaker" in defcycle:
        nit=0
    avg_time=-999.
    checkdate = datetime.datetime.now()
    tmpday=int(checkdate.strftime("%d"))
    diff = datetime.timedelta(days=(tmpday+1))
    checkdate=checkdate+diff
    get_nfiles=0
    while avg_time < 0:
        if nit < 0:
            return 1000.
        nit =nit-1
        #### get previous month                                                                                                                                                                             
        checkdate=checkdate-diff
        month=checkdate.strftime("%m")
        day=checkdate.strftime("%d")
        year=checkdate.strftime("%y")

        file_jobsummary="/data1//LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(GetMonth(int(month)))+"_20"+year+".txt"

        if not os.path.exists(file_jobsummary):
            return 1000.

        read_file_jobsummary = open(file_jobsummary,"r")


        for line in read_file_jobsummary:
            if os.getenv("USER") in line:
                tmpsample=defsample+" skim"
                if not "True" in line:
                    continue
                if len(defsample) == 1:
                    tmpsample="_"+tmpsample+" "
                elif "H_" in defsample:
                    tmpsample="_"+tmpsample+" "

                if tmpsample in line and defskim in line and defcycle in line and os.getenv("CATVERSION") in line:
                    splitline = line.split()
                    nthsplit=0
                    for s in splitline:
                        if nthsplit== 12:
                            get_nfiles=int(s)
                        nthsplit=nthsplit+1
        read_file_jobsummary.close()

        if get_nfiles < 1:
            continue
        else:
            return get_nfiles

    return 1000.


def GetAverageTime( gettinglongest, deftagger,defsample,defcycle,defskim, rundebug):


    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        return 1.

    if not os.path.exists(path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"):
        return 1000.


    nit=2
    avg_time=-999.
    checkdate = datetime.datetime.now()
    tmpday=int(checkdate.strftime("%d"))
    diff = datetime.timedelta(days=(tmpday+1))
    checkdate=checkdate+diff

    while avg_time < 0:

        gettime_nfiles=0
        gettime_njobs=0
        gettime_jobtime=0

        if nit < 0:
            return 1000.
        nit =nit-1
        #### get previous month                                                                                                                                                                             
        checkdate=checkdate-diff
        month=checkdate.strftime("%m")
        day=checkdate.strftime("%d")
        year=checkdate.strftime("%y")

        file_jobsummary="/data1//LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(GetMonth(int(month)))+"_20"+year+".txt"
        if rundebug:
            file_debug = open("debug.txt","a")
            file_debug.write(file_jobsummary+"\n")
        if not os.path.exists(file_jobsummary):
            return 1000.

        read_file_jobsummary = open(file_jobsummary,"r")
        nfound=0.
        for line in read_file_jobsummary:

            if not "True" in line:
                continue
            if os.getenv("USER") in line:
                tmpsample=defsample+" skim"
                if len(defsample) == 1:
                    tmpsample="_"+tmpsample+" "
                elif "H_" in defsample:
                    tmpsample="_"+tmpsample+" "

                if tmpsample in line and defskim in line and defcycle in line:
                    splitline = line.split()
                    nthsplit=0
                    if len(splitline) < 38:
                        continue
                    for s in splitline:
                        if nthsplit==24:
                            if float(s) < 0:
                                gettime_jobtime=0.
                            else:
                                gettime_jobtime=float(s)
                        if nthsplit==10:
                            gettime_njobs=float(s)
                        if nthsplit==12:
                            gettime_nfiles=float(s)

                        nthsplit=nthsplit+1
                    if gettime_jobtime > 0.:
                        break

        read_file_jobsummary.close()

        if gettime_jobtime < 1.:
            if rundebug:
                file_debug.write("gettime_jobtime = " + str(gettime_jobtime)+"\n")
            continue
        if gettime_nfiles < 1:
            if rundebug:
                file_debug.write("gettime_nfiles = " + str(gettime_nfiles)+"\n")

            continue
        if gettime_njobs < 1:
            if rundebug:
                file_debug.write("gettime_njobs = " + str(gettime_njobs)+"\n")

            continue

        if gettinglongest:
            if rundebug:
                file_debug.close()
            return (float(gettime_jobtime) * float(gettime_njobs))

        gettime_jobtime = float(gettime_jobtime) / float(gettime_nfiles)
        gettime_jobtime = float(gettime_jobtime) * float(gettime_njobs)
        avg_time=float(gettime_jobtime)
        if rundebug:
            file_debug.close()
        return avg_time
    if rundebug:
        file_debug.close()

    return 1000.

def FreeSpaceInQueue(jobqueue, deftagger):

    
    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        return 100.


    is_allowed_queue =  jobqueue == "fastq" or jobqueue == "longq"
    if not is_allowed_queue:
        return 1000.

    an_jobpre="/data2/"   ####  pre-path for job output                                                                                                                                                    


    path_clust_check_njobs=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(deftagger)+ "/clustercheck.txt"
    os.system("qstat -f   > " +  path_clust_check_njobs)
    file_clust_check_njobs=open(path_clust_check_njobs ,"r")
    fastq_ninqueue=0.
    fastq_nallowedinqueue=0.
    longq_ninqueue=0.
    longq_nallowedinqueue=0.
    for cline in file_clust_check_njobs:
        if "fastq" in cline:
            splitline = cline.split()
            if len(splitline) ==6 and ".local" in cline:
                if splitline[5] == "a":
                    return 0

            if len(splitline) ==5:
                qjobinfo=splitline[2]
                qjobinfo=qjobinfo.replace("/"," ")
                splitqjobinfo=qjobinfo.split()
                fastq_ninqueue=fastq_ninqueue+float(splitqjobinfo[1])
                fastq_nallowedinqueue=fastq_nallowedinqueue+float(splitqjobinfo[2])
        if "longq" in cline:
            splitline = cline.split()
            if len(splitline) ==6 and ".local" in cline:
                if splitline[5] == "a":
                    return 0

            if len(splitline) ==5:
                qjobinfo=splitline[2]
                qjobinfo=qjobinfo.replace("/"," ")
                splitqjobinfo=qjobinfo.split()
                longq_ninqueue=longq_ninqueue+float(splitqjobinfo[1])
                longq_nallowedinqueue=longq_nallowedinqueue+float(splitqjobinfo[2])

    file_clust_check_njobs.close()

    if jobqueue == "fastq":
        return (fastq_nallowedinqueue - fastq_ninqueue)

    else:
        return(longq_nallowedinqueue - longq_ninqueue)



def ChangeQueue(jobsummary, jobqueue, ncores_job, deftagger, rundebug):


    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        return jobqueue

    if rundebug:
        file_debug = open("debug.txt","a")

    if not ( jobqueue == "fastq" or jobqueue == "longq"):
        return jobqueue

    if rundebug:
        file_debug.write("queue ok\n")


    path_clust_check_njobs=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(deftagger)+ "/clustercheck.txt"
    os.system("qstat -f   > " +  path_clust_check_njobs)
    file_clust_check_njobs=open(path_clust_check_njobs ,"r")
    fastq_ninqueue=0.
    fastq_nallowedinqueue=0.
    longq_ninqueue=0.
    longq_nallowedinqueue=0.
    alarm_fast=False
    alarm_long=False

    for cline in file_clust_check_njobs:
        if "fastq" in cline:
            splitline = cline.split()
            if len(splitline) ==5:
                qjobinfo=splitline[2]
                qjobinfo=qjobinfo.replace("/"," ")
                splitqjobinfo=qjobinfo.split()
                fastq_ninqueue=fastq_ninqueue+float(splitqjobinfo[1])
                fastq_nallowedinqueue=fastq_nallowedinqueue+float(splitqjobinfo[2])
            elif len(splitline) ==6 and ".local" in cline:
                if splitline[5] == "a":
                    alarm_fast=True
                else:
                    qjobinfo=splitline[2]
                    qjobinfo=qjobinfo.replace("/"," ")
                    splitqjobinfo=qjobinfo.split()
                    fastq_ninqueue=fastq_ninqueue+float(splitqjobinfo[1])
                    fastq_nallowedinqueue=fastq_nallowedinqueue+float(splitqjobinfo[2])


        if "longq" in cline:
            splitline = cline.split()
            if len(splitline) ==5:
                qjobinfo=splitline[2]
                qjobinfo=qjobinfo.replace("/"," ")
                splitqjobinfo=qjobinfo.split()
                longq_ninqueue=longq_ninqueue+float(splitqjobinfo[1])
                longq_nallowedinqueue=longq_nallowedinqueue+float(splitqjobinfo[2])
            elif len(splitline) ==6 and ".local" in cline:
                if splitline[5] == "a":
                    alarm_long=True
                else:
                    qjobinfo=splitline[2]
                    qjobinfo=qjobinfo.replace("/"," ")
                    splitqjobinfo=qjobinfo.split()
                    longq_ninqueue=longq_ninqueue+float(splitqjobinfo[1])
                    longq_nallowedinqueue=longq_nallowedinqueue+float(splitqjobinfo[2])
        if alarm_long and alarm_fast:
            curses.echo()
            curses.nocbreak()
            curses.endwin()
            print "Exiting since fast and long queues are in alarm state"
            sys.exit()
        elif alarm_long:
            return "fastq"
        elif alarm_fast:
            return "longq"

    file_clust_check_njobs.close()
    if rundebug:
        file_debug.write("queue fast: fastq_ninqueue=" + str(fastq_ninqueue) + " fastq_nallowedinqueue = " + str(fastq_nallowedinqueue)+ " \n")
        file_debug.write("queue long: long_ninqueue=" + str(longq_ninqueue) + " longq_nallowedinqueue = " + str(longq_nallowedinqueue)+ " \n")
        file_debug.write("ncores_job = " + str(ncores_job) + " \n")
    if jobqueue == "fastq":
        if ncores_job < (fastq_nallowedinqueue-fastq_ninqueue):
            if rundebug:
                file_debug.write("fastq, return " + jobqueue+ "\n")
                file_debug.close()
            return jobqueue
        else:
            if (float(fastq_ninqueue) / float(fastq_nallowedinqueue)) < 0.9:
                if rundebug:
                    file_debug.write("fastq2, return " + jobqueue+ "\n")
                    file_debug.close()
                return jobqueue
            else:
                if ncores_job < (longq_nallowedinqueue-longq_ninqueue):
                    job_summary.append("########################################")
                    job_summary.append("Changing queue to submit job in empty queue")
                    job_summary.append("########################################")
                    if rundebug:
                        file_debug.write("longq, return " + jobqueue+ "\n")
                        file_debug.close()
                    return "longq"
                elif (float(longq_ninqueue)/ float(longq_nallowedinqueue)) < 0.1:
                    job_summary.append("########################################")
                    job_summary.append("Changing queue to submit job in empty queue")
                    job_summary.append("########################################")
                    if rundebug:
                        file_debug.write("longq2, return " + jobqueue+ "\n")
                        file_debug.close()
                    return "longq"
                else:
                    return jobqueue
    else:
        if ncores_job < (longq_nallowedinqueue-longq_ninqueue):
            if rundebug:
                file_debug.write("longq, return " + jobqueue+ "\n")
                file_debug.close()
            return jobqueue
        else:
            if (float(longq_ninqueue) / float(longq_nallowedinqueue)) < 0.7:
                if rundebug:
                    file_debug.write("longq2, return " + jobqueue+ "\n")
                    file_debug.close()
                return jobqueue
            else:
                if ncores_job < (fastq_nallowedinqueue-fastq_ninqueue):
                    job_summary.append("########################################")
                    job_summary.append("Changing queue to submit job in empty queue")
                    job_summary.append("########################################")
                    if rundebug:
                        file_debug.write("fastq, return " + jobqueue+ "\n")
                        file_debug.close()

                    return "fastq"
                elif (float(fastq_ninqueue)/ float(fastq_nallowedinqueue)) < 0.9:
                    job_summary.append("########################################")
                    job_summary.append("Changing queue to submit job in empty queue")
                    job_summary.append("########################################")
                    if rundebug:
                        file_debug.write("fastq2, return " + jobqueue+ "\n")
                        file_debug.close()
                    return "fastq"
                else:
                    return jobqueue


    return jobqueue


def DetermineNjobs(jobsummary, nfiles_job, longestjobtime, ncores_job, deftagger,defsample,defcycle,defskim, defqueue, nfreeqall, submitall, rundebug, njobs_expectedtorun, jobsleft):

    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        return 2

    if rundebug:
        file_debug = open("debug.txt","a")

    tmplongestjobtime=float(GetAverageTime(True,deftagger, defsample, defcycle,defskim,rundebug))
    isLongestJob=False
    if tmplongestjobtime == longestjobtime:
        isLongestJob=True

    if rundebug:
        file_debug.write("deftagger " + deftagger + " defsample = " + defsample + " defskim = " + defskim + " defqueue = " + defqueue + "\n")
    if not os.path.exists(path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"):
        return 20

    if ncores_job == 0:
         return 1

    if ncores_job == 1:
        return 1

    if submitall:
        return 1000

    expectedjobnfiles=int(GetNFiles(deftagger, defsample, defcycle,defskim))
    if "SKTreeMaker" in defcycle:
        return expectedjobnfiles

    if rundebug:
        file_debug.write("number of files = " + str(expectedjobnfiles)+"\n")

    if expectedjobnfiles < 0:
        jobsummary.append( "current sample/skim has not been processed before. Setting number of of jobs to 20 as default.")
        return 20


    if rundebug:
        file_debug.write("queue = " + str(defqueue) + "\n")
        file_debug.write("FreeSpaceInQueue: number of free cores = " + str(nfreeqall) +"\n" )


    if tmplongestjobtime == 1000.:
        return 20
    #### longestjobtime is time[s] to run 1 job on batch system                                                                                                                                             

    ### for jobs that take longer than 5000/n s                                                                                                                                                             
    isbusy_addon=0

    if njobs_expectedtorun > 0:
        if tmplongestjobtime < 60000 and tmplongestjobtime > 5000:
            if rundebug:
                file_debug.write("njobs_expectedtorun = " + str(njobs_expectedtorun) + "\n")
            if float(nfreeqall)  - float(njobs_expectedtorun) > 20:
                nleftover = float(nfreeqall)  - float(njobs_expectedtorun) - 20.
                if rundebug:
                    file_debug.write("nleftover= " +str(nleftover) + "\n")
                while  nleftover%float(jobsleft):
                    nleftover=nleftover+1
                    if rundebug:
                        file_debug.write("correctednleftover= " +str(nleftover) + "\n")
                isbusy_addon = float(nleftover)/float(jobsleft)
                if rundebug:
                    file_debug.write("isbusy_addon = " + str(isbusy_addon) + "\n")

    njobs_long=0

    if longestjobtime > 150000:
        njobs_long=75
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 50:
                return nfreeqall
            else:
                return njobs_long
    elif longestjobtime > 100000:
        njobs_long=60
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 50:
                return nfreeqall
            else:
                return njobs_long
    elif longestjobtime > 60000:
        njobs_long=50
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 35:
                return nfreeqall
            else:
                return njobs_long

    elif longestjobtime >20000:
        njobs_long=35

        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 20:
                return nfreeqall
            else:
                return njobs_long

    elif longestjobtime >10000:
        njobs_long=25

        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 15:
                return nfreeqall
            else:
                return njobs_long

    elif longestjobtime >5000:
        njobs_long=15

        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 12:
                return nfreeqall
            else:
                return njobs_long



    elif longestjobtime >2000:

        njobs_long=10
        njobs_long=10
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 10:
                return nfreeqall
            else:
                return njobs_long



    elif longestjobtime >1000:

        njobs_long=10
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 5:
                return nfreeqall
            else:
                return njobs_long



    elif longestjobtime >600:

        njobs_long=5
        longestjobtime= longestjobtime/float(njobs_long)
        if isLongestJob:
            if njobs_long > nfreeqall and nfreeqall > 2:
                return nfreeqall
            else:
                return njobs_long

    else:
         njobs_long=2
         longestjobtime= longestjobtime/float(njobs_long)
         if isLongestJob:
             return njobs_long

    if rundebug:
        file_debug.write("longestjobtime = " + str(longestjobtime)  +"\n" )
    if not longestjobtime == -499.5:
        if longestjobtime < 0.:
            if rundebug:
                file_debug.close()
            return 20


    ### expectedjobtime = time per file if ran 1 job in bacth queue                                                                                                                                         
    expectedjobtime=tmplongestjobtime

    if rundebug:
        file_debug.write("expectedjobtime = " + str(expectedjobtime) + "\n")
    if expectedjobtime  < 0:
        print "current job has not been processed before. Setting number of of jobs to 20 as default."
        if rundebug:
            file_debug.close()
        return 20

    if expectedjobtime  == 1000.:
        print "current job has not been processed before. Setting number of of jobs to 20 as default."
        if rundebug:
            file_debug.close()
        return 20

    ## now this is total time expcected to run for all files                                                                                                                                                
    #expectedjobtime = expectedjobtime* expectedjobnfiles                                                                                                                                                   
    if rundebug:
        file_debug.write("enfiles*xpectedjobtime = " + str(expectedjobtime) + "\n")


    #### If expectedjobtime is large then submit 10 or more jobs (as few as will be finihsed bfore longest jobs time)                                                                                       
    if expectedjobtime > 5000.:
        if not longestjobtime == expectedjobtime:
            for ix in range(10, 75):
                if float(expectedjobtime) < (float(ix)*float(longestjobtime)):
                    if rundebug:
                        file_debug.close()
                    return ix+isbusy_addon
            if rundebug:
                file_debug.close()
            return 25+isbusy_addon
        else:
            if rundebug:
                file_debug.close()
            return 50+isbusy_addon


    elif expectedjobtime > 3000.:

        for i in range(5, 15):
            if rundebug:
                file_debug.write("range " + str(i) + "\n")
            #### IF job will run in less than 10 minutes run max number of jobs                                                                                                                            \
                                                                                                                                                                                                            
            for ix in range(i, 15):
                if (float(expectedjobtime) / float(ix)) < longestjobtime:
                    if rundebug:
                        file_debug.write(str((float(expectedjobtime) / float(ix)))+"\n")
                        file_debug.write("ix = " + str(ix) +"\n")
                        file_debug.close()
                    return ix+isbusy_addon

    elif expectedjobtime > 600.:

        for i in range(2, 10):
            if rundebug:
                file_debug.write("range " + str(i) + "\n")
            #### IF job will run in less than 10 minutes run max number of jobs                                                                                                                            \
                                                                                                                                                                                                            
            for ix in range(i, 15):
                if (float(expectedjobtime) / float(ix)) < longestjobtime:
                    if rundebug:
                        file_debug.write(str((float(expectedjobtime) / float(ix)))+"\n")
                        file_debug.write("ix = " + str(ix) +"\n")
                        file_debug.close()
                    return ix+isbusy_addon

    else:
        if rundebug:
            file_debug.close()
        return 2
    if rundebug:
        file_debug.write("After expectedtime \n")

    if expectedjobtime > 1.:
        if not longestjobtime == expectedjobtime:
            for ix in range(2, 25):
                if float(expectedjobtime) < (float(ix)*float(longestjobtime)):
                    if rundebug:
                        file_debug.close()
                    return ix
            if rundebug:
                file_debug.close()
            return 25
        else:
            if rundebug:
                file_debug.close()
            return 50

    else:
        pre_job_time=GetTime(defsample,defcycle,deftagger, defskim)
        if pre_job_time == "None":
            pre_job_time=100.
        njobs_max=50
        if float(pre_job_time) < 100.:
            njobs_max=50
        elif float(pre_job_time) < 200.:
            njobs_max=25
        elif float(pre_job_time) < 300.:
            njobs_max=20
        elif float(pre_job_time) < 500.:
            njobs_max=15
        elif float(pre_job_time) < 1000.:
            njobs_max=10
        elif float(pre_job_time) < 1500.:
            njobs_max=5
        else:
            njobs_max=5
        if rundebug:
            file_debug.close()
        return njobs_max



def CheckJobHistory(info_type, defsample, defcycle, tagger,defskim):


    if "ui" in str(os.getenv("HOSTNAME")):
        if info_type == "MemoryV":
            return "None"
        if info_type == "MemoryP":
            return "None"
        if info_type == "Time":
            return "0."
        if info_type == "FileSize":
            return "0."


    if "FLATCAT" in defskim:
        defsample +="_lepton"
    if "SKTree_LeptonSkim" in defskim:
        defsample +="_lepton"
    if "SKTree_DiLepSkim"in defskim:
        defsample +="_dilepton"
    if "SKTree_HNDiLepSkim"in defskim:
        defsample +="_hndilepton"
    if "SKTree_HNFakeSkim"in defskim:
        defsample +="_hnfake"
    if "SKTree_HNFatJetSkim"in defskim:
        defsample +="_hnfatjet"

    if "SKTree_TriLepSkim"in defskim:
        defsample +="_trilepton"
    if "SKTree_NoSkim" in defskim:
        defsample +="_nocut"

        
    

    jobline=""
    list_tags=GetList()

    itag=-1
    while not jobline:
        itag=itag+1
        cattag=list_tags[itag]
        newformat=NewForat(cattag)

        #info_file_master = path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_"+ os.getenv("CATVERSION")+".txt"                                                              
        info_file= path_jobpre+"/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/" + os.getenv("USER") + "/PreMasterFile_"+os.getenv("CATVERSION")+ str(tagger)+".txt"

        #os.system("cp " + info_file_master + " " + info_file)                                                                                                                                              
        read_info_file = open(info_file,"r")
        isuser=False
        iscycle=False
        jobline=""
        for infoline in read_info_file:
            if "USER" in infoline:
                if  os.getenv("USER") in infoline:
                    isuser=True
                else:
                    isuser=False
            if isuser:
                if "Code:" in infoline and defcycle in infoline:
                    iscycle=True
                if "Code:" in infoline and not defcycle in infoline:
                    iscycle=False
                if iscycle:
                    if defsample in infoline:
                        if cattag in infoline:
                            jobline=infoline
        read_info_file.close()
        if itag == (len(list_tags) - 1):
            if not jobline:
                jobline="None"
    if jobline == "None":
        return "None"

    sinfoline = jobline.split()
    if newformat:
        if len(sinfoline) == 7:
            if info_type == "MemoryV":
                return sinfoline[5]
            if info_type == "MemoryP":
                return sinfoline[6]
            if info_type == "Time":
                return sinfoline[3]
            if info_type == "FileSize":
                return sinfoline[4]

    else:
        if len(sinfoline) == 5:
            if info_type == "MemoryV":
                return "None"
            if info_type == "MemoryP":
                return "None"
            if info_type == "Time":
                return sinfoline[3]
            if info_type == "FileSize":
                return sinfoline[4]

    return "None"


def GetVirtualMemoryUsage(defsample, defcycle,tagger,defskim):
    return CheckJobHistory("MemoryV", defsample, defcycle, tagger,defskim)

def GetPhysicalMemoryUsage(defsample, defcycle, tagger,defskim):
    return CheckJobHistory("MemoryP", defsample, defcycle, tagger,defskim)

def GetTime(defsample, defcycle, tagger,defskim):
    return CheckJobHistory("Time", defsample, defcycle, tagger,defskim)

def GetFileSize(defsample, defcycle,tagger,defskim):
    return CheckJobHistory("FileSize", defsample, defcycle,tagger,defskim)



def SedEmail(jobsummary, deftagger, e_subject, email_user, sendplots, plotlist):

    if not  os.getenv("USER") == "jalmond":
        if "jalmond" in email_user:
            print "Email could not be set since email address is not set correctly in bin/catconfig."
            return

    plotstring =""
    for x in plotlist:
        plotstring = plotstring+" -a " + x + " "


    an_jobpre="/data2/"   ####  pre-path for job output                                                                                                                                                    
    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        an_jonpre="/cms/scratch/SNU/CATAnalyzer/"


    path_file_email=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(deftagger)+"/email.sh"
    file_email=open(path_file_email,"w")
    if not sendplots:
        file_email.write('cat '+an_jonpre+'/CAT_SKTreeOutput/' + os.getenv("USER")  + '/CLUSTERLOG' + str(deftagger) + '/email.txt | mail -s "Job summary for job ' + str(deftagger) + " " + e_subject + '" '+str(email_user)+'')
    else:
        file_email.write('cat '+an_jonpre+'/CAT_SKTreeOutput/' + os.getenv("USER")  + '/CLUSTERLOG' + str(deftagger) + '/email.txt | mail  '+ plotstring+' -s "Job summary for job ' + str(deftagger) + " " + e_subject + '" '+str(email_user)+'')
    file_email.close()

    filejobsummary = open(an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(deftagger)+"/email.txt","w")
    for eline in jobsummary:
        filejobsummary.write(eline)
    filejobsummary.close()
    os.system("source " + path_file_email)


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
    return crashmessage

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
    elif defskim == "SKTree_HNDiLepSkim":
        defskim="HNDiLep"
    elif defskim == "SKTree_HNFakeSkim":
        defskim="HNFake"
    elif defskim == "SKTree_HNFatJetSkim":
        defskim="HNFatJet"

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
                    if defskim == "HNDiLep":
                        defchannel="SK" + defchannel + "_hndilep"
                    else:
                        if defskim == "HNFake":
                            defchannel="SK" + defchannel + "_hnfake"
                        else:
                            if defskim == "HNFatJet":
                                defchannel="SK" + defchannel + "_hnfatjet"
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
                    if defskim == "HNDiLep":
                        defsample="SK" + defsample + "_hndilep"

                    else:
                        if defskim == "HNFake":
                            defsample="SK" + defsample + "_hnfake"
                        else:
                            if defskim == "HNFatJet":
                                defsample="SK" + defsample + "_hnfatjet"
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

def GetOutFileName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle, mergedname):
    tmpname= GetPartualName(defskim, ismc , defsample, defrunnp, defruncf, defchannel ,defcycle)
    outsamplename=""
    if ismc:
        outsamplename=  defcycle +"_"+tmpname + ".root"
    elif defrunnp == "True":
        output_catversion=str(os.getenv("CATVERSION"))
        skimtag=""
        if defskim == "DiLep":
            skimtag= "_dilep"
        elif defskim == "HNDiLep":
            skimtag= "_hndilep"
        elif defskim == "HNFake":
            skimtag= "_hnfake"
        elif defskim == "HNFatJet":
            skimtag= "_hnfatjet"

        elif defskim == "TriLep":
            skimtag= "_trilep"
        elif defskim == "NoCut":
            skimtag= "_nocut"
        outsamplename=  defcycle + "_" + defchannel + "_SKnonprompt"+skimtag+ "_cat_" +  str(output_catversion)+ ".root"
        if not mergedname:
            outsamplename=  defcycle + tmpname + ".root"

    elif defruncf == "True":
        output_catversion=str(os.getenv("CATVERSION"))
        skimtag=""
        if defskim == "DiLep":
            skimtag= "_dilep"
        elif defskim == "HNDiLep":
            skimtag= "_hndilep"
        elif defskim == "HNFake":
            skimtag= "_hnfake"
        elif defskim == "HNFatJet":
            skimtag= "_hnfatjet"
        elif defskim == "TriLep":
            skimtag= "_trilep"
        elif defskim == "NoCut":
            skimtag= "_nocut"
        outsamplename=  defcycle + "_" + defchannel + "SKchargeflip_"+skimtag+ "_cat_" +  str(output_catversion)+ ".root"
        if not mergedname:
            outsamplename=  defcycle + tmpname + ".root"


    else:
        output_catversion=str(os.getenv("CATVERSION"))
        outsamplename=  defcycle +"_data_"+ defchannel + "_cat_" +  str(output_catversion)+ ".root"
        if not  mergedname:
            outsamplename=defcycle +"_"+tmpname + ".root"


    an_jobpre="/data2/"   ####  pre-path for job output                                                                                                                                                    
    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        an_jonpre="/cms/scratch/SNU/CATAnalyzer/"



    if "SKTreeMaker" in defcycle:
        if ismc:
            if defskim == "DiLep":
                return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MCTriLep/"+defsample+"/"

            elif "FatJet" in defcycle:
                return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MCHNFatJet/"+defsample+"/"

            elif "Fake" in defcycle:
                return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MCHNFake/"+defsample+"/"

            elif defskim == "Lepton":
                return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MCDiLep/"+defsample+"/"
            else:
                if defcycle == "SKTreeMakerNoCut":
                    return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MCNoCut/"+defsample+"/"
                else:
                    return an_jonpre+"/CatNtuples/"+str(os.getenv("CATVERSION"))+"/SKTrees/MC/"+defsample+"/"

    return outsamplename

def LargeFileSize(fsize,large_file_size):
    sfilesize=str(fsize)
    string_length= len(sfilesize)
    float_only_fsize= sfilesize[:-1]
    unit_only_fsize=  sfilesize[(int(string_length) - 1):]
    if unit_only_fsize == "G":
        return True
    if  unit_only_fsize == "M":
        if float(float_only_fsize)> large_file_size:
            return True
    return False

def FileSizeInB(fsize):
    unit_remove=1
    if "B" in str(fsize):
        unit_remove=2
    sfilesize=str(fsize)
    string_length= len(sfilesize)
    float_only_fsize= sfilesize[:-unit_remove]
    unit_only_fsize=  sfilesize[(int(string_length) - unit_remove):]

    if "K" in  unit_only_fsize:
        return float(float_only_fsize)*1000.
    elif "M" in  unit_only_fsize:
        return float(float_only_fsize)*1000000.
    elif "G" in  unit_only_fsize:
        return float(float_only_fsize)*1000000000.
    else:
        return float(float_only_fsize)

def LargeFileSizeIncrease(fsize,defsample, defcycle, tagger,defskim,file_increase_warning):

    if GetFileSize(defsample, defcycle,tagger,defskim) == "None":
        return False
    file_size_prev=   FileSizeInB(GetFileSize(defsample, defcycle, tagger,defskim))
    file_size = FileSizeInB(fsize)
    if file_size > file_increase_warning*file_size_prev:
        return True
    else:
        return False


def TimeIncrease(stime,defsample, defcycle, tagger,defskim,time_increase_warning):
    time_prev=GetTime(defsample, defcycle, tagger,defskim)
    if time_prev == "None":
        return False

    if float(stime) > float(time_prev)*time_increase_warning:
        if float(stime) < 30.:
            ##### if time is small this can be an issue with machine not code                                                                                                                               
            return False
        else:
            return True
    else:
        return False


def LargeMemory(mem,large_memory_check):
    if "GB" in str(mem):
        return True

    smem=str(mem)
    string_length= len(smem)
    float_only_mem= smem[:-2]
    if "MB" in smem:
        if float(float_only_mem) > large_memory_check:
            return True
    else:
        return False


def LargePhysicalMemoryIncrease(mem,defsample, defcycle, tagger,defskim):

    if GetPhysicalMemoryUsage(defsample, defcycle, tagger,defskim) == "None":
        return False

    if not "MB" in str(mem):
        return False
    smem=str(mem)
    string_length= len(smem)
    float_only_mem= smem[:-2]
    unit_only_mem=  smem[(int(string_length)-2):]

    rounded_float= str(round(float(float_only_mem),2))
    if unit_only_mem == "MB":
        if float(float_only_mem)  < 300:
            if (float(float_only_mem)*1000.) > FileSizeInB(GetPhysicalMemoryUsage(defsample, defcycle, tagger,defskim))*1.4:
                return True
            else:
                return False
        else:
             if (float(float_only_mem)*1000.)  > FileSizeInB(GetPhysicalMemoryUsage(defsample, defcycle, tagger,defskim))*1.3:
                 return True
             else:
                 return False
    return False




def LargeVirtualMemoryIncrease(mem,defsample, defcycle, tagger,defskim):

    if GetVirtualMemoryUsage(defsample, defcycle,tagger,defskim) == "None":
        return False
    if not "MB" in str(mem):
        return False
    smem=str(mem)
    string_length= len(smem)
    float_only_mem= smem[:-2]
    unit_only_mem=  smem[(int(string_length)-2):]

    rounded_float= str(round(float(float_only_mem),2))
    if unit_only_mem == "MB":
        if float(float_only_mem) < 300:
            if (float(float_only_mem)*1000.) > (FileSizeInB(GetVirtualMemoryUsage(defsample, defcycle, tagger,defskim))*1.4):
                return True
            else:
                return False
        else:
             if (float(float_only_mem)*1000.) > ((FileSizeInB(GetVirtualMemoryUsage(defsample, defcycle,tagger,defskim))*1.3)):
                 return True
             else:
                 return False
    return False


def CheckRunningStatus(check_crashfile):
    if not os.path.exists(check_crashfile):
        return
    file_check_crashfile=open(check_crashfile,"r")
    for line in file_check_crashfile:
        if " No such file or directory:" in line:
            print line
            sys.exit()
        if "is not defined" in line:
            print line
            sys.exit()
        if "SyntaxError: invalid syntax" in line:
            print line
            sys.exit()
    file_check_crashfile.close()
    return

def RoundMemory(mem):
    if not "MB" in str(mem):
        return str(mem)
    smem=str(mem)
    string_length= len(smem)
    float_only_mem= smem[:-2]
    unit_only_mem=  smem[(int(string_length)-2):]

    rounded_float= str(round(float(float_only_mem),2)) + unit_only_mem
    return rounded_float

def GetRunning(tagger, rsample):
    jobid_exists=True


    an_jobpre="/data2/"   ####  pre-path for job output                                                                                                                                                    
    isKisti = ("ui" in str(os.getenv("HOSTNAME")))

    if isKisti:
        an_jonpre="/cms/scratch/SNU/CATAnalyzer/"


    while jobid_exists:
        path_job_check=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + rsample + "jobid.txt"
        if  os.path.exists(path_job_check):
            jobid_exists=False


    file_job_check=open(path_job_check ,"r")
    jobid1=0
    jobid2=0

    njobs_finished=0.
    nrunning=0.
    nqueue=0.
    njobs_in_total=0.  ### should equal three above                                                                                                                                                        \
                                                                                                                                                                                                            
    path_clust_check=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + rsample + "clust_gr.txt"

    if not isKisti:
        os.system("qstat -u " + os.getenv("USER") + " > " +  path_clust_check)
    else:
        os.system("condor_q  " + os.getenv("USER") + " > " +  path_clust_check)


    ijob=0

    for sline in file_job_check:
        ssline = sline.split()
        if len(ssline) < 1:
            continue
        line=ssline[0]
        if jobid1 == 0:
            jobid1=line
        jobid2=line
        if  isKisti:
            jobid1 = 1
            jobid2 = 1

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
    path_clust_check=an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER")  + "/CLUSTERLOG" + str(tagger)+ "/" + rsample + "clust_gr.txt"
    os.system("rm " + path_clust_check)

    if njobs_in_total == 0:
        return 0.
    file_job_check.close()

    nrunning = nrunning + njobs_finished
    nrun_per = round( (nrunning/float(njobs_in_total)), 2)

    return nrun_per



def  SKIMNAME(useskim):
    skim_print=useskim
    if useskim == "SKTree_LeptonSkim":
        skim_print ="Lepton   "
    elif useskim == "SKTree_DiLepSkim":
        skim_print="DiLep. "
    elif useskim == "SKTree_HNDiLepSkim":
        skim_print="HNDiLep. "
    elif useskim == "SKTree_HNFake":
        skim_print="HNFake. "
    elif useskim == "SKTree_HNFatJet":
        skim_print="HNFatJet. "

    elif useskim == "SKTree_TriLepSkim":
        skim_print="TriLep. "
    elif useskim == "SKTree_NoSkim":
        skim_print="NoCut  "

    return skim_print


def Printuseskinput(cycle, useskinput):
    if not cycle == "SKTreeMaker":
        if not cycle == "SKTreeMakerNoCut":
            if not cycle == "SKTreeMakerDiLep":
                if not cycle == "SKTreeMakerFake":
                    if not cycle == "SKTreeMakerHNFatJet":
                        if not cycle == "SKTreeMakerHNDiLep":
                            if not useskinput == "True":
                                if not useskinput == "true":
                                    print "You are running on FlatCATntuples. This will be more cpu extensive. This is only advisable if you are testing some new branches NOT in SKTrees."
                                    
