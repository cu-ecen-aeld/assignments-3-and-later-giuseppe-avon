#!/bin/sh
# Accepts: 
# - Path to directory (filesdir)
# - Text searched within files (searchstr)
# - Return 1 and print statements if filesdir does not exist on fs
# - Prints a message "The number of files are X and the number of matching lines are Y"
# Author: Giuseppe Avon

if [ $# -ne 2 ]
then
    echo "Missing FILESDIR and SEARCHSTR parameters in call"
    exit 1
fi

if [ $# -eq 2 ]
then
    FILESDIR=$1
    SEARCHSTR=$2
    if [ -d $FILESDIR ]
    then
        FILESCOUNT=$(find ${FILESDIR} -type f | wc -l)
        MATCHESCOUNT=$(grep -c "${SEARCHSTR}" ${FILESDIR}/* | wc -l)
        echo "The number of files are ${FILESCOUNT} and the number of matching lines are ${MATCHESCOUNT}"
	exit 0
    else
        echo "The directory ${FILESDIR} is not existing"
        exit 1
    fi
    
fi
