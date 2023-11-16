./Make.sh Rescaling_mumu.cc
./Rescaling_mumu.exe 2016post output_mumu_2016post/GGMM.root output_mumu_2016post/rescaling_GGMM.root GGMM GGMM
./Rescaling_mumu.exe 2016post output_mumu_2016post/GGWW.root output_mumu_2016post/rescaling_GGWW.root GGMM GGMM
./Rescaling_mumu.exe 2016post output_mumu_2016post/Data.root output_mumu_2016post/rescaling_Data.root data_obs data_obs
hadd -f rescaling_mumu_2016post.root output_mumu_2016post/rescaling_GGMM.root output_mumu_2016post/rescaling_GGWW.root output_mumu_2016post/rescaling_Data.root
