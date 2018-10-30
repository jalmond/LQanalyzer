#!/bin/bash

pcmfile=$LQANALYZER_DIR/$1
if [ ! -a "$pcmfile" ]
then
    "File "$pcmfile" not found."
else
    mv $pcmfile ${LQANALYZER_LIB_PATH}
fi
