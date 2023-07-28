condor_submit submission_mumu_SingleMuonA.sub
condor_submit submission_mumu_SingleMuonB.sub
condor_submit submission_mumu_SingleMuonC.sub
condor_submit submission_mumu_SingleMuonD.sub
condor_submit submission_mumu_DY.sub
##condor_submit submission_mumu_TT.sub
##condor_submit submission_mumu_WW.sub

hadd -f output_mumu_2018/SingleMuonA.root output_mumu_2018/SingleMuonA0.root output_mumu_2018/SingleMuonA1.root output_mumu_2018/SingleMuonA2.root output_mumu_2018/SingleMuonA3.root output_mumu_2018/SingleMuonA4.root output_mumu_2018/SingleMuonA5.root output_mumu_2018/SingleMuonA6.root output_mumu_2018/SingleMuonA7.root output_mumu_2018/SingleMuonA8.root output_mumu_2018/SingleMuonA9.root 
hadd -f output_mumu_2018/SingleMuonB.root output_mumu_2018/SingleMuonB0.root output_mumu_2018/SingleMuonB1.root output_mumu_2018/SingleMuonB2.root output_mumu_2018/SingleMuonB3.root output_mumu_2018/SingleMuonB4.root output_mumu_2018/SingleMuonB5.root output_mumu_2018/SingleMuonB6.root output_mumu_2018/SingleMuonB7.root output_mumu_2018/SingleMuonB8.root output_mumu_2018/SingleMuonB9.root
hadd -f output_mumu_2018/SingleMuonC.root output_mumu_2018/SingleMuonC0.root output_mumu_2018/SingleMuonC1.root output_mumu_2018/SingleMuonC2.root output_mumu_2018/SingleMuonC3.root output_mumu_2018/SingleMuonC4.root output_mumu_2018/SingleMuonC5.root output_mumu_2018/SingleMuonC6.root output_mumu_2018/SingleMuonC7.root output_mumu_2018/SingleMuonC8.root output_mumu_2018/SingleMuonC9.root
hadd -f output_mumu_2018/SingleMuonD.root output_mumu_2018/SingleMuonD0.root output_mumu_2018/SingleMuonD1.root output_mumu_2018/SingleMuonD2.root output_mumu_2018/SingleMuonD3.root output_mumu_2018/SingleMuonD4.root output_mumu_2018/SingleMuonD5.root output_mumu_2018/SingleMuonD6.root output_mumu_2018/SingleMuonD7.root output_mumu_2018/SingleMuonD8.root output_mumu_2018/SingleMuonD9.root
hadd -f output_mumu_2018/Data.root output_mumu_2018/SingleMuonA.root output_mumu_2018/SingleMuonB.root output_mumu_2018/SingleMuonC.root output_mumu_2018/SingleMuonD.root
hadd -f output_mumu_2018/DY.root output_mumu_2018/DY0.root output_mumu_2018/DY1.root output_mumu_2018/DY2.root output_mumu_2018/DY3.root output_mumu_2018/DY4.root output_mumu_2018/DY5.root output_mumu_2018/DY6.root output_mumu_2018/DY7.root output_mumu_2018/DY8.root output_mumu_2018/DY9.root
###python Create_fake_mumu.py --year=2018
###hadd -f datacard_mumu_2018.root output_mumu_2018/Fake.root output_mumu_2018/TTTo2L2Nu.root output_mumu_2018/WW2L2Nu.root output_mumu_2018/Data.root output_mumu_2018/DY.root

