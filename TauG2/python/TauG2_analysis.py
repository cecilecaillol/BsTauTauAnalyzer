#!/usr/bin/env python
import os, sys, math
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection

### Proton selector be replaced by preprocessing module
from MyNanoAnalyzer.TauG2.objectSelector import ElectronSelector, MuonSelector, TauSelector
from MyNanoAnalyzer.TauG2.objectSelector import GenParticleSelector

from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool, TauESTool, campaigns
from TauPOG.TauIDSFs.TauIDSFTool import TauFESTool

from TauAnalysisTools.TauTriggerSFs.SFProvider import SFProvider


class Analysis(Module):
    def __init__(self, channel, isMC, year):
        self.channel       = channel
        self.isMC          = isMC
        self.year          = year

        self.tauSFsM_vseVVL = TauIDSFTool(year='UL2018',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='VVLoose',ptdm=True)
        self.tauSFsM_vseT = TauIDSFTool(year='UL2018',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='Tight',ptdm=True)
        self.testool       = TauESTool('UL2018','DeepTau2017v2p1VSjet')
        self.antiEleSFLTool = TauIDSFTool('UL2018','DeepTau2017v2p1VSe','VVLoose')
        self.antiMuSFLTool  = TauIDSFTool('UL2018','DeepTau2017v2p1VSmu','VLoose')
        self.antiEleSFTTool = TauIDSFTool('UL2018','DeepTau2017v2p1VSe','Tight')
        self.antiMuSFTTool  = TauIDSFTool('UL2018','DeepTau2017v2p1VSmu','Tight')
        self.festool       = TauFESTool('UL2018')
        self.ditautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2018UL_tauTriggerEff_DeepTau2017v2p1.root", "ditau", "Medium") #FOR ditau channel
        self.etautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2018UL_tauTriggerEff_DeepTau2017v2p1.root", "etau", "Medium") #FOR etau channel
        self.mutautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2018UL_tauTriggerEff_DeepTau2017v2p1.root", "mutau", "Medium") #FOR mutau channel
        self.tauDMSF       = TauIDSFTool('UL2018','DeepTau2017v2p1VSjet','Medium',dm=True)

	if self.year=="2017":
           self.tauSFsM_vseVVL = TauIDSFTool(year='UL2017',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='VVLoose',ptdm=True)
           self.tauSFsM_vseT = TauIDSFTool(year='UL2017',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='Tight',ptdm=True)
           self.testool       = TauESTool('UL2017','DeepTau2017v2p1VSjet')
           self.antiEleSFLTool = TauIDSFTool('UL2017','DeepTau2017v2p1VSe','VVLoose')
           self.antiMuSFLTool  = TauIDSFTool('UL2017','DeepTau2017v2p1VSmu','VLoose')
           self.antiEleSFTTool = TauIDSFTool('UL2017','DeepTau2017v2p1VSe','Tight')
           self.antiMuSFTTool  = TauIDSFTool('UL2017','DeepTau2017v2p1VSmu','Tight')
           self.festool       = TauFESTool('UL2017')
           self.ditautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2017UL_tauTriggerEff_DeepTau2017v2p1.root", "ditau", "Medium") #FOR ditau channel
           self.etautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2017UL_tauTriggerEff_DeepTau2017v2p1.root", "etau", "Medium") #FOR etau channel
           self.mutautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2017UL_tauTriggerEff_DeepTau2017v2p1.root", "mutau", "Medium") #FOR mutau channel
           self.tauDMSF       = TauIDSFTool('UL2017','DeepTau2017v2p1VSjet','Medium',dm=True)

        if self.year=="2016post":
           self.tauSFsM_vseVVL = TauIDSFTool(year='UL2016_postVFP',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='VVLoose',ptdm=True)
           self.tauSFsM_vseT = TauIDSFTool(year='UL2016_postVFP',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='Tight',ptdm=True)
           self.testool       = TauESTool('UL2016_postVFP','DeepTau2017v2p1VSjet')
           self.antiEleSFLTool = TauIDSFTool('UL2016_postVFP','DeepTau2017v2p1VSe','VVLoose')
           self.antiMuSFLTool  = TauIDSFTool('UL2016_postVFP','DeepTau2017v2p1VSmu','VLoose')
           self.antiEleSFTTool = TauIDSFTool('UL2016_postVFP','DeepTau2017v2p1VSe','Tight')
           self.antiMuSFTTool  = TauIDSFTool('UL2016_postVFP','DeepTau2017v2p1VSmu','Tight')
           self.festool       = TauFESTool('UL2016_postVFP')
           self.ditautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpostVFP_tauTriggerEff_DeepTau2017v2p1.root", "ditau", "Medium") #FOR ditau channel
           self.etautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpostVFP_tauTriggerEff_DeepTau2017v2p1.root", "etau", "Medium") #FOR etau channel
           self.mutautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpostVFP_tauTriggerEff_DeepTau2017v2p1.root", "mutau", "Medium") #FOR mutau channel
           self.tauDMSF       = TauIDSFTool('UL2016_postVFP','DeepTau2017v2p1VSjet','Medium',dm=True)

        if self.year=="2016pre":
           self.tauSFsM_vseVVL = TauIDSFTool(year='UL2016_preVFP',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='VVLoose',ptdm=True)
           self.tauSFsM_vseT = TauIDSFTool(year='UL2016_preVFP',id='DeepTau2017v2p1VSjet',wp='Medium',wp_vsele='Tight',ptdm=True)
           self.testool       = TauESTool('UL2016_preVFP','DeepTau2017v2p1VSjet')
           self.antiEleSFLTool = TauIDSFTool('UL2016_preVFP','DeepTau2017v2p1VSe','VVLoose')
           self.antiMuSFLTool  = TauIDSFTool('UL2016_preVFP','DeepTau2017v2p1VSmu','VLoose')
           self.antiEleSFTTool = TauIDSFTool('UL2016_preVFP','DeepTau2017v2p1VSe','Tight')
           self.antiMuSFTTool  = TauIDSFTool('UL2016_preVFP','DeepTau2017v2p1VSmu','Tight')
           self.festool       = TauFESTool('UL2016_preVFP')
           self.ditautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpreVFP_tauTriggerEff_DeepTau2017v2p1.root", "ditau", "Medium") #FOR ditau channel
           self.etautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpreVFP_tauTriggerEff_DeepTau2017v2p1.root", "etau", "Medium") #FOR etau channel
           self.mutautriggerSFTool = SFProvider("/afs/cern.ch/work/c/ccaillol/G2analysis/CMSSW_10_6_27/src/TauAnalysisTools/TauTriggerSFs/data/2016ULpreVFP_tauTriggerEff_DeepTau2017v2p1.root", "mutau", "Medium") #FOR mutau channel
           self.tauDMSF       = TauIDSFTool('UL2016_preVFP','DeepTau2017v2p1VSjet','Medium',dm=True)



        cmssw=os.environ['CMSSW_BASE']
        datafilename = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","Data_PileUp_UL2018_69p2.root")
        mcfilename   = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","MC_PileUp_UL2018.root")

        if self.year=="2017":
            datafilename = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","Data_PileUp_UL2017_69p2.root")
            mcfilename   = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","MC_PileUp_UL2017.root")

        if self.year=="2016pre":
            datafilename = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","Data_PileUp_UL2016_69p2.root")
            mcfilename   = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","MC_PileUp_UL2016_preVFP.root")

        if self.year=="2016post":
            datafilename = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","Data_PileUp_UL2016_69p2.root")
            mcfilename   = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","MC_PileUp_UL2016_postVFP.root")

        self.datafile = ROOT.TFile(datafilename, 'READ')
        self.mcfile   = ROOT.TFile(mcfilename, 'READ')
        self.datahist = self.datafile.Get('pileup')
        self.mchist   = self.mcfile.Get('pileup')

        pass

    def beginJob(self):
        pass

    def endJob(self):
        pass

    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
    
        self.out = wrappedOutputTree
        self.out.branch("nLepCand",              "I");
        self.out.branch("LepCand_id",            "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_pt",            "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eta",           "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_phi",           "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_charge",        "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_dxy",           "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_dz",            "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_gen",           "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_vse",           "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_vsmu",          "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_vsjet",         "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_muonMediumId",  "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_muonIso",       "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAiso90",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAiso80",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAisoL",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAnoiso90",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAnoiso80",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleMVAnoisoL",   "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleIso",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleSigmaDown",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleSigmaUp",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleScaleDown",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_eleScaleUp",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf",                   "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_uncert0_up",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_uncert1_up",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_alleras_up",   "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_era_up",       "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_dm_era_up",    "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_uncert0_down",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_uncert1_down",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_alleras_down", "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_era_down",     "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf_syst_dm_era_down",  "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_taues",         "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_taues_up",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_taues_down",    "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_fes",           "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_fes_up",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_fes_down",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antimusf",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antimusf_up",   "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antimusf_down", "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antielesf",     "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antielesf_up",  "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antielesf_down","F",  lenVar = "nLepCand");
        self.out.branch("LepCand_DecayMode",    "I",  lenVar = "nLepCand");# tau decay mode
        self.out.branch("LepCand_tautriggersf",    "F",  lenVar = "nLepCand");# trigger sf for ditau channel
        self.out.branch("LepCand_tautriggersf_up",    "F",  lenVar = "nLepCand");# trigger sf for ditau channel
        self.out.branch("LepCand_tautriggersf_down",    "F",  lenVar = "nLepCand");# trigger sf for ditau channel
        self.out.branch("LepCand_trgmatch",      "I",  lenVar = "nLepCand");
        self.out.branch("LepCand_dz2",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_dz3",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk1Pt",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk1Eta",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk1Phi",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk2Pt",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk2Eta",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk2Phi",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk3Pt",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk3Eta",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tk3Phi",      "F",  lenVar = "nLepCand");

        self.out.branch("nGenCand",              "I");
        self.out.branch("GenCand_id",            "I",  lenVar = "nGenCand");
        self.out.branch("GenCand_pt",            "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_eta",           "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_phi",           "F",  lenVar = "nGenCand");

        self.out.branch("nTracks",              "I");
        self.out.branch("Track_pt",             "F",  lenVar = "nTracks");
        self.out.branch("Track_eta",            "F",  lenVar = "nTracks");
        self.out.branch("Track_phi",            "F",  lenVar = "nTracks");
        self.out.branch("Track_dz",             "F",  lenVar = "nTracks");
        self.out.branch("Track_dxy",             "F",  lenVar = "nTracks");
        self.out.branch("Track_charge",         "I",  lenVar = "nTracks");
        self.out.branch("Track_isMatchedToHS",  "I",  lenVar = "nTracks");
        self.out.branch("Track_lostInnerHits",  "I",  lenVar = "nTracks");
        self.out.branch("Track_trackHighPurity",  "I",  lenVar = "nTracks");

        self.out.branch("nElectrons",        "I");
        self.out.branch("nMuons",            "I");
        self.out.branch("nTaus",             "I");

        self.out.branch("V_genpt",           "F");
        self.out.branch("pu_weight",         "F");
        
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def selectGenParticles(self, event):

        event.selectedGenParticles = []
        genparticles = Collection(event, "GenPart")
        for genp in genparticles:
            event.selectedGenParticles.append(genp)


    def selectElectrons(self, event, elSel):

        event.selectedElectrons = []
        electrons = Collection(event, "Electron")
        for el in electrons:
            if not elSel.evalElectron(el): continue

            #check overlap with selected leptons 
            deltaR_to_leptons=[ el.p4().DeltaR(lep.p4()) for lep in event.selectedMuons ]
            hasLepOverlap=sum( [dR<0.4 for dR in deltaR_to_leptons] )
            if hasLepOverlap>0: continue

            setattr(el, 'id', 11)
            event.selectedElectrons.append(el)
            
        event.selectedElectrons.sort(key=lambda x: x.pt, reverse=True)

    def selectTaus(self, event, tauSel):

        event.selectedTaus = []
        taus = Collection(event, "Tau")
        for tau in taus:

            #check overlap with selected leptons 
            deltaR_to_leptons=[ tau.p4().DeltaR(lep.p4()) for lep in event.selectedMuons+event.selectedElectrons ]
            hasLepOverlap=sum( [dR<0.4 for dR in deltaR_to_leptons] )
            if hasLepOverlap>0: continue

            if not tauSel.evalTau(tau): continue
            setattr(tau, 'id', 15)
            event.selectedTaus.append(tau)
            
        event.selectedTaus.sort(key=lambda x: x.pt, reverse=True)
        

    def selectMuons(self, event, muSel):
        ## access a collection in nanoaod and create a new collection based on this

        event.selectedMuons = []
        muons = Collection(event, "Muon")
        for mu in muons:
            if not muSel.evalMuon(mu): continue
            setattr(mu, 'id', 13)
            event.selectedMuons.append(mu)

        event.selectedMuons.sort(key=lambda x: x.pt, reverse=True)

    def selectTriggerObjects(self, event):
        event.selectedTriggerObjects = []
        triggerobjects = Collection(event, "TrigObj")
        for to in triggerobjects:
           if to.id!=11 and to.id!=13 and to.id!=15: continue
           event.selectedTriggerObjects.append(to)

    def selectTracks(self, event):
        event.selectedTracks = []
        chargedPF = Collection(event, "ChargedPFCandidates")
        #lostTracks = Collection(event, "LostTracks")
  	vertex_dz=0.0
	if self.channel=="ee":
	   vertex_dz=0.5*(event.selectedElectrons[0].dz+event.selectedElectrons[1].dz)
        elif self.channel=="emu":
           vertex_dz=0.5*(event.selectedElectrons[0].dz+event.selectedMuons[0].dz)
        elif self.channel=="etau":
           vertex_dz=event.selectedElectrons[0].dz
        elif self.channel=="mumu":
           vertex_dz=0.5*(event.selectedMuons[0].dz+event.selectedMuons[1].dz)
        elif self.channel=="mutau":
           vertex_dz=event.selectedMuons[0].dz
        elif self.channel=="tautau":
           vertex_dz=0.5*(event.selectedTaus[0].dz+event.selectedTaus[1].dz)
        for j in chargedPF:
            if self.isMC:
	        if abs(j.eta)<2.5 and abs(j.dz-vertex_dz)<2.5: #need wider window in dz in MC because of the BS correction later
                   event.selectedTracks.append(j)
	    else:
                if abs(j.eta)<2.5 and abs(j.dz-vertex_dz)<0.5: 
                   event.selectedTracks.append(j)

        #for j in lostTracks:
        #    if abs(j.eta)<2.5 and abs(j.dz-vertex_dz)<0.3:
        #        event.selectedTracks.append(j)
        event.selectedTracks.sort(key=lambda x: x.pt, reverse=True)

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #print "New event"

      	# Apply MET filters
        #if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter):
        #   return False
        #if not self.isMC and not event.Flag_eeBadScFilter:
        #   return False

        if self.year=="2017" or self.year=="2018":
           if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter and event.Flag_ecalBadCalibFilter):
              return False

        if self.year=="2016" or self.year=="2016pre" or self.year=="2016post":
           if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter): #FIXME add noisy hit filter https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2#UL_data
              return False

        
        #initiate object selector tools:
        elSel = ElectronSelector()
        tauSel = TauSelector()
        muSel = MuonSelector(minPt=10, ID='medium')

        #self.selectMuons(event, muSel)
        #self.selectElectrons(event, elSel)
        #self.selectTaus(event, tauSel)
	#print len(event.selectedElectrons),len(event.selectedMuons),len(event.selectedTaus)
        
        # apply object selection and make channels exclusive based on number of leptons
        self.selectMuons(event, muSel)
        if self.channel=="tautau" or self.channel=="etau" or self.channel=="ee":
            if len(event.selectedMuons)>0: return False
        if self.channel=="mutau" or self.channel=="emu":
            if len(event.selectedMuons)!=1: return False
        if self.channel=="mumu":
            if len(event.selectedMuons)<2: return False

        self.selectElectrons(event, elSel)
        if self.channel=="tautau" or self.channel=="mutau" or self.channel=="mumu":
            if len(event.selectedElectrons)>0: return False
        if self.channel=="etau" or self.channel=="emu":
            if len(event.selectedElectrons)!=1: return False
        if self.channel=="ee":
            if len(event.selectedElectrons)<2: return False

        self.selectTaus(event, tauSel)
        if self.channel=="etau" or self.channel=="mutau":
            if len(event.selectedTaus)<1: return False
        if self.channel=="tautau":
            if len(event.selectedTaus)<2: return False

        self.selectTriggerObjects(event)

        if self.isMC:
            self.selectGenParticles(event)
        
        #apply preliminary loose pt cuts based on trigger:
        if self.channel=="mutau":
            if event.selectedMuons[0].pt<20: return False

        if self.channel=="mumu":
            if event.selectedMuons[0].pt<24: return False

        if self.channel=="etau" or self.channel=="ee":
            if event.selectedElectrons[0].pt<25: return False

        if self.channel=="etau":
	    if event.selectedElectrons[0].pt<32 and event.selectedTaus[0].pt<34: return False

        if self.channel=="tautau":
            if event.selectedTaus[0].pt<39: return False

        if self.channel=="emu":
            if event.selectedElectrons[0].pt<23 and event.selectedMuons[0].pt<23: return False

	#apply channel-dependent tau ID cuts
        if self.channel=="mutau":
	    tau_vsmu=False
	    for k in range(0,len(event.selectedTaus)):
               if event.selectedTaus[k].idDeepTau2017v2p1VSmu>=8: tau_vsmu=True #pass tight VSmu
	    if not tau_vsmu: return False

        if self.channel=="etau":
            tau_vse=False
            for k in range(0,len(event.selectedTaus)):
               if event.selectedTaus[k].idDeepTau2017v2p1VSe>=32: tau_vse=True #pass tight VSmu
            if not tau_vse: return False

        self.selectTracks(event)

      	######################################################
      	###############  GEN-LEVEL ANALYSIS ##################
      	######################################################

        event.genCand=[]
        event.V_genpt=-1.0;


        if self.isMC:
            for genp in event.selectedGenParticles:
                if abs(genp.pdgId)==15 and abs(event.selectedGenParticles[genp.genPartIdxMother].pdgId)==23:
                    event.genCand.append(genp)
		if (abs(genp.pdgId)==13 and abs(event.selectedGenParticles[genp.genPartIdxMother].pdgId)==23):
                    event.genCand.append(genp)
                if (abs(genp.pdgId)==11 and abs(event.selectedGenParticles[genp.genPartIdxMother].pdgId)==23):
                    event.genCand.append(genp)
                if abs(genp.pdgId)==6:
                    event.genCand.append(genp)

        if self.isMC:
            for genp in event.selectedGenParticles:
              if (abs(genp.pdgId)==23 or abs(genp.pdgId)==24) and event.V_genpt<0:
                event.V_genpt=genp.pt

        ######################################################
        ##### HIGH LEVEL VARIABLES FOR SELECTED EVENTS   #####
        ######################################################
        

        postfix_tauid="2018"
        if self.year=="2016pre": postfix_tauid="2016_preVFP"
        elif self.year=="2016post": postfix_tauid="2016_postVFP"
        elif self.year=="2017": postfix_tauid="2017"

        event.selectedLeptons=event.selectedElectrons+event.selectedMuons+event.selectedTaus
        event.selectedLeptons.sort(key=lambda x: x.pt, reverse=True)
        
        lep_vsjet=[]
        lep_vse=[]
        lep_vsmu=[]
        lep_tauidMsf=[]
        lep_tauidMsf_uncert0_up=[]
        lep_tauidMsf_uncert1_up=[]
        lep_tauidMsf_syst_alleras_up=[]
        lep_tauidMsf_syst_era_up=[]
        lep_tauidMsf_syst_dm_era_up=[]
        lep_tauidMsf_uncert0_down=[]
        lep_tauidMsf_uncert1_down=[]
        lep_tauidMsf_syst_alleras_down=[]
        lep_tauidMsf_syst_era_down=[]
        lep_tauidMsf_syst_dm_era_down=[]

        lep_taues=[]
        lep_taues_up=[]
        lep_taues_down=[]
        lep_dz2=[]
        lep_dz3=[]
        lep_tk1Pt=[]
        lep_tk1Eta=[]
        lep_tk1Phi=[]
        lep_tk2Pt=[]
        lep_tk2Eta=[]
        lep_tk2Phi=[]
        lep_tk3Pt=[]
        lep_tk3Eta=[]
        lep_tk3Phi=[]
        lep_antielesf=[]
        lep_antielesf_up=[]
        lep_antielesf_down=[]
        lep_antimusf=[]
        lep_antimusf_up=[]
        lep_antimusf_down=[]
        lep_fes=[]
        lep_fes_up=[]
        lep_fes_down=[]
        lep_muonMediumId=[]
        lep_muonIso=[]
        lep_eleMVAiso90=[]
        lep_eleMVAiso80=[]
        lep_eleMVAisoL=[]
        lep_eleMVAnoiso90=[]
        lep_eleMVAnoiso80=[]
        lep_eleMVAnoisoL=[]
        lep_eleIso=[]
        lep_eleScaleUp=[]
        lep_eleScaleDown=[]
        lep_eleSigmaUp=[]
        lep_eleSigmaDown=[]
        lep_decaymode=[]
        lep_tautriggersf=[]
        lep_tautriggersf_up=[]
        lep_tautriggersf_down=[]
        lep_trgmatch=[]

        for lep in event.selectedLeptons:
             
            if lep.id==11:
                lep_eleMVAiso90.append(lep.mvaFall17V2Iso_WP90)
                lep_eleMVAiso80.append(lep.mvaFall17V2Iso_WP80)
                lep_eleMVAisoL.append(lep.mvaFall17V2Iso_WPL)
                lep_eleMVAnoiso90.append(lep.mvaFall17V2noIso_WP90)
                lep_eleMVAnoiso80.append(lep.mvaFall17V2noIso_WP80)
                lep_eleMVAnoisoL.append(lep.mvaFall17V2noIso_WPL)
                lep_eleIso.append(lep.miniPFRelIso_all)
                lep_eleScaleUp.append(lep.dEscaleUp)
                lep_eleScaleDown.append(lep.dEscaleDown)
                lep_eleSigmaUp.append(lep.dEsigmaUp)
                lep_eleSigmaDown.append(lep.dEsigmaDown)
                is_matched=0
                for to in event.selectedTriggerObjects:
                   top4=ROOT.TLorentzVector()
                   top4.SetPtEtaPhiM(to.pt,to.eta,to.phi,0)
                   if self.year=="2017" and self.channel=="etau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==11 and lep.p4().DeltaR(top4)<0.5 and ((bool(to.filterBits&1024) and bool(to.filterBits&2)) or bool(to.filterBits&64)): is_matched=1
		   elif self.channel=="etau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==11 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&2) or bool(to.filterBits&64)): is_matched=1
                   if self.channel=="emu" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==11 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&32)): is_matched=1
                lep_trgmatch.append(is_matched)

            else:
                lep_eleMVAiso90.append(-1)
                lep_eleMVAiso80.append(-1)
                lep_eleMVAisoL.append(-1)
                lep_eleMVAnoiso90.append(-1)
                lep_eleMVAnoiso80.append(-1)
                lep_eleMVAnoisoL.append(-1)
                lep_eleIso.append(-1)
                lep_eleScaleDown.append(-1)
                lep_eleScaleUp.append(-1)
                lep_eleSigmaDown.append(-1)
                lep_eleSigmaUp.append(-1)
              
            if lep.id==13:
                lep_muonMediumId.append(lep.mediumId)
                lep_muonIso.append(lep.pfRelIso04_all)
                is_matched=0
                for to in event.selectedTriggerObjects:
                   top4=ROOT.TLorentzVector()
                   top4.SetPtEtaPhiM(to.pt,to.eta,to.phi,0)
                   if self.channel=="mutau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==13 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&64) or bool(to.filterBits&8)): is_matched=1
                   elif self.channel=="mumu" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==13 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&8)): is_matched=1
                   elif self.channel=="emu" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==13 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&32)): is_matched=1
                lep_trgmatch.append(is_matched)
            else:
                lep_muonMediumId.append(-1)
                lep_muonIso.append(-1)
              
            if lep.id==15:
	        lep_dz2.append(lep.dz2)
                lep_dz3.append(lep.dz3)
                lep_tk1Pt.append(lep.tk1Pt)
                lep_tk1Eta.append(lep.tk1Eta)
                lep_tk1Phi.append(lep.tk1Phi)
                lep_tk2Pt.append(lep.tk2Pt)
                lep_tk2Eta.append(lep.tk2Eta)
                lep_tk2Phi.append(lep.tk2Phi)
                lep_tk3Pt.append(lep.tk3Pt)
                lep_tk3Eta.append(lep.tk3Eta)
                lep_tk3Phi.append(lep.tk3Phi)
                lep_decaymode.append(lep.decayMode)
                lep_vsjet.append(lep.idDeepTau2017v2p1VSjet)
                lep_vse.append(lep.idDeepTau2017v2p1VSe)
                lep_vsmu.append(lep.idDeepTau2017v2p1VSmu)
                is_matched=0
                for to in event.selectedTriggerObjects:
                   top4=ROOT.TLorentzVector()
                   top4.SetPtEtaPhiM(to.pt,to.eta,to.phi,0)
                   if self.channel=="mutau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==15 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&256)): is_matched=1
                   elif self.channel=="etau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==15 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&128)): is_matched=1
                   elif self.channel=="tautau" and abs(to.pt-lep.pt)/lep.pt<0.20 and to.id==15 and lep.p4().DeltaR(top4)<0.5 and (bool(to.filterBits&64)): is_matched=1
                lep_trgmatch.append(is_matched)
                
                if self.isMC and lep.genPartFlav==5:
                    if self.channel=="etau":
                       lep_tauidMsf.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav))
                       lep_tauidMsf_uncert0_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert0_up'))
                       lep_tauidMsf_uncert1_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert1_up'))
                       lep_tauidMsf_syst_alleras_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_alleras_up'))
                       lep_tauidMsf_syst_era_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_'+postfix_tauid+'_up'))
                       if lep.decayMode==0: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm0_'+postfix_tauid+'_up'))
                       elif lep.decayMode==1: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm1_'+postfix_tauid+'_up'))
                       elif lep.decayMode==10: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm10_'+postfix_tauid+'_up'))
                       else: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm11_'+postfix_tauid+'_up'))
                       lep_tauidMsf_uncert0_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert0_down'))
                       lep_tauidMsf_uncert1_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert1_down'))
                       lep_tauidMsf_syst_alleras_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_alleras_down'))
                       lep_tauidMsf_syst_era_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_'+postfix_tauid+'_down'))
                       if lep.decayMode==0: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm0_'+postfix_tauid+'_down'))
                       elif lep.decayMode==1: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm1_'+postfix_tauid+'_down'))
                       elif lep.decayMode==10: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm10_'+postfix_tauid+'_down'))
                       else: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseT.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm11_'+postfix_tauid+'_down'))

		    else: #other channels, vsele VVLoose
                       lep_tauidMsf.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav))
                       lep_tauidMsf_uncert0_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert0_up'))
                       lep_tauidMsf_uncert1_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert1_up'))
                       lep_tauidMsf_syst_alleras_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_alleras_up'))
                       lep_tauidMsf_syst_era_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_'+postfix_tauid+'_up'))
                       if lep.decayMode==0: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm0_'+postfix_tauid+'_up'))
                       elif lep.decayMode==1: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm1_'+postfix_tauid+'_up'))
                       elif lep.decayMode==10: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm10_'+postfix_tauid+'_up'))
                       else: lep_tauidMsf_syst_dm_era_up.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm11_'+postfix_tauid+'_up'))
                       lep_tauidMsf_uncert0_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert0_down'))
                       lep_tauidMsf_uncert1_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'uncert1_down'))
                       lep_tauidMsf_syst_alleras_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_alleras_down'))
                       lep_tauidMsf_syst_era_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_'+postfix_tauid+'_down'))
                       if lep.decayMode==0: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm0_'+postfix_tauid+'_down'))
                       elif lep.decayMode==1: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm1_'+postfix_tauid+'_down'))
                       elif lep.decayMode==10: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm10_'+postfix_tauid+'_down'))
                       else: lep_tauidMsf_syst_dm_era_down.append(self.tauSFsM_vseVVL.getSFvsDMandPT(lep.pt,lep.decayMode,lep.genPartFlav,'syst_dm11_'+postfix_tauid+'_down'))

                    lep_taues.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav))
                    lep_taues_up.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav,unc='Up'))
                    lep_taues_down.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav,unc='Down'))
		    if self.channel=="etau":
                       lep_tautriggersf.append(self.etautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=0))
                       lep_tautriggersf_up.append(self.etautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=1))
                       lep_tautriggersf_down.append(self.etautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=-1))
		    elif self.channel=="mutau":
                       lep_tautriggersf.append(self.mutautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=0))
                       lep_tautriggersf_up.append(self.mutautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=1))
                       lep_tautriggersf_down.append(self.mutautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=-1))
		    else:
                       lep_tautriggersf.append(self.ditautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=0))
                       lep_tautriggersf_up.append(self.ditautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=1))
                       lep_tautriggersf_down.append(self.ditautriggerSFTool.getSF(lep.pt,lep.decayMode,unc_scale=-1))
                else:
                    lep_tauidMsf.append(1.0)
                    lep_tauidMsf_uncert0_up.append(1.0)
                    lep_tauidMsf_uncert1_up.append(1.0)
                    lep_tauidMsf_syst_alleras_up.append(1.0)
                    lep_tauidMsf_syst_era_up.append(1.0)
                    lep_tauidMsf_syst_dm_era_up.append(1.0)
                    lep_tauidMsf_uncert0_down.append(1.0)
                    lep_tauidMsf_uncert1_down.append(1.0)
                    lep_tauidMsf_syst_alleras_down.append(1.0)
                    lep_tauidMsf_syst_era_down.append(1.0)
                    lep_tauidMsf_syst_dm_era_down.append(1.0)
                    lep_taues.append(1.0)
                    lep_taues_up.append(1.0)
                    lep_taues_down.append(1.0)
                    lep_tautriggersf.append(1.0)
                    lep_tautriggersf_up.append(1.0)
                    lep_tautriggersf_down.append(1.0)
                
                if self.isMC and (lep.genPartFlav==2 or lep.genPartFlav==4):
		    if self.channel=="mutau":
	               lep_antimusf.append(self.antiMuSFTTool.getSFvsEta(lep.eta,lep.genPartFlav))
                       lep_antimusf_up.append(self.antiMuSFTTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                       lep_antimusf_down.append(self.antiMuSFTTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
		    else:
                       lep_antimusf.append(self.antiMuSFLTool.getSFvsEta(lep.eta,lep.genPartFlav))
                       lep_antimusf_up.append(self.antiMuSFLTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                       lep_antimusf_down.append(self.antiMuSFLTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
                else:
                    lep_antimusf.append(1.0)
                    lep_antimusf_up.append(1.0)
                    lep_antimusf_down.append(1.0)
                
                if self.isMC and (lep.genPartFlav==1 or lep.genPartFlav==3):
		    if self.channel=="etau":
                       lep_antielesf.append(self.antiEleSFTTool.getSFvsEta(lep.eta,lep.genPartFlav))
                       lep_antielesf_up.append(self.antiEleSFTTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                       lep_antielesf_down.append(self.antiEleSFTTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
		    else:
                       lep_antielesf.append(self.antiEleSFLTool.getSFvsEta(lep.eta,lep.genPartFlav))
                       lep_antielesf_up.append(self.antiEleSFLTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                       lep_antielesf_down.append(self.antiEleSFLTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
                    lep_fes.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav))
                    lep_fes_up.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav,unc='Up'))
                    lep_fes_down.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav,unc='Down'))
                else:
                    lep_antielesf.append(1.0)
                    lep_antielesf_up.append(1.0)
                    lep_antielesf_down.append(1.0)
                    lep_fes.append(1.0)
                    lep_fes_up.append(1.0)
                    lep_fes_down.append(1.0)

            else: # not a tau
                lep_vsjet.append(0)
                lep_vse.append(0)
                lep_vsmu.append(0)
                lep_tauidMsf.append(1.0)
                lep_tauidMsf_uncert0_up.append(1.0)
                lep_tauidMsf_uncert1_up.append(1.0)
                lep_tauidMsf_syst_alleras_up.append(1.0)
                lep_tauidMsf_syst_era_up.append(1.0)
                lep_tauidMsf_syst_dm_era_up.append(1.0)
                lep_tauidMsf_uncert0_down.append(1.0)
                lep_tauidMsf_uncert1_down.append(1.0)
                lep_tauidMsf_syst_alleras_down.append(1.0)
                lep_tauidMsf_syst_era_down.append(1.0)
                lep_tauidMsf_syst_dm_era_down.append(1.0)

                lep_fes.append(1.0)
                lep_fes_up.append(1.0)
                lep_fes_down.append(1.0)
                lep_antimusf.append(1.0)
                lep_antimusf_up.append(1.0)
                lep_antimusf_down.append(1.0)
                lep_antielesf.append(1.0)
                lep_antielesf_up.append(1.0)
                lep_antielesf_down.append(1.0)
                lep_taues.append(1.0)
                lep_decaymode.append(-1)
                lep_dz2.append(-99)
                lep_dz3.append(-99)
                lep_tk1Pt.append(-99)
                lep_tk1Eta.append(-99)
                lep_tk1Phi.append(-99)
                lep_tk2Pt.append(-99)
                lep_tk2Eta.append(-99)
                lep_tk2Phi.append(-99)
                lep_tk3Pt.append(-99)
                lep_tk3Eta.append(-99)
                lep_tk3Phi.append(-99)
                lep_taues_up.append(1.0)
                lep_taues_down.append(1.0)
                lep_tautriggersf.append(1.0)
                lep_tautriggersf_up.append(1.0)
                lep_tautriggersf_down.append(1.0)

            if lep.id!=15 and lep.id!=13 and lep.id!=11:
                lep_trgmatch.append(-1)
        
        lep_id     = [lep.id for lep in event.selectedLeptons]
        lep_pt     = [lep.pt for lep in event.selectedLeptons]
        lep_eta    = [lep.eta for lep in event.selectedLeptons]
        lep_phi    = [lep.phi for lep in event.selectedLeptons]
        lep_charge = [lep.charge for lep in event.selectedLeptons]
        lep_dxy    = [lep.dxy for lep in event.selectedLeptons]
        lep_dz     = [lep.dz for lep in event.selectedLeptons]
        lep_gen    = []
	          
        for lep in event.selectedLeptons:
            if self.isMC: 
               lep_gen.append(lep.genPartFlav)
            else: 
                lep_gen.append(-1)

        gen_id     = [genp.pdgId for genp in event.genCand]
        gen_pt     = [genp.pt for genp in event.genCand]
        gen_eta    = [genp.eta for genp in event.genCand]
        gen_phi    = [genp.phi for genp in event.genCand]

        event.pu_weight=-1.0
        if self.isMC:
            dataw = self.datahist.GetBinContent(self.datahist.GetXaxis().FindBin(event.Pileup_nTrueInt))/self.datahist.Integral() 
            mcw   = self.mchist.GetBinContent(self.mchist.GetXaxis().FindBin(event.Pileup_nTrueInt))/self.mchist.Integral() 
            if mcw>0.:
              event.pu_weight = dataw/mcw
              if event.pu_weight>5.: 
                event.pu_weight=5.


        track_pt     = [track.pt for track in event.selectedTracks]
        track_eta     = [track.eta for track in event.selectedTracks]
        track_phi     = [track.phi for track in event.selectedTracks]
        track_dz     = [track.dz for track in event.selectedTracks]
        track_dxy     = [track.dxy for track in event.selectedTracks]
        track_charge     = [track.charge for track in event.selectedTracks]
        track_isMatchedToHS     = [track.isMatchedToGenHS for track in event.selectedTracks]
        track_lostInnerHits     = [track.lostInnerHits for track in event.selectedTracks]
        track_trackHighPurity     = [track.trackHighPurity for track in event.selectedTracks]

        ## store branches
        self.out.fillBranch("nLepCand",              len(event.selectedLeptons))
        self.out.fillBranch("LepCand_id" ,           lep_id)
        self.out.fillBranch("LepCand_pt" ,           lep_pt)
        self.out.fillBranch("LepCand_eta" ,          lep_eta)
        self.out.fillBranch("LepCand_phi" ,          lep_phi)
        self.out.fillBranch("LepCand_charge",        lep_charge)
        self.out.fillBranch("LepCand_dxy",           lep_dxy)
        self.out.fillBranch("LepCand_dz",            lep_dz)
        self.out.fillBranch("LepCand_dz2",            lep_dz2)
        self.out.fillBranch("LepCand_dz3",            lep_dz3)
        self.out.fillBranch("LepCand_tk1Pt",            lep_tk1Pt)
        self.out.fillBranch("LepCand_tk1Eta",            lep_tk1Eta)
        self.out.fillBranch("LepCand_tk1Phi",            lep_tk1Phi)
        self.out.fillBranch("LepCand_tk2Pt",            lep_tk2Pt)
        self.out.fillBranch("LepCand_tk2Eta",            lep_tk2Eta)
        self.out.fillBranch("LepCand_tk2Phi",            lep_tk2Phi)
        self.out.fillBranch("LepCand_tk3Pt",            lep_tk3Pt)
        self.out.fillBranch("LepCand_tk3Eta",            lep_tk3Eta)
        self.out.fillBranch("LepCand_tk3Phi",            lep_tk3Phi)
        self.out.fillBranch("LepCand_gen",           lep_gen)
        self.out.fillBranch("LepCand_vse",           lep_vse)
        self.out.fillBranch("LepCand_vsmu",          lep_vsmu)
        self.out.fillBranch("LepCand_muonMediumId",  lep_muonMediumId)
        self.out.fillBranch("LepCand_muonIso",       lep_muonIso)
        self.out.fillBranch("LepCand_eleMVAiso90",   lep_eleMVAiso90)
        self.out.fillBranch("LepCand_eleMVAiso80",   lep_eleMVAiso80)
        self.out.fillBranch("LepCand_eleMVAisoL",   lep_eleMVAisoL)
        self.out.fillBranch("LepCand_eleMVAnoiso90",   lep_eleMVAnoiso90)
        self.out.fillBranch("LepCand_eleMVAnoiso80",   lep_eleMVAnoiso80)
        self.out.fillBranch("LepCand_eleMVAnoisoL",   lep_eleMVAnoisoL)
        self.out.fillBranch("LepCand_eleIso",        lep_eleIso)
        self.out.fillBranch("LepCand_eleScaleUp",        lep_eleScaleUp)
        self.out.fillBranch("LepCand_eleScaleDown",        lep_eleScaleDown)
        self.out.fillBranch("LepCand_eleSigmaUp",        lep_eleSigmaUp)
        self.out.fillBranch("LepCand_eleSigmaDown",        lep_eleSigmaDown)
        self.out.fillBranch("LepCand_vsjet",         lep_vsjet)
        self.out.fillBranch("LepCand_tauidMsf",      lep_tauidMsf)
        self.out.fillBranch("LepCand_tauidMsf_uncert0_up",      lep_tauidMsf_uncert0_up)
        self.out.fillBranch("LepCand_tauidMsf_uncert1_up",      lep_tauidMsf_uncert1_up)
        self.out.fillBranch("LepCand_tauidMsf_syst_alleras_up",      lep_tauidMsf_syst_alleras_up)
        self.out.fillBranch("LepCand_tauidMsf_syst_era_up",      lep_tauidMsf_syst_era_up)
        self.out.fillBranch("LepCand_tauidMsf_syst_dm_era_up",      lep_tauidMsf_syst_dm_era_up)
        self.out.fillBranch("LepCand_tauidMsf_uncert0_down",      lep_tauidMsf_uncert0_down)
        self.out.fillBranch("LepCand_tauidMsf_uncert1_down",      lep_tauidMsf_uncert1_down)
        self.out.fillBranch("LepCand_tauidMsf_syst_alleras_down",      lep_tauidMsf_syst_alleras_down)
        self.out.fillBranch("LepCand_tauidMsf_syst_era_down",      lep_tauidMsf_syst_era_down)
        self.out.fillBranch("LepCand_tauidMsf_syst_dm_era_down",      lep_tauidMsf_syst_dm_era_down)

        self.out.fillBranch("LepCand_taues",         lep_taues)
        self.out.fillBranch("LepCand_taues_up",      lep_taues_up)
        self.out.fillBranch("LepCand_taues_down",    lep_taues_down)
        self.out.fillBranch("LepCand_antielesf",     lep_antielesf)
        self.out.fillBranch("LepCand_antielesf_up",  lep_antielesf_up)
        self.out.fillBranch("LepCand_antielesf_down",lep_antielesf_down)
        self.out.fillBranch("LepCand_antimusf",      lep_antimusf)
        self.out.fillBranch("LepCand_antimusf_up",   lep_antimusf_up)
        self.out.fillBranch("LepCand_antimusf_down", lep_antimusf_down)
        self.out.fillBranch("LepCand_fes",           lep_fes)
        self.out.fillBranch("LepCand_fes_up",        lep_fes_up)
        self.out.fillBranch("LepCand_fes_down",      lep_fes_down)
        self.out.fillBranch("LepCand_DecayMode", lep_decaymode)
        self.out.fillBranch("LepCand_tautriggersf",lep_tautriggersf)
        self.out.fillBranch("LepCand_tautriggersf_up",lep_tautriggersf_up)
        self.out.fillBranch("LepCand_tautriggersf_down",lep_tautriggersf_down)
        self.out.fillBranch("LepCand_trgmatch",    lep_trgmatch)

        self.out.fillBranch("nElectrons" ,        len(event.selectedElectrons))
        self.out.fillBranch("nMuons" ,            len(event.selectedMuons))
        self.out.fillBranch("nTaus" ,             len(event.selectedTaus))

        self.out.fillBranch("V_genpt",            event.V_genpt)
        self.out.fillBranch("pu_weight",          event.pu_weight)

        self.out.fillBranch("nTracks",             len(event.selectedTracks))
        self.out.fillBranch("Track_pt" ,           track_pt)
        self.out.fillBranch("Track_eta" ,          track_eta)
        self.out.fillBranch("Track_phi" ,          track_phi)
        self.out.fillBranch("Track_dz",            track_dz)
        self.out.fillBranch("Track_dxy",            track_dxy)
        self.out.fillBranch("Track_lostInnerHits" ,    track_lostInnerHits)
        self.out.fillBranch("Track_trackHighPurity" ,  track_trackHighPurity)
        self.out.fillBranch("Track_isMatchedToHS",     track_isMatchedToHS)
        self.out.fillBranch("Track_charge",            track_charge)

        if self.isMC and len(event.genCand)>0: 
            self.out.fillBranch("nGenCand",           len(event.genCand))
            self.out.fillBranch("GenCand_id" ,        gen_id)
            self.out.fillBranch("GenCand_pt" ,        gen_pt)
            self.out.fillBranch("GenCand_eta" ,       gen_eta)
            self.out.fillBranch("GenCand_phi" ,       gen_phi)

        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
analysis_eemc2018    = lambda : Analysis(channel="ee", isMC=True, year="2018")
analysis_emumc2018    = lambda : Analysis(channel="emu", isMC=True, year="2018")
analysis_etaumc2018    = lambda : Analysis(channel="etau", isMC=True, year="2018")
analysis_mumumc2018    = lambda : Analysis(channel="mumu", isMC=True, year="2018")
analysis_mutaumc2018    = lambda : Analysis(channel="mutau", isMC=True, year="2018")
analysis_tautaumc2018    = lambda : Analysis(channel="tautau", isMC=True, year="2018")

analysis_eemc2017    = lambda : Analysis(channel="ee", isMC=True, year="2017")
analysis_emumc2017    = lambda : Analysis(channel="emu", isMC=True, year="2017")
analysis_etaumc2017    = lambda : Analysis(channel="etau", isMC=True, year="2017")
analysis_mumumc2017    = lambda : Analysis(channel="mumu", isMC=True, year="2017")
analysis_mutaumc2017    = lambda : Analysis(channel="mutau", isMC=True, year="2017")
analysis_tautaumc2017    = lambda : Analysis(channel="tautau", isMC=True, year="2017")

analysis_eemc2016post    = lambda : Analysis(channel="ee", isMC=True, year="2016post")
analysis_emumc2016post    = lambda : Analysis(channel="emu", isMC=True, year="2016post")
analysis_etaumc2016post    = lambda : Analysis(channel="etau", isMC=True, year="2016post")
analysis_mumumc2016post    = lambda : Analysis(channel="mumu", isMC=True, year="2016post")
analysis_mutaumc2016post    = lambda : Analysis(channel="mutau", isMC=True, year="2016post")
analysis_tautaumc2016post    = lambda : Analysis(channel="tautau", isMC=True, year="2016post")

analysis_eemc2016pre    = lambda : Analysis(channel="ee", isMC=True, year="2016pre")
analysis_emumc2016pre    = lambda : Analysis(channel="emu", isMC=True, year="2016pre")
analysis_etaumc2016pre    = lambda : Analysis(channel="etau", isMC=True, year="2016pre")
analysis_mumumc2016pre    = lambda : Analysis(channel="mumu", isMC=True, year="2016pre")
analysis_mutaumc2016pre    = lambda : Analysis(channel="mutau", isMC=True, year="2016pre")
analysis_tautaumc2016pre    = lambda : Analysis(channel="tautau", isMC=True, year="2016pre")

analysis_eedata2018  = lambda : Analysis(channel="ee", isMC=False, year="2018")
analysis_emudata2018  = lambda : Analysis(channel="emu", isMC=False, year="2018")
analysis_etaudata2018  = lambda : Analysis(channel="etau", isMC=False, year="2018")
analysis_mumudata2018  = lambda : Analysis(channel="mumu", isMC=False, year="2018")
analysis_mutaudata2018  = lambda : Analysis(channel="mutau", isMC=False, year="2018")
analysis_tautaudata2018  = lambda : Analysis(channel="tautau", isMC=False, year="2018")

analysis_eedata2017  = lambda : Analysis(channel="ee", isMC=False, year="2017")
analysis_emudata2017  = lambda : Analysis(channel="emu", isMC=False, year="2017")
analysis_etaudata2017  = lambda : Analysis(channel="etau", isMC=False, year="2017")
analysis_mumudata2017  = lambda : Analysis(channel="mumu", isMC=False, year="2017")
analysis_mutaudata2017  = lambda : Analysis(channel="mutau", isMC=False, year="2017")
analysis_tautaudata2017  = lambda : Analysis(channel="tautau", isMC=False, year="2017")

analysis_eedata2016  = lambda : Analysis(channel="ee", isMC=False, year="2016")
analysis_emudata2016  = lambda : Analysis(channel="emu", isMC=False, year="2016")
analysis_etaudata2016  = lambda : Analysis(channel="etau", isMC=False, year="2016")
analysis_mumudata2016  = lambda : Analysis(channel="mumu", isMC=False, year="2016")
analysis_mutaudata2016  = lambda : Analysis(channel="mutau", isMC=False, year="2016")
analysis_tautaudata2016  = lambda : Analysis(channel="tautau", isMC=False, year="2016")


