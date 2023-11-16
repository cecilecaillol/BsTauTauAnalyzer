./Make.sh FinalSelection_tauid.cc
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/SingleMuonB.root output_tauid_2016pre/SingleMuonB.root data_obs data_obs
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/SingleMuonC.root output_tauid_2016pre/SingleMuonC.root data_obs data_obs
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/SingleMuonD.root output_tauid_2016pre/SingleMuonD.root data_obs data_obs
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/SingleMuonE.root output_tauid_2016pre/SingleMuonE.root data_obs data_obs
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/SingleMuonF.root output_tauid_2016pre/SingleMuonF.root data_obs data_obs
hadd -f output_tauid_2016pre/SingleMuon.root output_tauid_2016pre/SingleMuonB.root output_tauid_2016pre/SingleMuonC.root output_tauid_2016pre/SingleMuonD.root output_tauid_2016pre/SingleMuonE.root output_tauid_2016pre/SingleMuonF.root
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/DY.root output_tauid_2016pre/ZTT.root DY ZTT
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/DY.root output_tauid_2016pre/ZLL.root DY ZLL
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/DY.root output_tauid_2016pre/ZJ.root DY ZJ
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/W.root output_tauid_2016pre/Wincl.root W W 
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/W1.root output_tauid_2016pre/W1.root W1 W
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/W2.root output_tauid_2016pre/W2.root W2 W
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/W3.root output_tauid_2016pre/W3.root W3 W
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/W4.root output_tauid_2016pre/W4.root W4 W
hadd -f output_tauid_2016pre/W.root output_tauid_2016pre/Wincl.root output_tauid_2016pre/W1.root output_tauid_2016pre/W2.root output_tauid_2016pre/W3.root output_tauid_2016pre/W4.root
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ST_t_antitop.root output_tauid_2016pre/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ST_t_top.root output_tauid_2016pre/ST_t_top.root ST_t_top ST
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ST_tW_antitop.root output_tauid_2016pre/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ST_tW_top.root output_tauid_2016pre/ST_tW_top.root ST_tW_top ST
hadd -f output_tauid_2016pre/ST.root output_tauid_2016pre/ST_t_antitop.root output_tauid_2016pre/ST_t_top.root output_tauid_2016pre/ST_tW_antitop.root output_tauid_2016pre/ST_tW_top.root 
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/WW2L2Nu.root output_tauid_2016pre/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/WZ2Q2L.root output_tauid_2016pre/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/WZ3LNu.root output_tauid_2016pre/WZ3LNu.root WZ3LNu VV
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ZZ2L2Nu.root output_tauid_2016pre/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/ZZ4L.root output_tauid_2016pre/ZZ4L.root ZZ4L VV
hadd -f output_tauid_2016pre/VV.root output_tauid_2016pre/WW2L2Nu.root output_tauid_2016pre/WZ2Q2L.root output_tauid_2016pre/WZ3LNu.root output_tauid_2016pre/ZZ2L2Nu.root output_tauid_2016pre/ZZ4L.root
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/TTToHadronic.root output_tauid_2016pre/TTToHadronic.root TTToHadronic TT
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/TTToSemiLeptonic.root output_tauid_2016pre/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_tauid.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016pre/TTTo2L2Nu.root output_tauid_2016pre/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_tauid_2016pre/TT.root output_tauid_2016pre/TTToHadronic.root output_tauid_2016pre/TTToSemiLeptonic.root output_tauid_2016pre/TTTo2L2Nu.root
hadd -f output_tauid_2016pre/MC.root output_tauid_2016pre/ZLL.root output_tauid_2016pre/ZJ.root output_tauid_2016pre/ZTT.root output_tauid_2016pre/ST.root output_tauid_2016pre/VV.root output_tauid_2016pre/TT.root output_tauid_2016pre/W.root

python Create_fake_tauid.py --year=2016pre
python Scale_W_tauid.py --year=2016pre
hadd -f datacard_tauid_2016pre.root output_tauid_2016pre/Wrescaled.root output_tauid_2016pre/QCD.root output_tauid_2016pre/MC.root  output_tauid_2016pre/SingleMuon.root 
