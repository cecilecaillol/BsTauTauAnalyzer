#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array

is_datadriven=1

def add_lumi():
    lowX=0.63
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.07)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{#minus1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.17
    lowY=0.83
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
    lowX=0.28
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def add_Supplementary():
    lowX=0.28
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Supplementary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.2, 0.65, 0.88, 0.86, "", "brNDC")
        output.SetNColumns(3)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        return output

def make_legend2():
        output = ROOT.TLegend(0.45, 0.6, 0.92, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        return output

ROOT.gStyle.SetOptStat(0)

parser = argparse.ArgumentParser()
parser.add_argument('--year', '-y', default=None, help='Output name')
args = parser.parse_args()


c=ROOT.TCanvas("canvas","",0,0,800,800)
c.cd()
c.SetLogy()

#file=ROOT.TFile("postfit_control.root","r")
file=ROOT.TFile("finalfit_postfit_control.root","r")
filehep=ROOT.TFile("hepdata_fig11.root","recreate")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

categories=["em_nt_highmvis_postfit","et_nt_highmvis_postfit","mt_nt_highmvis_postfit","tt_nt_highmvis_postfit"]

Data=file.Get(categories[0]).Get("data_obs")
VV=file.Get(categories[0]).Get("VV")
ZTT=file.Get(categories[0]).Get("ZTT")
ZLL=ZTT.Clone()
ZLL.SetName("ZLL")
ZLL.Scale(0.0)
#if ("et" in categories[i] or "mt" in categories[i]): ZLL=file.Get(categories[i]).Get("ZLL")
GGTT=file.Get(categories[0]).Get("GGTT")
excl=file.Get(categories[0]).Get("GGWW")
#if ("et" in categories[0]): 
#  GGEE=file.Get(categories[0]).Get("GGEE")
#  excl.Add(GGEE)
#if ("mt" in categories[0]):
#  GGMM=file.Get(categories[0]).Get("GGMM")
#  excl.Add(GGMM)
Fake=file.Get(categories[0]).Get("Fake")
TT=Fake.Clone()
TT=file.Get(categories[0]).Get("top")
VV.Add(TT)
Total=file.Get(categories[0]).Get("TotalProcs")
Bkg=file.Get(categories[0]).Get("TotalBkg")

for i in range (1,4):
   for k in range(1, Data.GetSize()):
      Data.SetBinContent(k,Data.GetBinContent(k)+file.Get(categories[i]).Get("data_obs").GetBinContent(k))

      if k<3:
        VV.SetBinContent(k,VV.GetBinContent(k)+file.Get(categories[i]).Get("VV").GetBinContent(k))

      ZTT.SetBinContent(k,ZTT.GetBinContent(k)+file.Get(categories[i]).Get("ZTT").GetBinContent(k))

      GGTT.SetBinContent(k,GGTT.GetBinContent(k)+file.Get(categories[i]).Get("GGTT").GetBinContent(k))

      Fake.SetBinContent(k,Fake.GetBinContent(k)+file.Get(categories[i]).Get("Fake").GetBinContent(k))

      if i<3:
         ZLL.SetBinContent(k,ZLL.GetBinContent(k)+file.Get(categories[i]).Get("ZLL").GetBinContent(k))

      if i==2:
         excl.SetBinContent(k,excl.GetBinContent(k)+file.Get(categories[i]).Get("GGMM").GetBinContent(k))

      if i==1:
         excl.SetBinContent(k,excl.GetBinContent(k)+file.Get(categories[i]).Get("GGEE").GetBinContent(k))

      if i<3: 
         excl.SetBinContent(k,excl.GetBinContent(k)+file.Get(categories[i]).Get("GGWW").GetBinContent(k))

      Total.SetBinContent(k,Total.GetBinContent(k)+file.Get(categories[i]).Get("TotalProcs").GetBinContent(k))
      #Total.SetBinError(k,Total.GetBinError(k)+file.Get(categories[i]).Get("TotalProcs").GetBinError(k))
      Total.SetBinError(k,(Total.GetBinError(k)*Total.GetBinError(k)+file.Get(categories[i]).Get("TotalProcs").GetBinError(k)*file.Get(categories[i]).Get("TotalProcs").GetBinError(k))**0.5)

      Bkg.SetBinContent(k,Bkg.GetBinContent(k)+file.Get(categories[i]).Get("TotalBkg").GetBinContent(k))
      #Bkg.SetBinError(k,Bkg.GetBinError(k)+file.Get(categories[i]).Get("TotalBkg").GetBinError(k))
      Bkg.SetBinError(k,(Bkg.GetBinError(k)*Bkg.GetBinError(k)+file.Get(categories[i]).Get("TotalBkg").GetBinError(k)*file.Get(categories[i]).Get("TotalBkg").GetBinError(k))**0.5)

for k in range(1, Data.GetSize()):
   Data.SetBinError(k,(Data.GetBinContent(k))**0.5)

Data.GetXaxis().SetTitle("")
Data.GetXaxis().SetTitleSize(0)
Data.GetXaxis().SetNdivisions(10)
Data.GetYaxis().SetLabelFont(42)
Data.GetYaxis().SetLabelOffset(0.01)
Data.GetYaxis().SetLabelSize(0.06)
Data.GetYaxis().SetTitleSize(0.08)
Data.GetYaxis().SetTitleOffset(1.1)
Data.SetTitle("")
Data.GetYaxis().SetTitle("Events")
Data.SetMinimum(0.1)
if "aco" in categories[i]: Data.GetXaxis().SetRangeUser(0.001,1.0)


##blind
#if "nt" in categories[i] and "high" in categories[i]:
#   for k in range(1,4):
#       Data.SetBinContent(k,0.0)
#else:
#   for k in range(1,Data.GetSize()):
#       Data.SetBinContent(k,0.0)

ZLL.SetFillColor(ROOT.TColor.GetColor("#f9b5ac"))
ZTT.SetFillColor(ROOT.TColor.GetColor("#9dbf9e"))
excl.SetFillColor(ROOT.TColor.GetColor("#d0d6b5"))
Fake.SetFillColor(ROOT.TColor.GetColor("#987284"))
VV.SetFillColor(ROOT.TColor.GetColor("#4a4e4d"))
TT.SetLineColor(1)
VV.SetLineColor(1)
#GGWW.SetFillColor(ROOT.TColor.GetColor("#4de321"))

Data.SetMarkerStyle(20)
Data.SetMarkerSize(1)
ZTT.SetLineColor(1)
ZLL.SetLineColor(1)
excl.SetLineColor(1)
Fake.SetLineColor(1)
Data.SetLineColor(1)
Data.SetLineWidth(2)

GGTT.SetLineColor(2)
GGTT.SetLineWidth(3)
GGTTfull=GGTT.Clone()
GGTTfull.SetFillColor(ROOT.TColor.GetColor("#ee7674"))
GGTTfull.SetLineColor(1)
GGTTfull.SetLineWidth(1)


stack=ROOT.THStack("stack","stack")
#stack.Add(Fake)
#stack.Add(VV)
#if ("et" in categories[i] or "mt" in categories[i]): stack.Add(ZLL)
#stack.Add(ZTT)
#stack.Add(GGTTfull)

#stack.Add(GGTTfull)
stack.Add(VV)
#stack.Add(ZTT)
stack.Add(excl)
stack.Add(Fake)
stack.Add(ZLL)
stack.Add(ZTT)
stack.Add(GGTTfull)

errorBand = Total.Clone()

errorBand.SetMarkerSize(0)
errorBand.SetFillColor(new_idx)
errorBand.SetFillStyle(3001)
errorBand.SetLineWidth(1)
errorBand.SetLineColor(1)

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
#if "aco" in categories[i]: pad1.SetLogx()
#else: pad1.SetLogx(0)
#if "aco" in categories[i]: pad1.DrawFrame(0.001,0.0,1.0,max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))

Data.GetXaxis().SetLabelSize(0)
Data.SetMaximum(max(Data.GetMaximum()*1.5,errorBand.GetMaximum()*1.5))
Data.SetMinimum(0.1)
ex2 = ROOT.TExec("ex2","gStyle->SetErrorX(0);");
ex2.Draw()
Data.Draw("ep0")
ex1 = ROOT.TExec("ex1","gStyle->SetErrorX(0.5);");
ex1.Draw()
stack.Draw("histsame")
errorBand.Draw("e2same")
ex2.Draw()
Data.Draw("ep0same")

#if args.year=="2018": GGTT.Draw("histsame")

legende=make_legend()
legende.AddEntry(Data,"Observed ","elp")
legende.AddEntry(ZTT,"Z/#gamma* #rightarrow #tau#tau","f")
legende.AddEntry(ZLL, "Z/#gamma* #rightarrow ee/#mu#mu","f")
legende.AddEntry(excl,"Excl. bkg. ","f")
legende.AddEntry(VV, "VV + t#bar{t}","f")
#legende.AddEntry(GGWW,"#gamma#gamma#rightarrow WW","f")
legende.AddEntry(Fake,"Jet mis-ID","f")
legende.AddEntry(GGTTfull,"#gamma#gamma #rightarrow #tau#tau","f")
legende.AddEntry(errorBand,"Uncertainty","f")
legende.Draw()

l1=add_lumi()
l1.Draw("same")
l2=add_CMS()
l2.Draw("same")
l4=add_Supplementary()
#l4.Draw("same")
l3=add_Preliminary()
#l3.Draw("same")

lowX=0.45
lowY=0.835
lumi1  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
lumi1.SetBorderSize(   0 )
lumi1.SetFillStyle(    0 )
lumi1.SetTextAlign(   12 )
lumi1.SetTextColor(    1 )
lumi1.SetTextSize(0.05)
lumi1.SetTextFont (   42 )
lumi1.AddText("m_{#lower[-0.25]{vis}} > 100 GeV")
#lumi1.Draw("same")

pad1.RedrawAxis()

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
#if "aco" in categories[i]: pad2.SetLogx()
#else: pad2.SetLogx(0)

pad2.Draw()
pad2.cd()
h1=Data.Clone()
h1.SetMaximum(1.2)
h1.SetMinimum(0.8)
if "aco" in categories[i]: 
  h1.SetMaximum(2.0)
  h1.SetMinimum(0.0)
if "low" in categories[i]:
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
h1.GetXaxis().SetTitle("#it{N}_{#lower[-0.25]{tracks}}")
h1.GetXaxis().SetLabelSize(0.08)
h1.GetYaxis().SetLabelSize(0.08)
h1.GetYaxis().SetTitle("Obs./Exp.")
h1.GetXaxis().SetNdivisions(10)
h1.GetYaxis().SetNdivisions(5)
h1.GetXaxis().SetTitleSize(0.15)
h1.GetYaxis().SetTitleSize(0.12)
h1.GetXaxis().SetLabelSize(0.2)
h1.GetYaxis().SetLabelSize(0.1)
h1.GetXaxis().SetTitleOffset(0.8)
h1.GetYaxis().SetTitleOffset(0.5)
h1.GetXaxis().SetLabelOffset(0.015)

for i in range(1,h1.GetSize()):
  h1.GetXaxis().SetBinLabel(i,str(i-1))


h1.GetXaxis().SetTitleSize(0.15)
h1.GetYaxis().SetTitleSize(0.15)
h1.GetYaxis().SetTitleOffset(0.56)
h1.GetXaxis().SetTitleOffset(1.04)
h1.GetXaxis().SetLabelSize(0.15)
h1.GetYaxis().SetLabelSize(0.11)
h1.GetXaxis().SetTitleFont(42)
h1.GetYaxis().SetTitleFont(42)

h1.Draw("e0p")
ex3 = ROOT.TExec("ex3","gStyle->SetErrorX(0.5);");
ex3.Draw()
h3.Draw("e2same")
ex2.Draw()
h1.Draw("ep0same")

c.cd()
pad1.Draw()


pad3 = ROOT.TPad("pad3","pad3",0.19,0.55,0.55,0.77);
#pad3.SetTopMargin(0.05);
pad3.SetBottomMargin(0.17);
pad3.SetLeftMargin(0.18);
#pad3.SetRightMargin(0.05);
pad3.SetTickx(1)
pad3.SetTicky(1)
pad3.Draw()
pad3.cd()

subData=Data.Clone()
subBkg=Bkg.Clone()
hepBkg=Bkg.Clone()
for k in range(1,Bkg.GetSize()):
  Bkg.SetBinError(k,0)
subData.Add(Bkg,-1)
subData.GetXaxis().SetTitle("#it{N}_{#lower[-0.25]{tracks}}")
subData.GetYaxis().SetTitle("Events #minus Bkg.")
subData.GetXaxis().SetTitleSize(0.12)
subData.GetYaxis().SetTitleSize(0.12)
subData.GetXaxis().SetLabelSize(0.1)
subData.GetYaxis().SetLabelSize(0.07)
subData.GetXaxis().SetTitleOffset(0.6)
subData.GetYaxis().SetTitleOffset(0.5)
#subData.GetXaxis().SetTitleSize(0.15)
#subData.GetYaxis().SetTitleSize(0.12)
#subData.GetXaxis().SetLabelSize(0.15)
#subData.GetYaxis().SetLabelSize(0.1)
#subData.GetXaxis().SetTitleOffset(0.8)
#subData.GetYaxis().SetTitleOffset(0.5)
#subData.GetXaxis().SetLabelOffset(0.015)

for i in range(1,subData.GetSize()):
  subData.GetXaxis().SetBinLabel(i,str(i-1))

subData.SetMinimum(-40)
subData.GetYaxis().SetNdivisions(505)
subData.Draw("e0")
subSig=GGTT.Clone()
subSig.SetLineWidth(3)
subSig.Draw("histsame")
subBkg.Add(Bkg,-1)
subBkg.SetMarkerSize(0)
subBkg.SetFillColor(new_idx)
subBkg.SetFillStyle(3001)
subBkg.SetLineWidth(1)
subBkg.SetLineColor(1)
ex3.Draw()
subBkg.Draw("e2same")
ex2.Draw()
subData.Draw("e0same")

leg1 = ROOT.TLegend(0.29, 0.55, 0.77, 0.86, "", "brNDC")
leg1.SetNColumns(1)
leg1.SetLineWidth(0)
leg1.SetLineStyle(0)
leg1.SetFillStyle(0)
leg1.SetBorderSize(0)
leg1.SetTextFont(42)
leg1.AddEntry(subBkg,"Bkg. unc.", "f")
leg1.AddEntry(subSig,"#gamma#gamma#rightarrow#tau#tau", "l")
leg1.AddEntry(subData,"Obs. #minus bkg.", "elp")
leg1.Draw("same")

#pad3.Draw()




ROOT.gPad.RedrawAxis()

c.Modified()
c.SaveAs("plots_control_postfit/sum_ntracks_postfit.pdf")
c.SaveAs("plots_control_postfit/sum_ntracks_postfit.png")

c.SaveAs("Figure_010.pdf")
c.SaveAs("Figure_010.png")
c.SaveAs("Figure_010.root")

filehep.cd()
mydir=filehep.mkdir("all")
mydir.cd()
hepBkg.Write()
GGTT.SetName("TotalSig")
GGTT.Write()
VV.Write()
excl.SetName("excl")
excl.Write()
ZTT.Write()
ZLL.Write()
Fake.Write()
Data.Write()

