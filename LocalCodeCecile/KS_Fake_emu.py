#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.45, 0.64, 0.9, 0.86, "", "brNDC")
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

file=ROOT.TFile("avant_datacard_emu_2018.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

for i in range(0,2):
  hist1=file.Get("em_"+str(i)).Get("Fake").Clone()
  hist2=file.Get("em_"+str(i)).Get("rawFake").Clone()
  hist1.SetLineColor(ROOT.kGreen-1)
  hist1.SetTitle("")
  hist1.SetLineWidth(3)
  hist2.SetLineWidth(3)
  hist1.GetXaxis().SetTitle("m_{e#mu} (GeV)")
  hist1.GetYaxis().SetTitle("Events")
  hist1.Draw("hist")
  hist2.Draw("histsame")
  hist2.Draw("esame")
  hist1.Draw("esame")
  l=make_legend()
  l.AddEntry(hist1,"N_{tracks} = "+str(i),"l")
  l.AddEntry(hist2,"N_{tracks} < 10 ","l")
  l.Draw("same") 
  categ2  = ROOT.TPaveText(0.45, 0.5+0.013, 0.9, 0.5+0.155, "NDC")
  categ2.SetBorderSize(   0 )
  categ2.SetFillStyle(    0 )
  categ2.SetTextAlign(   12 )
  categ2.SetTextSize ( 0.05 )
  categ2.SetTextColor(    1 )
  categ2.SetTextFont (   42 )
  categ2.AddText("KS prob. = %.2f" %(hist1.KolmogorovTest(hist2)))
  categ2.Draw("same")
  c.SaveAs("plots_emu_2018/KS_fake_cat"+str(i)+".png")
