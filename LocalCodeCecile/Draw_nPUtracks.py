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
        output = ROOT.TLegend(0.5, 0.6, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(1)
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

fileData=ROOT.TFile("output_mumu_2018/Data.root","r")
fileDY=ROOT.TFile("output_mumu_2018/DY.root","r")
file_out=ROOT.TFile("npu_correction_2018.root","recreate")

if args.year=="2017":
  fileData=ROOT.TFile("output_mumu_2017/Data.root","r")
  fileDY=ROOT.TFile("output_mumu_2017/DY.root","r")

if args.year=="2016":
  fileData=ROOT.TFile("output_mumu_2016/Data.root","r")
  fileDY=ROOT.TFile("output_mumu_2016/DY.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

correction_map=ROOT.TH2F("correction_map","correction_map",51,0,51,200,-10,10)

ncat=200

for i in range (0,ncat):
   print("h_ntracks0p1"+str(i))
   Data=fileData.Get("h_ntracks0p1"+str(i))
   DY=fileDY.Get("h_ntracks0p1"+str(i))
   DYcorr=fileDY.Get("h_ntracks0p1_corrected"+str(i))
   
   #DY.Scale(25883043.0/100000)
   #DYcorr.Scale(25883043.0/100000)

   DY.Scale(1.0/DY.Integral())
   DYcorr.Scale(1.0/DYcorr.Integral())
   Data.Scale(1.0/Data.Integral())

   for k in range(0,51):
     correction_map.SetBinContent(k+1,i+1,Data.GetBinContent(k+1)/DYcorr.GetBinContent(k+1))

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.075)
   Data.GetYaxis().SetTitleOffset(1.04)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Probability density")
   Data.SetMinimum(0.1)


   DY.SetLineColor(ROOT.TColor.GetColor("#fe8a71"))
   DYcorr.SetLineColor(ROOT.TColor.GetColor("#a1ca1c"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
   DY.SetLineWidth(2)
   DYcorr.SetLineWidth(2)

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
   #pad1.SetLogx()

   Data.GetXaxis().SetLimits(0.9, 200)
   print(DY.Integral(),DYcorr.Integral(),Data.Integral())
   Data.GetXaxis().SetLabelSize(0)
   #Data.SetMaximum(max(DY.GetMaximum()*1.5,DY.GetMaximum()*1.5))
   Data.SetMaximum(10.0)
   Data.SetMinimum(0.00001)
   Data.Draw("e")
   DY.Draw("histsame")
   DYcorr.Draw("histsame")
   Data.Draw("esame")

   legende=make_legend()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DY,"Z#rightarrow #mu#mu","l")
   legende.AddEntry(DYcorr,"Z#rightarrow #mu#mu (BS corr.)","l")
   legende.Draw()

   l1=add_lumi(args.year)
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
 
   #pad1.SetLogx()
   pad1.RedrawAxis()

   categ  = ROOT.TPaveText(0.45, 0.45+0.013, 0.83, 0.45+0.155, "NDC")
   categ.SetBorderSize(   0 )
   categ.SetFillStyle(    0 )
   categ.SetTextAlign(   12 )
   categ.SetTextSize ( 0.06 )
   categ.SetTextColor(    1 )
   categ.SetTextFont (   42 )
   #categ.AddText(str(-10+i*0.2)+" < z < "+str(-10+(i+1)*0.2)+" cm")
   categ.AddText("%.1f < z < %.1f cm"%((-10+i*0.1),(-10+(i+1)*0.1)))
   categ.Draw("same")

   c.cd()
   pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
   #pad2.SetLogx()
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
   h2=Data.Clone()
   h1.SetMaximum(1.5)#FIXME(1.5)
   h1.SetMinimum(0.5)#FIXME(0.5)
   #h1.SetMarkerStyle(20)
   h1.SetLineColor(ROOT.TColor.GetColor("#fe8a71"))
   h2.SetLineColor(ROOT.TColor.GetColor("#a1ca1c"))
   h3=DY.Clone()
   hwoE1=DY.Clone()
   for iii in range (1,hwoE1.GetSize()-1):
     hwoE1.SetBinError(iii,0)
   hwoE2=DYcorr.Clone()
   for iii in range (1,hwoE2.GetSize()-1):
     hwoE2.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h2.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE1)
   h3.Divide(hwoE1)
   h2.Divide(hwoE2)
   h1.GetXaxis().SetTitle("N_{tracks}")
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

   h1.Draw("hist")
   h2.Draw("histsame")
   #h3.Draw("e2same")

   c.cd()
   pad1.Draw()

   ROOT.gPad.RedrawAxis()

   c.Modified()
   c.SaveAs("plots_mumu_"+args.year+"/ntracks0p1_"+str(i)+".pdf")
   c.SaveAs("plots_mumu_"+args.year+"/ntracks0p1_"+str(i)+".png")

file_out.cd()
correction_map.Write()

c2=ROOT.TCanvas("canvas","",0,0,800,600)
c2.SetRightMargin(0.20)
correction_map.SetTitle("")
correction_map.GetXaxis().SetTitle("N_{PU tracks}")
correction_map.GetYaxis().SetTitle("z")
correction_map.GetZaxis().SetTitle("Weight")
correction_map.GetXaxis().SetTitleSize(0.05)
correction_map.GetYaxis().SetTitleSize(0.05)
correction_map.GetZaxis().SetTitleSize(0.05)
correction_map.GetXaxis().SetTitleOffset(0.8)
correction_map.Draw("colz")
c2.SaveAs("plots_mumu_"+args.year+"/correction_map_npu.pdf")
c2.SaveAs("plots_mumu_"+args.year+"/correction_map_npu.png")

