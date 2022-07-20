# Summary of the code of plot data/MC comparison of tautau final state

### basic_selection_tautau.cc
this code is used to generate data samples in both SS region and Sig region after selection as no SF included
remember to check output file and sign of tautau to keep consistent

### basic_selection_tautau_sf.cc
this code is used to generate MC sample after selection with SF included in both SS region and OS region
remember to check output file and sign of tautau to keep consistent

### DataMCcom_sf.cc
Use to plot data/MC comparison only use bkg MC (no use up to now)

### DataMCcom_sf_addSSQCD.cc
Use to plot data/MC comparison with QCD evaluated from SS region (factor =1)

