#!/bin/bash
date=$(date +%d%m%y)
serverlist="124 188 130 145 144 158 154 159 133 216 218 168 151 152 141 169 132 142 180 149 129 170 171 125 135 131 143 172 173 174 184 186 178 200 201 202 204 24 26  27 28 226 227 252 253 160 161 162 163 220 221 225 232 112 113 114 115 130 193 166 183"
#serverlist="183 193 145 173 227 27 218 124 159 252 145 130"
for i in $serverlist;
do
	sshpass -p 'password' ssh USER@192.168.120.$i "bash NSE_PLACED_test.sh" &
done
wait

for i in $serverlist;
do
	 ( echo -e "\n\t\t\t\e[1m 192.168.120.$i  \e[0m\n"; sshpass -p 'password' ssh USER@192.168.120.$i " cat FINAL_OP " ) >> FINAL_OP${date}
done 
echo -e "\nFIN."
