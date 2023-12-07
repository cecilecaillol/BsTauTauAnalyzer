sh do_EDM_emu_2016pre.sh
sh do_EDM_emu_2016post.sh
sh do_EDM_emu_2017.sh
sh do_EDM_emu_2018.sh
python AddPerYearUncertainties.py --inputFile output_emu_2018/edm.root --outputFile output_emu_Run2/edm_emu_2018.root
python AddPerYearUncertainties.py --inputFile output_emu_2017/edm.root --outputFile output_emu_Run2/edm_emu_2017.root
python AddPerYearUncertainties.py --inputFile output_emu_2016pre/edm.root --outputFile output_emu_Run2/edm_emu_2016pre.root
python AddPerYearUncertainties.py --inputFile output_emu_2016post/edm.root --outputFile output_emu_Run2/edm_emu_2016post.root
hadd -f output_emu_Run2/edm.root output_emu_Run2/edm_emu_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="emu" --observable="dtau"
