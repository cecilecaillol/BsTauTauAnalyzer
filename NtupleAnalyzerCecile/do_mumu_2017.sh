./Make.sh FinalSelection_mumu.cc
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/SingleMuonB.root output_mumu_2017/SingleMuonB.root data_obs data_obs
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/SingleMuonC.root output_mumu_2017/SingleMuonC.root data_obs data_obs
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/SingleMuonD.root output_mumu_2017/SingleMuonD.root data_obs data_obs
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/SingleMuonE.root output_mumu_2017/SingleMuonE.root data_obs data_obs
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/SingleMuonF.root output_mumu_2017/SingleMuonF.root data_obs data_obs
hadd -f output_mumu_2017/Data.root output_mumu_2017/SingleMuonB.root output_mumu_2017/SingleMuonC.root output_mumu_2017/SingleMuonD.root output_mumu_2017/SingleMuonE.root output_mumu_2017/SingleMuonF.root
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/DY.root output_mumu_2017/DY.root DY DY
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/TTTo2L2Nu.root output_mumu_2017/TTTo2L2Nu.root TTTo2L2Nu TT
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/WW2L2Nu.root output_mumu_2017/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/GGMM.root output_mumu_2017/GGMM.root GGMM GGMM
./FinalSelection_mumu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2017/GGWW.root output_mumu_2017/GGWW.root GGWW GGWW
python Create_fake_mumu.py --year=2017
hadd -f datacard_mumu_2017.root output_mumu_2017/Fake.root output_mumu_2017/TTTo2L2Nu.root output_mumu_2017/WW2L2Nu.root output_mumu_2017/Data.root output_mumu_2017/DY.root #output_mumu_2017/GGMM.root
cp datacard_mumu_2017.root pdf_datacard_mumu_2017.root
