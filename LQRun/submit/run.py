import os, sys, subprocess 
from functions import *

configfile=open('test.txt','w')
configfile.write(makeConfigFile())
print " done"