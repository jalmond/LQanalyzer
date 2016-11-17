import os, getpass, sys
import time
from functions import *

version = os.getenv("CATVERSION")
sampledir = ["SingleMuon" , "DoubleMuon"]
period=["periodB" ,"periodC" , "periodD", "periodE" ,"periodF", "periodG"]

for i in sampledir:
 
   output_s=i
   output="/data2/LQ_SKTreeOutput/skim/jalmond/"+i

   print "Making dir: " + output
   
   if not (os.path.exists(output)):
      os.system("mkdir " + output)
   else:
      os.system("rm -r " + output + "/*")
      if not (os.path.exists(output + "/output/")):
         os.system("mkdir " + output + "/output/")

   for p in period:      
      poutput = output + "/" + p
      poutput_s = output_s + "/" + p

      if not (os.path.exists(poutput)):
         os.system("mkdir " + poutput)
         os.system("mkdir " + poutput + "/output/")
         
      os.system("ls /data2/DATA/cattoflat/Data/"+ version+ "/" + poutput_s + " > " + poutput + "/list.txt" )
      print "ls /data2/DATA/cattoflat/Data/"+ version+ "/" + poutput_s 
      fr = open(poutput + "/list.txt" , 'r')
      counter=0
      for line in fr:
         if ".root" in line:
            counter=counter+1
            

      runscript= "SkimFlatCat_data.h"
      runscriptC="SkimFlatCat_data.C"
      runfile=open(poutput+ "/run.sh","w")

      print str(counter)
      for j in range(1,counter+1):
         if not (os.path.exists(poutput+ "/" + str(j))):
            os.system("mkdir " + poutput+ "/" + str(j))
            
         configfile=open(poutput+ "/"  + str(j) + "/" + runscript,'w')
         configfile.write(makeNtupleMakerH("/data2/DATA/cattoflat/Data/"+ version+ "/" + poutput_s,poutput+ "/list.txt",j, poutput, True))
         configfile.close()
         
         configfileC=open(poutput+ "/" + str(j) + "/" + runscriptC,'w')
         configfileC.write(makeNtupleMakerC(poutput + "/" +  str(j),poutput+ "/list.txt", j, True))
         configfileC.close()
         

         
         outputFile = open((poutput+ "/"  + str(j) + "/Run_" + str(j) + ".sh"),"w")
         outputFile.write("#!/bin/sh" )
         outputFile.write("\n")
         outputFile.write("#$ -S /bin/bash \n")
         outputFile.write("#$ -N Run_" + str(j)  + "  \n")
         outputFile.write("#$ -wd  /data2/LQ_SKTreeOutput/skim/jalmond/" +i+ "/" + p +"/" + str(j) +"/"+ " \n")
         outputFile.write("#$ -o  /data2/LQ_SKTreeOutput/skim/jalmond/"   +i+ "/" + p +"/"+ str(j) + "/"  " \n")
         outputFile.write("#$ -e  /data2/LQ_SKTreeOutput/skim/jalmond/"  +i+ "/" + p +"/" + str(j) + "/" + " \n")
         outputFile.write("echo 'Job started at ' `date` \n")
         outputFile.write("cd /share/apps/root_v5-34-32/root/ \n")
         outputFile.write(". bin/thisroot.sh \n")
         outputFile.write("cd " + os.getenv("LQANALYZER_DIR") + "\n")
         
         outputFile.write("source setup.sh \n")
         outputFile.write("echo 'PWD= '$PWD \n")
         outputFile.write("cd /data2/LQ_SKTreeOutput/skim/jalmond/" +i + "/" + p + "/" + str(j) + "/" + " \n")
         outputFile.write("root -l -q -b /data2/LQ_SKTreeOutput/skim/jalmond/" +i + "/" + p + "/" + str(j) + "/SkimFlatCat_data.C ")
         outputFile.write("echo 'Ran macro 2' \n")
         outputFile.write("")
         outputFile.close()
         command3 = "qsub -V  /data2/LQ_SKTreeOutput/skim/jalmond/" +i + "/" + p + "/" + str(j) + "/Run_" + str(j) + ".sh \n"
         print "qsub -V  /data2/LQ_SKTreeOutput/skim/jalmond/" +i + "/"  + p + "/" + str(j) + "/Run_" + str(j) + ".sh"
         runfile.write(command3)
                
      runfile.close()
      os.system("source /data2/LQ_SKTreeOutput/skim/jalmond/" +i  +"/"+ p + "/run.sh")
      

      job_finised=False
      while not job_finised:
         time.sleep(20.)
         os.system("ls " +  poutput+ "/output/ > " + poutput + "/checkoutput.txt")
         os.system("ls " +  poutput+ "/output/" )
         count=0
         for line in open( poutput + "/checkoutput.txt", 'r'):
            if ".root" in line:
               count = count+1

            if count == counter:
               job_finised=True


      if not (os.path.exists("/data2/DATA/cattoflat/skim/"+ version)):
         os.system("mkdir " + "/data2/DATA/cattoflat/skim/"+ version)


      if not (os.path.exists("/data2/DATA/cattoflat/skim/"+ version+ "/" + i)):
                  os.system("mkdir " + "/data2/DATA/cattoflat/skim/"+ version+ "/" + i)
      if not (os.path.exists("/data2/DATA/cattoflat/skim/"+ version+ "/" + poutput_s)):
         os.system("mkdir " + "/data2/DATA/cattoflat/skim/"+ version+ "/" + poutput_s)

      print "Moving samples to /data2/DATA/cattoflat/skim/"+ version+ "/" + poutput_s    
      os.system("mv "  +  poutput+ "/output/*.root /data2/DATA/cattoflat/skim/"+ version+ "/" + poutput_s )
   
      os.system("rm -r " + poutput)
    
