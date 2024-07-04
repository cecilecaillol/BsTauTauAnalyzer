#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.35, 0.75, 0.92, 0.9, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

file_DY=ROOT.TFile("ZTT_etau_2018_acostudy.root","r")

c=ROOT.TCanvas("canvas","",0,0,600,600)
variable=["mvis","ptZ","aco"]
name=["m_{vis} (GeV)","p_{T}(Z) (GeV)","Acoplanarity"]

for i in range(0,len(variable)):
  h_DY=file_DY.Get("h_DY_"+variable[i]+"_waco")
  h_VV=file_DY.Get("h_DY_"+variable[i]+"_noaco")
  c.cd()
  
  h_VV.SetLineColor(2)
  h_DY.SetLineColor(1)
  
  h_VV.SetTitle("")
  h_VV.GetXaxis().SetTitle(name[i])
  h_VV.GetYaxis().SetTitle("Events")
  h_VV.GetXaxis().SetLabelSize(0.05)
  h_VV.GetYaxis().SetLabelSize(0.025)
  h_VV.GetXaxis().SetTitleSize(0.05)
  h_VV.GetYaxis().SetTitleSize(0.05)
  h_VV.GetYaxis().SetTitleOffset(0.92)
  h_VV.Draw("hist")
  h_DY.Draw("histsame")
  h_VV.Draw("esame")
  h_DY.Draw("esame")
  
  leg=make_legend()
  leg.AddEntry(h_DY,"Acoplanarity correction","l")
  leg.AddEntry(h_VV,"No acoplanarity correction","l")
  leg.Draw("same")
  
  c.SaveAs("DYcompa_acocorr_"+variable[i]+".png")

