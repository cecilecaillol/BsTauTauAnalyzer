from ROOT import RDataFrame, TFile, TChain, TTree, TFile, TH1D, TLorentzVector,TCanvas
import numpy as np
import sys
from math import cos,sin,sqrt,pi
import ROOT
import time as timer
time_start=timer.time()
ROOT.gInterpreter.AddIncludePath('/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/lib')
ROOT.gInterpreter.Declare('#include "basic_sel.h"')
ROOT.gInterpreter.Declare('#include "GetPFtrk.h"')
ROOT.gInterpreter.Declare('#include "Correction.h"')
ROOT.gInterpreter.Declare('#include "ApplyFR.h"')
ROOT.gSystem.Load('/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/lib/RDFfunc.so')




### this code is used to perform basic selection on ntuples after nanoaod analyzer
### year: 2016, 2017, 2018
### name: name of ntuple after analyzer
### sample: output root file name
year = sys.argv[1]
sample = sys.argv[2]
#name = sys.argv[3]

print ("year is ", year , " sample is ", sample)

#fout = TFile("/eos/cms/store/user/xuqin/taug-2/ntuple_after_basicsel/{}.root".format(sample),"recreate")
#fout = TFile("/eos/cms/store/cmst3/group/taug2/AnalysisXuelong/ntuple_after_basicsel/{}.root".format(sample),"recreate")
'''arbre = TChain("Events")
arbre2 = TChain("Runs")
arbre.Add("/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuple_after_analyzer/mutau/{}/*.root".format(name))
arbre2.Add("/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuple_after_analyzer/mutau/{}/*.root".format(name))
'''
ngen = 0.
isdata = True
isW = False

#For W sample, we use genEventCount and don't consider genweight
#For others, we use genEventsSumw and consider genweight
if (sample=="W" or sample=="W1" or sample=="W2" or sample=="W3" or sample=="W4"):
    isW=True

if (sample!="SingleMuonA" and sample!="SingleMuonB" and sample!="SingleMuonC" and sample!="SingleMuonD"):
###for dataA, all events with run<317509, no HPS trigger is used
###for dataB, some with run<317509 while others with run>=317509, separate it to two parts
###for dataC and D, all events with run>=317509, only HPS trigger is saved and considered
    isdata=False
    rdf2 = RDataFrame("Runs","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018/{}.root".format(sample))
    #ngen = rdf2.Sum("genEventCount").GetValue()
    ngen = rdf2.Sum("genEventSumw").GetValue()
 
print ("isdata ", isdata)
print ("ngen is ", ngen)
xs = 1.0
weight = 1.0
eff=1.0
luminosity = 59830.0
if (year=="2017"): luminosity=41480.0
if (year=="2016pre"): luminosity=19520.0
if (year=="2016post"): luminosity=16810.0

if (isdata):
    weight = 1.0
    
if (sample=="DY"): 
    xs=6077.22 
    eff=0.318004188
    weight=luminosity*xs/ngen*eff
    
    
elif (sample=="TTTo2L2Nu"): 
    xs=831.76*0.1061
    eff=0.6571875
    weight=luminosity*xs/ngen*eff
    
elif (sample=="TTToSemiLeptonic"): 
    xs=831.76*0.4392
    eff=0.401486111
    weight=luminosity*xs/ngen*eff
    
elif (sample=="TTToHadronic"):
    xs=831.76*0.4544
    eff=0.169864583
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ZZ2L2Nu"): 
    xs=3.0
    eff=0.3018125
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ZZ4L"): 
    xs=1.212 
    eff=0.304
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ZZ2L2Q"): 
    xs=3.22 
    eff=0.372686157
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ZZ2Q2L"): 
    xs=3.22 
    eff=0.372686157
    weight=luminosity*xs/ngen*eff
    
elif (sample=="WZ2L2Q"): 
    xs=5.595 
    eff=0.340629667
    weight=luminosity*xs/ngen*eff

elif (sample=="WZ2Q2L"): 
    xs=5.595 
    eff=0.340629667
    weight=luminosity*xs/ngen*eff
    
elif (sample=="WW2L2Nu"): 
    xs=118.7*0.3*0.3
    eff=0.396603175
    weight=luminosity*xs/ngen*eff
    
elif (sample=="WZ3LNu"): 
    xs=4.42965
    eff=0.340808684
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ST_tW_top"): 
    xs=35.6 
    eff=0.272813333
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ST_tW_antitop"): 
    xs=35.6 
    eff=0.272407407
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ST_t_top"): 
    xs=136.02
    eff=0.118160784
    weight=luminosity*xs/ngen*eff
    
elif (sample=="ST_t_antitop"):
    xs=80.95 
    eff=0.122142268
    weight=luminosity*xs/ngen*eff
    
elif (sample=="GGToTauTau"):
    xs = 1.161
    eff=0.00871
    weight=luminosity*xs/ngen*eff
    
elif (sample=="GGToWW"):
    xs = 0.40
    eff = 0.009625
    weight = luminosity*xs/ngen*eff

'''elif (sample=="GGToMuMu"):
    xs = 0.40
    eff = 0.009625
    weight = luminosity*xs/ngen*eff
elif (sample=="WJets"): 
    xs=61526.7
    eff=1.0
    weight=luminosity*xs/ngen*eff'''
print ("cross section is ", xs, " eff is ", eff, " xsweight is ", weight)


#nentries = arbre.GetEntries()
#print ("Before selection total entries", nentries)
df = RDataFrame(0)
df = RDataFrame("Events","/eos/cms/store/group/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018/{}.root".format(sample))
nentries = df.Count().GetValue()

print ("Before selection total entries", nentries)

###define useful variable: mu/tau index/pt/eta/phi/dz, isOS(taumu is opposite sign), is_isolated(tau pass mediumvsjet)
df_var = df.Define("mutauindex", "Getmutauindex(nLepCand,LepCand_id ,LepCand_dz)").Define("muindex","mutauindex[0]").Define("tauindex","mutauindex[1]")
if (isdata):
    df_var = df_var.Define("my_tau","GetLepVector(tauindex,LepCand_pt,LepCand_eta,LepCand_phi)")
else: 
    df_var = df_var.Define("my_tau","GetLepVector(tauindex,LepCand_pt,LepCand_eta,LepCand_phi,LepCand_gen,LepCand_taues,LepCand_fes)")
    
df_var = df_var.Define("my_mu","GetLepVector(muindex,LepCand_pt,LepCand_eta,LepCand_phi)")\
            .Define("taupt","my_tau.Pt()").Define("taueta","my_tau.Eta()").Define("tauphi","my_tau.Phi()").Define("taudz","LepCand_dz[tauindex]")\
            .Define("mupt","my_mu.Pt()").Define("mueta","my_mu.Eta()").Define("muphi","my_mu.Phi()").Define("mudz","LepCand_dz[muindex]")\
            .Define("isOS","GetisOS(LepCand_charge,tauindex,muindex)").Define("is_isolated","Getis_isolated(LepCand_vsjet,tauindex)")



###Add some basic selection: mu/tau eta, muid/iso, trigger, deltaR, tauvsmu, taupt, mupt

###Take shape sys into consideration, mutrigger with taupt>28 (should change to 30), mutautrigger with taupt>30 (should change to 32) when get histogram

df_sel = df_var.Filter("fabs(mueta)<2.4 && fabs(taueta)<2.3").Filter("LepCand_muonMediumId[muindex]==1 && LepCand_muonIso[muindex]<0.15")\
    .Filter("LepCand_vsmu[tauindex]>8").Filter("my_tau.DeltaR(my_mu)>=0.5")

isSingleMuonTrigger = "HLT_IsoMu24 && (mupt>26) && (taupt>28)"

isMuonTauTriggerdata = "((run>=317509 && HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1) || (run<317509 && HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1))\
    && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
if (sample=="SingleMuonC" or sample=="SingleMuonD"):
    isMuonTauTriggerdata = "(HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1) && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
'''if (sample=="dataA"):
    isMuonTauTriggerdata = "(HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1) && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
elif (sample=="dataBHPS"):
    isSingleMuonTrigger = "HLT_IsoMu24 && (mupt>26) && (run>=317509)"
    isMuonTauTriggerdata = "(run>=317509 && HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1) && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
elif (sample=="dataBnoHPS"):
    isSingleMuonTrigger = "HLT_IsoMu24 && (mupt>26) && (run<317509)"
    isMuonTauTriggerdata = "(run<317509 && HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1) && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
elif (sample=="dataC" or sample=="dataD"):
    isMuonTauTriggerdata = "(HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1) && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"
'''
isMuonTauTriggerMC = "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1 && mupt>21 && mupt<26 && fabs(mueta<2.1) && fabs(taueta)<2.1 && taupt>30"

if (isdata):
    df_sel = df_sel.Define("isSingleMuonTrigger", isSingleMuonTrigger).Define("isMuonTauTrigger",isMuonTauTriggerdata)
else:
    df_sel = df_sel.Define("isSingleMuonTrigger", isSingleMuonTrigger).Define("isMuonTauTrigger",isMuonTauTriggerMC)

df_sel = df_sel.Filter("isSingleMuonTrigger || isMuonTauTrigger")

###Add xsweight and SFweight
if (not isdata):
    df_sel = df_sel.Define("murecosf","GetMuonrecoSF(my_mu)").Define("murecosf_stat","GetMuonrecoSF_stat(my_mu)").Define("murecosf_syst","GetMuonrecoSF_syst(my_mu)")\
        .Define("mutrgsf","GetMuonTriggerSF(my_mu)").Define("mutrgsf_stat","GetMuonTriggerSF_stat(my_mu)").Define("mutrgsf_syst","GetMuonTriggerSF_syst(my_mu)")\
        .Define("muidsf","GetMuonIDSF(my_mu)").Define("muidsf_stat","GetMuonIDSF_stat(my_mu)").Define("muidsf_syst","GetMuonIDSF_syst(my_mu)")\
        .Define("muisosf","GetMuonIsoSF(my_mu)").Define("muisosf_stat","GetMuonIsoSF_stat(my_mu)").Define("muisosf_syst","GetMuonIsoSF_syst(my_mu)")\
        .Define("musf_HLTMu20Tau27","GetMuonSF_HLTMu20Tau27(mupt,mueta)")
    if (not isW):
        df_sel = df_sel.Define("xsweight","{}*genWeight".format(weight)).Define("SFweight","GetSFweight_mutau(murecosf, muisosf,muidsf, mutrgsf,musf_HLTMu20Tau27,puWeight,tauindex,isSingleMuonTrigger,isMuonTauTrigger,LepCand_gen,LepCand_tauidMsf,LepCand_antielesf,LepCand_antimusf,LepCand_tautriggersf)")
    else:
        df_sel = df_sel.Define("xsweight","Getxsweight_W(LHE_Njets)").Define("SFweight","GetSFweight_mutau(murecosf, muisosf,muidsf, mutrgsf,musf_HLTMu20Tau27, puWeight,tauindex,isSingleMuonTrigger,isMuonTauTrigger,LepCand_gen,LepCand_tauidMsf,LepCand_antielesf,LepCand_antimusf,LepCand_tautriggersf)")
else:
    df_sel = df_sel.Define("murecosf","1.0").Define("murecosf_stat","1.0").Define("murecosf_syst","1.0")\
        .Define("mutrgsf","1.0").Define("mutrgsf_stat","1.0").Define("mutrgsf_syst","1.0")\
        .Define("muidsf","1.0").Define("muidsf_stat","1.0").Define("muidsf_syst","1.0")\
        .Define("muisosf","1.0").Define("muisosf_stat","1.0").Define("muisosf_syst","1.0")\
        .Define("musf_HLTMu20Tau27","1.0")
    df_sel = df_sel.Define("xsweight","1.0").Define("SFweight","1.0")
###Add information of mass (mvis>40, transverse mass, collinear mass), acoplanarity
df_sel = df_sel.Define("mvis","(my_mu+my_tau).M()").Define("mtrans","GetTransmass(my_mu, MET_pt, MET_phi)")\
    .Define("mcol","GetCollMass(my_mu,my_tau,MET_pt,MET_phi)").Define("Acopl","GetAcopl(my_mu,my_tau)")

###Define vtxtautau with 3 definition(simple average, theta-average, pt-average)
df_addvtx = df_sel.Define("zvtxll1","recovtxz1(LepCand_dz[muindex],LepCand_dz[tauindex],PV_z)")\
    .Filter("fabs(LepCand_dz[muindex]-LepCand_dz[tauindex])<0.1")



##Acoplanarity weights only for DY samples
if (isdata):
    df = df_addvtx.Define("genAco","-99.0").Define("Acoweight","1.0").Define("npvs_weight","1.0").Define("puWeight","1.0").Define("puWeightUp","1.0").Define("puWeightDown","1.0").Define("npvsDown_weight","1.0").Define("npvsUp_weight","1.0")
else: 
    if sample=="DY":
        df = df_addvtx.Define("genAco","GetGenAco(nGenCand,GenCand_phi,Acopl)").Define("Acoweight","Get_Aweight(genAco, nGenCand, GenCand_pt,mupt,taupt)")
    else:
        df = df_addvtx.Define("genAco","-99.0").Define("Acoweight","1.0")
    df = df.Define("npvs_weight","Get_npvs_weight(PV_npvs)").Define("npvsDown_weight","Get_npvsDown_weight(PV_npvs)").Define("npvsUp_weight","Get_npvsUp_weight(PV_npvs)")
##make new  mutrack and tautrack collection, choose highest pt muon track as mutrack, choose same dz as tautrack 


df = df.Define("Track_muptdiff","Computediffpt_lep(Track_pt,mupt)")\
    .Define("Track_mudeltaR","ComputedeltaR_lep(Track_eta,Track_phi,mueta,muphi)")\
    .Define("Track_tau1ptdiff","Computediffpt_lep(Track_pt,LepCand_tk1Pt[tauindex])")\
    .Define("Track_tau1deltaR","ComputedeltaR_lep(Track_eta,Track_phi,LepCand_tk1Eta[tauindex],LepCand_tk1Phi[tauindex])")\
    .Define("Track_tau2ptdiff","Computediffpt_lep(Track_pt,LepCand_tk2Pt[tauindex])")\
    .Define("Track_tau2deltaR","ComputedeltaR_lep(Track_eta,Track_phi,LepCand_tk2Eta[tauindex],LepCand_tk2Phi[tauindex])")\
    .Define("Track_tau3ptdiff","Computediffpt_lep(Track_pt,LepCand_tk3Pt[tauindex])")\
    .Define("Track_tau3deltaR","ComputedeltaR_lep(Track_eta,Track_phi,LepCand_tk3Eta[tauindex],LepCand_tk3Phi[tauindex])")\
    .Define("Track_mumatch","Gettrkmatch(Track_muptdiff,Track_mudeltaR)")\
    .Define("Track_tau1match","Gettrkmatch(Track_tau1ptdiff,Track_tau1deltaR)")\
    .Define("Track_tau2match","Gettrkmatch(Track_tau2ptdiff,Track_tau2deltaR)")\
    .Define("Track_tau3match","Gettrkmatch(Track_tau3ptdiff,Track_tau3deltaR)")

'''df = df.Define("muoncut","ChargedPFCandidates_muptdiff<0.1 && ChargedPFCandidates_mudeltaR<0.1 && abs(ChargedPFCandidates_pdgId)==13")\
    .Define("nMuontrk","Sum(muoncut)")\
    .Define("Muontrk_pt","ChargedPFCandidates_pt[muoncut]")\
    .Define("Muontrk_eta","ChargedPFCandidates_eta[muoncut]")\
    .Define("Muontrk_phi","ChargedPFCandidates_phi[muoncut]")\
    .Define("Muontrk_dz","ChargedPFCandidates_dz[muoncut]")\
    .Define("Muontrk_mass","ChargedPFCandidates_mass[muoncut]")\
    .Define("Muontrk_pdgId","ChargedPFCandidates_pdgId[muoncut]")\
    .Define("Muontrk_isMatchedToGenHS","ChargedPFCandidates_isMatchedToGenHS[muoncut]")\
    .Define("Muontrk_mudz","ChargedPFCandidates_mudz[muoncut]")\
    .Define("Muontrk_muptdiff","ChargedPFCandidates_muptdiff[muoncut]")\
    .Define("Muontrk_mudeltaR","ChargedPFCandidates_mudeltaR[muoncut]")
    

print ("Choose final mutrk")
df = df.Define("Muontrk_minmudz", "Min(Muontrk_mudz)" )\
    .Define("FinalMuontrk_cut","Muontrk_mudz==Muontrk_minmudz")\
    .Define("nFinalMuontrk","Sum(FinalMuontrk_cut)")\
    .Define("FinalMuontrk_pt","Muontrk_pt[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_eta","Muontrk_eta[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_phi","Muontrk_phi[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_dz","Muontrk_dz[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_mass","Muontrk_mass[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_pdgId","Muontrk_pdgId[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_isMatchedToGenHS","Muontrk_isMatchedToGenHS[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_mudz","Muontrk_mudz[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_muptdiff","Muontrk_muptdiff[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_mudeltaR","Muontrk_mudeltaR[FinalMuontrk_cut]")\
    .Define("FinalMuontrk_ditaudz","Compute_ditaudz(FinalMuontrk_dz,PV_z,zvtxll1)")
'''

'''df = df.Define("mutrkcut","ChargedPFCandidates_muptdiff<0.1 && ChargedPFCandidates_mudeltaR<0.001 && ChargedPFCandidates_mudz<0.05")\
    .Define("nFinalMuontrk","Sum(mutrkcut)")\
    .Define("FinalMuontrk_pt","ChargedPFCandidates_pt[mutrkcut]")\
    .Define("FinalMuontrk_eta","ChargedPFCandidates_eta[mutrkcut]")\
    .Define("FinalMuontrk_phi","ChargedPFCandidates_phi[mutrkcut]")\
    .Define("FinalMuontrk_dz","ChargedPFCandidates_dz[mutrkcut]")\
    .Define("FinalMuontrk_mass","ChargedPFCandidates_mass[mutrkcut]")\
    .Define("FinalMuontrk_pdgId","ChargedPFCandidates_pdgId[mutrkcut]")\
    .Define("FinalMuontrk_isMatchedToGenHS","ChargedPFCandidates_isMatchedToGenHS[mutrkcut]")\
    .Define("FinalMuontrk_mudz","ChargedPFCandidates_mudz[mutrkcut]")\
    .Define("FinalMuontrk_muptdiff","ChargedPFCandidates_muptdiff[mutrkcut]")\
    .Define("FinalMuontrk_mudeltaR","ChargedPFCandidates_mudeltaR[mutrkcut]")\
    .Define("FinalMuontrk_ditaudz","Compute_ditaudz(FinalMuontrk_dz,PV_z,zvtxll1)")

print ("Choose tautrk")

df = df.Define("tautrkcut","(abs(ChargedPFCandidates_pt-LepCand_trk1pt[tauindex])<0.002 && abs(ChargedPFCandidates_eta-LepCand_trk1eta[tauindex])<0.002 && abs(ChargedPFCandidates_phi-LepCand_trk1phi[tauindex])<0.002 && abs(ChargedPFCandidates_dz-LepCand_trk1dz[tauindex])<0.002) \
    || (abs(ChargedPFCandidates_pt-LepCand_trk2pt[tauindex])<0.002 && abs(ChargedPFCandidates_eta-LepCand_trk2eta[tauindex])<0.002 && abs(ChargedPFCandidates_phi-LepCand_trk2phi[tauindex])<0.002 && abs(ChargedPFCandidates_dz-LepCand_trk2dz[tauindex])<0.002 ) \
    || (abs(ChargedPFCandidates_pt-LepCand_trk3pt[tauindex])<0.002 && abs(ChargedPFCandidates_eta-LepCand_trk3eta[tauindex])<0.002 && abs(ChargedPFCandidates_phi-LepCand_trk3phi[tauindex])<0.002 && abs(ChargedPFCandidates_dz-LepCand_trk3dz[tauindex])<0.002 )") \
    .Define("nFinalTautrk","Sum(tautrkcut)")\
    .Define("FinalTautrk_pt","ChargedPFCandidates_pt[tautrkcut]")\
    .Define("FinalTautrk_eta","ChargedPFCandidates_eta[tautrkcut]")\
    .Define("FinalTautrk_phi","ChargedPFCandidates_phi[tautrkcut]")\
    .Define("FinalTautrk_dz","ChargedPFCandidates_dz[tautrkcut]")\
    .Define("FinalTautrk_pdgId","ChargedPFCandidates_pdgId[tautrkcut]")\
    .Define("FinalTautrk_mass","ChargedPFCandidates_mass[tautrkcut]")\
    .Define("FinalTautrk_isMatchedToGenHS","ChargedPFCandidates_isMatchedToGenHS[tautrkcut]")\
    .Define("FinalTautrk_ditaudz","Compute_ditaudz(FinalTautrk_dz,PV_z,zvtxll1)")
    '''

'''###Remove mutau trk
print ("Remove mutau trk from PFCandidates")
df = df.Define("PFtrkcut", "Getntrkcut_mutau(ChargedPFCandidates_pt, ChargedPFCandidates_eta, ChargedPFCandidates_phi, ChargedPFCandidates_dz,\
     FinalMuontrk_pt,  FinalMuontrk_eta,  FinalMuontrk_phi,  FinalMuontrk_dz,\
     FinalTautrk_pt,  FinalTautrk_eta,  FinalTautrk_phi,  FinalTautrk_dz)")\
    .Define("nPFtrk", "Sum(PFtrkcut)")\
    .Define("PFtrk_pt","ChargedPFCandidates_pt[PFtrkcut]")\
    .Define("PFtrk_eta","ChargedPFCandidates_eta[PFtrkcut]")\
    .Define("PFtrk_phi","ChargedPFCandidates_phi[PFtrkcut]")\
    .Define("PFtrk_dz","ChargedPFCandidates_dz[PFtrkcut]")\
    .Define("PFtrk_pdgId","ChargedPFCandidates_pdgId[PFtrkcut]")\
    .Define("PFtrk_mass","ChargedPFCandidates_mass[PFtrkcut]")\
    .Define("PFtrk_isMatchedToGenHS","ChargedPFCandidates_isMatchedToGenHS[PFtrkcut]")'''


###Get ditaudz (putrk need to add BS correction)
print ("Calculate ditaudz")
if (isdata):
    df = df.Define("Track_ditaudz","Compute_ditaudz(Track_dz,PV_z,zvtxll1)")
else: 
    df = df.Define("Track_ditaudz","Get_BScor_ditaudz(Track_dz,Track_isMatchedToHS,PV_z,zvtxll1)")
    
df = df.Define("Trkcut","Track_ditaudz<0.05 && (!Track_mumatch) && (!Track_tau1match) && (!Track_tau2match) && (!Track_tau3match)")\
    .Define("nTrk", "Sum(Trkcut)")\
    .Define("Trk_pt","Track_pt[Trkcut]")\
    .Define("Trk_eta","Track_eta[Trkcut]")\
    .Define("Trk_phi","Track_phi[Trkcut]")\
    .Define("Trk_dz","Track_dz[Trkcut]")\
    .Define("Trk_isMatchedToHS","Track_isMatchedToHS[Trkcut]")\
    .Define("Trk_ditaudz","Track_ditaudz[Trkcut]")

###Apply nputrack correction
print ("Apply nputrack correctionz")
if (isdata):
    df = df.Define("nPUtrk", "0")\
    .Define("nPUtrkweight","1.0")
else: 
    df = df.Define("PUtrkcut","Trk_isMatchedToHS==0")\
    .Define("nPUtrk", "Sum(PUtrkcut)")\
    .Define("nPUtrkweight","Get_ntpuweight(nPUtrk,zvtxll1)")


###Apply nHStrk correction(only for DY)
print ("Apply nHStrack correctionz")
if (isdata):
    df = df.Define("nHStrk","0")\
        .Define("nHStrkweight","1.0")
else:
    if (sample=="DY"):
        df = df.Define("HStrkcut","Trk_isMatchedToHS==1")\
            .Define("nHStrk","Sum(HStrkcut)")\
            .Define("nHStrkweight","Get_ntHSweight(nHStrk,genAco)")
    else:
        df = df.Define("HStrkcut","Trk_isMatchedToHS==1")\
            .Define("nHStrk","Sum(HStrkcut)")\
            .Define("nHStrkweight","1.0") 



columns = ROOT.std.vector("string")()
for c in ("run", "luminosityBlock", "event", \
    "HLT_IsoMu24","HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1",\
    "isSingleMuonTrigger","isMuonTauTrigger",\
    "MET_phi","MET_pt","PV_ndof","PV_x","PV_y","PV_z","PV_chi2","PV_score","PV_npvs","PV_npvsGood",\
    "nLepCand","LepCand_id","LepCand_pt","LepCand_eta","LepCand_phi","LepCand_charge","LepCand_dxy","LepCand_dz","LepCand_gen",\
    "LepCand_vse","LepCand_vsmu","LepCand_vsjet","LepCand_muonMediumId","LepCand_muonIso",\
    "LepCand_tauidMsf","LepCand_tauidMsf_uncert0_up","LepCand_tauidMsf_uncert1_up", "LepCand_tauidMsf_syst_alleras_up", "LepCand_tauidMsf_syst_era_up", "LepCand_tauidMsf_syst_dm_era_up",\
    "LepCand_tauidMsf_uncert0_down", "LepCand_tauidMsf_uncert1_down", "LepCand_tauidMsf_syst_alleras_down", "LepCand_tauidMsf_syst_era_down", "LepCand_tauidMsf_syst_dm_era_down",\
    "LepCand_taues","LepCand_taues_up","LepCand_taues_down",\
    "LepCand_fes","LepCand_fes_up","LepCand_fes_down",\
    "LepCand_antimusf","LepCand_antimusf_up","LepCand_antimusf_down",\
    "LepCand_antielesf","LepCand_antielesf_up","LepCand_antielesf_down",\
    "LepCand_tautriggersf","LepCand_tautriggersf_up","LepCand_tautriggersf_down",\
    "LepCand_DecayMode","LepCand_trgmatch",\
    "LepCand_tk1Pt","LepCand_tk2Pt","LepCand_tk3Pt","LepCand_tk1Eta","LepCand_tk2Eta","LepCand_tk3Eta",\
    "LepCand_tk1Phi","LepCand_tk2Phi","LepCand_tk3Phi","LepCand_dz2","LepCand_dz3",\
    "nGenCand","GenCand_id","GenCand_pt","GenCand_eta","GenCand_phi",\
    "V_genpt","puWeight","puWeightUp","puWeightDown","tauindex","muindex","my_tau","my_mu","taupt","taueta","tauphi","taudz","mupt","mueta","muphi",\
    "mudz","isOS","is_isolated","xsweight","SFweight","mvis","mtrans","mcol","Acopl","zvtxll1",\
    "murecosf","murecosf_stat","murecosf_syst","muidsf","muidsf_stat","muidsf_syst","muisosf","muisosf_stat","muisosf_syst","mutrgsf","mutrgsf_stat","mutrgsf_syst","musf_HLTMu20Tau27",\
    "nTrk","nPUtrk","nHStrk","Acoweight","npvs_weight","npvsDown_weight","npvsUp_weight","nPUtrkweight","nHStrkweight","genAco"):
    columns.push_back(c)

if (isdata):
    if sample=="SingleMuonA" or sample=="SingleMuonB":
        columns.push_back("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1")
else:
    columns.push_back("GenVtx_z")
    
if sample=="GGToTauTau":
    branchlist = list(df.GetColumnNames())
    for taug2weights in list(filter(lambda x: "TauG2Weights" in str(x), branchlist)):
        columns.push_back(taug2weights)


df.Snapshot("Events","/eos/cms/store/cmst3/group/taug2/AnalysisXuelong/ntuples_mutau_2018_basicsel/{}.root".format(sample),columns)

nentries = df.Count().GetValue()
print ("After selection entries", nentries)

time_end=timer.time()
print('totally cost',time_end-time_start)

