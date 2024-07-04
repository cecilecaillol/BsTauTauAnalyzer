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

file_VV=ROOT.TFile("study_VV.root","r")
file_DY=ROOT.TFile("study_DYemu.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)

h_VV=file_VV.Get("h_nHS_pt30to40")
h_DY=file_DY.Get("h_nHS_pt30to40")
c.cd()

h_VV.SetLineColor(2)
h_DY.SetLineColor(1)

h_VV.SetTitle("")
h_VV.GetXaxis().SetTitle("HS/UE extra track multiplicity")
h_VV.GetYaxis().SetTitle("Probability density")
h_VV.GetXaxis().SetLabelSize(0.05)
h_VV.GetYaxis().SetLabelSize(0.025)
h_VV.GetXaxis().SetTitleSize(0.05)
h_VV.GetYaxis().SetTitleSize(0.05)
h_VV.GetYaxis().SetTitleOffset(0.92)
h_VV.DrawNormalized("hist")
h_DY.DrawNormalized("histsame")
h_VV.DrawNormalized("esame")
h_DY.DrawNormalized("esame")

leg=make_legend()
leg.AddEntry(h_VV,"VV2L2Nu","l")
leg.AddEntry(h_DY,"DY","l")
leg.Draw("same")

c.SaveAs("VVstudy.png")

