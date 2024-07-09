# GGWWAnalyzer

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
git clone https://github.com/cms-tau-pog/TauIDSFs TauPOG/TauIDSFs
mkdir TauAnalysisTools
git clone -b run2_SFs https://github.com/cms-tau-pog/TauTriggerSFs $CMSSW_BASE/src/TauAnalysisTools/TauTriggerSFs
scram b -j 8
git clone https://github.com/cecilecaillol/GGWWAnalyzer.git
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

Example for a ttbar MC file in the emu final state. The trigger list can be left empty. Change the last word to run other final states, or to run over data (e.g. "emudata" instead of "emumc").

```
python $CMSSW_BASE/src/PhysicsTools/NanoAODTools/scripts/nano_postproc.py output /eos/cms/store/cmst3/group/taug2/reNanoAOD/RunIISummer20UL18_TuneCP5_madgraphLO_reweight/GGToTauTau_Inclusive_M_50GeV_PTFilter/221124_110940/0000/NanoAODv9_28.root --bi $CMSSW_BASE/src/GGWWAnalyzer/Skimmer/scripts/keep_in.txt --bo $CMSSW_BASE/src/GGWWAnalyzer/Skimmer/scripts/keep_out_emu.txt -c "(nElectron>0&&nMuon>0)" -I GGWWAnalyzer.Skimmer.Skimmer_analysis analysis_emumc2018
```

## Submit jobs via condor

Edit runNtuplizer.py with (or add arguments to the command below):
 * location for the output ntuples in your eos repository
 * final state to be run

Edit EraConfig.py:
 * comment or uncomment the last lines depending on whether you are running on MC or data (different json and trigger conditions)

Choose the list of files you want to run over in the command below (see lists of data and MC samples in GGWWAnalyzer/Skimmer/data/).

```
voms-proxy-init --voms=cms --valid=48:0
python $CMSSW_BASE/src/GGWWAnalyzer/Skimmer/scripts/runNtuplizer.py --in $CMSSW_BASE/src/GGWWAnalyzer/Skimmer/data/reNanoAODMC2018.txt
```

Follow the instructions printed by the above command to submit jobs. Don't forget the voms part. 
