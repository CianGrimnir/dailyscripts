#!/usr/bin/env python

# File : 	file_trans_win_dir.py
# Author by: 	Rakesh.N
# Purpose: 	File/Directory transfer from local to remote Linux/Windows system

import os
import paramiko
import sys

if  not len(sys.argv) > 5:
	print "Usage: python file_transfer.py $HOST $USER $LOCAL_PATH $REMOTE_PATH $LOCAL_FILE \n"
#	Usage:	
# 	python file_trans_win.py  192.168.20.202 ritesh $PWD/ D:\\ count.py 	  	-----> Windows
#	python file_trans_win_dir.py 192.168.20.189 vinit $PWD/ /tmp/testing/ exercise	 ---> Directory
	sys.exit()

(host,user,local_path,remote_path)=sys.argv[1:5]
password="password"		#password="wonderwall9210"
local_file=list([x.split(' ') for x in sys.argv[5:]])

paramiko.util.log_to_file('/tmp/win.log')
transfer=paramiko.SSHClient()
transfer.set_missing_host_key_policy(paramiko.AutoAddPolicy())
transfer.connect(hostname=host,port=22,username=user,password=password)
sftp=transfer.open_sftp()

def Directory_Transfer(localpath,remotepath,win):
	os.chdir(os.path.split(localpath)[0])
	parent=os.path.split(localpath)[1]
	print "Directory  %s  Transfer : %s System : %s  Parent Dir : %s\n" %(localpath,remotepath,win,parent)
	for walker in os.walk(parent):
		try:
			if win:
				sftp.mkdir(os.path.join(remotepath.replace('\\','/'),walker[0]).replace("/","\\"))
				#print(os.path.join(remotepath.replace('\\','/'),walker[0]).replace("/","\\"))
			else:
				sftp.mkdir(os.path.join(remotepath,walker[0]))
				#print(os.path.join(remotepath,walker[0]))
		except IOError as IO:
			print "Error: %s" %IO
		for file in walker[2]:
			if win:
				sftp.put(os.path.join(walker[0],file),os.path.join(remotepath.replace("\\","/"),walker[0],file).replace("/","\\"))
				#print(os.path.join(walker[0],file),os.path.join(remotepath.replace("\\","/"),walker[0],file).replace("/","\\"))
			else:
				sftp.put(os.path.join(walker[0],file),os.path.join(remotepath,walker[0],file))
				#print(os.path.join(walker[0],file),os.path.join(remotepath,walker[0],file))

#def Get_Directory(remote_path,local_path,win):     yet to define

system=int(raw_input("Enter remote system OS :\n0.linux\n1.Windows\n"))
for files in local_file:
	file_transfer=local_path + files[0]
	remote_loc=remote_path + files[0]
	if os.path.isdir(file_transfer):
		Directory_Transfer(file_transfer,remote_path,system)
	else:
		print file_transfer + '  >>>>  ' + remote_loc
		sftp.put(file_transfer,remote_loc)

sftp.close()
transfer.close()
