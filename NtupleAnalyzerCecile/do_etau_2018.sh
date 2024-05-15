./Make.sh FinalSelection_etau.cc
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaA.root output_etau_2018/EGammaA.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaB.root output_etau_2018/EGammaB.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaC.root output_etau_2018/EGammaC.root data_obs data_obs
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaD.root output_etau_2018/EGammaD.root data_obs data_obs
hadd -f output_etau_2018/EGamma.root output_etau_2018/EGammaA.root output_etau_2018/EGammaB.root output_etau_2018/EGammaC.root output_etau_2018/EGammaD.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/DY.root output_etau_2018/ZTT.root DY ZTT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/DY.root output_etau_2018/ZLL.root DY ZLL
hadd -f output_etau_2018/DY.root output_etau_2018/ZTT.root output_etau_2018/ZLL.root 
python Relax_DY.py --year=2018
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W.root output_etau_2018/Wincl.root W W 
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W1.root output_etau_2018/W1.root W1 W
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W2.root output_etau_2018/W2.root W2 W
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W3.root output_etau_2018/W3.root W3 W
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/W4.root output_etau_2018/W4.root W4 W
hadd -f output_etau_2018/W.root output_etau_2018/Wincl.root output_etau_2018/W1.root output_etau_2018/W2.root output_etau_2018/W3.root output_etau_2018/W4.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_t_antitop.root output_etau_2018/ST_t_antitop.root ST_t_antitop top
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_t_top.root output_etau_2018/ST_t_top.root ST_t_top top
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_tW_antitop.root output_etau_2018/ST_tW_antitop.root ST_tW_antitop top
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ST_tW_top.root output_etau_2018/ST_tW_top.root ST_tW_top top
#./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WW2L2Nu.root output_etau_2018/WW2L2Nu.root WW2L2Nu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WZ2Q2L.root output_etau_2018/WZ2Q2L.root WZ2Q2L VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/WZ3LNu.root output_etau_2018/WZ3LNu.root WZ3LNu VV
#./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ZZ2L2Nu.root output_etau_2018/ZZ2L2Nu.root ZZ2L2Nu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/VV2L2Nu.root output_etau_2018/VV2L2Nu.root VV2L2Nu VV
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/ZZ4L.root output_etau_2018/ZZ4L.root ZZ4L VV
hadd -f output_etau_2018/VV.root output_etau_2018/VV2L2Nu.root output_etau_2018/WZ2Q2L.root output_etau_2018/WZ3LNu.root output_etau_2018/ZZ4L.root #output_etau_2018/WW2L2Nu.root output_etau_2018/ZZ2L2Nu.root
#hadd -f output_etau_2018/VV.root output_etau_2018/WZ2Q2L.root output_etau_2018/WZ3LNu.root output_etau_2018/ZZ4L.root output_etau_2018/WW2L2Nu.root output_etau_2018/ZZ2L2Nu.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTToHadronic.root output_etau_2018/TTToHadronic.root TTToHadronic top
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTToSemiLeptonic.root output_etau_2018/TTToSemiLeptonic.root TTToSemiLeptonic top
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/TTTo2L2Nu.root output_etau_2018/TTTo2L2Nu.root TTTo2L2Nu top
hadd -f output_etau_2018/top.root output_etau_2018/TTToHadronic.root output_etau_2018/TTToSemiLeptonic.root output_etau_2018/TTTo2L2Nu.root output_etau_2018/ST_t_antitop.root output_etau_2018/ST_t_top.root output_etau_2018/ST_tW_antitop.root output_etau_2018/ST_tW_top.root
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGHTT.root output_etau_2018/GGHTT.root GGHTT GGHTT
#./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau_Ctb20.root output_etau_2018/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau_Ctb20_fid.root output_etau_2018/GGTT.root GGTT_Ctb20 GGTT
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau_Ctb20_fid.root output_etau_2018/GGTT_fid.root GGTT_Ctb20 GGTT_fid
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau_Ctb20_fid.root output_etau_2018/GGTT_nonfid.root GGTT_Ctb20 GGTT_nonfid
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToWW.root output_etau_2018/GGWW.root GGWW GGWW
./FinalSelection_etau.exe 2018 /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToElEl.root output_etau_2018/GGEE.root GGEE GGEE
hadd -f output_etau_2018/MC.root output_etau_2018/DYrescaled.root output_etau_2018/VV.root output_etau_2018/top.root output_etau_2018/GGWW.root output_etau_2018/GGEE.root 

cp output_etau_2018/GGTT.root output_etau_2018/signal.root
#sh do_BSM_etau_2018.sh
#python Prepare_BSM_combine.py --year="2018" --channel="etau"

python Create_fake.py --year=2018
hadd -f datacard_etau_2018.root output_etau_2018/Fake.root output_etau_2018/MC.root  output_etau_2018/EGamma.root output_etau_2018/GGTT.root output_etau_2018/GGTT_fid.root output_etau_2018/GGTT_nonfid.root output_etau_2018/W.root #output_etau_2018/bsm.root
#hadd -f bsm_datacard_etau_2018.root output_etau_2018/Fake.root output_etau_2018/MC.root  output_etau_2018/EGamma.root output_etau_2018/GGTT.root output_etau_2018/GGWW.root output_etau_2018/bsm.root
