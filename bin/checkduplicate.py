import os

dir = "/data1/SNUData/Data/Electron/DoubleElectron/Nov13/periodC/"
os.system("cd " + dir );
os.system("ls *.root > check.txt")

isfile = os.path.isfile
join = os.path.join
number_of_files = sum(1 for item in os.listdir(dir) if isfile(join(dir, item)))
tocheck = "RootTupleMakerV2_output_DATA_"

for i in range(1, 2181):
    fullname = tocheck + str(i) + "_"
    nrepeat=0
    fr = open('check.txt','r')
    for line in fr:
        if fullname in line:
            nrepeat+=1
#            print str(i) + ": Found "  + line
        if nrepeat == 2:
            print line         
            nrepeat+=1
            print "FOUND TWICE"
            
