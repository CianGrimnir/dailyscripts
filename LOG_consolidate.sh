#!/bin/bash

declare -a arr
declare -a logarr
IFS=$'\n'
j=0
arr=($(awk  -v prev=0  'BEGIN{OFS="|";cmd="date +%s.%6N -d "} {gsub(/[][]/,"")} /execType F/ {b=$1;cmd b|getline new;print $1,$10,$22,$(NF-6),$20,$(NF-4),$NF,new-prev;prev=new}' OrderTracker_02670_00))
for i in `awk -F"|" '{print $2}' <<< "${arr[*]}"`; do  
	logarr+=($(awk -v temp=1 -v i=0 -v var=$i 'BEGIN{OFS=" "}
			{if ($NF==var){split($2,a,"[,]");
				$1=$2=$NF=$(NF-1)="";arr[i++]=$0"|"substr(a[1],2,length(a[1]))"|"substr(a[2],1,length(a[2]-1))}}
					END{if (length(arr) == 1)
						 {for (i in arr) 
							{trade=0;print arr[i],"Trade detected",trade}} 
					else  { for (i in arr) {if (arr[i] ~ /Trade detected/ && temp == 1) 
							{trade=1;print arr[i+1],"Trade detected ",trade;exit;} 
			else {trade=1;print arr[i],"Trade detected",trade;exit;}}}}' LOG_FILE_CUSTOM_FIX_02670_00))
done

for i in `awk -F'[| ]' '{print $(NF-3)"|"$(NF-4)}' <<< "${logarr[*]}"`;do
	echo "${arr[j]}" "${logarr[j]}"
	j=$((j+1))
	#awk -v var=$i -F'[|:]' '{split(var,a,"|");if ($3==a[1] || $3==a[2]) {print $0}}' NCDEX_log_file_02711_00
	grep -Ew "ApplSeqNo:($i)" NCDEX_log_file_02711_00
done > /tmp/arun
