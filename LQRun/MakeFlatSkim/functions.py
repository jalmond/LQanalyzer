import os

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
        

                                                                        
