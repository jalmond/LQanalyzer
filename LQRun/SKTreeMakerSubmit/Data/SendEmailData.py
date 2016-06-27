import os,time
from functions import *

configfile=open('emailData.txt','w')
configfile.write(makeEmail("Ferdinando", os.getenv("CATVERSION") , "Data"))
configfile.close()
