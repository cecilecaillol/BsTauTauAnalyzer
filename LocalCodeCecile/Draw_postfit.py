#!/usr/bin/env python
import ROOT
import re
import argparse
from array import array
import ctypes

is_datadriven=1

def add_lumi():
    lowX=0.63
    lowY=0.83
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
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(62)
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.6
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
    lumi.AddText("")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.36, 0.45, 0.9, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

def make_legend2():
        output = ROOT.TLegend(0.53, 0.5, 0.9, 0.86, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

def make_legend3():
        output = ROOT.TLegend(0.55, 0.3, 0.9, 0.6, "", "brNDC")
        output.SetNColumns(2)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        return output

def make_legend31():
        output = ROOT.TLegend(0.3, 0.3, 0.65, 0.6, "", "brNDC")
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

file=ROOT.TFile("postfit.root","r")
files=ROOT.TFile("signal_all.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

#categories=["em_em_nt0_postfit","em_em_nt1_postfit","et_et_nt0_postfit","et_et_nt1_postfit","mt_mt_nt0_postfit","mt_mt_nt1_postfit","tt_tt_nt0_postfit","tt_tt_nt1_postfit"]
#name=["emu_nt0_postfit","emu_nt1_postfit","etau_nt0_postfit","etau_nt1_postfit","mutau_nt0_postfit","mutau_nt1_postfit","tautau_nt0_postfit","tautau_nt1_postfit"]
categories_pre=["em_em_nt0_postfit","em_em_nt1_postfit","et_et_nt0_postfit","et_et_nt1_postfit","mt_mt_nt0_postfit","mt_mt_nt1_postfit","tt_tt_nt0_postfit","tt_tt_nt1_postfit"]
categories=["em_em_nt0_postfit","em_em_nt1_postfit","et_et_nt0_postfit","et_et_nt1_postfit","mt_mt_nt0_postfit","mt_mt_nt1_postfit","tt_tt_nt0_postfit","tt_tt_nt1_postfit"]
name=["emu_nt0_postfit","emu_nt1_postfit","etau_nt0_postfit","etau_nt1_postfit","mutau_nt0_postfit","mutau_nt1_postfit","tautau_nt0_postfit","tautau_nt1_postfit"]
title=["m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)","m_{#lower[-0.15]{vis}} (GeV)"]
ncat=8

for i in range (0,ncat):
   Data=file.Get(categories[i]).Get("data_obs")
   VV=file.Get(categories[i]).Get("VV")
   ZTT=file.Get(categories[i]).Get("ZTT")
   BSM=ZTT.Clone()
   BSM0=ZTT.Clone()
   if (categories[i]=="em_em_nt0_postfit"): 
        BSM=files.Get("em_0").Get("GGTT_8p0")
        BSM0=files.Get("em_0").Get("GGTT_0p0")
   if (categories[i]=="em_em_nt1_postfit"):
        BSM=files.Get("em_1").Get("GGTT_8p0")
        BSM0=files.Get("em_1").Get("GGTT_0p0")
   if (categories[i]=="et_et_nt0_postfit"):
        BSM=files.Get("et_0").Get("GGTT_8p0")
        BSM0=files.Get("et_0").Get("GGTT_0p0")
   if (categories[i]=="et_et_nt1_postfit"):
        BSM=files.Get("et_1").Get("GGTT_8p0")
        BSM0=files.Get("et_1").Get("GGTT_0p0")
   if (categories[i]=="mt_mt_nt0_postfit"):
        BSM=files.Get("mt_0").Get("GGTT_8p0")
        BSM0=files.Get("mt_0").Get("GGTT_0p0")
   if (categories[i]=="mt_mt_nt1_postfit"):
        BSM=files.Get("mt_1").Get("GGTT_8p0")
        BSM0=files.Get("mt_1").Get("GGTT_0p0")
   if (categories[i]=="tt_tt_nt0_postfit"):
        BSM=files.Get("tt_0").Get("GGTT_8p0")
        BSM0=files.Get("tt_0").Get("GGTT_0p0")
   if (categories[i]=="tt_tt_nt1_postfit"):
        BSM=files.Get("tt_1").Get("GGTT_8p0")
        BSM0=files.Get("tt_1").Get("GGTT_0p0")
   err = ctypes.c_double(1.)
   nor = ZTT.IntegralAndError(0, ZTT.GetNbinsX() + 1, err)
   print(nor,err)

   ZTT.Add(VV)
   ZLL=ZTT.Clone()
   if ("et" in categories[i] or "mt" in categories[i]): ZLL=file.Get(categories[i]).Get("ZLL")
   GGTT=file.Get(categories[i]).Get("GGTT")
   excl=file.Get(categories[i]).Get("GGWW")
   #if not "tt" in categories[i]: VV.Add(GGWW)
   if "et" in categories[i]: 
      GGEE=file.Get(categories[i]).Get("GGEE")
      excl.Add(GGEE)
   if "mt" in categories[i]: 
      GGMM=file.Get(categories[i]).Get("GGMM")
      excl.Add(GGMM)
   Fake=file.Get(categories[i]).Get("Fake")
   Total=file.Get(categories[i]).Get("TotalProcs")
   Bkg=file.Get(categories[i]).Get("TotalBkg")

   Data.GetXaxis().SetTitle("")
   Data.GetXaxis().SetTitleSize(0)
   Data.GetXaxis().SetNdivisions(505)
   Data.GetYaxis().SetLabelFont(42)
   Data.GetYaxis().SetLabelOffset(0.01)
   Data.GetYaxis().SetLabelSize(0.06)
   Data.GetYaxis().SetTitleSize(0.08)
   Data.GetYaxis().SetTitleOffset(1.1)
   Data.SetTitle("")
   Data.GetYaxis().SetTitle("Events")
   Data.SetMinimum(0.1)


   #blind
   #if "em" in categories[i]:
   #  for k in range(5,Data.GetSize()):
   #      Data.SetBinContent(k,0.0)
   #if "et" in categories[i]:
   #  for k in range(4,Data.GetSize()):
   #      Data.SetBinContent(k,0.0)
   #if "mt" in categories[i]:
   #  for k in range(4,Data.GetSize()):
   #      Data.SetBinContent(k,0.0)
   #if "tt" in categories[i]:
   #  for k in range(3,Data.GetSize()):
   #      Data.SetBinContent(k,0.0)

   ZLL.SetFillColor(ROOT.TColor.GetColor("#f9b5ac"))
   ZTT.SetFillColor(ROOT.TColor.GetColor("#9dbf9e"))
   if not "tt" in categories[i]: excl.SetFillColor(ROOT.TColor.GetColor("#d0d6b5"))
   Fake.SetFillColor(ROOT.TColor.GetColor("#987284"))
   #GGWW.SetFillColor(ROOT.TColor.GetColor("#4de321"))

   Data.SetMarkerStyle(20)
   Data.SetMarkerSize(1)
   ZTT.SetLineColor(1)
   if ("et" in categories[i] or "mt" in categories[i]): ZLL.SetLineColor(1)
   if not "tt" in categories[i]: excl.SetLineColor(1)
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
   #stack.Add(ZTT)
   if not "tt" in categories[i]: stack.Add(excl)
   stack.Add(Fake)
   if ("et" in categories[i] or "mt" in categories[i]): stack.Add(ZLL)
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

   Data.GetXaxis().SetLabelSize(0)
   Data.SetMaximum(max(Data.GetMaximum()*1.55,errorBand.GetMaximum()*1.55))
   Data.SetMinimum(0.1)
   Data.Draw("e")
   stack.Draw("histsame")
   errorBand.Draw("e2same")
   Data.Draw("esame")

   #if args.year=="2018": GGTT.Draw("histsame")

   legende=make_legend()
   if "tt" in categories[i]:
      legende=make_legend2()
   legende.AddEntry(Data,"Observed ","elp")
   if ("tt" in categories[i]): legende.AddEntry(ZTT,"Z/#gamma* #rightarrow #tau#tau ","f")
   else: legende.AddEntry(ZTT,"Z/#gamma* (#rightarrow #tau#tau) + VV ","f")
   if ("mt" in categories[i]): legende.AddEntry(ZLL, "Z/#gamma* #rightarrow #mu#mu ","f")
   if ("et" in categories[i]): legende.AddEntry(ZLL, "Z/#gamma* #rightarrow ee ","f")
   #if not "tt" in categories[i]: legende.AddEntry(excl,"#gamma#gamma #rightarrow ee/#mu#mu/WW","f")
   if "em" in categories[i] and "nt0" in categories[i]: legende.AddEntry(excl,"#gamma#gamma #rightarrow WW ","f")
   if "et" in categories[i] and "nt0" in categories[i]: legende.AddEntry(excl,"#gamma#gamma #rightarrow ee/WW ","f")
   #if "mt" in categories[i]: legende.AddEntry(excl,"#gamma#gamma #rightarrow #mu#mu/WW","f")
   #legende.AddEntry(GGWW,"#gamma#gamma#rightarrow WW","f")
   legende.AddEntry(Fake,"Jet mis-ID ","f")
   legende.AddEntry(GGTTfull,"#gamma#gamma #rightarrow #tau#tau ","f")
   legende.AddEntry(errorBand,"Uncertainty ","f")
   legende.Draw()

   l1=add_lumi()
   l1.Draw("same")
   l2=add_CMS()
   l2.Draw("same")
   l3=add_Preliminary()
   l3.Draw("same")

   lowX=0.16
   lowY=0.83
   lumi1  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
   lumi1.SetBorderSize(   0 )
   lumi1.SetFillStyle(    0 )
   lumi1.SetTextAlign(   12 )
   lumi1.SetTextColor(    1 )
   lumi1.SetTextSize(0.07)
   lumi1.SetTextFont (   42 )
   if "emu_nt0" in name[i]: lumi1.AddText("e#mu, #it{N}_{#lower[-0.25]{tracks}} = 0")
   if "etau_nt0" in name[i]: lumi1.AddText("e#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 0")
   if "mutau_nt0" in name[i]: lumi1.AddText("#mu#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 0")
   if "tautau_nt0" in name[i]: lumi1.AddText("#tau_{h}#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 0")
   if "emu_nt1" in name[i]: lumi1.AddText("e#mu, #it{N}_{#lower[-0.25]{tracks}} = 1")
   if "etau_nt1" in name[i]: lumi1.AddText("e#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 1")
   if "mutau_nt1" in name[i]: lumi1.AddText("#mu#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 1")
   if "tautau_nt1" in name[i]: lumi1.AddText("#tau_{h}#tau_{h}, #it{N}_{#lower[-0.25]{tracks}} = 1")
   lumi1.Draw("same")
 
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
   pad2.Draw()
   pad2.cd()

   h1=Data.Clone()
   h1.SetMaximum(1.8)
   h1.SetMinimum(0.2)
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
   h1.GetXaxis().SetNdivisions(505)#was 505
   h1.GetYaxis().SetNdivisions(5)

   h1.GetXaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleSize(0.15)
   h1.GetYaxis().SetTitleOffset(0.56)
   h1.GetXaxis().SetTitleOffset(1.04)
   h1.GetXaxis().SetLabelSize(0.11)
   h1.GetYaxis().SetLabelSize(0.11)
   h1.GetXaxis().SetTitleFont(42)
   h1.GetYaxis().SetTitleFont(42)

   sf=GGTTfull.Integral()/BSM0.Integral()
   BSM.Scale(sf)

   BSM.Add(Bkg)
   BSM.Divide(hwoE)
   BSM.SetLineColor(4)
   BSM.SetLineWidth(2)

   if "em" in categories[i] or "tt" in categories[i]: h1.GetXaxis().ChangeLabel(4,-1,-1,-1,-1,-1,"500");
   else: h1.GetXaxis().ChangeLabel(3,-1,-1,-1,-1,-1,"500");

   h1.Draw("e0p")
   h3.Draw("e2same")
   BSM.Draw("histsame")

   line=ROOT.TLine(55,1,200,1)
   if "tt" in categories[i]: line=ROOT.TLine(70,1,250,1)
   if "em" in categories[i]: line=ROOT.TLine(40,1,200,1)
   line.SetLineColor(ROOT.TColor.GetColor("#ee7674"))
   line.SetLineWidth(2)
   line.Draw("same")

   h1.Draw("e0psame")

   legende3=make_legend3()
   if "tt" in categories[i] or "nt1" in categories[i]: legende3=make_legend31()
   legende3.AddEntry(line,"SM a_{#tau}","l")
   legende3.AddEntry(BSM,"a_{#tau} = 0.008","l")
   legende3.Draw("same")


   line2=ROOT.TLine(174,0.1,176,0.3)
   if "tt" in categories[i]: line2=ROOT.TLine(224,0.1,226,0.3)
   line2.Draw("same")
   line3=ROOT.TLine(175,0.1,177,0.3)
   if "tt" in categories[i]: line3=ROOT.TLine(225,0.1,227,0.3)
   line3.Draw("same")

   #xmin=40
   #xmid=150
   #xmax=200
   #y=0.1
   #ndiv_lin=10
   #chopt=''
   #flin = ROOT.TF1('flin',"x",xmin,xmid)
   #xaxis = ROOT.TGaxis(xmin,y,xmid,y,'flin',ndiv_lin,chopt)
   #xaxis.SetLineWidth(1)
   #xaxis.SetLineColor(2)
   #xaxis.SetTickSize(0.03*(xmax-xmin)/(xmid-xmin)) # scales with axis length
   #xaxis.SetLabelFont(42)
   #xaxis.SetLabelColor(2)
   #xaxis.SetLabelSize(0.1)
   #xaxis.SetLabelOffset(6e-3)
   #xaxis.SetTitleSize(0)
   #xaxis.Draw()


   ROOT.gPad.RedrawAxis()

   c.cd()

   pad1.Draw()

   ROOT.gPad.RedrawAxis()



   c.Modified()

   c.SaveAs("new_plots_postfit/control_"+name[i]+".pdf")
   c.SaveAs("new_plots_postfit/control_"+name[i]+".png")

   if categories[i]=="em_em_nt0_postfit":
     c.SaveAs("Figure_009-a.pdf")
     c.SaveAs("Figure_009-a.png")
     c.SaveAs("Figure_009-a.root")

   if categories[i]=="et_et_nt0_postfit":
     c.SaveAs("Figure_009-b.pdf")
     c.SaveAs("Figure_009-b.png")
     c.SaveAs("Figure_009-b.root")

   if categories[i]=="mt_mt_nt0_postfit":
     c.SaveAs("Figure_009-c.pdf")
     c.SaveAs("Figure_009-c.png")
     c.SaveAs("Figure_009-c.root")

   if categories[i]=="tt_tt_nt0_postfit":
     c.SaveAs("Figure_009-d.pdf")
     c.SaveAs("Figure_009-d.png")
     c.SaveAs("Figure_009-d.root")

   if categories[i]=="em_em_nt1_postfit":
     c.SaveAs("Figure_010-a.pdf")
     c.SaveAs("Figure_010-a.png")
     c.SaveAs("Figure_010-a.root")

   if categories[i]=="et_et_nt1_postfit":
     c.SaveAs("Figure_010-b.pdf")
     c.SaveAs("Figure_010-b.png")
     c.SaveAs("Figure_010-b.root")

   if categories[i]=="mt_mt_nt1_postfit":
     c.SaveAs("Figure_010-c.pdf")
     c.SaveAs("Figure_010-c.png")
     c.SaveAs("Figure_010-c.root")

   if categories[i]=="tt_tt_nt1_postfit":
     c.SaveAs("Figure_010-d.pdf")
     c.SaveAs("Figure_010-d.png")
     c.SaveAs("Figure_010-d.root")



