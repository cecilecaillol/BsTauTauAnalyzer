#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

is_datadriven=1

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
    lowX=0.25
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
    lowX=0.25
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
        output = ROOT.TLegend(0.5, 0.55, 0.92, 0.86, "", "brNDC")
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
ROOT.gStyle.SetPaintTextFormat("1.3f");

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='Output name')
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetLogy()
c.SetLogx()

file=ROOT.TFile("rescaling_mumu_2018.root","r")
if args.year=="2017":
   file=ROOT.TFile("datacard_mumu_2017.root","r")

if args.year=="2016":
   file=ROOT.TFile("datacard_mumu_2016.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["mumu16"]
name=["mvis"]
title=["m_{#mu#mu} (GeV)"]
ncat=1


for i in range (0,ncat):
   Data=file.Get("data_obs_low")
   Bkg=file.Get("data_obs_high")
   Sig=file.Get("GGMM_low")
   Bkg.Scale((Data.GetBinContent(8)+Data.GetBinContent(9)+Data.GetBinContent(7))/(2.6*(Sig.GetBinContent(8)+Sig.GetBinContent(9)+Sig.GetBinContent(7))+Bkg.GetBinContent(8)+Bkg.GetBinContent(9)+Bkg.GetBinContent(7)))
   ScaledSig=Sig.Clone()
   ScaledSig.Scale(2.63)

   for k in range(1,Data.GetSize()-1):
     Data.SetBinContent(k,Data.GetBinContent(k)/Data.GetBinWidth(k))
     Data.SetBinError(k,Data.GetBinError(k)/Data.GetBinWidth(k))
     Bkg.SetBinContent(k,Bkg.GetBinContent(k)/Bkg.GetBinWidth(k))
     Bkg.SetBinError(k,Bkg.GetBinError(k)/Bkg.GetBinWidth(k))
     Sig.SetBinContent(k,Sig.GetBinContent(k)/Sig.GetBinWidth(k))
     Sig.SetBinError(k,Sig.GetBinError(k)/Sig.GetBinWidth(k))
     ScaledSig.SetBinContent(k,ScaledSig.GetBinContent(k)/ScaledSig.GetBinWidth(k))
     ScaledSig.SetBinError(k,ScaledSig.GetBinError(k)/ScaledSig.GetBinWidth(k))
   
   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(1.04)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events/GeV")
   Data.SetMinimum(0.1)


   Bkg.SetFillColor(ROOT.TColor.GetColor("#defde0"))
   Sig.SetFillColor(ROOT.TColor.GetColor("#f0defd"))


   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   Bkg.SetLineColor(1)
   Sig.SetLineColor(1)

   stack=ROOT.THStack("stack","stack")
   stack.Add(Sig)
   stack.Add(Bkg)

   errorBand = Sig.Clone()
   errorBand.Add(Bkg)

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
   Data.SetMinimum(0.01)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   ScaledSig.Add(Bkg)
   ScaledSig.SetLineColor(2)
   ScaledSig.SetFillColor(0)
   #ScaledSig.Draw("histsame")

   legende=make_legend()
   if "inverted" in name[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(Bkg,"Inclusive bkg","f")
   legende.AddEntry(Sig,"Elastic #gamma#gamma#rightarrow#mu#mu","f")
   #legende.AddEntry(ScaledSig,"Bkg + sig x 2.6","l")
   legende.AddEntry(errorBand,"Uncertainty","f")
   legende.Draw()

   l1=add_lumi(args.year)
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
 
   pad1.RedrawAxis()

   categ  = ROOT.TPaveText(0.35, 0.5+0.013, 0.83, 0.50+0.155, "NDC")
   categ.SetBorderSize(   0 )
   categ.SetFillStyle(    0 )
   categ.SetTextAlign(   12 )
   categ.SetTextSize ( 0.05 )
   categ.SetTextColor(    1 )
   categ.SetTextFont (   42 )
   #categ.Draw("same")

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
   h1.Add(Bkg.Clone(),-1)
   h1.SetMaximum(6)#FIXME(1.5)
   h1.SetMinimum(0.0)#FIXME(0.5)
   h1.SetMarkerStyle(20)
   h3=errorBand.Clone()
   hwoE=Sig.Clone()
   #for iii in range (1,hwoE.GetSize()-1):
   #  hwoE.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE)
   h3.Divide(hwoE)
   h1.GetXaxis().SetTitle(title[i])
   h1.GetXaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetLabelSize(0.08)
   h1.GetYaxis().SetTitle("#frac{Data - bkg}{#gamma#gamma#rightarrow#mu#mu}")
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
   #h3.Draw("e2same")


   #total = ROOT.TF1( 'total', 'pol1', 60, 600 )
   total = ROOT.TF1( 'total', 'pol0', 120, 550 )
   total.SetLineColor( 2 )
   h1.Fit(total,'R')

   total2 = ROOT.TF1( 'total', 'pol1', 120, 550 )
   total2.SetLineColor( 3 )
   h1.Fit(total2,'R')

   c.cd()

   pad1.cd()
   pave  = ROOT.TPaveText(0.5, 0.35, 0.9, 0.55, "NDC")
   pave.SetBorderSize(   0 )
   pave.SetFillStyle(    0 )
   pave.SetTextAlign(   12 )
   pave.SetTextColor(    1 )
   pave.SetTextSize(0.04)
   pave.SetTextFont (   42 )
   pave.AddText("Flat SF = %.2f #pm %.2f" %(total.GetParameter(0),total.GetParError(0)))
   pave.AddText("Linear SF = %.2f+%.5f#times m_{#mu#mu}" %(total2.GetParameter(0),total2.GetParameter(1)))
   pave.Draw("same")

   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_mumu_"+args.year+"/rescaling.png")

