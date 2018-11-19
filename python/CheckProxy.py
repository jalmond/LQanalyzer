
import os

def SetUpProxy():

    setupOk=False

    while not setupOk:
        os.system("voms-proxy-init")
        os.system("voms-proxy-info > checkproxy_setup.txt")

        readfile = open("checkproxy_setup.txt", "r")
        for line in readfile:
            if "timeleft" in line:
                if "12:" in line or  "11:" in line :
                    print "Proxy created: " + line
                    setupOk=True
                else:
                    print "Failed to setup proxy"

        readfile.close()


    os.system("rm checkproxy_setup.txt")


def CheckProxy():

    os.system("voms-proxy-info > checkproxy.txt")
    readfile = open("checkproxy.txt", "r")
    for line in readfile:
        line = line.replace(":"," ")
        sline=line.split()

        if "timeleft" in line:
            if int(sline[3]) < 2 :
                SetUpProxy()
    readfile.close()

    os.system("rm checkproxy.txt")




from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
jobtag=options.x

if jobtag == "setup":
    SetUpProxy()
else:
    CheckProxy()
