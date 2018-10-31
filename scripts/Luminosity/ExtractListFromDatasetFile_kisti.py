import os,sys

def GetListOfDataSets(catversion):
    
    dlist=[]

    url = 'https://docs.google.com/spreadsheets/d/e/2PACX-1vTWct60gAWZoN7tmVAw_WJmQmDWdrpXluF1xz8cn4sL8NCll3Vb8ppN2254P10zmnZ_oqF1f8XSHuav/pub?gid=238920808&single=true&output=csv'
    
    import csv

    from urllib import urlopen

    cr = csv.reader(urlopen(url).readlines())
    for row in cr:
        if row[0] == "END":
            return dlist
        if not row[0] == "Name":
            if len(row) > 2:
                len_alias = len(row[0])
                len_dn = len(row[1])
                len_xsec = len(row[2])
                len_1 = 30 - len_alias
                len_2 = 180 - len_dn
                len_3 = 10 - len_xsec
                print "[Alias,dataset,xsec]: " + row[0]+ " "*len_1+ row[1] +" "*len_2 +row[2]
                if len(row) > 7:
                    dlist.append([row[0],row[1],row[2],row[7]])
                else:
                    dlist.append([row[0],row[1],row[2],"jalmond"])

        
    return dlist
    


catversion=str(os.getenv("CATVERSION"))
datasetlist=GetListOfDataSets(catversion)


path_full_sample_list_user=os.getenv("LQANALYZER_DATASET_DIR") + "/" + os.getenv("USER")+"/cattuplist_"+catversion+ os.getenv("USER")+".txt"

if not os.path.exists(os.getenv("LQANALYZER_DATASET_DIR") + "/" + os.getenv("USER")):
    os.system("mkdir " + os.getenv("LQANALYZER_DATASET_DIR") + "/"  + os.getenv("USER"))


if os.path.exists(path_full_sample_list_user):
    os.system("rm " +path_full_sample_list_user)

cdatasetlist=[]
cnamelist=[]

file_full_sample_list = open(path_full_sample_list_user,"w")

for x in datasetlist:
    
    if x == ['','','','']:
        continue
    datasetname=x[1]
    xsec=x[2]
    name=x[0]
    user = x[3]
    orig_datasetname=datasetname
    part_datasetname=  datasetname

    if "/" in datasetname:
        datasetname=datasetname.replace("/"," " )
        datasetname_split= datasetname.split()
        if len(datasetname_split) > 0:
            part_datasetname= datasetname_split[0]


    if not datasetname:
        print "Dataset name could not be determined for file " + str(x)
        sys.exit()
    if not name:
        print "Alias not found in file " + str(x)
        sys.exit()

    if not os.path.exists("/xrootd_user/"+user+"/xrootd/cattoflat/MC/"+str(os.getenv("CATVERSION"))+"/"+part_datasetname):
        print "skipping " + "/xrootd_user/"+user+"/xrootd/cattoflat/MC/"+str(os.getenv("CATVERSION"))+"/"+part_datasetname
    else:
        file_full_sample_list.write(name + " " + part_datasetname + " " + str(xsec)+ " " + orig_datasetname+ " " + user+"\n")
        print name + " " + part_datasetname + " " + str(xsec)+ " " + orig_datasetname+ " " + user

#file_full_sample_list.write("END")
file_full_sample_list.close()

print "Latest file for datasets --> " + path_full_sample_list_user




