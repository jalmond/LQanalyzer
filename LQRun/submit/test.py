####################################################################
# Settings for User
####################################################################
InputDir="/data1/SNUData/Data/Electron/DoubleElectron/Nov13/periodA/"
sample="periodAelectron"
number_of_cores=50
number_of_events_per_job=-1
print "Splitting job into " + str(number_of_cores) + " subjobs"

### configure run
timeWait=60#

###################################################
### Make Input File
###################################################
from functions import *
import os,getpass
os.system("ls " + InputDir + "/*.root > inputlist.txt")
isfile = os.path.isfile
join = os.path.join

## Get numnber of files in Input directory
number_of_files = sum(1 for item in os.listdir(InputDir) if isfile(join(InputDir, item)))
print str(number_of_files) + " files to process"

#import numpy as np
nfilesperjobs=0
for i in range(1,number_of_files):
    if not i%number_of_cores:
        print i
        nfilesperjobs+=1

remainder= number_of_files - nfilesperjobs*number_of_cores
print str(remainder)
