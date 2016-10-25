import os,sys


output_jobinfo_only=False


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-j", "--job", dest="j", default="123",help="tag")
parser.add_option("-o", "--output", dest="o", default="False",help="tag")


(options, args) = parser.parse_args()
jobid=options.j
outinfo=options.o


if jobid == "123":
    print "use sktree_bkg_log -j <jobid>"
    sys.exit()

if outinfo == "False":
    output_jobinfo_only=False
else:
    output_jobinfo_only=True

bkg_job_file_path="/data2/CAT_SKTreeOutput/jalmond/CLUSTERLOG" + jobid + "/output_bkg.txt"
finished_path="/data2/CAT_SKTreeOutput/jalmond/CLUSTERLOG" + jobid + "/output_finished.txt"
if not os.path.exists(bkg_job_file_path):
    if not os.path.exists(finished_path):
        "Job ID " + jobid + " does not exist"
else:
    file_bkg_job_file_path = open(bkg_job_file_path,"r")
    
    for line in file_bkg_job_file_path:
        sline = line.split()
        if len(sline) == 0:
            continue
        outline =""
        for x in range(1,len(sline)):
            outline=outline+ " " + sline[x]
        if "Terminal Output" in outline:    
            if output_jobinfo_only:
                file_bkg_job_file_path.close()
                sys.exit()
            print "\n"
            print outline    
        elif "Files:" in  outline:
            print "\n"
            print outline
        else:
            print outline    
    file_bkg_job_file_path.close()
