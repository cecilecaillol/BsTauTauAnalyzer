#!/usr/bin/env python
import ROOT
import re  
from array import array
import argparse

ROOT.gStyle.SetOptStat(0)

def make_legend():
        output = ROOT.TLegend(0.38, 0.64, 0.89, 0.9, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(62)
        return output

parser = argparse.ArgumentParser()
parser.add_argument('--channel')
options = parser.parse_args()

file=ROOT.TFile("GGTT_et.root","r")
if options.channel=="emu": file=ROOT.TFile("GGTT_em.root","r")

aco=file.Get("h_acoplanarity")


c=ROOT.TCanvas("canvas","",0,0,600,600)
c.SetLeftMargin(0.15)
c.cd()

hist=["h_acoplanarity","h_resolution_acoplanarity"]
hist_lt100=["h_acoplanarity_sumptlt100","h_resolution_acoplanarity_sumptlt100"]
hist_gt100=["h_acoplanarity_sumptgt100","h_resolution_acoplanarity_sumptgt100"]
xname=["Acoplanarity","Reco A - gen A"]
name=["compa_aco","compa_resaco"]

for i in range(0,len(hist)):

   aco=file.Get(hist[i])
   aco_lt100=file.Get(hist_lt100[i])
   aco_gt100=file.Get(hist_gt100[i])
   
   aco.SetTitle("")
   aco.GetXaxis().SetTitle(xname[i])
   aco.GetYaxis().SetTitle("Probability density")
   aco.GetXaxis().SetTitleSize(0.06)
   aco.GetXaxis().SetTitleOffset(0.8)
   aco.GetYaxis().SetTitleSize(0.06)
   if options.channel=="etau": aco.SetMaximum(1.5*aco.GetMaximum())
   if options.channel=="emu": aco.SetMaximum(2.0*aco.GetMaximum())
   aco.SetLineColor(ROOT.EColor.kOrange+1)
   aco.SetLineWidth(3)
   aco_lt100.SetLineColor(ROOT.EColor.kGreen+1)
   aco_lt100.SetLineWidth(3)
   aco_gt100.SetLineColor(ROOT.EColor.kBlue+1)
   aco_gt100.SetLineWidth(3)
   aco.DrawNormalized("hist")
   aco_lt100.DrawNormalized("histsame")
   aco_gt100.DrawNormalized("histsame")
   
   l=make_legend()
   l.AddEntry(aco,"All","l")
   if options.channel=="etau": 
     l.AddEntry(aco_lt100,"p_{T}(e) + p_{T}(#tau_{h}) < 100 GeV","l")
     l.AddEntry(aco_gt100,"p_{T}(e) + p_{T}(#tau_{h}) > 100 GeV","l")
   if options.channel=="emu": 
     l.AddEntry(aco_lt100,"p_{T}(e) + p_{T}(#mu) < 100 GeV","l")
     l.AddEntry(aco_gt100,"p_{T}(e) + p_{T}(#mu) > 100 GeV","l")
   l.Draw("same")
   
   categ  = ROOT.TPaveText(0.78, 0.5+0.013, 0.83, 0.5+0.155, "NDC")
   categ.SetBorderSize(   0 )
   categ.SetFillStyle(    0 )
   categ.SetTextAlign(   12 )
   categ.SetTextSize ( 0.08 )
   categ.SetTextColor(    1 )
   categ.SetTextFont (   42 )
   if options.channel=="etau": categ.AddText("e#tau_{h}")
   if options.channel=="emu": categ.AddText("e#mu")
   if options.channel=="mutau": categ.AddText("#mu#tau_{h}")
   if options.channel=="tautau": categ.AddText("#tau_{h}#tau_{h}")
   categ.Draw("same")
   
   if options.channel=="etau": c.SaveAs("plots_etau_2018/"+name[i]+".png")
   if options.channel=="emu": c.SaveAs("plots_emu_2018/"+name[i]+".png")
   
