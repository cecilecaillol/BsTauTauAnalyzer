from ROOT import RDataFrame, TFile, TChain, TTree, TFile, TH1D, TLorentzVector,TCanvas,TH1F,TPaveText,TH2F
from ROOT.RDF import TH1DModel, TH2DModel
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
import sys
sys.path.append("..")

ROOT.gInterpreter.AddIncludePath('../lib/')
ROOT.gInterpreter.Declare('#include "../lib/ApplyFR.h"')
ROOT.gInterpreter.Declare('#include "../lib/Sys.h"')
ROOT.gSystem.Load('../lib/RDFfunc.so')


class variable:
    def __init__(self, name, title, nbins, binning):
        self.name=name
        self.title = title
        self.nbins=nbins
        self.binning = binning
    
class cate:
    def __init__(self, name, samplelist):
        self.name=name
        self.samplelist=samplelist
        
def getdflist(cate,channel):
    dflist = []
    for sample in cate.samplelist:
        if channel=="mutau":
            dflist.append(RDataFrame("Events","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018_basicsel/{}.root".format(sample)))
        if channel=="tautau":
            dflist.append(RDataFrame("Events","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_tautau_2018_basicsel/{}.root".format(sample)))
    return dflist

def gethisto(df,sample,cut,cutname,weight,variable):
    print ("generate histogram of ", sample , " cut ", cut, " weight ", weight)
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Filter(cut).Define("totalweight",weight).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto_cate(dflist,cate,cut,cutname,weight,variable):
    print ("generate cate histogram of ", cate.name , " cut ", cutname, " weight ", weight)
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto(df,sample,cut,cutname,weight,variable)
        h.Add(histo,1)
    h.Sumw2()
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h


def gethisto2D(df,sample,cut,cutname,weight,variable1,variable2):
    print ("generate 2D histogram of ", sample , " cut ", cut, " weight ", weight)
    hmodel = TH2DModel("h_{}_{}_{}_{}".format(variable1.name,variable2.name,cutname,sample),"",variable1.nbins,variable1.binning,variable2.nbins,variable2.binning)
    histo = df.Define("totalweight",weight).Filter(cut).Histo2D(hmodel,variable1.name,variable2.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto2D_cate(dflist,cate,cut,cutname,weight,variable1,variable2):
    print ("generate cate 2Dhistogram of ", cate.name , " cut ", cutname, " weight ", weight)
    h = TH2F("h_{}_{}_{}_{}".format(variable1.name,variable2.name,cutname,cate.name),"",variable1.nbins,variable1.binning,variable2.nbins,variable2.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto2D(df,sample,cut,cutname,weight,variable1,variable2)
        h.Add(histo,1)
    h.Sumw2()
    for i in range(1,h.GetNbinsX()+1):
        for j in range(1,h.GetNbinsY()+1):
            if h.GetBinContent(i,j)<=0:
                h.SetBinContent(i,j,0)
                h.SetBinError(i,j,0)
    return h

def gethisto_withFR(df,sample,cut,cutname,weight,variable,channel):
    print(df.Count().GetValue())
    print ("cut is ", cut)
    print (df.Filter(cut).Count().GetValue())
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    print("xixi")
    if channel =="mutau":
        df = df.Filter(cut).Define("totalweight",weight).Define("FR","GetFR_{}(LepCand_DecayMode[tauindex],mvis,mtrans,taupt,nTrk,isMuonTauTrigger)".format(channel)).Define("plotweight","totalweight*FR")
    elif channel =="tautau":
        df = df.Filter(cut).Define("totalweight",weight).Define("FR","GetFR_{}(LepCand_DecayMode[tau2index],tau2pt,nTrk)".format(channel)).Define("plotweight","totalweight*FR")
    histo = df.Histo1D(hmodel,variable.name,"plotweight").GetPtr()
    print ("histo",sample , " " , cutname, "", cut, "", histo.Integral())
    histo.Sumw2()
    return histo

def gethisto_withFR_cate(dflist,cate,cut,cutname,weight,variable,channel):
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto_withFR(df,sample,cut,cutname,weight,variable,channel)
        h.Add(histo,1)
    h.Sumw2()
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h

def gethisto_sys_singleweight(df,sample,cut,cutname,weight,variable,func):
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Define("weight2",func).Define("totalweight","{}*weight2".format(weight)).Filter(cut).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto_sys_singleweight_cate(dflist,cate,cut,cutname,weight,variable,func):
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto_sys_singleweight(df,sample,cut,cutname,weight,variable,func)
        h.Add(histo,1)
    h.Sumw2()
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h



def gethisto_sys_doubleweight(df,sample,cut,cutname,weight,variable,functau1,functau2):
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Define("weighttau1",functau1).Define("weighttau2",functau2).Define("totalweight","{}*weighttau1*weighttau2".format(weight)).Filter(cut).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto_sys_doubleweight_cate(dflist,cate,cut,cutname,weight,variable,functau1,functau2):
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto_sys_doubleweight(df,sample,cut,cutname,weight,variable,functau1,functau2)
        h.Add(histo,1)
    h.Sumw2()
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h





def gethisto_syssinglenewtaupt(df,sample,cut,cutname,weight,variable,func):
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Redefine("my_tau",func).Redefine("taupt","my_tau.Pt()").Redefine("mvis","(my_mu + my_tau).M()").Define("totalweight",weight).Filter(cut).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto_cate_syssinglenewtaupt(dflist, cate, cut, cutname, weight, variable, func):
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto_syssinglenewtaupt(df,sample,cut,cutname,weight,variable, func)
        h.Add(histo,1)
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h


def gethisto_sysdoublenewtaupt(df,sample,cut,cutname,weight,variable,func1,func2):
    hmodel = TH1DModel("h_{}_{}_{}".format(variable.name,cutname,sample),"",variable.nbins,variable.binning)
    histo = df.Redefine("my_tau1",func1).Redefine("my_tau2",func2).Redefine("tau1pt","my_tau1.Pt()").Redefine("tau2pt","my_tau2.Pt()").Redefine("mvis","(my_tau1 + my_tau2).M()").Define("totalweight",weight).Filter(cut).Histo1D(hmodel,variable.name,"totalweight").GetPtr()
    histo.Sumw2()
    return histo

def gethisto_cate_sysdoublenewtaupt(dflist, cate, cut, cutname, weight, variable, func1,func2):
    h = TH1F("h_{}_{}_{}".format(variable.name,cutname,cate.name),"",variable.nbins,variable.binning)
    for df,sample in zip(dflist,cate.samplelist):
        histo = gethisto_sysdoublenewtaupt(df,sample,cut,cutname,weight,variable, func1,func2)
        h.Add(histo,1)
    for i in range(1,h.GetNbinsX()+1):
        if h.GetBinContent(i)<=0:
            h.SetBinContent(i,0)
            h.SetBinError(i,0)
    return h








