def make_batch_script(workdir, jname, lqdir, macroname, cluster):

    config='#!/bin/sh'
    config+='\n'
    config+='#$ -S /bin/bash \n'
    config+='#$ -N ' + jname + '  \n'
    config+='#$ -wd ' + workdir + ' \n'
    config+='#$ -o ' + workdir + ' \n'
    config+='#$ -e ' + workdir + ' \n'

    config+='echo "Job started at " `date` \n'
    if cluster:
        config+='cd /share/apps/root_v5_34_32/root/ \n'
    else:
        config+='cd /share/apps/root_v5-34-32/root/ \n'

    config+='. bin/thisroot.sh \n'
    config+='cd ' + lqdir + '\n'

    config+='source setup.sh \n'
    config+='echo "PWD= "$PWD \n'
    config+='cd ' + workdir + ' \n'
    config+="root -l -b -q \'CountGenWeights.C(\""+mit->first+ "\",\""+filelist.at(i)+"\",\""+ "hist" + TString(istr) +".root\")\' ";
    config+='echo "Ran macro 2" \n'
    config+=''

    return config
