import os


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filepath=options.x

for line in open(filepath+"/condor.log", 'r'):
    if "..." in line:
        continue
    new_line = line.replace("."," ")
    new_line = new_line.replace("("," ")

    sline = new_line.split()
    print "removing job that has finished: condor_rm " + sline[1]
    os.system("condor_rm " + sline[1])
    break

