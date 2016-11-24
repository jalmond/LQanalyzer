import os,sys

def GetListOfDataSets(catversion):
    
    dlist=[]
    path_datasetlist="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/datasets_"+str(catversion)+"/"
    path_user_datasetlist="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/" + os.getenv("USER")
    if not os.path.exists(path_user_datasetlist):
        os.system("mkdir " + path_user_datasetlist)
        
    current_list=path_user_datasetlist+"/"+str(catversion)+"listskim.txt"    
    os.system("rm " + path_datasetlist + "/*~")
    os.system("ls " + path_datasetlist + " > " + current_list)
    file_current_list=open(current_list,"r")
    for line in file_current_list:
        splitline = line.split()
        if len(splitline) > 0:
            dlist.append(path_datasetlist+"/"+str(splitline[0]))
    file_current_list.close()
    os.system("rm " + current_list)
    return dlist
    

def GetList():
    vetolist=["TH_1L3B_Eta", "_Run201","scale","mtop","mpiOFF","alpha","ST_TH_1L3B","json","herwigpp","WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8","TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8","TT_TuneEE5C_13TeV-powheg-herwigpp","TT_TuneCUETP8M1noCR_13TeV-powheg-pythia8"]


    catversion=str(os.getenv("CATVERSION"))
    datasetlist=GetListOfDataSets(catversion)
    samplelist=[]


    for line in datasetlist:
        veto=False
        for x in vetolist:
            if x in line:
                veto=True
        if veto:
            continue
        samplelist.append(line)
        
        
    cdatasetlist=[]

    for x in samplelist:
        if "cattuplist_" in x:
            continue
        
        if "json" in x:
            continue

        if "~" in x:
            continue

        sample_configfile=x
        file_sample_configfile = open(sample_configfile,"r")
        datasetname=""
        xsec=0.
        colour=0
        name=""
        isMC = True
        if "Run2016" in x:
            isMC=False
            
        for line in file_sample_configfile:
            sline = line.split()
            if "name =" in line:
                if len(sline) == 4:
                    name=sline[3]
            if "DataSetName" in line:
                if len(sline) == 4:
                    
                    datasetname = sline[3]
                    if "/" in datasetname:
                        datasetname=datasetname.replace("/"," " )
                        datasetname_split= datasetname.split()
                        if len(datasetname_split) > 0:
                            part_datasetname= datasetname_split[0]
                            cdatasetlist.append(part_datasetname)
                    


    return cdatasetlist
