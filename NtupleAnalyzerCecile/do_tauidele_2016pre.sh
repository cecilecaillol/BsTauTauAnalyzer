./Make.sh FinalSelection_tauidele.cc
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronB.root output_tauidele_2016pre/EGammaB.root data_obs data_obs
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronC.root output_tauidele_2016pre/EGammaC.root data_obs data_obs
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronD.root output_tauidele_2016pre/EGammaD.root data_obs data_obs
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronE.root output_tauidele_2016pre/EGammaE.root data_obs data_obs
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/SingleElectronF.root output_tauidele_2016pre/EGammaF.root data_obs data_obs
hadd -f output_tauidele_2016pre/EGamma.root output_tauidele_2016pre/EGammaB.root output_tauidele_2016pre/EGammaC.root output_tauidele_2016pre/EGammaD.root output_tauidele_2016pre/EGammaE.root output_tauidele_2016pre/EGammaF.root
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/DY.root output_tauidele_2016pre/ZTT.root DY ZTT
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/DY.root output_tauidele_2016pre/ZLL.root DY ZLL
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/DY.root output_tauidele_2016pre/ZJ.root DY ZJ
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W.root output_tauidele_2016pre/Wincl.root W W 
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W1.root output_tauidele_2016pre/W1.root W1 W
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W2.root output_tauidele_2016pre/W2.root W2 W
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W3.root output_tauidele_2016pre/W3.root W3 W
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/W4.root output_tauidele_2016pre/W4.root W4 W
hadd -f output_tauidele_2016pre/W.root output_tauidele_2016pre/Wincl.root output_tauidele_2016pre/W1.root output_tauidele_2016pre/W2.root output_tauidele_2016pre/W3.root output_tauidele_2016pre/W4.root
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_t_antitop.root output_tauidele_2016pre/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_t_top.root output_tauidele_2016pre/ST_t_top.root ST_t_top ST
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_tW_antitop.root output_tauidele_2016pre/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ST_tW_top.root output_tauidele_2016pre/ST_tW_top.root ST_tW_top ST
hadd -f output_tauidele_2016pre/ST.root output_tauidele_2016pre/ST_t_antitop.root output_tauidele_2016pre/ST_t_top.root output_tauidele_2016pre/ST_tW_antitop.root output_tauidele_2016pre/ST_tW_top.root 
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WW2L2Nu.root output_tauidele_2016pre/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WZ2Q2L.root output_tauidele_2016pre/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/WZ3LNu.root output_tauidele_2016pre/WZ3LNu.root WZ3LNu VV
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ZZ2L2Nu.root output_tauidele_2016pre/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/ZZ4L.root output_tauidele_2016pre/ZZ4L.root ZZ4L VV
hadd -f output_tauidele_2016pre/VV.root output_tauidele_2016pre/WW2L2Nu.root output_tauidele_2016pre/WZ2Q2L.root output_tauidele_2016pre/WZ3LNu.root output_tauidele_2016pre/ZZ2L2Nu.root output_tauidele_2016pre/ZZ4L.root
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTToHadronic.root output_tauidele_2016pre/TTToHadronic.root TTToHadronic TT
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTToSemiLeptonic.root output_tauidele_2016pre/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_tauidele.exe 2016pre /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2016pre/TTTo2L2Nu.root output_tauidele_2016pre/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_tauidele_2016pre/TT.root output_tauidele_2016pre/TTToHadronic.root output_tauidele_2016pre/TTToSemiLeptonic.root output_tauidele_2016pre/TTTo2L2Nu.root
hadd -f output_tauidele_2016pre/MC.root output_tauidele_2016pre/ZLL.root output_tauidele_2016pre/ZTT.root output_tauidele_2016pre/ZJ.root output_tauidele_2016pre/ST.root output_tauidele_2016pre/VV.root output_tauidele_2016pre/TT.root output_tauidele_2016pre/W.root

python Create_fake_tauidele.py --year=2016pre
python Scale_W_tauidele.py --year=2016pre
hadd -f datacard_tauidele_2016pre.root output_tauidele_2016pre/Wrescaled.root output_tauidele_2016pre/QCD.root output_tauidele_2016pre/MC.root  output_tauidele_2016pre/EGamma.root 
