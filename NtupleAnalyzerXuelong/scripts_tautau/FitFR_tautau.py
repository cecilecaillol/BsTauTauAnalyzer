from ROOT import TFile, TFile, TH1D, TCanvas,TH1F,TPaveText,TF1,TMath
import math
#from ROOT.RDF import TH1DModel
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
import ROOT
ROOT.gROOT.SetBatch(1)
def fitFlat(x,p):
    return p[0]

def fitLinear(x,p):
    return p[0] + p[1]*x[0]

def fitExp(x,p):
    return p[0] + p[1]*(TMath.Exp(-(p[2]*x[0])))
                        
def fitLandau(x,p):
    return p[0] + p[1]*(TMath.Landau(x[0],p[2],p[3],0))

def fitPoly2(x,p):
    return p[0] + p[1]*x[0] + p[2]*x[0]*x[0]

def fitPoly3(x,p):
    return p[0] + p[1]*x[0] + p[2]*x[0]*x[0] + p[3]*x[0]*x[0]*x[0]

f = TFile("./FR_tautau.root")

def fit_histo(cut, decaymode, variablename , variabletitle):
    histo = "hFR_{}_{}_DM{}".format(variablename,cut,decaymode)
    print ("histo is ", histo)
    hFR = f.Get(histo)
    
    fMin = 30
    fMax = 300
    nPar = 3   
    fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)
    if variablename=="tau2pt":
        if decaymode==0:
            fMin = 40
            fMax = 300
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)
        elif decaymode==1:
            fMin = 40
            fMax = 300
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)

        elif decaymode==10:
            fMin = 40
            fMax = 300
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)

        elif decaymode==11:
            fMin = 40
            fMax = 300
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)
            
    elif variablename=="nTrk":
        if decaymode==0:
            fMin = -0.5
            fMax = 99.5
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)
        elif decaymode==1:
            fMin = -0.5
            fMax = 99.5
            nPar = 4
            fitfunc = TF1("fitfunc", fitExp, fMin, fMax, nPar)
        elif decaymode==10:
            fMin = -0.5
            fMax = 99.5
            nPar = 4
            fitfunc = TF1("fitfunc", fitExp, fMin, fMax, nPar)
        elif decaymode==11:
            fMin = -0.5
            fMax = 99.5
            nPar = 3
            fitfunc = TF1("fitfunc", fitPoly2, fMin, fMax, nPar)
        #nPar = 2
        #fitfunc = TF1("fitfunc", fitLinear, fMin, fMax, nPar)
    else:
        fMin = 0
        fMax = 1
        nPar=1
        fitfunc = TF1("fitfunc", fitFlat,fMin,fMax,nPar)
        
    hFR.Fit("fitfunc","R0")
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetFrameLineWidth(1)
    ROOT.gStyle.SetLineWidth(1)
    ROOT.gStyle.SetOptStat(0)
    c = TCanvas("c","",800,600)
    c.cd()
    c.SetFillColor(0)
    c.SetBorderMode(0)
    c.SetBorderSize(10)
    c.SetTickx(1)
    c.SetTicky(1)
    c.SetLeftMargin(0.10)
    c.SetRightMargin(0.05)
    c.SetTopMargin(0.122)
    c.SetBottomMargin(0.122)
    c.SetFrameFillStyle(0)
    c.SetFrameLineStyle(0)
    c.SetFrameLineWidth(2)
    c.SetFrameBorderMode(0)
    c.SetFrameBorderSize(10)

    hFR.GetXaxis().SetLabelSize(0.03)
    hFR.GetXaxis().SetTitle(variabletitle)
    hFR.GetXaxis().SetNdivisions(505)
    hFR.GetYaxis().SetLabelFont(42)
    hFR.GetYaxis().SetLabelOffset(0.01)
    hFR.GetYaxis().SetLabelSize(0.03)
    hFR.GetYaxis().SetTitleSize(0.03)
    hFR.GetYaxis().SetTitleOffset(1.2)
    hFR.GetYaxis().SetTickLength(0.012)
    hFR.SetTitle("")
    hFR.GetYaxis().SetTitle("FF")

    hFR.SetMarkerStyle(20)
    hFR.SetMarkerSize(1)
    hFR.SetLineWidth(1)
    hFR.Draw("e1p")
    fitfunc.SetLineColor(2);
    fitfunc.Draw("SAME")

    lowX=0.11
    lowY=0.835
    CMS =TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    CMS.SetTextFont(61)
    CMS.SetTextSize(0.06)
    CMS.SetBorderSize(   0 )
    CMS.SetFillStyle(    0 )
    CMS.SetTextAlign(   12 )
    CMS.SetTextColor(    1 )
    CMS.AddText("CMS")
    CMS.Draw("same")

    lowX=0.65
    lowY=0.835
    lumi  =TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    lumi.AddText("2018, 59.74 fb^{-1} (13 TeV)")
    lumi.Draw("same")

    lowX=0.20
    lowY=0.835
    Pre  = TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    Pre.SetTextFont(52)
    Pre.SetTextSize(0.04)
    Pre.SetBorderSize(   0 )
    Pre.SetFillStyle(    0 )
    Pre.SetTextAlign(   12 )
    Pre.SetTextColor(    1 )
    Pre.AddText("Preliminary")
    Pre.Draw("same")
    c.RedrawAxis()
    
    c.SaveAs("FRplots/FR_{}_DM{}_{}.png".format(cut,decaymode,variablename))
    return fitfunc

class variable:
    def __init__(self, name, title, nbins, binning):
        self.name=name
        self.title = title
        self.nbins=nbins
        self.binning = binning

taupt = variable("tau2pt","#sub tau_{h} p_{T}",int(9),np.array([40,45,50,60,80,100,150,200,250,300],dtype=float))
ntrk = variable("nTrk","N_{tracks}",int(24),np.array([-0.5,0.5,1.5,2.5,3.5,4.5,9.5,14.5,19.5,24.5,29.5,34.5,39.5,44.5,49.5,54.5,59.5,64.5,69.5,74.5,79.5,84.5,89.5,94.5,99.5],dtype=float))
Acopl = variable("Acopl","Acoplanarity",int(21),np.array([0,0.02,0.05,0.1,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00],dtype=float))
variablelist = [taupt, ntrk]
outfile = TFile("FRfit_tautau.root","recreate")
for cut in ["QCD"]:
    for decaymode in [0,1,10,11]:
        for variable in variablelist:
            print ("Begin to fit cut_{} decaymode_{} variable_{}".format(cut,decaymode,variable.name))
            fitfunc = fit_histo(cut,decaymode,variable.name,variable.title)
            fitfunc.SetName("fitfunc_{}_DM{}_{}".format(cut,decaymode,variable.name))
            outfile.cd()
            fitfunc.Write()

outfile.Close()