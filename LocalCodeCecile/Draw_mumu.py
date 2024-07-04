#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

is_datadriven=1

def add_lumi(year):
    lowX=0.59
    lowY=0.83
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    if (year=="2018"): lumi.AddText("2018, 60 fb^{#minus1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{#minus1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{#minus1} (13 TeV)")
    if (year=="2016pre"): lumi.AddText("2016 preVFP, 20 fb^{-1} (13 TeV)")
    if (year=="2016post"): lumi.AddText("2016 postVFP, 17 fb^{-1} (13 TeV)")
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
    #lumi.AddText("Preliminary")
    #lumi.AddText("Supplementary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.32, 0.55, 0.9, 0.86, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        return output

def make_legend2():
        output = ROOT.TLegend(0.2, 0.7, 0.92, 0.95, "", "brNDC")
        output.SetNColumns(4)
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

#file=ROOT.TFile("datacard_mumu_2018.root","r")
#if args.year=="2017":
#   file=ROOT.TFile("datacard_mumu_2017.root","r")
#
#if args.year=="2016":
#   file=ROOT.TFile("datacard_mumu_2016.root","r")
#
#if args.year=="2016pre":
#   file=ROOT.TFile("datacard_mumu_2016pre.root","r")
#
#if args.year=="2016post":
#   file=ROOT.TFile("datacard_mumu_2016post.root","r")

#file=ROOT.TFile("acocorrected_datacard_mumu_2018.root","r")
file=ROOT.TFile("pdf_datacard_mumu_2018.root","r")
if args.year=="2017":
   file=ROOT.TFile("pdf_datacard_mumu_2017.root","r")

if args.year=="2016":
   file=ROOT.TFile("pdf_datacard_mumu_2016.root","r")

if args.year=="2016pre":
   file=ROOT.TFile("pdf_datacard_mumu_2016pre.root","r")

if args.year=="2016post":
   file=ROOT.TFile("pdf_datacard_mumu_2016post.root","r")


adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["mumu0","mumu1","mumu2","mumu3","mumu4","mumu5","mumu6","mumu7","mumu8","mumu9","mumu10","mumu11","mumu12","mumu13","mumu14","mumu15","mumu1_pdfu","mumu2_pdfu","mumu1_pdfd","mumu2_pdfd","mumu1_scale1","mumu1_scale2","mumu1_scale3","mumu1_scale4","mumu1_scale5","mumu1_scale6","mumu2_scale1","mumu2_scale2","mumu2_scale3","mumu2_scale4","mumu2_scale5","mumu2_scale6","mumudz"]
name=["mvis","acoplanarity","ptZ","npvs","npvsDown","npvsUp","acoplanarity_2030_2030","acoplanarity_3040_2030","acoplanarity_4050_2030","acoplanarity_gt50_2030","acoplanarity_3040_3040","acoplanarity_4050_3040","acoplanarity_gt50_3040","acoplanarity_4050_4050","acoplanarity_gt50_4050","acoplanarity_gt50_gt50","acoplanarity_pdfu","ptZ_pdfu","acoplanarity_pdfd","ptZ_pdfd","acoplanarity_scale1","acoplanarity_scale2","acoplanarity_scale3","acoplanarity_scale4","acoplanarity_scale5","acoplanarity_scale6","ptZ_scale1","ptZ_scale2","ptZ_scale3","ptZ_scale4","ptZ_scale5","ptZ_scale6","dz"]
title=["m_{vis} (GeV)","Acoplanarity","p_{T}(Z) (GeV)","N_{PV}", "N_{PV} (MC down)", "N_{PV} (MC up)","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","p_{T}(Z) (GeV)","Acoplanarity","p_{T}(Z) (GeV)","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","Acoplanarity","p_{T}(Z) (GeV)","p_{T}(Z) (GeV)","p_{T}(Z) (GeV)","p_{T}(Z) (GeV)","p_{T}(Z) (GeV)","p_{T}(Z) (GeV)","|d_{z}(#mu,#mu)| (cm)"]
ncat=16+4+12+1

file_out=ROOT.TFile("correction_acoplanarity_"+args.year+".root","recreate")


inclusive_sf=1.0
for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs")
   DY=file.Get(categories[i]).Get("DY")
   DY_scale1=DY.Clone()
   DY_scale2=DY.Clone()
   DY_scale3=DY.Clone()
   DY_scale4=DY.Clone()
   DY_scale5=DY.Clone()
   DY_scale6=DY.Clone()
   DY_ps1=DY.Clone()
   DY_ps2=DY.Clone()
   DY_ps3=DY.Clone()
   DY_ps4=DY.Clone()
   Fake=file.Get(categories[i]).Get("Fake")
   #VV=file.Get(categories[i]).Get("WW") #FIXME was VV
   VV=file.Get(categories[i]).Get("VV") #FIXME was VV
   TT=file.Get(categories[i]).Get("TT")
   #DY.Scale(0.10)
   sf=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY.Integral()
   inclusive_sf1=sf
   inclusive_sf2=sf
   inclusive_sf3=sf
   inclusive_sf4=sf
   inclusive_sf5=sf
   inclusive_sf6=sf
   initialsf_scale1=file.Get("mumu1").Get("DY_scale1").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_scale2=file.Get("mumu1").Get("DY_scale2").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_scale3=file.Get("mumu1").Get("DY_scale3").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_scale4=file.Get("mumu1").Get("DY_scale4").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_scale5=file.Get("mumu1").Get("DY_scale5").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_scale6=file.Get("mumu1").Get("DY_scale6").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_ps1=file.Get("mumu1").Get("DY_ps1").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_ps2=file.Get("mumu1").Get("DY_ps2").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_ps3=file.Get("mumu1").Get("DY_ps3").Integral()/file.Get("mumu1").Get("DY").Integral()
   initialsf_ps4=file.Get("mumu1").Get("DY_ps4").Integral()/file.Get("mumu1").Get("DY").Integral()
   if ((i>5 and i<16) or i==1):
     print(categories[i],"DY_scale1")
     DY_scale1=file.Get(categories[i]).Get("DY_scale1")
     DY_scale2=file.Get(categories[i]).Get("DY_scale2")
     DY_scale3=file.Get(categories[i]).Get("DY_scale3")
     DY_scale4=file.Get(categories[i]).Get("DY_scale4")
     DY_scale5=file.Get(categories[i]).Get("DY_scale5")
     DY_scale6=file.Get(categories[i]).Get("DY_scale6")
     #DY_scale1.Scale(1.0/0.983)
     #DY_scale2.Scale(1.0/1.015)
     #DY_scale3.Scale(1.0/0.960)
     #DY_scale4.Scale(1.0/1.025)
     #DY_scale5.Scale(1.0/0.986)
     #DY_scale6.Scale(1.0/1.018)
     DY_scale1.Scale(1.0/initialsf_scale1)
     DY_scale2.Scale(1.0/initialsf_scale2)
     DY_scale3.Scale(1.0/initialsf_scale3)
     DY_scale4.Scale(1.0/initialsf_scale4)
     DY_scale5.Scale(1.0/initialsf_scale5)
     DY_scale6.Scale(1.0/initialsf_scale6)
     DY_ps1.Scale(1.0/initialsf_ps1)
     DY_ps2.Scale(1.0/initialsf_ps2)
     DY_ps3.Scale(1.0/initialsf_ps3)
     DY_ps4.Scale(1.0/initialsf_ps4)
     DY_ps1=file.Get(categories[i]).Get("DY_ps1")
     DY_ps2=file.Get(categories[i]).Get("DY_ps2")
     DY_ps3=file.Get(categories[i]).Get("DY_ps3")
     DY_ps4=file.Get(categories[i]).Get("DY_ps4")
     sf1=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale1.Integral()
     sf2=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale2.Integral()
     sf3=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale3.Integral()
     sf4=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale4.Integral()
     sf5=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale5.Integral()
     sf6=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_scale6.Integral()
     sfps1=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_ps1.Integral()
     sfps2=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_ps2.Integral()
     sfps3=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_ps3.Integral()
     sfps4=(Data.Integral()-Fake.Integral()-VV.Integral()-TT.Integral())/DY_ps4.Integral()

   print(sf)
   if i==1: 
     inclusive_sf1=sf1
     inclusive_sf2=sf2
     inclusive_sf3=sf3
     inclusive_sf4=sf4
     inclusive_sf5=sf5
     inclusive_sf6=sf6
     inclusive_sfps1=sfps1
     inclusive_sfps2=sfps2
     inclusive_sfps3=sfps3
     inclusive_sfps4=sfps4
     inclusive_sf=sf

   if i<16: DY.Scale(inclusive_sf)
   else: DY.Scale(sf)
   if ((i>5 and i<16) or i==1):
     #DY_scale1.Scale(inclusive_sf1)
     #DY_scale2.Scale(inclusive_sf2)
     #DY_scale3.Scale(inclusive_sf3)
     #DY_scale4.Scale(inclusive_sf4)
     #DY_scale5.Scale(inclusive_sf5)
     #DY_scale6.Scale(inclusive_sf6)
     #DY_ps1.Scale(inclusive_sfps1)
     #DY_ps2.Scale(inclusive_sfps2)
     #DY_ps3.Scale(inclusive_sfps3)
     #DY_ps4.Scale(inclusive_sfps4)
     DY_scale1.Scale(inclusive_sf)
     DY_scale2.Scale(inclusive_sf)
     DY_scale3.Scale(inclusive_sf)
     DY_scale4.Scale(inclusive_sf)
     DY_scale5.Scale(inclusive_sf)
     DY_scale6.Scale(inclusive_sf)
     DY_ps1.Scale(inclusive_sf)
     DY_ps2.Scale(inclusive_sf)
     DY_ps3.Scale(inclusive_sf)
     DY_ps4.Scale(inclusive_sf)

   if ((i>5 and i<16) or i==1): print("DY norm scale: ",DY.Integral(),DY_scale1.Integral(),DY_scale2.Integral(),DY_scale3.Integral(),DY_scale4.Integral(),DY_scale5.Integral(),DY_scale6.Integral())

   Fake.Scale(3)
   
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


   DY.SetFillColor(ROOT.TColor.GetColor("#f9b5ac"))
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
   stack.Add(VV)
   stack.Add(TT)
   stack.Add(Fake)
   stack.Add(DY)

   errorBand = DY.Clone()
   errorBand.Add(Fake)
   errorBand.Add(TT)
   errorBand.Add(VV)

   errorBand_scale1 = DY.Clone()
   errorBand_scale2 = DY.Clone()
   errorBand_scale3 = DY.Clone()
   errorBand_scale4 = DY.Clone()
   errorBand_scale5 = DY.Clone()
   errorBand_scale6 = DY.Clone()
   errorBand_ps1 = DY.Clone()
   errorBand_ps2 = DY.Clone()
   errorBand_ps3 = DY.Clone()
   errorBand_ps4 = DY.Clone()
   if i>5 and i<16:
     errorBand_scale1 = DY_scale1.Clone()
     errorBand_scale1.Add(Fake)
     errorBand_scale1.Add(TT)
     errorBand_scale1.Add(VV)
     errorBand_scale2 = DY_scale2.Clone()
     errorBand_scale2.Add(Fake)
     errorBand_scale2.Add(TT)
     errorBand_scale2.Add(VV)
     errorBand_scale3 = DY_scale3.Clone()
     errorBand_scale3.Add(Fake)
     errorBand_scale3.Add(TT)
     errorBand_scale3.Add(VV)
     errorBand_scale4 = DY_scale4.Clone()
     errorBand_scale4.Add(Fake)
     errorBand_scale4.Add(TT)
     errorBand_scale4.Add(VV)
     errorBand_scale5 = DY_scale5.Clone()
     errorBand_scale5.Add(Fake)
     errorBand_scale5.Add(TT)
     errorBand_scale5.Add(VV)
     errorBand_scale6 = DY_scale6.Clone()
     errorBand_scale6.Add(Fake)
     errorBand_scale6.Add(TT)
     errorBand_scale6.Add(VV)
     errorBand_ps1 = DY_ps1.Clone()
     errorBand_ps1.Add(Fake)
     errorBand_ps1.Add(TT)
     errorBand_ps1.Add(VV)
     errorBand_ps2 = DY_ps2.Clone()
     errorBand_ps2.Add(Fake)
     errorBand_ps2.Add(TT)
     errorBand_ps2.Add(VV)
     errorBand_ps3 = DY_ps3.Clone()
     errorBand_ps3.Add(Fake)
     errorBand_ps3.Add(TT)
     errorBand_ps3.Add(VV)
     errorBand_ps4 = DY_ps4.Clone()
     errorBand_ps4.Add(Fake)
     errorBand_ps4.Add(TT)
     errorBand_ps4.Add(VV)


   errorBand.SetMarkerSize(0)
   errorBand.SetFillColor(new_idx)
   errorBand.SetFillStyle(3001)
   errorBand.SetLineWidth(0)

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
   if "dz" in name[i]: pad1.SetLogy()
   pad1.SetLogx()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.65,errorBand.GetMaximum()*1.65))
   #Data.SetMinimum(0.1)
   if name[i]=="acoplanarity":
      Data.GetXaxis().SetLimits(0.001,1.0)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   legende=make_legend()
   legende.AddEntry(Data,"Observed","p")
   legende.AddEntry(DY,"Z/#gamma* #rightarrow #mu#mu (uncorrected)","f")
   #legende.AddEntry(TT,"TT","f")
   #legende.AddEntry(VV,"VV","f")
   #legende.AddEntry(Fake,"Fake","f")
   legende.AddEntry(errorBand,"Stat. uncertainty","f")
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
   #pad2.SetGridx()
   #pad2.SetGridy()
   pad2.SetLogx()
   pad2.Draw()
   pad2.cd()
   h1=Data.Clone()
   if i>5 and i<16:
     h1_scale1=Data.Clone()
     h1_scale1.Divide(errorBand_scale1)
     h1_scale2=Data.Clone()
     h1_scale2.Divide(errorBand_scale2)
     h1_scale3=Data.Clone()
     h1_scale3.Divide(errorBand_scale3)
     h1_scale4=Data.Clone()
     h1_scale4.Divide(errorBand_scale4)
     h1_scale5=Data.Clone()
     h1_scale5.Divide(errorBand_scale5)
     h1_scale6=Data.Clone()
     h1_scale6.Divide(errorBand_scale6)
     h1_ps1=Data.Clone()
     h1_ps1.Divide(errorBand_ps1)
     h1_ps2=Data.Clone()
     h1_ps2.Divide(errorBand_ps2)
     h1_ps3=Data.Clone()
     h1_ps3.Divide(errorBand_ps3)
     h1_ps4=Data.Clone()
     h1_ps4.Divide(errorBand_ps4)

   h1.SetMaximum(1.2)#FIXME(1.5)
   h1.SetMinimum(0.8)#FIXME(0.5)
   if "npvs" in name[i]:
     h1.SetMaximum(5.0)#FIXME(1.5)
     h1.SetMinimum(0.0)#FIXME(0.5)
   if "dz" in name[i]:
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
     if i>5 and i<16:
        total1 = ROOT.TF1( 'total1', 'pol8', 0, 0.4 )
        total1.SetLineColor( 3 )
        h1_scale1.Fit(total1,'R')
        total1.SetName("fit_"+name[i]+"_scale1")
        total2 = ROOT.TF1( 'total2', 'pol8', 0, 0.4 )
        total2.SetLineColor( ROOT.kMagenta )
        h1_scale2.Fit(total2,'R')
        total2.SetName("fit_"+name[i]+"_scale2")
        total3 = ROOT.TF1( 'total3', 'pol8', 0, 0.4 )
        total3.SetLineColor( ROOT.kTeal+1 )
        h1_scale3.Fit(total3,'R')
        total3.SetName("fit_"+name[i]+"_scale3")
        total4 = ROOT.TF1( 'total4', 'pol8', 0, 0.4 )
        total4.SetLineColor( ROOT.kOrange )
        h1_scale4.Fit(total4,'R')
        total4.SetName("fit_"+name[i]+"_scale4")
        total5 = ROOT.TF1( 'total5', 'pol8', 0, 0.4 )
        total5.SetLineColor( ROOT.kOrange-1 )
        h1_scale5.Fit(total5,'R')
        total5.SetName("fit_"+name[i]+"_scale5")
        total6 = ROOT.TF1( 'total6', 'pol8', 0, 0.4 )
        total6.SetLineColor( ROOT.kBlue )
        h1_scale1.Fit(total6,'R')
        total6.SetName("fit_"+name[i]+"_scale6")
        totalps1 = ROOT.TF1( 'totalps1', 'pol8', 0, 0.4 )
        totalps1.SetLineColor( ROOT.kViolet )
        totalps1.SetLineStyle(2)
        h1_ps1.Fit(totalps1,'R')
        totalps1.SetName("fit_"+name[i]+"_ps1")
        totalps2 = ROOT.TF1( 'totalps2', 'pol8', 0, 0.4 )
        totalps2.SetLineColor( ROOT.kRed+3 )
        totalps2.SetLineStyle(2)
        h1_ps2.Fit(totalps2,'R')
        totalps2.SetName("fit_"+name[i]+"_ps2")
        totalps3 = ROOT.TF1( 'totalps3', 'pol8', 0, 0.4 )
        totalps3.SetLineColor( ROOT.kTeal+9 )
        totalps3.SetLineStyle(2)
        h1_ps3.Fit(totalps3,'R')
        totalps3.SetName("fit_"+name[i]+"_ps3")
        totalps4 = ROOT.TF1( 'totalps4', 'pol8', 0, 0.4 )
        totalps4.SetLineColor( ROOT.kAzure-3 )
        totalps4.SetLineStyle(2)
        h1_ps4.Fit(totalps4,'R')
        totalps4.SetName("fit_"+name[i]+"_ps4")
        file_out.cd()
        total1.Write()
        total2.Write()
        total3.Write()
        total4.Write()
        total5.Write()
        total6.Write()
        totalps1.Write()
        totalps2.Write()
        totalps3.Write()
        totalps4.Write()

     total = ROOT.TF1( 'total', 'pol8', 0, 0.35 )
     total.SetLineColor( 2 ) #FIXME
     total.SetLineWidth( 2 )
     h1.Fit(total,'R') #FIXME
     total.SetName("fit_"+name[i])
     h1.Draw("e0psame")
     file_out.cd()
     total.Write()
     if i>5 and i<16:
       total1.Draw("same")
       total2.Draw("same")
       total3.Draw("same")
       total4.Draw("same")
       total5.Draw("same")
       total6.Draw("same")
       totalps1.Draw("same")
       totalps2.Draw("same")
       totalps3.Draw("same")
       totalps4.Draw("same")
       legende2=make_legend2()
       legende2.AddEntry(total,"Nominal","l")
       legende2.AddEntry(total1,"#mu_{R}=0.5, #mu_{f}=0.5","l")
       legende2.AddEntry(total2,"#mu_{R}=0.5, #mu_{f}=1.0","l")
       legende2.AddEntry(total3,"#mu_{R}=1.0, #mu_{f}=0.5","l")
       legende2.AddEntry(total4,"#mu_{R}=1.0, #mu_{f}=2.0","l")
       legende2.AddEntry(total5,"#mu_{R}=2.0, #mu_{f}=1.0","l")
       legende2.AddEntry(total6,"#mu_{R}=2.0, #mu_{f}=2.0","l")
       legende2.AddEntry(totalps1,"ISR up","l")
       legende2.AddEntry(totalps2,"FSR up","l")
       legende2.AddEntry(totalps3,"ISR down","l")
       legende2.AddEntry(totalps4,"FSR down","l")
       legende2.Draw("same")

     legf = ROOT.TLegend(0.48, 0.35, 0.9, 0.56, "", "brNDC")
     legf.SetNColumns(1)
     legf.SetLineWidth(0)
     legf.SetLineStyle(0)
     legf.SetFillStyle(0)
     legf.SetBorderSize(0)
     legf.SetTextFont(42)
     legf.AddEntry(total,"Polynomial fit","l")
     legf.Draw("same")

     kMyFaintRed = ROOT.TColor.GetColor(1.0,0.97,0.94)
     MyLightRed = ROOT.TColor.GetColor(1.0,0.86,0.90)
     
     xmin, xmax = 0.001, 0.015
     ymin, ymax = 0.8, 1.2
     vals = [(xmin,ymin),(xmax,ymin),(xmax,ymax),(xmin,ymax),(xmin,ymin)]
     graph = ROOT.TGraph()
     for ii, (x,y) in enumerate(vals):
       graph.SetPoint(ii,x,y)
     graph.SetFillColor(kMyFaintRed)
     graph.SetFillStyle(1001) # solid
     graph.Draw('F')
     
     latex = ROOT.TLatex()
     latex.SetTextFont(42)
     latex.SetTextAlign(13) # left-top align
     latex.SetTextColor(ROOT.kOrange+6)
     latex.SetTextSize(0.14)
     latex.DrawLatex(xmin+0.002,ymax-0.05,"SR")

     legf.Draw("same")
     h1.Draw("e0psame")

     pad2.RedrawAxis()

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

   h1.Draw("psame")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_mumu_"+args.year+"/control_corrected_"+name[i]+".pdf")
   c.SaveAs("plots_mumu_"+args.year+"/control_corrected_"+name[i]+".png")
   c.SaveAs("plots_mumu_"+args.year+"/control_corrected_"+name[i]+".C")
   c.SaveAs("plots_mumu_"+args.year+"/control_corrected_"+name[i]+".root")

