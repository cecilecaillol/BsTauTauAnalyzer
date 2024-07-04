#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array


def add_lumi():
    lowX=0.62
    lowY=0.83
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.27
    lowY=0.83
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
    lowX=0.36
    lowY=0.805
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.05)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
    lumi.AddText("Supplementary")
    lumi.AddText("")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.63, 0.78, 0.95, 0.95, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        output.SetTextSize(0.04)
        return output


#c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",600,400);
#c1.GetFrame().SetBorderSize(12);
c1.SetLeftMargin( 0.25 );
#c1.SetTopMargin( 0.15 );
#c1.SetBottomMargin( 0.15 );
c1.SetTickx(1)

n = 5;
x, x95, y, y95, exl, eyl, exh, eyh, exl95, exh95 = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ),
experiment=[]

x.append(0.00094)
x95.append(0.0009)
y.append(1)
y95.append(1.1)
exh.append(0.00415-0.00094)
eyh.append(0)
exl.append(0.00213+0.00094)
eyl.append(0)
exh95.append(0.0062-0.0009)
exl95.append(0.0042+0.0009)
experiment.append("Combined")

x.append(0.00117)
x95.append(0.001)
y.append(2)
y95.append(2.1)
exh.append(0.00487-0.00117)
eyh.append(0)
exl.append(0.00261+0.00117)
eyl.append(0)
exh95.append(0.00)
exl95.append(0.00)
experiment.append("#tau_{h}#tau_{h}")

x.append(0.00098)
x95.append(-0.041)
y.append(3)
y95.append(3.1)
exh.append(0.00416-0.00098)
eyh.append(0)
exl.append(0.00217+0.00098)
eyl.append(0)
exh95.append(0.041+0.024)
exl95.append(0.057-0.041)
experiment.append("#mu#tau_{h}")

x.append(0.00592)
x95.append(-0.018)
y.append(4)
y95.append(4.1)
exh.append(0.00992-0.00592)
eyh.append(0)
exl.append(0.00668+0.00592)
eyl.append(0)
exh95.append(0.013+0.018)
exl95.append(0.052-0.018)
experiment.append("e#tau_{h}")

x.append(0.00047)
x95.append(0.004)
y.append(5)
y95.append(5.1)
exh.append(0.00618-0.00047)
eyh.append(0)
exl.append(0.00431+0.00047)
eyl.append(0)
exh95.append(0.058-0.004)
exl95.append(0.052+0.004)
experiment.append("e#mu")

gr95 = ROOT.TGraphAsymmErrors(n,x95,y95,exl95,exh95,eyl,eyh);
axis=gr95.GetXaxis();
axis.SetLimits(-0.02, 0.02)
gr95.SetTitle("");
gr95.SetMarkerStyle(21);
gr95.SetMarkerSize(0.5)
gr95.SetLineWidth(2)
gr95.SetLineColor(ROOT.kGreen+3)
gr95.SetMarkerColor(ROOT.kGreen+3)
#gr95.Draw("AP");
gr95.SetTitle("");
gr95.GetXaxis().SetTitle("a_{#lower[-0.25]{#tau}}");
gr95.GetXaxis().SetTitleSize(0.05);
gr95.GetYaxis().SetNdivisions(0, 0, 0);
gr95.GetXaxis().SetNdivisions(505)

gr = ROOT.TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
gr.SetTitle("");
axis=gr.GetXaxis();
axis.SetLimits(-0.008, 0.012)
gr.SetMarkerStyle(20);
#gr.SetMarkerSize(0.5);
gr.SetLineWidth(2)
gr.Draw("AP");
gr.SetTitle("");
gr.GetXaxis().SetTitle("a_{#lower[-0.25]{#tau}}");
gr.GetXaxis().SetTitleOffset(0.9)
gr.GetXaxis().SetTitleSize(0.05);
gr.GetXaxis().SetNdivisions(505);
gr.GetYaxis().SetNdivisions(0, 0, 0);

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.055);
t.SetTextFont(42);
for i in range(0,n):
   t.DrawLatex(-0.013, y[i], experiment[i]);
   #t.DrawLatex(-0.03, y[i], "e#mu");

t2 = ROOT.TText();
t2.SetTextAlign(2);
t2.SetTextSize(0.035);
t2.SetTextFont(42);
t2.SetTextColor(ROOT.kRed);
t2.DrawText(0.0013, 5.2, "SM");

line = ROOT.TLine(0.0011772, 0.6, 0.0011772, 5.4);
line.SetLineStyle(2);
line.SetLineColor(ROOT.kRed);
line.Draw();

line2 = ROOT.TLine(-0.008,1.5,0.012,1.5);
line2.Draw();

leg=make_legend()
leg.AddEntry(gr,"Observed", "lp")
leg.AddEntry(gr95,"Expected", "l")
#leg.Draw("same")

lumi1=add_lumi()
lumi2=add_CMS()
lumi3=add_Preliminary()
lumi1.Draw("same")
lumi2.Draw("same")
lumi3.Draw("same")

c1.Update();

c1.SaveAs("fs_atau.pdf")
c1.SaveAs("fs_atau.png")
c1.SaveAs("fs_atau.root")
