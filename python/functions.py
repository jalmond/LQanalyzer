import os

def   GetMonth(imonth):
    if imonth == 1:
        return "Jan"
    if imonth == 2:
        return "Feb"
    if imonth == 3:
        return "Mar"
    if imonth == 4:
        return "Apr"
    if imonth == 5:
        return "May"
    if imonth == 6:
        return "June"
    if imonth == 7:
        return "July"
    if imonth == 8:
        return "Aug"
    if imonth == 9:
        return "Sep"
    if imonth == 10:
        return "Oct"
    if imonth == 11:
        return "Nov"
    if imonth == 12:
        return "Dec"
    else:
        return "Dec"


def CheckPathInFile(channel,sample,mc):
    CopySKTrees(channel, sample, mc , "False")
    

    

def CopySKTrees(channel,sample,mc,docopy):
    
    if not docopy == "False":
        docopy = "True"
    
    import os
    filename = 'txt/datasets_cms21.txt'
    tmpxsec=0
    inputdir=""
    if not mc:
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    if channel ==entries[0] and sample == entries[1]:
                        inputdir = entries[2]
                        print inputdir 
    else:
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    tmpxsec=entries[1]
                    if sample == entries[0]:
                        inputdir = entries[2]

    sample_dir = os.getenv("LQANALYZER_DIR")+ "/data/input/"
    if not os.path.exists(sample_dir):                
        os.system("mkdir " + sample_dir)
    if not mc:
        sample_dir+= "data/"
        if not os.path.exists(sample_dir):
            os.system("mkdir " + sample_dir)
        sample_dir += channel+sample
        if not os.path.exists(sample_dir):
                os.system("mkdir " + sample_dir)
    else: 
        sample_dir += "mc/"    
        if not os.path.exists(sample_dir):  
            os.system("mkdir " + sample_dir)
        sample_dir += sample
        if not os.path.exists(sample_dir):
            os.system("mkdir " + sample_dir)     

    if docopy == "True":
        user = raw_input("Please enter username of cms21 account")    
        run = "scp " + str(user) + "@147.47.242.42:" + inputdir + "/*.root " + sample_dir
        print run
        os.system(run)
    
    infile=False
    if not mc:    
        for line in open('txt/datasets_mac.txt', 'r'):
                if not line.startswith("#"):
                    entries = line.split()
                    if len(entries)==3:
                        if sample == entries[1]:    
                            if channel in entries[0]:
                                infile=True
    else:
        for line in open('txt/datasets_mac.txt', 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    if sample == entries[0]:
                       infile=True 

    if not infile:                   
        f = open('txt/datasets_mac.txt', 'a') 
        try:
            if not mc:
                towrite = channel + " " + sample + " " + sample_dir
            else:
                towrite = sample + " " + tmpxsec + " " + sample_dir
            f.write(towrite)
        finally:    
            f.closed()  



def make_kistibatch_script(commandsfilename):

    run_commands = open(commandsfilename,'w')

    print>>run_commands,'''#!/bin/bash
SECTION=`printf %03d $1`
WORKDIR=`pwd`
echo "#### Extracting run files ####"
tar -zxvf runFile.tar.gz
echo "#### cmsenv ####"
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc630
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
eval `scramv1 runtime -sh`
cd -
echo "#### setup root ####"
source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh
NoAuthError=999
Trial=0
while [ "$NoAuthError" -ne 0 ]; do
  if [ "$Trial" -gt 9999 ]; then
    break
  fi
  echo "#### running ####"
  echo "root -l -b -q runJob_${SECTION}.C"
  root -l -b -q runJob_${SECTION}.C 2> err.log
  NoAuthError=`grep "Error in <TNetXNGFile::Open>" err.log -R | wc -l`
  if [ "$NoAuthError" -ne 0 ]; then
    echo "NoAuthError="$NoAuthError
    echo "AUTH error occured.. running again in 30 seconds.."
    Trial=$((Trial+=1))
    sleep 30
  fi
done
cat err.log >&2
'''
    run_commands.close()

#    config='#!/bin/sh'
#    config+="SECTION=`printf %03d $1`\n"
#    config+="WORKDIR=`pwd'\n"
#    #config+='echo "#### Extracting libraries ####"'
#    #config+="tar -zxvf lib.tar.#gz"
#    config+='echo "#### Extracting run files ####"\n'
 #   config+="tar -zxvf runFile.tar.gz\n"
    #tar -zxvf data.tar.gz
 #   config+='echo "#### cmsenv ####"\n'
 #   config+="export CMS_PATH=/cvmfs/cms.cern.ch\n"
 #   config+="source $CMS_PATH/cmsset_default.sh\n"
 #   config+="export SCRAM_ARCH=slc6_amd64_gcc630\n"
 #   config+="cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/\n"
 #   config+="eval `scramv1 runtime -sh`\n"
 #   config+="cd -\n"
 #   config+='echo "#### setup root ####"\n'
 #   config+="'source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh'\n"
 #   config+="\n"
 #   config+="NoAuthError=999\n"
 #   config+="Trial=0\n"
 #   config+='while [ "$NoAuthError" -ne 0 ]; do"\n'
 #   config+='if [ "$Trial" -gt 9999 ]; then\n'
 #   config+="break\n"
 #   config+="fi\n"
  #  config+='echo "#### running ####"\n'
  #  config+='echo "root -l -b -q run_${SECTION}.C"\n'
  #  config+="root -l -b -q runJob_${SECTION}.C 2> err.log\n"
  #  config+="NoAuthError=`grep 'Error in <TNetXNGFile::Open>' err.log -R | wc -l`\n"
  #  config+='if [ "$NoAuthError" -ne 0 ]; then\n'
  #  config+='echo "NoAuthError="$NoAuthError\n'
  #  config+='echo "AUTH error occured.. running again in 30 seconds.."\n'
   # config+='Trial=$((Trial+=1))\n'
   # config+='sleep 30\n'
#    config+="fi\n"
#    config+="done\n"
 #   config+="cat err.log >&2\n"

  #  return config


def make_batch_script(workdir, jname, lqdir, macroname, cluster):

    config='#!/bin/sh'
    config+='\n'
    config+='#$ -S /bin/bash \n'
    config+='#$ -N ' + jname + '  \n'
    config+='#$ -wd ' + workdir + ' \n'
    config+='#$ -o ' + workdir + ' \n'
    config+='#$ -e ' + workdir + ' \n'

    config+='echo "Job started at " `date` \n'
    if os.getenv("sktreemaker_version") == "False":
        config+='cd /share/apps/root_v6-12-06/  \n'      
    else:
        config+='cd /share/apps/root_v5-34-32/root/ \n'

    config+='. bin/thisroot.sh \n'
    config+='cd ' + lqdir + '\n'

    config+='source setup.sh ' + os.getenv("CATVERSION") + ' \n'
    config+='echo "PWD= "$PWD \n'
    config+='cd ' + workdir + ' \n'
    config+='root -l -q -b ' + macroname +' \n'
    config+='echo "Ran macro 2" \n'
    config+=''

    return config


def makeConfigFileSNU(log,sample, input, tree, cycle, ver, output_tmp, output, nevents, outstep, skipev, datatype, channel, period, totalmcevents, xsec, tar_lumi, eff_lumi, useSKinput, runevent, libraries, runnp, runcf, runtau, skflag,tmplibdir, nskim, njob):
    
    yeartag="80X"

    if not os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir):
        os.system("mkdir " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir)
        os.system("cp " + os.getenv("LQANALYZER_LIB_PATH") + "/*.so  " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir+"/")
        #os.system("cp " + os.getenv("LQANALYZER_LIB_PATH") + "/*.rootmap  " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir+"/")
        
    config='{\n'
    config+='    gEnv->SetValue("TFile.AsyncPrefetching", 1);\n'

    config+='   //### Load Libraries\n'
    config+='   gSystem->Load("libPhysics.so");\n'
    config+='   gSystem->Load("libTree.so");\n'
    config+='   gSystem->Load("libHist.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libNtuplecore'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libSelection'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libPlotting'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libHNCommonLeptonFakes'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/librochcor_'+yeartag+'");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libBTag'+yeartag+'SFUtil.so");\n'
    for lib in libraries:
        config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/' + lib + ' + .so");\n'
        
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libAnalyzerTools'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libLQAnalysis'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libSKTreeMaker'+yeartag+'.so");\n'
    config+='   gSystem->Load("'+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libValidation'+yeartag+'.so");\n'
    
    config+='   gSystem->Load("libPyROOT.so");\n'
    config+='   \n'
    config+='   TString filename = "' + input + '";\n'
    config+='   LQController analysis;\n'
    if useSKinput == "True":        
        config+='   analysis.SetLQInput(false);\n'
    elif useSKinput == "true":
        config+='   analysis.SetLQInput(false);\n'    
    else :
        config+='   analysis.SetLQInput(true);\n'
    config+='   analysis.SetJobName("' + sample + "_" + cycle+'");\n'
    config+='   analysis.SetTagName("' +tmplibdir +'");\n'
    config+='   analysis.SetInputList(TString(filename));\n'
    config+='   analysis.SetTreeName("'+ tree +'");\n'
    config+='   analysis.SetCycleName("' + cycle + '");\n'
    config+='   analysis.SetSkimName("' + nskim + '");\n'
    config+='   analysis.SetLogLevel("'+ log +'");\n'
    if not datatype =="mc" :
        config+='   analysis.SetChannel("'+ channel +'");\n'
    
    if not eff_lumi == -1.:
        config+='   analysis.SetEffectiveLuminosity(' + str(eff_lumi)+');\n'
    if not runevent ==-1:
        config+='   analysis.RunEvent(' + str(runevent)+');\n'
    if not nevents ==-1:
        config+='   analysis.SetNEventsToProcess(' + str(nevents) + ');\n'
    if not skipev ==-1:
        config+='   analysis.SkipEvents(' + str(skipev) + ');\n'
    if not outstep ==-1 :
        config+='   analysis.SetOutPutStep(' + str(outstep) + ');\n'
    if not period  =="":
        config+='   analysis.SetDataPeriod("' + period + '");\n'
    if not tar_lumi ==-1.:
        config+='   analysis.SetTargetLuminosity('+ str(tar_lumi) +');\n'
    if not datatype =="":
        config+='   analysis.SetDataType("' + datatype + '");\n'
    if not totalmcevents == -1 :
        config+='   analysis.SetTotalMCEvents(' + str(totalmcevents) +');\n'
    if not xsec == -1.:
        config+='   analysis.SetMCCrossSection(' + str(xsec) +');\n'
    config+='   analysis.SetUserFlag("'+skflag+'");\n'    
    config+='   analysis.RunNonPrompt("' +runnp+'");\n'
    config+='   analysis.RunTauMode("' +runtau+'");\n'
    config+='   analysis.RunChargeFlip("' +runcf+'");\n'
    config+='   analysis.SetName("' + sample + '",'+ str(ver) +',"'+ output_tmp +'");\n'                        
    config+='   analysis.Initialize();\n'
    config+='   analysis.ExecuteCycle();\n'

    #config+='   cout << "Moving " ' + output_tmp + sample + '_' + str(ver) + '.root ' + output + '" << endl;\n'
    config+='   gSystem->Exec("mv ' + output_tmp + sample + '_' + str(ver) + '.root ' + output + '");\n'
    #config+='    gSystem->Exec("ls ' + output + '"));\n'
    config+='  \n}'

    return config


def makeConfigFile(log,sample, input, tree, cycle, ver, output_tmp, output, nevents, outstep, skipev, datatype, channel, period, totalmcevents, xsec, tar_lumi, eff_lumi, useSKinput, runevent, libraries, runnp, runcf, runtau, skflag,tmplibdir, nskim, njob):


    if not os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir):
        os.system("mkdir " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir)
        os.system("cp " + os.getenv("LQANALYZER_LIB_PATH") + "/*.so  " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir+"/")
        os.system("cp " + os.getenv("LQANALYZER_LIB_PATH") + "/*.pcm  " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+tmplibdir+"/")

    yeartag="80X"

        
    config='   //### Load Libraries\n'
    config+='   R__LOAD_LIBRARY(libPhysics.so);\n'
    config+='   R__LOAD_LIBRARY(libTree.so);\n'
    config+='   R__LOAD_LIBRARY(libHist.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libNtuplecore'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libSelection'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libPlotting'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libHNCommonLeptonFakes'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/librochcor_'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libBTag'+yeartag+'SFUtil.so);\n'
    for lib in libraries:
        config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/' + lib + ' + .so);\n'
        
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libAnalyzerTools'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libLQAnalysis'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libSKTreeMaker'+yeartag+'.so);\n'
    config+='   R__LOAD_LIBRARY('+os.getenv("LQANALYZER_BATCHLIB_PATH")+tmplibdir+'/libValidation'+yeartag+'.so);\n'
    
    config+='   R__LOAD_LIBRARY(libPyROOT.so);\n'

    
    config+='void runJob_'+njob+'(){\n'

    config+='   \n'
    config+='    gEnv->SetValue("TFile.AsyncPrefetching", 1);\n'
    config+='   TString filename = "' + input + '";\n'
    config+='   LQController analysis;\n'
    if useSKinput == "True":        
        config+='   analysis.SetLQInput(false);\n'
    elif useSKinput == "true":
        config+='   analysis.SetLQInput(false);\n'    
    else :
        config+='   analysis.SetLQInput(true);\n'
    config+='   analysis.SetJobName("' + sample + "_" + cycle+'");\n'
    config+='   analysis.SetTagName("' +tmplibdir +'");\n'
    config+='   analysis.SetInputList(TString(filename));\n'
    config+='   analysis.SetTreeName("'+ tree +'");\n'
    config+='   analysis.SetCycleName("' + cycle + '");\n'
    config+='   analysis.SetSkimName("' + nskim + '");\n'
    config+='   analysis.SetLogLevel("'+ log +'");\n'
    if not datatype =="mc" :
        config+='   analysis.SetChannel("'+ channel +'");\n'
    
    if not eff_lumi == -1.:
        config+='   analysis.SetEffectiveLuminosity(' + str(eff_lumi)+');\n'
    if not runevent ==-1:
        config+='   analysis.RunEvent(' + str(runevent)+');\n'
    if not nevents ==-1:
        config+='   analysis.SetNEventsToProcess(' + str(nevents) + ');\n'
    if not skipev ==-1:
        config+='   analysis.SkipEvents(' + str(skipev) + ');\n'
    if not outstep ==-1 :
        config+='   analysis.SetOutPutStep(' + str(outstep) + ');\n'
    if not period  =="":
        config+='   analysis.SetDataPeriod("' + period + '");\n'
    if not tar_lumi ==-1.:
        config+='   analysis.SetTargetLuminosity('+ str(tar_lumi) +');\n'
    if not datatype =="":
        config+='   analysis.SetDataType("' + datatype + '");\n'
    if not totalmcevents == -1 :
        config+='   analysis.SetTotalMCEvents(' + str(totalmcevents) +');\n'
    if not xsec == -1.:
        config+='   analysis.SetMCCrossSection(' + str(xsec) +');\n'
    config+='   analysis.SetUserFlag("'+skflag+'");\n'    
    config+='   analysis.RunNonPrompt("' +runnp+'");\n'
    config+='   analysis.RunTauMode("' +runtau+'");\n'
    config+='   analysis.RunChargeFlip("' +runcf+'");\n'
    config+='   analysis.SetName("' + sample + '",'+ str(ver) +',"'+ output_tmp +'");\n'                        
    config+='   analysis.Initialize();\n'
    config+='   analysis.ExecuteCycle();\n'

    #config+='   cout << "Moving " ' + output_tmp + sample + '_' + str(ver) + '.root ' + output + '" << endl;\n'
    config+='   gSystem->Exec("mv ' + output_tmp + sample + '_' + str(ver) + '.root ' + output + '");\n'
    #config+='    gSystem->Exec("ls ' + output + '"));\n'
    config+='  \n}'

    return config

#Import date
def now():
    from datetime import datetime
    return str(datetime.now().month) + str(datetime.now().day)+ str(datetime.now().hour)+str(datetime.now().minute)
