./Make.sh FinalSelection_emu.cc
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/MuonEGF.root output_emu_2016post/MuonEGF.root data_obs data_obs
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/MuonEGG.root output_emu_2016post/MuonEGG.root data_obs data_obs
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/MuonEGH.root output_emu_2016post/MuonEGH.root data_obs data_obs
hadd -f output_emu_2016post/MuonEG.root output_emu_2016post/MuonEGF.root output_emu_2016post/MuonEGG.root output_emu_2016post/MuonEGH.root 
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/DY.root output_emu_2016post/DYLL.root DY ZTT
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/DYemu.root output_emu_2016post/DY.root DYemu ZTT
python Relax_DY_em.py --year=2016post
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/W.root output_emu_2016post/W.root W W 
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ST_t_antitop.root output_emu_2016post/ST_t_antitop.root ST_t_antitop top
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ST_t_top.root output_emu_2016post/ST_t_top.root ST_t_top top
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ST_tW_antitop.root output_emu_2016post/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ST_tW_top.root output_emu_2016post/ST_tW_top.root ST_tW_top top
#./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/WW2L2Nu.root output_emu_2016post/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/WZ2Q2L.root output_emu_2016post/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/WZ3LNu.root output_emu_2016post/WZ3LNu.root WZ3LNu VV
#./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ZZ2L2Nu.root output_emu_2016post/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/VV2L2Nu.root output_emu_2016post/VV2L2Nu.root VV2L2Nu VV
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/ZZ4L.root output_emu_2016post/ZZ4L.root ZZ4L VV
hadd -f output_emu_2016post/VV.root output_emu_2016post/VV2L2Nu.root output_emu_2016post/WZ2Q2L.root output_emu_2016post/WZ3LNu.root output_emu_2016post/ZZ4L.root #output_emu_2016post/WW2L2Nu.root output_emu_2016post/ZZ2L2Nu.root
#hadd -f output_emu_2016post/VV.root output_emu_2016post/WZ2Q2L.root output_emu_2016post/WZ3LNu.root output_emu_2016post/ZZ4L.root output_emu_2016post/WW2L2Nu.root output_emu_2016post/ZZ2L2Nu.root
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/TTToHadronic.root output_emu_2016post/TTToHadronic.root TTToHadronic top
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/TTToSemiLeptonic.root output_emu_2016post/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/TTTo2L2Nu_small.root output_emu_2016post/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_emu_2016post/top.root output_emu_2016post/TTToHadronic.root output_emu_2016post/TTToSemiLeptonic.root output_emu_2016post/TTTo2L2Nu.root output_emu_2016post/ST_t_antitop.root output_emu_2016post/ST_t_top.root output_emu_2016post/ST_tW_antitop.root output_emu_2016post/ST_tW_top.root 
hadd -f output_emu_2016post/MC.root output_emu_2016post/DYrescaled.root output_emu_2016post/VV.root output_emu_2016post/top.root
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/GGToTauTau_Ctb20.root output_emu_2016post/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_emu.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/GGToWW.root output_emu_2016post/GGWW.root GGWW GGWW

python Create_fake_emu.py --year=2016post



hadd -f datacard_emu_2016post.root output_emu_2016post/Fake.root output_emu_2016post/MC.root output_emu_2016post/MuonEG.root output_emu_2016post/GGTT.root output_emu_2016post/GGWW.root 

#sh do_emu_BSM_2016post.sh
#python Prepare_BSM_combine.py --year="2016post" --channel="emu"
#hadd -f datacard_emu_2016post.root output_emu_2016post/Fake.root output_emu_2016post/MC.root output_emu_2016post/MuonEG.root output_emu_2016post/GGTT.root output_emu_2016post/GGWW.root output_emu_2016post/bsm.root
