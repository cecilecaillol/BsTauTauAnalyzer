./Make.sh Rescaling_mumu.cc
./Rescaling_mumu.exe 2016pre output_mumu_2016pre/GGMM.root output_mumu_2016pre/rescaling_GGMM.root GGMM GGMM
./Rescaling_mumu.exe 2016pre output_mumu_2016pre/GGWW.root output_mumu_2016pre/rescaling_GGWW.root GGMM GGMM
./Rescaling_mumu.exe 2016pre output_mumu_2016pre/Data.root output_mumu_2016pre/rescaling_Data.root data_obs data_obs
hadd -f rescaling_mumu_2016pre.root output_mumu_2016pre/rescaling_GGMM.root output_mumu_2016pre/rescaling_GGWW.root output_mumu_2016pre/rescaling_Data.root
