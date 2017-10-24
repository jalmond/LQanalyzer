import os


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="",help="tag")
parser.add_option("-y", "--y", dest="y", default="",help="tag")
parser.add_option("-z", "--z", dest="z", default="",help="tag")

(options, args) = parser.parse_args()
list_master=options.x
list_sig=options.y
list_nonsig=options.z


if list_master=="":
    list_master ="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_CAT_mc_v8-0-7.txt"
    list_sig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_sig_CAT_mc_v8-0-7.txt"
    list_nonsig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_nonsig_CAT_mc_v8-0-7.txt"

arr_master=[]
arr_sig=[]
arr_nonsig=[]
r_list_master=open(list_master,"r")
for line in r_list_master:
    arr_master.append(line)
r_list_master.close()


r_list_sig=open(list_sig,"r")
for line in r_list_sig:
    arr_sig.append(line)
r_list_sig.close()

missing_sig=[]
missing_nonsig=[]
r_list_nonsig=open(list_nonsig,"r")
for line in r_list_nonsig:
    arr_nonsig.append(line)
r_list_nonsig.close()

for r in arr_master:
    found=False
    rsplit = r.split()
    if "#" in r:
        continue
    if len(rsplit) == 0:
        continue

    sig=False
    isnonsig = "hndilep" in r or "hnfake"  in r
    if isnonsig:
        if "SKHN" in r:
            isnonsig=False
    
    if "HN" in r and not isnonsig  or "TTTo" in rsplit[0] or "CHToCB" in rsplit[0]:
        sig=True
        for r2 in arr_sig:
            r2split = r2.split()
            if "#" in r2:
                continue
            if len(r2split) == 0:
                continue
    else:
        for r3 in arr_nonsig:
            r3split = r3.split()
            if "#" in r3:
                continue
            if len(r3split) == 0:
                continue

    if not found:                
        if sig:
            missing_sig.append(r)
        else:
            missing_nonsig.append(r)



newlist_sig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_sig_CAT_mc_v8-0-7new.txt"
newlist_nonsig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_nonsig_CAT_mc_v8-0-7new.txt"

r_newlist_sig=open(newlist_sig,"w")
r_newlist_nonsig=open(newlist_nonsig,"w")

arr_flat=[]
arr_lep=[]
arr_dilep=[]
arr_trilep=[]
arr_hnfake=[]
arr_hndilep=[]
for s in missing_sig:
    if not "SK" in s:
        arr_flat.append(s)
    elif "_dilep" in s:
        arr_dilep.append(s)
    elif "_trilep" in s:
        arr_trilep.append(s)
    elif "_hndilep" in s:
        arr_hndilep.append(s)
    elif "_hnfake" in s:
        arr_hnfake.append(s)
    else:
      arr_lep.append(s)


for sa in arr_sig:
    if "#" in sa:
        r_newlist_sig.write(sa)
    if "CATTuples" in sa:
        for sf in arr_flat:
            r_newlist_sig.write(sf)
    if "### Single_lepton_skims:_SKTrees" in sa:
        for sf in arr_lep:
            r_newlist_sig.write(sf)
    if "#### Dilepton_skims:_SKTrees" in sa:
        for sf in arr_dilep:
            r_newlist_sig.write(sf)
    if "#### Trilepton_skims:_SKTrees" in sa:
        for sf in arr_trilep:
            r_newlist_sig.write(sf)
    
    if "#### HNFake skims: SKTrres" in sa:
        for sf in arr_hnfake:
            r_newlist_sig.write(sf)
    if "## HNDiLep skims: SKTrees" in sa:
        for sf in arr_hndilep:
            r_newlist_sig.write(sf)

r_newlist_sig.close()
    
arrns_flat=[]
arrns_lep=[]
arrns_dilep=[]
arrns_trilep=[]
arrns_hnfake=[]
arrns_hndilep=[]
for s in missing_nonsig:
    if not "SK" in s:
        arrns_flat.append(s)
    elif "_dilep" in s:
        arrns_dilep.append(s)
    elif "_trilep" in s:
        arrns_trilep.append(s)
    elif "_hndilep" in s:
        arrns_hndilep.append(s)
    elif "_hnfake" in s:
        arrns_hnfake.append(s)
    else:
        arrns_lep.append(s)

for sa in arr_nonsig:
    if "#" in sa:
        r_newlist_nonsig.write(sa)
    if "CATTuples" in sa:
        for sf in arrns_flat:
            if "/data" in sf:
                r_newlist_nonsig.write(sf)
    if "### Single_lepton_skims:_SKTrees" in sa:
        for sf in arrns_lep:
            r_newlist_nonsig.write(sf)
    if "#### Dilepton_skims:_SKTrees" in sa:
        for sf in arrns_dilep:
            r_newlist_nonsig.write(sf)
    if "#### Trilepton_skims:_SKTrees" in sa:
        for sf in arrns_trilep:
            r_newlist_nonsig.write(sf)

    if "#### HNFake skims: SKTrres" in sa:
        for sf in arrns_hnfake:
            r_newlist_nonsig.write(sf)
    if "## HNDiLep skims: SKTrees" in sa:
        for sf in arrns_hndilep:
            r_newlist_nonsig.write(sf)


r_newlist_nonsig.close()

for s in arrns_flat:
    print s


mainlist_sig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_sig_CAT_mc_v8-0-7.txt"
mainlist_nonsig="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/datasets_snu_nonsig_CAT_mc_v8-0-7.txt"

print "Change in " + mainlist_sig +":"
os.system("diff " + mainlist_sig + " " + newlist_sig)
print " "*20
print "Change in " + mainlist_nonsig +":"
os.system("diff " + mainlist_nonsig + " " + newlist_nonsig)

os.system("cp " + newlist_sig + " " + mainlist_sig)
os.system("cp " + newlist_nonsig + " " + mainlist_nonsig)
