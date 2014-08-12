def GetFiles(dir):

    import os
    files = ["MyDataPileupHistogram.root", "Total_FRcorr60_51_bis.root", "HMN_FinalSFNoJets.root", "FakeRateOpt.root" , "FakeRate2807.root" , "FakeRateMC.root"]

    for file in files:
        if not os.path.exists(dir + file):
            os.system("wget http://www.hep.man.ac.uk/u/john/CMS/rootfiles/" + file)
            os.system(" mv " + file + " " + dir)
        
