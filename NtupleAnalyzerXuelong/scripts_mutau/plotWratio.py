from ROOT import TFile, TFile, TH1D, TCanvas,TH1F,TPaveText,TF1,TMath,TH2F
import math
#from ROOT.RDF import TH1DModel
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
import ROOT
ROOT.gROOT.SetBatch(1)

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetFrameLineWidth(1)
ROOT.gStyle.SetLineWidth(1)
ROOT.gStyle.SetOptStat(0)


dm = int(sys.argv[1])

f = TFile("FRW_mutau.root","r")

histo = TH2F()

if dm==-1:
    histo = f.Get("hWFR_mtrans_mvis_allDM")
    
else:
    histo = f.Get("hWFR_mtrans_mvis_DM{}".format(dm))
    histo0 = f.Get("hWFR_mtrans_mvis_allDM")
    histo.Divide(histo0)
    
c = TCanvas("c","",800,600)
c.cd()
c.SetFillColor(0)
c.SetBorderMode(0)
c.SetBorderSize(10)
c.SetTickx(1)
c.SetTicky(1)
c.SetLeftMargin(0.10)
c.SetRightMargin(0.10)
c.SetTopMargin(0.122)
c.SetBottomMargin(0.122)
c.SetFrameFillStyle(0)
c.SetFrameLineStyle(0)
c.SetFrameLineWidth(2)
c.SetFrameBorderMode(0)
c.SetFrameBorderSize(10)

histo.GetXaxis().SetLabelSize(0.03)
histo.GetXaxis().SetTitle("mtrans")
histo.GetXaxis().SetNdivisions(505)
histo.GetYaxis().SetLabelFont(42)
histo.GetYaxis().SetLabelOffset(0.01)
histo.GetYaxis().SetLabelSize(0.03)
histo.GetYaxis().SetTitleSize(0.03)
histo.GetYaxis().SetTitleOffset(1.2)
histo.GetYaxis().SetTickLength(0.012)
histo.SetTitle("")
histo.GetYaxis().SetTitle("mvis")

histo.Draw("COLZ")


lowX=0.11
lowY=0.835
CMS =TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
CMS.SetTextFont(61)
CMS.SetTextSize(0.06)
CMS.SetBorderSize(   0 )
CMS.SetFillStyle(    0 )
CMS.SetTextAlign(   12 )
CMS.SetTextColor(    1 )
CMS.AddText("CMS")
CMS.Draw("same")

lowX=0.65
lowY=0.835
lumi  =TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
lumi.SetBorderSize(   0 )
lumi.SetFillStyle(    0 )
lumi.SetTextAlign(   12 )
lumi.SetTextColor(    1 )
lumi.SetTextSize(0.04)
lumi.SetTextFont (   42 )
lumi.AddText("2018, 59.74 fb^{-1} (13 TeV)")
lumi.Draw("same")

lowX=0.20
lowY=0.835
Pre  = TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
Pre.SetTextFont(52)
Pre.SetTextSize(0.04)
Pre.SetBorderSize(   0 )
Pre.SetFillStyle(    0 )
Pre.SetTextAlign(   12 )
Pre.SetTextColor(    1 )
Pre.AddText("Preliminary")
Pre.Draw("same")
c.RedrawAxis()

c.SaveAs("FRplots/Wratio_DM{}.png".format(dm))

