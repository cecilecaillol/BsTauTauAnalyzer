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
parser.add_argument('--year', help="Year?")
options = parser.parse_args()


fileData=ROOT.TFile("output_etau_2018/EGamma.root","r")
if options.year!="2018":
  fileData=ROOT.TFile("output_etau_"+options.year+"/SingleElectron.root","r")
fileMC=ROOT.TFile("output_etau_"+options.year+"/MC.root","r")
fileW=ROOT.TFile("output_etau_"+options.year+"/W.root","r")
fileout=ROOT.TFile("fractions_"+options.year+".root","recreate")

W=fileW.Get("fractionOS").Clone()
QCD=fileData.Get("fractionSS").Clone()
QCD.Add(fileMC.Get("fractionSS"),-1)
QCD.Add(fileW.Get("fractionSS"),-1) #FIXME

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

######################################

W2=fileW.Get("fractionNtrackOS").Clone()
QCD2=fileData.Get("fractionNtrackSS").Clone()
QCD2.Add(fileMC.Get("fractionNtrackSS"),-1)
QCD2.Add(fileW.Get("fractionNtrackSS"),-1) #FIXME
#print fileData.Get("fractionNtrackOS").GetBinContent(11),fileMC.Get("fractionNtrackOS").GetBinContent(11),W2.GetBinContent(11),QCD2.GetBinContent(11)

denom2=W2.Clone()
denom2.Add(QCD2)
W2.Divide(denom2)
W2.SetName("fracNtrack_W")
fileout.cd()
W2.Write()

W2.SetTitle("")
W2.SetMarkerStyle(20)
W2.SetMarkerColor(1)
W2.SetLineColor(1)
W2.GetXaxis().SetTitle("N_{tracks}")
W2.GetYaxis().SetTitle("W fraction")
W2.Draw("e")
lumi.Draw("same")
cms.Draw("same")
c.cd()
c.Modified()
c.SaveAs("plots_etau_"+options.year+"/fractionsNtrack.pdf")
c.SaveAs("plots_etau_"+options.year+"/fractionsNtrack.png")

######################################

W3=fileW.Get("fractionAcoplanarityOS").Clone()
QCD3=fileData.Get("fractionAcoplanaritySS").Clone()
QCD3.Add(fileMC.Get("fractionAcoplanaritySS"),-1)
QCD3.Add(fileW.Get("fractionAcoplanaritySS"),-1) #FIXME

denom3=W3.Clone()
denom3.Add(QCD3)
W3.Divide(denom3)
average=W3.GetBinContent(1)
for k in range(1,W3.GetSize()):
   W3.SetBinContent(k,W3.GetBinContent(k)/average)
W3.GetXaxis().SetRangeUser(0,1)
#total = ROOT.TF1( 'total', 'pol3', 0, 1 )
W3.SetName("fracAcoplanarity_W")
fileout.cd()
W3.Write()

W3.SetTitle("")
W3.SetMarkerStyle(20)
W3.SetMarkerColor(1)
W3.SetLineColor(1)
W3.GetXaxis().SetTitle("Acoplanarity")
W3.GetYaxis().SetTitle("Ratio to nominal W fraction")
W3.Draw("e")
#total.SetLineColor( 2 )
#W3.Fit(total,'R')
lumi.Draw("same")
cms.Draw("same")
c.cd()
c.Modified()
c.SaveAs("plots_etau_"+options.year+"/fractionsAcoplanarity.pdf")
c.SaveAs("plots_etau_"+options.year+"/fractionsAcoplanarity.png")


