#!/bin/bash
cd /home/USER/TICK_READER_1/
TickTrack=$(ls -t TickTracker1* | head -1)
tail -100f $TickTrack | grep  --line-buffered -vE 'started|WriteToLogFile' | while read a;do 
echo "$a" |awk -F" " '{ 
	 if ($2 ~ /Unwind/) {gsub($2,"\033[0m\033[0;34m&\033[1;m");gsub($3,"\x1B[1;97;44m & \033[1m\033[0;34m");gsub($10,"\x1B[1;97;44m & \033[1m\033[0;34m"); print $0,"\033[1;m" } else {gsub($2,"\033[0m\033[0;32m&\033[1;m")gsub($3,"\x1B[1;97;42m & \033[1m\033[0;32m");gsub($10,"\x1B[1;97;42m & \033[1m\033[0;32m"); print $0,"\033[1;m" }}'; done  > out_LOG &
