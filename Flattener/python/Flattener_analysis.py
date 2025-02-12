#!/usr/bin/env python
import os, sys, math
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module
#import correctionlib as _core

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

        ##https://gitlab.cern.ch/cms-nanoAOD/jsonpog-integration/-/tree/master/POG/MUO?ref_type=heads
	#muonSF2018UL_file = os.path.join(cmssw+"src/BsTauTauAnalyzer/Flattener/data/muon_Z_2018UL.json")
        #self.cset_muon_Z = _core.CorrectionSet.from_file(muonSF2018UL_file)
        #self.corr_muonID = self.cset_muon_Z["NUM_TightID_DEN_genTracks"]
        #self.corr_muonIso = self.cset_muon_Z["NUM_TightRelIso_DEN_TightIDandIPCut"]
        #self.corr_muonHLTIsoMu = self.cset_muon_Z["NUM_IsoMu24_DEN_CutBasedIdTight_and_PFIsoTight"]

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
           #self.out.branch("mu1_ID_sf",           "F");
           #self.out.branch("mu1_iso_sf",           "F");
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

           #self.out.branch("mu2_ID_sf",           "F");
           #self.out.branch("mu2_iso_sf",           "F");
           #self.out.branch("mu2_HLTIsoMu_sf",           "F");

        if self.channel=="e" or self.channel=="ee" or self.channel=="emu":
           self.out.branch("e1_pt",            "F");
           self.out.branch("e1_eta",           "F");
           self.out.branch("e1_phi",           "F");
           self.out.branch("e1_dxy",            "F");
           self.out.branch("e1_dz",           "F");
           self.out.branch("e1_charge",           "F");
           self.out.branch("e1_cutbased",           "I");

        if self.channel=="ee":
           self.out.branch("e2_pt",            "F");
           self.out.branch("e2_eta",           "F");
           self.out.branch("e2_phi",           "F");
           self.out.branch("e2_dxy",            "F");
           self.out.branch("e2_dz",           "F");
           self.out.branch("e2_charge",           "F");
           self.out.branch("e2_cutbased",           "I");

        self.out.branch("nj",             "I");
        self.out.branch("j_pt",        "F",  lenVar = "nj");
        self.out.branch("j_eta",       "F",  lenVar = "nj");
        self.out.branch("j_phi",       "F",  lenVar = "nj");
        self.out.branch("j_m",         "F",  lenVar = "nj");
        self.out.branch("j_puid",         "I",  lenVar = "nj");
        self.out.branch("j_jetid",         "I",  lenVar = "nj");
        self.out.branch("j_deepflavB", "F",  lenVar = "nj");
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
            #if j.pt<30 :
            #    continue
            if abs(j.eta) > 2.5:
                continue

            ##require tight (2^1) or tightLepVeto (2^2) [https://twiki.cern.ch/twiki/bin/view/CMS/JetID#nanoAOD_Flags]
            #if j.jetId<2:
            #    continue
            ## https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID puId==0 means 000: fail all PU ID; puId==4 means 100: pass loose ID, fail medium, fail tight; puId==6 means 110: pass loose and medium ID, fail tight; puId==7 means 111: pass loose, medium, tight ID. 
            #if j.pt<50 and j.puId<1:
            #    continue

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
        if self.year=="2017" or self.year=="2018":
           if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter and event.Flag_ecalBadCalibFilter):
              return False

        if self.year=="2016" or self.year=="2016pre" or self.year=="2016post":
           if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter and event.Flag_BadPFMuonDzFilter and event.Flag_hfNoisyHitsFilter and event.Flag_eeBadScFilter): #FIXME add noisy hit filter https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFiltersRun2#UL_data
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

        self.selectTaus(event, tauSel)

	## select trigger objects to do trigger matching
        #self.selectTriggerObjects(event)

	# select gen particles in simulation
        if self.isMC:
            self.selectGenParticles(event)

        #apply preliminary loose lepton pt cuts based on trigger:
        if self.channel=="mu":
            if event.selectedMuons[0].pt<29: return False

        if self.channel=="mumu":
            if event.selectedMuons[0].pt<19: return False
            if event.selectedMuons[1].pt<14: return False

        if self.channel=="e":
            if event.selectedElectrons[0].pt<29: return False

        if self.channel=="ee":
            if event.selectedElectrons[0].pt<19: return False
            if event.selectedElectrons[1].pt<14: return False

        if self.channel=="emu":
            if event.selectedElectrons[0].pt<19: return False
            if event.selectedMuons[0].pt<19: return False


	# select jets and filter events with at least 1 jet with pT > 30 GeV
        self.selectAK4Jets(event)
        if len(event.selectedAK4Jets)<1: return False
        #has_jetpt30=False
        #for jet in event.selectedAK4Jets:
        #   if jet.pt>30: has_jetpt30=True
	#if not has_jetpt30: return False

      	######################################################
      	###############  GEN-LEVEL ANALYSIS ##################
      	######################################################

        event.genCand=[]

        if self.isMC:
            for genp in event.selectedGenParticles:
                if (abs(genp.pdgId)==531 or abs(genp.pdgId)==15 or abs(genp.pdgId)==13 or abs(genp.pdgId)==11 or abs(genp.pdgId)==6 or abs(genp.pdgId)==24 or abs(genp.pdgId)==23):
                    event.genCand.append(genp)


        ######################################################
        ##### HIGH LEVEL VARIABLES FOR SELECTED EVENTS   #####
        ######################################################
        
        gen_id     = [genp.pdgId for genp in event.genCand]
        gen_pt     = [genp.pt for genp in event.genCand]
        gen_eta    = [genp.eta for genp in event.genCand]
        gen_phi    = [genp.phi for genp in event.genCand]

        jet_pt     = [jet.pt for jet in event.selectedAK4Jets]
        jet_eta    = [jet.eta for jet in event.selectedAK4Jets]
        jet_phi    = [jet.phi for jet in event.selectedAK4Jets]
        jet_m      = [jet.mass for jet in event.selectedAK4Jets]
        jet_deepflavB = [jet.btagDeepFlavB for jet in event.selectedAK4Jets]
        jet_puid      = [jet.puId for jet in event.selectedAK4Jets]
        jet_jetid      = [jet.jetId for jet in event.selectedAK4Jets]
        jet_hadronflavour = []
        for jet in event.selectedAK4Jets:
           if self.isMC:
                jet_hadronflavour.append(jet.hadronFlavour)
           else:
                jet_hadronflavour.append(-1)

        tau_pt     = [tau.pt for tau in event.selectedTaus]
        tau_eta    = [tau.eta for tau in event.selectedTaus]
        tau_phi    = [tau.phi for tau in event.selectedTaus]
        tau_charge = [tau.charge for tau in event.selectedTaus]

	################################################
        ######### store branches #######################
	################################################

	# lepton branches
	if self.channel=="mu" or self.channel=="mumu" or self.channel=="emu":
           self.out.fillBranch("mu1_pt",             event.selectedMuons[0].pt)
           self.out.fillBranch("mu1_eta",            event.selectedMuons[0].eta)
           self.out.fillBranch("mu1_phi",            event.selectedMuons[0].phi)
           self.out.fillBranch("mu1_dxy",            event.selectedMuons[0].dxy)
           self.out.fillBranch("mu1_dz",             event.selectedMuons[0].dz)
           self.out.fillBranch("mu1_charge",         event.selectedMuons[0].charge)
           self.out.fillBranch("mu1_tightId",         event.selectedMuons[0].tightId)
           self.out.fillBranch("mu1_iso",         event.selectedMuons[0].pfRelIso04_all)
           #self.out.fillBranch("mu1_ID_sf",          self.corr_muonID.evaluate(abs(selectedMuons[0].eta),selectedMuons[0].pt,"nominal"))
           #self.out.fillBranch("mu1_iso_sf",         self.corr_muonIso.evaluate(abs(selectedMuons[0].eta),selectedMuons[0].pt,"nominal"))
           #self.out.fillBranch("mu1_HLTIsoMu_sf",    self.corr_muonHLTIsoMu.evaluate(abs(selectedMuons[0].eta),selectedMuons[0].pt,"nominal"))

        if self.channel=="mumu":
           self.out.fillBranch("mu2_pt",             event.selectedMuons[1].pt)
           self.out.fillBranch("mu2_eta",            event.selectedMuons[1].eta)
           self.out.fillBranch("mu2_phi",            event.selectedMuons[1].phi)
           self.out.fillBranch("mu2_dxy",            event.selectedMuons[1].dxy)
           self.out.fillBranch("mu2_dz",             event.selectedMuons[1].dz)
           self.out.fillBranch("mu2_charge",         event.selectedMuons[1].charge)
           self.out.fillBranch("mu2_tightId",        event.selectedMuons[1].tightId)
           self.out.fillBranch("mu2_iso",            event.selectedMuons[1].pfRelIso04_all)
           #self.out.fillBranch("mu2_ID_sf",          self.corr_muonID.evaluate(abs(selectedMuons[1].eta),selectedMuons[1].pt,"nominal"))
           #self.out.fillBranch("mu2_iso_sf",         self.corr_muonIso.evaluate(abs(selectedMuons[1].eta),selectedMuons[1].pt,"nominal"))
           #self.out.fillBranch("mu2_HLTIsoMu_sf",    self.corr_muonHLTIsoMu.evaluate(abs(selectedMuons[1].eta),selectedMuons[1].pt,"nominal"))

        if self.channel=="e" or self.channel=="ee" or self.channel=="emu":
           self.out.fillBranch("e1_pt",        event.selectedElectrons[0].pt)
           self.out.fillBranch("e1_eta",       event.selectedElectrons[0].eta)
           self.out.fillBranch("e1_phi",       event.selectedElectrons[0].phi)
           self.out.fillBranch("e1_dxy",       event.selectedElectrons[0].dxy)
           self.out.fillBranch("e1_dz",        event.selectedElectrons[0].dz)
           self.out.fillBranch("e1_charge",    event.selectedElectrons[0].charge)
           self.out.fillBranch("e1_cutbased",  event.selectedElectrons[0].cutBased)

        if self.channel=="ee":
           self.out.fillBranch("e2_pt",         event.selectedElectrons[1].pt)
           self.out.fillBranch("e2_eta",        event.selectedElectrons[1].eta)
           self.out.fillBranch("e2_phi",        event.selectedElectrons[1].phi)
           self.out.fillBranch("e2_dxy",        event.selectedElectrons[0].dxy)
           self.out.fillBranch("e2_dz",         event.selectedElectrons[1].dz)
           self.out.fillBranch("e2_charge",     event.selectedElectrons[1].charge)
           self.out.fillBranch("e2_cutbased",   event.selectedElectrons[1].cutBased)

	# jet branches
        self.out.fillBranch("nj" ,             len(event.selectedAK4Jets))
        self.out.fillBranch("j_pt",            jet_pt);
        self.out.fillBranch("j_eta",           jet_eta);
        self.out.fillBranch("j_phi",           jet_phi);
        self.out.fillBranch("j_m",             jet_m);
        self.out.fillBranch("j_puid",          jet_puid);
        self.out.fillBranch("j_jetid",         jet_jetid);
        self.out.fillBranch("j_deepflavB",     jet_deepflavB);
        self.out.fillBranch("j_hadronFlavour", jet_hadronflavour);

        # jet branches
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

        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
analysis_emc2018    = lambda : Analysis(channel="e", isMC=True, year="2018")
analysis_mumc2018    = lambda : Analysis(channel="mu", isMC=True, year="2018")
analysis_emumc2018    = lambda : Analysis(channel="emu", isMC=True, year="2018")
analysis_eemc2018    = lambda : Analysis(channel="ee", isMC=True, year="2018")
analysis_mumumc2018    = lambda : Analysis(channel="mumu", isMC=True, year="2018")

analysis_emc2017    = lambda : Analysis(channel="e", isMC=True, year="2017")
analysis_mumc2017    = lambda : Analysis(channel="mu", isMC=True, year="2017")
analysis_emumc2017    = lambda : Analysis(channel="emu", isMC=True, year="2017")
analysis_eemc2017    = lambda : Analysis(channel="ee", isMC=True, year="2017")
analysis_mumumc2017    = lambda : Analysis(channel="mumu", isMC=True, year="2017")

analysis_emc2016post    = lambda : Analysis(channel="e", isMC=True, year="2016post")
analysis_mumc2016post    = lambda : Analysis(channel="mu", isMC=True, year="2016post")
analysis_emumc2016post    = lambda : Analysis(channel="emu", isMC=True, year="2016post")
analysis_eemc2016post    = lambda : Analysis(channel="ee", isMC=True, year="2016post")
analysis_mumumc2016post    = lambda : Analysis(channel="mumu", isMC=True, year="2016post")

analysis_emc2016pre    = lambda : Analysis(channel="e", isMC=True, year="2016pre")
analysis_mumc2016pre    = lambda : Analysis(channel="mu", isMC=True, year="2016pre")
analysis_emumc2016pre    = lambda : Analysis(channel="emu", isMC=True, year="2016pre")
analysis_eemc2016pre    = lambda : Analysis(channel="ee", isMC=True, year="2016pre")
analysis_mumumc2016pre    = lambda : Analysis(channel="mumu", isMC=True, year="2016pre")


analysis_edata2018  = lambda : Analysis(channel="e", isMC=False, year="2018")
analysis_mudata2018  = lambda : Analysis(channel="mu", isMC=False, year="2018")
analysis_emudata2018  = lambda : Analysis(channel="emu", isMC=False, year="2018")
analysis_eedata2018  = lambda : Analysis(channel="ee", isMC=False, year="2018")
analysis_mumudata2018  = lambda : Analysis(channel="mumu", isMC=False, year="2018")

analysis_edata2017  = lambda : Analysis(channel="e", isMC=False, year="2017")
analysis_mudata2017  = lambda : Analysis(channel="mu", isMC=False, year="2017")
analysis_emudata2017  = lambda : Analysis(channel="emu", isMC=False, year="2017")
analysis_eedata2017  = lambda : Analysis(channel="ee", isMC=False, year="2017")
analysis_mumudata2017  = lambda : Analysis(channel="mumu", isMC=False, year="2017")

analysis_edata2016  = lambda : Analysis(channel="e", isMC=False, year="2016")
analysis_mudata2016  = lambda : Analysis(channel="mu", isMC=False, year="2016")
analysis_emudata2016  = lambda : Analysis(channel="emu", isMC=False, year="2016")
analysis_eedata2016  = lambda : Analysis(channel="ee", isMC=False, year="2016")
analysis_mumudata2016  = lambda : Analysis(channel="mumu", isMC=False, year="2016")


