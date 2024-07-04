# MyNanoAnalyzer

Code to run preselection for tau g-2 analysis. The supported final states are "ee,emu,etau,mumu,mutau,tautau", where tau denotes a hadronically decaying tau lepton.

## Setup

```
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
git clone https://github.com/cms-tau-pog/TauIDSFs TauPOG/TauIDSFs
git clone https://github.com/cecilecaillol/MyNanoAnalyzer.git
scram b -j 8
```

## Run locally

Example for a ttbar MC file in the emu final state. The trigger list can be left empty. Change the last word to run other final states, or to run over data (e.g. "emudata" instead of "emumc").

```
python $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/nano_postproc.py output /eos/cms/store/cmst3/group/taug2/reNanoAOD/RunIISummer20UL18_TuneCP5_madgraphLO_reweight/GGToTauTau_Inclusive_M_50GeV_PTFilter/221124_110940/0000/NanoAODv9_28.root --bi $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/scripts/keep_in.txt --bo $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/scripts/keep_out_etau.txt -c "(nElectron>0&&nTau>0)" -I MyNanoAnalyzer.TauG2.TauG2_analysis analysis_etaumc2018
```

## Submit jobs via condor

Edit runNtuplizer.py with (or add arguments to the command below):
 * location for the output ntuples in your eos repository
 * final state to be run

Edit EraConfig.py:
 * comment or uncomment the last lines depending on whether you are running on MC or data (different json and trigger conditions)

Choose the list of files you want to run over in the command below (see lists of data and MC samples in MyNanoAnalyzer/TauG2/data/).

```
voms-proxy-init --voms=cms --valid=48:0
python $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/scripts/runNtuplizer.py --in $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/data/reNanoAODMC2018.txt
```

Follow the instructions printed by the above command to submit jobs. Don't forget the voms part. 
