import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,getdflist,gethisto_withFR_cate,gethisto_cate,gethisto_sys_singleweight_cate,gethisto_sys_doubleweight_cate,gethisto_cate_syssinglenewtaupt
from ROOT import TFile
import numpy as np
from math import sqrt

ST = cate("ST",["ST_t_top","ST_t_antitop","ST_tW_top","ST_tW_antitop"])
VV = cate("VV",["WW2L2Nu","WZ2Q2L","WZ3LNu","ZZ2Q2L","ZZ2L2Nu","ZZ4L"])
TT = cate("TT",["TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic"])
ZTT = cate("ZTT",["DY"])
GGTT = cate("GGTT",["GGToTauTau"])
GGWW = cate("GGWW",["GGToWW"])

dfST = getdflist(ST,"mutau")
dfVV = getdflist(VV,"mutau")
dfTT = getdflist(TT,"mutau")
dfZTT = getdflist(ZTT,"mutau")
dfGGTT = getdflist(GGTT,"mutau")
dfGGWW = getdflist(GGWW,"mutau")

    
data_obs = cate("data_obs",["SingleMuonA","SingleMuonB","SingleMuonC","SingleMuonD"])
dfdata = getdflist(data_obs,"mutau")


def setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso, hisZLL_iso,hisGGTT_iso,hisGGWW_iso,uncertainties_name):
    hisST_iso.SetName("ST{}".format(uncertainties_name))
    hisVV_iso.SetName("VV{}".format(uncertainties_name))
    hisTT_iso.SetName("TT{}".format(uncertainties_name))
    hisZTT_iso.SetName("ZTT{}".format(uncertainties_name))
    hisZLL_iso.SetName("ZLL{}".format(uncertainties_name))
    hisGGTT_iso.SetName("GGTT{}".format(uncertainties_name))
    hisGGWW_iso.SetName("GGWW{}".format(uncertainties_name))
    for i in range(1,hisGGTT_iso.GetNbinsX()+1):
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
        if hisGGWW_iso.GetBinContent(i)<=0:
            hisGGWW_iso.SetBinContent(i,0)
            hisGGWW_iso.SetBinError(i,0) 
    maxbin = hisGGTT_iso.GetNbinsX()
    
    hisST_iso.SetBinContent(maxbin, hisST_iso.GetBinContent(maxbin)+hisST_iso.GetBinContent(maxbin+1))
    hisST_iso.SetBinError(maxbin, sqrt(hisST_iso.GetBinError(maxbin)**2+hisST_iso.GetBinError(maxbin+1)**2))
    hisST_iso.SetBinContent(maxbin+1,0)
    hisST_iso.SetBinError(maxbin+1,0)

    hisVV_iso.SetBinContent(maxbin, hisVV_iso.GetBinContent(maxbin)+hisVV_iso.GetBinContent(maxbin+1))
    hisVV_iso.SetBinError(maxbin, sqrt(hisVV_iso.GetBinError(maxbin)**2+hisVV_iso.GetBinError(maxbin+1)**2))
    hisVV_iso.SetBinContent(maxbin+1,0)
    hisVV_iso.SetBinError(maxbin+1,0)

    hisTT_iso.SetBinContent(maxbin, hisTT_iso.GetBinContent(maxbin)+hisTT_iso.GetBinContent(maxbin+1))
    hisTT_iso.SetBinError(maxbin, sqrt(hisTT_iso.GetBinError(maxbin)**2+hisTT_iso.GetBinError(maxbin+1)**2))
    hisTT_iso.SetBinContent(maxbin+1,0)
    hisTT_iso.SetBinError(maxbin+1,0)

    hisZTT_iso.SetBinContent(maxbin, hisZTT_iso.GetBinContent(maxbin)+hisZTT_iso.GetBinContent(maxbin+1))
    hisZTT_iso.SetBinError(maxbin, sqrt(hisZTT_iso.GetBinError(maxbin)**2+hisZTT_iso.GetBinError(maxbin+1)**2))
    hisZTT_iso.SetBinContent(maxbin+1,0)
    hisZTT_iso.SetBinError(maxbin+1,0)
    
    
    hisZLL_iso.SetBinContent(maxbin, hisZLL_iso.GetBinContent(maxbin)+hisZLL_iso.GetBinContent(maxbin+1))
    hisZLL_iso.SetBinError(maxbin, sqrt(hisZLL_iso.GetBinError(maxbin)**2+hisZLL_iso.GetBinError(maxbin+1)**2))
    hisZLL_iso.SetBinContent(maxbin+1,0)
    hisZLL_iso.SetBinError(maxbin+1,0)
    
    hisGGTT_iso.SetBinContent(maxbin, hisGGTT_iso.GetBinContent(maxbin)+hisGGTT_iso.GetBinContent(maxbin+1))
    hisGGTT_iso.SetBinError(maxbin, sqrt(hisGGTT_iso.GetBinError(maxbin)**2+hisGGTT_iso.GetBinError(maxbin+1)**2))
    hisGGTT_iso.SetBinContent(maxbin+1,0)
    hisGGTT_iso.SetBinError(maxbin+1,0)

    hisGGWW_iso.SetBinContent(maxbin, hisGGWW_iso.GetBinContent(maxbin)+hisGGWW_iso.GetBinContent(maxbin+1))
    hisGGWW_iso.SetBinError(maxbin, sqrt(hisGGWW_iso.GetBinError(maxbin)**2+hisGGWW_iso.GetBinError(maxbin+1)**2))
    hisGGWW_iso.SetBinContent(maxbin+1,0)
    hisGGWW_iso.SetBinError(maxbin+1,0)

    return hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso,hisZLL_iso,hisGGTT_iso,hisGGWW_iso
    

def getallhisto_mutau_relaxDY(cut,DYshapecut,cutname,variable):
    channel="mutau"
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    
    cutisodata = cut+" && isOS && is_isolated"
    cutnonisodata = cut+" && isOS && !is_isolated"
    
    cutisodataname = cutname+"_iso_data"
    cutnonisodataname = cutname+"_noniso_data"
    
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tauindex]!=0"
    cutnonisoMC = cut+" && isOS && !is_isolated  && LepCand_gen[tauindex]!=0"
    
    cutisoMCname = cutname+"_iso_realMC"
    cutnonisoMCname = cutname+"_noniso_realMC"
    
    
    cutisoDYshape = DYshapecut+" && isOS && is_isolated  && LepCand_gen[tauindex]!=0"
    cutnonisoDYshape = DYshapecut+" && isOS && !is_isolated  && LepCand_gen[tauindex]!=0"
    
    cutisoDYshapename = cutname+"_iso_realDYshape"
    cutnonisoDYshapename = cutname+"_noniso_realDYshape"
    
    hisST_noniso = gethisto_withFR_cate(dfST,ST,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisVV_noniso = gethisto_withFR_cate(dfVV,VV,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisTT_noniso = gethisto_withFR_cate(dfTT,TT,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisZTT_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoMC+"&& LepCand_gen[tauindex]==5",cutnonisoMCname+"_ZTT",weight,variable,channel)
    hisZLL_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoMC+"&& LepCand_gen[tauindex]!=5",cutnonisoMCname+"_ZLL",weight,variable,channel)
    
    hisZTTshape_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoDYshape+"&& LepCand_gen[tauindex]==5",cutnonisoDYshapename+"_ZTT",weight,variable,channel)
    hisZLLshape_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoDYshape+"&& LepCand_gen[tauindex]!=5",cutnonisoDYshapename+"_ZLL",weight,variable,channel)
    
    SFnoniso_ZTT = hisZTT_noniso.Integral()/hisZTTshape_noniso.Integral()
    SFnoniso_ZLL = hisZLL_noniso.Integral()/hisZLLshape_noniso.Integral()
    
    hisZTT_noniso_relax = hisZTTshape_noniso.Clone()
    hisZTT_noniso_relax.Scale(SFnoniso_ZTT)
    
    hisZLL_noniso_relax = hisZLLshape_noniso.Clone()
    hisZLL_noniso_relax.Scale(SFnoniso_ZLL)
    
    data_noniso =  gethisto_withFR_cate(dfdata,data_obs,cutnonisodata,cutnonisodataname,"1",variable,channel)
    
    print("data")
    Fake = data_noniso.Clone("Fake")
    Fake.Add(hisST_noniso,-1)
    Fake.Add(hisVV_noniso,-1)
    Fake.Add(hisTT_noniso,-1)
    Fake.Add(hisZTT_noniso_relax,-1)
    Fake.Add(hisZLL_noniso_relax,-1)
    
    hisST_iso = gethisto_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable)
    hisVV_iso = gethisto_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable)
    hisTT_iso = gethisto_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable)
    
    hisZTT_iso = gethisto_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]==5",cutisoMCname+"_ZTT",weight,variable)
    hisZLL_iso = gethisto_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]!=5",cutisoMCname+"_ZLL",weight,variable)
    
    hisZTTshape_iso = gethisto_cate(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]==5",cutisoDYshapename+"_ZTT",weight,variable)
    hisZLLshape_iso = gethisto_cate(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]!=5",cutisoDYshapename+"_ZLL",weight,variable)
    
    SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
    SFiso_ZLL = hisZLL_iso.Integral()/hisZLLshape_iso.Integral()
    
    hisZTT_iso_relax = hisZTTshape_iso.Clone()
    hisZTT_iso_relax.Scale(SFiso_ZTT)
    
    hisZLL_iso_relax = hisZLLshape_iso.Clone()
    hisZLL_iso_relax.Scale(SFiso_ZLL)
    ##add inelastic-elastic SF for GGTT and GGWW
    weight_withSF = weight
    if "nTrk==0" in cut:
        weight_withSF = weight + "*2.65"
    elif "nTrk==1" in cut:
        weight_withSF = weight + "*1.87"
    hisGGTT_iso = gethisto_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable)
    hisGGWW_iso = gethisto_cate(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable)
    data_iso =  gethisto_cate(dfdata,data_obs,cutisodata,cutisodataname,"1",variable)
    
    hisST_iso.SetName("ST")
    hisVV_iso.SetName("VV")
    hisTT_iso.SetName("TT")
    hisZTT_iso_relax.SetName("ZTT")
    hisZLL_iso_relax.SetName("ZLL")
    hisGGTT_iso.SetName("GGTT")
    hisGGWW_iso.SetName("GGWW")
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
        if hisZTT_iso_relax.GetBinContent(i)<=0:
            hisZTT_iso_relax.SetBinContent(i,0)
            hisZTT_iso_relax.SetBinError(i,0) 
        if hisZLL_iso_relax.GetBinContent(i)<=0:
            hisZLL_iso_relax.SetBinContent(i,0)
            hisZLL_iso_relax.SetBinError(i,0) 
        if hisGGTT_iso.GetBinContent(i)<=0:
            hisGGTT_iso.SetBinContent(i,0)
            hisGGTT_iso.SetBinError(i,0) 
        if hisGGWW_iso.GetBinContent(i)<=0:
            hisGGWW_iso.SetBinContent(i,0)
            hisGGWW_iso.SetBinError(i,0) 
    maxbin = Fake.GetNbinsX()
    Fake.SetBinContent(maxbin, Fake.GetBinContent(maxbin)+Fake.GetBinContent(maxbin+1))
    Fake.SetBinError(maxbin, sqrt(Fake.GetBinError(maxbin)**2+Fake.GetBinError(maxbin+1)**2))
    Fake.SetBinContent(maxbin+1,0)
    Fake.SetBinError(maxbin+1,0)
    
    
    hisST_iso.SetBinContent(maxbin, hisST_iso.GetBinContent(maxbin)+hisST_iso.GetBinContent(maxbin+1))
    hisST_iso.SetBinError(maxbin, sqrt(hisST_iso.GetBinError(maxbin)**2+hisST_iso.GetBinError(maxbin+1)**2))
    hisST_iso.SetBinContent(maxbin+1,0)
    hisST_iso.SetBinError(maxbin+1,0)

    hisVV_iso.SetBinContent(maxbin, hisVV_iso.GetBinContent(maxbin)+hisVV_iso.GetBinContent(maxbin+1))
    hisVV_iso.SetBinError(maxbin, sqrt(hisVV_iso.GetBinError(maxbin)**2+hisVV_iso.GetBinError(maxbin+1)**2))
    hisVV_iso.SetBinContent(maxbin+1,0)
    hisVV_iso.SetBinError(maxbin+1,0)

    hisTT_iso.SetBinContent(maxbin, hisTT_iso.GetBinContent(maxbin)+hisTT_iso.GetBinContent(maxbin+1))
    hisTT_iso.SetBinError(maxbin, sqrt(hisTT_iso.GetBinError(maxbin)**2+hisTT_iso.GetBinError(maxbin+1)**2))
    hisTT_iso.SetBinContent(maxbin+1,0)
    hisTT_iso.SetBinError(maxbin+1,0)

    hisZTT_iso_relax.SetBinContent(maxbin, hisZTT_iso_relax.GetBinContent(maxbin)+hisZTT_iso_relax.GetBinContent(maxbin+1))
    hisZTT_iso_relax.SetBinError(maxbin, sqrt(hisZTT_iso_relax.GetBinError(maxbin)**2+hisZTT_iso_relax.GetBinError(maxbin+1)**2))
    hisZTT_iso_relax.SetBinContent(maxbin+1,0)
    hisZTT_iso_relax.SetBinError(maxbin+1,0)


    hisZLL_iso_relax.SetBinContent(maxbin, hisZLL_iso_relax.GetBinContent(maxbin)+hisZLL_iso_relax.GetBinContent(maxbin+1))
    hisZLL_iso_relax.SetBinError(maxbin, sqrt(hisZLL_iso_relax.GetBinError(maxbin)**2+hisZLL_iso_relax.GetBinError(maxbin+1)**2))
    hisZLL_iso_relax.SetBinContent(maxbin+1,0)
    hisZLL_iso_relax.SetBinError(maxbin+1,0)
    
    hisGGTT_iso.SetBinContent(maxbin, hisGGTT_iso.GetBinContent(maxbin)+hisGGTT_iso.GetBinContent(maxbin+1))
    hisGGTT_iso.SetBinError(maxbin, sqrt(hisGGTT_iso.GetBinError(maxbin)**2+hisGGTT_iso.GetBinError(maxbin+1)**2))
    hisGGTT_iso.SetBinContent(maxbin+1,0)
    hisGGTT_iso.SetBinError(maxbin+1,0)

    hisGGWW_iso.SetBinContent(maxbin, hisGGWW_iso.GetBinContent(maxbin)+hisGGWW_iso.GetBinContent(maxbin+1))
    hisGGWW_iso.SetBinError(maxbin, sqrt(hisGGWW_iso.GetBinError(maxbin)**2+hisGGWW_iso.GetBinError(maxbin+1)**2))
    hisGGWW_iso.SetBinContent(maxbin+1,0)
    hisGGWW_iso.SetBinError(maxbin+1,0)

    data_iso.SetBinContent(maxbin, data_iso.GetBinContent(maxbin)+data_iso.GetBinContent(maxbin+1))
    data_iso.SetBinError(maxbin, sqrt(data_iso.GetBinError(maxbin)**2+data_iso.GetBinError(maxbin+1)**2))
    data_iso.SetBinContent(maxbin+1,0)
    data_iso.SetBinError(maxbin+1,0)


    return hisST_iso,hisVV_iso,hisTT_iso, hisZTT_iso_relax, hisZLL_iso_relax,hisGGTT_iso,hisGGWW_iso,Fake,data_iso


def getsyshisto_mutau(cut,DYshapecut,cutname,variable):
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    #uncertainty that only need to add an additional weight
    uncertainties_singleweight = ["_CMS_tauid_stat1_dm0_yearDown","_CMS_tauid_stat1_dm0_yearUp","_CMS_tauid_stat1_dm1_yearDown","_CMS_tauid_stat1_dm1_yearUp","_CMS_tauid_stat1_dm10_yearDown","_CMS_tauid_stat1_dm10_yearUp","_CMS_tauid_stat1_dm11_yearDown","_CMS_tauid_stat1_dm11_yearUp",\
        "_CMS_tauid_stat2_dm0_yearDown","_CMS_tauid_stat2_dm0_yearUp","_CMS_tauid_stat2_dm1_yearDown","_CMS_tauid_stat2_dm1_yearUp","_CMS_tauid_stat2_dm10_yearDown","_CMS_tauid_stat2_dm10_yearUp","_CMS_tauid_stat2_dm11_yearDown","_CMS_tauid_stat2_dm11_yearUp", \
        "_CMS_tauid_syst_allerasDown", "_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_yearDown", "_CMS_tauid_syst_yearUp", 
        "_CMS_tauid_syst_dm0_yearDown","_CMS_tauid_syst_dm0_yearUp","_CMS_tauid_syst_dm1_yearDown","_CMS_tauid_syst_dm1_yearUp","_CMS_tauid_syst_dm10_yearDown","_CMS_tauid_syst_dm10_yearUp","_CMS_tauid_syst_dm11_yearDown","_CMS_tauid_syst_dm11_yearUp",\
        "_CMS_mutauFR_barrel_yearDown","_CMS_mutauFR_barrel_yearUp","_CMS_mutauFR_endcap_yearDown","_CMS_mutauFR_endcap_yearUp",\
        "_CMS_pileup_yearDown","_CMS_pileup_yearUp",\
        "_CMS_mutautrg_yearDown","_CMS_mutautrg_yearUp","_CMS_mutrg_yearDown","_CMS_mutrg_yearUp"\
        ]
    #uncertainties_singleweight = ["_CMS_pileup_yearDown","_CMS_pileup_yearUp"]
    
    #function_singleweight = ["Getpusysweight(puWeight,puWeightDown,npvs_weight,npvsDown_weight)",\
    #"Getpusysweight(puWeight,puWeightUp,npvs_weight,npvsUp_weight)"]
    
    function_singleweight = ["Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_down[tauindex])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_up[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_down[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_up[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_down[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_up[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_down[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert0_up[tauindex])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_down[tauindex])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_up[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_down[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_up[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_down[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_up[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_down[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_uncert1_up[tauindex])",\
        "Gettauidsysweight(LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_alleras_down[tauindex])",\
        "Gettauidsysweight(LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_alleras_up[tauindex])",\
        "Gettauidsysweight(LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_era_down[tauindex])",\
        "Gettauidsysweight(LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_era_up[tauindex])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_down[tauindex])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_up[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_down[tauindex])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_up[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_down[tauindex])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_up[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_down[tauindex])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_tauidMsf[tauindex],LepCand_tauidMsf_syst_dm_era_up[tauindex])",\
        "Gettauantimusysweight(true,LepCand_gen[tauindex],LepCand_antimusf[tauindex], LepCand_antimusf_down[tauindex],taueta)",\
        "Gettauantimusysweight(true,LepCand_gen[tauindex],LepCand_antimusf[tauindex], LepCand_antimusf_up[tauindex],taueta)",\
        "Gettauantimusysweight(false,LepCand_gen[tauindex],LepCand_antimusf[tauindex], LepCand_antimusf_down[tauindex],taueta)",\
        "Gettauantimusysweight(false,LepCand_gen[tauindex],LepCand_antimusf[tauindex], LepCand_antimusf_up[tauindex],taueta)",\
        "Getpusysweight(puWeight,puWeightDown,npvs_weight,npvsDown_weight)",\
        "Getpusysweight(puWeight,puWeightUp,npvs_weight,npvsUp_weight)", \
        "Getmutautrgweight(isMuonTauTrigger,LepCand_tautriggersf[tauindex],LepCand_tautriggersf_down[tauindex])",\
        "Getmutautrgweight(isMuonTauTrigger,LepCand_tautriggersf[tauindex],LepCand_tautriggersf_up[tauindex])",\
        "Getsinglemutrgweight(isSingleMuonTrigger,0.98)",\
        "Getsinglemutrgweight(isSingleMuonTrigger,1.02)",
        ]

    
    #uncertainty that will change taupt so that change mvis
    uncertainties_newtaupt = ["_CMS_taues_dm0_yearDown","_CMS_taues_dm0_yearUp","_CMS_taues_dm1_yearDown","_CMS_taues_dm1_yearUp","_CMS_taues_3prong_yearDown","_CMS_taues_3prong_yearUp"]
    function_newtaupt_tau = ["Gettauessys(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_down[tauindex],my_tau)",\
        "Gettauessys(0,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_up[tauindex],my_tau)",\
        "Gettauessys(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_down[tauindex],my_tau)",\
        "Gettauessys(1,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_up[tauindex],my_tau)",\
        "Gettauessys(10,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_down[tauindex],my_tau)",\
        "Gettauessys(11,LepCand_DecayMode[tauindex],LepCand_gen[tauindex],LepCand_taues[tauindex],LepCand_taues_up[tauindex],my_tau)",\
        ]
    channel="mutau"
    
    SThisto = []
    VVhisto = []
    TThisto = []
    ZTThisto = []
    ZLLhisto = []
    GGTThisto = []
    GGWWhisto = []
    
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tauindex]!=0"
    cutnonisoMC = cut+" && isOS && !is_isolated  && LepCand_gen[tauindex]!=0"
    
    cutisoMCname = cutname+"_iso_realMC"
    cutnonisoMCname = cutname+"_noniso_realMC"
    
    
    cutisoDYshape = DYshapecut+" && isOS && is_isolated  && LepCand_gen[tauindex]!=0"
    cutnonisoDYshape = DYshapecut+" && isOS && !is_isolated  && LepCand_gen[tauindex]!=0"
    
    cutisoDYshapename = cutname+"_iso_realDYshape"
    cutnonisoDYshapename = cutname+"_noniso_realDYshape"
    
    for i in range(len(uncertainties_singleweight)):
    #for i in range(4,5):
        uncertainties_name = str.replace(uncertainties_singleweight[i],"year","2018")
        print ("begin to get syshisto ", uncertainties_name)
        print ("func : ", function_singleweight[i])
        
        func  = function_singleweight[i]
        cutisoMCname = cutisoMCname + uncertainties_name
        cutisoDYshapename = cutisoDYshapename + uncertainties_name
        
        hisST_iso = gethisto_sys_singleweight_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable,func)
        hisVV_iso = gethisto_sys_singleweight_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable,func)
        hisTT_iso = gethisto_sys_singleweight_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable,func)
        
        hisZTT_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]==5",cutisoMCname+"_ZTT",weight,variable,func)
        hisZLL_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]!=5",cutisoMCname+"_ZLL",weight,variable,func)

        hisZTTshape_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]==5",cutisoDYshapename+"_ZTT",weight,variable,func)
        hisZLLshape_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]!=5",cutisoDYshapename+"_ZLL",weight,variable,func)
        
        SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
        SFiso_ZLL = hisZLL_iso.Integral()/hisZLLshape_iso.Integral()
        
        hisZTT_iso_relax = hisZTTshape_iso.Clone()
        hisZTT_iso_relax.Scale(SFiso_ZTT)

        hisZLL_iso_relax = hisZLLshape_iso.Clone()
        hisZLL_iso_relax.Scale(SFiso_ZLL)

        weight_withSF = weight
        if "nTrk==0" in cut:
            weight_withSF = weight + "*2.65"
        elif "nTrk==1" in cut:
            weight_withSF = weight + "*1.87"
            
        hisGGTT_iso = gethisto_sys_singleweight_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        hisGGWW_iso = gethisto_sys_singleweight_cate(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        
        hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisZLL_iso_relax,hisGGTT_iso,hisGGWW_iso = setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisZLL_iso_relax,hisGGTT_iso,hisGGWW_iso,uncertainties_name)
        
        SThisto.append(hisST_iso)
        VVhisto.append(hisVV_iso)
        TThisto.append(hisTT_iso)
        ZTThisto.append(hisZTT_iso_relax)
        ZLLhisto.append(hisZLL_iso_relax)
        GGTThisto.append(hisGGTT_iso)
        GGWWhisto.append(hisGGWW_iso)


    #sys.exit(0)
    for i in range(len(uncertainties_newtaupt)):
        uncertainties_name = str.replace(uncertainties_newtaupt[i],"year","2018")
        print ("begin to get syshisto ", uncertainties_name)
        print ("func : ", function_newtaupt_tau[i])
        func  = function_newtaupt_tau[i]
        cutisoMCname = cutisoMCname + uncertainties_name
        cutisoDYshapename = cutisoDYshapename + uncertainties_name
        hisST_iso = gethisto_cate_syssinglenewtaupt(dfST,ST,cutisoMC,cutisoMCname,weight,variable,func)
        hisVV_iso = gethisto_cate_syssinglenewtaupt(dfVV,VV,cutisoMC,cutisoMCname,weight,variable,func)
        hisTT_iso = gethisto_cate_syssinglenewtaupt(dfTT,TT,cutisoMC,cutisoMCname,weight,variable,func)
        
        hisZTT_iso = gethisto_cate_syssinglenewtaupt(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]==5",cutisoMCname+"_ZTT",weight,variable,func)
        hisZLL_iso = gethisto_cate_syssinglenewtaupt(dfZTT,ZTT,cutisoMC+"&& LepCand_gen[tauindex]!=5",cutisoMCname+"_ZLL",weight,variable,func)
        
        hisZTTshape_iso = gethisto_cate_syssinglenewtaupt(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]==5",cutisoDYshapename+"_ZTT",weight,variable,func)
        hisZLLshape_iso = gethisto_cate_syssinglenewtaupt(dfZTT,ZTT,cutisoDYshape+"&& LepCand_gen[tauindex]!=5",cutisoDYshapename+"_ZLL",weight,variable,func)
        
        SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
        SFiso_ZLL = hisZLL_iso.Integral()/hisZLLshape_iso.Integral()

        hisZTT_iso_relax = hisZTTshape_iso.Clone()
        hisZTT_iso_relax.Scale(SFiso_ZTT)

        hisZLL_iso_relax = hisZLLshape_iso.Clone()
        hisZLL_iso_relax.Scale(SFiso_ZLL)

        weight_withSF = weight
        if "nTrk==0" in cut:
            weight_withSF = weight + "*2.65"
        elif "nTrk==1" in cut:
            weight_withSF = weight + "*1.87"
        
        hisGGTT_iso = gethisto_cate_syssinglenewtaupt(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        hisGGWW_iso = gethisto_cate_syssinglenewtaupt(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        
        hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisZLL_iso_relax,hisGGTT_iso,hisGGWW_iso = setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisZLL_iso_relax,hisGGTT_iso,hisGGWW_iso,uncertainties_name)
        
        SThisto.append(hisST_iso)
        VVhisto.append(hisVV_iso)
        TThisto.append(hisTT_iso)
        ZTThisto.append(hisZTT_iso_relax)
        ZLLhisto.append(hisZLL_iso_relax)
        GGTThisto.append(hisGGTT_iso)
        GGWWhisto.append(hisGGWW_iso)
    
    return SThisto, VVhisto, TThisto, ZTThisto,ZLLhisto,GGWWhisto,GGTThisto



mvis = variable("mvis","m_{vis}",int(8),np.array([40,55,70,85,100,150,200,350,500],dtype=float)) 

fout = TFile("./Taug2_mutau_2018.root","recreate")

fout.mkdir("mt_0")
fout.mkdir("mt_1")


mt_0cut = "(nTrk==0) && (Acopl<0.02) && ((taupt>30 && isSingleMuonTrigger)||(taupt>32 && isMuonTauTrigger)) && mvis>40 && mtrans<75 "
mt_1cut = "(nTrk==1) && (Acopl<0.02) && ((taupt>30 && isSingleMuonTrigger)||(taupt>32 && isMuonTauTrigger)) && mvis>40 && mtrans<75"

DYshapecut = "(nTrk<10) && (Acopl<0.02) && ((taupt>30 && isSingleMuonTrigger)||(taupt>32 && isMuonTauTrigger)) && mvis>40 && mtrans<75"

mt_0_histotuple = getallhisto_mutau_relaxDY(mt_0cut,DYshapecut,"mt_0",mvis)
mt_0_systuple = getsyshisto_mutau(mt_0cut,DYshapecut,"mt_0",mvis)
fout.cd("mt_0")
for histo in mt_0_histotuple:
    histo.Write()
for hislist in mt_0_systuple:
    for histo in hislist:
        histo.Write()
        
mt_1_histotuple = getallhisto_mutau_relaxDY(mt_1cut,DYshapecut,"mt_1",mvis)
mt_1_systuple = getsyshisto_mutau(mt_1cut,DYshapecut,"mt_1",mvis)
fout.cd("mt_1")
for histo in mt_1_histotuple:
    histo.Write()
for hislist in mt_1_systuple:
    for histo in hislist:
        histo.Write()
fout.Close()