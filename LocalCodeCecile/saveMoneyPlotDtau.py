#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array


def add_lumi():
    lowX=0.24
    lowY=0.14
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.25
    lowY=0.182
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
    lowX=0.38
    lowY=0.175
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.035)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
    lumi.AddText("")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.63, 0.18, 0.95, 0.3, "", "brNDC")
        output.SetNColumns(1)
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
#c1.SetTopMargin( 0.15 );
#c1.SetBottomMargin( 0.15 );
c1.SetTickx(1)

n = 6;
x, x95, y, exl, eyl, exh, eyh, exl95, exh95 = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' )
experiment=[]
ref=[]

x.append(0.)
x95.append(0.)
y.append(1)
exh.append(1.8e-17)
eyh.append(0)
exl.append(1.8e-17)
eyl.append(0)
exh95.append(2.9e-17)
exl95.append(2.9e-17)
experiment.append("This result")
ref.append("")

x.append(-1111110.0002)
x95.append(-1111110.0002)
y.append(2)
exh.append(0)
eyh.append(0)
exl.append(0)
eyl.append(0)
exh95.append(0)
exl95.append(0)
experiment.append("")
ref.append("")

###############################################

x.append(-0.62e-17)
x95.append(0e-17)
y.append(3)
exh.append(0.63e-17)
eyh.append(0)
exl.append(0.63e-17)
eyl.append(0)
exh95.append(0.61e-17)
exl95.append(1.85e-17)
experiment.append("Belle")
ref.append("JHEP 04 (2022) 110")

x.append(16e-17)
x95.append(0.0)
y.append(4)
exh.append(19e-17)
eyh.append(0)
exl.append(19e-17)
eyl.append(0)
exh95.append(46e-17)
exl95.append(46e-17)
experiment.append("ARGUS")
ref.append("PLB 485 (2000) 37")

x.append(0.0)
x95.append(0.0)
y.append(5)
exh.append(19.8e-17)
eyh.append(0)
exl.append(19.8e-17)
eyl.append(0)
exh95.append(31e-17)
exl95.append(31e-17)
experiment.append("L3")
ref.append("PLB 434 (1998) 169")

x.append(16)
x95.append(-0.00)
y.append(6)
exh.append(0.0)
eyh.append(0)
exl.append(0.0)
eyl.append(0)
exh95.append(36e-17)
exl95.append(38e-17)
experiment.append("OPAL")
ref.append("PLB 431 (1998) 188")

gr95 = ROOT.TGraphAsymmErrors(n,x95,y,exl95,exh95,eyl,eyh);
axis=gr95.GetXaxis();
axis.SetLimits(-47e-17, 50e-17)
gr95.SetTitle("");
gr95.SetMarkerStyle(20)
gr95.SetMarkerSize(0);
gr95.SetLineColor(ROOT.kGreen+3)
gr95.Draw("AP");
gr95.SetTitle("");
gr95.GetXaxis().SetTitle("d_{#lower[-0.25]{#tau}} (e cm)");
gr95.GetXaxis().SetTitleSize(0.05);
gr95.GetYaxis().SetNdivisions(0, 0, 0);

gr = ROOT.TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
gr.SetTitle("");
gr.SetMarkerStyle(20);
gr.SetLineWidth(3)
gr.Draw("P");
gr.SetTitle("");
gr.GetXaxis().SetTitle("d_{#tau} (e cm)");
gr.GetXaxis().SetTitleSize(0.05);
gr.GetXaxis().SetNdivisions(505);
gr.GetYaxis().SetNdivisions(0, 0, 0);

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.035);
t.SetTextFont(42);
for i in range(0,n):
   t.DrawText(-83e-17, y[i], experiment[i]);

t3 = ROOT.TText();
t3.SetTextAlign(2);
t3.SetTextSize(0.023);
t3.SetTextFont(41);
for i in range(0,n):
   t3.DrawText(-83e-17, y[i]-0.3, ref[i]);


t2 = ROOT.TText();
t2.SetTextAlign(2);
t2.SetTextSize(0.035);
t2.SetTextFont(42);
t2.SetTextColor(ROOT.kRed);
t2.DrawText(1.0e-17, 6.3, "SM");

line = ROOT.TLine(0.0, 0.5, 0.0, 6.5);
line.SetLineStyle(2);
line.SetLineColor(ROOT.kRed);
line.Draw();

line2 = ROOT.TLine(-47e-17,2.5,47e-17,2.5);
line2.Draw();

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

c1.SaveAs("dtau_overview.pdf")
c1.SaveAs("dtau_overview.png")
c1.SaveAs("Figure_012-b.pdf")
c1.SaveAs("Figure_012-b.png")
c1.SaveAs("Figure_012-b.root")

