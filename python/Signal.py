def IsSignal(sample):
    
    if "HeavyNeutrino" in sample:
        return True

    if  "Majorana" in sample:
        return True

    if   "HN" in  sample:
        return True

    if "CHT" in sample:
        return True

    if "TTToH" in sample :
        return True

    if "WR" in sample:
        return True




