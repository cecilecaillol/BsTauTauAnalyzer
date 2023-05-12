import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,getdflist,gethisto_cate
import numpy as np
from ROOT import TFile
from math import sqrt
GGTT = cate("GGTT",["GGToTauTau"])
dfGGTT = getdflist(GGTT,"tautau")

def GetBSMhisto(BSMweight,BSMname,cut,cutname,variable):
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    weight = weight + BSMweight
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tau2index]!=0"
    cutisoMCname = cutname+"_iso_realMC"
    weight_withSF = weight
    if "nTrk==0" in cut:
        weight_withSF = weight + "*2.65"
    elif "nTrk==1" in cut:
        weight_withSF = weight + "*1.87"
    hisGGTT_iso = gethisto_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable)
    hisGGTT_iso.SetName("GGTT{}".format(BSMname))
    maxbin = hisGGTT_iso.GetNbinsX()
    for i in range(1,hisGGTT_iso.GetNbinsX()+1):
        if hisGGTT_iso.GetBinContent(i)<=0:
            hisGGTT_iso.SetBinContent(i,0)
            hisGGTT_iso.SetBinError(i,0) 
    hisGGTT_iso.SetBinContent(maxbin, hisGGTT_iso.GetBinContent(maxbin)+hisGGTT_iso.GetBinContent(maxbin+1))
    hisGGTT_iso.SetBinError(maxbin, sqrt(hisGGTT_iso.GetBinError(maxbin)**2+hisGGTT_iso.GetBinError(maxbin+1)**2))
    hisGGTT_iso.SetBinContent(maxbin+1,0)
    hisGGTT_iso.SetBinError(maxbin+1,0)
    return hisGGTT_iso

def getBSMhisto(cut,cutname,variable):
    hisGGTTlist = []
    integer = 0
    decimals = 0
    ceBRname = ""
    TauG2weightsname = ""
    BSMweight=""
    print ("prepare normal histogram")
    histo_normal = GetBSMhisto(BSMweight,ceBRname,cut,cutname,variable)
    hisGGTTlist.append(histo_normal)
    for i in np.arange(-40.0,40.8,0.8):
        if (i<-0.4):
            integer = int(i-0.1)
        else:
            integer = int(i+0.1)
        decimals = int(round(abs(i-integer)*10,0))
        print ("i = ", i , " integer ", integer, " decimals ", decimals)
        if (i<-0.4):
            ceBRname = "_m{}p{}".format(abs(integer),decimals)
        else:
            ceBRname = "_{}p{}".format(integer,decimals)
        TauG2weightsname = "TauG2Weights_ceBRe33"+ceBRname
        BSMweight = "*"+TauG2weightsname
        print("prepare histo with weight", BSMweight, " name ", ceBRname)
        histo = GetBSMhisto(BSMweight,ceBRname,cut,cutname,variable)
        hisGGTTlist.append(histo)
    return hisGGTTlist


mvis = variable("mvis","m_{vis}",int(8),np.array([40,55,70,85,100,150,200,350,500],dtype=float)) 

fout = TFile("./Signal_tautau.root","recreate")

fout.mkdir("tt_0")
fout.mkdir("tt_1")

tt_0cut = "(nTrk==0) && (Acopl<0.02) && tau1pt>40 && tau2pt>40 && mvis>40"
tt_1cut = "(nTrk==1) && (Acopl<0.02) && tau1pt>40 && tau2pt>40 && mvis>40"
tt_0_histotuple = getBSMhisto(tt_0cut,"tt_0",mvis)
fout.cd("tt_0")
for histo in tt_0_histotuple:
    histo.Write()

fout.cd("tt_1")
tt_1_histotuple = getBSMhisto(tt_1cut,"tt_1",mvis)
fout.cd("tt_1")
for histo in tt_1_histotuple:
    histo.Write()
