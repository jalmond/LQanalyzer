import os,getpass

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

  source RunJob_${SECTION}.sh 2> err.log

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


from optparse import OptionParser
parser = OptionParser()
parser.add_option("-x", "--x", dest="x", default="123",help="tag")

(options, args) = parser.parse_args()
filepath=options.x

make_kistibatch_script(filepath+"RunJob.sh")

cwd = os.getcwd()
os.chdir(filepath)
os.system('tar -czf runFile.tar.gz Run*.sh CountGenWeight*.C')
os.chdir(cwd)
