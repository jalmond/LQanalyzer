copy_command=""
if [[ $HOSTNAME == "cmscluster.snu.ac.kr" ]];
then
    ssh jalmond@cms3.snu.ac.kr 'ls /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/' >nonlocal_check.txt
    ls $LQANALYZER_FILE_DIR/ > local_check.txt
    copy_command=jalmond@cms3.snu.ac.kr:/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/
else 
    ssh jalmond@147.47.242.67 'ls /data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/' >nonlocal_check.txt
    ls $LQANALYZER_FILE_DIR/ > local_check.txt
    copy_command=jalmond@147.47.242.67:/data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/
fi

while read line_local
do
    not_new="False"
    while read line_nonlocal
    do
	if [[ $line_local == $line_nonlocal ]];
	then 
	    not_new="True"
	fi
    done < nonlocal_check.txt


    if [[ $not_new == "False" ]];
    then
	scp $LQANALYZER_FILE_DIR/$line_local $copy_command
	echo "Copying new file " $LQANALYZER_FILE_DIR/$line " -->  "$copy_command
    fi
done < local_check.txt
rm nonlocal_check.txt
rm local_check.txt
