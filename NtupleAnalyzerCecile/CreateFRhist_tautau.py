import ROOT
import re
from array import array
import argparse

parser = argparse.ArgumentParser()
#parser.add_argument('--tes', default="nominal", choices=['nominal', 'up', 'down'], help="TES?")
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()

hist=[
"h_tauFR_QCD_dm0_VVVL","h_tauFR_QCD_dm0_M",
"h_tauFR_QCD_dm1_VVVL","h_tauFR_QCD_dm1_M",
"h_tauFR_QCD_dm10_VVVL","h_tauFR_QCD_dm10_M",
"h_tauFR_QCD_dm11_VVVL","h_tauFR_QCD_dm11_M"
]

fileData=ROOT.TFile("output_tautau_2018/Tau.root","r")
fileMC=ROOT.TFile("output_tautau_2018/MC.root","r")
fileDataSub=ROOT.TFile("output_tautau_2018/DataSub.root","recreate")

ncat=8

for i in range (0,ncat):
   Data=fileData.Get(hist[i])
   Data.Add(fileMC.Get(hist[i]),-1)
   Data.SetName(hist[i])
   fileDataSub.cd()
   Data.Write()

