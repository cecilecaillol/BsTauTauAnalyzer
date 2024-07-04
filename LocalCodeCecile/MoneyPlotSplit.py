#!/usr/bin/env python
import ROOT
import re  
import argparse
from array import array


def add_lumi():
    lowX=0.27
    lowY=0.44
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
    lowX=0.27
    lowY=0.48
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
    lowX=0.4
    lowY=0.48
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.04)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.27, 0.35, 0.8, 0.5, "", "brNDC")
        output.SetNColumns(1)
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
        output.SetTextFont(42)
        output.SetTextSize(0.05)
        return output


#c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",600,900);
#c1.GetFrame().SetBorderSize(12);
c1.SetLeftMargin( 0.25 );
#c1.SetTopMargin( 0.15 );
#c1.SetBottomMargin( 0.15 );

n = 9;
x, y, exl, eyl, exh, eyh, exl95, exh95 = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' )
experiment=[]
ref=[]

x.append(-0.0002)
y.append(1)
exh.append(0.0034)
eyh.append(0)
exl.append(0.0033)
eyl.append(0)
exh95.append(0.0053+0.0002)
exl95.append(0.0056-0.0002)
experiment.append("Combined")
ref.append("")

x.append(-0.0002)
y.append(2)
exh.append(0.0032)
eyh.append(0)
exl.append(0.0032)
eyl.append(0)
exh95.append(0.0055+0.0002)
exl95.append(0.0059-0.0002)
experiment.append("#mu#tau_{h}")
ref.append("")

x.append(-0.000)
y.append(3)
exh.append(0.0037)
eyh.append(0)
exl.append(0.0038)
eyl.append(0)
exh95.append(0.0064)
exl95.append(0.0065)
experiment.append("#tau_{h}#tau_{h}")
ref.append("")

x.append(0.006)
y.append(4)
exh.append(0.0027)
eyh.append(0)
exl.append(0.0053)
eyl.append(0)
exh95.append(0.0092+0.0006)
exl95.append(0.0097-0.0006)
experiment.append("e#tau_{h}")
ref.append("")

x.append(-0.0027)
y.append(5)
exh.append(0.0091)
eyh.append(0)
exl.append(0.0042)
eyl.append(0)
exh95.append(0.0053+0.0002)
exl95.append(0.0056-0.0002)
experiment.append("e#mu")
ref.append("")

x.append(-1111110.0002)
y.append(6)
exh.append(0)
eyh.append(0)
exl.append(0)
eyl.append(0)
exh95.append(0)
exl95.append(0)
experiment.append("")
ref.append("")

###############################################

x.append(0.001)
y.append(7)
exh.append(0.055)
eyh.append(0)
exl.append(0.089)
eyl.append(0)
exh95.append(0.00)
exl95.append(0.00)
experiment.append("CMS Pb+Pb")
ref.append("PRL 131 (2023) 151803")

x.append(-0.041)
y.append(8)
exh.append(0.041-0.029)
eyh.append(0)
exl.append(0.050-0.041)
eyl.append(0)
exh95.append(0.041+0.024)
exl95.append(0.057-0.041)
experiment.append("ATLAS Pb+Pb")
ref.append("PRL 131 (2023) 151802")

x.append(-0.018)
y.append(9)
exh.append(0.017)
eyh.append(0)
exl.append(0.017)
eyl.append(0)
exh95.append(0.013+0.018)
exl95.append(0.052-0.018)
experiment.append("DELPHI")
ref.append("EPJC 35 (2004) 159")

gr95 = ROOT.TGraphAsymmErrors(n,x,y,exl95,exh95,eyl,eyh);
axis=gr95.GetXaxis();
axis.SetLimits(-0.098, 0.07)
gr95.SetTitle("");
gr95.SetMarkerStyle(20);
gr95.SetLineColor(ROOT.kGreen+3)
gr95.Draw("AP");
gr95.SetTitle("");
gr95.GetXaxis().SetTitle("#alpha_{#tau}");
gr95.GetXaxis().SetTitleSize(0.05);
gr95.GetYaxis().SetNdivisions(0, 0, 0);

gr = ROOT.TGraphAsymmErrors(n,x,y,exl,exh,eyl,eyh);
gr.SetTitle("");
gr.SetMarkerStyle(20);
gr.SetLineWidth(3)
gr.Draw("P");
gr.SetTitle("");
gr.GetXaxis().SetTitle("#alpha_{#tau}");
gr.GetXaxis().SetTitleSize(0.05);
gr.GetYaxis().SetNdivisions(0, 0, 0);

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.03);
t.SetTextFont(42);
for i in range(0,n):
   t.DrawText(-0.161, y[i], experiment[i]);

t3 = ROOT.TText();
t3.SetTextAlign(2);
t3.SetTextSize(0.023);
t3.SetTextFont(41);
for i in range(0,n):
   t3.DrawText(-0.161, y[i]-0.3, ref[i]);


t2 = ROOT.TText();
t2.SetTextAlign(2);
t2.SetTextSize(0.035);
t2.SetTextFont(42);
t2.SetTextColor(ROOT.kRed);
t2.DrawText(0.01, 9.5, "SM");

line = ROOT.TLine(0.0011772, 0.3, 0.0011772, 9.6);
line.SetLineStyle(2);
line.SetLineColor(ROOT.kRed);
line.Draw();

line2 = ROOT.TLine(-0.1,6.5,0.07,6.5);
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

c1.SaveAs("atau_overview.pdf")
c1.SaveAs("atau_overview.png")

