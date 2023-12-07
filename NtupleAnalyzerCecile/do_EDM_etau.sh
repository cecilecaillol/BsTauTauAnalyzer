sh do_EDM_etau_2016pre.sh
sh do_EDM_etau_2016post.sh
sh do_EDM_etau_2017.sh
sh do_EDM_etau_2018.sh
python AddPerYearUncertainties.py --inputFile output_etau_2018/edm.root --outputFile output_etau_Run2/edm_etau_2018.root
python AddPerYearUncertainties.py --inputFile output_etau_2017/edm.root --outputFile output_etau_Run2/edm_etau_2017.root
python AddPerYearUncertainties.py --inputFile output_etau_2016pre/edm.root --outputFile output_etau_Run2/edm_etau_2016pre.root
python AddPerYearUncertainties.py --inputFile output_etau_2016post/edm.root --outputFile output_etau_Run2/edm_etau_2016post.root
hadd -f output_etau_Run2/edm.root output_etau_Run2/edm_etau_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="etau" --observable="dtau"
