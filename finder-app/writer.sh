#!/bin/sh
# Accepts: 
# - First argument is full path to a file (incl filename) WRITEFILE
# - Second argument is a text string which will be written within this file WRITESTR
# Returns:
# - 1 and print if arguments missing
# - Create a new file with name and path WRITEFILE with content WRITESTR overwriting any existing file 
# - Create the path if doesn't exist.
# - 1 if file cannot be created
# Author: Giuseppe Avon

if [ $# -ne 2 ]
then
    echo "Missing WRITEFILE and WRITESTR parameters in call"
    exit 1
fi

if [ $# -eq 2 ]
then
    WRITEFILE=$1
    WRITESTR=$2
   
    DIRNAME=$(dirname ${WRITEFILE})
    mkdir -p dirname "${DIRNAME}"
    
    echo "${WRITESTR}" >| "${WRITEFILE}"
    EXECRESULT=$?
    
    if [ ${EXECRESULT} -ne "0" ]
    then
        echo "Failure writing to ${WRITEFILE}, returned with status ${EXECRESULT}"
        exit 1
    else
        exit 0
    fi
    
fi
