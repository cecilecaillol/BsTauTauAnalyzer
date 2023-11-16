./Make.sh FinalSelection_mumu.cc
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/SingleMuonA.root output_mumu_2018/SingleMuonA.root data_obs data_obs
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/SingleMuonB.root output_mumu_2018/SingleMuonB.root data_obs data_obs
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/SingleMuonC.root output_mumu_2018/SingleMuonC.root data_obs data_obs
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/SingleMuonD.root output_mumu_2018/SingleMuonD.root data_obs data_obs
#####./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/SingleMuonD_1.root output_mumu_2018/SingleMuonD_1.root data_obs data_obs
hadd -f output_mumu_2018/Data.root output_mumu_2018/SingleMuonA.root output_mumu_2018/SingleMuonB.root output_mumu_2018/SingleMuonC.root output_mumu_2018/SingleMuonD.root #output_mumu_2018/SingleMuonD_1.root
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/DY.root output_mumu_2018/DY.root DY DY
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/TTTo2L2Nu.root output_mumu_2018/TTTo2L2Nu.root TTTo2L2Nu TT
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/WW2L2Nu.root output_mumu_2018/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/GGMM.root output_mumu_2018/GGMM.root GGMM GGMM
./FinalSelection_mumu.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/GGWW.root output_mumu_2018/GGWW.root GGWW GGWW
python Create_fake_mumu.py --year=2018
hadd -f pdf_datacard_mumu_2018.root output_mumu_2018/Fake.root output_mumu_2018/TTTo2L2Nu.root output_mumu_2018/WW2L2Nu.root output_mumu_2018/Data.root output_mumu_2018/DY.root output_mumu_2018/GGMM.root output_mumu_2018/GGWW.root
cp datacard_mumu_2018.root acocorrected_datacard_mumu_2018.root
