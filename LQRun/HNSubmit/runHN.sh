source HNDiElectron_submit.sh 
cd ../../data/output/SSElectron/
rm HNDiElectron_SKnonprompt_dilep_5_3_14.root
hadd HNDiElectron_SKnonprompt_dilep_5_3_14.root HNDiElectron_SKnonprompt_period*  
rm HNDiElectron_SKchargeflip_dilep_5_3_14.root 
hadd HNDiElectron_SKchargeflip_dilep_5_3_14.root HNDiElectron_chargeflip_SK*
rm HNDiElectron_data_5_3_14.root 
hadd HNDiElectron_data_5_3_14.root HNDiElectron_period*
cd ../../../Macros/HvyNPlottingMacroDataVsMC/

