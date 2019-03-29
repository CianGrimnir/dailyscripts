#!/usr/bin/env python 

import os, paramiko, socket, sys, time, logging, datetime, signal, multiprocessing
from multiprocessing import Pool

logging.basicConfig(filename='/home/mint/DAILY_CHECK/rakesh_script/checkall/sshException.log',level=logging.DEBUG,format='%(asctime)s %(levelname)-8s %(message)s',datefmt='%a %d %b %Y %H:%M:%S')

day=datetime.datetime.now()												# clear logfiles on Monday to reduce oversize

if day.isoweekday() == 1:
	open('/home/mint/DAILY_CHECK/rakesh_script/checkall/sshException.log','w').close()
	open('/home/mint/DAILY_CHECK/rakesh_script/checkall/PoolHandler.log','w').close()

if  not len(sys.argv) > 1:
        print("\n\033[1;31mpass args\033[1;m\nMethod of usage: python nse_ordertrack_status_V1_INT.py 'args' \n$args: \
		 1) nse\t\t:- NSE MAD check \n\t2) order \t:- Order check \n\t3) trade \t:- Trade check \n\t4) -v or -V \t:- Version\n\t \
		 5) client \t:- Client Connect\n\t6) exch \t:- Exchange response\n ")
        sys.exit(1)

if sys.argv[1] == 'nse':
	command1='''(echo "import re";echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "patt=re.compile(r'MAD+')"; \
			echo "nse_files=[f for f in os.listdir('/home/USER/USER-Application/') if f.startswith('NSE_OMS')]"; \
			echo "latest=max(nse_files, key=lambda x: os.stat(x).st_mtime)";echo "with open('/home/USER/USER-Application/%s'%latest,'r') as f: data=f.readlines()"; \
			echo "test=[f for f in data if patt.search(f)]";echo "for i in test:print i")| python '''

elif sys.argv[1] == 'order':
	command1='''(echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "logfiles=[f for f in os.listdir('/home/USER/USER-Application/') if f.startswith('OrderTra')]"; \
			echo "newest=max(logfiles, key=lambda x: os.stat(x).st_mtime)";echo "with open(newest,'r') as f: f.seek(0);lines=f.readlines()";echo "for i in lines[-10::]: print i")| python'''

elif sys.argv[1] == 'trade':
	command1='''(echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "logfiles=[f for f in os.listdir('/home/USER/USER-Application/') if f.startswith('LOG_') and os.path.isfile(f)]"; \
			echo "newest=max(logfiles, key=lambda x: os.stat(x).st_mtime)";echo "with open(newest,'r') as f: f.seek(0);lines=f.readlines()";echo "for i in lines[-10::]: print i")| python'''

if sys.argv[1] == 'exch':
        command1='''(echo "import re";echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "patt=re.compile(r'( 2126 | 2125 )+')"; \
			echo "nse_files=[f for f in os.listdir('/home/USER/USER-Application/') if f.startswith('NSE_OMS')]"; \
			echo "latest=max(nse_files, key=lambda x: os.stat(x).st_mtime)";echo "with open('/home/USER/USER-Application/%s'%latest,'r') as f: data=f.readlines()"; \
			echo "test=[f for f in data if patt.search(f)]";echo "for i in test[-10::]:print i")| python '''

if sys.argv[1] == 'client':
	command1='''(echo "import re";echo "import os";echo "os.chdir('/home/USER/USER-Application/')";echo "patt=re.compile(r'MAD+')"; \
			echo "client_files=[f for f in os.listdir('/home/USER/USER-Application/') if re.match(r'LOG_[0-9].*',f)]"; \
			echo "latest=max(client_files, key=lambda x: os.stat(x).st_mtime)";echo "with open('/home/USER/USER-Application/%s'%latest,'r') as f: data=f.readlines()"; \
			echo "test=[f for f in data if patt.search(f)]";echo "for i in test:print i")| python '''
if sys.argv[1] == '-v' or sys.argv[1] == '-V':
	print(chr(27) + "[2J")												#clear screen
	print '\nnse_ordertrack_status_V1_INT.py version \033[34m 5.3.7\033[1;m\n'
	print("Method of usage: python nse_ordertrack_status_V1_INT.py 'args' \n$args:  \
		1) nse\t\t:- NSE MAD check \n\t2) order \t:- Order check \n\t3) trade \t:- Trade check \n\t4) -v or -V \t:- Version\n\t \
		5) client \t:- Client Connect\n\t6) exch \t:- Exchange response\n ")
	sys.exit(0)

with open("/home/mint/DAILY_CHECK/rakesh_script/checkall/hostfile","r") as f: host=f.readlines()			# store IP Address from file to host
pattern=sys.argv[1]
output=[]
result={}
os.environ["PYTHONUNBUFFERED"]="1"											# To make python unbuffered, other option -> run script via 'python -u'

def INT_HANDLER():													# INTERRUPT handler initialized with each process
	signal.signal(signal.SIGINT,signal.SIG_IGN)

def paramiko_function(hosts):
	Ferror={}
	output=[]
	#pid=multiprocessing.current_process().pid									# To print pid of each process
	output.append(str('\n'+'\033[1m'+'\x1b[7;34;47m'+'For server '+hosts.strip()+'\x1b[0m'+'\n'))
	user,port,password=('user',22,'password')
	if __name__ == "__main__":
		s=paramiko.SSHClient()
		s.set_missing_host_key_policy(paramiko.AutoAddPolicy())
		try:
			s.connect(hosts,port,user,password, timeout=2)
		except socket.error as error:
			output.append(str('\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s" % error))
			Ferror[hosts]=error
			print '\n'+'\033[1m'+'\x1b[7;34;47m'+'For server '+hosts.strip()+'\x1b[0m'+'\n'
			print '\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s" % error
			return Ferror
		except paramiko.SSHException as SSHException:
			output.append(str('\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s" % SSHException))
			Ferror[hosts]=SSHException
			print '\n'+'\033[1m'+'\x1b[7;34;47m'+'For server '+hosts.strip()+'\x1b[0m'+'\n'
			print '\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s" % error
			return Ferror
		(stdin, stdout, stderr)=s.exec_command(command1)
		line=stdout.readlines()
		for i in range(len(line)-(len(line)/2)):
			if line[i]=='\n':
				line.pop(i)
		c=[i.replace("\n","") for i in line]
		for i in c: output.append(i)

		if len(c) == 0:
			output.append(str('\x1b[7;37;40m'+pattern.upper()+' NOT COMPLETE!'+'\x1b[0m'+'\n'))
			Ferror[hosts]=(pattern.upper()+' NOT COMPLETE!')
			for i in output: print i
			return Ferror

		if sys.argv[1] != 'client' and len(c) == 2 or len(c) == 1:
			output.append(str('\x1b[7;37;40m'+pattern.upper()+' file found, but EMPTY!'+'\x1b[0m'+'\n'))
			Ferror[hosts]=(pattern.upper()+' file found, but EMPTY!')

		if sys.argv[1] == 'trade' and len(line) == 4:
			output.append(str('\x1b[7;37;40m'+pattern.upper()+' file found, NO TRADE YET!!'+'\x1b[0m'+'\n'))
			Ferror[hosts]=(pattern.upper()+' file found, NO TRADE YET!!')

		if output[-2].find('COMPLETE') < 0 and sys.argv[1] == 'nse':
			output.append(str('\033[0m\033[1;31m'+' MAD COMPLETE NOT FOUND\033[1;m'))
			Ferror[hosts]=('\033[0m\033[1;31m'+' MAD COMPLETE NOT FOUND\033[1;m')

		elif sys.argv[1] == 'nse':
			output.append(str('\033[0m\033[1;35m'+'MAD COMPLETE FOUND\033[1;m'))

		err=stderr.readlines()
		if len(err) > 1:
			if not err:
				output.append(str('\033[1;31m'+pattern.upper()+' NOT EXIST IN FILE\033[1;m'))
				Ferror[hosts]=(pattern.upper()+' NOT EXIST IN FILE')

			elif any("Value" in s for s in err):								#if ValueError exception happens
				output.append(str('\033[1;31m'+pattern.upper()+' FILE NOT FOUND :-\033[1;m %s'%err[2]))
				Ferror[hosts]=(err[2],pattern.upper()+' FILE NOT FOUND')

		for i in output:
			print i

		s.close()
		if len(Ferror.items()) > 0:										# return empty dict if Ferror is empty, else return actual value
			return Ferror
		else:
			return {}

def main():
	result={}
	sys.stderr=open('/home/mint/DAILY_CHECK/rakesh_script/checkall/PoolHandler.log','a')				# write std.error to file mentioned
	sys.stderr.write("\n"+sys.argv[0]+"\t"+time.ctime()+"\n\n")							# write strings to stderr
	multiprocessing.log_to_stderr(logging.DEBUG)									# LOGGING multiprocess threads
	pool=Pool(5,INT_HANDLER)											# create pool of n process, having INT_HANDLER as initializer function
	try:
		for Ferror in pool.imap_unordered(paramiko_function,host,chunksize=4):							# fetch return dict from paramiko_function, pool.imap act as iterator function
			try:
				if len(Ferror.items()) > 0:								# if returned dict not empty store it in result dict
					for k,v in Ferror.items():
						result[k]=v
			except AttributeError:
				pass
			pass
	except KeyboardInterrupt:											# handle KeyboardInterrupt, it "work" because INT_HANDLER is initialized with each process
		print('\n\033[0m\033[1;31m'+'SIGINT signal recieved\033[1;m\n');
		sys.exit(0)

	for k,v in result.items():											# print error along with it's IP at the end
		print("\n"+'\033[1m'+'\x1b[7;34;47m'+k.strip()+'\x1b[0m')
		m=list(result[k])
		if len(m) == 2:
			m,n=result[k]
			print "\n"+'\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s \n" %(n)
			continue
		print "\n"+'\x1b[7;31;47m'+"Error :"+'\x1b[0m'+" %s \n" %(''.join(i for i in m))

if __name__ == "__main__":
	main()
