import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,gethisto2D_cate,gethisto2D,getdflist
from ROOT import TFile
import numpy as np

ST = cate("ST",["ST_t_top","ST_t_antitop","ST_tW_top","ST_tW_antitop"])
VV = cate("VV",["WW2L2Nu","WZ2Q2L","WZ3LNu","ZZ2Q2L","ZZ2L2Nu","ZZ4L"])
TT = cate("TT",["TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic"])
ZTT = cate("ZTT",["DY"])
W = cate("W",["W","W1","W2","W3","W4"])
#GGWW = cate("GGWW",["GGToWW"])

dfST = getdflist(ST,"mutau")
dfVV = getdflist(VV,"mutau")
dfTT = getdflist(TT,"mutau")
dfZTT = getdflist(ZTT,"mutau")
dfW = getdflist(W,"mutau")

    
data_obs = cate("data_obs",["SingleMuonA","SingleMuonB","SingleMuonC","SingleMuonD"])
dfdata = getdflist(data_obs,"mutau")


def getWFRhisto(cut,cutname,variable1,variable2):
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    
    cutOS = cut + "&& isOS && is_isolated"
    cutSS = cut + "&& (!isOS) && is_isolated"
    cutOSname = cutname +"OS_iso"
    cutSSname = cutname + "SS_iso"
    channel = "mutau"
    histoSTSS = gethisto2D_cate(dfST,ST,cutSS,cutSSname,weight,variable1,variable2)
    histoVVSS = gethisto2D_cate(dfVV,VV,cutSS,cutSSname,weight,variable1,variable2)
    histoTTSS = gethisto2D_cate(dfTT,TT,cutSS,cutSSname,weight,variable1,variable2)
    histoZTTSS = gethisto2D_cate(dfZTT,ZTT,cutSS,cutSSname,weight,variable1,variable2)
    histoWSS = gethisto2D_cate(dfW,W,cutSS,cutSSname,weight,variable1,variable2)
    histodataSS = gethisto2D_cate(dfdata,data_obs,cutSS,cutSSname,"1",variable1,variable2)
    histoSS= histodataSS.Clone("h_{}_{}_{}_{}".format(variable1.name,variable2.name,cutSSname,"QCD"))
    histoSS.Add(histoSTSS,-1)
    histoSS.Add(histoVVSS,-1)
    histoSS.Add(histoTTSS,-1)
    histoSS.Add(histoZTTSS,-1)
    histoSS.Add(histoWSS,-1)
    
    histoWOS = gethisto2D_cate(dfW,W,cutOS,cutOSname,weight,variable1,variable2)
    

    hFR = histoWOS.Clone("hWFR_{}_{}_{}".format(variable1.name,variable2.name,cutname))
    #hFR.Divide(histononiso)
    deno = histoSS.Clone("hWQCD_{}_{}_{}".format(variable1.name,variable2.name,cutname))
    deno.Add(histoWOS)
    hFR.Divide(deno)
    
    return histoSTSS,histoVVSS,histoTTSS,histoZTTSS,histoWSS,histodataSS,histoSS,histoWOS,hFR

mvis = variable("mvis","mvis",int(5),np.array([50,100,150,200,250,300],dtype=float))
mtranse = variable("mtrans","mtrans",int(3),np.array([0,25,50,75],dtype=float))


fout = TFile("./FRW_mutau.root","recreate")
'''for DM in [0,1,10,11]:
    cut = "LepCand_DecayMode[tauindex]=={} && taupt>30 && mvis>40 && isSingleMuonTrigger".format(DM)
    cutname = "DM{}".format(DM)
    histotuple = getWFRhisto(cut,cutname,mtranse,mvis)
    fout.cd()
    for histo in histotuple:
        histo.Write()'''
cut = "(LepCand_DecayMode[tauindex]==0 || LepCand_DecayMode[tauindex]==1 || LepCand_DecayMode[tauindex]==10 || LepCand_DecayMode[tauindex]==11) && taupt>30 && mvis>40 && isSingleMuonTrigger"
cutname = "allDM"
histotuple = getWFRhisto(cut,cutname,mtranse,mvis)
fout.cd()
for histo in histotuple:
    histo.Write()

fout.Close()