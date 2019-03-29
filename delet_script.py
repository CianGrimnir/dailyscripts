#!/usr/bin/env python

# script to delete .pyc file of corresponding py scripts.

import os
ab=[]
for roots,dirs,files in os.walk("/home/rakesh/myscript/"):
    for file in files:
        if file.endswith(".py"):
            ab.append(os.path.join(roots,file))
            #myfile.write(os.path.join(roots,var1)) ##write ab value to file
bc=[]
for i in range(len(ab)):
    bc.append(ab[i]+"c")
xy=[]
for roots,dirs,files in os.walk("/home/rakesh/myscript/"):
    for file in files:
        if file.endswith(".pyc"):
            xy.append(os.path.join(roots,file))

for i in ex:
    os.remove(i)
#os.remove([x[:-1] for x in bc if x in xy])
