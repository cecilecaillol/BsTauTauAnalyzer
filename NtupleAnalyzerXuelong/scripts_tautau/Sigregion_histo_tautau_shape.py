import sys
sys.path.append("..")
from pyFunc.gethisto import variable,cate,getdflist,gethisto_withFR_cate,gethisto_cate,gethisto_sys_singleweight_cate,gethisto_sys_doubleweight_cate,gethisto_cate_sysdoublenewtaupt
from ROOT import TFile
import numpy as np
from math import sqrt

ST = cate("ST",["ST_t_top","ST_t_antitop","ST_tW_top","ST_tW_antitop"])
VV = cate("VV",["WW2L2Nu","WZ2Q2L","WZ3LNu","ZZ2Q2L","ZZ2L2Nu","ZZ4L"])
TT = cate("TT",["TTTo2L2Nu","TTToHadronic","TTToSemiLeptonic"])
ZTT = cate("ZTT",["DY"])
GGTT = cate("GGTT",["GGToTauTau"])
GGWW = cate("GGWW",["GGToWW"])

dfST = getdflist(ST,"tautau")
dfVV = getdflist(VV,"tautau")
dfTT = getdflist(TT,"tautau")
dfZTT = getdflist(ZTT,"tautau")
dfGGTT = getdflist(GGTT,"tautau")
dfGGWW = getdflist(GGWW,"tautau")

    
data_obs = cate("data_obs",["TauA","TauB","TauC","TauD"])
dfdata = getdflist(data_obs,"tautau")


def setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso,hisGGTT_iso,hisGGWW_iso,uncertainties_name):
    hisST_iso.SetName("ST{}".format(uncertainties_name))
    hisVV_iso.SetName("VV{}".format(uncertainties_name))
    hisTT_iso.SetName("TT{}".format(uncertainties_name))
    hisZTT_iso.SetName("ZTT{}".format(uncertainties_name))
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
    
    hisGGTT_iso.SetBinContent(maxbin, hisGGTT_iso.GetBinContent(maxbin)+hisGGTT_iso.GetBinContent(maxbin+1))
    hisGGTT_iso.SetBinError(maxbin, sqrt(hisGGTT_iso.GetBinError(maxbin)**2+hisGGTT_iso.GetBinError(maxbin+1)**2))
    hisGGTT_iso.SetBinContent(maxbin+1,0)
    hisGGTT_iso.SetBinError(maxbin+1,0)

    hisGGWW_iso.SetBinContent(maxbin, hisGGWW_iso.GetBinContent(maxbin)+hisGGWW_iso.GetBinContent(maxbin+1))
    hisGGWW_iso.SetBinError(maxbin, sqrt(hisGGWW_iso.GetBinError(maxbin)**2+hisGGWW_iso.GetBinError(maxbin+1)**2))
    hisGGWW_iso.SetBinContent(maxbin+1,0)
    hisGGWW_iso.SetBinError(maxbin+1,0)

    return hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso,hisGGTT_iso,hisGGWW_iso
    

def getallhisto_tautau_relaxDY(cut,DYshapecut,cutname,variable):
    channel="tautau"
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    
    cutisodata = cut+" && isOS && is_isolated"
    cutnonisodata = cut+" && isOS && !is_isolated"
    
    cutisodataname = cutname+"_iso_data"
    cutnonisodataname = cutname+"_noniso_data"
    
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tau2index]!=0"
    cutnonisoMC = cut+" && isOS && !is_isolated  && LepCand_gen[tau2index]!=0"
    
    cutisoMCname = cutname+"_iso_realMC"
    cutnonisoMCname = cutname+"_noniso_realMC"
    
    
    cutisoDYshape = DYshapecut+" && isOS && is_isolated  && LepCand_gen[tau2index]!=0"
    cutnonisoDYshape = DYshapecut+" && isOS && !is_isolated  && LepCand_gen[tau2index]!=0"
    
    cutisoDYshapename = cutname+"_iso_realDYshape"
    cutnonisoDYshapename = cutname+"_noniso_realDYshape"
    
    hisST_noniso = gethisto_withFR_cate(dfST,ST,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisVV_noniso = gethisto_withFR_cate(dfVV,VV,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisTT_noniso = gethisto_withFR_cate(dfTT,TT,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisZTT_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoMC,cutnonisoMCname,weight,variable,channel)

    hisZTTshape_noniso = gethisto_withFR_cate(dfZTT,ZTT,cutnonisoDYshape,cutnonisoDYshapename,weight,variable,channel)

    SFnoniso_ZTT = hisZTT_noniso.Integral()/hisZTTshape_noniso.Integral()
    
    hisZTT_noniso_relax = hisZTTshape_noniso.Clone()
    hisZTT_noniso_relax.Scale(SFnoniso_ZTT)
    
    data_noniso =  gethisto_withFR_cate(dfdata,data_obs,cutnonisodata,cutnonisodataname,"1",variable,channel)
    
    print("data")
    Fake = data_noniso.Clone("Fake")
    Fake.Add(hisST_noniso,-1)
    Fake.Add(hisVV_noniso,-1)
    Fake.Add(hisTT_noniso,-1)
    Fake.Add(hisZTT_noniso_relax,-1)
    
    hisST_iso = gethisto_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable)
    hisVV_iso = gethisto_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable)
    hisTT_iso = gethisto_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable)
    
    hisZTT_iso = gethisto_cate(dfZTT,ZTT,cutisoMC,cutisoMCname,weight,variable)

    hisZTTshape_iso = gethisto_cate(dfZTT,ZTT,cutisoDYshape,cutisoDYshapename,weight,variable)

    SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
    
    hisZTT_iso_relax = hisZTTshape_iso.Clone()
    hisZTT_iso_relax.Scale(SFiso_ZTT)
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


    return hisST_iso,hisVV_iso,hisTT_iso, hisZTT_iso_relax, hisGGTT_iso,hisGGWW_iso,Fake,data_iso


def getsyshisto_tautau(cut,DYshapecut,cutname,variable):
    weight = "xsweight*SFweight*Acoweight*npvs_weight*nPUtrkweight*nHStrkweight"
    #uncertainty that only need to add an additional weight
    uncertainties_doubleweight = ["_CMS_tauid_stat1_dm0_yearDown","_CMS_tauid_stat1_dm0_yearUp","_CMS_tauid_stat1_dm1_yearDown","_CMS_tauid_stat1_dm1_yearUp","_CMS_tauid_stat1_dm10_yearDown","_CMS_tauid_stat1_dm10_yearUp","_CMS_tauid_stat1_dm11_yearDown","_CMS_tauid_stat1_dm11_yearUp",\
        "_CMS_tauid_stat2_dm0_yearDown","_CMS_tauid_stat2_dm0_yearUp","_CMS_tauid_stat2_dm1_yearDown","_CMS_tauid_stat2_dm1_yearUp","_CMS_tauid_stat2_dm10_yearDown","_CMS_tauid_stat2_dm10_yearUp","_CMS_tauid_stat2_dm11_yearDown","_CMS_tauid_stat2_dm11_yearUp", \
        "_CMS_tauid_syst_allerasDown", "_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_yearDown", "_CMS_tauid_syst_yearUp", 
        "_CMS_tauid_syst_dm0_yearDown","_CMS_tauid_syst_dm0_yearUp","_CMS_tauid_syst_dm1_yearDown","_CMS_tauid_syst_dm1_yearUp","_CMS_tauid_syst_dm10_yearDown","_CMS_tauid_syst_dm10_yearUp","_CMS_tauid_syst_dm11_yearDown","_CMS_tauid_syst_dm11_yearUp",\
        "_CMS_ditautrg_yearDown","_CMS_ditautrg_yearUp"]
    uncertainties_singleweight = ["_CMS_pileup_yearDown","_CMS_pileup_yearUp"]
    
    function_singleweight = ["Getpusysweight(puWeight,puWeightDown,npvs_weight,npvsDown_weight)",\
    "Getpusysweight(puWeight,puWeightUp,npvs_weight,npvsUp_weight)"]
    
    function_weight_tau1 = ["Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_down[tau1index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_up[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_down[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_up[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_down[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_up[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_down[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert0_up[tau1index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_down[tau1index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_up[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_down[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_up[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_down[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_up[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_down[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_uncert1_up[tau1index])",\
        "Gettauidsysweight(LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_alleras_down[tau1index])",\
        "Gettauidsysweight(LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_alleras_up[tau1index])",\
        "Gettauidsysweight(LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_era_down[tau1index])",\
        "Gettauidsysweight(LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_era_up[tau1index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_down[tau1index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_up[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_down[tau1index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_up[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_down[tau1index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_up[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_down[tau1index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_tauidMsf[tau1index],LepCand_tauidMsf_syst_dm_era_up[tau1index])",\
        "Getditautrigweight(LepCand_tautriggersf[tau1index],LepCand_tautriggersf_down[tau1index])",\
        "Getditautrigweight(LepCand_tautriggersf[tau1index],LepCand_tautriggersf_up[tau1index])"
        ]
    
    function_weight_tau2 = ["Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_down[tau2index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_up[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_down[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_up[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_down[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_up[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_down[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert0_up[tau2index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_down[tau2index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_up[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_down[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_up[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_down[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_up[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_down[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_uncert1_up[tau2index])",\
        "Gettauidsysweight(LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_alleras_down[tau2index])",\
        "Gettauidsysweight(LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_alleras_up[tau2index])",\
        "Gettauidsysweight(LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_era_down[tau2index])",\
        "Gettauidsysweight(LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_era_up[tau2index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_down[tau2index])",\
        "Gettauidsysweight_dm(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_up[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_down[tau2index])",\
        "Gettauidsysweight_dm(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_up[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_down[tau2index])",\
        "Gettauidsysweight_dm(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_up[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_down[tau2index])",\
        "Gettauidsysweight_dm(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_tauidMsf[tau2index],LepCand_tauidMsf_syst_dm_era_up[tau2index])",\
        "Getditautrigweight(LepCand_tautriggersf[tau2index],LepCand_tautriggersf_down[tau2index])",\
        "Getditautrigweight(LepCand_tautriggersf[tau2index],LepCand_tautriggersf_up[tau2index])"
        ]
    
    #uncertainty that will change taupt so that change mvis
    uncertainties_newtaupt = ["_CMS_taues_dm0_yearDown","_CMS_taues_dm0_yearUp","_CMS_taues_dm1_yearDown","_CMS_taues_dm1_yearUp","_CMS_taues_3prong_yearDown","_CMS_taues_3prong_yearUp"]
    
    
    function_newtaupt_tau1 = ["Gettauessys(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_down[tau1index],my_tau1)",\
        "Gettauessys(0,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_up[tau1index],my_tau1)",\
        "Gettauessys(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_down[tau1index],my_tau1)",\
        "Gettauessys(1,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_up[tau1index],my_tau1)",\
        "Gettauessys(10,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_down[tau1index],my_tau1)",\
        "Gettauessys(11,LepCand_DecayMode[tau1index],LepCand_gen[tau1index],LepCand_taues[tau1index],LepCand_taues_up[tau1index],my_tau1)",\
        ]
    
    function_newtaupt_tau2 = ["Gettauessys(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_down[tau2index],my_tau2)",\
        "Gettauessys(0,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_up[tau2index],my_tau2)",\
        "Gettauessys(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_down[tau2index],my_tau2)",\
        "Gettauessys(1,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_up[tau2index],my_tau2)",\
        "Gettauessys(10,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_down[tau2index],my_tau2)",\
        "Gettauessys(11,LepCand_DecayMode[tau2index],LepCand_gen[tau2index],LepCand_taues[tau2index],LepCand_taues_up[tau2index],my_tau2)",\
        ]
    channel="tautau"
    
    SThisto = []
    VVhisto = []
    TThisto = []
    ZTThisto = []
    GGTThisto = []
    GGWWhisto = []
    
    cutisoMC = cut+" && isOS && is_isolated  && LepCand_gen[tau2index]!=0"
    cutnonisoMC = cut+" && isOS && !is_isolated  && LepCand_gen[tau2index]!=0"
    
    cutisoMCname = cutname+"_iso_realMC"
    cutnonisoMCname = cutname+"_noniso_realMC"
    
    
    cutisoDYshape = DYshapecut+" && isOS && is_isolated  && LepCand_gen[tau2index]!=0"
    cutnonisoDYshape = DYshapecut+" && isOS && !is_isolated  && LepCand_gen[tau2index]!=0"
    
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
        
        #hisZTTshape_iso = gethisto_sys_singleweight_cate(ZTT,cutisoDYshape+"&& LepCand_gen[tau2index]==5",cutisoDYshapename+"_ZTT",weight,variable,func)
        hisST_iso = gethisto_sys_singleweight_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable,func)
        hisVV_iso = gethisto_sys_singleweight_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable,func)
        hisTT_iso = gethisto_sys_singleweight_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable,func)
        
        hisZTT_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoMC,cutisoMCname+"_ZTT",weight,variable,func)

        hisZTTshape_iso = gethisto_sys_singleweight_cate(dfZTT,ZTT,cutisoDYshape,cutisoDYshapename+"_ZTT",weight,variable,func)

        SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
        
        hisZTT_iso_relax = hisZTTshape_iso.Clone()
        hisZTT_iso_relax.Scale(SFiso_ZTT)

        weight_withSF = weight
        if "nTrk==0" in cut:
            weight_withSF = weight + "*2.65"
        elif "nTrk==1" in cut:
            weight_withSF = weight + "*1.87"
            
        hisGGTT_iso = gethisto_sys_singleweight_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        hisGGWW_iso = gethisto_sys_singleweight_cate(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable,func)
        
        hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso = setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso,uncertainties_name)
        
        SThisto.append(hisST_iso)
        VVhisto.append(hisVV_iso)
        TThisto.append(hisTT_iso)
        ZTThisto.append(hisZTT_iso_relax)
        GGTThisto.append(hisGGTT_iso)
        GGWWhisto.append(hisGGWW_iso)
        
        


    for i in range(len(uncertainties_doubleweight)):
    #for i in range(4,5):
        uncertainties_name = str.replace(uncertainties_doubleweight[i],"year","2018")
        print ("begin to get syshisto ", uncertainties_name)
        print ("func1 : ", function_weight_tau1[i])
        print ("func2 : ", function_weight_tau2[i])
        
        func1  = function_weight_tau1[i]
        func2  = function_weight_tau2[i]
        cutisoMCname = cutisoMCname + uncertainties_name
        cutisoDYshapename = cutisoDYshapename + uncertainties_name
        
        hisST_iso = gethisto_sys_doubleweight_cate(dfST,ST,cutisoMC,cutisoMCname,weight,variable,func1, func2)
        hisVV_iso = gethisto_sys_doubleweight_cate(dfVV,VV,cutisoMC,cutisoMCname,weight,variable,func1, func2)
        hisTT_iso = gethisto_sys_doubleweight_cate(dfTT,TT,cutisoMC,cutisoMCname,weight,variable,func1, func2)
        
        hisZTT_iso = gethisto_sys_doubleweight_cate(dfZTT,ZTT,cutisoMC,cutisoMCname+"_ZTT",weight,variable,func1, func2)

        hisZTTshape_iso = gethisto_sys_doubleweight_cate(dfZTT,ZTT,cutisoDYshape,cutisoDYshapename+"_ZTT",weight,variable,func1, func2)

        SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
        
        hisZTT_iso_relax = hisZTTshape_iso.Clone()
        hisZTT_iso_relax.Scale(SFiso_ZTT)
        
        weight_withSF = weight
        if "nTrk==0" in cut:
            weight_withSF = weight + "*2.65"
        elif "nTrk==1" in cut:
            weight_withSF = weight + "*1.87"
            
        hisGGTT_iso = gethisto_sys_doubleweight_cate(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable,func1, func2)
        hisGGWW_iso = gethisto_sys_doubleweight_cate(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable,func1, func2)
        
        hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso = setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso,uncertainties_name)
        
        SThisto.append(hisST_iso)
        VVhisto.append(hisVV_iso)
        TThisto.append(hisTT_iso)
        ZTThisto.append(hisZTT_iso_relax)
        GGTThisto.append(hisGGTT_iso)
        GGWWhisto.append(hisGGWW_iso)


    #sys.exit(0)
    for i in range(len(uncertainties_newtaupt)):
        uncertainties_name = str.replace(uncertainties_newtaupt[i],"year","2018")
        print ("begin to get syshisto ", uncertainties_name)
        print ("func1 : ", function_newtaupt_tau1[i])
        print ("func2 : ", function_newtaupt_tau2[i])
        func1  = function_newtaupt_tau1[i]
        func2  = function_newtaupt_tau2[i]
        cutisoMCname = cutisoMCname + uncertainties_name
        cutisoDYshapename = cutisoDYshapename + uncertainties_name
        hisST_iso = gethisto_cate_sysdoublenewtaupt(dfST,ST,cutisoMC,cutisoMCname,weight,variable,func1,func2)
        hisVV_iso = gethisto_cate_sysdoublenewtaupt(dfVV,VV,cutisoMC,cutisoMCname,weight,variable,func1,func2)
        hisTT_iso = gethisto_cate_sysdoublenewtaupt(dfTT,TT,cutisoMC,cutisoMCname,weight,variable,func1,func2)
        
        hisZTT_iso = gethisto_cate_sysdoublenewtaupt(dfZTT,ZTT,cutisoMC,cutisoMCname+"_ZTT",weight,variable,func1,func2)

        hisZTTshape_iso = gethisto_cate_sysdoublenewtaupt(dfZTT,ZTT,cutisoDYshape,cutisoDYshapename+"_ZTT",weight,variable,func1,func2)

        SFiso_ZTT = hisZTT_iso.Integral()/hisZTTshape_iso.Integral()
        
        hisZTT_iso_relax = hisZTTshape_iso.Clone()
        hisZTT_iso_relax.Scale(SFiso_ZTT)

        weight_withSF = weight
        if "nTrk==0" in cut:
            weight_withSF = weight + "*2.65"
        elif "nTrk==1" in cut:
            weight_withSF = weight + "*1.87"
        
        hisGGTT_iso = gethisto_cate_sysdoublenewtaupt(dfGGTT,GGTT,cutisoMC,cutisoMCname,weight_withSF,variable,func1,func2)
        hisGGWW_iso = gethisto_cate_sysdoublenewtaupt(dfGGWW,GGWW,cutisoMC,cutisoMCname,weight_withSF,variable,func1,func2)
        
        hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso = setallisohisto(hisST_iso,hisVV_iso,hisTT_iso,hisZTT_iso_relax,hisGGTT_iso,hisGGWW_iso,uncertainties_name)
        
        SThisto.append(hisST_iso)
        VVhisto.append(hisVV_iso)
        TThisto.append(hisTT_iso)
        ZTThisto.append(hisZTT_iso_relax)
        GGTThisto.append(hisGGTT_iso)
        GGWWhisto.append(hisGGWW_iso)
    
    return SThisto, VVhisto, TThisto, ZTThisto,GGWWhisto,GGTThisto



mvis = variable("mvis","m_{vis}",int(8),np.array([40,55,70,85,100,150,200,350,500],dtype=float)) 

fout = TFile("./Taug2_tautau_2018.root","recreate")

fout.mkdir("tt_0")
fout.mkdir("tt_1")


tt_0cut = "(nTrk==0) && (Acopl<0.02) && tau1pt>40 && tau2pt>40 && mvis>40"
tt_1cut = "(nTrk==1) && (Acopl<0.02) && tau1pt>40 && tau2pt>40 && mvis>40"
DYshapecut = "(nTrk<10) && (Acopl<0.02) && tau1pt>40 && tau2pt>40 && mvis>40"

tt_0_histotuple = getallhisto_tautau_relaxDY(tt_0cut,DYshapecut,"tt_0",mvis)
tt_0_systuple = getsyshisto_tautau(tt_0cut,DYshapecut,"tt_0",mvis)
fout.cd("tt_0")
for histo in tt_0_histotuple:
    histo.Write()
for hislist in tt_0_systuple:
    for histo in hislist:
        histo.Write()
        
tt_1_histotuple = getallhisto_tautau_relaxDY(tt_1cut,DYshapecut,"tt_1",mvis)
tt_1_systuple = getsyshisto_tautau(tt_1cut,DYshapecut,"tt_1",mvis)
fout.cd("tt_1")
for histo in tt_1_histotuple:
    histo.Write()
for hislist in tt_1_systuple:
    for histo in hislist:
        histo.Write()
fout.Close()