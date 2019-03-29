#!/bin/bash

which bc > /dev/null 2>&1
[[ $? -ne 0 ]] && { echo "bc not found."; exit; }

declare -a arr_placed
declare -a response
max="1.0"
day=$(date +%d-%b-%Y)
arr=($(find /home/USER/USER-Application/ -maxdepth 1 -mtime -1  -iname "NSE_OMS*"))
for file in "${arr[@]}"
do
	arr_placed=()
	response=()
	echo -e "\nFile :  $file\n"
	echo -e "\e[1mDiff \t\t PLCED TIME \t\t RESP TIME\e[0m"
	while read p
	do
		if [[ $(grep -i 'placed' <<< $p) ]]
		then
			arr_placed+=($(awk -v var=$day 'BEGIN{cmd="date +%s.%6N -d "} {gsub(/[][]/,"");a=varFS$1;cmd a|getline var1;print var1;}'  <<< $p))
			if [ "${#response[@]}" -gt 0 ]
			then
				diff="$(echo ${arr_placed[0]}-${response[0]}|bc)"
		                if awk 'BEGIN{exit ARGV[1]<ARGV[2]}' "$diff" "$max"; then echo -e "$diff\t `date -d@${arr_placed[0]} +%H:%M:%S.%6N` \t `date -d@${response[0]} +%H:%M:%S.%6N` "; fi
	        	        arr_placed=( "${arr_placed[@]:1}" )
				response=( "${response[@]:1}" )
			fi
		elif [[ $(grep -i 'TRANS' <<< $p) ]]
		then
			if [ ${#arr_placed[@]} -eq 0 ]
			then
				response+=($(awk -v var=$day 'BEGIN{cmd="date +%s.%6N -d "} {gsub(/[][]/,"");a=varFS$1;cmd a|getline var1;print var1;}'  <<< $p))
				continue;
			fi
			response+=($(awk -v var=$day 'BEGIN{cmd="date +%s.%6N -d "} {gsub(/[][]/,"");a=varFS$1;cmd a|getline var1;print var1;}'  <<< $p))
			diff="$(echo ${response[0]}-${arr_placed[0]}|bc)"
			if awk 'BEGIN{exit ARGV[1]<ARGV[2]}' "$diff" "$max"; then echo -e "$diff\t `date -d@${arr_placed[0]} +%H:%M:%S.%6N` \t `date -d@${response[0]} +%H:%M:%S.%6N` "; fi
			arr_placed=( "${arr_placed[@]:1}" )
			response=( "${response[@]:1}" )
		fi
#	done < <(awk -F' ' ' /PLACED/ || $4 ~ /2155|2125/ ' "$file")
	done < <(awk -F' ' ' ($0 ~ /PLACED/) || ($4 ~ /2155|2125/) && ($2 ~ /TRANS/){print $0}'  "$file")
echo -e "\nPLACED VALUE LEFT: ${#arr_placed[@]} \t RESPONSE VALUE LEFT: ${#response[@]}\n"
done > FINAL_OP
