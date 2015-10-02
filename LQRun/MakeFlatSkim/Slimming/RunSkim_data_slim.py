import os, getpass, sys
import time
from functions import *

sampledir = ["DoubleMuon"]


for i in sampledir:
   output=i
   print "Making dir: " + output
   
   if not (os.path.exists(output)):
      os.system("mkdir " + output)
      os.system("mkdir " + output + "/output/")
   else:
      os.system("rm -r " + output + "/*")
      if not (os.path.exists(output + "/output/")):
         os.system("mkdir " + output + "/output/")
              
      
   os.system("ls /data2/DATA/cattoflat/skim/" + i + " > " + output + "/list.txt" )

   fr = open(output + "/list.txt" , 'r')
   counter=0
   for line in fr:
      if ".root" in line:
         counter=counter+1


   runscript= "SlimFlatCat.h"
   runscriptC="SlimFlatCat.C"
   for j in range(1,counter+1):
      if not (os.path.exists(output+ "/" + str(j))):
         os.system("mkdir " + output+ "/" + str(j))
         
      configfile=open(output+ "/"  + str(j) + "/" + runscript,'w')
      configfile.write(makeNtupleMakerSlimH("/data2/DATA/cattoflat/skim/" + output,output+ "/list.txt",j, output))
      configfile.close()

      configfileC=open(output+ "/" + str(j) + "/" + runscriptC,'w')
      configfileC.write(makeNtupleMakerSlimC(output + "/" +  str(j),output+ "/list.txt", j))
      configfileC.close()
      
      os.system("root -l -q -b " +  output+ "/" + str(j) + "/SlimFlatCat.C &> " + output + "/" + str(j) + "/log.txt&" )


   job_finised=False
   while not job_finised:
      time.sleep(20.)
      os.system("ls " +  output+ "/output/ > " + output + "/checkoutput.txt")
      count=0
      for line in open( output + "/checkoutput.txt", 'r'):
         if ".root" in line:
            count = count+1

         if count == counter:
            job_finised=True


   if not (os.path.exists("/data2/DATA/cattoflat/skim/slim/" + i)):
      os.system("mkdir " + "/data2/DATA/cattoflat/skim/slim/" + i)

   print "Moving samples to /data2/DATA/cattoflat/skim/slim/" + i    
   os.system("mv "  +  output+ "/output/*.root /data2/DATA/cattoflat/skim/slim/" + i )
   
   os.system("rm -r " + output)
    
