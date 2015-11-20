import os

def makeEmail(users, version, type):
    config= 'Dear ' + users + ',\n'
    config+= '\n'
    if "MC" in type:
        config+='The MC sktrees for catversion ' + version + ' are now ready and updated in LQanalyzer branch CatAnalyzer_13TeV_' + version + '\n'
    else:
        config+='The Data sktrees for catversion ' + version + ' are now ready and updated in LQanalyzer branch CatAnalyzer_13TeV_' + version + '\n'
    config+= '\n'
    config+= 'Thanks,\n'
    config+= 'John,\n'

    return config
        
            
        

                                                                        
