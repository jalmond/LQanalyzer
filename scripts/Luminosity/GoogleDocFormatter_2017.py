import os,sys

def GetListOfDataSets(sample_type):
    
    dlist=[]
    
    if sample_type == "mc":
        url = 'https://docs.google.com/spreadsheets/d/e/2PACX-1vTWct60gAWZoN7tmVAw_WJmQmDWdrpXluF1xz8cn4sL8NCll3Vb8ppN2254P10zmnZ_oqF1f8XSHuav/pub?gid=1688046080&single=true&output=csv'


    if sample_type == "signal":
        url = 'https://docs.google.com/spreadsheets/d/e/2PACX-1vTWct60gAWZoN7tmVAw_WJmQmDWdrpXluF1xz8cn4sL8NCll3Vb8ppN2254P10zmnZ_oqF1f8XSHuav/pub?gid=602011091&single=true&output=csv'
    
    import csv

    from urllib import urlopen

    cr = csv.reader(urlopen(url).readlines())
    for row in cr:
        if row[0] == "END":
            return dlist
        if not row[0] == "User":
            if len(row) > 3:
                len_alias = len(row[1])
                len_dn = len(row[2])
                len_xsec = len(row[3])
                len_1 = 30 - len_alias
                len_2 = 180 - len_dn
                len_3 = 10 - len_xsec
                #print "[Alias,dataset,xsec]: " + row[1]+ " "*len_1+ row[2] +" "*len_2 +row[3]
                print "[Alias,dataset,xsec]: " + row[1]+ " "+ row[2] +" " +row[3]                                                                                                              
                if row[0] == "":
                    dlist.append([row[1],row[2],row[3],"jalmond"])
                else:
                    dlist.append([row[1],row[2],row[3],row[0]])
                

                
        
    return dlist
    


#### what is path of mc cattuples                                                                                                                                                                

datasetlist=GetListOfDataSets("mc")
#datasetlist_signal=GetListOfDataSets(catversion,"signal")
datasetlist_signal=[]
#datasetlist=datasetlist+datasetlist_signal

sk_version="SKFlat_v949cand2_1/"

path_full_sample_list_user=os.getenv("LQANALYZER_DATASET_DIR") + "/" + os.getenv("USER")+"/skflat_"+os.getenv("USER")+".txt"

if not os.path.exists(os.getenv("LQANALYZER_DATASET_DIR") + "/" + os.getenv("USER")):
    os.system("mkdir " + os.getenv("LQANALYZER_DATASET_DIR") + "/"  + os.getenv("USER"))


if os.path.exists(path_full_sample_list_user):
    os.system("rm " +path_full_sample_list_user)

cdatasetlist=[]
cnamelist=[]
user_list=[]
file_full_sample_list = open(path_full_sample_list_user,"w")

tamsa_list=[]
missing_sample=[]
for x in datasetlist:
    
    if x == ['','','','']:
        continue
    datasetname=x[1]
    xsec=x[2]
    name=x[0]
    user = x[3]
    cattuple_path="/xrootd/store/user/"+user+"/SKFlat/2017/"

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

    tag=""
    os.system("ls -lth  " + cattuple_path+"/"+part_datasetname +"/"+ sk_version+"/>> log1.txt" )  
    readlog1 = open("log1.txt","r")
    for line in readlog1:
        if "geonmo" in line:
            sline = line.split()
            if len(sline) == 9:
                tag=sline[8]
    readlog1.close()
    os.system("rm log1.txt")
    
    if not os.path.exists(cattuple_path+"/"+part_datasetname +"/"+ sk_version+ "/"+tag):
        print "##### missing "
        missing_sample.append(part_datasetname)
    else:
        file_full_sample_list.write(name + " " + part_datasetname + " " + str(xsec)+ " " + orig_datasetname+ " " + user+"\n")
        print cattuple_path+"/"+ part_datasetname +"/"+ sk_version +tag
    if not  user in user_list:
        user_list.append(user)
        

print " "
print "Tamsa list:"
for x in tamsa_list:
    print x

for x in user_list: 
    os.system("du -hsc "  + cattuple_path +"/"+part_datasetname +"/"+ sk_version+"/* > " + user + "_list.txt") 
    print "du -hsc "  + cattuple_path +"/"+part_datasetname +"/"+ sk_version+"/* > " + user + "_list.txt"

nsample_it=0
for x in datasetlist:

    if x == ['','','','']:
        continue
    datasetname=x[1]
    xsec=x[2]
    name=x[0]
    user = x[3]
    cattuple_path="/xrootd/store/user/"+user+"/SKFlat/2017/"

    orig_datasetname=datasetname
    part_datasetname=  datasetname

    if "/" in datasetname:
        datasetname=datasetname.replace("/"," " )
        datasetname_split= datasetname.split()
        if len(datasetname_split) > 0:
            part_datasetname= datasetname_split[0]


    if not os.path.exists(cattuple_path+"/"+part_datasetname):
        print "0.00"
    else:
        for line in open(user + "_list.txt", 'r'):
            if part_datasetname in line:
                sline = line.split()
                print sline[0]
    
    if nsample_it == len(datasetlist)-len(datasetlist_signal)-1:
        print "-"*50

    nsample_it=nsample_it+1

#file_full_sample_list.write("END")
file_full_sample_list.close()

print "samples that are missing are"
for x in missing_sample:
    print x

print "Latest file for datasets --> " + path_full_sample_list_user




