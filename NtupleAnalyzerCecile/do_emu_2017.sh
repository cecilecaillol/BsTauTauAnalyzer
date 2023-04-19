./Make.sh FinalSelection_emu.cc
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/MuonEGB.root output_emu_2017/MuonEGB.root data_obs data_obs
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/MuonEGC.root output_emu_2017/MuonEGC.root data_obs data_obs
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/MuonEGD.root output_emu_2017/MuonEGD.root data_obs data_obs
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/MuonEGE.root output_emu_2017/MuonEGE.root data_obs data_obs
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/MuonEGF.root output_emu_2017/MuonEGF.root data_obs data_obs
hadd -f output_emu_2017/MuonEG.root output_emu_2017/MuonEGB.root output_emu_2017/MuonEGC.root output_emu_2017/MuonEGD.root output_emu_2017/MuonEGE.root output_emu_2017/MuonEGF.root
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/DY.root output_emu_2017/DY.root DY ZTT
python Relax_DY_em.py --year=2017
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/W.root output_emu_2017/W.root W W 
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ST_t_antitop.root output_emu_2017/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ST_t_top.root output_emu_2017/ST_t_top.root ST_t_top ST
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ST_tW_antitop.root output_emu_2017/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ST_tW_top.root output_emu_2017/ST_tW_top.root ST_tW_top ST
hadd -f output_emu_2017/ST.root output_emu_2017/ST_t_antitop.root output_emu_2017/ST_t_top.root output_emu_2017/ST_tW_antitop.root output_emu_2017/ST_tW_top.root 
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/WW2L2Nu.root output_emu_2017/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/WZ2Q2L.root output_emu_2017/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/WZ3LNu.root output_emu_2017/WZ3LNu.root WZ3LNu VV
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ZZ2L2Nu.root output_emu_2017/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/ZZ4L.root output_emu_2017/ZZ4L.root ZZ4L VV
hadd -f output_emu_2017/VV.root output_emu_2017/WW2L2Nu.root output_emu_2017/WZ2Q2L.root output_emu_2017/WZ3LNu.root output_emu_2017/ZZ2L2Nu.root output_emu_2017/ZZ4L.root
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/TTToHadronic.root output_emu_2017/TTToHadronic.root TTToHadronic TT
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/TTToSemiLeptonic.root output_emu_2017/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/TTTo2L2Nu_small.root output_emu_2017/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_emu_2017/TT.root output_emu_2017/TTToHadronic.root output_emu_2017/TTToSemiLeptonic.root output_emu_2017/TTTo2L2Nu.root
hadd -f output_emu_2017/MC.root output_emu_2017/DYrescaled.root output_emu_2017/ST.root output_emu_2017/VV.root output_emu_2017/TT.root
#./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/GGToTauTau.root output_emu_2017/GGTT.root GGTT GGTT
#./FinalSelection_emu.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2017/GGToWW.root output_emu_2017/GGWW.root GGWW GGWW

python Create_fake_emu.py --year=2017



hadd -f datacard_emu_2017.root output_emu_2017/Fake.root output_emu_2017/MC.root output_emu_2017/MuonEG.root #output_emu_2017/GGTT.root output_emu_2017/GGWW.root 

#sh do_emu_BSM_2017.sh
#python Prepare_BSM_combine.py --year="2017" --channel="emu"
##hadd -f datacard_emu_2017.root output_emu_2017/Fake.root output_emu_2017/MC.root output_emu_2017/MuonEG.root output_emu_2017/GGTT.root output_emu_2017/GGWW.root output_emu_2017/bsm.root
