import os

inputfile = open("inputlist.txt","r")
inputfile2 = open("inputlist.txt","r")
list= []
for line in inputfile:
    sline=line.split()
    repeat=False
    for dname in list:
        if sline[3] == dname:
            repeat=True
    if not repeat:            
        print 'dirmap["' + sline[3] + '"] =' + str(sline[6]) + ';'
        list.append(sline[3])

list2= []
for line in inputfile2:
    sline=line.split()
    repeat=False
    for dname in list2:
        if sline[3] == dname:
            repeat=True
    if not repeat:
        print 'lqmap["' + sline[3] + '"] ="";'
        list2.append(sline[3])
        
