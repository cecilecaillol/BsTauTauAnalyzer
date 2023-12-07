./Make.sh FinalSelection_etau.cc
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/SingleElectronF.root output_etau_2016post/SingleElectronF.root data_obs data_obs
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/SingleElectronG.root output_etau_2016post/SingleElectronG.root data_obs data_obs
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/SingleElectronH.root output_etau_2016post/SingleElectronH.root data_obs data_obs
hadd -f output_etau_2016post/SingleElectron.root output_etau_2016post/SingleElectronF.root output_etau_2016post/SingleElectronG.root output_etau_2016post/SingleElectronH.root
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/DY.root output_etau_2016post/ZTT.root DY ZTT
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/DY.root output_etau_2016post/ZLL.root DY ZLL
hadd -f output_etau_2016post/DY.root output_etau_2016post/ZTT.root output_etau_2016post/ZLL.root 
python Relax_DY.py --year=2016post
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/W.root output_etau_2016post/Wincl.root W W 
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/W1.root output_etau_2016post/W1.root W1 W
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/W2.root output_etau_2016post/W2.root W2 W
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/W3.root output_etau_2016post/W3.root W3 W
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/W4.root output_etau_2016post/W4.root W4 W
hadd -f output_etau_2016post/W.root output_etau_2016post/Wincl.root output_etau_2016post/W1.root output_etau_2016post/W2.root output_etau_2016post/W3.root output_etau_2016post/W4.root
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ST_t_antitop.root output_etau_2016post/ST_t_antitop.root ST_t_antitop top
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ST_t_top.root output_etau_2016post/ST_t_top.root ST_t_top top
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ST_tW_antitop.root output_etau_2016post/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ST_tW_top.root output_etau_2016post/ST_tW_top.root ST_tW_top top
#./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/WW2L2Nu.root output_etau_2016post/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/WZ2Q2L.root output_etau_2016post/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/WZ3LNu.root output_etau_2016post/WZ3LNu.root WZ3LNu VV
#./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ZZ2L2Nu.root output_etau_2016post/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/VV2L2Nu.root output_etau_2016post/VV2L2Nu.root VV2L2Nu VV
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/ZZ4L.root output_etau_2016post/ZZ4L.root ZZ4L VV
hadd -f output_etau_2016post/VV.root output_etau_2016post/VV2L2Nu.root output_etau_2016post/WZ2Q2L.root output_etau_2016post/ZZ4L.root output_etau_2016post/WZ3LNu.root #output_etau_2016post/WW2L2Nu.root output_etau_2016post/ZZ2L2Nu.root
#hadd -f output_etau_2016post/VV.root output_etau_2016post/WZ2Q2L.root output_etau_2016post/ZZ4L.root output_etau_2016post/WZ3LNu.root output_etau_2016post/WW2L2Nu.root output_etau_2016post/ZZ2L2Nu.root
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/TTToHadronic.root output_etau_2016post/TTToHadronic.root TTToHadronic top
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/TTToSemiLeptonic.root output_etau_2016post/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/TTTo2L2Nu.root output_etau_2016post/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_etau_2016post/top.root output_etau_2016post/TTToHadronic.root output_etau_2016post/TTToSemiLeptonic.root output_etau_2016post/TTTo2L2Nu.root output_etau_2016post/ST_t_antitop.root output_etau_2016post/ST_t_top.root output_etau_2016post/ST_tW_antitop.root output_etau_2016post/ST_tW_top.root
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/GGToTauTau_Ctb20.root output_etau_2016post/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/GGToWW.root output_etau_2016post/GGWW.root GGWW GGWW
./FinalSelection_etau.exe 2016post /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016post/GGToElEl.root output_etau_2016post/GGEE.root GGEE GGEE
hadd -f output_etau_2016post/MC.root output_etau_2016post/DYrescaled.root output_etau_2016post/VV.root output_etau_2016post/top.root output_etau_2016post/GGWW.root output_etau_2016post/GGEE.root

#cp output_etau_2016post/GGTT.root output_etau_2016post/signal.root
#sh do_etau_BSM_2016post.sh
#python Prepare_BSM_combine.py --year="2016post" --channel="etau"

python Create_fake.py --year=2016post
hadd -f datacard_etau_2016post.root output_etau_2016post/Fake.root output_etau_2016post/MC.root  output_etau_2016post/SingleElectron.root output_etau_2016post/W.root output_etau_2016post/GGTT.root #output_etau_2016post/bsm.root
