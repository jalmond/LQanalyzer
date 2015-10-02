def GetFiles(dir):

    import os
    files = [""]
    

    for file in files:
        if not os.path.exists(dir + file):
            os.system("wget http://www.hep.man.ac.uk/u/john/CMS/rootfiles/" + file)
            os.system(" mv " + file + " " + dir)
        
