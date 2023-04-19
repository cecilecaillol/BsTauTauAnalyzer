#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

print("test")
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
        output = ROOT.TLegend(0.4, 0.6, 0.92, 0.86, "", "brNDC")
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
fileGGMM=ROOT.TFile("output_mumu_2018/GGMM.root","r")
file_out=ROOT.TFile("nhs_correction_2018.root","recreate")

if args.year=="2017":
  fileData=ROOT.TFile("output_mumu_2017/Data.root","r")
  fileDY=ROOT.TFile("output_mumu_2017/DY.root","r")

if args.year=="2016":
  fileData=ROOT.TFile("output_mumu_2016/Data.root","r")
  fileDY=ROOT.TFile("output_mumu_2016/DY.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

binNHS=[0,1,2,3,4,5,10,15,20,25,30,35]
binA=[0.0,0.02,1.0]

correction_map=ROOT.TH2F("correction_map","correction_map",11,array('d',binNHS),2,array('d',binA))

ncat=2

for i in range (0,ncat):
   Data=fileData.Get("h_ntracksAll"+str(i))
   DYHS=fileDY.Get("h_ntracksAll"+str(i))
   GGMMHS=fileGGMM.Get("h_ntracksAll"+str(i))
   Data.Add(GGMMHS,-2.6)
   #DYHS.Scale(0.10)

   DYHS0=fileDY.Get("h_ntracksAll_genHS0"+str(i))
   DYHS1=fileDY.Get("h_ntracksAll_genHS1"+str(i))
   DYHS2=fileDY.Get("h_ntracksAll_genHS2"+str(i))
   DYHS3=fileDY.Get("h_ntracksAll_genHS3"+str(i))
   DYHS4=fileDY.Get("h_ntracksAll_genHS4"+str(i))
   DYHS5=fileDY.Get("h_ntracksAll_genHS5to10"+str(i))
   DYHS6=fileDY.Get("h_ntracksAll_genHS10to15"+str(i))
   DYHS7=fileDY.Get("h_ntracksAll_genHS15to20"+str(i))
   DYHS8=fileDY.Get("h_ntracksAll_genHS20to25"+str(i))
   DYHS9=fileDY.Get("h_ntracksAll_genHS25to30"+str(i))
   DYHS10=fileDY.Get("h_ntracksAll_genHSgt30"+str(i))

   #DYHS0.Scale(0.10)
   #DYHS1.Scale(0.10)
   #DYHS2.Scale(0.10)
   #DYHS3.Scale(0.10)
   #DYHS4.Scale(0.10)
   #DYHS5.Scale(0.10)
   #DYHS6.Scale(0.10)
   #DYHS7.Scale(0.10)
   #DYHS8.Scale(0.10)
   #DYHS9.Scale(0.10)
   #DYHS10.Scale(0.10)

   print(Data.Integral(0,Data.GetSize()),DYHS.Integral(0,DYHS.GetSize()))
   totalDY=DYHS.Integral(0,DYHS.GetSize())
   DYHS.Scale(1.0/totalDY)
   DYHS0.Scale(1.0/totalDY)
   DYHS1.Scale(1.0/totalDY)
   DYHS2.Scale(1.0/totalDY)
   DYHS3.Scale(1.0/totalDY)
   DYHS4.Scale(1.0/totalDY)
   DYHS5.Scale(1.0/totalDY)
   DYHS6.Scale(1.0/totalDY)
   DYHS7.Scale(1.0/totalDY)
   DYHS8.Scale(1.0/totalDY)
   DYHS9.Scale(1.0/totalDY)
   DYHS10.Scale(1.0/totalDY)
   Data.Scale(1.0/Data.Integral(0,Data.GetSize()))

   SF0=Data.GetBinContent(1)/DYHS0.GetBinContent(1)
   DYHS0.Scale(SF0)
   SF1=(Data.GetBinContent(2)-DYHS0.GetBinContent(2))/DYHS1.GetBinContent(2)
   DYHS1.Scale(SF1)
   SF2=(Data.GetBinContent(3)-DYHS0.GetBinContent(3)-DYHS1.GetBinContent(3))/DYHS2.GetBinContent(3)
   DYHS2.Scale(SF2)
   SF3=(Data.GetBinContent(4)-DYHS0.GetBinContent(4)-DYHS1.GetBinContent(4)-DYHS2.GetBinContent(4))/DYHS3.GetBinContent(4)
   DYHS3.Scale(SF3)
   SF4=(Data.GetBinContent(5)-DYHS0.GetBinContent(5)-DYHS1.GetBinContent(5)-DYHS2.GetBinContent(5)-DYHS3.GetBinContent(5))/DYHS4.GetBinContent(5)
   DYHS4.Scale(SF4)

   SF5=(Data.Integral(5,10)-DYHS0.Integral(5,10)-DYHS1.Integral(5,10)-DYHS2.Integral(5,10)-DYHS3.Integral(5,10)-DYHS4.Integral(5,10))/DYHS5.Integral(5,10)
   DYHS5.Scale(SF5)
   SF6=(Data.Integral(10,15)-DYHS0.Integral(10,15)-DYHS1.Integral(10,15)-DYHS2.Integral(10,15)-DYHS3.Integral(10,15)-DYHS4.Integral(10,15)-DYHS5.Integral(10,15))/DYHS6.Integral(10,15)
   DYHS6.Scale(SF6)
   SF7=(Data.Integral(15,20)-DYHS0.Integral(15,20)-DYHS1.Integral(15,20)-DYHS2.Integral(15,20)-DYHS3.Integral(15,20)-DYHS4.Integral(15,20)-DYHS5.Integral(15,20)-DYHS6.Integral(15,20))/DYHS7.Integral(15,20)
   DYHS7.Scale(SF7)
   SF8=(Data.Integral(20,25)-DYHS0.Integral(20,25)-DYHS1.Integral(20,25)-DYHS2.Integral(20,25)-DYHS3.Integral(20,25)-DYHS4.Integral(20,25)-DYHS5.Integral(20,25)-DYHS6.Integral(20,25)-DYHS7.Integral(20,25))/DYHS8.Integral(20,25)
   DYHS8.Scale(SF8)
   SF9=(Data.Integral(25,30)-DYHS0.Integral(25,30)-DYHS1.Integral(25,30)-DYHS2.Integral(25,30)-DYHS3.Integral(25,30)-DYHS4.Integral(25,30)-DYHS5.Integral(25,30)-DYHS6.Integral(25,30)-DYHS7.Integral(25,30)-DYHS8.Integral(25,30))/DYHS9.Integral(25,30)
   DYHS9.Scale(SF9)
   SF10=(Data.Integral(30,31)-DYHS0.Integral(30,31)-DYHS1.Integral(30,31)-DYHS2.Integral(30,31)-DYHS3.Integral(30,31)-DYHS4.Integral(30,31)-DYHS5.Integral(30,31)-DYHS6.Integral(30,31)-DYHS7.Integral(30,31)-DYHS8.Integral(30,31)-DYHS9.Integral(30,31))/DYHS10.Integral(30,31)
   DYHS10.Scale(SF10)
   print(SF0,SF1,SF2,SF3,SF4,SF5,SF6,SF7,SF8,SF9,SF10)

   correction_map.SetBinContent(1,i+1,SF0)
   correction_map.SetBinContent(2,i+1,SF1)
   correction_map.SetBinContent(3,i+1,SF2)
   correction_map.SetBinContent(4,i+1,SF3)
   correction_map.SetBinContent(5,i+1,SF4)
   correction_map.SetBinContent(6,i+1,SF5)
   correction_map.SetBinContent(7,i+1,SF6)
   correction_map.SetBinContent(8,i+1,SF7)
   correction_map.SetBinContent(9,i+1,SF8)
   correction_map.SetBinContent(10,i+1,SF9)
   correction_map.SetBinContent(11,i+1,SF10)

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


   DYHS.SetLineColor(2)
   DYHS0.SetFillColor(ROOT.TColor.GetColor("#1e8a7a"))
   DYHS1.SetFillColor(ROOT.TColor.GetColor("#e78577"))
   DYHS2.SetFillColor(ROOT.TColor.GetColor("#a18273"))
   DYHS3.SetFillColor(ROOT.TColor.GetColor("#dd8a71"))
   DYHS4.SetFillColor(ROOT.TColor.GetColor("#bb8c7f"))
   DYHS5.SetFillColor(ROOT.TColor.GetColor("#51837e"))
   DYHS6.SetFillColor(ROOT.TColor.GetColor("#ca87c1"))
   DYHS7.SetFillColor(ROOT.TColor.GetColor("#c58e6b"))
   DYHS8.SetFillColor(ROOT.TColor.GetColor("#a4872f"))
   DYHS9.SetFillColor(ROOT.TColor.GetColor("#2f81e1"))
   DYHS10.SetFillColor(ROOT.TColor.GetColor("#bf11a1"))

   stack=ROOT.THStack("stack","stack")
   stack.Add(DYHS0)
   stack.Add(DYHS1)
   stack.Add(DYHS2)
   stack.Add(DYHS3)
   stack.Add(DYHS4)
   stack.Add(DYHS5)
   stack.Add(DYHS6)
   stack.Add(DYHS7)
   stack.Add(DYHS8)
   stack.Add(DYHS9)
   stack.Add(DYHS10)

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   Data.SetLineColor(1)
   Data.SetLineWidth(2)
   DYHS.SetLineWidth(4)

   DYscaled=DYHS0.Clone()
   DYscaled.Add(DYHS1)
   DYscaled.Add(DYHS2)
   DYscaled.Add(DYHS3)
   DYscaled.Add(DYHS4)
   DYscaled.Add(DYHS5)
   DYscaled.Add(DYHS6)
   DYscaled.Add(DYHS7)
   DYscaled.Add(DYHS8)
   DYscaled.Add(DYHS9)
   DYscaled.Add(DYHS10)

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

   #print(DY.Integral(),DYcorr.Integral(),Data.Integral())
   Data.GetXaxis().SetLabelSize(0)
   #Data.SetMaximum(max(DY.GetMaximum()*1.5,DY.GetMaximum()*1.5))
   Data.SetMaximum(10.0)
   Data.SetMinimum(0.00001)
   Data.Draw("e")
   DYHS.Draw("histsame")
   stack.Draw("histsame")
   DYHS.Draw("histsame")
   Data.Draw("esame")

   legende=make_legend2()
   legende.AddEntry(Data,"Observed","elp")
   legende.AddEntry(DYHS,"MC, no HS corr","l")
   legende.AddEntry(DYHS0,"MC N(reco HS) = 0")
   legende.AddEntry(DYHS1,"MC N(reco HS) = 1")
   legende.AddEntry(DYHS2,"MC N(reco HS) = 2")
   legende.AddEntry(DYHS3,"MC N(reco HS) = 3")
   legende.AddEntry(DYHS4,"MC N(reco HS) = 4")
   legende.AddEntry(DYHS5,"MC 5 #leq N(reco HS) < 10")
   legende.AddEntry(DYHS6,"MC 10 #leq N(reco HS) < 15")
   legende.AddEntry(DYHS7,"MC 15 #leq N(reco HS) < 20")
   legende.AddEntry(DYHS8,"MC 20 #leq N(reco HS) < 25")
   legende.AddEntry(DYHS9,"MC 25 #leq N(reco HS) < 30")
   legende.AddEntry(DYHS10,"MC N(reco HS) #geq 30")
   legende.Draw()

   l1=add_lumi(args.year)
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")
 
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
   h2=Data.Clone()
   h1.SetMaximum(1.5)#FIXME(1.5)
   h1.SetMinimum(0.0)#FIXME(0.5)
   #h1.SetMarkerStyle(20)
   h1.SetLineColor(ROOT.TColor.GetColor("#fe8a71"))
   h2.SetLineColor(ROOT.TColor.GetColor("#a1ca1c"))
   h3=DYHS.Clone()
   hwoE1=DYHS.Clone()
   hwoE2=DYscaled.Clone()
   for iii in range (1,hwoE1.GetSize()-1):
     hwoE1.SetBinError(iii,0)
     hwoE2.SetBinError(iii,0)
   h3.Sumw2()
   h1.Sumw2()
   h2.Sumw2()
   h1.SetStats(0)
   h1.Divide(hwoE1)
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
   c.SaveAs("plots_mumu_"+args.year+"/ntracksHS_"+str(i)+".pdf")
   c.SaveAs("plots_mumu_"+args.year+"/ntracksHS_"+str(i)+".png")

file_out.cd()
correction_map.Write()

c2=ROOT.TCanvas("canvas","",0,0,800,600)
c2.SetRightMargin(0.20)
correction_map.SetTitle("")
correction_map.GetXaxis().SetTitle("N_{HS tracks}")
correction_map.GetYaxis().SetTitle("Acoplanarity")
correction_map.GetZaxis().SetTitle("Weight")
correction_map.GetXaxis().SetTitleSize(0.05)
correction_map.GetYaxis().SetTitleSize(0.05)
correction_map.GetZaxis().SetTitleSize(0.05)
correction_map.GetXaxis().SetTitleOffset(0.8)
correction_map.Draw("colz")
c2.SaveAs("plots_mumu_"+args.year+"/correction_map_nhs.pdf")
c2.SaveAs("plots_mumu_"+args.year+"/correction_map_nhs.png")

