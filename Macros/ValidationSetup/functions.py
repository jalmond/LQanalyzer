def MakeRunFile(dataset,cuts , ID):
    config='cd SKTreeValidation' + dataset+ '/ \n'
    for i in cuts:
        config+='./MakeDataMCCompPlots Config/hnplots_periodCtoD_' +ID +"_" + i + '.txt \n'
    config+='cd -\n'
    return config
def MakeHistFile():
    config='h_llmass   5 20. 200.\n'
    config+='h_leadingLeptonPt  2 10. 200.\n'
    config+='h_secondLeptonPt  2 10. 200.\n'
    config+='h_LeptonEta 2 -2.5 2.5\n'
    config+='h_Njets 1 0 6\n'
    config+='h_PFMET 2 0. 300.\n'
    config+='h_nVertices 1 0. 30.\n'
    config+='h_Nelectrons 1 0 5\n'
    config+='h_Nmuons 1 0 5\n'
    config+='h_Nbjets 1 0 3\n'
    config+='h_bTag 2 -1. 1.\n'
    config+='h_jets_pt 2 0. 105.\n'
    config+='h_dijetsmass  5 0. 200.\n'
    config+='h_l1jjmass   2 50. 400.\n'
    config+='h_l2jjmass   2 50. 400.\n'
    config+='h_lljjmass   2 50. 500.\n'
    config+='END'

    return config
def makeConfigFile(filepath, dataset, histfile, cutfile, catversion, samples, cut):

    cv = catversion.replace("-","")
    config='# Specify_location_of_data/mc \n'
    config+='mcpath          ' + filepath  +' \n'
    config+='datapath        ' + filepath  +'SKTreeValidation_data_'+dataset+'_cat_'+catversion+'.root \n'
    config+='datadrivenpath  ' + filepath  +' \n'
    config+='# Specify_the_list_of_hists_to_plot \n'
    config+='plottingpath    dat/'+histfile+' \n'
    config+='cutpath         dat/'+cutfile +' \n'
    config+='# file_prefix \n'
    config+='prefix          SKTreeValidation_SK \n'
    config+='postfix         _cat_'+catversion+'.root \n'
    config+='# NAME_THE_OUTPUT_DIR \n'
    config+='outputdir  HN13TeV_SKTreeValidation_'+cv+'_periodCtoD_' + cut +' \n'
    config+='histdir    CAT2015_'+cv+' \n'
    config+='# CONFIGURE_HISTOGRAMS \n'
    config+='showdata   true \n'
    config+='usenp      false \n'
    config+='ylog       true \n'
    config+='# List_the_samples_to_be_includedv \n'
    for l in samples:
        config+='samples    ' + l + ' \n'
    config+='END \n'
    return config
    
    
