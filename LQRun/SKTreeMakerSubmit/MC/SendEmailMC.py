import os,time

from functions import *

configfile=open('emailMC.txt','w')
configfile.write(makeEmail("All",os.getenv("CATVERSION") , "MC"))
configfile.close()

                
    
