import os, getpass, sys
import time
from functions import *

version = os.getenv("CATVERSION")
sampledir = ["DoubleMuon", "SingleMuon"]
period=["periodC" , "periodD"]

for i in sampledir:
   output=i
   print "Making dir: " + output
   
   if not (os.path.exists(output)):
      os.system("mkdir " + output)
   else:
      os.system("rm -r " + output + "/*")
      if not (os.path.exists(output + "/output/")):
         os.system("mkdir " + output + "/output/")

   for p in period:      
      poutput = output + "/" + p

      if not (os.path.exists(poutput)):
         os.system("mkdir " + poutput)
         os.system("mkdir " + poutput + "/output/")
         
      os.system("ls /data2/DATA/cattoflat/Data/"+ version+ "/" + poutput + " > " + poutput + "/list.txt" )
      
      fr = open(poutput + "/list.txt" , 'r')
      counter=0
      for line in fr:
         if ".root" in line:
            counter=counter+1
            

      runscript= "SkimFlatCat.h"
      runscriptC="SkimFlatCat.C"
      for j in range(1,counter+1):
         if not (os.path.exists(poutput+ "/" + str(j))):
            os.system("mkdir " + poutput+ "/" + str(j))
            
         configfile=open(poutput+ "/"  + str(j) + "/" + runscript,'w')
         configfile.write(makeNtupleMakerH("/data2/DATA/cattoflat/Data/"+ version+ "/" + poutput,poutput+ "/list.txt",j, poutput))
         configfile.close()
         
         configfileC=open(poutput+ "/" + str(j) + "/" + runscriptC,'w')
         configfileC.write(makeNtupleMakerC(poutput + "/" +  str(j),poutput+ "/list.txt", j))
         configfileC.close()
      
         os.system("root -l -q -b " +  poutput+ "/" + str(j) + "/SkimFlatCat.C &> " + poutput + "/" + str(j) + "/log.txt&" )
      

      job_finised=False
      while not job_finised:
         time.sleep(20.)
         os.system("ls " +  poutput+ "/output/ > " + poutput + "/checkoutput.txt")
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
      if not (os.path.exists("/data2/DATA/cattoflat/skim/"+ version+ "/" + poutput)):
         os.system("mkdir " + "/data2/DATA/cattoflat/skim/"+ version+ "/" + poutput)

      print "Moving samples to /data2/DATA/cattoflat/skim/"+ version+ "/" + poutput    
      os.system("mv "  +  poutput+ "/output/*.root /data2/DATA/cattoflat/skim/"+ version+ "/" + poutput )
   
      os.system("rm -r " + poutput)
    
