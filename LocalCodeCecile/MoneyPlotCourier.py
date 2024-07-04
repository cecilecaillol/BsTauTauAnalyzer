#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array


def add_lumi():
    lowX=0.61
    lowY=0.833
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{#minus1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.25
    lowY=0.84
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(62)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.385
    lowY=0.808
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.045)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    lumi.AddText("")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.23, 0.83, 0.92, 0.93, "", "brNDC")
        output.SetNColumns(3)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        output.SetTextSize(0.04)
        return output


#c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",600,700);
#c1.GetFrame().SetBorderSize(12);
c1.SetLeftMargin( 0.25 );
c1.SetTopMargin( 0.15 );
#c1.SetBottomMargin( 0.15 );
c1.SetTickx(1)

n = 5;
x, x95, y, exl, eyl, exh, eyh, exl95, exh95 = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' )
experiment=[]
process=[]
ref=[]

x.append(0.0009)
x95.append(0.0009)
y.append(1)
exh.append(0.0032)
eyh.append(0)
exl.append(0.0031)
eyl.append(0)
exh95.append(0.0062-0.0009)
exl95.append(0.0042+0.0009)
#experiment.append("This result")
#experiment.append("This result, CMS #gamma#gamma#rightarrow#tau#tau (#gamma from p)")
#process.append("#gamma#gamma#rightarrow#tau#tau (#gamma from p)")
#ref.append("")

experiment.append("CMS")
process.append("#gamma#gamma#rightarrow#tau#tau (#gamma from p)")
ref.append("This result")

#x.append(-1111110.0002)
#x95.append(-1111110.0002)
#y.append(2)
#exh.append(0)
#eyh.append(0)
#exl.append(0)
#eyl.append(0)
#exh95.append(0)
#exl95.append(0)
#experiment.append("")
#ref.append("")

###############################################

x.append(0.001)
x95.append(0.001)
y.append(2)
exh.append(0.055)
eyh.append(0)
exl.append(0.089)
eyl.append(0)
exh95.append(0.00)
exl95.append(0.00)
experiment.append("CMS")
#experiment.append("CMS, #gamma#gamma#rightarrow#tau#tau (#gamma from Pb)")
process.append("#gamma#gamma#rightarrow#tau#tau (#gamma from Pb)")
ref.append("PRL 131 (2023) 151803")

x.append(-0.041)
x95.append(-0.041)
y.append(3)
exh.append(0.041-0.029)
eyh.append(0)
exl.append(0.050-0.041)
eyl.append(0)
exh95.append(0.041+0.024)
exl95.append(0.057-0.041)
experiment.append("ATLAS")
#experiment.append("ATLAS, #gamma#gamma#rightarrow#tau#tau (#gamma from Pb)")
process.append("#gamma#gamma#rightarrow#tau#tau (#gamma from Pb)")
ref.append("PRL 131 (2023) 151802")

x.append(-0.018)
x95.append(-0.018)
y.append(4)
exh.append(0.017)
eyh.append(0)
exl.append(0.017)
eyl.append(0)
exh95.append(0.013+0.018)
exl95.append(0.052-0.018)
experiment.append("DELPHI")
#experiment.append("DELPHI, \n #gamma#gamma#rightarrow#tau#tau (#gamma from e)")
process.append("#gamma#gamma#rightarrow#tau#tau (#gamma from e)")
ref.append("EPJC 35 (2004) 159")

x.append(0.004)
x95.append(0.004)
y.append(5)
exh.append(0.035)
eyh.append(0)
exl.append(0.035)
eyl.append(0)
exh95.append(0.058-0.004)
exl95.append(0.052+0.004)
experiment.append("L3")
#experiment.append("L3, ee#rightarrowZ#rightarrow#tau#tau#gamma")
process.append("ee#rightarrowZ#rightarrow#tau#tau#gamma")
ref.append("PLB 434 (1998) 169")

#x.append(-10.00)
#x95.append(-0.00)
#y.append(6)
#exh.append(0.0)
#eyh.append(0)
#exl.append(0.0)
#eyl.append(0)
#exh95.append(0.065)
#exl95.append(0.068)
#experiment.append("OPAL")
#ref.append("PLB 431 (1998) 188")

gr95 = ROOT.TGraphAsymmErrors(n,x95,y,exl95,exh95,eyl,eyh);
axis=gr95.GetXaxis();
axis.SetLimits(-0.1, 0.07)
gr95.SetTitle("");
gr95.SetMarkerStyle(20);
gr95.SetMarkerSize(0)
gr95.SetLineColor(ROOT.kGreen+3)
gr95.SetLineStyle(2)
gr95.SetLineWidth(2)
gr95.Draw("AP");
gr95.SetTitle("");
gr95.GetXaxis().SetTitle("a_{#lower[-0.25]{#tau}}");
gr95.GetXaxis().SetTitleSize(0.05);
gr95.GetYaxis().SetNdivisions(0, 0, 0);
gr95.GetXaxis().SetNdivisions(505)

gr = ROOT.TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
gr.SetTitle("");
gr.SetMarkerStyle(20);
gr.SetLineWidth(3)
gr.Draw("P");
gr.SetTitle("");
gr.GetXaxis().SetTitle("a_{#lower[-0.25]{#tau}}");
gr.GetXaxis().SetTitleSize(0.05);
gr.GetXaxis().SetNdivisions(505);
gr.GetYaxis().SetNdivisions(0, 0, 0);

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.035);
#t.SetTextSize(0.021);
t.SetTextFont(62);
for i in range(0,n):
   t.DrawLatex(-0.163, y[i]+0.1, experiment[i]);

t8 = ROOT.TLatex();
t8.SetTextAlign(2);
t8.SetTextSize(0.023);
t8.SetTextFont(42);
for i in range(0,n):
   t8.DrawLatex(-0.163, y[i]-0.1, process[i]);

t3 = ROOT.TText();
t3.SetTextAlign(2);
t3.SetTextSize(0.023);
t3.SetTextFont(41);
for i in range(0,n):
   t3.DrawText(-0.163, y[i]-0.3, ref[i]);


t2 = ROOT.TText();
t2.SetTextAlign(2);
t2.SetTextSize(0.035);
t2.SetTextFont(42);
t2.SetTextColor(ROOT.kRed);
t2.DrawText(0.002, 3.5, "SM");

line = ROOT.TLine(0.0011772, 0.6, 0.0011772, 5.4);
#line.SetLineStyle(2);
line.SetLineColor(ROOT.kRed);
line.Draw();

#line2 = ROOT.TLine(-0.1,1.5,0.07,1.5);
#line2.Draw();

leg=make_legend()
leg.AddEntry(gr,"Observed", "p")
leg.AddEntry(gr,"68% CL", "l")
leg.AddEntry(gr95,"95% CL", "l")
leg.Draw("same")

lumi1=add_lumi()
lumi2=add_CMS()
lumi3=add_Preliminary()
lumi1.Draw("same")
lumi2.Draw("same")
lumi3.Draw("same")

c1.Update();

c1.SaveAs("courier2.pdf")
c1.SaveAs("courier2.png")
c1.SaveAs("courier2.root")

