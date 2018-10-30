#! /bin/sh                                                                                                                                                                                                                                                                      
while read line
  do
  if [[ $line == *"LANG"* ]]; then
      setupok=True
  fi
done < ~/.bash_profile

if [[ $setupok == "False" ]]; then
    echo "Please add the following lines to ~/.bash_profile file:"
    echo 'LANG="en_US.utf-8"'
    echo 'LC_COLLATE="lt_LT.utf-8"'
    echo 'LC_TIME="en_DK.utf-8"'
    return 1
fi
