# BsTauTauAnalyzer

## Setup

```
mkdir MyWorkingDirectory
cd MyWorkingDirectory
cmssw-el7
cmsrel CMSSW_10_6_27
cd CMSSW_10_6_27/src/
cmsenv
git cms-init
git clone https://github.com/cms-nanoAOD/nanoAOD-tools.git PhysicsTools/NanoAODTools
git clone https://github.com/cecilecaillol/BsTauTauAnalyzer.git
scram b -j 8
```

To add pileup weights, edit PhysicsTools/NanoAODTools/scripts/nano\_postproc.py. After l2, add:
```
from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import *
```

After l76, add:
```
for mod, names in options.imports:
        if "mc" in names or "sig" in names:
      if "2018" in names:
             modules.append(puAutoWeight_UL2018())
          if "2017" in names:
             modules.append(puAutoWeight_UL2017())
          if "2016" in names:
             modules.append(puAutoWeight_UL2016())
```

## Run locally

Example for a ttbar MC file in the emu final state. The trigger list can be left empty. Change the last word to run other final states, or to run over data (e.g. "emudata2018" instead of "emumc2018").

```
python $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/nano_postproc.py output root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL18NanoAODv9/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/130000/131D2BA3-C682-4F4C-B18A-4B1B0F195A2F.root --bi $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/keep_in.txt --bo $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/keep_out.txt -c "1" -I BsTauTauAnalyzer.Flattener.Flattener_analysis analysis_emumc2018 -N 1000
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
python $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/scripts/runNtuplizer.py --in $CMSSW_BASE/src/BsTauTauAnalyzer/Flattener/data/NanoAODMC2018.txt
```

Follow the instructions printed by the above command to submit jobs. Don't forget the voms part. 
