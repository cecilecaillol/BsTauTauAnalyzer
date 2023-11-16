./Make.sh FinalSelection_tauid.cc
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/SingleMuonB.root output_tauid_2017/SingleMuonB.root data_obs data_obs
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/SingleMuonC.root output_tauid_2017/SingleMuonC.root data_obs data_obs
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/SingleMuonD.root output_tauid_2017/SingleMuonD.root data_obs data_obs
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/SingleMuonE.root output_tauid_2017/SingleMuonE.root data_obs data_obs
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/SingleMuonF.root output_tauid_2017/SingleMuonF.root data_obs data_obs
hadd -f output_tauid_2017/SingleMuon.root output_tauid_2017/SingleMuonB.root output_tauid_2017/SingleMuonC.root output_tauid_2017/SingleMuonD.root output_tauid_2017/SingleMuonE.root output_tauid_2017/SingleMuonF.root
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/DY.root output_tauid_2017/ZTT.root DY ZTT
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/DY.root output_tauid_2017/ZLL.root DY ZLL
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/DY.root output_tauid_2017/ZJ.root DY ZJ
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/W.root output_tauid_2017/Wincl.root W W 
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/W1.root output_tauid_2017/W1.root W1 W
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/W2.root output_tauid_2017/W2.root W2 W
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/W3.root output_tauid_2017/W3.root W3 W
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/W4.root output_tauid_2017/W4.root W4 W
hadd -f output_tauid_2017/W.root output_tauid_2017/Wincl.root output_tauid_2017/W1.root output_tauid_2017/W2.root output_tauid_2017/W3.root output_tauid_2017/W4.root
#./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ST_t_antitop.root output_tauid_2017/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ST_t_top.root output_tauid_2017/ST_t_top.root ST_t_top ST
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ST_tW_antitop.root output_tauid_2017/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ST_tW_top.root output_tauid_2017/ST_tW_top.root ST_tW_top ST
hadd -f output_tauid_2017/ST.root output_tauid_2017/ST_t_top.root output_tauid_2017/ST_tW_antitop.root output_tauid_2017/ST_tW_top.root #output_tauid_2017/ST_t_antitop.root
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/WW2L2Nu.root output_tauid_2017/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/WZ2Q2L.root output_tauid_2017/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/WZ3LNu.root output_tauid_2017/WZ3LNu.root WZ3LNu VV
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ZZ2L2Nu.root output_tauid_2017/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/ZZ4L.root output_tauid_2017/ZZ4L.root ZZ4L VV
hadd -f output_tauid_2017/VV.root output_tauid_2017/WW2L2Nu.root output_tauid_2017/WZ2Q2L.root output_tauid_2017/WZ3LNu.root output_tauid_2017/ZZ2L2Nu.root output_tauid_2017/ZZ4L.root
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/TTToHadronic.root output_tauid_2017/TTToHadronic.root TTToHadronic TT
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/TTToSemiLeptonic.root output_tauid_2017/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_tauid.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2017/TTTo2L2Nu.root output_tauid_2017/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_tauid_2017/TT.root output_tauid_2017/TTToHadronic.root output_tauid_2017/TTToSemiLeptonic.root output_tauid_2017/TTTo2L2Nu.root
hadd -f output_tauid_2017/MC.root output_tauid_2017/ZLL.root output_tauid_2017/ZJ.root output_tauid_2017/ZTT.root output_tauid_2017/ST.root output_tauid_2017/VV.root output_tauid_2017/TT.root output_tauid_2017/W.root

python Create_fake_tauid.py --year=2017
python Scale_W_tauid.py --year=2017
hadd -f datacard_tauid_2017.root output_tauid_2017/Wrescaled.root output_tauid_2017/QCD.root output_tauid_2017/MC.root  output_tauid_2017/SingleMuon.root 
