#!/bin/bash

#shell编程技巧

#debug头处理
debug=$(echo $@ | grep "\-\-debug" | wc -l)
debug_echo()
{ 
	if [[ "$debug" == "1" ]];then 
		message="$(date +%s) $1"; 
		echo "$message" 1>&2; 
		logger "$message";
	fi 
}

#防止任务重复执行
[[ "$(pidof ${0##*/} | wc -w)" -gt "2" ]] && echo "Already running ..." && return 2

echo "xxxx" 2>&1 #将标准错误重定向到标准输出
