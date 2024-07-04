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

file_nominal=ROOT.TFile("ARCreview/DY_etau_2018_nominal.root","r")
file_nocorrection=ROOT.TFile("ARCreview/DY_etau_2018_nocorrection.root","r")
file_aco=ROOT.TFile("ARCreview/DY_etau_2018_aco.root","r")
file_acoPU=ROOT.TFile("ARCreview/DY_etau_2018_acoPU.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)

h_nominal=file_nominal.Get("et_0/ZTT")
h_nocorrection=file_nocorrection.Get("et_0/ZTT")
h_aco=file_aco.Get("et_0/ZTT")
h_acoPU=file_acoPU.Get("et_0/ZTT")
h_aco.Scale(0.0398/0.0247)
h_acoPU.Scale(0.0393/0.0247)
h_nocorrection.Scale(0.0398/0.0247)
c.cd()

h_nominal.SetLineColor(ROOT.kAzure)
h_nocorrection.SetLineColor(ROOT.kOrange-3)
h_aco.SetLineColor(ROOT.kViolet)
h_acoPU.SetLineColor(ROOT.kGreen+1)
h_nominal.SetLineWidth(3)
h_nocorrection.SetLineWidth(3)
h_aco.SetLineWidth(3)
h_acoPU.SetLineWidth(3)

h_nominal.SetTitle("")
h_nominal.SetMaximum(2.2*h_nominal.GetMaximum())
h_nominal.GetXaxis().SetTitle("m_{vis} (GeV)")
h_nominal.GetYaxis().SetTitle("Events")
h_nominal.GetXaxis().SetLabelSize(0.05)
h_nominal.GetYaxis().SetLabelSize(0.025)
h_nominal.GetXaxis().SetTitleSize(0.05)
h_nominal.GetYaxis().SetTitleSize(0.05)
h_nominal.GetYaxis().SetTitleOffset(0.92)
h_nominal.Draw("hist")
h_aco.Draw("histsame")
h_acoPU.Draw("histsame")
h_nocorrection.Draw("histsame")

leg=make_legend()
leg.AddEntry(h_nominal,"Nominal","l")
leg.AddEntry(h_acoPU,"No HS corr.","l")
leg.AddEntry(h_aco,"No HS/PU corr.","l")
leg.AddEntry(h_nocorrection,"No HS/PU/aco corr.","l")
leg.Draw("same")

c.SaveAs("section6effect_DYetau2018.png")

