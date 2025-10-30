# BsTauTauAnalyzer

## Setup

```
mkdir MyWorkingDirectory
cd MyWorkingDirectory
cmsrel CMSSW_15_0_10
cd CMSSW_15_0_10/src/
cmsenv
git cms-init
git cms-addpkg PhysicsTools/NanoAODTools
git clone https://github.com/cecilecaillol/BsTauTauAnalyzer.git -b Run3
scram b -j 8
```

## Run locally

Example for a ttbar MC file in the emu final state. The trigger list can be left empty. Change the last word to run other final states, or to run over data (e.g. "emudata2018" instead of "emumc2018").

```
python3 $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/nano_postproc.py output root://cms-xrd-global.cern.ch//store/mc/RunIII2024Summer24NanoAODv15/TTto2L2Nu_TuneCP5CR2_13p6TeV_powheg-pythia8/NANOAODSIM/150X_mcRun3_2024_realistic_v2-v2/2520000/067bfe45-b4a0-45e9-8309-f478e218aaf0.root --bi $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/keep_in.txt --bo $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/keep_out.txt -c "1" -I BsTauTauAnalyzer.Flattener.Flattener_analysis analysis_emumc2024 -N 1000
```

## Submit jobs via condor

Edit runNtuplizer.py with (or add arguments to the command below):
 * location for the output ntuples in your eos repository
 * final state to be run

Edit EraConfig.py:
 * comment or uncomment the last lines depending on whether you are running on MC or data (different json and trigger conditions)

Choose the list of files you want to run over in the command below (see lists of data and MC samples in BsTauTauAnalyzer/Flattener/data/).

```
voms-proxy-init --voms=cms --valid=48:0
python3 $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/runNtuplizer.py --in $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/data/NanoAODMC2024.txt
```

Follow the instructions printed by the above command to submit jobs. Don't forget the voms part. 
