#!/usr/bin/env python 

import paramiko, socket, sys, logging, datetime, re, signal, multiprocessing, time, os
from multiprocessing import Pool

output=[]
result={}
logging.basicConfig(filename='/home/mint/DAILY_CHECK/rakesh_script/checkall/sshException.log',level=logging.DEBUG,format='%(asctime)s %(levelname)-8s %(message)s',datefmt='%a %d %b %Y %H:%M:%S') 	# formating logging

day=datetime.datetime.now()
if day.isoweekday() == 1:													# if day is monday, clear the file content
	open('sshException.log','w').close()

if len(sys.argv) > 1:
	if  sys.argv[1] == '-h':
		print "\033[1;31mpass args\033[1;m\n\nMethod of usage: python USER_statergy.py 'pattern' \n"
		sys.exit(0)
	pattern=sys.argv[1]
	re_pattern=re.compile(r'%s' %pattern,re.I)
command1='''(echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "strategy=os.readlink('USER_Application')";echo "print strategy")| python '''		# exec_command to execute in remote machine
strategy='USER_application'
f=open("/home/mint/DAILY_CHECK/rakesh_script/checkall/hostfile","r")
host=f.readlines()
f.close()
os.environ["PYTHONUNBUFFERED"]="1"													# setting python stdout unbuffered

def INT_HANDLER():
        signal.signal(signal.SIGINT,signal.SIG_IGN)

def strategy_function(hosts):
	Ferror={}
	output=[]
	user,port,password=('USER',22,'password')
	if __name__ == "__main__":
		s=paramiko.SSHClient()
		s.set_missing_host_key_policy(paramiko.AutoAddPolicy())
		try:
			s.connect(hosts,port,user,password)
		except socket.error,error:
			Ferror[hosts]=error
		except paramiko.SSHException,SSHException:
			Ferror[hosts]=SSHException
		(stdin, stdout, stderr)=s.exec_command(command1)
		line=stdout.readlines()
		c=[i.replace("\n","") for i in line]
		if len(c) == 0:														# executable file not found
			print('\n\x1b[7;37;40m'+strategy.upper()+'  NOT FOUND!!'+'\x1b[0m'+'\n')
			Ferror[hosts]=(strategy.upper()+'  NOT FOUND!!')
		try:
                        if re_pattern:													# list only backend having specific pattern in exectuable filename ( passed as argument )
                                if re_pattern.search(c[0]):
                                        output.append('\n'+'\033[1m \033[94m'+'For server '+hosts.strip()+'\033[0m\t'+c[0])
                except NameError:
			pass
                        output.append('\n'+'\033[1m \033[94m'+'For Server '+hosts.strip()+'\033[0m\t'+c[0])
		for i in output:													# print appended stdout values from output 
			print i
		if len(Ferror.items()) > 0:												# if Ferror is empty return empty dict , else { actual value }
			return Ferror
		else:
			return {}
		s.close()


def main():
	result={}
        sys.stderr=open('/home/mint/DAILY_CHECK/rakesh_script/checkall/PoolHandler.log','a')						# redirecting stderr to file
        sys.stderr.write("\n"+sys.argv[0]+"\t"+time.ctime()+"\n\n")									# write to stderr
        multiprocessing.log_to_stderr(logging.DEBUG)											# multiprocessing logging stderr
        pool=Pool(3,INT_HANDLER)													# creating pool of n process at a time
        try:
                for Ferror in pool.imap(strategy_function,host):									# generating dict of return values ( Ferror ), INT_HANDLER initializer function for each process 
                        try:
                                if len(Ferror.items()) > 0:
                                        for k,v in Ferror.items():
                                                result[k]=v
                        except AttributeError:
                                pass
                        pass
	except KeyboardInterrupt:													# keyboard interrupt handler making use of INT_HANDLER function
                print('\n\033[0m\033[1;31m'+'SIGINT signal recieved\033[1;m\n');
                sys.exit(0)

	for k,v in Ferror.items():													# printing returned values
		m=list(Ferror[k])
		if len(m) == 2:
			m,n=Ferror[k]
			print "\n"+'\033[1m'+'\x1b[7;34;47m'+k.strip()+'\x1b[0m'+"\t"+'\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s \n" %(n)
			continue
		print "\n"+'\033[1m'+'\x1b[7;34;47m'+k.strip()+'\x1b[0m'+"\t"+'\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s \n" %(''.join(i for i in m))
if __name__ == "__main__":
	main()
