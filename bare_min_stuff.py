#! /usr/local/bin/python2.6
############################################################################
# File name : bare_min_stuff.py                                            #
# Purpose   : To download/build/install the bare minimum components to make#
#             Ubuntu based servers/workstations ready.                     #
# Usages    : python2.6 base_min_stuff.py (or type ./bare_min_stuff on the #
#             shell if executable flag is set).                            #
# Start date: 12/06/2009                                                   #
# End date  : 18/06/2009                                                   #
# Author    : Ankur Kumar (ankur@USERaddress)                             #
# Modification history : if tracked by bazaar then type                    #
#                        "bzr log bare_min_stuff.py" for the revision      #
#                        history or "bzr diff bare_min_stuff.py" to see the#
#                        code changes.                                     #
############################################################################

# this dictionary contains base packages names and download url for wget.
basePckgsWget = {
#                 'kernel source' : ('linux-2.6.30.tar.bz2', 'kernel.org/pub/linux/kernel/v2.6/'),
#                 'rt patch'      : ('patch-2.6.30-rt.bz2', 'kernel.org/pub/linux/kernel/projects/rt/'),
                 'ncurses'       : ('ncurses-5.7.tar.gz', 'ftp.gnu.org/pub/gnu/ncurses/'),
                 'lzo2'          : ('lzo-2.03.tar.gz', 'oberhumer.com/opensource/lzo/download/'),
                 'bazaar'        : ('bzr-2.0.0.tar.gz', 'launchpad.net/bzr/2.0/2.0.0/+download/'),
                 'cppcheck'      : ('cppcheck-1.33.tar.bz2', 'sunet.dl.sourceforge.net/sourceforge/cppcheck/'),
#                 'ACE'           : ('ACE-5.7.0.tar.bz2',  'download.dre.vanderbilt.edu/previous_versions/'),
                }
                
pckgsBldRules = {
#                 'kernel source'  : ('make', 'make modules_install', 'make install',),
#                 'rt patch'       : ('', '', '',),
                 'ncurses'        : ('./configure --with-shared', 'make', 'make install',
                                     'make clean', 'make distclean',),
                 'lzo2'           : ('./configure --enable-shared', 'make', 'make install',
                                     'make clean', 'make distclean',),
                 'bazaar'         : ('python2.6 setup.py install build_ext --allow-python-fallback',),
                 'cppcheck'       : ('make all', 'make install', 'make clean',),
#                 'ACE'            : ('mkdir objdir', 'cd objdir', 'configure --without-ssl', 
#                                     'make', 'make install', 'make clean', 'make distclean',), 
                } 

# this dictionary contains base packages names for apt-get.
basePckgsApt = {
                'pgsql headers' : 'libpq-dev', 
                'gmake'         : 'make',
                'gdb'           : 'gdb',
                'libtool'       : 'libtool',
                'emacs'         : 'emacs',
                'ngrep'         : 'ngrep',
                'gcc multilib'  : 'gcc-4.3-multilib',
                'g++ multilib'  : 'g++-multilib',
                'doxygen'       : 'doxygen',
                'graphviz'      : 'graphviz',
                'autoconf'      : 'autoconf',
                'manpages'      : ('manpages-dev', 'glibc-doc', 'manpages-posix-dev'),
                'valgrind'      : 'valgrind',
               }
                
# these strings carry the apt, wget and archives unpack commands .
strAptUpdt      = 'apt-get update '
strApt          = 'apt-get install -y '
strWget         = 'wget  --no-check-certificate ' 
strTgz          = 'tar -zxvf '
strTbz2         = 'tar -jxvf '
 
# this dictionary  carry the users to be added along with the passwords.
dusrsToBeCreated = {
                    'mint' : 'password',
                   } 

# this list carry the system files and the enteries to be modified/appended.
dsysflsToBeModified = {
                       '/etc/sudoers' : ('mint ALL=(ALL) ALL\n',),
                       '/etc/default/rcS' : ('TMPTIME=-1\n',),
                       '/etc/ssh/sshd_config' : ('UseDNS no\n',),
                       '/etc/sysctl.conf' : ('kernel.core_pattern = core.%e%s%h\n',),
                       '/etc/security/limits.conf' : ('* soft core unlimited\n',),
                      } 

# this dictionary contains the paths and the directories to be created there
# with the permissions masks.
ddirsToBeCreated = {
                    '/tmp' : {'LOGS' : 0777, 'LOGS/OPTION' : 0777, },
                   } 
 
# these lists carry the packages installation success or failure for apt.
pckgsSuccessApt = []
pckgsFailureApt = []

# these lists carry the packages source archives download success or failure
# for wget.
pckgsSuccessWget = []
pckgsFailureWget = []

# these lists carry the sources unpack success or failure.
unpkSuccessArchiv = []
unpkFailureArchiv = []

# these lists carry the installation success or failure from source archives.
instlSuccessWget = []
instlFailureWget = []

# these lists carry the directories creation with required permissions success
# or failure.
dircreateSuccess = []
dircreateFailure = []

# string to store current working directory to finally come back.
sCurWkgDir       = ''

# function to install packages using apt and download the source archives using
# wget.
def pckgsInstall():
    
    # first sync with the global apt repository
    r = -1
    try:
        r = os.system(strAptUpdt)
    except Exception, e:
        print
        print ' Error : sync to apt global repository failed' + ',' + e   
        print
    
    # now install apt packages
    for bPA in basePckgsApt:
        if types.TupleType == type(basePckgsApt[bPA]):
            for a in basePckgsApt[bPA]:
                try:
                    r = os.system(strApt + a) 
                    if 0 == r:
                        pckgsSuccessApt.append(a)
                    else:
                        pckgsFailureApt.append(a)    
                except Exception, e:
                    pckgsFailureApt.append(a)
                    print
                    print ' Error : installation of ' + a + ' failed' + ',' + e
                    print
         
        else:
            try:
                r = os.system(strApt + basePckgsApt[bPA])
                if 0 == r:
                    pckgsSuccessApt.append(basePckgsApt[bPA])
                else:
                    pckgsFailureApt.append(basePckgsApt[bPA])    
            except Exception, e:
                pckgsFailureApt.append(basePckgsApt[bPA])
                print
                print ' Error : installation of ' + basePckgsApt[bPA] + ' failed' + ',' + e    
                print 
                            
    # finally download source archives
    for bPW in basePckgsWget:
        if types.TupleType == type(basePckgsWget[bPW]):
            try:
                r  = os.system(strWget + basePckgsWget[bPW][1] + basePckgsWget[bPW][0])
                if 0 == r:
                    pckgsSuccessWget.append(bPW)
                else:
                    pckgsFailureWget.append(bPW)        
            except Exception, e:
                pckgsFailureWget.append(bPW)               
                print
                print ' Error : download of ' + basePckgsWget[bPW][0] + ' failed' + ',' +  e
                print
                
# function to install packages from source archives
def pckgsInstallFromSource():
    
    # first unpack all the successfully downloaded archives.
    for asp in pckgsSuccessWget:
        sExt = basePckgsWget[asp][0].split('.').pop().lower()
        strUnpk = ''
        if 'gz' == sExt:
            strUnpk = strTgz
        elif 'bz2' == sExt:
            strUnpk = strTbz2
        try:
            r = os.system(strUnpk + basePckgsWget[asp][0])
            if 0 == r:
                unpkSuccessArchiv.append(asp)
            else:
                unpkFailureArchiv.append(asp)
        except Exception, e:
            unpkFailureArchi.append(asp)
            print
            print ' Error : unpacking of ' + basePckgsWget[asp][0] + ' failed' + ',' + e       
            print
                                                    
    # now record current working diectory.
    sCurWkgDir = os.getcwd()
    
    # now move to the successfully unpacked archives directories and apply
    # their respective build steps.
    for asp in unpkSuccessArchiv:
        if types.TupleType == type(basePckgsWget[asp]):
            try:
                sPckgDir = ''
                if 'ACE' == asp:
                    sPckgDir = 'ACE_wrappers'
                else:
                    sPckgDir = basePckgsWget[asp][0].split('.tar')[0]
                
                if os.path.isdir(sPckgDir):
                    os.chdir(sPckgDir)
                else:
                    instlFailureWget.append(asp)
                    print
                    print ' Error : no ' + sPckgDir + ' directory exists.'    
                    print
                    continue
                
                l = len(pckgsBldRules[asp])
                for act in pckgsBldRules[asp]:
                    try:
                        r = os.system(act)
                        if r != 0:
                            instlFailureWget.append(asp)
                            break
                        else:
                            l = l-1
                            if 0 == l:
                                instlSuccessWget.append(asp)    
                    except Exception, e:
                        instlFailureWget.append(asp)    
                        print
                        print ' Error : execution of ' + act + ' failed.' + ',' + e
                        print
            
                try:
                    os.chdir(sCurWkgDir)
                except:
                    print ' Error : chdir ' + ',' + e     
                    exit(-1)
            except Exception, e:
                instlFailureWget.append(asp)        
                print
                print ' Error : installation of ' + basePckgsWget[asp][0] + ' failed' + ',', e
                print

# function to add settings in various configuration file.
def addSettingsToConfFiles():

    for itrcf in dsysflsToBeModified:
    
        try:
            if not os.path.isfile(itrcf):
                print ' Error : system file ' + itrcf + ' doesn not exist.'
                continue
            else:
                backupAndAddSettings(itrcf)    
        except Exception, e:
            print ' Error : os.path.isfile(' + itrcf + ') , ' + str(e)
            continue
            
# function to backup original conf files and create new conf files with added
# settings.
def backupAndAddSettings(itrcf):

    # first copy original system file to backup file with unique time stamp.
    ore = re.compile('\s+')
    ts = time.asctime()
    sfbak = itrcf + '.bak.' +  re.split(ore, ts)[3]
    try:
        shutil.copy(itrcf, sfbak)
    except Exception, e:
        print ' Error : shutil.copy(' + itrcf + ', ' + sfbak +') , ' + str(e)
        return False
        
    try:
        ocf = open(itrcf, 'ab')
        try:
            ocf.write(dsysflsToBeModified[itrcf][0])
            ocf.close()
        except Exception, e:
            print ' Error : write(' + dsysflsToBeModified[itrcf][0] + ') , ' + str(e)    
            return False
    except Exception, e:
        print ' Error : open(' + itrcf + ' , \'rba\') , ' + str(e)
        return False
        
    return True    
                   
# function to create directories and set their permissions.
def addDirChPer():

    for itrdp in ddirsToBeCreated:
    
        if not os.path.isdir(itrdp):
            print ' Error : partition ' + itrdp + ' does not exist.'
            for itrdd in ddirsToBeCreated[itrdp]:
                dircreateFailure.append(itrdp + os.sep + itrdd)
            continue
        else:
            for itrd in ddirsToBeCreated[itrdp]:
                if not os.path.isdir(itrdp+ os.sep + itrd): 
                    try:
                        os.makedirs(itrdp + os.sep + itrd)
                        dircreateSuccess.append(itrdp + os.sep + itrd)
                    except Exception, e:
                        print ' Error : os.mkdir(' + itrdp + os.sep + itrd + ') , ' + str(e)
                        dircreateFailure.append(itrdp + os.sep + itrd)
                    
                else:
                    print ' Error : ' + itrdp + os.sep + itrd + ' already exists.'
                    dircreateFailure.append(itrdp + os.sep + itrd)
                    
                try:
                   os.chmod(itrdp + os.sep + itrd, ddirsToBeCreated[itrdp][itrd])
                except Exception, e:
                   print ' Error : os.chmod(' + itrdp + os.sep + itrd + ',' + str(ddirsToBeCreated[itrdp][itrd]) + ') , ' + str(e)
                   continue           
                    
    return True                                   

# function to print installation summary.
def intlnSummary():

    pass
        

# body in case the file is not imported.
if '__main__' == __name__:
     
     try:
         import types
     except Exception, e:
         print ' Error : import types', e    
         exit(-1)
     
     try:
         import os
     except Exception, e:
         print ' Error : import os', e
         exit(-1)
         
     try:
         import os.path
     except Exception, e:
         print ' Error : import os.path', e
         exit(-1)  
     
     try:
         import shutil
     except Exception, e:
         print ' Error : import shutil', e
         exit(-1)
     
     try:
         import time
     except Exception, e:
         print ' Error : import time', e
         exit(-1)    
     
     try:
         import re
     except Exception, e:
         print ' Error : import re', e
         exit(-1)    
     
     try:
         import sys
     except Exception, e:
         print ' Error : import sys', e
         exit(-1)
         
     try:
         import psyco
     except Exception, e:
         print ' Warning : import psyco', e
         
     print
     print ' #### Start of install activity ####'
     print
     pckgsInstall()
     pckgsInstallFromSource()
     addSettingsToConfFiles()
     addDirChPer()
                             
     print
     print ' #### End of install activity ####'
     print
     print ' #### Installation summary ####'
     print
     
     print ' Installed components =>'
     if len(pckgsSuccessApt):
         print '  Apt packages :' 
         for ic in pckgsSuccessApt:
             print '   ' + ic
     print
     if len(pckgsSuccessWget):
         print '  Wget packages downloaded:'
         for ic in pckgsSuccessWget:
             print '   ' + ic                        
     print
     print ' Could not install components =>'
     if len(pckgsFailureApt):
         print '   Apt packages :'
         for nic in pckgsFailureApt:
             print '   ' + nic
     print
     if len(pckgsFailureWget):
         print '   Wget packages downloaded:'
         for nic in pckgsFailureWget:
             print '   ' + nic    
     print
     
     print '\n #### Installation from sources summary ####\n'
     print ' Unpacked from source archive =>'
     if len(unpkSuccessArchiv):
         for ifc in unpkSuccessArchiv:
             print '  ' + ifc
     print
     print ' Could not unpack from sources =>'
     if len(unpkFailureArchiv):
         for nifc in unpkFailureArchiv:
             print '  ' + nifc    
     print
     print ' Installed from sources =>'
     if len(instlSuccessWget):
         for ifc in instlSuccessWget:
             print '  ' + ifc
     print
     print ' Could not install from sources =>'
     if len(instlFailureWget):
         for nifc in instlFailureWget:
             print '  ' + nifc   
     print
     
     print '\n #### Directories creation sumamry ####\n'
     if len(dircreateSuccess):
         print '  Creation success =>'
         for itrd in dircreateSuccess:
             print '   ' + itrd
     print
     if len(dircreateFailure):
         print '  Creation failure =>'
         for itrd in dircreateFailure:
             print '   ' + itrd       
     print
