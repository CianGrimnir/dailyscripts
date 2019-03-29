#!/bin/bash

declare -a arr_placed
declare -a response
max="1.0"
day=$(date +%d-%b-%Y)
PLACED=0

cd /home/USER/USER-Application/
[[ $# -eq 1 ]] && { file=$1; } || { file=`ls -t NSE_OMS*|head -1`; }

( echo -e "\nFile :  $file\n"
echo -e "Diff \t\t PLCED TIME \t\t RESP TIME "
tail -f "$file" | grep -iE --line-buffered 'placed|TRANS .*( 2125 | 2155 )' | while read p
do      
	if [[ $PLACED -eq 0 ]] 
        then
               [[ $(grep -i 'placed' <<< $p) ]] && { PLACED=1; } || { continue; }
	fi
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
done ) | tee  /home/USER/tail_finalOP
#echo -e "\nPLACED VALUE LEFT: ${#arr_placed[@]} \t RESPONSE VALUE LEFT: ${#response[@]}\n"
