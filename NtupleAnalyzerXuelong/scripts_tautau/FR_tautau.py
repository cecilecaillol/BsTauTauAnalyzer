import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,gethisto_cate,gethisto,getdflist
from ROOT import TFile
import numpy as np


ST = cate("ST",["ST_t_top","ST_t_antitop","ST_tW_top","ST_tW_antitop"])
VV = cate("VV",["WW2L2Nu","WZ2Q2L","WZ3LNu","ZZ2Q2L","ZZ2L2Nu","ZZ4L"])
TT = cate("TT",["TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic"])
ZTT = cate("ZTT",["DY"])
#GGWW = cate("GGWW",["GGToWW"])

dfST = getdflist(ST,"tautau")
dfVV = getdflist(VV,"tautau")
dfTT = getdflist(TT,"tautau")
dfZTT = getdflist(ZTT,"tautau")

    
data_obs = cate("data_obs",["TauA","TauB","TauC","TauD"])
dfdata = getdflist(data_obs,"tautau")

def getFRhisto(cut,cutname,variable):
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    
    cutiso = cut+" && is_isolated"
    cutisoname = cutname + "_iso"
    
    cutisoreal = cutiso + "&& LepCand_gen[tau2index]!=0"
    cutisorealname = cutisoname + "_real"
    
    cutnoniso = cut+" && !is_isolated"
    cutnonisoname = cutname + "_noniso"
    cutnonisoreal = cutnoniso + "&& LepCand_gen[tau2index]!=0"
    cutnonisorealname = cutnonisoname + "_real"
    channel = "tautau"
    
    histoSTiso = gethisto_cate(dfST,ST,cutisoreal,cutisorealname,weight,variable)
    histoVViso = gethisto_cate(dfVV,VV,cutisoreal,cutisorealname,weight,variable)
    histoTTiso = gethisto_cate(dfTT,TT,cutisoreal,cutisorealname,weight,variable)
    histoZTTiso = gethisto_cate(dfZTT,ZTT,cutisoreal,cutisorealname,weight,variable)
    histodataiso = gethisto_cate(dfdata,data_obs,cutiso,cutisoname,"1",variable)
    histoiso = histodataiso.Clone("h_{}_{}_{}".format(variable.name,cutname,"dataiso_sub"))
    histoiso.Add(histoSTiso,-1)
    histoiso.Add(histoVViso,-1)
    histoiso.Add(histoTTiso,-1)
    histoiso.Add(histoZTTiso,-1)
    
 
    histoSTnoniso = gethisto_cate(dfST,ST,cutnonisoreal,cutnonisorealname,weight,variable)
    histoVVnoniso = gethisto_cate(dfVV,VV,cutnonisoreal,cutnonisorealname,weight,variable)
    histoTTnoniso = gethisto_cate(dfTT,TT,cutnonisoreal,cutnonisorealname,weight,variable)
    histoZTTnoniso = gethisto_cate(dfZTT,ZTT,cutnonisoreal,cutnonisorealname,weight,variable)
    histodatanoniso = gethisto_cate(dfdata,data_obs,cutnoniso,cutnonisoname,"1",variable)

    histononiso = histodatanoniso.Clone("h_{}_{}_{}".format(variable.name,cutname,"datanoniso_sub"))
    histononiso.Add(histoSTnoniso,-1)
    histononiso.Add(histoVVnoniso,-1)
    histononiso.Add(histoTTnoniso,-1)
    histononiso.Add(histoZTTnoniso,-1)
    
    for i in (1,histoiso.GetNbinsX()+1):
        if histoiso.GetBinContent(i)<=0:
            histoiso.SetBinContent(i,0)
            histoiso.SetBinError(i,0)
        if histononiso.GetBinContent(i)<=0:
            histononiso.SetBinContent(i,0)
            histononiso.SetBinError(i,0)
    
    hFR = histoiso.Clone("hFR_{}_{}".format(variable.name,cutname))
    hFR.Divide(histononiso)

    if variable.name=="Acopl" or variable.name=="nTrk":
        ratio = histoiso.Integral(1,histoiso.GetNbinsX())/histononiso.Integral(1,histononiso.GetNbinsX())
        print ("ratio = ", ratio)
        for i in range(1,hFR.GetNbinsX()+1):
            print ("before i = ", i , " ",hFR.GetBinContent(i))
            hFR.SetBinContent(i,hFR.GetBinContent(i)/ratio)
            hFR.SetBinError(i,hFR.GetBinError(i)/ratio)
            print ("after i = ", i , " ",hFR.GetBinContent(i))
            print ("")
    return histoSTiso,histoVViso,histoTTiso,histoZTTiso,histoSTnoniso,histoVVnoniso,histoTTnoniso,histoZTTnoniso,histodataiso,histodatanoniso,histoiso,histononiso,hFR



taupt = variable("tau2pt","#sub tau_{h} p_{T}",int(9),np.array([40,45,50,60,80,100,150,200,250,300],dtype=float))
ntrk = variable("nTrk","N_{tracks}",int(24),np.array([-0.5,0.5,1.5,2.5,3.5,4.5,9.5,14.5,19.5,24.5,29.5,34.5,39.5,44.5,49.5,54.5,59.5,64.5,69.5,74.5,79.5,84.5,89.5,94.5,99.5],dtype=float))
Acopl = variable("Acopl","Acoplanarity",int(21),np.array([0,0.02,0.05,0.1,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00],dtype=float))

#variablelist = [taupt]
variablelist = [taupt, ntrk, Acopl]

fout = TFile("./FR_tautau.root","recreate")
for DM in [0,1,10,11]:
#for DM in [0]:
    for variable in variablelist:
        QCDcut = "!isOS && tau1pt>40 && tau2pt>40 && mvis>40"
        QCDcut = QCDcut+" && LepCand_DecayMode[tau2index]=={}".format(DM)
        QCDcutname = "QCD_DM{}".format(DM)
        histoQCDtuple = getFRhisto(QCDcut,QCDcutname,variable)
        fout.cd()
        for histoQCD in histoQCDtuple:
            histoQCD.Write()
fout.Close()