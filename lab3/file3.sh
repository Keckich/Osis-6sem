#!/bin/bash


if [ $# -ne 1 ]; then
	echo "Enter: ./`basename $0` filename"
	exit 1
fi

sed -i '1s/^[a-z]/\U&/' $@ # 1st symbol in file
sed -i 's/[!?\.][!?\.]*.[a-z]/\U&/g' $@ # one symbol after ! or ? or .
sed -i ':a;N;$!ba;s/[!?\.][!?\.]*\n*[a-z]/\U&/g' $@ # one symbol after ! or ? or . on the next line
