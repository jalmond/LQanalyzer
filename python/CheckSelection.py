import os,sys

an_jonpre="/data2/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    an_jonpre="/data4/"

files_check = ["electrons.sel","muons.sel","jets.sel", "user_electrons.sel","user_muons.sel","user_jets.sel"]

if os.path.exists(an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER") + "/GoodSelection/"):
    os.system("rm -r   " + an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER") + "/GoodSelection/")

for i in files_check:
    path_file =  str(os.getenv("LQANALYZER_DIR")) + "/CATConfig/SelectionConfig/"+i
    file_ = open(path_file,"r")
    ncut_el=0
    for line in file_:
        sline = line.split()
        if "ncuts" in line:
            if not len(sline) == 2:
                print "Fix ncuts in input file path " + path_file
                sys.exit()
            ncut_el = int(sline[1])
        elif not "webpage" in line and not "###" in line:
            if not len(sline) == (2*ncut_el + 3):
                print line + " "  + str(len(sline)) + ": FIX in " + path_file
                sys.exit()                
    file_.close()
os.system("mkdir  "+an_jonpre+"/CAT_SKTreeOutput/" + os.getenv("USER") + "/GoodSelection/")
