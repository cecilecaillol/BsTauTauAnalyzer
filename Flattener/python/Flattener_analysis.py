#!/usr/bin/env python
import os, sys, math
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module
import correctionlib as _core

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection

### Proton selector be replaced by preprocessing module
from BsTauTauAnalyzer.Flattener.objectSelector import ElectronSelector, MuonSelector, TauSelector, GenParticleSelector

class Analysis(Module):
    def __init__(self, channel, isMC, year):
        self.channel       = channel
        self.isMC          = isMC
        self.year          = year

        cmssw=os.environ['CMSSW_BASE']

	# SFs via correctionlib

        ##https://cms-analysis-corrections.docs.cern.ch/corrections_era/Run3-24CDEReprocessingFGHIPrompt-Summer24-NanoAODv15/MUO/latest/
        muonSF2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/muon_Z_2024.json")
        self.cset_muon_Z = _core.CorrectionSet.from_file(muonSF2024_file)
        self.corr_muonID = self.cset_muon_Z["NUM_TightID_DEN_TrackerMuons"]
        self.corr_muonIso = self.cset_muon_Z["NUM_TightPFIso_DEN_TightID"]
        #self.corr_muonHLTIsoMu = self.cset_muon_Z["NUM_IsoMu24_DEN_CutBasedIdTight_and_PFIsoTight"]

        ##https://cms-analysis-corrections.docs.cern.ch/corrections_era/Run3-24CDEReprocessingFGHIPrompt-Summer24-NanoAODv15/EGM/latest/
        electronSF2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/electron_2024.json")
        self.cset_electron = _core.CorrectionSet.from_file(electronSF2024_file)
        self.corr_electronReco = self.cset_electron["Electron-ID-SF"]
        electronIDSF2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/electronID_2024.json")
        self.cset_electronID = _core.CorrectionSet.from_file(electronIDSF2024_file)
        self.corr_electronID = self.cset_electronID["Electron-ID-SF"]

        ##https://cms-analysis-corrections.docs.cern.ch/corrections_era/Run3-24CDEReprocessingFGHIPrompt-Summer24-NanoAODv15/BTV/latest
        btaggingSF2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/btagging_2024.json")
        self.cset_btagging = _core.CorrectionSet.from_file(btaggingSF2024_file)
        self.corr_btagging = self.cset_btagging["UParTAK4_kinfit"]

        ##https://cms-analysis-corrections.docs.cern.ch/corrections_era/Run3-24CDEReprocessingFGHIPrompt-Summer24-NanoAODv15/JME/latest
        jetid2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/jetid_2024.json")
        self.cset_jetid = _core.CorrectionSet.from_file(jetid2024_file)
        self.corr_jetid = self.cset_jetid["AK4PUPPI_Tight"]

        ##https://cms-analysis-corrections.docs.cern.ch/corrections/JME/Run3-24CDEReprocessingFGHIPrompt-Summer24-NanoAODv15/latest
        jvm2024_file = os.path.join(cmssw+"/src/BsTauTauAnalyzer/Flattener/data/jetvetomaps_2024.json")
        self.cset_jvm = _core.CorrectionSet.from_file(jvm2024_file)
        self.corr_jvm = self.cset_jvm["Summer24Prompt24_RunBCDEFGHI_V1"]

        pass

    def beginJob(self):
        pass

    def endJob(self):
        pass

    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
    
        self.out = wrappedOutputTree

	# declare branches

        if self.channel=="mu" or self.channel=="mumu" or self.channel=="emu":
           self.out.branch("mu1_pt",            "F");
           self.out.branch("mu1_eta",           "F");
           self.out.branch("mu1_phi",           "F");
           self.out.branch("mu1_dxy",            "F");
           self.out.branch("mu1_dz",           "F");
           self.out.branch("mu1_charge",           "F");
           self.out.branch("mu1_tightId",           "I");
           self.out.branch("mu1_iso",           "F");
           self.out.branch("mu1_ID_sf",           "F");
           self.out.branch("mu1_iso_sf",           "F");
           self.out.branch("mu1_singletrg",           "I");
           self.out.branch("mu1_crosstrg",           "I");
           self.out.branch("mu1_doubletrg",           "I");
           #self.out.branch("mu1_HLTIsoMu_sf",           "F");

        if self.channel=="mumu":
           self.out.branch("mu2_pt",            "F");
           self.out.branch("mu2_eta",           "F");
           self.out.branch("mu2_phi",           "F");
           self.out.branch("mu2_dxy",            "F");
           self.out.branch("mu2_dz",           "F");
           self.out.branch("mu2_charge",           "F");
           self.out.branch("mu2_tightId",           "I");
           self.out.branch("mu2_iso",           "F");
           self.out.branch("mu2_ID_sf",           "F");
           self.out.branch("mu2_iso_sf",           "F");
           self.out.branch("mu2_singletrg",           "I");
           self.out.branch("mu2_crosstrg",           "I");
           self.out.branch("mu2_doubletrg",           "I");
           #self.out.branch("mu2_HLTIsoMu_sf",           "F");

        if self.channel=="e" or self.channel=="ee" or self.channel=="emu":
           self.out.branch("e1_pt",            "F");
           self.out.branch("e1_eta",           "F");
           self.out.branch("e1_phi",           "F");
           self.out.branch("e1_dxy",            "F");
           self.out.branch("e1_dz",           "F");
           self.out.branch("e1_charge",           "F");
           self.out.branch("e1_cutbased",           "I");
           self.out.branch("e1_ID_sf",           "F");
           self.out.branch("e1_reco_sf",           "F");
           self.out.branch("e1_singletrg",           "I");
           self.out.branch("e1_crosstrg",           "I");
           self.out.branch("e1_doubletrg",           "I");

        if self.channel=="ee":
           self.out.branch("e2_pt",            "F");
           self.out.branch("e2_eta",           "F");
           self.out.branch("e2_phi",           "F");
           self.out.branch("e2_dxy",            "F");
           self.out.branch("e2_dz",           "F");
           self.out.branch("e2_charge",           "F");
           self.out.branch("e2_cutbased",           "I");
           self.out.branch("e2_ID_sf",           "F");
           self.out.branch("e2_reco_sf",           "F");
           self.out.branch("e2_singletrg",           "I");
           self.out.branch("e2_crosstrg",           "I");
           self.out.branch("e2_doubletrg",           "I");

        self.out.branch("pass_jvm",             "I");

        self.out.branch("nj",             "I");
        self.out.branch("j_pt",        "F",  lenVar = "nj");
        self.out.branch("j_eta",       "F",  lenVar = "nj");
        self.out.branch("j_phi",       "F",  lenVar = "nj");
        self.out.branch("j_m",         "F",  lenVar = "nj");
        self.out.branch("j_puid",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawB",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawC",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawOther",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawSingletau",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawTauhtaue",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawTauhtauh",         "F",  lenVar = "nj");
        #self.out.branch("j_ParTRawTauhtaumu",         "F",  lenVar = "nj");
        self.out.branch("j_deepflavB", "F",  lenVar = "nj");
        self.out.branch("j_upartB", "F",  lenVar = "nj");
        self.out.branch("j_upartB_sfL", "F",  lenVar = "nj");
        self.out.branch("j_upartB_sfM", "F",  lenVar = "nj");
        self.out.branch("j_upartB_sfT", "F",  lenVar = "nj");
        self.out.branch("j_upartB_sfXT", "F",  lenVar = "nj");
        self.out.branch("j_upartB_sfXXT", "F",  lenVar = "nj");
        self.out.branch("j_hadronFlavour", "I",  lenVar = "nj");

        self.out.branch("ntau",             "I");
        self.out.branch("tau_pt",        "F",  lenVar = "ntau");
        self.out.branch("tau_eta",       "F",  lenVar = "ntau");
        self.out.branch("tau_phi",       "F",  lenVar = "ntau");
        self.out.branch("tau_charge",        "I",  lenVar = "ntau");

        self.out.branch("nGenCand",              "I");
        self.out.branch("GenCand_id",            "I",  lenVar = "nGenCand");
        self.out.branch("GenCand_pt",            "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_eta",           "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_phi",           "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_isBsTauTau",            "I",  lenVar = "nGenCand");

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

    def selectMuons(self, event, muSel):
        ## access a collection in nanoaod and create a new collection based on this

        event.selectedMuons = []
        muons = Collection(event, "Muon")
        for mu in muons:
            if not muSel.evalMuon(mu): continue
            setattr(mu, 'id', 13)
            event.selectedMuons.append(mu)

        event.selectedMuons.sort(key=lambda x: x.pt, reverse=True)

    def selectTaus(self, event, tauSel):

        event.selectedTaus = []
        taus = Collection(event, "Tau")
        for tau in taus:
            if not tauSel.evalTau(tau): continue

            #check overlap with selected leptons 
            deltaR_to_leptons=[ tau.p4().DeltaR(lep.p4()) for lep in event.selectedMuons+event.selectedElectrons ]
            hasLepOverlap=sum( [dR<0.4 for dR in deltaR_to_leptons] )
            if hasLepOverlap>0: continue

            setattr(tau, 'id', 15)
            event.selectedTaus.append(tau)

        event.selectedTaus.sort(key=lambda x: x.pt, reverse=True)

    def selectAK4Jets(self, event):
        ## Selected jets: pT>30, |eta|<4.7, pass tight ID

        event.selectedAK4Jets = []
        ak4jets = Collection(event, "Jet")
        for j in ak4jets:
            if abs(j.eta) > 5.191: #extended eta range to value supported by JME
                continue

            # in Run3 PU ID is not recommended

            if not self.corr_jetid.evaluate(j.eta, j.chHEF, j.neHEF, j.chEmEF, j.neEmEF, j.muEF, j.chMultiplicity, j.neMultiplicity, j.chMultiplicity+j.neMultiplicity): continue #pass jetID, need to recalculate on top of NanoAODv15

            #check overlap with selected leptons 
            deltaR_to_leptons=[ j.p4().DeltaR(lep.p4()) for lep in event.selectedMuons+event.selectedElectrons]
            hasLepOverlap=sum( [dR<0.4 for dR in deltaR_to_leptons] )
            if hasLepOverlap>0: continue

            event.selectedAK4Jets.append(j)

        event.selectedAK4Jets.sort(key=lambda x: x.pt, reverse=True)


    def selectTriggerObjects(self, event):
        event.selectedTriggerObjects = []
        triggerobjects = Collection(event, "TrigObj")
        for to in triggerobjects:
           if to.id!=11 and to.id!=13 and to.id!=15: continue
           event.selectedTriggerObjects.append(to)

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        # Noise filters from JME
        if self.year=="2024" or self.year=="2025":
            if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter and event.Flag_ecalBadCalibFilter):
                return False

        if self.year=="2022" or self.year=="2023":
            if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter):
                return False

        #initiate object selector tools:
        elSel = ElectronSelector()
        muSel = MuonSelector()
        tauSel = TauSelector()

        # apply object selection and make channels exclusive based on number of leptons
        self.selectMuons(event, muSel)
        if self.channel=="e" or self.channel=="ee":
            if len(event.selectedMuons)>0: return False
        if self.channel=="mu" or self.channel=="emu":
            if len(event.selectedMuons)!=1: return False
        if self.channel=="mumu":
            if len(event.selectedMuons)!=2: return False

        self.selectElectrons(event, elSel)
        if self.channel=="mu" or self.channel=="mumu":
            if len(event.selectedElectrons)>0: return False
        if self.channel=="e" or self.channel=="emu":
            if len(event.selectedElectrons)!=1: return False
        if self.channel=="ee":
            if len(event.selectedElectrons)!=2: return False

        #apply preliminary loose lepton pt cuts based on trigger:
        if self.channel=="mu":
            if event.selectedMuons[0].pt<25: return False

        if self.channel=="mumu":
            if event.selectedMuons[0].pt<19: return False
            if event.selectedMuons[1].pt<14: return False
            if event.selectedMuons[0].pt<24 and event.selectedMuons[1].pt<24: return False # at least one with pT > 25 GeV

        if self.channel=="e":
            if event.selectedElectrons[0].pt<30: return False

        if self.channel=="ee":
            if event.selectedElectrons[0].pt<19: return False
            if event.selectedElectrons[1].pt<14: return False
            if event.selectedElectrons[0].pt<24 and event.selectedElectrons[1].pt<24: return False # at least one with pT > 25 GeV

        if self.channel=="emu":
            if event.selectedElectrons[0].pt<19: return False
            if event.selectedMuons[0].pt<19: return False
            if event.selectedElectrons[0].pt<24 and event.selectedMuons[0].pt<24: return False # at least one with pT > 25 GeV

	    # select jets and filter events with at least 1 (e/mu channels) or 2 (ee/emu/mumu channels) L btagged jet with pT > 20 GeV
        self.selectAK4Jets(event)
        if len(event.selectedAK4Jets)<1: return False
        event.nbjetL=0
        for j in event.selectedAK4Jets:
            if abs(j.eta)<2.5 and j.btagUParTAK4B>0.0246: event.nbjetL = event.nbjetL+1
        if (self.channel=="e" or self.channel=="mu") and event.nbjetL<2: return False
        if (self.channel=="ee" or self.channel=="emu" or self.channel=="mumu") and event.nbjetL<1: return False

        # select gen particles in simulation
        if self.isMC:
            self.selectGenParticles(event)

        # select gen partucles to save based on pdgid
        event.genCand=[]
        event.genIdx=[]
        idx=0
        if self.isMC:
            for genp in event.selectedGenParticles:
                if (abs(genp.pdgId)==531 or abs(genp.pdgId)==15 or abs(genp.pdgId)==13 or abs(genp.pdgId)==11 or abs(genp.pdgId)==6 or abs(genp.pdgId)==24 or abs(genp.pdgId)==23):
                    event.genCand.append(genp)
                    event.genIdx.append(idx)
                idx=idx+1


        gen_id     = [genp.pdgId for genp in event.genCand]
        gen_pt     = [genp.pt for genp in event.genCand]
        gen_eta    = [genp.eta for genp in event.genCand]
        gen_phi    = [genp.phi for genp in event.genCand]
        gen_isbstt = []
        for k in range(0,len(gen_pt)):
           is_bstt=0
           if abs(gen_id[k])==531:
              for genp in event.selectedGenParticles:
                 if (abs(genp.pdgId)==15 and (abs(event.selectedGenParticles[genp.genPartIdxMother].pdgId)==531 or abs(event.selectedGenParticles[event.selectedGenParticles[genp.genPartIdxMother].genPartIdxMother].pdgId)==531) and (genp.genPartIdxMother==event.genIdx[k] or event.selectedGenParticles[genp.genPartIdxMother].genPartIdxMother==event.genIdx[k])):
                    is_bstt=1
           gen_isbstt.append(is_bstt)

        # save jet variables
        jet_pt     = [jet.pt for jet in event.selectedAK4Jets]
        jet_eta    = [jet.eta for jet in event.selectedAK4Jets]
        jet_phi    = [jet.phi for jet in event.selectedAK4Jets]
        jet_m      = [jet.mass for jet in event.selectedAK4Jets]
        jet_deepflavB = [jet.btagDeepFlavB for jet in event.selectedAK4Jets]
        jet_upartB = [jet.btagUParTAK4B for jet in event.selectedAK4Jets]
        if self.isMC:
           jet_upartB_sfL = [self.corr_btagging.evaluate("central","L",5,min(2.49,abs(jet.eta)),max(20.0,jet.pt)) for jet in event.selectedAK4Jets] #FIXME replace 5 by hadronflavor when the json is updated
           jet_upartB_sfM = [self.corr_btagging.evaluate("central","M",5,min(2.49,abs(jet.eta)),max(20.0,jet.pt)) for jet in event.selectedAK4Jets]
           jet_upartB_sfT = [self.corr_btagging.evaluate("central","T",5,min(2.49,abs(jet.eta)),max(20.0,jet.pt)) for jet in event.selectedAK4Jets]
           jet_upartB_sfXT = [self.corr_btagging.evaluate("central","XT",5,min(2.49,abs(jet.eta)),max(20.0,jet.pt)) for jet in event.selectedAK4Jets]
           jet_upartB_sfXXT = [self.corr_btagging.evaluate("central","XXT",5,min(2.49,abs(jet.eta)),max(20.0,jet.pt)) for jet in event.selectedAK4Jets]
        else: #for data we can store 1
           jet_upartB_sfL = [1.0 for jet in event.selectedAK4Jets] 
           jet_upartB_sfM = [1.0 for jet in event.selectedAK4Jets]
           jet_upartB_sfT = [1.0 for jet in event.selectedAK4Jets]
           jet_upartB_sfXT = [1.0 for jet in event.selectedAK4Jets]
           jet_upartB_sfXXT = [1.0 for jet in event.selectedAK4Jets]
        if self.year=="2024" or self.year=="2025": jet_puid      = [jet.puIdDisc for jet in event.selectedAK4Jets]
        else: jet_puid      = [1.0 for jet in event.selectedAK4Jets]
        #jet_ParTRawB  = [jet.myParTRawB for jet in event.selectedAK4Jets]
        #jet_ParTRawC  = [jet.myParTRawC for jet in event.selectedAK4Jets]
        #jet_ParTRawOther  = [jet.myParTRawOther for jet in event.selectedAK4Jets]
        #jet_ParTRawSingletau  = [jet.myParTRawSingletau for jet in event.selectedAK4Jets]
        #jet_ParTRawTauhtaue  = [jet.myParTRawTauhtaue for jet in event.selectedAK4Jets]
        #jet_ParTRawTauhtauh  = [jet.myParTRawTauhtauh for jet in event.selectedAK4Jets]
        #jet_ParTRawTauhtaumu  = [jet.myParTRawTauhtaumu for jet in event.selectedAK4Jets]
        jet_hadronflavour = []
        for jet in event.selectedAK4Jets:
           if self.isMC:
                jet_hadronflavour.append(jet.hadronFlavour)
           else:
                jet_hadronflavour.append(-1)

        self.selectTaus(event, tauSel)
        tau_pt     = [tau.pt for tau in event.selectedTaus]
        tau_eta    = [tau.eta for tau in event.selectedTaus]
        tau_phi    = [tau.phi for tau in event.selectedTaus]
        tau_charge = [tau.charge for tau in event.selectedTaus]

        # trigger matching
        self.selectTriggerObjects(event)
        def is_trigger_matched(pdgid,trigger,lep):
            for to in event.selectedTriggerObjects:
                top4=ROOT.TLorentzVector()
                top4.SetPtEtaPhiM(to.pt,to.eta,to.phi,0)
                if lep.p4().DeltaR(top4)<0.3:
                    if to.id==pdgid:
                        if trigger=="single" and pdgid==11 and (bool(to.filterBits&1) or bool(to.filterBits&2)): return True
                        if trigger=="cross" and pdgid==11 and bool(to.filterBits&6): return True
                        if trigger=="double" and pdgid==11 and (bool(to.filterBits&4) or bool(to.filterBits&5)): return True
                        if trigger=="single" and pdgid==13 and bool(to.filterBits&3): return True
                        if trigger=="cross" and pdgid==13 and bool(to.filterBits&5): return True
                        if trigger=="double" and pdgid==13 and bool(to.filterBits&4): return True
            return False

	    # lepton branches
        if self.channel=="mu" or self.channel=="mumu" or self.channel=="emu":
               self.out.fillBranch("mu1_pt",             event.selectedMuons[0].pt)
               self.out.fillBranch("mu1_eta",            event.selectedMuons[0].eta)
               self.out.fillBranch("mu1_phi",            event.selectedMuons[0].phi)
               self.out.fillBranch("mu1_dxy",            event.selectedMuons[0].dxy)
               self.out.fillBranch("mu1_dz",             event.selectedMuons[0].dz)
               self.out.fillBranch("mu1_charge",         event.selectedMuons[0].charge)
               self.out.fillBranch("mu1_tightId",        event.selectedMuons[0].tightId)
               self.out.fillBranch("mu1_iso",            event.selectedMuons[0].pfRelIso04_all)
               if self.isMC:
                  self.out.fillBranch("mu1_ID_sf",          self.corr_muonID.evaluate(event.selectedMuons[0].eta,event.selectedMuons[0].pt,"nominal"))
                  self.out.fillBranch("mu1_iso_sf",         self.corr_muonIso.evaluate(event.selectedMuons[0].eta,event.selectedMuons[0].pt,"nominal"))
               else:
                  self.out.fillBranch("mu1_ID_sf",       1.0)
                  self.out.fillBranch("mu1_iso_sf",      1.0)
               self.out.fillBranch("mu1_singletrg",      is_trigger_matched(13,"single",event.selectedMuons[0]))
               self.out.fillBranch("mu1_crosstrg",      is_trigger_matched(13,"cross",event.selectedMuons[0]))
               self.out.fillBranch("mu1_doubletrg",      is_trigger_matched(13,"double",event.selectedMuons[0]))
               #self.out.fillBranch("mu1_HLTIsoMu_sf",    self.corr_muonHLTIsoMu.evaluate(abs(selectedMuons[0].eta),selectedMuons[0].pt,"nominal")) #FIXME not available yet
    
        if self.channel=="mumu":
               self.out.fillBranch("mu2_pt",             event.selectedMuons[1].pt)
               self.out.fillBranch("mu2_eta",            event.selectedMuons[1].eta)
               self.out.fillBranch("mu2_phi",            event.selectedMuons[1].phi)
               self.out.fillBranch("mu2_dxy",            event.selectedMuons[1].dxy)
               self.out.fillBranch("mu2_dz",             event.selectedMuons[1].dz)
               self.out.fillBranch("mu2_charge",         event.selectedMuons[1].charge)
               self.out.fillBranch("mu2_tightId",        event.selectedMuons[1].tightId)
               self.out.fillBranch("mu2_iso",            event.selectedMuons[1].pfRelIso04_all)
               if self.isMC:
                  self.out.fillBranch("mu2_ID_sf",          self.corr_muonID.evaluate(event.selectedMuons[1].eta,event.selectedMuons[1].pt,"nominal"))
                  self.out.fillBranch("mu2_iso_sf",         self.corr_muonIso.evaluate(event.selectedMuons[1].eta,event.selectedMuons[1].pt,"nominal"))
               else:
                  self.out.fillBranch("mu2_ID_sf",       1.0)
                  self.out.fillBranch("mu2_iso_sf",      1.0)
               self.out.fillBranch("mu2_singletrg",      is_trigger_matched(13,"single",event.selectedMuons[1]))
               self.out.fillBranch("mu2_crosstrg",      is_trigger_matched(13,"cross",event.selectedMuons[1]))
               self.out.fillBranch("mu2_doubletrg",      is_trigger_matched(13,"double",event.selectedMuons[1]))
               #self.out.fillBranch("mu2_HLTIsoMu_sf",    self.corr_muonHLTIsoMu.evaluate(abs(selectedMuons[1].eta),selectedMuons[1].pt,"nominal"))
    
        if self.channel=="e" or self.channel=="ee" or self.channel=="emu":
               self.out.fillBranch("e1_pt",        event.selectedElectrons[0].pt)
               self.out.fillBranch("e1_eta",       event.selectedElectrons[0].eta)
               self.out.fillBranch("e1_phi",       event.selectedElectrons[0].phi)
               self.out.fillBranch("e1_dxy",       event.selectedElectrons[0].dxy)
               self.out.fillBranch("e1_dz",        event.selectedElectrons[0].dz)
               self.out.fillBranch("e1_charge",    event.selectedElectrons[0].charge)
               self.out.fillBranch("e1_cutbased",  event.selectedElectrons[0].cutBased)
               self.out.fillBranch("e1_singletrg",      is_trigger_matched(11,"single",event.selectedElectrons[0]))
               self.out.fillBranch("e1_crosstrg",      is_trigger_matched(11,"cross",event.selectedElectrons[0]))
               self.out.fillBranch("e1_doubletrg",      is_trigger_matched(11,"double",event.selectedElectrons[0]))
               if self.isMC:
                  if event.selectedElectrons[0].pt>20 and event.selectedElectrons[0].pt<75:
                      if self.year=="2024" or self.year=="2025": self.out.fillBranch("e1_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","Reco20to75",event.selectedElectrons[0].superclusterEta,event.selectedElectrons[0].pt))
                      else: self.out.fillBranch("e1_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","Reco20to75",event.selectedElectrons[0].eta,event.selectedElectrons[0].pt)) #SC eta not saved in nanoaodv12
                  elif event.selectedElectrons[0].pt>=75: 
                      if self.year=="2024" or self.year=="2025": self.out.fillBranch("e1_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","RecoAbove75",event.selectedElectrons[0].superclusterEta,event.selectedElectrons[0].pt))
                      else: self.out.fillBranch("e1_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","RecoAbove75",event.selectedElectrons[0].eta,event.selectedElectrons[0].pt))
                  else: self.out.fillBranch("e1_reco_sf", 1.0)
                  if self.year=="2024" or self.year=="2025": self.out.fillBranch("e1_ID_sf",     self.corr_electronID.evaluate("2024","sf","Tight",event.selectedElectrons[0].superclusterEta,max(20.0,event.selectedElectrons[0].pt)))
                  else: self.out.fillBranch("e1_ID_sf",     self.corr_electronID.evaluate("2024","sf","Tight",event.selectedElectrons[0].eta,max(20.0,event.selectedElectrons[0].pt)))
               else:
                  self.out.fillBranch("e1_reco_sf",1.0)
                  self.out.fillBranch("e1_ID_sf",1.0)
    
        if self.channel=="ee":
               self.out.fillBranch("e2_pt",         event.selectedElectrons[1].pt)
               self.out.fillBranch("e2_eta",        event.selectedElectrons[1].eta)
               self.out.fillBranch("e2_phi",        event.selectedElectrons[1].phi)
               self.out.fillBranch("e2_dxy",        event.selectedElectrons[0].dxy)
               self.out.fillBranch("e2_dz",         event.selectedElectrons[1].dz)
               self.out.fillBranch("e2_charge",     event.selectedElectrons[1].charge)
               self.out.fillBranch("e2_cutbased",   event.selectedElectrons[1].cutBased)
               self.out.fillBranch("e2_singletrg",      is_trigger_matched(11,"single",event.selectedElectrons[1]))
               self.out.fillBranch("e2_crosstrg",      is_trigger_matched(11,"cross",event.selectedElectrons[1]))
               self.out.fillBranch("e2_doubletrg",      is_trigger_matched(11,"double",event.selectedElectrons[1]))
               if self.isMC:
                  if event.selectedElectrons[1].pt>20 and event.selectedElectrons[1].pt<75:
                     if self.year=="2024" or self.year=="2025": self.out.fillBranch("e2_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","Reco20to75",event.selectedElectrons[1].superclusterEta,event.selectedElectrons[1].pt))
                     else: self.out.fillBranch("e2_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","Reco20to75",event.selectedElectrons[1].eta,event.selectedElectrons[1].pt))
                  elif event.selectedElectrons[1].pt>=75: 
                      if self.year=="2024" or self.year=="2025": self.out.fillBranch("e2_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","RecoAbove75",event.selectedElectrons[1].superclusterEta,event.selectedElectrons[1].pt))
                      else: self.out.fillBranch("e2_reco_sf",   self.corr_electronReco.evaluate("2024Prompt","sf","RecoAbove75",event.selectedElectrons[1].eta,event.selectedElectrons[1].pt))
                  else: self.out.fillBranch("e2_reco_sf", 1.0)
                  if self.year=="2024" or self.year=="2025": self.out.fillBranch("e2_ID_sf",     self.corr_electronID.evaluate("2024","sf","Tight",event.selectedElectrons[1].superclusterEta,max(20.0,event.selectedElectrons[1].pt)))
                  else: self.out.fillBranch("e2_ID_sf",     self.corr_electronID.evaluate("2024","sf","Tight",event.selectedElectrons[1].eta,max(event.selectedElectrons[1].pt,20.0)))
               else:
                  self.out.fillBranch("e2_reco_sf", 1.0)
                  self.out.fillBranch("e2_ID_sf", 1.0)

        # jet veto map (veto the entire event in Run3, veto only the jet in Run2)
        event.pass_jvm=True
        for j in event.selectedAK4Jets:
            if self.corr_jvm.evaluate("jetvetomap",j.eta,j.phi)!=0: event.pass_jvm=False

        self.out.fillBranch("pass_jvm",       event.pass_jvm)

    	# jet branches
        self.out.fillBranch("nj" ,                len(event.selectedAK4Jets))
        self.out.fillBranch("j_pt",               jet_pt);
        self.out.fillBranch("j_eta",              jet_eta);
        self.out.fillBranch("j_phi",              jet_phi);
        self.out.fillBranch("j_m",                jet_m);
        self.out.fillBranch("j_puid",             jet_puid);
        self.out.fillBranch("j_deepflavB",        jet_deepflavB);
        self.out.fillBranch("j_upartB",           jet_upartB);
        self.out.fillBranch("j_upartB_sfL",       jet_upartB_sfL);
        self.out.fillBranch("j_upartB_sfM",       jet_upartB_sfM);
        self.out.fillBranch("j_upartB_sfT",       jet_upartB_sfT);
        self.out.fillBranch("j_upartB_sfXT",      jet_upartB_sfXT);
        self.out.fillBranch("j_upartB_sfXXT",     jet_upartB_sfXXT);
        self.out.fillBranch("j_hadronFlavour", jet_hadronflavour);
        #self.out.fillBranch("j_ParTRawB",         jet_ParTRawB);
        #self.out.fillBranch("j_ParTRawC",         jet_ParTRawC);
        #self.out.fillBranch("j_ParTRawOther",         jet_ParTRawOther);
        #self.out.fillBranch("j_ParTRawSingletau",         jet_ParTRawSingletau);
        #self.out.fillBranch("j_ParTRawTauhtaue",         jet_ParTRawTauhtaue);
        #self.out.fillBranch("j_ParTRawTauhtauh",         jet_ParTRawTauhtauh);
        #self.out.fillBranch("j_ParTRawTauhtaumu",         jet_ParTRawTauhtaumu);
        
        # tau branches
        self.out.fillBranch("ntau" ,          len(event.selectedTaus))
        self.out.fillBranch("tau_pt",         tau_pt);
        self.out.fillBranch("tau_eta",        tau_eta);
        self.out.fillBranch("tau_phi",        tau_phi);
        self.out.fillBranch("tau_charge",     tau_charge);

        # GEN branches 
        if self.isMC:
            self.out.fillBranch("nGenCand",           len(event.genCand))
            self.out.fillBranch("GenCand_id" ,        gen_id)
            self.out.fillBranch("GenCand_pt" ,        gen_pt)
            self.out.fillBranch("GenCand_eta" ,       gen_eta)
            self.out.fillBranch("GenCand_phi" ,       gen_phi)
            self.out.fillBranch("GenCand_isBsTauTau" ,        gen_isbstt)
        
        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
analysis_emc2025    = lambda : Analysis(channel="e", isMC=True, year="2025")
analysis_mumc2025    = lambda : Analysis(channel="mu", isMC=True, year="2025")
analysis_emumc2025    = lambda : Analysis(channel="emu", isMC=True, year="2025")
analysis_eemc2025    = lambda : Analysis(channel="ee", isMC=True, year="2025")
analysis_mumumc2025    = lambda : Analysis(channel="mumu", isMC=True, year="2025")

analysis_edata2025  = lambda : Analysis(channel="e", isMC=False, year="2025")
analysis_mudata2025  = lambda : Analysis(channel="mu", isMC=False, year="2025")
analysis_emudata2025  = lambda : Analysis(channel="emu", isMC=False, year="2025")
analysis_eedata2025  = lambda : Analysis(channel="ee", isMC=False, year="2025")
analysis_mumudata2025  = lambda : Analysis(channel="mumu", isMC=False, year="2025")

analysis_emc2024    = lambda : Analysis(channel="e", isMC=True, year="2024")
analysis_mumc2024    = lambda : Analysis(channel="mu", isMC=True, year="2024")
analysis_emumc2024    = lambda : Analysis(channel="emu", isMC=True, year="2024")
analysis_eemc2024    = lambda : Analysis(channel="ee", isMC=True, year="2024")
analysis_mumumc2024    = lambda : Analysis(channel="mumu", isMC=True, year="2024")

analysis_edata2024  = lambda : Analysis(channel="e", isMC=False, year="2024")
analysis_mudata2024  = lambda : Analysis(channel="mu", isMC=False, year="2024")
analysis_emudata2024  = lambda : Analysis(channel="emu", isMC=False, year="2024")
analysis_eedata2024  = lambda : Analysis(channel="ee", isMC=False, year="2024")
analysis_mumudata2024  = lambda : Analysis(channel="mumu", isMC=False, year="2024")

analysis_emc2023    = lambda : Analysis(channel="e", isMC=True, year="2023")
analysis_mumc2023    = lambda : Analysis(channel="mu", isMC=True, year="2023")
analysis_emumc2023    = lambda : Analysis(channel="emu", isMC=True, year="2023")
analysis_eemc2023    = lambda : Analysis(channel="ee", isMC=True, year="2023")
analysis_mumumc2023    = lambda : Analysis(channel="mumu", isMC=True, year="2023")

analysis_edata2023  = lambda : Analysis(channel="e", isMC=False, year="2023")
analysis_mudata2023  = lambda : Analysis(channel="mu", isMC=False, year="2023")
analysis_emudata2023  = lambda : Analysis(channel="emu", isMC=False, year="2023")
analysis_eedata2023  = lambda : Analysis(channel="ee", isMC=False, year="2023")
analysis_mumudata2023  = lambda : Analysis(channel="mumu", isMC=False, year="2023")

analysis_emc2022    = lambda : Analysis(channel="e", isMC=True, year="2022")
analysis_mumc2022    = lambda : Analysis(channel="mu", isMC=True, year="2022")
analysis_emumc2022    = lambda : Analysis(channel="emu", isMC=True, year="2022")
analysis_eemc2022    = lambda : Analysis(channel="ee", isMC=True, year="2022")
analysis_mumumc2022    = lambda : Analysis(channel="mumu", isMC=True, year="2022")

analysis_edata2022  = lambda : Analysis(channel="e", isMC=False, year="2022")
analysis_mudata2022  = lambda : Analysis(channel="mu", isMC=False, year="2022")
analysis_emudata2022  = lambda : Analysis(channel="emu", isMC=False, year="2022")
analysis_eedata2022  = lambda : Analysis(channel="ee", isMC=False, year="2022")
analysis_mumudata2022  = lambda : Analysis(channel="mumu", isMC=False, year="2022")

