from function_gb import *
import os


submit_file = open('submit.sh','w')
for x in range (1592, 2524):
    lqdir="/data4/LQAnalyzerCode/gbyu/CHs_v2_sub/LQanalyzer/"
    
    for y in range (1,21):
        submit_file2 = open('submit_'+str(x)+'_'+str(y)+'.sh','w')
        submit_file2.write(make_batch_script("/data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_716210_cmscluster.snu.ac.kr/Job_"+str(x)+"/","CHttbarMS",lqdir,"/data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_716210_cmscluster.snu.ac.kr/Job_"+str(x)+"/runJob_"+str(x)+"_"+str(y)+".C"))
        submit_file2.close()
    #os.system("source submit.sh")
        submit_file.write('qsub -V submit_'+str(x)+'_'+str(y)+'.sh \n')
        print "running /data4/LQ_SKTreeOutput/gbyu/SKttbarMS_pf_716210_cmscluster.snu.ac.kr/Job_"+str(x)+"/runJob_"+str(x)+"_"+str(y)+".C"

