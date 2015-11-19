import os

def makeEmail(users, version, type):
    config= 'Dear ' + users + ',\n'
    config+= '\n'
    if "MC" in type:
        config+='The MC skims for catversion ' + version + ' are now ready at /data2/DATA/cattoflat/skim/' + version +'/'    
    else:
        config+='The skims for catversion ' + version + ' are now ready at /data2/DATA/cattoflat/skim/' + version +'/'    
    config+= '\n'
    config+= 'Thanks,\n'
    config+= 'John,\n'

    config+= '\n'
    if "MC" in type:
        config+= 'The name/nevents/sum_gen_weights/xsec*filt_eff/lumi/local_path for these samples are listed below\n'

        lumilist=open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_v7-4-5.txt","r")
        for line in lumilist:
            if "/data2/DATA/cattoflat/MC/" in line:
                config+= line 
    
    return config
        
            


def makeNtupleMakerH(sample,samplelist,j, output):

    ntuplemaker=open("SkimFlatCat.h","r")
    config=""
        
    for line in ntuplemaker:
        if "chain->Add(" in line:
            config+=makeConfigFileH(sample,samplelist,j) +"\n"

        elif "Loop();//" in line:
            config+='Loop();\n'
            config+='gSystem->Exec("mv '  + output + '/' +  str(j) + '/*.root ' + output + '/output/");\n'
                
        else:
            config+=line.strip() +"\n"
            
    
    return config


def makeNtupleMakerSlimH(sample,samplelist,j, output):

    ntuplemaker=open("SlimFlatCat.h","r")
    config=""
        
    for line in ntuplemaker:
        if "chain->Add(" in line:
            config+=makeConfigFileSlimH(sample,samplelist,j) +"\n"
            
        elif "Loop();//" in line:
            config+='Loop();\n'
            config+='gSystem->Exec("mv '  + output + '/' +  str(j) + '/*.root ' + output + '/output/");\n'
            
        else:
            config+=line.strip() +"\n"
                
            
    return config

                                                                            
        
def makeConfigFileH(sample, samplelist,j):
    config=""

    count=0
    fr = open(samplelist, 'r')
    for line in fr:
        if ".root" in line:
            count= count+1
            if count == j:
                sline = line[:-1]
                path = sample + "/" + sline + "/ntuple/event"
                config+='chain->Add("' + path + '");'
                config+="\n"

    return config    

def makeConfigFileSlimH(sample, samplelist,j):
    config=""
    
    count=0
    fr = open(samplelist, 'r')
    for line in fr:
        if ".root" in line:
            count= count+1
            if count == j:
                sline = line[:-1]
                path = sample + "/" + sline + "/event"
                config+='chain->Add("' + path + '");'
                config+="\n"
                
    return config

                                                        


def makeNtupleMakerC(out,samplelist, j):

    ntuplemaker=open("SkimFlatCat.C","r")
    config=""

    for line in ntuplemaker:
        if "Skim.root" in line:
            config+='TFile *skimfile = new TFile("'
            config+= out 
            config+='/Skim_' + str(j)  +'.root","recreate");\n'
        else:
            config+=line.strip() +"\n"
    return config


def makeNtupleMakerSlimC(out,samplelist, j):

    ntuplemaker=open("SlimFlatCat.C","r")
    config=""
    
    for line in ntuplemaker:
        if "Skim.root" in line:
            config+='TFile *skimfile = new TFile("'
            config+= out
            config+='/Skim_' + str(j)  +'.root","recreate");\n'
        else:
            config+=line.strip() +"\n"
    return config
        

                                                                        
