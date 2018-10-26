import os
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")
(options, args) = parser.parse_args()
filetag=options.x

print "Looking for " + filetag

os.system("ps ux > logk")
readps= open("logk")
listpid=[]
for line in readps:
    if filetag in line:
        if not "killbkg" in line:
            sline = line.split()
            pidtokill = sline[1]
            listpid.append(pidtokill)
            processtokill=""
            for x in range(10, len(sline)):
                processtokill+=  sline[x]+" "
        
            print "Kill " + str(pidtokill) + "  : " + processtokill
        
readps.close()
os.system("rm logk")

input = raw_input("Kill all list?")
if input == "Y":
    for x in listpid:
        os.system("kill -9 " + str(x))
        print "kill -9 " + str(x)

os.system("ps ux")
