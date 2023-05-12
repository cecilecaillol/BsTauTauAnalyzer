./Make.sh FinalSelection_mumu.cc
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/SingleMuonF.root output_mumu_2016post/SingleMuonF.root data_obs data_obs
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/SingleMuonG.root output_mumu_2016post/SingleMuonG.root data_obs data_obs
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/SingleMuonH.root output_mumu_2016post/SingleMuonH.root data_obs data_obs
hadd -f output_mumu_2016post/Data.root output_mumu_2016post/SingleMuonF.root output_mumu_2016post/SingleMuonG.root output_mumu_2016post/SingleMuonH.root
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/DY.root output_mumu_2016post/DY.root DY DY
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/TTTo2L2Nu.root output_mumu_2016post/TTTo2L2Nu.root TTTo2L2Nu TT
./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/WW2L2Nu.root output_mumu_2016post/WW2L2Nu.root WW2L2Nu VV
#./FinalSelection_mumu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2016post/GGMM.root output_mumu_2016post/GGMM.root GGMM GGMM
python Create_fake_mumu.py --year=2016post
hadd -f datacard_mumu_2016post.root output_mumu_2016post/Fake.root output_mumu_2016post/TTTo2L2Nu.root output_mumu_2016post/WW2L2Nu.root output_mumu_2016post/Data.root output_mumu_2016post/DY.root #output_mumu_2016post/GGMM.root
