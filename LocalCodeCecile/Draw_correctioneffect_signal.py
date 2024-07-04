#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.45, 0.55, 0.92, 0.92, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

file_nominal=ROOT.TFile("ARCreview/GGTT_etau_2018_nominal.root","r")
file_nocorrection=ROOT.TFile("ARCreview/GGTT_etau_2018_nocorrection.root","r")
file_noPU=ROOT.TFile("ARCreview/GGTT_etau_2018_noPU.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)

h_nominal=file_nominal.Get("et_0/GGTT")
h_nocorrection=file_nocorrection.Get("et_0/GGTT")
h_noPU=file_noPU.Get("et_0/GGTT")
c.cd()

h_nominal.SetLineColor(ROOT.kAzure)
h_nocorrection.SetLineColor(ROOT.kOrange-3)
h_noPU.SetLineColor(ROOT.kGreen+1)
h_nominal.SetLineWidth(3)
h_nocorrection.SetLineWidth(3)
h_noPU.SetLineWidth(3)

h_nominal.SetTitle("")
h_nominal.SetMaximum(1.3*h_nominal.GetMaximum())
h_nominal.GetXaxis().SetTitle("m_{vis} (GeV)")
h_nominal.GetYaxis().SetTitle("Events")
h_nominal.GetXaxis().SetLabelSize(0.05)
h_nominal.GetYaxis().SetLabelSize(0.025)
h_nominal.GetXaxis().SetTitleSize(0.05)
h_nominal.GetYaxis().SetTitleSize(0.05)
h_nominal.GetYaxis().SetTitleOffset(0.92)
h_nominal.Draw("hist")
h_noPU.Draw("histsame")
h_nocorrection.Draw("histsame")

leg=make_legend()
leg.AddEntry(h_nominal,"Nominal","l")
leg.AddEntry(h_noPU,"No PU corr.","l")
leg.AddEntry(h_nocorrection,"No PU/elastic corr.","l")
leg.Draw("same")

c.SaveAs("section6effect_GGTTetau2018.png")

