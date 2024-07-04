import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.45, 0.64, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

parser = argparse.ArgumentParser()
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()

file=ROOT.TFile("Taug2_etau_Run2.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

ncat=2
name=["ISR","muF"]

for j in range(0,ncat):

   pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
   pad1.Draw()
   pad1.cd()
   pad1.SetFillColor(0)
   pad1.SetBorderMode(0)
   pad1.SetBorderSize(10)
   pad1.SetTickx(1)
   pad1.SetTicky(1)
   pad1.SetLeftMargin(0.18)
   pad1.SetRightMargin(0.05)
   pad1.SetTopMargin(0.122)
   pad1.SetBottomMargin(0.026)
   pad1.SetFrameFillStyle(0)
   pad1.SetFrameLineStyle(0)
   pad1.SetFrameBorderMode(0)
   pad1.SetFrameBorderSize(10)
   #pad1.SetLogy()
   
   h0=file.Get("et_0").Get("ZLL")
   hu=file.Get("et_0").Get("ZLL_CMS_"+name[j]+"Up")
   hd=file.Get("et_0").Get("ZLL_CMS_"+name[j]+"Down")

   hd.SetLineColor(ROOT.EColor.kOrange+3)
   hu.SetLineColor(ROOT.EColor.kGreen+3)
   h0.SetTitle("")

   h0.Draw("e")
   hu.Draw("histsame")
   hd.Draw("histsame")

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   pad2.SetTopMargin(0.05);
   pad2.SetBottomMargin(0.35);
   pad2.SetLeftMargin(0.18);
   pad2.SetRightMargin(0.05);
   pad2.SetTickx(1)
   pad2.SetTicky(1)
   pad2.SetGridx()
   pad2.SetGridy()
   pad2.Draw()
   pad2.cd()

   hur=hu.Clone()
   hdr=hd.Clone()
   hur.Divide(h0)
   hdr.Divide(h0)
   hur.GetXaxis().SetLabelSize(0.1)
   hur.GetYaxis().SetLabelSize(0.08)
   hur.SetMinimum(0.9)
   hur.SetMaximum(1.1)
   hur.Draw("e")
   hdr.Draw("esame")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("unc/ZLL_"+name[j]+"_etau.png")

