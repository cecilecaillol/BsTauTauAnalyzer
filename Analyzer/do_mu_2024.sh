./Make.sh FinalSelection_mu.cc
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024C.root output_mu_2024/Muon_2024C.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024D.root output_mu_2024/Muon_2024D.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024E.root output_mu_2024/Muon_2024E.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024F.root output_mu_2024/Muon_2024F.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024G.root output_mu_2024/Muon_2024G.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024H.root output_mu_2024/Muon_2024H.root data_obs data_obs
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/Muon_2024I.root output_mu_2024/Muon_2024I.root data_obs data_obs
hadd -f output_mu_2024/Muon_2024.root output_mu_2024/Muon_2024C.root output_mu_2024/Muon_2024D.root output_mu_2024/Muon_2024E.root output_mu_2024/Muon_2024F.root output_mu_2024/Muon_2024G.root output_mu_2024/Muon_2024H.root output_mu_2024/Muon_2024I.root

./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TTto2L2Nu_v1.root output_mu_2024/TTto2L2Nu.root TTto2L2Nu TTto2L2Nu
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TTtoLNu2Q.root output_mu_2024/TTtoLNu2Q.root TTtoLNu2Q TTtoLNu2Q
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TWminusto2L2Nu.root output_mu_2024/TWminusto2L2Nu.root TWminusto2L2Nu singletop
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TWminustoLNu2Q.root output_mu_2024/TWminustoLNu2Q.root TWminustoLNu2Q singletop
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TbarWplusto2L2Nu.root output_mu_2024/TbarWplusto2L2Nu.root TbarWplusto2L2Nu singletop
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/TbarWplustoLNu2Q.root output_mu_2024/TbarWplustoLNu2Q.root TbarWplustoLNu2Q singletop
hadd -f output_mu_2024/singletop.root output_mu_2024/TWminusto2L2Nu.root output_mu_2024/TWminustoLNu2Q.root output_mu_2024/TbarWplusto2L2Nu.root output_mu_2024/TbarWplustoLNu2Q.root 
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/WW.root output_mu_2024/WW.root WW VV
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/WZ.root output_mu_2024/WZ.root WZ VV
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/ZZ.root output_mu_2024/ZZ.root ZZ VV
hadd -f output_mu_2024/VV.root output_mu_2024/WW.root output_mu_2024/WZ.root output_mu_2024/ZZ.root
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/WtoMuNu.root output_mu_2024/WtoMuNu.root WtoMuNu W
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/WtoTauNu.root output_mu_2024/WtoTauNu.root WtoTauNu W
hadd -f output_mu_2024/W.root output_mu_2024/WtoMuNu.root output_mu_2024/WtoTauNu.root
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/DYto2Mu.root output_mu_2024/DYto2Mu.root DYto2Mu DY
./FinalSelection_mu.exe 2024 /eos/cms/store/cmst3/group/bpark/ccaillol/ntuples_mu_2024/DYto2Tau.root output_mu_2024/DYto2Tau.root DYto2Tau DY
hadd -f output_mu_2024/DY.root output_mu_2024/DYto2Mu.root output_mu_2024/DYto2Tau.root
hadd -f datacard_mu2024.root output_mu_2024/Muon_2024.root  output_mu_2024/VV.root output_mu_2024/W.root output_mu_2024/DY.root output_mu_2024/TTto2L2Nu.root output_mu_2024/TTtoLNu2Q.root output_mu_2024/singletop.root
