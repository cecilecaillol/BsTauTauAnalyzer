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
parser.add_argument('--year', '-y', default=None, help='Output name')
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetLogy()
c.SetLogx()

file=ROOT.TFile("datacard_mumu_2018.root","r")
if args.year=="2017":
   file=ROOT.TFile("datacard_mumu_2017.root","r")

if args.year=="2016":
   file=ROOT.TFile("datacard_mumu_2016.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["mumu0","mumu1","mumu2","mumu3","mumu4","mumu5","mumu6","mumu7","mumu8","mumu9","mumu10","mumu11","mumu12","mumu13","mumu14","mumu15"]
name=["mvis","acoplanarity","ptZ","npvs","npvsDown","npvsUp","acoplanarity_2030_2030","acoplanarity_3040_2030","acoplanarity_4050_2030","acoplanarity_gt50_2030","acoplanarity_3040_3040","acoplanarity_4050_3040","acoplanarity_gt50_3040","acoplanarity_4050_4050","acoplanarity_gt50_4050","acoplanarity_gt50_gt50"]
title=["m_{vis} (GeV)","Acoplanarity","p_{T}(Z) (GeV)","N_{PV}", "N_{PV} (MC down)", "N_{PV} (MC up)","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity"]
ncat=16

file_out=ROOT.TFile("correction_acoplanarity_"+args.year+".root","recreate")

for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs")
   DY=file.Get(categories[i]).Get("DY")
   Fake=file.Get(categories[i]).Get("Fake")
   #VV=file.Get(categories[i]).Get("WW") #FIXME was VV
   VV=file.Get(categories[i]).Get("VV") #FIXME was VV
   TT=file.Get(categories[i]).Get("TT")
   #DY.Scale(0.10)
   sf=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY.Integral()
   print(sf)
   DY.Scale(sf)
   
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


   DY.SetFillColor(ROOT.TColor.GetColor("#fe8a71"))
   Fake.SetFillColor(ROOT.TColor.GetColor("#3da4ab"))
   TT.SetFillColor(ROOT.TColor.GetColor("#4a4e4d"))
   VV.SetFillColor(ROOT.TColor.GetColor("#ff8c94"))


   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   DY.SetLineColor(1)
   TT.SetMarkerSize(1)
   VV.SetLineColor(1)
   Fake.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)

   stack=ROOT.THStack("stack","stack")
   stack.Add(DY)
   stack.Add(Fake)
   stack.Add(VV)
   stack.Add(TT)

   errorBand = DY.Clone()
   errorBand.Add(Fake)
   errorBand.Add(TT)
   errorBand.Add(VV)

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
   #pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
   #Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   legende=make_legend()
   if "inverted" in name[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DY,"Z#rightarrow #mu#mu","f")
   legende.AddEntry(TT,"TT","f")
   legende.AddEntry(VV,"VV","f")
   legende.AddEntry(Fake,"Fake","f")
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
   if "gt50_gt50" in name[i]:
     categ.AddText("#mu_{1} p_{T} > 50 GeV, #mu_{2} p_{T} > 50 GeV")
   elif "gt50_4050" in name[i]:
     categ.AddText("#mu_{1} p_{T} > 50 GeV, 40 < #mu_{2} p_{T} < 50 GeV")
   elif "gt50_3040" in name[i]:
     categ.AddText("#mu_{1} p_{T} > 50 GeV, 30 < #mu_{2} p_{T} < 40 GeV")
   elif "gt50_2030" in name[i]:
     categ.AddText("#mu_{1} p_{T} > 50 GeV, 20 < #mu_{2} p_{T} < 30 GeV")
   elif "2030_2030" in name[i]:
     categ.AddText("20 < #mu_{1} p_{T} < 30 GeV, 20 < #mu_{2} p_{T} < 30 GeV")
   elif "3040_2030" in name[i]:
     categ.AddText("30 < #mu_{1} p_{T} < 40 GeV, 20 < #mu_{2} p_{T} < 30 GeV")
   elif "4050_2030" in name[i]:
     categ.AddText("40 < #mu_{1} p_{T} < 50 GeV, 20 < #mu_{2} p_{T} < 30 GeV")
   elif "3040_3040" in name[i]:
     categ.AddText("30 < #mu_{1} p_{T} < 40 GeV, 30 < #mu_{2} p_{T} < 40 GeV")
   elif "4050_3040" in name[i]:
     categ.AddText("40 < #mu_{1} p_{T} < 50 GeV, 30 < #mu_{2} p_{T} < 40 GeV")
   elif "4050_4050" in name[i]:
     categ.AddText("40 < #mu_{1} p_{T} < 50 GeV, 40 < #mu_{2} p_{T} < 50 GeV")
   categ.Draw("same")

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
   h1.SetMaximum(1.5)#FIXME(1.5)
   h1.SetMinimum(0.5)#FIXME(0.5)
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
   h1.GetXaxis().SetTitle(title[i])
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

   if "acoplanarity" in name[i]:
     total = ROOT.TF1( 'total', 'pol8', 0, 0.4 )
     total.SetLineColor( 2 )
     h1.Fit(total,'R')
     total.SetName("fit_"+name[i])
     file_out.cd()
     total.Write()

   if "npvs" in name[i]:
     #total = ROOT.TF1( 'total', 'pol5', 0, 70 )
     #total.SetLineColor( 2 )
     #h1.Fit(total,'R')
     #total.SetName("fit_npvs")
     #file_out.cd()
     #total.Write()

     corr=Data.Clone()
     corr.Add(TT,-1)
     corr.Add(VV,-1)
     corr.Add(Fake,-1)
     corr.Divide(DY.Clone())
     corr.Scale(DY.Integral()/(Data.Integral()-TT.Integral()-VV.Integral()-Fake.Integral()))
     corr.SetName("correction_hist_"+name[i])
     file_out.cd()
     corr.Write()


   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_mumu_"+args.year+"/control_"+name[i]+".pdf")
   c.SaveAs("plots_mumu_"+args.year+"/control_"+name[i]+".png")

