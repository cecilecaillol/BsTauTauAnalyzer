./Make.sh FinalSelection_emu.cc
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/MuonEGB.root output_emu_2016pre/MuonEGB.root data_obs data_obs
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/MuonEGC.root output_emu_2016pre/MuonEGC.root data_obs data_obs
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/MuonEGD.root output_emu_2016pre/MuonEGD.root data_obs data_obs
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/MuonEGE.root output_emu_2016pre/MuonEGE.root data_obs data_obs
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/MuonEGF.root output_emu_2016pre/MuonEGF.root data_obs data_obs
hadd -f output_emu_2016pre/MuonEG.root output_emu_2016pre/MuonEGB.root output_emu_2016pre/MuonEGC.root output_emu_2016pre/MuonEGD.root output_emu_2016pre/MuonEGE.root output_emu_2016pre/MuonEGF.root
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/DY.root output_emu_2016pre/DYLL.root DY ZTT
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/DYemu.root output_emu_2016pre/DY.root DYemu ZTT 
python Relax_DY_em.py --year=2016pre
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/W.root output_emu_2016pre/W.root W W 
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ST_t_antitop.root output_emu_2016pre/ST_t_antitop.root ST_t_antitop top
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ST_t_top.root output_emu_2016pre/ST_t_top.root ST_t_top top
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ST_tW_antitop.root output_emu_2016pre/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ST_tW_top.root output_emu_2016pre/ST_tW_top.root ST_tW_top top
#./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/WW2L2Nu.root output_emu_2016pre/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/WZ2Q2L.root output_emu_2016pre/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/WZ3LNu.root output_emu_2016pre/WZ3LNu.root WZ3LNu VV
#./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ZZ2L2Nu.root output_emu_2016pre/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/VV2L2Nu.root output_emu_2016pre/VV2L2Nu.root VV2L2Nu VV
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/ZZ4L.root output_emu_2016pre/ZZ4L.root ZZ4L VV
hadd -f output_emu_2016pre/VV.root output_emu_2016pre/VV2L2Nu.root output_emu_2016pre/WZ2Q2L.root output_emu_2016pre/WZ3LNu.root output_emu_2016pre/ZZ4L.root #output_emu_2016pre/WW2L2Nu.root output_emu_2016pre/ZZ2L2Nu.root
#hadd -f output_emu_2016pre/VV.root output_emu_2016pre/WZ2Q2L.root output_emu_2016pre/WZ3LNu.root output_emu_2016pre/ZZ4L.root output_emu_2016pre/WW2L2Nu.root output_emu_2016pre/ZZ2L2Nu.root
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/TTToHadronic.root output_emu_2016pre/TTToHadronic.root TTToHadronic top
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/TTToSemiLeptonic.root output_emu_2016pre/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/TTTo2L2Nu_small.root output_emu_2016pre/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_emu_2016pre/top.root output_emu_2016pre/TTToHadronic.root output_emu_2016pre/TTToSemiLeptonic.root output_emu_2016pre/TTTo2L2Nu.root output_emu_2016pre/ST_t_antitop.root output_emu_2016pre/ST_t_top.root output_emu_2016pre/ST_tW_antitop.root output_emu_2016pre/ST_tW_top.root 
hadd -f output_emu_2016pre/MC.root output_emu_2016pre/DYrescaled.root output_emu_2016pre/VV.root output_emu_2016pre/top.root
#./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/GGToTauTau_Ctb20.root output_emu_2016pre/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/GGToTauTau_Ctb20_fid.root output_emu_2016pre/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/GGToTauTau_Ctb20_fid.root output_emu_2016pre/GGTT_fid.root GGTT_Ctb20 GGTT_fid
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/GGToTauTau_Ctb20_fid.root output_emu_2016pre/GGTT_nonfid.root GGTT_Ctb20 GGTT_nonfid
./FinalSelection_emu.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016pre/GGToWW.root output_emu_2016pre/GGWW.root GGWW GGWW

python Create_fake_emu.py --year=2016pre



hadd -f datacard_emu_2016pre.root output_emu_2016pre/Fake.root output_emu_2016pre/MC.root output_emu_2016pre/MuonEG.root output_emu_2016pre/GGTT.root output_emu_2016pre/GGTT_fid.root output_emu_2016pre/GGTT_nonfid.root output_emu_2016pre/GGWW.root 

#sh do_emu_BSM_2016pre.sh
#python Prepare_BSM_combine.py --year="2016pre" --channel="emu"
#hadd -f datacard_emu_2016pre.root output_emu_2016pre/Fake.root output_emu_2016pre/MC.root output_emu_2016pre/MuonEG.root output_emu_2016pre/GGTT.root output_emu_2016pre/GGWW.root output_emu_2016pre/bsm.root
