./Make.sh FinalSelection_tautau.cc
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauA.root output_tautau_2018/TauA.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauB.root output_tautau_2018/TauB.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauC.root output_tautau_2018/TauC.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauD.root output_tautau_2018/TauD.root data_obs data_obs
hadd -f output_tautau_2018/Tau.root output_tautau_2018/TauA.root output_tautau_2018/TauB.root output_tautau_2018/TauC.root output_tautau_2018/TauD.root
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/DY.root output_tautau_2018/DY.root DY ZTT
python Relax_DY_tautau.py --year=2018
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ST_t_antitop.root output_tautau_2018/ST_t_antitop.root ST_t_antitop ST
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ST_t_top.root output_tautau_2018/ST_t_top.root ST_t_top ST
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ST_tW_antitop.root output_tautau_2018/ST_tW_antitop.root ST_tW_antitop ST
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ST_tW_top.root output_tautau_2018/ST_tW_top.root ST_tW_top ST
hadd -f output_tautau_2018/ST.root output_tautau_2018/ST_t_antitop.root output_tautau_2018/ST_t_top.root output_tautau_2018/ST_tW_antitop.root output_tautau_2018/ST_tW_top.root 
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/WW2L2Nu.root output_tautau_2018/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/WZ2Q2L.root output_tautau_2018/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/WZ3LNu.root output_tautau_2018/WZ3LNu.root WZ3LNu VV
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ZZ2L2Nu.root output_tautau_2018/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/ZZ4L.root output_tautau_2018/ZZ4L.root ZZ4L VV
hadd -f output_tautau_2018/VV.root output_tautau_2018/WW2L2Nu.root output_tautau_2018/WZ2Q2L.root output_tautau_2018/WZ3LNu.root output_tautau_2018/ZZ2L2Nu.root output_tautau_2018/ZZ4L.root
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TTToHadronic.root output_tautau_2018/TTToHadronic.root TTToHadronic TT
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TTToSemiLeptonic.root output_tautau_2018/TTToSemiLeptonic.root TTToSemiLeptonic TT
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TTTo2L2Nu.root output_tautau_2018/TTTo2L2Nu.root TTTo2L2Nu TT
hadd -f output_tautau_2018/TT.root output_tautau_2018/TTToHadronic.root output_tautau_2018/TTToSemiLeptonic.root output_tautau_2018/TTTo2L2Nu.root
hadd -f output_tautau_2018/MC.root output_tautau_2018/DYrescaled.root output_tautau_2018/ST.root output_tautau_2018/VV.root output_tautau_2018/TT.root
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/GGToTauTau.root output_tautau_2018/GGTT.root GGTT GGTT
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/GGToWW.root output_tautau_2018/GGWW.root GGWW GGWW

cp output_tautau_2018/GGTT.root output_tautau_2018/signal.root
#sh do_tautau_BSM_2018.sh
#python Prepare_BSM_combine.py --year="2018" --channel="tautau"

python Create_fake_tautau.py --year=2018
hadd -f datacard_tautau_2018.root output_tautau_2018/Fake.root output_tautau_2018/MC.root  output_tautau_2018/Tau.root output_tautau_2018/GGTT.root output_tautau_2018/GGWW.root
