./Make.sh FinalSelection_etau.cc
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronB.root output_etau_2016pre/SingleElectronB.root data_obs data_obs
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronC.root output_etau_2016pre/SingleElectronC.root data_obs data_obs
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronD.root output_etau_2016pre/SingleElectronD.root data_obs data_obs
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronE.root output_etau_2016pre/SingleElectronE.root data_obs data_obs
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronF.root output_etau_2016pre/SingleElectronF.root data_obs data_obs
hadd -f output_etau_2016pre/SingleElectron.root output_etau_2016pre/SingleElectronB.root output_etau_2016pre/SingleElectronC.root output_etau_2016pre/SingleElectronD.root output_etau_2016pre/SingleElectronE.root output_etau_2016pre/SingleElectronF.root
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/DY.root output_etau_2016pre/ZTT.root DY ZTT
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/DY.root output_etau_2016pre/ZLL.root DY ZLL
hadd -f output_etau_2016pre/DY.root output_etau_2016pre/ZTT.root output_etau_2016pre/ZLL.root 
python Relax_DY.py --year=2016pre
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W.root output_etau_2016pre/Wincl.root W W 
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W1.root output_etau_2016pre/W1.root W1 W
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W2.root output_etau_2016pre/W2.root W2 W
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W3.root output_etau_2016pre/W3.root W3 W
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W4.root output_etau_2016pre/W4.root W4 W
hadd -f output_etau_2016pre/W.root output_etau_2016pre/Wincl.root output_etau_2016pre/W1.root output_etau_2016pre/W2.root output_etau_2016pre/W3.root output_etau_2016pre/W4.root
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_t_antitop.root output_etau_2016pre/ST_t_antitop.root ST_t_antitop top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_t_top.root output_etau_2016pre/ST_t_top.root ST_t_top top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_tW_antitop.root output_etau_2016pre/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_tW_top.root output_etau_2016pre/ST_tW_top.root ST_tW_top top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WW2L2Nu.root output_etau_2016pre/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WZ2Q2L.root output_etau_2016pre/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WZ3LNu.root output_etau_2016pre/WZ3LNu.root WZ3LNu VV
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ZZ2L2Nu.root output_etau_2016pre/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ZZ4L.root output_etau_2016pre/ZZ4L.root ZZ4L VV
hadd -f output_etau_2016pre/VV.root output_etau_2016pre/WW2L2Nu.root output_etau_2016pre/WZ2Q2L.root output_etau_2016pre/WZ3LNu.root output_etau_2016pre/ZZ2L2Nu.root output_etau_2016pre/ZZ4L.root
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTToHadronic.root output_etau_2016pre/TTToHadronic.root TTToHadronic top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTToSemiLeptonic.root output_etau_2016pre/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTTo2L2Nu.root output_etau_2016pre/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_etau_2016pre/top.root output_etau_2016pre/TTToHadronic.root output_etau_2016pre/TTToSemiLeptonic.root output_etau_2016pre/TTTo2L2Nu.root output_etau_2016pre/ST_t_antitop.root output_etau_2016pre/ST_t_top.root output_etau_2016pre/ST_tW_antitop.root output_etau_2016pre/ST_tW_top.root 
hadd -f output_etau_2016pre/MC.root output_etau_2016pre/DYrescaled.root output_etau_2016pre/VV.root output_etau_2016pre/top.root
#./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/GGToTauTau.root output_etau_2016pre/GGTT.root GGTT GGTT
#./FinalSelection_etau.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/GGToWW.root output_etau_2016pre/GGWW.root GGWW GGWW

#cp output_etau_2016pre/GGTT.root output_etau_2016pre/signal.root
#sh do_etau_BSM_2016pre.sh
#python Prepare_BSM_combine.py --year="2016pre" --channel="etau"

python Create_fake.py --year=2016pre
hadd -f datacard_etau_2016pre.root output_etau_2016pre/Fake.root output_etau_2016pre/MC.root  output_etau_2016pre/SingleElectron.root output_etau_2016pre/W.root #output_etau_2016pre/GGTT.root output_etau_2016pre/GGWW.root #output_etau_2016pre/bsm.root
