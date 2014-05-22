rm */*.root*

wget http://www.hep.man.ac.uk/u/joel/ATLAS/joel_fr_re.root 
mv joel_fr_re.root MuonRates/

wget http://atlas.inp.nsk.su/kskovpen/share/elfake.root
wget http://atlas.inp.nsk.su/kskovpen/share/elrealeff.root
mv el* ElectronRates_kirill

wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRateDiLeptonWRHN.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRateDiLeptonWRHN_run1.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRateDiLeptonWRHN_HST.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRateDiLeptonWRHN_run1.root
mv Fake*  MuonRates/


wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeUp.Either.root       
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.Nominal.Primary.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealDown.Secondary.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeDown.Either.root     
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeUp.Primary.root      
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.Nominal.Secondary.root   
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeDown.Primary.root    
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeUp.Secondary.root    
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealUp.Either.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.FakeDown.Secondary.root  
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealDown.Either.root     
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealUp.Primary.root
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.Nominal.Either.root      
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealDown.Primary.root    
wget http://www.hep.man.ac.uk/u/john/ATLAS/WRHN/Fake2013/RootFiles/FakeRatePlots.MCSub.RealUp.Secondary.root


mv FakeRatePl* ElectronRates_lou


