import os


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filepath=options.x

path_new = "inputlist_efflumi_batch.txt";
file_fixedpath = open(path_new,"w")

for line in open(filepath, 'r'):
    
    new_line = line.replace("/xrootd/store/user/jalmond","root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/jalmond")
    file_fixedpath.write(new_line)
file_fixedpath.close()
