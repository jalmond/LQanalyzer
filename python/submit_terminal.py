import os,time,sys

def UpdateJobsRunning(clear_line, i, number_of_cores):
    sys.stdout.write('\r' + clear_line)
    sys.stdout.flush()
    sys.stdout.write('\r'+ 'Current jobs running : [' + str(i-1) + '/' + str(number_of_cores) + ']... '+ str(number_of_cores-i+1) + ' in queue' )
    sys.stdout.flush()

def UpdateJobsRunnigFirstRun(clear_line,number_of_cores):

    sys.stdout.write('\r' + clear_line)
    sys.stdout.flush()
    sys.stdout.write('\r'+ 'Current jobs running : [' + str(number_of_cores) + '/' + str(number_of_cores) + ']... ')
    sys.stdout.flush()
    time.sleep(1.)

    
