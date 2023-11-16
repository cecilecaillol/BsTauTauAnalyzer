./Make.sh FinalSelection_etau.cc
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/SingleElectronB.root output_etau_2017/SingleElectronB.root data_obs data_obs
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/SingleElectronC.root output_etau_2017/SingleElectronC.root data_obs data_obs
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/SingleElectronD.root output_etau_2017/SingleElectronD.root data_obs data_obs
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/SingleElectronE.root output_etau_2017/SingleElectronE.root data_obs data_obs
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/SingleElectronF.root output_etau_2017/SingleElectronF.root data_obs data_obs
hadd -f output_etau_2017/SingleElectron.root output_etau_2017/SingleElectronB.root output_etau_2017/SingleElectronC.root output_etau_2017/SingleElectronD.root output_etau_2017/SingleElectronE.root output_etau_2017/SingleElectronF.root
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/DY.root output_etau_2017/ZTT.root DY ZTT
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/DY.root output_etau_2017/ZLL.root DY ZLL
hadd -f output_etau_2017/DY.root output_etau_2017/ZTT.root output_etau_2017/ZLL.root 
python Relax_DY.py --year=2017
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/W.root output_etau_2017/Wincl.root W W 
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/W1.root output_etau_2017/W1.root W1 W
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/W2.root output_etau_2017/W2.root W2 W
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/W3.root output_etau_2017/W3.root W3 W
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/W4.root output_etau_2017/W4.root W4 W
hadd -f output_etau_2017/W.root output_etau_2017/Wincl.root output_etau_2017/W1.root output_etau_2017/W2.root output_etau_2017/W3.root output_etau_2017/W4.root
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ST_t_antitop.root output_etau_2017/ST_t_antitop.root ST_t_antitop top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ST_t_top.root output_etau_2017/ST_t_top.root ST_t_top top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ST_tW_antitop.root output_etau_2017/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ST_tW_top.root output_etau_2017/ST_tW_top.root ST_tW_top top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/WW2L2Nu.root output_etau_2017/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/WZ2Q2L.root output_etau_2017/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/WZ3LNu.root output_etau_2017/WZ3LNu.root WZ3LNu VV
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ZZ2L2Nu.root output_etau_2017/ZZ2L2Nu.root ZZ2L2Nu VV
#./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/VV2L2Nu.root output_etau_2017/VV2L2Nu.root VV2L2Nu VV
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/ZZ4L.root output_etau_2017/ZZ4L.root ZZ4L VV
#hadd -f output_etau_2017/VV.root output_etau_2017/VV2L2Nu.root output_etau_2017/WZ2Q2L.root output_etau_2017/WZ3LNu.root output_etau_2017/ZZ4L.root #output_etau_2017/WW2L2Nu.root output_etau_2017/ZZ2L2Nu.root
hadd -f output_etau_2017/VV.root output_etau_2017/WZ2Q2L.root output_etau_2017/WZ3LNu.root output_etau_2017/ZZ4L.root output_etau_2017/WW2L2Nu.root output_etau_2017/ZZ2L2Nu.root
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/TTToHadronic.root output_etau_2017/TTToHadronic.root TTToHadronic top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/TTToSemiLeptonic.root output_etau_2017/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/TTTo2L2Nu.root output_etau_2017/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_etau_2017/top.root output_etau_2017/TTToHadronic.root output_etau_2017/TTToSemiLeptonic.root output_etau_2017/TTTo2L2Nu.root output_etau_2017/ST_t_antitop.root output_etau_2017/ST_t_top.root output_etau_2017/ST_tW_antitop.root output_etau_2017/ST_tW_top.root
hadd -f output_etau_2017/MC.root output_etau_2017/DYrescaled.root output_etau_2017/VV.root output_etau_2017/top.root
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/GGToTauTau_Ctb20.root output_etau_2017/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_etau.exe 2017 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2017/GGToWW.root output_etau_2017/GGWW.root GGWW GGWW

#cp output_etau_2017/GGTT.root output_etau_2017/signal.root
#sh do_etau_BSM_2017.sh
#python Prepare_BSM_combine.py --year="2017" --channel="etau"

python Create_fake.py --year=2017
hadd -f datacard_etau_2017.root output_etau_2017/Fake.root output_etau_2017/MC.root  output_etau_2017/SingleElectron.root output_etau_2017/GGTT.root output_etau_2017/GGWW.root output_etau_2017/W.root #output_etau_2017/bsm.root
#hadd -f datacard_etau_2017.root output_etau_2017/Fake.root output_etau_2017/MC.root  output_etau_2017/SingleElectron.root output_etau_2017/W.root 
