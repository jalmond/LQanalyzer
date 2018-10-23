import os


def initiate_sktreemaker(isKisti,sktreeoutput, workoutput_mounted, sample_catversion):

    if not isKisti:
        sktreeoutput=workoutput_mounted

    SKTreeOutput_pre = sktreeoutput+"/CatNtuples/" + sample_catversion
    if not os.path.exists(SKTreeOutput_pre):
        os.system("mkdir " + SKTreeOutput_pre)
        
    SKTreeOutput_pre2 = sktreeoutput+"/CatNtuples/" + sample_catversion + "/SKTrees/"

    if not os.path.exists(SKTreeOutput_pre2):
        os.system("mkdir " + SKTreeOutput_pre2)

    return  sktreeoutput+"/CatNtuples/" + sample_catversion + "/SKTrees/"



def SetupSKTree(isKisti,sktreeoutput, workoutput_mounted, sample_catversion, mc,original_channel, cycle):

    SKTreeOutput = initiate_sktreemaker(isKisti,sktreeoutput, workoutput_mounted, sample_catversion)

    cycle_tag = ""
    if cycle == "SKTreeMakerDiLep":
        cycle_tag="DiLep"
    if cycle == "SKTreeMakerHNDiLep":
        cycle_tag="HNDiLep" 
    if cycle == "SKTreeMakerFakeHN":
        cycle_tag="FakeHN"
    if cycle == "SKTreeMakerTriLep":
        cycle_tag="TriLep"

    Finaloutputdir=""
    if not os.path.exists(SKTreeOutput):
        os.system("mkdir  " + SKTreeOutput)
        Finaloutputdir = SKTreeOutput + "Data"+cycle_tag+"/"
        
        if not os.path.exists(Finaloutputdir):
            os.system("mkdir " + Finaloutputdir)

        if original_channel =="DoubleEG":
            Finaloutputdir += "DoubleEG/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)

        if original_channel =="DoubleMuon":
            Finaloutputdir += "DoubleMuon/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)
        if original_channel =="MuonEG":
            Finaloutputdir += "MuonEG/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)
        if original_channel =="SingleMuon":
            Finaloutputdir += "SingleMuon/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)
        if original_channel =="SingleElectron":
            Finaloutputdir += "SingleElectron/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)
        if original_channel =="SinglePhoton":
            Finaloutputdir += "SinglePhoton/"
            if not os.path.exists(Finaloutputdir):
                os.system("mkdir " + Finaloutputdir)
        Finaloutputdir += "period" + original_sample + "/"
        if not os.path.exists(Finaloutputdir):
            os.system("mkdir " + Finaloutputdir)
    else:
        Finaloutputdir = SKTreeOutput + "MC"+cycle_tag+"/"
        if not os.path.exists(Finaloutputdir):
            os.system("mkdir " + Finaloutputdir)

        Finaloutputdir +=  original_sample + "/"
        if not os.path.exists(Finaloutputdir):
            os.system("mkdir " + Finaloutputdir)
            os.system("chmod 777 -R " +  Finaloutputdir)
            
    return Finaloutputdir
