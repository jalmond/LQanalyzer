#!/usr/bin/python

import os,sys, getopt

dir = sys.argv[1]
tocheck= sys.argv[2]
print "Number of files in directory = "
count = os.system("ls -1 " + str(dir) + "  | wc -l")

os.system("cd " + str(dir) );
os.system("ls " + str(dir) + "/*.root > check.txt")

isfile = os.path.isfile
join = os.path.join
number_of_files = sum(1 for item in os.listdir(dir) if isfile(join(dir, item)))
#tocheck = "RootTupleMakerV2_output_DATA_"

print "Checking for duplicated Job ID :" + tocheck + "[jobid]" + "_##.root"

dupl =0
for i in range(1, count):
    fullname = tocheck + str(i) + "_"
    nrepeat=0
    fr = open('check.txt','r')
    for line in fr:
        if fullname in line:
            nrepeat+=1
            #print "Job " +i  + ": --> " +  line
            if nrepeat == 2:
                print line         
                nrepeat+=1
                print "FOUND TWICE"
                dupl+=1
if dupl == 0:
    print "No duplicated jobs in directory"
os.system("rm check.txt")
