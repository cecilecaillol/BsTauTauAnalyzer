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
python $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/nano_postproc.py output root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL18NanoAODv9/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/280000/675D05BF-23FA-3E4F-9973-339D13789D66.root --bi $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/scripts/keep_in.txt --bo $CMSSW_BASE/src/MyNanoAnalyzer/TauG2/scripts/keep_out.txt -c "(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ||HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ)&&(nElectron>0&&nMuon>0)" -I MyNanoAnalyzer.TauG2.TauG2_analysis -N 100 analysis_emumc
```

## Submit jobs via condor

Edit runNtuplizer.py with (or add arguments to the command below):
 * location for the output ntuples in your eos repository
 * final state to be run

Edit EraConfig.py:
 * comment or uncomment the last lines depending on whether you are running on MC or data (different json and trigger conditions)

Choose the list of files you want to run over in the command below.

```
voms-proxy-init --voms=cms --valid=48:0
python $CMSSW_BASE/src/CMSDASTools/Analysis/scripts/runNtuplizer.py --in $CMSSW_BASE/src/CMSDASTools/Analysis/data/listSamplesMC2018.txt
```

Follow the instructions printed by the above command to submit jobs. Don't forget the voms part. 
