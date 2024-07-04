#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.15, 0.15, 0.92, 0.3, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

parser = argparse.ArgumentParser()
parser.add_argument('--year')
options = parser.parse_args()

channel="el"
#channel="mu"

#discriminant="HLTEle32"
discriminant="MVAisoWp80"

#discriminant="HLTIsoMu24"
#discriminant="mediumIso"
#discriminant="mediumID"

file_lt10=ROOT.TFile("sf_"+channel+"_"+options.year+"_"+discriminant+"_ntrackslt10.root","r")
file_gt30=ROOT.TFile("sf_"+channel+"_"+options.year+"_"+discriminant+"_ntracksgt30.root","r")
file_all=ROOT.TFile("sf_"+channel+"_"+options.year+"_"+discriminant+"_ntracksall.root","r")

histos=["eff_eta_pt35to50","sf_eta_pt35to50","eff_eta_pt20to35","sf_eta_pt20to35","eff_eta_pt50to75","sf_eta_pt50to75"]
names=["eff_eta_"+discriminant+"_pt35to50","sf_eta_"+discriminant+"_pt35to50","eff_eta_"+discriminant+"_pt20to35","sf_eta_"+discriminant+"_pt20to35","eff_eta_"+discriminant+"_pt50to75","sf_eta_"+discriminant+"_pt50to75"]

if channel=="mu":
   histos=["eff_eta_pt30to40","sf_eta_pt30to40","eff_eta_pt40to50","sf_eta_pt40to50","eff_eta_pt50to60","sf_eta_pt50to60","eff_eta_pt24to30","sf_eta_pt24to30"]
   names=["eff_eta_"+discriminant+"_pt30to40","sf_eta_"+discriminant+"_pt30to40","eff_eta_"+discriminant+"_pt40to50","sf_eta_"+discriminant+"_pt40to50","eff_eta_"+discriminant+"_pt50to60","sf_eta_"+discriminant+"_pt50to60","eff_eta_"+discriminant+"_pt24to30","sf_eta_"+discriminant+"_pt24to30"]

c=ROOT.TCanvas("canvas","",0,0,600,600)

for i in range(0,len(names)):
  h_lt10=file_lt10.Get(histos[i])
  h_gt30=file_gt30.Get(histos[i])
  h_all=file_all.Get(histos[i])
  c.cd()
  
  h_lt10.SetLineColor(2)
  h_gt30.SetLineColor(3)
  h_all.SetLineColor(4)

  h_lt10.SetTitle("")
  h_lt10.GetXaxis().SetTitle("#eta")
  h_lt10.GetYaxis().SetTitle("Efficiency")
  if "sf" in names[i]:  
     h_lt10.GetYaxis().SetTitle("Scale factor")
     if channel=="mu" and "mediumID" in names[i]: h_lt10.SetMinimum(0.9)
     if channel=="mu" and "mediumID" in names[i]: h_lt10.SetMaximum(1.02)
     if channel=="mu" and "mediumIso" in names[i]: h_lt10.SetMinimum(0.95)
     if channel=="mu" and "mediumIso" in names[i]: h_lt10.SetMaximum(1.02)
     if channel=="mu" and "HLT" in names[i]: h_lt10.SetMinimum(0.92)
     if channel=="mu" and "HLT" in names[i]: h_lt10.SetMaximum(1.05)
     if channel=="el" and "MVA" in names[i]: h_lt10.SetMaximum(1.0)
  h_lt10.GetXaxis().SetLabelSize(0.05)
  h_lt10.GetYaxis().SetLabelSize(0.05)
  h_lt10.GetXaxis().SetTitleSize(0.05)
  h_lt10.GetYaxis().SetTitleSize(0.05)
  h_lt10.Draw("hist")
  h_all.Draw("histsame")
  h_gt30.Draw("histsame")
  h_lt10.Draw("esame")
  h_all.Draw("esame")
  h_gt30.Draw("esame")

  leg=make_legend()
  leg.AddEntry(h_lt10,"N_{tracks} < 10","l")
  leg.AddEntry(h_gt30,"N_{tracks} > 30","l")
  leg.AddEntry(h_all,"All N_{tracks}","l")
  leg.Draw("same")

  c.SaveAs("ntracks_"+names[i]+"_"+options.year+".png")

