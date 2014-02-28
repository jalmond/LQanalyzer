from makeTransferFile_snu import *
import os
#### to chang

list = [sys.argv[1]]

sample_pre = ""
sample_post =""

endpath = sys.argv[2]
datapath = sys.argv[3]
    

for s in samples:
    sample = s
    endpath = endpath + "/" +  s
    makeTransferFile_snu("cms2",sample, endpath )    
    #rename("cms2",sample, endpath )
    
