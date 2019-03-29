#!/usr/bin/env python

import subprocess, os, sys, string, threading, errno, logging, datetime, signal, time, multiprocessing
from multiprocessing import Pool

blaclist=['20.26']
a=[]
global Ferror
Ferror={}
result={}
pun=string.punctuation

with open("hostfile","r") as f: server=f.readlines()
os.environ["PYTHONUNBUFFERED"]="1"									# To make python unbuffered, other option -> run script via 'python -u'

def timeout(p):												# subprocess don't have builtin timeout function to terminate session, custom timeout to handle it
	if p.poll() is None:
		try:
			p.kill()
			global Ferror
			global exi
			print('\n \033[1;36m'+ip.strip('\n')+'\033[0m\033[1;31m'+' unreachable!\033[1;m')
			Ferror[ip]=('\n \033[1;36m'+ip.strip('\n')+'\033[0m\033[1;31m'+' unreachable!\033[1;m')
			exi=0
		except OSError as e:
			if e.errno != errno.ESRCH:
				raise

def INT_HANDLER():											# SIGNAL INTERRUPT HANDLER
	signal.signal(signal.SIGINT,signal.SIG_IGN)

def subprocess_function(j):
	global ip
	global Ferror
	Ferror={}
	a=[]
	ip=j
	global exi
	exi=1
	timer=2.0
	if '.'.join(j.strip().split('.')[-2:]) in blaclist:
		timer=4.0
	host="user@"+j.strip()
	command1='''(echo "import os";echo "name='process_name'";echo "r=os.popen('ps -ef').read().strip().split(\n)";echo "print [r[i] for i in range(len(r)) if name in r[i]]")| python'''
	ssh=subprocess.Popen(["ssh","%s" % host,command1],shell=False,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	t=threading.Timer(timer,timeout,[ssh])								# creating thread timer
	t.start()											# starting thread, timeout function will be called after time defined in timer variable
	result1=ssh.stdout.readlines()
	error=ssh.stderr.readlines()
	result2=result1
	ll=str(''.join([o for o in result2 if o not in pun]).replace('\n',''))
	for word in ll.split():
		a.append(word)
#	r=0
	for i in range(0,1):
		try:
			if a[i].find('name'):
				a.pop(i)
		except IndexError:
			pass
	if len(a) > 0:
		print('\n \033[1;36m'+j.strip('\n')+'\033[0m\033[1;32m'+' running\033[1;m')
	elif not a and exi!=0 and not error and t.is_alive():
			print('\n \033[1;36m'+j.strip('\n')+'\033[0m\033[1;31m'+' not running\033[1;m')
			Ferror[j]=('\n \033[1;36m'+j.strip('\n')+'\033[0m\033[1;31m'+' not running\033[1;m')
	elif not a and exi!=0 and not error and not t.is_alive():
			Ferror[ip]=('\n \033[1;36m'+ip.strip('\n')+'\033[0m\033[1;31m'+' unreachable.\033[1;m')
	try:
		if error[0].startswith('ssh:') and exi != 0 :
			print('\n \033[1;36m'+j.strip('\n')+'\033[0m\033[1;31m'+' unreachable.\033[1;m')
			Ferror[j]=('\n \033[1;36m'+j.strip('\n')+'\033[0m\033[1;31m'+' unreachable.\033[1;m')
	except IndexError:
		pass
        if len(Ferror.items()) > 0:									# return empty dict if Ferror is empty, else return actual value
		return Ferror
        else:
                return {}

def main():
	result={}
        sys.stderr=open('logging.log','a')            # write std.error to file mentioned
        sys.stderr.write("\n"+sys.argv[0]+"\t"+time.ctime()+"\n\n")                                     # write strings to stderr
        multiprocessing.log_to_stderr(logging.DEBUG)                                                    # LOGGING multiprocess threads
	pool=Pool(8,INT_HANDLER)									# create pool of n process, having INT_HANDLER as initializer function
	try:
		for Ferror in pool.imap(subprocess_function,server):					# fetch return dict from subprocess_function
			try:
				if len(Ferror.items()) > 0:						# if returned dict not empty store it in result dict
					for k,v in Ferror.items():
						result[k]=v
			except AttributeError:
				pass
		pass
	except KeyboardInterrupt:									# handle KeyboardInterrupt, it works because INT_HANDLER is initialized with each process
		print('\n\033[0m\033[1;31m'+'SIGINT signal recieved\033[1;m\n');
                sys.exit(0)

	print("\r")
	for k,v in result.items():									# print error along with it's IP at the end
                m=list(result[k])
                if len(m) == 2:
                        m,n=result[k]
                        print " %s \n" %(n)
                        continue
                print " %s " %(''.join(i for i in m))

if __name__ == "__main__":
        main()
