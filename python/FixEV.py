import os

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filepath=options.x



filepathFix=filepath.replace(".txt","_fix.txt")
readfile=open(filepath,"r")
wfile=open(filepathFix,"w")
for line in  readfile:
    if "[ s[" in line:
        line = line.replace("[ s["," ][")
    if "[[" in line:
        line = line.replace("[[","[")
    if " [" in line:
        line = line.replace(" [","][")


    split = line.split()
    ncheck=0
    for s in split:
        if "[" in s:
            ncheck=ncheck+1
        if "][" in s:
            if not s == "][":
                s_tmp=s.replace("][","")
                line = line.replace(s,s_tmp+" ][")

    if ncheck == 1:
        wfile.write(line)
    if ncheck > 1:
        tmpline="[ "
        split2 = line.split()
        print line
        for s in split2:
            if "[" in s:
                if s == "][":
                    tmpline=tmpline+" ]"
                    print "--> " + tmpline
                    wfile.write(tmpline+"\n")
                    tmpline="[ "
            elif "]" in s:
                tmpline=tmpline+" ]"
                print "--> " + tmpline
                wfile.write(tmpline+"\n")
            else:
                tmpline=tmpline + s +" "


readfile.close()
wfile.close()
