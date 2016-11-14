import os,sys

def GetListOfDataSets(catversion):
    
    dlist=[]
    path_datasetlist="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/datasets_"+str(catversion)+"/"
    path_user_datasetlist="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/" + os.getenv("USER")
    if not os.path.exists(path_user_datasetlist):
        os.system("mkdir " + path_user_datasetlist)
        
    current_list=path_user_datasetlist+"/"+str(catversion)+"list.txt"    
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
    


catversion=str(os.getenv("CATVERSION"))
datasetlist=GetListOfDataSets(catversion)

path_full_sample_list_user="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/" + os.getenv("USER")+"/cattuplist_"+catversion+ os.getenv("USER")+".txt"

if not os.path.exists("/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/" + os.getenv("USER")):
    os.system("mkdir " + "/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/" + os.getenv("USER"))


if os.path.exists(path_full_sample_list_user):
    os.system("rm " +path_full_sample_list_user)

cdatasetlist=[]
cnamelist=[]

file_full_sample_list = open(path_full_sample_list_user,"w")

for x in datasetlist:
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

        if "xsec" in line:
            if len(sline) == 4:
                xsec= float(sline[3])
    file_sample_configfile.close()

    orig_datasetname=datasetname
    part_datasetname=  datasetname

    if "/" in datasetname:
        datasetname=datasetname.replace("/"," " )
        datasetname_split= datasetname.split()
        if len(datasetname_split) > 0:
            part_datasetname= datasetname_split[0]

    if not datasetname:
        print "Dataset name could not be determined for file " + x
        sys.exit()
    if not name:
        print "Alias not found in file " + x
        sys.exit()

    if isMC:    
        if not xsec:
            print "xsec could not be deterined for file " + x
            #if not "kskovpen" in line:
            #    sys.exit()
       
        for xd in  cdatasetlist:
            if part_datasetname == xd:
                print "This has the same dataset name as a previous file. Fix..."
                sys.exit()
        for xd in  cnamelist:
            if name == xd:
                print "This has the same alias name as a previous file. Fix..."
                print name
                sys.exit()
        cdatasetlist.append(part_datasetname)
        cnamelist.append(name)
        file_full_sample_list.write(name + " " + part_datasetname + " " + str(xsec)+ " " + orig_datasetname+"\n")
    #else:
        #file_full_sample_list.write(name + " " + part_datasetname + " " + datasetname + "\n")


#file_full_sample_list.write("END")
file_full_sample_list.close()

print "Latest file for datasets --> " + path_full_sample_list_user




