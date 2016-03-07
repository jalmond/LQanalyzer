#! /bin/sh

if [ -f $1$2 ]; then
    rm $1$2
fi
hadd $1$2 $3 
