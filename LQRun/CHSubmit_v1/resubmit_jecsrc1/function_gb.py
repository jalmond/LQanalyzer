def make_batch_script(workdir, jname, lqdir, macroname):

    config='#!/bin/sh'
    config+='\n'
    config+='#$ -S /bin/bash \n'
    config+='#$ -N ' + jname + '  \n'
    config+='#$ -wd ' + workdir + ' \n'
    config+='#$ -o ' + workdir + ' \n'
    config+='#$ -e ' + workdir + ' \n'

    config+='echo "Job started at " `date` \n'
    config+='cd /share/apps/root_v5_34_32/root/ \n'
    config+='. bin/thisroot.sh \n'
    config+='cd ' + lqdir + '\n'

    config+='source setup.sh \n'
    config+='echo "PWD= "$PWD \n'
    config+='cd ' + workdir + ' \n'
    config+='root -l -q -b ' + macroname +' \n'
    config+='echo "Ran macro 2" \n'
    config+=''
    
    return config
