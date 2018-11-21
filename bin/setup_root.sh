#! /bin/sh                                                                                                                                                                                                                                                                      
if [[ $HOSTNAME == "ui"* ]];
then

    python python/CheckProxy.py -x "setup"


    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%    Working on KISTI               %%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"


    export LQANALYZER_DIR=${PWD}

    export CMS_PATH=/cvmfs/cms.cern.ch
    source $CMS_PATH/cmsset_default.sh
    export SCRAM_ARCH=slc6_amd64_gcc630
    cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
    eval `scramv1 runtime -sh`
    echo " "
    echo "Working directory: "
    cd -
    source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh
    echo " "
    cd $LQANALYZER_DIR

elif [ $HOSTNAME == "cms.snu.ac.kr" ];
then
    echo ""
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%    Working on 42cluster           %%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"

    if [[ $1  == "False" ]];
    then
	source /share/apps/root_v6-12-06/bin/thisroot.sh
	export GCC_HOME=/share/apps/gcc491
	export PATH=$GCC_HOME/bin:$PATH
	export LD_LIBRARY_PATH=$GCC_HOME/lib64:$GCC_HOME/lib:$LD_LIBRARY_PATH
	
    else
	source /share/apps/root_v5-34-32/root/bin/thisroot.sh
    fi
    
else

    
    export CMS_PATH=/cvmfs/cms.cern.ch
    source $CMS_PATH/cmsset_default.sh
    export SCRAM_ARCH=slc6_amd64_gcc630
    cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
    eval `scramv1 runtime -sh`
    cd -
    source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh

fi

