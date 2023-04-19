#!/usr/bin/env python
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

file=ROOT.TFile("ZTT.root","r")

mvis1=[file.Get("h_mvis_nt0"),file.Get("h_mvis_nt1"),file.Get("h_mvis_nt2"),file.Get("h_mvis_nt3"),file.Get("h_mvis_nt4"),file.Get("h_mvis_nt5"),file.Get("h_mvis_nt6"),file.Get("h_mvis_nt7"),file.Get("h_mvis_nt8"),file.Get("h_mvis_nt9")]

mvis2=[file.Get("h_mvis_nt0to10"),file.Get("h_mvis_nt10to20"),file.Get("h_mvis_nt20to30"),file.Get("h_mvis_nt30to40"),file.Get("h_mvis_nt40to50"),file.Get("h_mvis_nt50to60"),file.Get("h_mvis_nt60to70"),file.Get("h_mvis_nt70to80"),file.Get("h_mvis_nt80to90"),file.Get("h_mvis_nt90to100")]

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

h1=ROOT.TH2F("h2","h2",10,0,10,10,0,10)
h1.SetTitle("")
h1.GetXaxis().SetTitle("N_{tracks}")
h1.GetYaxis().SetTitle("N_{tracks}")
h1.GetZaxis().SetTitle("KS probability")
for i in range(0,10):
  for j in range(0,10):
     h1.SetBinContent(i+1,j+1,mvis1[i].KolmogorovTest(mvis1[j]))
h1.Draw("colz")
c.SaveAs("plots_etau_2018/KS_mvis_DY_nt0to9.png")

h2=ROOT.TH2F("h2","h2",10,0,100,10,0,100)
h2.SetTitle("")
h2.GetXaxis().SetTitle("N_{tracks}")
h2.GetYaxis().SetTitle("N_{tracks}")
h2.GetZaxis().SetTitle("KS probability")
for i in range(0,10):
  for j in range(0,10):
     print(i,j)
     h2.SetBinContent(i+1,j+1,mvis2[i].KolmogorovTest(mvis2[j]))
h2.Draw("colz")
c.SaveAs("plots_etau_2018/KS_mvis_DY_nt0to100.png")

h3=ROOT.TH2F("h3","h3",5,0,10,5,0,10)
h3.SetTitle("")
h3.GetXaxis().SetTitle("N_{tracks}")
h3.GetYaxis().SetTitle("N_{tracks}")
h3.GetZaxis().SetTitle("KS probability")
for i in range(0,5):
  for j in range(0,5):
     hist1=mvis1[2*i].Clone()
     hist1.Add(mvis1[2*i+1].Clone())
     hist2=mvis1[2*j].Clone()
     hist2.Add(mvis1[2*j+1].Clone())
     h3.SetBinContent(i+1,j+1,hist1.KolmogorovTest(hist2))
h3.Draw("colz")
c.SaveAs("plots_etau_2018/KS_mvis_DY_nt0to9_rebin2.png")


hist1=file.Get("h_mvis_nt0").Clone()
hist1.Add(file.Get("h_mvis_nt1"))
hist2=file.Get("h_mvis_nt2").Clone()
hist2.Add(file.Get("h_mvis_nt3"))
hist3=file.Get("h_mvis_nt4").Clone()
hist3.Add(file.Get("h_mvis_nt5"))
hist4=file.Get("h_mvis_nt6").Clone()
hist4.Add(file.Get("h_mvis_nt7"))
hist5=file.Get("h_mvis_nt8").Clone()
hist5.Add(file.Get("h_mvis_nt9"))
histAll=file.Get("h_mvis_nt0to10").Clone()
hist1.SetLineColor(1)
hist2.SetLineColor(2)
hist3.SetLineColor(3)
hist4.SetLineColor(4)
hist5.SetLineColor(5)
histAll.SetLineColor(6)
hist1.SetTitle("")
hist1.GetXaxis().SetTitle("N_{tracks}")
hist1.GetYaxis().SetTitle("Probability density")
hist1.DrawNormalized("hist")
hist2.DrawNormalized("histsame")
hist3.DrawNormalized("histsame")
hist4.DrawNormalized("histsame")
hist5.DrawNormalized("histsame")
histAll.DrawNormalized("histsame")
hist1.DrawNormalized("esame")
hist2.DrawNormalized("esame")
hist3.DrawNormalized("esame")
hist4.DrawNormalized("esame")
hist5.DrawNormalized("esame")
histAll.DrawNormalized("esame")
l=make_legend()
l.AddEntry(hist1,"0 #leq N_{tk} < 2","l")
l.AddEntry(hist2,"2 #leq N_{tk} < 4","l")
l.AddEntry(hist3,"4 #leq N_{tk} < 6","l")
l.AddEntry(hist4,"6 #leq N_{tk} < 8","l")
l.AddEntry(hist5,"8 #leq N_{tk} < 10","l")
l.AddEntry(histAll,"0 #leq N_{tk} < 10","l")
l.Draw("same") 
c.SaveAs("plots_etau_2018/ZTT_mvis_compa.png")
