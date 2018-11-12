import os,time


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filepath=options.x

okToSubmit=False
while not okToSubmit:
    os.system('condor_q ' + os.getenv("USER") +" > submittion_log.txt") 
    file_fulllist = open("submittion_log.txt","r")
    njobs=0
    for x in file_fulllist:
        njobs=njobs+1
    file_fulllist.close()
    print "njobs = " + str(njobs)
    if njobs < 30:
        okToSubmit=True
    else:
        time.sleep(100.)
    os.system("rm submittion_log.txt")
        
cwd = os.getcwd()
os.chdir(filepath)
os.system('condor_submit Run_submit.jds')
os.chdir(cwd)


