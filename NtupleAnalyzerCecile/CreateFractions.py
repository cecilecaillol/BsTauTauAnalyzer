import ROOT
import re
from array import array
import argparse

def add_lumi(year):
    lowX=0.4
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.055)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.16
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.065)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi


parser = argparse.ArgumentParser()
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()


fileData=ROOT.TFile("output_etau_2018/EGamma.root","r")
fileMC=ROOT.TFile("output_etau_2018/MC.root","r")
fileW=ROOT.TFile("output_etau_2018/W.root","r")
#fileout=ROOT.TFile("output_etau_2018/fractions.root","recreate")
fileout=ROOT.TFile("testfractions.root","recreate")

W=fileW.Get("fractionOS").Clone()
QCD=fileData.Get("fractionSS").Clone()
QCD.Add(fileMC.Get("fractionSS"),-1)

denom=W.Clone()
denom.Add(QCD)
W.Divide(denom)
W.SetName("frac_W")
fileout.cd()
W.Write()

ROOT.gStyle.SetOptStat(0)
c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetRightMargin(0.2)
W.SetTitle("")
W.SetMarkerStyle(20)
W.SetMarkerColor(1)
W.SetLineColor(1)
W.GetXaxis().SetTitle("m_{T}(e,MET) (GeV)")
W.GetYaxis().SetTitle("m_{vis}(e,#tau_{h}) (GeV)")
W.GetZaxis().SetTitle("W fraction")
W.GetZaxis().SetTitleOffset(1.5)
W.Draw("colz")
lumi=add_lumi(options.year)
lumi.Draw("same")
cms=add_CMS()
cms.Draw("same")
c.cd()
c.Modified()
c.SaveAs("plots_etau_"+options.year+"/fractions.pdf")
c.SaveAs("plots_etau_"+options.year+"/fractions.png")

