./Make.sh FinalSelection_mumu.cc
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/SingleMuonB.root output_mumu_2016pre/SingleMuonB.root data_obs data_obs
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/SingleMuonC.root output_mumu_2016pre/SingleMuonC.root data_obs data_obs
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/SingleMuonD.root output_mumu_2016pre/SingleMuonD.root data_obs data_obs
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/SingleMuonE.root output_mumu_2016pre/SingleMuonE.root data_obs data_obs
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/SingleMuonF.root output_mumu_2016pre/SingleMuonF.root data_obs data_obs
hadd -f output_mumu_2016pre/Data.root output_mumu_2016pre/SingleMuonB.root output_mumu_2016pre/SingleMuonC.root output_mumu_2016pre/SingleMuonD.root output_mumu_2016pre/SingleMuonE.root output_mumu_2016pre/SingleMuonF.root
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/DY.root output_mumu_2016pre/DY.root DY DY
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/TTTo2L2Nu.root output_mumu_2016pre/TTTo2L2Nu.root TTTo2L2Nu TT
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/WW2L2Nu.root output_mumu_2016pre/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_mumu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016pre/GGMM.root output_mumu_2016pre/GGMM.root GGMM GGMM
python Create_fake_mumu.py --year=2016pre
hadd -f datacard_mumu_2016pre.root output_mumu_2016pre/Fake.root output_mumu_2016pre/TTTo2L2Nu.root output_mumu_2016pre/WW2L2Nu.root output_mumu_2016pre/Data.root output_mumu_2016pre/DY.root output_mumu_2016pre/GGMM.root
