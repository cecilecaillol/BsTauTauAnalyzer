python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1026_mttto500/Taug2_mutau_2016pre_BSM.root --outputFile output_mutau_Run2/mutau_2016pre.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1026_mttto500/Taug2_mutau_2016post_BSM.root --outputFile output_mutau_Run2/mutau_2016post.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1026_mttto500/Taug2_mutau_2017_BSM.root --outputFile output_mutau_Run2/mutau_2017.root
python AddPerYearUncertainties.py --inputFile /eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/datacards_mutau_tautau/for_preapproval_1026_mttto500/Taug2_mutau_2018_BSM.root --outputFile output_mutau_Run2/mutau_2018.root
hadd -f output_mutau_Run2/signal.root output_mutau_Run2/mutau_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="mutau"
