./Make.sh Rescaling_mumu.cc
./Rescaling_mumu.exe 2017 output_mumu_2017/GGMM.root output_mumu_2017/rescaling_GGMM.root GGMM GGMM
./Rescaling_mumu.exe 2017 output_mumu_2017/GGWW.root output_mumu_2017/rescaling_GGWW.root GGMM GGMM
./Rescaling_mumu.exe 2017 output_mumu_2017/Data.root output_mumu_2017/rescaling_Data.root data_obs data_obs
hadd -f rescaling_mumu_2017.root output_mumu_2017/rescaling_GGMM.root output_mumu_2017/rescaling_GGWW.root output_mumu_2017/rescaling_Data.root
