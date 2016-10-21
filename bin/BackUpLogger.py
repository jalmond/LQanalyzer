import os,datetime,sys
from datetime import timedelta

path_admin = "/data1/LQAnalyzer_rootfiles_for_analysis/CATMOD/config.txt"

dobackup=False
backup_date=[]
file_admin = open(path_admin, "r")
copy_admin_file=[]
for line in file_admin:
    copy_admin_file.append(line)
    if "administrator" in line and os.getenv("USER") in line:
        dobackup=True
    if "backup" in line:
        splitline = line.split()
        if len(splitline) == 2:
            backup_date.append(splitline[1])
            
file_admin.close()
if dobackup:            
    nowtime = datetime.datetime.now()
    diff = datetime.timedelta(days=7)
    PAST = nowtime - diff
    date_now=nowtime.strftime("%d")
    date_past=PAST.strftime("%d")
    month_now=nowtime.strftime("%m")
    month_past=PAST.strftime("%m")
    
    if  int(date_now)  % 2 == 0:
        lastest_backup="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/BackUp/" + nowtime.strftime("%d-%m-%y")+"/"
        if not os.path.exists(lastest_backup):
            os.system("mkdir " + lastest_backup)
            os.system("cp /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/MasterFile_v* " + lastest_backup)
            os.system("cp /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary* "+ lastest_backup)
            print "Backing up statfiles in " + lastest_backup
            
            if len(backup_date) == 3:
                remove_backup="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/BackUp/"+backup_date[0]
                if os.path.exists(remove_backup):
                    os.system("rm -r " + remove_backup)
                    mod_file_admin = open(path_admin, "w")
                    for xline in copy_admin_file:
                        if not backup_date[0] in xline:
                            mod_file_admin.write(xline)
                    mod_file_admin.write("backup " + nowtime.strftime("%d-%m-%y"))
                    mod_file_admin.close()        
            else:
                mod_file_admin = open(path_admin, "w")
                for xline in copy_admin_file:
                    mod_file_admin.write(xline)
                mod_file_admin.write("backup " + nowtime.strftime("%d-%m-%y"))    
                mod_file_admin.close()

