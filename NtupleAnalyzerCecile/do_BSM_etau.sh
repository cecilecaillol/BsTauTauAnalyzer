sh do_BSM_etau_2016pre.sh
sh do_BSM_etau_2016post.sh
sh do_BSM_etau_2017.sh
sh do_BSM_etau_2018.sh
python AddPerYearUncertainties.py --inputFile output_etau_2018/signal.root --outputFile output_etau_Run2/etau_2018.root
python AddPerYearUncertainties.py --inputFile output_etau_2017/signal.root --outputFile output_etau_Run2/etau_2017.root
python AddPerYearUncertainties.py --inputFile output_etau_2016pre/signal.root --outputFile output_etau_Run2/etau_2016pre.root
python AddPerYearUncertainties.py --inputFile output_etau_2016post/signal.root --outputFile output_etau_Run2/etau_2016post.root
hadd -f output_etau_Run2/signal.root output_etau_Run2/etau_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="etau" --observable="atau"
