#!/bin/bash
startMsg="Job started on "`date`
echo $startMsg

year=${1}
sample=${2}
name=${3}
cd /afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong
source setup.sh

cd /afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scripts_mutau

echo "python3 FinalSelection_mutau.py ${year} ${sample}"
python3 FinalSelection_mutau.py ${year} ${sample}

echo $startMsg
echo job finished on `date`