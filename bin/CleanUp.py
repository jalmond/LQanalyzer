def CleanUpJobLogs(path):

    import os, getpass,sys
    print "Cleaning up " + path
    logspace1 = path
    if (os.path.exists(logspace1)):
        os.system("date > " + logspace1 + "/last_login_date.txt")
        month=""
        date=""
        for line in open(logspace1+ "/last_login_date.txt", 'r'):
            entries = line.split()
            month=entries[1]
            date=entries[2]

        os.system("ls -l " + logspace1 + " > " + logspace1 + "/file_dates.txt")
        for line2 in open(logspace1 + "/file_dates.txt", 'r'):
            if not ".txt" in line2:
                entries = line2.split()
                if not len(entries)==2:
                    
                      month_file=entries[5]
                      date_file=entries[6]
                      days_to_keep=7
                              
                      if month_file not in month:
                          if int(date) > int(days_to_keep):
                              print "Log file older than one week: Removing " + logspace1 + entries[8]
                              os.system(" rm -r " + logspace1 + "/" + entries[8])
                      elif int(date_file) < (int(date)-int(days_to_keep)):
                          print "Log file older than one week: Removing " + logspace1 + entries[8]
                          os.system(" rm -r " + logspace1 + "/" + entries[8])
                                      
                                                                                                                                                                                                                                          
    
def CleanUpLogs(path):

    import os, getpass,sys
    print "Cleaning up " + path 
    logspace1 = path 
    if (os.path.exists(logspace1)):
        os.system("date > " + logspace1 + "/last_login_date.txt")
        month=""
        date=""
        for line in open(logspace1+ "/last_login_date.txt", 'r'):
            entries = line.split()
            month=entries[1]
            date=entries[2]

        os.system("ls -l " + logspace1 + " > " + logspace1 + "/file_dates.txt")
        for line2 in open(logspace1 + "/file_dates.txt", 'r'):
            is_deleted=False
            if not ".txt" in line2:

                entries = line2.split()
                if not len(entries)==2:

                    if str(os.getenv("HOSTNAME")) in line2:
                        os.system("ps ux | grep 'root.exe' &> " + logspace1 + "/pslog")
                        filename = logspace1 + "/pslog"
                        
                        n_previous_jobs=0
                        for psline in open(filename, 'r'):
                            if not "grep" in psline:
                                n_previous_jobs+=1
                                
                        if n_previous_jobs == 0:
                            os.system(" rm -r " + logspace1 + "/" + entries[8])
                            is_deleted=True
                            print "Deleting directory "  + logspace1 + "/" + entries[8] +" since this is made on " + os.getenv("HOSTNAME") + " but no jobs running on this machine."
                          
                    nfiles=0
                    if (os.path.exists(logspace1 + "/" + entries[8] +"/output/")):
                        os.system("ls -l " + logspace1 + "/" + entries[8] +"/output/ > " + logspace1 + "/rootfile_list.txt")

                        for line3 in open(logspace1 +  "/rootfile_list.txt", 'r'):
                            if ".root" in line3:
                                nfiles = nfiles +1
                    if (os.path.exists(logspace1 + "/" + entries[8] +"/output_tmp/")):            
                        os.system("ls -l " + logspace1 + "/" + entries[8] +"/output_tmp/ > " + logspace1 + "/rootfile_listtmp.txt")
                        for line4 in open(logspace1 +  "/rootfile_listtmp.txt", 'r'):
                            if ".root" in line4:
                                nfiles = nfiles+1

                    month_file=entries[5]
                    date_file=entries[6]
                    days_to_keep=5
                    if "_joboutput_" in line2:
                        days_to_keep=1
                    if nfiles != 0 :
                        days_to_keep=2
      

                     
                    if month_file not in month:
                        if int(date) > int(days_to_keep):
                            if not is_deleted:
                                print "Log file older than one week: Removing " + logspace1 + entries[8]
                                os.system(" rm -r " + logspace1 + "/" + entries[8])
                    elif int(date_file) < (int(date)-int(days_to_keep)):
                        if not is_deleted:
                            print "Log file older than one week: Removing " + logspace1 + entries[8]   
                            os.system(" rm -r " + logspace1 + "/" + entries[8])        

