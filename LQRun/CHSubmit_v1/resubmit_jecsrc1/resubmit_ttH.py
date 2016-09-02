from function_gb import *
import os

submit_file = open('submit.sh','w')
with open("list","rb") as f :
    while True:
        lines = f.readline()
        if lines == "": 
            break
        line = lines.rstrip("\n\r")
        lqdir="/data4/LQAnalyzerCode/gbyu/CHs_v2/LQanalyzer/"
        submit_file2 = open('submit_'+str(line)+'.sh','w')
        submit_file2.write(make_batch_script("/data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7131751_cmscluster.snu.ac.kr/Job_"+str(line)+"/","CHttH",lqdir,"/data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7131751_cmscluster.snu.ac.kr/Job_"+str(line)+"/runJob_"+str(line)+".C"))
        submit_file2.close()
    #os.system("source submit.sh");
        submit_file.write('qsub -V submit_'+str(line)+'.sh \n')
        print "running /data4/LQ_SKTreeOutput/gbyu/SKttH_pf_7131751_cmscluster.snu.ac.kr/runJob_"+str(line)+".C"

f.close()
