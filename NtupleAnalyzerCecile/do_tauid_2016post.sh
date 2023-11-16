./Make.sh FinalSelection_tauid.cc
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/SingleMuonF.root output_tauid_2016post/SingleMuonF.root data_obs data_obs
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/SingleMuonG.root output_tauid_2016post/SingleMuonG.root data_obs data_obs
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/SingleMuonH.root output_tauid_2016post/SingleMuonH.root data_obs data_obs
hadd -f output_tauid_2016post/SingleMuon.root output_tauid_2016post/SingleMuonF.root output_tauid_2016post/SingleMuonG.root output_tauid_2016post/SingleMuonH.root
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/DY.root output_tauid_2016post/ZTT.root DY ZTT
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/DY.root output_tauid_2016post/ZLL.root DY ZLL
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/DY.root output_tauid_2016post/ZJ.root DY ZJ
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/W.root output_tauid_2016post/Wincl.root W W 
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/W1.root output_tauid_2016post/W1.root W1 W
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/W2.root output_tauid_2016post/W2.root W2 W
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/W3.root output_tauid_2016post/W3.root W3 W
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/W4.root output_tauid_2016post/W4.root W4 W
hadd -f output_tauid_2016post/W.root output_tauid_2016post/Wincl.root output_tauid_2016post/W1.root output_tauid_2016post/W2.root output_tauid_2016post/W3.root output_tauid_2016post/W4.root
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ST_t_antitop.root output_tauid_2016post/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ST_t_top.root output_tauid_2016post/ST_t_top.root ST_t_top ST
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ST_tW_antitop.root output_tauid_2016post/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ST_tW_top.root output_tauid_2016post/ST_tW_top.root ST_tW_top ST
hadd -f output_tauid_2016post/ST.root output_tauid_2016post/ST_t_antitop.root output_tauid_2016post/ST_t_top.root output_tauid_2016post/ST_tW_antitop.root output_tauid_2016post/ST_tW_top.root 
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/WW2L2Nu.root output_tauid_2016post/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/WZ2Q2L.root output_tauid_2016post/WZ2Q2L.root WZ2Q2L VV
#./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/WZ3LNu.root output_tauid_2016post/WZ3LNu.root WZ3LNu VV
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ZZ2L2Nu.root output_tauid_2016post/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/ZZ4L.root output_tauid_2016post/ZZ4L.root ZZ4L VV
hadd -f output_tauid_2016post/VV.root output_tauid_2016post/WW2L2Nu.root output_tauid_2016post/WZ2Q2L.root output_tauid_2016post/ZZ2L2Nu.root output_tauid_2016post/ZZ4L.root #output_tauid_2016post/WZ3LNu.root
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/TTToHadronic.root output_tauid_2016post/TTToHadronic.root TTToHadronic TT
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/TTToSemiLeptonic.root output_tauid_2016post/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_tauid.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mutau_2016post/TTTo2L2Nu.root output_tauid_2016post/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_tauid_2016post/TT.root output_tauid_2016post/TTToHadronic.root output_tauid_2016post/TTToSemiLeptonic.root output_tauid_2016post/TTTo2L2Nu.root
hadd -f output_tauid_2016post/MC.root output_tauid_2016post/ZLL.root output_tauid_2016post/ZJ.root output_tauid_2016post/ZTT.root output_tauid_2016post/ST.root output_tauid_2016post/VV.root output_tauid_2016post/TT.root output_tauid_2016post/W.root

python Create_fake_tauid.py --year=2016post
python Scale_W_tauid.py --year=2016post
hadd -f datacard_tauid_2016post.root output_tauid_2016post/Wrescaled.root output_tauid_2016post/QCD.root output_tauid_2016post/MC.root  output_tauid_2016post/SingleMuon.root 
