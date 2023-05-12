#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

def add_lumi(year):
    lowX=0.55
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

def make_legend():
        output = ROOT.TLegend(0.5, 0.65, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

def make_legend2():
        output = ROOT.TLegend(0.45, 0.6, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output
    
    
ROOT.gStyle.SetOptStat(0)

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='Year to draw')
parser.add_argument('--channel', '-c', default=None, help='channel to draw')
parser.add_argument('--variable', '-v', default=None, help='Variable to draw')
args = parser.parse_args()

c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()

file=ROOT.TFile("./Taug2_mutau_2018.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)
#title="#tau p_{T}"
#title="#mu p_{T}"
title="m_{vis}"



Data=file.Get(args.channel).Get("data_obs")
#W=file.Get(categories[i]).Get("W")
TT=file.Get(args.channel).Get("TT")
VV=file.Get(args.channel).Get("VV")
ZTT=file.Get(args.channel).Get("ZTT")
ZLL = file.Get(args.channel).Get("ZLL")
ST=file.Get(args.channel).Get("ST")
GGTT=file.Get(args.channel).Get("GGTT")
GGWW=file.Get(args.channel).Get("GGWW")
VV.Add(ST.Clone())
#VV.Add(W.Clone())
Fake=file.Get(args.channel).Get("Fake")

GGTT.Scale(5)


Data.GetXaxis().SetTitle("")
Data.GetXaxis().SetTitleSize(0)
Data.GetXaxis().SetNdivisions(505)
Data.GetYaxis().SetLabelFont(42)
Data.GetYaxis().SetLabelOffset(0.01)
Data.GetYaxis().SetLabelSize(0.06)
Data.GetYaxis().SetTitleSize(0.075)
Data.GetYaxis().SetTitleOffset(1.04)
Data.SetTitle("")
Data.GetYaxis().SetTitle("Events/bin")
Data.SetMinimum(0.1)

#blind
for k in range(1,Data.GetSize()):
    Data.SetBinContent(k,0.0)
TT.SetFillColor(ROOT.TColor.GetColor("#4a4e4d"))
ZTT.SetFillColor(ROOT.TColor.GetColor("#f6cd61"))
ZLL.SetFillColor(ROOT.TColor.GetColor("#969df1"))
VV.SetFillColor(ROOT.TColor.GetColor("#ff8c94"))
Fake.SetFillColor(ROOT.TColor.GetColor("#3da4ab"))
GGWW.SetFillColor(ROOT.kGreen+1)

Data.SetMarkerStyle(20)
Data.SetMarkerSize(1)
TT.SetLineColor(1)
ZTT.SetLineColor(1)
ZLL.SetLineColor(1)
VV.SetLineColor(1)
Fake.SetLineColor(1)
Data.SetLineColor(1)
Data.SetLineWidth(2)

GGWW.SetLineColor(1)


GGTT.SetLineColor(2)
GGTT.SetLineWidth(3)
GGTTfull=GGTT.Clone()
GGTTfull.SetFillColor(2)
stack=ROOT.THStack("stack","stack")
stack.Add(TT)
stack.Add(Fake)
stack.Add(VV)
stack.Add(ZTT)
stack.Add(ZLL)
stack.Add(GGWW)
#stack.Add(GGTTfull)

errorBand = ZTT.Clone()
errorBand.Add(TT)
errorBand.Add(ZLL)
errorBand.Add(VV)
errorBand.Add(Fake)
errorBand.Add(GGWW)
#errorBand.Add(GGTTfull)

errorBand.SetMarkerSize(0)
errorBand.SetFillColor(new_idx)
errorBand.SetFillStyle(3001)
errorBand.SetLineWidth(1)

pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
pad1.Draw()
pad1.cd()
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetBorderSize(10)
pad1.SetTickx(1)
pad1.SetTicky(1)
pad1.SetLeftMargin(0.18)
pad1.SetRightMargin(0.05)
pad1.SetTopMargin(0.122)
pad1.SetBottomMargin(0.026)
pad1.SetFrameFillStyle(0)
pad1.SetFrameLineStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetFrameBorderSize(10)
pad1.SetLogy()

Data.GetXaxis().SetLabelSize(0)
Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
Data.SetMinimum(0.1)
Data.Draw("e")
stack.Draw("histsame")
errorBand.Draw("e2same")
Data.Draw("esame")

GGTT.Draw("histsame")

legende=make_legend()
legende.AddEntry(Data,"Observed","elp")
legende.AddEntry(ZTT,"Z#rightarrow #tau#tau","f")
legende.AddEntry(ZLL,"Z#rightarrow #mu#mu","f")
legende.AddEntry(TT,"t#bar{t}","f")
legende.AddEntry(VV,"VV,single-t","f")
legende.AddEntry(Fake,"Fake","f")
legende.AddEntry(GGWW,"#gamma#gamma#rightarrow WW","f")
legende.AddEntry(GGTT,"Signal x 3","l")
legende.AddEntry(errorBand,"Uncertainty","f")
legende.Draw()

l1=add_lumi(args.year)
l1.Draw("same")
l2=add_CMS()
l2.Draw("same")
l3=add_Preliminary()
l3.Draw("same")

pad1.RedrawAxis()

c.cd()
pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
pad2.SetTopMargin(0.05);
pad2.SetBottomMargin(0.35);
pad2.SetLeftMargin(0.18);
pad2.SetRightMargin(0.05);
pad2.SetTickx(1)
pad2.SetTicky(1)
pad2.SetGridx()
pad2.SetGridy()
pad2.Draw()
pad2.cd()
h1=Data.Clone()
h1.SetMaximum(2.0)#FIXME(1.5)
h1.SetMinimum(0.0)#FIXME(0.5)
h1.SetMarkerStyle(20)
h3=errorBand.Clone()
hwoE=errorBand.Clone()

for iii in range (1,hwoE.GetSize()-1):
    hwoE.SetBinError(iii,0)
h3.Sumw2()
h1.Sumw2()
h1.SetStats(0)
h1.Divide(hwoE)
h3.Divide(hwoE)
h1.GetXaxis().SetTitle(title)
h1.GetXaxis().SetLabelSize(0.08)
h1.GetYaxis().SetLabelSize(0.08)
h1.GetYaxis().SetTitle("Obs./Exp.")
h1.GetXaxis().SetNdivisions(505)
h1.GetYaxis().SetNdivisions(5)

h1.GetXaxis().SetTitleSize(0.15)
h1.GetYaxis().SetTitleSize(0.15)
h1.GetYaxis().SetTitleOffset(0.56)
h1.GetXaxis().SetTitleOffset(1.04)
h1.GetXaxis().SetLabelSize(0.11)
h1.GetYaxis().SetLabelSize(0.11)
h1.GetXaxis().SetTitleFont(42)
h1.GetYaxis().SetTitleFont(42)

h1.Draw("e0p")
h3.Draw("e2same")

c.cd()
pad1.Draw()

ROOT.gPad.RedrawAxis()

c.Modified()
c.SaveAs("Plotsmutau/"+args.year+"Sig/control_"+args.variable+args.channel+".pdf")
c.SaveAs("Plotsmutau/"+args.year+"Sig/control_"+args.variable+args.channel+".png")