#!/bin/zsh 

path=$1
fileslist=$(find $1 -type f)
for i in $fileslist
do 
	convmv -f GBK -t UTF-8 -r --notest $i > temp
	if [ $? -eq 0];then 
		mv temp > $i
done
