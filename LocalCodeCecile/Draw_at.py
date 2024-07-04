#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array

is_datadriven=1

def add_lumi(year):
    lowX=0.5
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    if (year=="2016pre"): lumi.AddText("2016 preVFP, 19 fb^{-1} (13 TeV)")
    if (year=="2016post"): lumi.AddText("2016 postVFP, 16 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

ROOT.gStyle.SetOptStat(0)

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='Output name')
args = parser.parse_args()


from ROOT import TCanvas, TGraphErrors
from ROOT import gROOT
from array import array
 
c1 = TCanvas( 'c1', 'A Simple Graph with error bars', 200, 10, 700, 500 )
c1.SetLeftMargin(0.3)
 
n = 5;
x  = array( 'f', [ -0.22, 0.05, 0., 0., 0. ] )
ex = array( 'f', [  0.05,  0.1, 0., 0., 0. ] )
y  = array( 'f', [     1,  2, 3, 4, 5 ] )
ey = array( 'f', [  0.,  0., 0., 0., 0. ] )
 
gr = TGraphErrors( n, x, y, ex, ey )
gr.SetTitle( '' )
gr.SetMarkerColor( 4 )
gr.SetMarkerStyle( 21 )
gr.Draw( 'AP' )
gr.GetYaxis().SetTitleSize(0.)
gr.GetYaxis().SetLabelSize(0.)

label=[]
for i in range(0,n):

label.append(ROOT.TPaveText(0.05, 0.2, 0.3, 0.3, "NDC"))
label.AddText("DELPHI")
label1.SetBorderSize(   0 )
label1.SetFillStyle(    0 )
label1.SetTextAlign(   12 )
label1.SetTextColor(    1 )
label1.SetTextSize(0.06)
label1.SetTextFont (   42 )
label1.Draw("same")


 
c1.Update()
c1.SaveAs("test.png")
