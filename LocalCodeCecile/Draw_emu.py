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

file=ROOT.TFile("datacard_emu_2018.root","r")
if args.year=="2017":
   file=ROOT.TFile("datacard_emu_2017.root","r")

if args.year=="2016":
   file=ROOT.TFile("datacard_emu_2016.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["em_0","em_1","em_2","em_3","em_4","em_5","em_6","em_7","em_8"]
name=["mvis","e_pt","mu_pt","e_eta","mu_eta","met","emu_pt","njets","acoplanarity"]
title=["m_{vis} (GeV)","e p_{T} (GeV)","#mu p_{T} (GeV)","e #eta","#mu #eta","MET (GeV)","p_{T}(e,#mu) (GeV)","N_{jets}","acoplanarity"]
ncat=9

#categories=["em_0","em_1","em_2","em_3"]
#name=["mvis_nt0","mvis_nt1","ptemu_nt0","ptemu_nt1"]
#title=["m_{vis} (GeV)","m_{vis} (GeV)","p_{T}(e#mu) (GeV)","p_{T}(e#mu) (GeV)"]
#ncat=4

for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs")
   #W=file.Get(categories[i]).Get("W")
   TT=file.Get(categories[i]).Get("TT")
   VV=file.Get(categories[i]).Get("VV")
   ZTT=file.Get(categories[i]).Get("ZTT")
   ST=file.Get(categories[i]).Get("ST")
   if args.year=="2018": GGTT=file.Get(categories[i]).Get("GGTT")
   if args.year=="2018": GGWW=file.Get(categories[i]).Get("GGWW")
   VV.Add(ST.Clone())
   #VV.Add(W.Clone())
   Fake=file.Get(categories[i]).Get("Fake")
   #Fake.Scale(0.8)
   #Fake.Scale(0.5)
   
   if args.year=="2018": GGTT.Scale(10)
   if args.year=="2018": GGWW.Scale(3.6)

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


   if "mvis_nt" in name[i]: # blind
      for k in range(1,Data.GetSize()):
         Data.SetBinContent(k,0.0)

   TT.SetFillColor(ROOT.TColor.GetColor("#4a4e4d"))
   ZTT.SetFillColor(ROOT.TColor.GetColor("#f6cd61"))
   VV.SetFillColor(ROOT.TColor.GetColor("#ff8c94"))
   Fake.SetFillColor(ROOT.TColor.GetColor("#3da4ab"))
   if args.year=="2018": GGWW.SetFillColor(ROOT.kGreen+1)

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   TT.SetLineColor(1)
   ZTT.SetLineColor(1)
   VV.SetLineColor(1)
   Fake.SetLineColor(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)

   if args.year=="2018": GGTT.SetLineColor(2)
   if args.year=="2018": GGTT.SetLineWidth(3)

   stack=ROOT.THStack("stack","stack")
   stack.Add(TT)
   stack.Add(Fake)
   stack.Add(VV)
   if args.year=="2018": stack.Add(GGWW)
   stack.Add(ZTT)

   errorBand = ZTT.Clone()
   errorBand.Add(TT)
   errorBand.Add(VV)
   if args.year=="2018": errorBand.Add(GGWW)
   errorBand.Add(Fake)

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
   if "mvis_nt" in name[i]:
     pad1.SetLogy()

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
   Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   if args.year=="2018": GGTT.Draw("histsame")

   legende=make_legend()
   if "inverted" in name[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(ZTT,"Z#rightarrow #tau#tau","f")
   #legende.AddEntry(ZLL,"Z#rightarrow ee","f")
   legende.AddEntry(TT,"t#bar{t}","f")
   legende.AddEntry(VV,"VV,single-t, W","f")
   if args.year=="2018": legende.AddEntry(GGWW,"#gamma#gamma#rightarrow WW","f")
   legende.AddEntry(Fake,"Fake","f")
   if args.year=="2018": legende.AddEntry(GGTT,"Signal x 10","l")
   legende.AddEntry(errorBand,"Uncertainty","f")
   legende.Draw()

   l1=add_lumi(args.year)
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
 
   pad1.RedrawAxis()

   if args.year=="2018": 
     S = GGTT.Integral()/10
     B =  Fake.Integral()
     SoB = S/B
     SosB = S/B**0.5

     categ  = ROOT.TPaveText(0.45, 0.5+0.013, 0.83, 0.50+0.155, "NDC")
     categ.SetBorderSize(   0 )
     categ.SetFillStyle(    0 )
     categ.SetTextAlign(   12 )
     categ.SetTextSize ( 0.04 )
     categ.SetTextColor(    1 )
     categ.SetTextFont (   42 )
     categ.AddText("S = %.2f, B = %.1f, S/B = %.2f, S/sqrt(B) = %.2f" %(S,B,SoB,SosB))
     #categ.AddText("S = %.2f, B = %.1f"%(GGTT.Integral()/30, Fake.Integral()))
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

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_emu_"+args.year+"/control_"+name[i]+".pdf")
   c.SaveAs("plots_emu_"+args.year+"/control_"+name[i]+".png")

