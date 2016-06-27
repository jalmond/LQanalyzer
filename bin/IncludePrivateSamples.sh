# This does the following:
# Loops over paths for Flatcatuples/NocutSKim/LeptonSkim/DiLeptonSKim 
# Loops over catversions
# Loops over each line in datasets_snu_CAT_mc_private.txt and adds the line to the correct input list
# if the sample is new it emails jalmond@cern.ch to include in the global list
# if the sample is already in the global list it deletes it from datasets_snu_CAT_mc_private.txt

declare -a list_of_catversions=("v7-6-5" "v7-6-4" "v7-6-3" "v7-6-2" "v7-4-5" "v7-4-4")
declare -a list_of_paths=("/data2/DATA/cattoflat/MC/" "/SKTrees/MCNoCut/" "/SKTrees/MC/" "/SKTrees/MCDiLep/")

declare -a PRIVATELIST=()

already_added=true
isempty=true
for ipath in  ${list_of_paths[@]};
  do
  for ic in  ${list_of_catversions[@]};
    do
    isfirst=true
    while read line
      do
      line_tmp=$line
      
      if [[ $line == *${ipath}* ]];
	  then
	  sline=$(echo $line | head -n1 | awk '{print $6}')
	  if [[ $sline == *$ic* ]];
	      then
	      is_already_in_samplelist=false
	      
	      while read cline
              do
		if [[ $cline == *${sline}* ]];
		    then
		    is_already_in_samplelist=true
		fi
	      done < ${LQANALYZER_DIR}"/LQRun/txt/datasets_snu_CAT_mc_"${ic}".txt"
	      if [[ $is_already_in_samplelist == "false" ]];
		  then
		  if [[ $isfirst == "true" ]];
		      then
		      isfirst=false
		      echo " " >> ${LQANALYZER_DIR}"/LQRun/txt/datasets_snu_CAT_mc_"${ic}".txt"
		  fi
		  echo $line>> ${LQANALYZER_DIR}"/LQRun/txt/datasets_snu_CAT_mc_"${ic}".txt"
		  isempty=false
		  already_added=false
		  echo "Private sample is added to " ${LQANALYZER_DIR}"/LQRun/txt/datasets_snu_CAT_mc_"${ic}".txt"
		  PRIVATELIST+=({$line})
	      fi
	  fi
      fi

    done < ${LQANALYZER_DIR}"/LQRun/txt/datasets_snu_CAT_mc_private.txt"
  done
done

if [[ $isempty == "false" ]];
    then
    if [[ $already_added == "true" ]];
	then
	echo "All private samples are in global list. Reseting datasets_snu_CAT_mc_private.txt"
	cp $LQANALYZER_FILE_DIR/datasets_snu_CAT_mc_private.txt  ${LQANALYZER_DIR}/LQRun/txt/  
    fi
fi

sendemail=false
for line_list in ${PRIVATELIST[@]};
  do
  sendemail=true
  echo $line_list >> email_privatelist.txt
done
if [[ $sendemail == "true" ]];
    then
    cat email_privatelist.txt | mail -s "Private Samples To Add to SampleMap" jalmond@cern.ch
    rm email_privatelist.txt
fi

