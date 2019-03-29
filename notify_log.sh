#!/bin/bash

#logging notify messages in specified logfile


#dbus-monitor "interface='org.freedesktop.Notifications'"|grep --line-buffered "string"|  grep --line-buffered "string"| grep --line-buffered -e method -e ":" -e '""' -e urgency -e notify -v|awk '{print $NF;exit;}' | xargs -I '{}' printf "---$(date )---\n"{}"\n" >> $HOME/accesslogs/notify_log 
#dbus-monitor "interface='org.freedesktop.Notifications'"|grep --line-buffered "string" | grep --line-buffered -e method -e ":" -e '""' -e urgency -e category -e notify -v | grep  --line-buffered '[^ ]+$' -oE | xargs -I '{}' printf "---$( date +"%D %H:%m:%S" )---\n"{}"\n" >> $HOME/accesslogs/notify_log
dbus-monitor "interface='org.freedesktop.Notifications'"|grep --line-buffered "string" | grep --line-buffered -e method -e ":" -e '""' -e urgency -e category -e notify -v |  sed -ue $'s/string//g'  |ts "[%D %H:%M:%S]" >> $HOME/accesslogs/notify_log
