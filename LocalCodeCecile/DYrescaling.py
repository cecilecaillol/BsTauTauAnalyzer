#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array

nt=0

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
myhist=ROOT.TH1F("myhist","myhist",21,0,21)

#all DYemu
myhist.SetBinContent(1,2.55)
myhist.SetBinError(1,0.05)

#DYemu
myhist.SetBinContent(2,2.84)
myhist.SetBinError(2,0.13)
myhist.SetBinContent(3,2.42)
myhist.SetBinError(3,0.12)
myhist.SetBinContent(4,2.56)
myhist.SetBinError(4,0.09)
myhist.SetBinContent(5,2.47)
myhist.SetBinError(5,0.07)

#emu
myhist.SetBinContent(6,2.67)
myhist.SetBinError(6,0.39)
myhist.SetBinContent(7,1.85)
myhist.SetBinError(7,0.35)
myhist.SetBinContent(8,2.27)
myhist.SetBinError(8,0.26)
myhist.SetBinContent(9,2.86)
myhist.SetBinError(9,0.32)

#etau
myhist.SetBinContent(10,3.53)
myhist.SetBinError(10,0.62)
myhist.SetBinContent(11,2.61)
myhist.SetBinError(11,0.61)
myhist.SetBinContent(12,2.96)
myhist.SetBinError(12,0.60)
myhist.SetBinContent(13,2.18)
myhist.SetBinError(13,0.43)

#mutau
myhist.SetBinContent(14,2.72)
myhist.SetBinError(14,0.35)
myhist.SetBinContent(15,3.04)
myhist.SetBinError(15,0.39)
myhist.SetBinContent(16,1.97)
myhist.SetBinError(16,0.25)
myhist.SetBinContent(17,2.82)
myhist.SetBinError(17,0.28)

#tautau
myhist.SetBinContent(18,2.17)
myhist.SetBinError(18,0.93)
myhist.SetBinContent(19,2.51)
myhist.SetBinError(19,0.96)
myhist.SetBinContent(20,2.55)
myhist.SetBinError(20,0.94)
myhist.SetBinContent(21,2.09)
myhist.SetBinError(21,0.74)

if nt==1:
   #all DYemu
   myhist.SetBinContent(1,5.02)
   myhist.SetBinError(1,0.07)
   
   #DYemu
   myhist.SetBinContent(2,5.30)
   myhist.SetBinError(2,0.19)
   myhist.SetBinContent(3,5.03)
   myhist.SetBinError(3,0.19)
   myhist.SetBinContent(4,5.02)
   myhist.SetBinError(4,0.13)
   myhist.SetBinContent(5,4.91)
   myhist.SetBinError(5,0.07)
   
   #emu
   myhist.SetBinContent(6,5.05)
   myhist.SetBinError(6,0.58)
   myhist.SetBinContent(7,5.54)
   myhist.SetBinError(7,0.66)
   myhist.SetBinContent(8,4.67)
   myhist.SetBinError(8,0.41)
   myhist.SetBinContent(9,4.32)
   myhist.SetBinError(9,0.39)
   
   #etau
   myhist.SetBinContent(10,4.49)
   myhist.SetBinError(10,0.75)
   myhist.SetBinContent(11,4.61)
   myhist.SetBinError(11,0.92)
   myhist.SetBinContent(12,5.27)
   myhist.SetBinError(12,0.77)
   myhist.SetBinContent(13,4.62)
   myhist.SetBinError(13,0.63)
   
   #mutau
   myhist.SetBinContent(14,5.53)
   myhist.SetBinError(14,0.53)
   myhist.SetBinContent(15,5.47)
   myhist.SetBinError(15,0.60)
   myhist.SetBinContent(16,5.68)
   myhist.SetBinError(16,0.44)
   myhist.SetBinContent(17,4.74)
   myhist.SetBinError(17,0.40)
   
   #tautau
   myhist.SetBinContent(18,6.77)
   myhist.SetBinError(18,1.82)
   myhist.SetBinContent(19,8.91)
   myhist.SetBinError(19,2.09)
   myhist.SetBinContent(20,6.04)
   myhist.SetBinError(20,1.57)
   myhist.SetBinContent(21,3.52)
   myhist.SetBinError(21,0.93)




myhist.SetTitle("")
myhist.SetMarkerStyle(20)
myhist.GetYaxis().SetTitle("DY scaling factor (%)")
myhist.GetYaxis().SetTitleSize(0.08)
myhist.GetYaxis().SetTitleOffset(0.5)
if nt==1: myhist.GetYaxis().SetTitle("DY scaling factor (%)")
myhist.GetXaxis().SetBinLabel(1,"All")
myhist.GetXaxis().SetBinLabel(2,"2016pre")
myhist.GetXaxis().SetBinLabel(3,"2016post")
myhist.GetXaxis().SetBinLabel(4,"2017")
myhist.GetXaxis().SetBinLabel(5,"2018")
myhist.GetXaxis().SetBinLabel(6,"2016pre")
myhist.GetXaxis().SetBinLabel(7,"2016post")
myhist.GetXaxis().SetBinLabel(8,"2017")
myhist.GetXaxis().SetBinLabel(9,"2018")
myhist.GetXaxis().SetBinLabel(10,"2016pre")
myhist.GetXaxis().SetBinLabel(11,"2016post")
myhist.GetXaxis().SetBinLabel(12,"2017")
myhist.GetXaxis().SetBinLabel(13,"2018")
myhist.GetXaxis().SetBinLabel(14,"2016pre")
myhist.GetXaxis().SetBinLabel(15,"2016post")
myhist.GetXaxis().SetBinLabel(16,"2017")
myhist.GetXaxis().SetBinLabel(17,"2018")
myhist.GetXaxis().SetBinLabel(18,"2016pre")
myhist.GetXaxis().SetBinLabel(19,"2016post")
myhist.GetXaxis().SetBinLabel(20,"2017")
myhist.GetXaxis().SetBinLabel(21,"2018")
myhist.Draw("e")

total2 = ROOT.TF1( 'total2', 'pol0', 5, 9 )
total2.SetLineColor( 7 )
myhist.Fit(total2,'R')
box2=ROOT.TBox(5,total2.GetParameter(0)-total2.GetParError(0),9,total2.GetParameter(0)+total2.GetParError(0))
box2.SetFillColor(ROOT.TColor.GetColor("#ffdac1"))
box2.Draw("same")

total3 = ROOT.TF1( 'total3', 'pol0', 9, 13 )
total3.SetLineColor( 7 )
myhist.Fit(total3,'R')
box3=ROOT.TBox(9,total3.GetParameter(0)-total3.GetParError(0),13,total3.GetParameter(0)+total3.GetParError(0))
box3.SetFillColor(ROOT.TColor.GetColor("#e2f0cb"))
box3.Draw("same")

total4 = ROOT.TF1( 'total4', 'pol0', 13, 17 )
total4.SetLineColor( 7 )
myhist.Fit(total4,'R')
box4=ROOT.TBox(13,total4.GetParameter(0)-total4.GetParError(0),17,total4.GetParameter(0)+total4.GetParError(0))
box4.SetFillColor(ROOT.TColor.GetColor("#b5ead7"))
box4.Draw("same")

total5 = ROOT.TF1( 'total5', 'pol0', 17, 21 )
total5.SetLineColor( 0 )
myhist.Fit(total5,'R')
box5=ROOT.TBox(17,total5.GetParameter(0)-total5.GetParError(0),21,total5.GetParameter(0)+total5.GetParError(0))
box5.SetFillColor(ROOT.TColor.GetColor("#c7ceea"))
box5.Draw("same")

l1=ROOT.TLine(1,myhist.GetMinimum()*0.6,1,myhist.GetMaximum()*1.2)
l1.SetLineStyle(2)
l1.Draw("same")
l2=ROOT.TLine(5,myhist.GetMinimum()*0.6,5,myhist.GetMaximum()*1.2)
l2.SetLineStyle(2)
l2.Draw("same")
l3=ROOT.TLine(9,myhist.GetMinimum()*0.6,9,myhist.GetMaximum()*1.2)
l3.SetLineStyle(2)
l3.Draw("same")
l4=ROOT.TLine(13,myhist.GetMinimum()*0.6,13,myhist.GetMaximum()*1.2)
l4.SetLineStyle(2)
l4.Draw("same")
l5=ROOT.TLine(17,myhist.GetMinimum()*0.6,17,myhist.GetMaximum()*1.2)
l5.SetLineStyle(2)
l5.Draw("same")

l6=ROOT.TLine(0,myhist.GetBinContent(1),21,myhist.GetBinContent(1))
l6.SetLineColor(2)
l6.Draw("same")
l7=ROOT.TLine(0,myhist.GetBinContent(1)+myhist.GetBinError(1),21,myhist.GetBinContent(1)+myhist.GetBinError(1))
l7.SetLineColor(2)
l7.SetLineStyle(3)
l7.Draw("same")
l8=ROOT.TLine(0,myhist.GetBinContent(1)-myhist.GetBinError(1),21,myhist.GetBinContent(1)-myhist.GetBinError(1))
l8.SetLineColor(2)
l8.SetLineStyle(3)
l8.Draw("same")

myhist.Draw("esame")

categ1  = ROOT.TPaveText(0.15, 0.8, 0.35, 0.9, "NDC")
categ1.SetBorderSize(   0 )
categ1.SetFillStyle(    0 )
categ1.SetTextAlign(   12 )
categ1.SetTextColor(    1 )
categ1.SetTextSize(0.04)
categ1.SetTextFont (   42 )
categ1.AddText("e#mu, Z#rightarrow#tau_{e}#tau_{#mu}")
categ1.Draw("same")

categ2  = ROOT.TPaveText(0.3, 0.8, 0.5, 0.9, "NDC")
categ2.SetBorderSize(   0 )
categ2.SetFillStyle(    0 )
categ2.SetTextAlign(   12 )
categ2.SetTextColor(    1 )
categ2.SetTextSize(0.04)
categ2.SetTextFont (   42 )
categ2.AddText("e#mu, Z#rightarrowll")
categ2.Draw("same")

categ3  = ROOT.TPaveText(0.45, 0.8, 0.65, 0.9, "NDC")
categ3.SetBorderSize(   0 )
categ3.SetFillStyle(    0 )
categ3.SetTextAlign(   12 )
categ3.SetTextColor(    1 )
categ3.SetTextSize(0.04)
categ3.SetTextFont (   42 )
categ3.AddText("e#tau_{h}, Z#rightarrowll")
categ3.Draw("same")

categ4  = ROOT.TPaveText(0.6, 0.8, 0.8, 0.9, "NDC")
categ4.SetBorderSize(   0 )
categ4.SetFillStyle(    0 )
categ4.SetTextAlign(   12 )
categ4.SetTextColor(    1 )
categ4.SetTextSize(0.04)
categ4.SetTextFont (   42 )
categ4.AddText("#mu#tau_{h}, Z#rightarrowll")
categ4.Draw("same")

categ5  = ROOT.TPaveText(0.7, 0.8, 0.9, 0.9, "NDC")
categ5.SetBorderSize(   0 )
categ5.SetFillStyle(    0 )
categ1.SetTextAlign(   12 )
categ5.SetTextColor(    1 )
categ5.SetTextSize(0.04)
categ5.SetTextFont (   42 )
categ5.AddText("#tau_{h}#tau_{h}, Z#rightarrowll")
categ5.Draw("same")

lowX=0.15
lowY=0.85
lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
lumi.SetTextFont(42)
lumi.SetTextSize(0.08)
lumi.SetBorderSize(   0 )
lumi.SetFillStyle(    0 )
lumi.SetTextAlign(   12 )
lumi.SetTextColor(    1 )
if (nt==0): lumi.AddText("N_{tracks} < 10 to N_{tracks} = 0")
if (nt==1): lumi.AddText("N_{tracks} < 10 to N_{tracks} = 1")
lumi.Draw("same")

if nt==0: c1.SaveAs("DYrescaling_nt0.png")
if nt==1: c1.SaveAs("DYrescaling_nt1.png")
