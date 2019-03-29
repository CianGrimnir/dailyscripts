#!/bin/bash
date=$(date +%d%m%y)
#serverlist="106 107  222  147 206 29 129 132 130 144 133  241 128 127 126 134 148 214 217 135 189 190 191  168 169 220 221 166 249 113 114 167 183 110 111 112 187 246 244 186  184  194 195 188 122 243 109 151 242 153 172 140 141 143  228 229 230 231  152 247 136 219  251 196 223 117 118 192 193 250 207 173 174 175 176 177 178 179 180 181 182"
serverlist="200 201 202 203 204 205 209 210 211 212 212 213 216 218 "
for i in $serverlist;
do
	sshpass -p 'password' ssh USER@192.168.145.$i "bash NSE_PLACED_test_CR.sh" &
done
wait

for i in $serverlist;
do
	 ( echo -e "\n\t\t\t\e[1m 192.168.145.$i  \e[0m\n"; sshpass -p 'password' ssh USER@192.168.145.$i " cat FINAL_OP " ) >> FINAL_OP_CR_T${date}
done 
echo -e "\nFIN."
