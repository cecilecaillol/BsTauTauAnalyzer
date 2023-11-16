./Make.sh FinalSelection_tautau.cc
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauA.root output_tautau_2018/TauA.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauB.root output_tautau_2018/TauB.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauC.root output_tautau_2018/TauC.root data_obs data_obs
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/TauD.root output_tautau_2018/TauD.root data_obs data_obs
hadd -f output_tautau_2018/Tau.root output_tautau_2018/TauA.root output_tautau_2018/TauB.root output_tautau_2018/TauC.root output_tautau_2018/TauD.root
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/DY.root output_tautau_2018/DY.root DY ZTT
python Relax_DY_tautau.py --year=2018
./FinalSelection_tautau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/GGToTauTau_Ctb20.root output_tautau_2018/GGTT.root GGTT_Ctb20 GGTT
cp output_tautau_2018/GGTT.root output_tautau_2018/signal.root

python Create_fake_tautau.py --year=2018
hadd -f datacard_tautau_2018.root output_tautau_2018/Fake.root output_tautau_2018/DYrescaled.root  output_tautau_2018/Tau.root output_tautau_2018/GGTT.root
