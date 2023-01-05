import ROOT
import re
from array import array
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()


fileData=ROOT.TFile("output_etau_2018/EGamma.root","r")
fileMC=ROOT.TFile("output_etau_2018/MC.root","r")
fileW=ROOT.TFile("output_etau_2018/W.root","r")
fileout=ROOT.TFile("output_etau_2018/fractions.root","recreate")

W=fileW.Get("fractionOS").Clone()
QCD=fileData.Get("fractionSS").Clone()
QCD.Add(fileMC.Get("fractionSS"),-1)

denom=W.Clone()
denom.Add(QCD)
W.Divide(denom)
W.SetName("frac_W")
fileout.cd()
W.Write()

