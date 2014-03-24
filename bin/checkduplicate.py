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


print "Checking for duplicated Job ID :" + tocheck + "[jobid]" + "_##.root"

count = number_of_files
dupl =0
for i in range(1, count):
    fullname = tocheck + str(i) + "_"
    nrepeat=0
    fr = open('check.txt','r')
    for line in fr:
        if fullname in line:
            nrepeat+=1
            print "Job " + str(i)  + ": --> " +  line
            if nrepeat != 1:
                print "FOUND TWICE: removing " + line
                os.system("rm -f " + line)
                dupl+=1

if dupl == 0:
    print "No duplicated jobs in directory"
os.system("rm check.txt")
