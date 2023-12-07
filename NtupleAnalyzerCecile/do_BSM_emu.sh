sh do_BSM_emu_2016pre.sh
sh do_BSM_emu_2016post.sh
sh do_BSM_emu_2017.sh
sh do_BSM_emu_2018.sh
python AddPerYearUncertainties.py --inputFile output_emu_2018/signal.root --outputFile output_emu_Run2/emu_2018.root
python AddPerYearUncertainties.py --inputFile output_emu_2017/signal.root --outputFile output_emu_Run2/emu_2017.root
python AddPerYearUncertainties.py --inputFile output_emu_2016pre/signal.root --outputFile output_emu_Run2/emu_2016pre.root
python AddPerYearUncertainties.py --inputFile output_emu_2016post/signal.root --outputFile output_emu_Run2/emu_2016post.root
hadd -f output_emu_Run2/signal.root output_emu_Run2/emu_201*.root
python Prepare_BSM_combine.py --year="Run2" --channel="emu" --observable="atau"
