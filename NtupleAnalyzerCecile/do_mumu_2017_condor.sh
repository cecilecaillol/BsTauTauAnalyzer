condor_submit submission_mumu_SingleMuonB2017.sub
condor_submit submission_mumu_SingleMuonC2017.sub
condor_submit submission_mumu_SingleMuonD2017.sub
condor_submit submission_mumu_SingleMuonE2017.sub
condor_submit submission_mumu_SingleMuonF2017.sub
condor_submit submission_mumu_DY2017.sub
##condor_submit submission_mumu_TT.sub
##condor_submit submission_mumu_WW.sub

#hadd -f output_mumu_2017/SingleMuonB.root output_mumu_2017/SingleMuonB0.root output_mumu_2017/SingleMuonB1.root output_mumu_2017/SingleMuonB2.root output_mumu_2017/SingleMuonB3.root output_mumu_2017/SingleMuonB4.root output_mumu_2017/SingleMuonB5.root output_mumu_2017/SingleMuonB6.root output_mumu_2017/SingleMuonB7.root output_mumu_2017/SingleMuonB8.root output_mumu_2017/SingleMuonB9.root
#hadd -f output_mumu_2017/SingleMuonC.root output_mumu_2017/SingleMuonC0.root output_mumu_2017/SingleMuonC1.root output_mumu_2017/SingleMuonC2.root output_mumu_2017/SingleMuonC3.root output_mumu_2017/SingleMuonC4.root output_mumu_2017/SingleMuonC5.root output_mumu_2017/SingleMuonC6.root output_mumu_2017/SingleMuonC7.root output_mumu_2017/SingleMuonC8.root output_mumu_2017/SingleMuonC9.root
#hadd -f output_mumu_2017/SingleMuonD.root output_mumu_2017/SingleMuonD0.root output_mumu_2017/SingleMuonD1.root output_mumu_2017/SingleMuonD2.root output_mumu_2017/SingleMuonD3.root output_mumu_2017/SingleMuonD4.root output_mumu_2017/SingleMuonD5.root output_mumu_2017/SingleMuonD6.root output_mumu_2017/SingleMuonD7.root output_mumu_2017/SingleMuonD8.root output_mumu_2017/SingleMuonD9.root
#hadd -f output_mumu_2017/SingleMuonE.root output_mumu_2017/SingleMuonE0.root output_mumu_2017/SingleMuonE1.root output_mumu_2017/SingleMuonE2.root output_mumu_2017/SingleMuonE3.root output_mumu_2017/SingleMuonE4.root output_mumu_2017/SingleMuonE5.root output_mumu_2017/SingleMuonE6.root output_mumu_2017/SingleMuonE7.root output_mumu_2017/SingleMuonE8.root output_mumu_2017/SingleMuonE9.root
#hadd -f output_mumu_2017/SingleMuonF.root output_mumu_2017/SingleMuonF0.root output_mumu_2017/SingleMuonF1.root output_mumu_2017/SingleMuonF2.root output_mumu_2017/SingleMuonF3.root output_mumu_2017/SingleMuonF4.root output_mumu_2017/SingleMuonF5.root output_mumu_2017/SingleMuonF6.root output_mumu_2017/SingleMuonF7.root output_mumu_2017/SingleMuonF8.root output_mumu_2017/SingleMuonF9.root
#hadd -f output_mumu_2017/Data.root output_mumu_2017/SingleMuonB.root output_mumu_2017/SingleMuonC.root output_mumu_2017/SingleMuonD.root output_mumu_2017/SingleMuonE.root output_mumu_2017/SingleMuonF.root
#hadd -f output_mumu_2017/DY.root output_mumu_2017/DY0.root output_mumu_2017/DY1.root output_mumu_2017/DY2.root output_mumu_2017/DY3.root output_mumu_2017/DY4.root output_mumu_2017/DY5.root output_mumu_2017/DY6.root output_mumu_2017/DY7.root output_mumu_2017/DY8.root output_mumu_2017/DY9.root
###python Create_fake_mumu.py --year=2017
###hadd -f datacard_mumu_2017.root output_mumu_2017/Fake.root output_mumu_2017/TTTo2L2Nu.root output_mumu_2017/WW2L2Nu.root output_mumu_2017/Data.root output_mumu_2017/DY.root

