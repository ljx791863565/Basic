#!/bin/bash
#####################################################
BackDir=$HOME/BACKUP
Date=`date +%Y-Ym-%d`
SourceDir=$HOME
RetainDay=7
LogFile=$BackDir/log/`date +%Y-%m`.log
ProjectList=$BackDir/project.lst
#####################################################
echo "backup start at $(date + "%Y-%m-%d %H:%M:%S")" >> $LogFile
echo "-------------------------------------------------" >> $LogFile
cd $BackDir
PROJECTLIST=`cat $ProjectList`
for Project in $PROJECTLIST
do
	ProjectData=$SourceDir/$Projrct
	DestDir=$BackDir/$Project
	PackFile=$Date.$Project.tgz
	if [[ -f $BackDir/$PackFile ]]; then
		echo "backup file have exist!" >> $LogFile
	else
		cp -RHpf $ProjectData $DestDir >/dev/null
		tar -zcvf $PakcFile $Project >/dev/null
		echo "backup $Project done into $PackFile" >> $LogFile
		rm -rf $Project
	fi
	OldFile="$BackDir/"$(date -d="$RetainDay days ago" +"%Y-%m-%d").$Project.tgz
	if [[ -f $OldFile ]]; then
		rm -rf $OldFile >/dev/null
		echo "[$OldFile],Delete Old File Success!" >>$LogFile
	fi
	echo " " >>$LogFile
done 

echo "-------------------------------------------------" >> $LogFile
echo "backup end at $(date +"%Y-%m-%d %H:%M:%S")" >> $LogFile
echo " " >> $LogFile
echo " " >> $LogFile

exit
