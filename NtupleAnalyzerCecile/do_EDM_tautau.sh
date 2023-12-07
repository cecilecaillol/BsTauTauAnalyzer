python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1130/Taug2_tautau_2016pre_BSM_Im.root --outputFile output_tautau_Run2/edm_tautau_2016pre.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1130/Taug2_tautau_2016post_BSM_Im.root --outputFile output_tautau_Run2/edm_tautau_2016post.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1130/Taug2_tautau_2017_BSM_Im.root --outputFile output_tautau_Run2/edm_tautau_2017.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1130/Taug2_tautau_2018_BSM_Im.root --outputFile output_tautau_Run2/edm_tautau_2018.root
hadd -f output_tautau_Run2/edm.root output_tautau_Run2/edm_tautau_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="tautau" --observable="dtau"
