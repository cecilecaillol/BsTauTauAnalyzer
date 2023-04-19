#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array

ROOT.gStyle.SetOptStat(0)
file_out=ROOT.TFile("beamspot_TF1_2017.root","recreate")

def pyf_tf1(x,p):
   print("test")
   file_in=ROOT.TFile("output_mumu_2017/Data.root","r")
   hist=file_in.Get("h_beamspot")
   print("test2")
   mybin  = hist.FindBin(x[0]);
   print(mybin)
   if (mybin <= 0 or mybin > hist.GetNbinsX()):
      return 0.;
   return hist.GetBinContent(mybin)


#f1 = ROOT.TF1("f1", pyf_tf1, hist.GetXaxis().GetXmin(), hist.GetXaxis().GetXmax(), 0)
f1 = ROOT.TF1("f1", pyf_tf1, 2.9,3.8, 0)
file_out.cd()
f1.Write()

fileData=ROOT.TFile("output_mumu_2017/Data.root","r")
c3=ROOT.TCanvas("canvas","",0,0,800,600)
bs=fileData.Get("h_beamspot")
bs.SetLineColor(1)
bs.SetTitle("")
bs.GetXaxis().SetTitle("Beamspot width (cm)")
bs.GetYaxis().SetTitle("Events")
bs.GetYaxis().SetTitleOffset(0.9)
bs.GetXaxis().SetTitleSize(0.05)
bs.GetYaxis().SetTitleSize(0.05)
bs.Draw("hist")
c3.SaveAs("plots_mumu_2017/bs_width.pdf")


bsz=fileData.Get("h_beamspotz")
bsz.SetLineColor(1)
bsz.SetTitle("")
bsz.GetXaxis().SetTitle("Beamspot z (cm)")
bsz.GetYaxis().SetTitle("Events")
bsz.GetXaxis().SetTitleSize(0.05)
bsz.GetYaxis().SetTitleSize(0.05)
bsz.Draw("hist")
c3.SaveAs("plots_mumu_2017/bs_z.pdf")

