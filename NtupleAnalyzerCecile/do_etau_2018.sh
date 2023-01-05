./Make.sh FinalSelection_etau.cc
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaA.root output_etau_2018/EGammaA.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaB.root output_etau_2018/EGammaB.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaC.root output_etau_2018/EGammaC.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaD.root output_etau_2018/EGammaD.root data_obs data_obs
hadd -f output_etau_2018/EGamma.root output_etau_2018/EGammaA.root output_etau_2018/EGammaB.root output_etau_2018/EGammaC.root output_etau_2018/EGammaD.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/DY.root output_etau_2018/ZTT.root DY ZTT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/DY.root output_etau_2018/ZLL.root DY ZLL
hadd -f output_etau_2018/DY.root output_etau_2018/ZTT.root output_etau_2018/ZLL.root 
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W.root output_etau_2018/W.root W W 
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_t_antitop.root output_etau_2018/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_t_top.root output_etau_2018/ST_t_top.root ST_t_top ST
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_tW_antitop.root output_etau_2018/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_tW_top.root output_etau_2018/ST_tW_top.root ST_tW_top ST
hadd -f output_etau_2018/ST.root output_etau_2018/ST_t_antitop.root output_etau_2018/ST_t_top.root output_etau_2018/ST_tW_antitop.root output_etau_2018/ST_tW_top.root 
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WW2L2Nu.root output_etau_2018/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WZ2Q2L.root output_etau_2018/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WZ3LNu.root output_etau_2018/WZ3LNu.root WZ3LNu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ZZ2L2Nu.root output_etau_2018/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ZZ4L.root output_etau_2018/ZZ4L.root ZZ4L VV
hadd -f output_etau_2018/VV.root output_etau_2018/WW2L2Nu.root output_etau_2018/WZ2Q2L.root output_etau_2018/WZ3LNu.root output_etau_2018/ZZ2L2Nu.root output_etau_2018/ZZ4L.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTToHadronic.root output_etau_2018/TTToHadronic.root TTToHadronic TT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTToSemiLeptonic.root output_etau_2018/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTTo2L2Nu.root output_etau_2018/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_etau_2018/TT.root output_etau_2018/TTToHadronic.root output_etau_2018/TTToSemiLeptonic.root output_etau_2018/TTTo2L2Nu.root
hadd -f output_etau_2018/MC.root output_etau_2018/DY.root output_etau_2018/W.root output_etau_2018/ST.root output_etau_2018/VV.root output_etau_2018/TT.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGTT.root output_etau_2018/GGTT.root GGTT GGTT

python Create_fake.py --year=2018
hadd -f datacard_etau_2018.root output_etau_2018/Fake.root output_etau_2018/DY.root output_etau_2018/ST.root output_etau_2018/VV.root output_etau_2018/TT.root  output_etau_2018/EGamma.root output_etau_2018/GGTT.root output_etau_2018/W.root
