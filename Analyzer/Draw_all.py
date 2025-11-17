#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

ROOT.gROOT.SetBatch(True)

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
    if (year=="2024"): lumi.AddText("2024, 109 fb^{-1} (13.6 TeV)")
    if (year=="2018"): lumi.AddText("2018, 60 fb^{-1} (13 TeV)")
    if (year=="2017"): lumi.AddText("2017, 41 fb^{-1} (13 TeV)")
    if (year=="2016"): lumi.AddText("2016, 36 fb^{-1} (13 TeV)")
    if (year=="2016pre"): lumi.AddText("2016 preVFP, 19 fb^{-1} (13 TeV)")
    if (year=="2016post"): lumi.AddText("2016 postVFP, 16 fb^{-1} (13 TeV)")
    if (year=="Run2"): lumi.AddText("Run-2, 138 fb^{-1} (13 TeV)")
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
        output = ROOT.TLegend(0.5, 0.5, 0.92, 0.86, "", "brNDC")
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
parser.add_argument('--channel', '-c', default=None, help='Output name')
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetLogy()

file=ROOT.TFile("datacard_"+args.channel+args.year+".root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["em_0","em_1","em_2","em_3","em_4","em_5","em_6","em_7","em_8"]
name=["mvis","ept","mupt","eeta","mueta","met","mt_emet","mt_mumet","njets"]
title=["m_{vis} (GeV)","e p_{T} (GeV)","#mu p_{T} (GeV)","e #eta","#mu #eta","MET","m_{T}(e, MET) (GeV)","m_{T}(#mu, MET) (GeV)","N(jets)"]
ncat=9

if args.channel=="mumu":
    name=["mvis","mu1pt","mu2pt","mu1eta","mu2eta","met","mt_mu1met","mt_mu2met","njets"]
    title=["m_{vis} (GeV)","Leading #mu p_{T} (GeV)","Subleading #mu p_{T} (GeV)","Leading #mu #eta","Subleading #mu #eta","MET","m_{T}(#mu1, MET) (GeV)","m_{T}(#mu2, MET) (GeV)","N(jets)"]

if args.channel=="ee":
    name=["mvis","e1pt","e2pt","e1eta","e2eta","met","mt_e1met","mt_e2met","njets"]
    title=["m_{vis} (GeV)","Leading e p_{T} (GeV)","Subleading e p_{T} (GeV)","Leading e #eta","Subleading e #eta","MET","m_{T}(e1, MET) (GeV)","m_{T}(e2, MET) (GeV)","N(jets)"]

if args.channel=="e":
    name=["ept","eeta","met","mt_emet","dphi_emet","dummy1","dummy2","nb","njets"]
    title=["e p_{T} (GeV)","e #eta","MET","m_{T}(e, MET) (GeV)","|#Delta#phi(e, MET)|","","","N(b jets)","N(jets)"]

if args.channel=="mu":
    name=["mupt","mueta","met","mt_emet","dphi_mumet","dummy1","dummy2","nb","njets"]
    title=["#mu p_{T} (GeV)","#mu #eta","MET","m_{T}(#mu, MET) (GeV)","|#Delta#phi(#mu, MET)|","","","N(b jets)","N(jets)"]

for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs")
   TTTo2L2Nu=file.Get(categories[i]).Get("TTto2L2Nu")
   TTToSemiLeptonic=file.Get(categories[i]).Get("TTtoLNu2Q")
   ST=file.Get(categories[i]).Get("singletop")
   DY=file.Get(categories[i]).Get("DY")
   VV=file.Get(categories[i]).Get("VV")
   W=file.Get(categories[i]).Get("W")

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

   TTTo2L2Nu.SetFillColor(ROOT.TColor.GetColor("#5790fc"))
   TTToSemiLeptonic.SetFillColor(ROOT.TColor.GetColor("#f89c20"))
   DY.SetFillColor(ROOT.TColor.GetColor("#e42536"))
   ST.SetFillColor(ROOT.TColor.GetColor("#964a8b"))
   VV.SetFillColor(ROOT.TColor.GetColor("#9c9ca1"))
   W.SetFillColor(ROOT.TColor.GetColor("#7a21dd"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   TTTo2L2Nu.SetLineColor(1)
   TTToSemiLeptonic.SetLineColor(1)
   DY.SetLineColor(1)
   ST.SetLineColor(1)
   VV.SetLineColor(1)
   W.SetLineColor(1)

   stack=ROOT.THStack("stack","stack")
   stack.Add(ST)
   stack.Add(VV)
   stack.Add(TTTo2L2Nu)
   stack.Add(TTToSemiLeptonic)
   stack.Add(DY)
   stack.Add(W)

   errorBand = ST.Clone()
   errorBand.Add(TTTo2L2Nu)
   errorBand.Add(DY)
   errorBand.Add(VV)
   errorBand.Add(TTToSemiLeptonic)
   errorBand.Add(W)

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

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
   Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   legende=make_legend()
   if "inverted" in name[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(TTTo2L2Nu,"t#bar{t} lep","f")
   legende.AddEntry(TTToSemiLeptonic,"t#bar{t} semi-lep","f")
   legende.AddEntry(DY,"DY","f")
   legende.AddEntry(ST,"Single top","f")
   legende.AddEntry(VV,"Diboson","f")
   legende.AddEntry(W,"W+jets","f")
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
   h1.SetMaximum(1.3)
   h1.SetMinimum(0.7)
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

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_"+args.channel+"_"+args.year+"/"+name[i]+".pdf")
   c.SaveAs("plots_"+args.channel+"_"+args.year+"/"+name[i]+".png")

