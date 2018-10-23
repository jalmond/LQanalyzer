def CleanUpJobLogs(path):
    import os, getpass,sys
    print "Cleaning up " + path
    

    logspace1 = path
    if (os.path.exists(logspace1)):
        if not "ui" in str(os.getenv("HOSTNAME")):
            os.system("qstat -u " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")
        else:
            os.system("condor_q " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")
        qsub_all_filename = logspace1 +'/qsub_del'
        n_qsub_jobs=0
        for qsub_all_line in open(qsub_all_filename, 'r'):
            if not "ui" in str(os.getenv("HOSTNAME")):
                if getpass.getuser() in qsub_all_line:
                    n_qsub_jobs=n_qsub_jobs+1
            else:
                if "held" in qsub_all_line:
                    split_qsub_all_line = qsub_all_line.split()
                    n_qsub_jobs =  split_qsub_all_line[0] 

        os.system("rm "+logspace1 + "/qsub_del")
        if n_qsub_jobs != 0:
            print "Not cleaning up since user has jobs are running in batch"
            return
    
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
                      days_to_keep=3
                              
                      if month_file not in month:
                          if int(date) > int(days_to_keep):
                              print "Log file older than one week: Removing " + logspace1 + entries[8]
                              os.system(" rm -r " + logspace1 + "/" + entries[8])
                          else:
                              os.system("ls -l " + logspace1 + "/"+entries[8] +" > " + logspace1 + "/"+entries[8] + "/file_dates.txt")
                              for line3 in open(logspace1 + "/"+entries[8] + "/file_dates.txt",'r'):
                                  if not ".txt" in line3:
                                      entries_sep = line3.split()
                                      if not len(entries_sep)==2:
                                          month_file=entries_sep[5]
                                          date_file=entries_sep[6]
                                          if int(date) > int(days_to_keep):
                                              print "Log file older than one week: Removing " + logspace1 + entries[8] + "/"+entries_sep[8]
                                              os.system(" rm -r " + logspace1 + "/" + entries[8] + "/"+entries_sep[8])
                              if os.path.exists(logspace1 + "/"+entries[8] + "/file_dates.txt"):                
                                  os.system("rm " + logspace1 + "/"+entries[8] + "/file_dates.txt")

                      elif int(date_file) < (int(date)-int(days_to_keep)):
                          print "Log file older than one week: Removing " + logspace1 + entries[8]
                          os.system(" rm -r " + logspace1 + "/" + entries[8])
                          
                      else:
                          os.system("ls -l " + logspace1 + "/"+entries[8] +" > " + logspace1 + "/"+entries[8] + "/file_dates.txt")
                          for line3 in open(logspace1 + "/"+entries[8] + "/file_dates.txt",'r'):
                              if not ".txt" in line3:
                                  entries_sep = line3.split()
                                  if not len(entries_sep)==2:
                                      month_file=entries_sep[5]
                                      date_file=entries_sep[6]
                                      if int(date_file) <  (int(date)-int(days_to_keep)):
                                          print "Log file older than one week: Removing " + logspace1 + entries[8] + "/"+entries_sep[8]
                                          os.system(" rm -r " + logspace1 + "/" + entries[8] + "/"+entries_sep[8])
                          if os.path.exists(logspace1 + "/"+entries[8] + "/file_dates.txt"):
                              os.system("rm " + logspace1 + "/"+entries[8] + "/file_dates.txt")
                      ##### now check inside each directory

                          
    
    
def CleanUpLogs(path):

    import os, getpass,sys
    print "Cleaning up " + path 
    logspace1 = path 

    if (os.path.exists(logspace1)):

        if not "ui" in str(os.getenv("HOSTNAME")):
            os.system("qstat -u " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")
        else:
            os.system("condor_q " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")

        qsub_all_filename = logspace1 +'/qsub_del'
        n_qsub_jobs=0
        for qsub_all_line in open(qsub_all_filename, 'r'):

            if not "ui" in str(os.getenv("HOSTNAME")):
                if getpass.getuser() in qsub_all_line:
                    n_qsub_jobs=n_qsub_jobs+1
            else:
                if "held" in qsub_all_line:
                    split_qsub_all_line = qsub_all_line.split()
                    n_qsub_jobs =  split_qsub_all_line[0]
            
        os.system("rm "+logspace1 + "/qsub_del")
        if n_qsub_jobs != 0:
            print "Not cleaning up since jobs are running in batch"
            return
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
            if not "date.txt" in line2:

                entries = line2.split()
                if not len(entries)==2:

                    if str(os.getenv("HOSTNAME")) in line2 or "Cluster" in line2 or "statlog" in line2 or "MasterFile_tmp" in line2 or "filesize" in line2:
                        os.system("ps ux | grep 'root.exe' &> " + logspace1 + "/pslog")
                        filename = logspace1 + "/pslog"
                        
                        n_previous_jobs=0
                        for psline in open(filename, 'r'):
                            if not "grep" in psline:
                                n_previous_jobs+=1
                               
                        os.system("ps ux | grep 'hadd' &> " + logspace1 + "/psloghadd")
                        filenamehadd = logspace1 + "/psloghadd"

                        for psline in open(filenamehadd, 'r'):
                            if not "grep" in psline:
                                n_previous_jobs+=1

                        if n_previous_jobs == 0:

                            if not "ui" in str(os.getenv("HOSTNAME")):
                                os.system("qstat -u " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")
                            else:
                                os.system("condor_q " + getpass.getuser()+ " > " +   logspace1 + "/qsub_del")


                            qsub_all_filename = logspace1 +'/qsub_del'
                            n_qsub_jobs=0
                            for qsub_all_line in open(qsub_all_filename, 'r'):
                                if not "ui" in str(os.getenv("HOSTNAME")):
                                    if getpass.getuser() in qsub_all_line:
                                        n_qsub_jobs=n_qsub_jobs+1
                                else:
                                    if "held" in qsub_all_line:
                                        split_qsub_all_line = qsub_all_line.split()
                                        n_qsub_jobs =  split_qsub_all_line[0]

                            if n_qsub_jobs == 0:
                                os.system(" rm -r " + logspace1 + "/" + entries[8])
                                print "Deleting directory "  + logspace1 + "/" + entries[8] +" since this is made on " + os.getenv("HOSTNAME") + " but no jobs running on this machine."
                                is_deleted=True
                                if "CLUSTERLOG" in entries[8]:
                                    getjobid=entries[8]
                                    getjobid=getjobid.replace("CLUSTERLOG","")
                                    if os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid):
                                        os.system("rm -r " + os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid)

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
                                if "CLUSTERLOG"in entries[8]:
                                    getjobid=entries[8]
                                    getjobid=getjobid.replace("CLUSTERLOG","")
                                    if os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid):
                                        os.system("rm -r "+ os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid)

                    elif int(date_file) < (int(date)-int(days_to_keep)):
                        if not is_deleted:
                            print "Log file older than one week: Removing " + logspace1 + entries[8]   
                            os.system(" rm -r " + logspace1 + "/" + entries[8])        
                            if "CLUSTERLOG"in entries[8]:
                                getjobid=entries[8]
                                getjobid=getjobid.replace("CLUSTERLOG","")
                                if os.path.exists(os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid):
                                    os.system("rm -r "+ os.getenv("LQANALYZER_BATCHLIB_PATH")+"/"+getjobid)
                                        
