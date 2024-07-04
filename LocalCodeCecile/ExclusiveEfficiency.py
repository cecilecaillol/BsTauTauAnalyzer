#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.45, 0.64, 0.9, 0.84, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

parser = argparse.ArgumentParser()
parser.add_argument('--year', default="2016", choices=['2016', '2017', '2018'], help="Year?")
options = parser.parse_args()

file1=ROOT.TFile("GGTT_eff_etau_2018_v2.root","r")
file2=ROOT.TFile("ZTT_eff_etau_2018_v2.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()
c.SetLeftMargin(0.15)
c.SetLogy()

variable=["N_{tracks}","Acoplanarity"]
name=["ntracks","aco"]
categ=["et_7","et_8"]
ncat=2

for j in range(0,ncat):
  h1c=file1.Get("h_ntracks")
  if (j==1): h1c=file1.Get("h_aco")
  #h1c=h1.Clone()
  #total=h1.Integral()
  #for k in range(1,h1.GetSize()-1):
  #  partial=0
  #  for kk in range(1,k+1):
  #    partial+=h1.GetBinContent(kk)
  #  eff=partial/total
  #  h1c.SetBinContent(k,eff)

  #h2=file2.Get(categ[j]).Get("ZTT")
  h2c=file2.Get("h_ntracks")
  if (j==1): h2c=file2.Get("h_aco")
  #h2c=h2.Clone()
  #total2=h2.Integral()
  #for k in range(1,h2.GetSize()-1):
  #  partial2=0
  #  for kk in range(1,k+1):
  #    partial2+=h2.GetBinContent(kk)
  #  eff2=partial2/total2
  #  h2c.SetBinContent(k,eff2)
  
  #if j==0: h1c.SetMinimum(0.001)
  #else: h1c.SetMinimum(0.1)
  h1c.SetTitle("")
  h1c.GetXaxis().SetTitle(variable[j])
  h1c.GetYaxis().SetTitle("Probability density")
  h1c.GetYaxis().SetTitleSize(0.06)
  h1c.GetYaxis().SetTitleOffset(0.9)
  h1c.SetLineWidth(3)
  h1c.DrawNormalized("hist")
  h2c.SetLineColor(ROOT.kMagenta+2)
  h2c.SetLineWidth(3)
  h2c.DrawNormalized("histsame")
  leg=make_legend()
  leg.AddEntry(h1c,"Signal","l")
  leg.AddEntry(h2c,"Z#rightarrow#tau#tau","l")
  leg.Draw("same")

  c.SaveAs("plots_etau_2018/eff_"+name[j]+".png")
