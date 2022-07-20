# Summary of the code of plot data/MC comparison of mutau final state

## Use only MC samples with the assumption that QCD in SS region = OS region

### basic_selection_mutau.cc
this code is used to generate data samples after selection as no SF included

### basic_selection_mutau_sf.cc
this code is used to generate MC sample after selection with SF included in both SS region and OS region
line 263: define the sign of mutau
line 163: define the output file

### DataMCcom_sf_SS.cc
Used to generate comparison plots of SS region, use data subtract MC as QCD background

### DataMCcom_sf.cc
Used to generate comparison plots of OS signal region, without QCD background

### DataMCcom_sf_addSSQCD.cc
Used to generate comparison plots of OS signal region, with QCD background

## Use data-driven FR method to estimate jet fake tau bkg

### rm_jetfaketau,cc
remove jet fake tau from MC samples in signal region, will be used in comparison plots

### CalFR.cc
Calculate fake rate using same sign region

### Estibkg.cc
Get data sample in OS region VVVL tauvsjet and add corresponding fake rate

### basic_selection_mutau_sf_anti_iso_nojetfaketau.cc
Get MC sample in OS region VVVL tauvsjet and add corresponding fake rate, will be subtracted from estimate bkg

### DataMCcom_estbkg_Cor.cc
Plot comparison plots

