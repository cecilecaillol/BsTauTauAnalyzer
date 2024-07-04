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
    lowY=0.807
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.045)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
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
c1 = ROOT.TCanvas("c1","A Simple Graph with error bars",600,600);
#c1.GetFrame().SetBorderSize(12);
c1.SetLeftMargin( 0.4 );
c1.SetTopMargin( 0.15 );
c1.SetRightMargin( 0.09 );
#c1.SetLeftMargin( 0.25 );
#c1.SetTopMargin( 0.15 );
#c1.SetBottomMargin( 0.15 );
c1.SetTickx(1)

n = 5;
x, x95, y, exl, eyl, exh, eyh, exl95, exh95 = array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' ), array( 'd' )
experiment=[]
ref=[]
process=[]


x.append(0.)
x95.append(0.)
y.append(1)
exh.append(1.8e-17)
eyh.append(0)
exl.append(1.8e-17)
eyl.append(0)
exh95.append(2.9e-17)
exl95.append(2.9e-17)
#experiment.append("This result")
#ref.append("")
experiment.append("CMS")
process.append("#gamma#gamma #rightarrow #tau#tau (#gamma from p)")
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

x.append(-0.62e-17)
x95.append(0e-17)
y.append(2)
exh.append(0.63e-17)
eyh.append(0)
exl.append(0.63e-17)
eyl.append(0)
exh95.append(0.61e-17)
exl95.append(1.85e-17)
experiment.append("Belle")
process.append("ee #rightarrow #gamma* #rightarrow #tau#tau")
ref.append("JHEP 04 (2022) 110")

x.append(16e-17)
x95.append(0.0)
y.append(3)
exh.append(19e-17)
eyh.append(0)
exl.append(19e-17)
eyl.append(0)
exh95.append(46e-17)
exl95.append(46e-17)
experiment.append("ARGUS")
process.append("ee #rightarrow #gamma* #rightarrow #tau#tau")
ref.append("PLB 485 (2000) 37")

x.append(0.0)
x95.append(0.0)
y.append(4)
exh.append(19.8e-17)
eyh.append(0)
exl.append(19.8e-17)
eyl.append(0)
exh95.append(31e-17)
exl95.append(31e-17)
experiment.append("L3")
process.append("ee #rightarrow #tau#tau#gamma")
ref.append("PLB 434 (1998) 169")

x.append(16)
x95.append(-0.00)
y.append(5)
exh.append(0.0)
eyh.append(0)
exl.append(0.0)
eyl.append(0)
exh95.append(36e-17)
exl95.append(38e-17)
experiment.append("OPAL")
process.append("ee #rightarrow Z #rightarrow #tau#tau#gamma")
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
gr95.GetXaxis().SetTitleOffset(0.8);
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

#t = ROOT.TLatex();
#t.SetTextAlign(2);
#t.SetTextSize(0.035);
#t.SetTextFont(42);
#for i in range(0,n):
#   t.DrawText(-83e-17, y[i], experiment[i]);

#t3 = ROOT.TText();
#t3.SetTextAlign(2);
#t3.SetTextSize(0.023);
#t3.SetTextFont(41);
#for i in range(0,n):
#   t3.DrawText(-83e-17, y[i]-0.3, ref[i]);

t = ROOT.TLatex();
t.SetTextAlign(2);
t.SetTextSize(0.04);
#t.SetTextSize(0.021);
t.SetTextFont(62);
for i in range(1,n):
   t.DrawLatex(-111e-17, y[i]+0.2, experiment[i]);

tt = ROOT.TLatex();
tt.SetTextAlign(2);
tt.SetTextSize(0.04);
#tt.SetTextSize(0.021);
tt.SetTextFont(62);
tt.SetTextColor(ROOT.kRed)
for i in range(0,1):
   tt.DrawLatex(-111e-17, y[i]+0.2, experiment[i]);

t8 = ROOT.TLatex();
t8.SetTextAlign(2);
t8.SetTextSize(0.04);
t8.SetTextFont(42);
for i in range(1,n):
   t8.DrawLatex(-111e-17, y[i]-0.05, process[i]);

tt8 = ROOT.TLatex();
tt8.SetTextAlign(2);
tt8.SetTextSize(0.04);
tt8.SetTextFont(42);
tt8.SetTextColor(ROOT.kRed)
for i in range(0,1):
   tt8.DrawLatex(-111e-17, y[i]-0.05, process[i]);

t3 = ROOT.TText();
t3.SetTextAlign(2);
t3.SetTextSize(0.04);
t3.SetTextFont(41);
for i in range(1,n):
   t3.DrawText(-111e-17, y[i]-0.3, ref[i]);


tt3 = ROOT.TText();
tt3.SetTextAlign(2);
tt3.SetTextSize(0.04);
tt3.SetTextFont(41);
tt3.SetTextColor(ROOT.kRed)
for i in range(0,1):
   tt3.DrawText(-111e-17, y[i]-0.3, ref[i]);


t2 = ROOT.TText();
t2.SetTextAlign(2);
t2.SetTextSize(0.035);
t2.SetTextFont(42);
t2.SetTextColor(ROOT.kBlue);
t2.DrawText(1.0e-17, 3.5, "SM");

line = ROOT.TLine(0.0, 0.6, 0.0, 5.4);
line.SetLineStyle(2);
line.SetLineColor(ROOT.kBlue);
line.Draw();

#line2 = ROOT.TLine(-47e-17,1.5,47e-17,1.5);
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

gr.Draw("P")

c1.Update();

c1.SaveAs("dtau_overview.pdf")
c1.SaveAs("dtau_overview.png")
c1.SaveAs("Figure_013-b.pdf")
c1.SaveAs("Figure_013-b.png")
c1.SaveAs("Figure_013-b.root")

