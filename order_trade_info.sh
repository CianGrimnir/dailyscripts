#!/bin/bash

cd /home/USER/USER-Application/LOGS/
time=",1166109781"									# Jan EXP date :- 1166109781
touch Order_bidding_237.csv
iconv -t UTF-8 Order_bidding_237.csv							# CSV GENERATE
for i in `ls -lhtr | awk '/Dec 13/ && /OrderTracker_*/ {print $9}'		`	# Extracting OrderTracker file of Dec 13 date
do
        grep '1169821800.*20222' ${i} |awk '{print $4}' > temp1				# Redirecting obtained order_number of specified date and 20222 pattern to file temp1
        for var in `cat temp1`								# Looping through order_number	
        do	echo $var >> Order_bidding_237.csv					# First field of CSV file :- Order number 
                value=`grep "$var.*20073" ${i} | awk '{print $2}'|cut -d'#' -f2`	# Assign Sequence number of specific order_number matching 20073 pattern to value variable
		sed -i "/^$var/s/$/, $value/g" Order_bidding_237.csv			# Second field of CSV file :- sequence number 
#		sed -i "/^$var/s/$/ $time/g" Order_bidding_237.csv
        done
done
awk  '{$3=",1166109781";}1'  Order_bidding_237.csv > Order_bidding_237_FINAL.csv	# Final CSV file will have order_number, sequence_number and latest logtime of Dec 13 field in specified order
sed -i 's/ //g' Order_bidding_237_FINAL.csv						# Removing Blank spaces between fields
