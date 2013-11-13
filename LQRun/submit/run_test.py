# Set By User
InputDir="/data1/SNUData/Data/Electron/DoubleElectron/Nov13/periodA/"
sample="periodAelectron"
number_of_cores=20 
print "Splitting job into " + str(number_of_cores)

from function import *

import os,getpass
os.system("ls " + InputDir + " > inputlist.txt")

isfile = os.path.isfile
join = os.path.join

## Get numnber of files in Input directory
number_of_files = sum(1 for item in os.listdir(InputDir) if isfile(join(InputDir, item)))
#print number_of_files

#import numpy as np
njobs=0
for i in range(0,number_of_files):
    if not i%number_of_cores:
        njobs+=1
        
print "Running " + str(njobs) + " jobs"

## counters
nfiles=0
count=1

output="/var/tmp/"+ getpass.getuser() + sample + "/"
os.system("mkdir " + output)

fr = open('inputlist.txt', 'r')
fwrite = open(output+"filename%s" % (count), 'w')
for line in fr:
    nfiles+=1        
    if not nfiles % number_of_cores:
        fwrite.close()
        count+=1
        fwrite = open("filename%s.txt" % (count), 'w')
        fwrite.write(line)
    else:
        fwrite.write(line)
fwrite.close()
fr.close()

configfile.write(makeConfigFile())
os.system('nohup root -q -b runbackground.C&>test&')                            
os.system('tail -f test')
                                
