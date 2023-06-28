import ROOT
import re
from array import array
import argparse

parser = argparse.ArgumentParser()
#parser.add_argument('--tes', default="nominal", choices=['nominal', 'up', 'down'], help="TES?")
parser.add_argument('--year')
options = parser.parse_args()

hist=[
"h_tauFR_QCD_dm0_VVVL","h_tauFR_QCD_dm0_M",
"h_tauFR_QCD_dm1_VVVL","h_tauFR_QCD_dm1_M",
"h_tauFR_QCD_dm10_VVVL","h_tauFR_QCD_dm10_M",
"h_tauFR_QCD_dm11_VVVL","h_tauFR_QCD_dm11_M",
"h_tauFR_W_dm0_VVVL","h_tauFR_W_dm0_M",
"h_tauFR_W_dm1_VVVL","h_tauFR_W_dm1_M",
"h_tauFR_W_dm10_VVVL","h_tauFR_W_dm10_M",
"h_tauFR_W_dm11_VVVL","h_tauFR_W_dm11_M",
"h_tauFR_QCD_xtrg_VVVL","h_tauFR_QCD_xtrg_M",
"h_tauFR_W_xtrg_VVVL","h_tauFR_W_xtrg_M",
"h_tauFRnt_QCD_dm0_VVVL","h_tauFRnt_QCD_dm0_M",
"h_tauFRnt_QCD_dm1_VVVL","h_tauFRnt_QCD_dm1_M",
"h_tauFRnt_QCD_dm10_VVVL","h_tauFRnt_QCD_dm10_M",
"h_tauFRnt_QCD_dm11_VVVL","h_tauFRnt_QCD_dm11_M",
"h_tauFRnt_W_dm0_VVVL","h_tauFRnt_W_dm0_M",
"h_tauFRnt_W_dm1_VVVL","h_tauFRnt_W_dm1_M",
"h_tauFRnt_W_dm10_VVVL","h_tauFRnt_W_dm10_M",
"h_tauFRnt_W_dm11_VVVL","h_tauFRnt_W_dm11_M"
]

fileData=ROOT.TFile("output_etau_2018/EGamma.root","r")
if options.year!="2018": fileData=ROOT.TFile("output_etau_"+options.year+"/SingleElectron.root","r")
fileMC=ROOT.TFile("output_etau_"+options.year+"/MC.root","r")
fileDataSub=ROOT.TFile("output_etau_"+options.year+"/DataSub.root","recreate")

ncat=20+16

for i in range (0,ncat):
   Data=fileData.Get(hist[i])
   for j in range(1,Data.GetSize()-1):
       if Data.GetBinContent(j)<1: Data.SetBinError(j,1.8)
   Data.Add(fileMC.Get(hist[i]),-1)
   for j in range(1,Data.GetSize()-1):
       if Data.GetBinContent(j)<0: Data.SetBinContent(j,0.0)
   Data.SetName(hist[i])
   fileDataSub.cd()
   Data.Write()

