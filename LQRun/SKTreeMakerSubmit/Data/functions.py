import os

def makeEmail(users, version, type):
    config= 'Dear ' + users + ',\n'
    config+= '\n'
    if "MC" in type:
        config+='The MC sktrees for catversion ' + version + ' are now ready and updated in LQanalyzer branch CatAnalyzer_13TeV_' + version + '.\n'
        config+='Paths and effective luminosity of the new MC sktrees are found in LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_' + version +'.txt. \n'
    else:
        config+='The Data sktrees for catversion ' + version + ' are now ready and updated in LQanalyzer branch CatAnalyzer_13TeV_' + version + '\n'
        config+='Paths for the new data sktrees are found in LQanalyzer/LQRun/txt/datasets_snu_CAT_data_' + version +'.txt. \n'
        
    config+= '\n'
    config+= 'Thanks,\n'
    config+= 'John,\n'

    return config
        
            
        

                                                                        
