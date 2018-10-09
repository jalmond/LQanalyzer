import os,sys

path_jobpre="/data1/"
if "tamsa2.snu.ac.kr" in str(os.getenv("HOSTNAME")):
    path_jobpre="/data2/"



if  "ui" in str(os.getenv("HOSTNAME")):
    path_jobpre="/cms/scratch/SNU/CATAnalyzer/"


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")
parser.add_option("-s", "--s", dest="s", default="123",help="tag")

(options, args) = parser.parse_args()
yeartag=options.x
monthtag=options.s

if not os.path.exists(path_jobpre+"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(monthtag)+"_"+str(yeartag)+".txt"):
    sys.exit()
file_toread = open(path_jobpre+"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(monthtag)+"_"+str(yeartag)+".txt","r")

userlist=[]


for line in file_toread:
    if not "job_complete= True" in line:
        continue
    splitline = line.split()
    if len(splitline) == 39:
        if splitline[22] < 0 or splitline[24] < 0:
           continue

    if splitline > 0:
        userexists=False
        for u in userlist:
            if u == splitline[0]:
                userexists=True
        if not userexists:
            userlist.append(splitline[0])
        if not len(splitline) == 39 :
            print "Fail: " + line
        
file_toread.close()

print "List of users using " + yeartag  + " in "  + monthtag +" = " 
fullcode_list=[]
for u in userlist:
    codelist=[]
    user=u
    file_toread = open(path_jobpre+"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(monthtag)+"_"+str(yeartag)+".txt","r")
    for line in file_toread:
        if not "job_complete= True"in line:
            continue
        splitline = line.split()
        if len(splitline) == 39:
            if splitline[18] < 0 or splitline[20] < 0:
                continue
            if splitline[0] == user:
                newcode =True
                for c in codelist:
                    if splitline[1] == c:
                        newcode=False
                if newcode:
                    print "Code= " + splitline[1] 
                    codelist.append(splitline[1])
                    fullcode_list.append(splitline[1])
        else:
            print "Number of entries per line = " + str(len(splitline))


    file_toread.close()


for c in fullcode_list:
    time_all=0.
    time_1=0.
    time_last=0.
    user=""
    times_ran=0
    njobs=0
    nfiles=0
    nsamples=0
    file_toread = open(path_jobpre+"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+str(monthtag)+"_"+str(yeartag)+".txt","r")
       
    for line in file_toread:
        if not "job_complete= True" in line:
            continue
        splitline = line.split()
        if len(splitline) == 39:
            if splitline[22] < 0 or splitline[24] < 0:
                continue
            if splitline[1] == c:
                nsamples=nsamples+1
                user=splitline[0]
                njobs=njobs+(int(splitline[10]))
                nfiles=nfiles+(int(splitline[12]))
                times_ran=times_ran+(int(splitline[14]))
                time_all=time_all+float(splitline[22])
                time_1=time_1+float(splitline[24])
                time_last=time_last+float(splitline[26])
    
    file_toread.close()
    print "Time in cpu hours"
    times_ran=times_ran/nsamples
    print c+ ": ["+user+"] times processed = " + str(times_ran)
    print c+ ": ["+user+"] njobs sent to queue = " + str(njobs)
    print c+ ": ["+user+"] average number of files per job = " + str(nfiles)
    print c+ ": ["+user+"] average number of samples ran job = " + str(float(nsamples)/float(times_ran))
    print c+ ": ["+user+"] Total time = " + str(time_all/60.)
    print c+ ": ["+user+"] Total time (-queue)= " + str((time_last)/60.)
    if time_all > 0.:
        print c+ ": ["+user+"] Percentage time in queue no jobs running  " + str((time_all- time_last)/time_all)
    if times_ran > 0:
        print c+ ": ["+user+"] Total time(cpu)/run = " + str((time_last)/(times_ran*60.))
    print c+ ": ["+user+"] Total jobs per run" + str(njobs)

