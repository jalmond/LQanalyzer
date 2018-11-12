import os,sys
import ROOT
        
def GetListOfDataSets(catversion, sample_type):
    
    dlist=[]
    
    if sample_type == "mc":
        url = 'https://docs.google.com/spreadsheets/d/e/2PACX-1vTWct60gAWZoN7tmVAw_WJmQmDWdrpXluF1xz8cn4sL8NCll3Vb8ppN2254P10zmnZ_oqF1f8XSHuav/pub?gid=238920808&single=true&output=csv'
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
                print "[Alias,dataset,xsec]: " + row[1]+ " "*len_1+ row[2] +" "*len_2 +row[3]
                
                if row[0] == "":
                    dlist.append([row[1],row[2],row[3],"jalmond"])
                else:
                    dlist.append([row[1],row[2],row[3],row[0]])
                

                
        
    return dlist
    


#### what is path of mc cattuples                                                                                                                                                                
catversion=str(os.getenv("CATVERSION"))

datasetlist=GetListOfDataSets(catversion,"mc")
datasetlist_signal=GetListOfDataSets(catversion,"signal")

datasetlist=datasetlist+datasetlist_signal

path_full_sample_list_user=os.getenv("LQANALYZER_DATASET_DIR") + "/" + os.getenv("USER")+"/cattuplist_"+catversion+ os.getenv("USER")+".txt"

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
    cattuple_path="/xrootd/store/user/"+user+"/cattoflat/MC/"+catversion

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

    if not os.path.exists(cattuple_path+"/"+part_datasetname):
        print "##### missing "
        missing_sample.append(part_datasetname)
    else:
        file_full_sample_list.write(name + " " + part_datasetname + " " + str(xsec)+ " " + orig_datasetname+ " " + user+"\n")
        print cattuple_path+"/"+part_datasetname

        os.system("ls " + cattuple_path+"/"+part_datasetname  + "/* > check.txt")

        check_log = open("check.txt", "r")

        for line in  check_log:
            if "SNU_v8-0-8" in line:
                print line
                os.system("rm " + cattuple_path+"/"+part_datasetname + "/*.root")
                os.system("mv " + cattuple_path+"/"+part_datasetname + "/*/*.root " +  cattuple_path+"/"+part_datasetname+"/")
                os.system("rm -rf "+ cattuple_path+"/"+part_datasetname + "/SNU*")

        check_log.close()
        continue
        
        check_log = open("check.txt", "r")
        for line in  check_log:
                s=line.split()
                if len(s) == 0:
                    continue
                s=s[0]

                if ".root" in line:
                        f = ROOT.TFile(s)
                        if f.IsZombie() :
                                print "Error " + line
                        elif not f:
                                print "Error " + line
                        elif f.TestBit(ROOT.TFile.kRecovered):
                                print "Error " + line


        check_log.close()
                                
        os.system("rm check.txt")
        tamsa_list.append("/data2/DATA/cattoflat/MC/"+str(os.getenv("CATVERSION"))+"/"+part_datasetname)
    if not  user in user_list:
        user_list.append(user)
        

print " "
print "Tamsa list:"
for x in tamsa_list:
    print x

for x in user_list: 
    os.system("du -hsc /xrootd/store/user/"+x+"/cattoflat/MC/"+str(os.getenv("CATVERSION"))+"/* > " + user + "_list.txt") 




nsample_it=0
for x in datasetlist:

    if x == ['','','','']:
        continue
    datasetname=x[1]
    xsec=x[2]
    name=x[0]
    user = x[3]
    cattuple_path="/xrootd/store/user/"+user+"/cattoflat/MC/"+catversion

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




