#! /bin/sh
# $Id: setup.sh 1
###################################################################################
# @Project: cleanup.sh                                                            #
#                                                                                 #
# @author John Almond       <jalmond@cern.ch>           - SNU                     #
#                                                                                 #
#                                                                                 #
##################################################################################
find . -name \*~ -type f -delete
    
function clean_emacs(){    

    cd $LQANALYZER_DIR
    find . -name \*~ -type f -delete
    echo "Have Cleaned up all *~ files in:"
    cd -

}

