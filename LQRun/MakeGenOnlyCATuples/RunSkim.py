import os, getpass, sys
import time
from functions import *


version = os.getenv("CATVERSION")
sampledir = ["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
             "ttbb_4FS_ckm_amcatnlo_madspin_pythia8",
             "TT_TuneCUETP8M1_mtop1755_13TeV-powheg-pythia8",
             "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
             "ttHTobb_M125_13TeV_powheg_pythia8"
             ,  "ttWJets_13TeV_madgraphMLM",
             "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 
             "ttHToNonbb_M125_13TeV_powheg_pythia8", 
             "ttZJets_13TeV_madgraphMLM",
             "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 
             "TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8", 
             "VBF_HToMuMu_M125_13TeV_powheg_pythia8",
             "DYJetsToLL_M-5to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", 
             "TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
             "WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
             "GluGlu_HToMuMu_M125_13TeV_powheg_pythia8",
             "TTTo2L2Nu_13TeV-powheg",
             "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
             "ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1", 
             "TTTo2L2Nu_13TeV_ScaleDown-powheg", 
             "WW_TuneCUETP8M1_13TeV-pythia8",
             "ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1",  
             "TTTo2L2Nu_13TeV_ScaleUp-powheg",  
             "WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
             "ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1",  
             "TTToSemiLeptonic_13TeV-powheg",  
             "WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
             "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",  
             "TTToSemiLeptonic_13TeV_ScaleDown-powheg",  
             "WZ_TuneCUETP8M1_13TeV-pythia8",
             "ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1",  
             "TTToSemiLeptonic_13TeV_ScaleUp-powheg",  
             "WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8",
             "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",  
             "TT_TuneCUETP8M1_13TeV-powheg-pythia8",  
             "ZZ_TuneCUETP8M1_13TeV-pythia8",
             "ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1",  
             "TT_TuneCUETP8M1_mtop1695_13TeV-powheg-pythia8", 
             "ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8" ]
sampledir=["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"]

file_list_all="/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_" + version +".txt"

missing_sample="False"
for line in open(file_list_all, 'r'):
    
    if ("/data2/DATA/cattoflat/MC/" + version +"/") in line:
        sample_in_list="False"
        for i in sampledir:
            if i in line:
                sample_in_list="True"
        if sample_in_list == "False":
            #print "Missing sample " + line
            missing_sample="True"


skip=0
counter=0

for i in sampledir:
   counter = counter+1
   if  counter < skip:
      continue
   
   output_s=i
   output="/data2/LQ_SKTreeOutput/ssskim/jalmond/"+i
   print "Making dir: " + output

   if (os.path.exists("/data2/DATA/cattoflat/ssskim/"+ version+ "/" + i)):
      continue
   
   if not (os.path.exists(output)):
      os.system("mkdir " + output)
      os.system("mkdir " + output + "/output/")
   else:
      os.system("rm -rf " + output)
      os.system("mkdir " + output)
      os.system("mkdir " + output + "/output/")
              
      
   os.system("ls /data2/DATA/cattoflat/MC/" + version + "/" + i + " > " + output + "/list.txt" )

   fr = open(output + "/list.txt" , 'r')
   counter=0
   for line in fr:
      if ".root" in line:
         counter=counter+1

   if counter==0:
      continue;

   runfile=open(output+ "/run.sh","w")
   for j in range(1,counter+1):
       runscript= "SkimFlatCat.h"
       runscriptC="SkimFlatCat.C"

       if not (os.path.exists(output+ "/" + str(j))):
           os.system("mkdir " + output+ "/" + str(j))
         
       configfile=open(output+ "/"  + str(j) + "/" + runscript,'w')
       configfile.write(makeNtupleMakerH("/data2/DATA/cattoflat/MC/" + version + "/"+ output_s,output+ "/list.txt",j, output,False))
       configfile.close()

       configfileC=open(output+ "/" + str(j) + "/" + runscriptC,'w')
       configfileC.write(makeNtupleMakerC(output + "/" +  str(j),output+ "/list.txt", j, False))
       configfileC.close()

       
       outputFile = open((output+ "/"  + str(j) + "/Run_" + str(j) + ".sh"),"w")
       outputFile.write("#!/bin/sh" )
       outputFile.write("\n")
       outputFile.write("#$ -S /bin/bash \n")
       outputFile.write("#$ -N Run_" + str(j)  + "  \n")
       outputFile.write("#$ -wd  /data2/LQ_SKTreeOutput/ssskim/jalmond/" +i+"/" + str(j) +"/"+ " \n")
       outputFile.write("#$ -o  /data2/LQ_SKTreeOutput/ssskim/jalmond/"   +i+"/"+ str(j) + "/"  " \n")
       outputFile.write("#$ -e  /data2/LQ_SKTreeOutput/ssskim/jalmond/"  +i+"/" + str(j) + "/" + " \n")
       outputFile.write("echo 'Job started at ' `date` \n")
       outputFile.write("cd /share/apps/root_v5-34-32/root/ \n")
       outputFile.write(". bin/thisroot.sh \n")
       outputFile.write("cd " + os.getenv("LQANALYZER_DIR") + "\n")
       
       outputFile.write("source setup.sh \n")
       outputFile.write("echo 'PWD= '$PWD \n")
       outputFile.write("cd /data2/LQ_SKTreeOutput/ssskim/jalmond/"  +i+"/" + str(j) + "/" + " \n")
       outputFile.write("root -l -q -b " +  output+ "/" + str(j) + "/SkimFlatCat.C ")
       outputFile.write("echo 'Ran macro 2' \n")
       outputFile.write("")
       outputFile.close()
       command3 = "qsub -V  /data2/LQ_SKTreeOutput/ssskim/jalmond/" +i + "/" + str(j) + "/Run_" + str(j) + ".sh \n"
       print "qsub -V  /data2/LQ_SKTreeOutput/ssskim/jalmond/" +i + "/" + str(j) + "/Run_" + str(j) + ".sh"
       runfile.write(command3)

    
   runfile.close()

   
   os.system("source /data2/LQ_SKTreeOutput/ssskim/jalmond/" +i + "/run.sh")    

   job_finised=False
   while not job_finised:
       print "Checking jobs"
       time.sleep(20.)
       os.system("ls " +  output+ "/output/ > " + output + "/checkoutput.txt")
       os.system("ls " +  output+ "/output/")
       count=0
       for line in open( output + "/checkoutput.txt", 'r'):
           if ".root" in line:
               count = count+1
           print str(count) + " " + str(counter)    
           if count == counter:
               job_finised=True


   if not (os.path.exists("/data2/DATA/cattoflat/ssskim/"+ version)):
      os.system("mkdir " + "/data2/DATA/cattoflat/ssskim/" + version)
          
   if not (os.path.exists("/data2/DATA/cattoflat/ssskim/"+ version+ "/" + i)):
      os.system("mkdir " + "/data2/DATA/cattoflat/ssskim/" + version+ "/"+ i)

      
   print "Moving samples to /data2/DATA/cattoflat/ssskim/" + version+ "/"+ i    
   os.system("mv "  +  output+ "/output/*.root /data2/DATA/cattoflat/ssskim/"+ version+ "/" + i )
   print "mv "  +  output+ "/output/*.root /data2/DATA/cattoflat/ssskim/" + version+ "/"+ i 
   
   os.system("rm -rf " + output)
