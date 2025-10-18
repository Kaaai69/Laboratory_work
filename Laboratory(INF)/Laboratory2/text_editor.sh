#!/bin/bash
touch notes.txt
while read -r line;
do
    for word in $line; do	
	if [ "$word" == "exit" ]; then
	    break 2
	fi
    done
    echo $line >> notes.txt
done
cat notes.txt	
rm notes.txt

