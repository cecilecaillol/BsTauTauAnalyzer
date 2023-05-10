#!/bin/bash
startMsg="Job started on "`date`
echo $startMsg

cd /afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong
source setup.sh

cd /afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scripts_tautau

for v in mvis Acopl tau1pt tau2pt nTrk MET_pt tau1eta tau2eta
#for v in mvis tau1pt tau2pt
do 
    echo "python3 Inclusive_histo_tautau.py ${v}"
    python3 Inclusive_histo_tautau.py ${v}
    echo "python3 plotInclusive_tautau.py -y 2018 -c full -v ${v}"
    python3 plotInclusive_tautau.py -y 2018 -c full -v ${v}
done

