def makeTransferFile_snu(snumachine, sample, endpath):
	import os
	
        #### not to change
	machine="uosaf0007.sscc.uos.ac.kr"
	path= "/cms/store/user/jalmond/"
	dir=sample + "/"
	toremove = path+dir
	print 'length to remove = ' + str(len(toremove))
    
        ###### DO COPY
	os.system("rm *.txt")

	if not (os.path.exists(endpath)):
		os.system("mkdir " + endpath)
	if not (os.path.exists(endpath)):
		os.exit();
			
	os.system("xrd " + machine + " ls " + path + dir + " > " + sample +".txt")
	os.system("sed -i '/^$/d' " + sample +".txt")
	
	os.system("sed -r 's/^.{43}//' " + sample + ".txt > copy.txt")
	os.system("cut -d/ -f 7 copy.txt > fullsamplelist.txt")
	
	
        ## output the number of files from grid job
	
        ## check if rootfiles already exist in output location
	print "ssh jalmond@" + snumachine + ".snu.ac.kr 'cd "+ endpath  +"; ls  ./' > remove_already_copiedfiles.txt"

	os.system("ssh jalmond@" + snumachine + ".snu.ac.kr 'cd "+ endpath  +"; ls  ./' > remove_already_copiedfiles.txt")
	os.system("sed -i '/^$/d' remove_already_copiedfiles.txt")
	
	fr = open('remove_already_copiedfiles.txt' ,'r')
	for line in fr:
		print 'file ' + line.strip() + ' already copied, removing from list to be copied'  
		# remove filename from copy.txt
		os.system("sed -i '/" + line.strip()+"/d' copy.txt")
		
		print "removed all files previously copied"
		
	f = open('copy.txt' ,'r')
	for line in f:
		# copy to local dir
		print 'copying '+ line.strip()
		copy = "xrdcopy root://" + machine+"/"
		fullpath = line.strip()
		os.system(copy+fullpath + " " + endpath + "/")  

		filename=line.strip()[len(toremove):]
		print "copied file removed from copy.txt"
		# remove filename from copy.txt
		os.system("sed -i '/" + filename+"/d' copy.txt")
		
	print "Finished copying to " + snumachine + ".snu.ac.kr:/" + endpath + ". List of files copied are: "   
	os.system("ssh jalmond@" + snumachine + ".snu.ac.kr 'cd "+ endpath  +"; ls  ./'")
	os.system("ssh jalmond@" + snumachine + ".snu.ac.kr 'cd "+ endpath  +"; ls  ./' > files_at_snuend.txt")

	
	os.system("grep -Fxv -f  files_at_snuend.txt fullsamplelist.txt > missingfiles.txt")
	os.system("sed -i '/^$/d' missingfiles.txt")
	
	fm = open('missingfiles.txt' ,'r')
	for line in fm:
		# copy to local dir
		print 'File not copied originally is: '+ line.strip()  +". Retrying copy" 
		copy = "xrdcopy root://" + machine+"/"
		fullpath = line.strip()
		os.system(copy+fullpath + " " + endpath + "/")
    
		filename=line.strip()[len(toremove):]
		# remove filename from copy.txt
		os.system("sed -i '/" + filename+"/d' missingfiles.txt")
                                                    
	print "Doing final check. Files failed to copy ="
	os.system("ssh jalmond@" + snumachine + ".snu.ac.kr 'cd "+ endpath  +"; ls  ./' > files_at_snuend_v2.txt")

	os.system("grep -Fxv -f  files_at_snuend_v2.txt fullsamplelist.txt")
	





