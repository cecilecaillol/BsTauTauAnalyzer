import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,gethisto_cate,gethisto,getdflist,gethisto_withFR_cate
from ROOT import TFile
import numpy as np

varname = sys.argv[1]
print (varname)

ST = cate("ST",["ST_t_top","ST_t_antitop","ST_tW_top","ST_tW_antitop"])
VV = cate("VV",["WW2L2Nu","WZ2Q2L","WZ3LNu","ZZ2Q2L","ZZ2L2Nu","ZZ4L"])
TT = cate("TT",["TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic"])
ZTT = cate("ZTT",["DY"])
GGTT = cate("GGTT",["GGToTauTau"])
#GGWW = cate("GGWW",["GGToWW"])

dfST = getdflist(ST,"mutau")
dfVV = getdflist(VV,"mutau")
dfTT = getdflist(TT,"mutau")
dfZTT = getdflist(ZTT,"mutau")
dfGGTT = getdflist(GGTT,"mutau")

    
data_obs = cate("data_obs",["SingleMuonA","SingleMuonB","SingleMuonC","SingleMuonD"])
dfdata = getdflist(data_obs,"mutau")


def getallhisto_mutau(cut,cutname,variable):
    channel = "mutau"
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    
    cutisodata = cut+" && isOS && is_isolated"
    cutnonisodata = cut+" && isOS && !is_isolated"
    
    cutisodataname = cutname+"_iso_data"
    cutnonisodataname = cutname+"_noniso_data"
    
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tauindex]!=0"
    cutnonisoMC = cut+" && isOS && !is_isolated  && LepCand_gen[tauindex]!=0"
    
    cutisoMCname = cutname+"_iso_realMC"
    cutnonisoMCname = cutname+"_noniso_realMC"

    hisST_noniso = gethisto_withFR_cate(dfST,ST,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisVV_noniso = gethisto_withFR_cate(dfVV,VV,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisTT_noniso = gethisto_withFR_cate(dfTT,TT,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisZTT_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoMC+"&& LepCand_gen[tauindex]==5",cutnonisoMCname+"_ZTT",weight,variable,channel)
    hisZLL_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoMC+"&& LepCand_gen[tauindex]!=5",cutnonisoMCname+"_ZLL",weight,variable,channel)
    
    data_noniso =  gethisto_withFR_cate(dfdata,data_obs,cutnonisodata,cutnonisodataname,"1",variable,channel)
    print("data")
    Fake = data_noniso.Clone("Fake")
    Fake.Add(hisST_noniso,-1)
    Fake.Add(hisVV_noniso,-1)
    Fake.Add(hisTT_noniso,-1)
    Fake.Add(hisZTT_noniso,-1)
    Fake.Add(hisZLL_noniso,-1)
    
    hisST_iso = gethisto_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable)
    hisVV_iso = gethisto_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable)
    hisTT_iso = gethisto_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable)
    hisZTT_iso = gethisto_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]==5",cutisoMCname+"_ZTT",weight,variable)
    hisZLL_iso = gethisto_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]!=5",cutisoMCname+"_ZLL",weight,variable)
    hisGGTT_iso = gethisto_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight,variable)
    data_iso =  gethisto_cate(dfdata,data_obs,cutisodata,cutisodataname,"1",variable)
    
    hisST_iso.SetName("ST")
    hisVV_iso.SetName("VV")
    hisTT_iso.SetName("TT")
    hisZTT_iso.SetName("ZTT")
    hisZLL_iso.SetName("ZLL")
    hisGGTT_iso.SetName("GGTT")
    data_iso.SetName("data_obs")
    for i in range(1,Fake.GetNbinsX()+1):
        if Fake.GetBinContent(i)<=0:
            Fake.SetBinContent(i,0)
            Fake.SetBinError(i,0)
        if hisST_iso.GetBinContent(i)<=0:
            hisST_iso.SetBinContent(i,0)
            hisST_iso.SetBinError(i,0) 
        if hisVV_iso.GetBinContent(i)<=0:
            hisVV_iso.SetBinContent(i,0)
            hisVV_iso.SetBinError(i,0) 
        if hisTT_iso.GetBinContent(i)<=0:
            hisTT_iso.SetBinContent(i,0)
            hisTT_iso.SetBinError(i,0) 
        if hisZTT_iso.GetBinContent(i)<=0:
            hisZTT_iso.SetBinContent(i,0)
            hisZTT_iso.SetBinError(i,0) 
        if hisZLL_iso.GetBinContent(i)<=0:
            hisZLL_iso.SetBinContent(i,0)
            hisZLL_iso.SetBinError(i,0) 
        if hisGGTT_iso.GetBinContent(i)<=0:
            hisGGTT_iso.SetBinContent(i,0)
            hisGGTT_iso.SetBinError(i,0) 
    
    return hisST_iso,hisVV_iso,hisTT_iso, hisZTT_iso,hisZLL_iso,hisGGTT_iso,Fake,data_iso


mvis = variable("mvis","m_{vis}",int(32),np.array([0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,400,500],dtype=float))
taupt = variable("taupt","#tau p_{T}",int(34),np.array([30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,84,88,92,96,100,105,110,115,120],dtype=float))
mupt = variable("mupt","#mu p_{T}",int(39),np.array([20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,84,88,92,96,100,105,110,115,120],dtype=float))
Aco = variable("Acopl","acoplanarity",int(40),np.arange(0,1.025,0.025,dtype=float))
mtranse = variable("mtrans","m_{T}(#mu,MET)",int(36),np.arange(0,185,5,dtype=float))
nTrk = variable("nTrk","N_{tracks}",int(50),np.arange(0,102,2,dtype=float))
MET = variable("MET_pt","MET",int(19),np.array([0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120],dtype=float))
taueta = variable("taueta","#tau #eta", int(25), np.arange(-2.5,2.7,0.2,dtype=float))
mueta = variable("mueta","#mu #eta", int(25), np.arange(-2.5,2.7,0.2,dtype=float))
#variablelist = [mvis,taupt,mupt,Aco,mtranse]
variablelist = [mvis,taupt,mupt,Aco,mtranse,nTrk,MET,taueta,mueta]
for var in variablelist:
    if varname == var.name:
        fout = TFile("./inclusivefile/Inclusive_mutau_2018_{}.root".format(var.name),"recreate")
        fout.mkdir("full")
        cut = "nTrk>=0 && ((taupt>30 && isSingleMuonTrigger)||(taupt>32 && isMuonTauTrigger)) && mvis>40"
        if var.name!="mtrans":
            cut = cut + " && mtrans<75"
        print ("Begin to generate histo of variable ", var.name, " with cut ", cut)
        cutname = "Inclusive"
        histotuple = getallhisto_mutau(cut,"Inclusive",var)
        fout.cd("full")
        for histo in histotuple:
            histo.Write() 
        fout.Close()