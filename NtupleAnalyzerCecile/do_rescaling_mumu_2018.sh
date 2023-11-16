./Make.sh Rescaling_mumu.cc
./Rescaling_mumu.exe 2018 output_mumu_2018/GGMM.root output_mumu_2018/rescaling_GGMM.root GGMM GGMM
./Rescaling_mumu.exe 2018 output_mumu_2018/GGWW.root output_mumu_2018/rescaling_GGWW.root GGMM GGMM
#./Rescaling_mumu.exe 2018 output_mumu_2018/GGToMuMu.root output_mumu_2018/rescaling_GGToMuMu.root GGMM GGMM
./Rescaling_mumu.exe 2018 output_mumu_2018/Data.root output_mumu_2018/rescaling_Data.root data_obs data_obs
#hadd -f rescaling_mumu_2018.root output_mumu_2018/rescaling_GGMM.root output_mumu_2018/rescaling_Data.root
hadd -f rescaling_mumu_2018.root output_mumu_2018/rescaling_GGMM.root output_mumu_2018/rescaling_GGWW.root output_mumu_2018/rescaling_Data.root
