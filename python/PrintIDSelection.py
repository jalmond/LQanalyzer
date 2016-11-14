import os,sys


def PrintOutElectrons(ID, generalpath, userpath):

    path= "PrintOutElectrons.txt"
    file_master=open(path,"w")

    file_path=open(generalpath,"r")
    for line in file_path:
        file_master.write(line)
    file_path.close()

    file_userpath=open(userpath,"r")
    for line in file_userpath:
        if "ncut" in line or "webpage" in line or " ID " in line:
            continue
        file_master.write(line)
    file_userpath.close()
    file_master.close()

    IDexists=False
    file_path=open(path,"r")
    for line in file_path:
        sline = line.split()
        if len(sline) > 2:
            if sline[1] == ID:
                IDexists=True
    file_path.close()
     
    if not IDexists:
        print "ID [" + ID + "] does not exist use either:"
        file_path=open(path,"r")
        for line in file_path:
            sline =line.split()
            if len(sline) >2:
                if not sline[1] == "ID":
                    print sline[1]
        file_path.close()
        os.system("rm " + path)
        sys.exit()
        

    list_of_cut=[]
    ncut=0
    out_list=[]
    webpage=""
    file_path=open(path,"r")
    for line in file_path:
        if "ncut" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            ncut=sline[1]
        if "webpage" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            webpage=sline[1]
    
        if not "ID" in line:
            continue
        sline = line.split()
        nparts=2*int(ncut) + 3
        if not len(sline) == nparts:
            print "Error in " + path
            print "ncuts set wrong"
            sys.exit()
        for x in range(0,len(sline)):
            list_of_cut.append(sline[x])
        break
    file_path.close()


    print "*"*100
    file_path=open(path,"r")
    for line in file_path:
        if  "ID" in line:
            continue
        if not (ID+" ") in line:
            continue
        sline = line.split()
        for x in range(0,len(sline)):
            if "|" in  sline[x]:
                continue
            if "ID" in list_of_cut[x]:
                print list_of_cut[x] + "  :  " + sline[x]
                print "_"*len(list_of_cut[x] + "  :  " + sline[x])
                out_list.append(list_of_cut[x] + "  :  " + sline[x])
            elif "min" in list_of_cut[x]:
                print list_of_cut[x] + "  >  " + sline[x]
                out_list.append(list_of_cut[x] + "  >  " + sline[x])
            elif "true" in  sline[x] or "false" in  sline[x] :
                print list_of_cut[x] + "  = " + sline[x]
                out_list.append(list_of_cut[x] + "  = " + sline[x])
            else:
                print list_of_cut[x] + "  <  " + sline[x]
                out_list.append(list_of_cut[x] + "  <  " + sline[x])
    file_path.close()

    print "*"*100
    print "\n"
    os.system("curl https://github.com/vallot/CATTools/blob/"+os.getenv("CATVERSION")+"/CatProducer/python/electronProducer_cfi.py > log")

    
    print "*"*100
    print "\n"
    print "__________________________________________________________________________________"
    print "Twiki: " + webpage
    print "__________________________________________________________________________________"


    file_electron = open("log","r")
    for line in file_electron:
        if "cutBased" in line:
            if "loose" in line:
                print "loose = "+line[130:-48]
            if "medium" in line:
                print "medium = "+line[130:-48]
            if "tight" in line:
                print "tight = "+line[130:-48]
            if "veto" in line:
                print "veto = "+line[130:-48]
    file_electron.close()
    print "\n"
    print "*"*100
    print "POG ID cuts veto -> Tight applied in ElectronSelection.cc do not use the PATs POG definitions. "
    print "This is because pog ids apply dxy and isolation cuts which need relaxing for fake electrons."
    print "Objects use el.SNUID() not el.Tight()" 
    print "SNUID: 1111 = Tight"
    print "SNUID: 111  = Medium"
    print "SNUID: 11   = Loose"
    print "SNUID: 1    = Veto"
    os.system("rm log")
    os.system("rm " + path)
    return out_list



def PrintOutJets(ID,generalpath, userpath):
    
    path= "PrintOutJets.txt"
    file_master=open(path,"w")

    file_path=open(generalpath,"r")
    for line in file_path:
        file_master.write(line)
    file_path.close()

    file_userpath=open(userpath,"r")
    for line in file_userpath:
        if "ncut" in line or "webpage" in line or " ID " in line:
            continue
        file_master.write(line)
    file_userpath.close()
    file_master.close()

    IDexists=False
    file_path=open(path,"r")
    for line in file_path:
        sline = line.split()
        if len(sline) > 2:
            if sline[1] == ID:
                IDexists=True
    file_path.close()

    if not IDexists:
        print "ID [" + ID + "] does not exist use either:"
        file_path=open(path,"r")
        for line in file_path:
            sline =line.split()
            if len(sline) >2:
                if not sline[1] == "ID":
                    print sline[1]
        file_path.close()
        os.system("rm " + path)
        sys.exit()

    

    list_of_cut=[]
    out_list=[]
    ncut=0
    webpage=""
    file_path=open(path,"r")
    for line in file_path:
        if "ncut" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            ncut=sline[1]
        if "webpage" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            webpage=sline[1]

        if not "ID" in line:
            continue
        sline = line.split()
        nparts=2*int(ncut) + 3
        if not len(sline) == nparts:
            print "Error in " + path
            sys.exit()
        for x in range(0,len(sline)):
            list_of_cut.append(sline[x])
        break
    file_path.close()


    print "*"*100
    file_path=open(path,"r")
    for line in file_path:
        if  "ID" in line:
            continue
        if not (ID+" ") in line:
            continue
        sline = line.split()
        for x in range(0,len(sline)):
            if "|" in  sline[x]:
                continue
            if "ID" in list_of_cut[x]:
                print list_of_cut[x] + "  :  " + sline[x]
                out_list.append(list_of_cut[x] + "  :  " + sline[x])
            elif "min" in list_of_cut[x]:
                print list_of_cut[x] + "  >  " + sline[x]
                out_list.append(list_of_cut[x] + "  >  " + sline[x])
            elif "true" in  sline[x] or "false" in  sline[x] :
                print list_of_cut[x] + "  = " + sline[x]
                out_list.append(list_of_cut[x] + "  = " + sline[x])
            else:
                print list_of_cut[x] + "  <  " + sline[x]
                out_list.append(list_of_cut[x] + "  <  " + sline[x])
    file_path.close()

    print "__________________________________________________________________________________"
    print "Twiki: " + webpage
    print "__________________________________________________________________________________"
    os.system("rm " + path)
    return out_list
    
def PrintOutMuons(ID,generalpath, userpath):

    path= "PrintOutMuons.txt"
    file_master=open(path,"w")

    file_path=open(generalpath,"r")
    for line in file_path:
        file_master.write(line)
    file_path.close()

    file_userpath=open(userpath,"r")
    for line in file_userpath:
        if "ncut" in line or "webpage" in line or " ID " in line:
            continue
        file_master.write(line)
    file_userpath.close()
    file_master.close()
    
    IDexists=False
    file_path=open(path,"r")
    for line in file_path:
        sline = line.split()
        if len(sline) > 2:
            if sline[1] == ID:
                IDexists=True
    file_path.close()
    
    if not IDexists:
        print "ID [" + ID + "] does not exist use either:"
        file_path=open(path,"r")
        for line in file_path:
            sline =line.split()
            if len(sline) >2:
                if not sline[1] == "ID":  
                    print sline[1]
        file_path.close()
        os.system("rm " + path)
        sys.exit()

    list_of_cut=[]
    out_list=[]
    ncut=0
    webpage=""
    file_path=open(path,"r")
    for line in file_path:
        if "ncut" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            ncut=sline[1]
        if "webpage" in line:
            sline = line.split()
            if not len(sline) ==2:
                print "Error in " + path
                sys.exit()
            webpage=sline[1]


        if not "ID" in line:
            continue
        sline = line.split()
        nparts=2*int(ncut) + 3
        if not len(sline) == nparts:
            print "Error in " + path
            sys.exit()
        for x in range(0,len(sline)):
            list_of_cut.append(sline[x])
        break
    file_path.close()


    print "*"*100
    file_path=open(path,"r")
    for line in file_path:
        if  "ID" in line:
            continue
        if not (ID+" ") in line:
            continue
        sline = line.split()
        for x in range(0,len(sline)):
            if "|" in  sline[x]:
                continue
            if "ID" in list_of_cut[x]:
                print list_of_cut[x] + "  :  " + sline[x]
                out_list.append(list_of_cut[x] + "  :  " + sline[x])
            elif "min" in list_of_cut[x]:
                print list_of_cut[x] + "  >  " + sline[x]   
                out_list.append(list_of_cut[x] + "  >  " + sline[x])
            elif "true" in  sline[x] or "false" in  sline[x] :
                print list_of_cut[x] + "  = " + sline[x]
                out_list.append(list_of_cut[x] + "  = " + sline[x])
            else:
                print list_of_cut[x] + "  <  " + sline[x]
                out_list.append(list_of_cut[x] + "  <  " + sline[x])
    file_path.close()

    print "__________________________________________________________________________________"
    print "Twiki: " + webpage
    print "__________________________________________________________________________________"
    os.system("rm " + path)
    return out_list

muon_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/muons.sel"
electron_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/electrons.sel"
jet_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/jets.sel"


user_muon_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/user_muons.sel"
user_electron_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/user_electrons.sel"
user_jet_path_id=os.getenv("LQANALYZER_DIR")+"/CATConfig/SelectionConfig/user_jets.sel"


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-i", "--id1", dest="i", default="123",help="tag")
parser.add_option("-j", "--id2", dest="j", default="123",help="tag")

(options, args) = parser.parse_args()
id1=options.i
id2=options.j

if id1 == "123" and id2 == "123":
    print "no input given. "
    sys.exit()

list_id1=[]
list_id2=[]

if id1:
    if "MUON" in id1:
        list_id1=PrintOutMuons(id1,muon_path_id,user_muon_path_id)
    elif "JET" in id1:
        list_id1=PrintOutJets(id1,jet_path_id,user_jet_path_id)
    elif "ELECTRON" in id1:
        list_id1=PrintOutElectrons(id1,electron_path_id,user_electron_path_id)
    else:
        print "ID not found"
if id2:
    if id2=="123":
        sys.exit()

    if "MUON" in id2:
        list_id2=PrintOutMuons(id2,muon_path_id,user_muon_path_id)
    elif "JET"in id2:
        list_id2=PrintOutJets(id2,jet_path_id,user_jet_path_id)
    elif "ELECTRON" in id2:
        list_id2=PrintOutElectrons(id2,electron_path_id,user_electron_path_id)
    else:
        print "ID not found"      
if id1=="123":
    sys.exit()

if id2=="123":
    sys.exit()

if "MUON" in id1:
    if not "MUON" in id2:
        print "IDs need to be of same object"
        sys.exit()


if "ELECTRON" in id1:
    if not "ELECTRON" in id2:
        print "IDs need to be of same object"
        sys.exit()


if "JET" in id1:
    if not "JET" in id2:
        print "IDs need to be of same object"
        sys.exit()

print "\n"
print "\n"
print "Difference in IDs are:"
print "_________________________"
ndiff=0
for x in range(0, len(list_id2)):
    if not list_id2[x] == list_id1[x]:
        ndiff=ndiff+1
        sline=list_id2[x].split()
        if len(sline) > 2:
            print  list_id1[x] + " |  " +  sline[2] 

if ndiff == 0:
    print "No differences in IDs"
