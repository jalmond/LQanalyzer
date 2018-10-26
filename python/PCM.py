import os

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")


(options, args) = parser.parse_args()
pcmloc=options.x

if os.path.exists(pcmloc):
    print "mv " + pcmloc + " " + os.getenv("LQANALYZER_LIB_PATH")
    os.system("mv " + pcmloc + " " + os.getenv("LQANALYZER_LIB_PATH"))
else:
    print pcmloc + " not created"
