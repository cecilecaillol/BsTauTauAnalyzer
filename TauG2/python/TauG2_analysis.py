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

class Analysis(Module):
    def __init__(self, channel, isMC):
        self.channel       = channel
        self.isMC          = isMC
        self.tauSFsM       = TauIDSFTool('UL2018','DeepTau2017v2p1VSjet','Medium')
	self.testool       = TauESTool('UL2018','DeepTau2017v2p1VSjet')
        self.antiEleSFTool = TauIDSFTool('UL2018','DeepTau2017v2p1VSe','Loose')
        self.antiMuSFTool  = TauIDSFTool('UL2018','DeepTau2017v2p1VSmu','Tight')
        self.festool       = TauFESTool('UL2018')

	cmssw=os.environ['CMSSW_BASE']
        datafilename = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","Data_PileUp_UL2018_69p2.root")
        mcfilename   = os.path.join(cmssw+"/src/MyNanoAnalyzer/TauG2/data/","MC_PileUp_UL2018.root")
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
        self.out.branch("LepCand_eleIso",        "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_tauidMsf",      "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_tauidMsf_up",    "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_tauidMsf_down",  "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_taues",         "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_taues_up",      "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_taues_down",    "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_fes",           "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_fes_up",        "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_fes_down",      "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antimusf",      "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_antimusf_up",   "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_antimusf_down", "F",  lenVar = "nLepCand");
        self.out.branch("LepCand_antielesf",     "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_antielesf_up",  "F",  lenVar = "nLepCand");
        #self.out.branch("LepCand_antielesf_down","F",  lenVar = "nLepCand");
        self.out.branch("nGenCand",              "I");
        self.out.branch("GenCand_id",            "I",  lenVar = "nGenCand");
        self.out.branch("GenCand_pt",            "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_eta",           "F",  lenVar = "nGenCand");
        self.out.branch("GenCand_phi",           "F",  lenVar = "nGenCand");

        self.out.branch("nJets",             "I");
        self.out.branch("nElectrons",        "I");
        self.out.branch("nMuons",            "I");
        self.out.branch("nTaus",             "I");

        self.out.branch("JetCand_pt",        "F",  lenVar = "nJets");
        self.out.branch("JetCand_eta",       "F",  lenVar = "nJets");
        self.out.branch("JetCand_phi",       "F",  lenVar = "nJets");
        self.out.branch("JetCand_m",         "F",  lenVar = "nJets");
        self.out.branch("JetCand_puid",      "I",  lenVar = "nJets");
        self.out.branch("JetCand_jetid",     "I",  lenVar = "nJets");
        self.out.branch("JetCand_deepflavB", "F",  lenVar = "nJets");

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


    def selectAK4Jets(self, event):
        ## Selected jets: pT>30, |eta|<4.7, pass tight ID
        
        event.selectedAK4Jets = []
        ak4jets = Collection(event, "Jet")
        for j in ak4jets:

            if j.pt<30 : 
                continue

            if abs(j.eta) > 4.7:
                continue
            
            ##require tight (2^1) or tightLepVeto (2^2) [https://twiki.cern.ch/twiki/bin/view/CMS/JetID#nanoAOD_Flags]
            if j.jetId<2: 
                continue

            ## https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID puId==0 means 000: fail all PU ID; puId==4 means 100: pass loose ID, fail medium, fail tight; puId==6 means 110: pass loose and medium ID, fail tight; puId==7 means 111: pass loose, medium, tight ID. 
	    if j.puId<1: 
	    	continue
                
            #check overlap with selected leptons 
            deltaR_to_leptons=[ j.p4().DeltaR(lep.p4()) for lep in event.selectedMuons+event.selectedElectrons+event.selectedTaus ]
            hasLepOverlap=sum( [dR<0.4 for dR in deltaR_to_leptons] )
            if hasLepOverlap>0: continue

            event.selectedAK4Jets.append(j)
            
        event.selectedAK4Jets.sort(key=lambda x: x.pt, reverse=True)


    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #print "New event"

	# Apply MET filters

	if not (event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_BadPFMuonFilter):
	   return False
	if not self.isMC and not event.Flag_eeBadScFilter:
	   return False
        
        #initiate object selector tools:
        elSel = ElectronSelector()
        tauSel = TauSelector()
        muSel = MuonSelector(minPt=20, ID='medium')
        
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
            if len(event.selectedElectrons)<1: return False
        if self.channel=="tautau":
            if len(event.selectedElectrons)<2: return False

        self.selectAK4Jets(event)

	if self.isMC:
	   self.selectGenParticles(event)
        
        #apply preliminary loose pt cuts based on trigger:
        if self.channel=="mutau" or self.channel=="mumu":
	    if event.selectedMuons[0].pt<20: return False

        if self.channel=="etau" or self.channel=="ee":
            if event.selectedElectrons[0].pt<25: return False

        if self.channel=="tautau":
            if event.selectedTaus[0].pt<45: return False

        if self.channel=="emu":
            if event.selectedElectrons[0].pt<24 and event.selectedMuons[0].pt<24: return False

	#apply channel-dependent tau ID cuts
        if self.channel=="mutau":
	    if event.selectedTaus[0].idDeepTau2017v2p1VSmu<8: return False #pass tight VSmu

        if self.channel=="etau":
            if event.selectedTaus[0].idDeepTau2017v2p1VSe<32: return False #pass tight VSe


	######################################################
	###############  GEN-LEVEL ANALYSIS ##################
	######################################################

	event.genCand=[]
	event.V_genpt=-1.0;

	for genp in event.selectedGenParticles:
	   if abs(genp.pdgId)==15 and len(event.genCand)<2:
	      event.genCand.append(genp)

	if self.isMC:
	   for genp in event.selectedGenParticles:
		if (abs(genp.pdgId)==23 or abs(genp.pdgId)==24) and event.V_genpt<0:
		   event.V_genpt=genp.pt

        ######################################################
        ##### HIGH LEVEL VARIABLES FOR SELECTED EVENTS   #####
        ######################################################
        
        event.selectedLeptons=event.selectedElectrons+event.selectedMuons+event.selectedTaus
        event.selectedLeptons.sort(key=lambda x: x.pt, reverse=True)

	lep_vsjet=[]
        lep_vse=[]
        lep_vsmu=[]
	lep_tauidMsf=[]
        #lep_tauidMsf_up=[]
        #lep_tauidMsf_down=[]
        lep_taues=[]
        #lep_taues_up=[]
        #lep_taues_down=[]
        lep_antielesf=[]
        #lep_antielesf_up=[]
        #lep_antielesf_down=[]
        lep_antimusf=[]
        #lep_antimusf_up=[]
        #lep_antimusf_down=[]
        lep_fes=[]
        #lep_fes_up=[]
        #lep_fes_down=[]
	lep_muonMediumId=[]
	lep_muonIso=[]
	lep_eleMVAiso90=[]
	lep_eleMVAiso80=[]
	lep_eleIso=[]

	for lep in event.selectedLeptons:
	   if lep.id==11:
              lep_eleMVAiso90.append(lep.mvaFall17V2Iso_WP90)
              lep_eleMVAiso80.append(lep.mvaFall17V2Iso_WP80)
              lep_eleIso.append(lep.miniPFRelIso_all)
	   else:
              lep_eleMVAiso90.append(-1)
              lep_eleMVAiso80.append(-1)
              lep_eleIso.append(-1)
	   if lep.id==13:
	      lep_muonMediumId.append(lep.mediumId)
              lep_muonIso.append(lep.pfRelIso04_all)
	   else:
              lep_muonMediumId.append(-1)
              lep_muonIso.append(-1)
	   if lep.id==15:
	      lep_vsjet.append(lep.idDeepTau2017v2p1VSjet)
              lep_vse.append(lep.idDeepTau2017v2p1VSe)
              lep_vsmu.append(lep.idDeepTau2017v2p1VSmu)
	      if self.isMC and lep.genPartFlav==5:
                 lep_tauidMsf.append(self.tauSFsM.getSFvsPT(lep.pt))
                 #lep_tauidMsf_up.append(self.tauSFsM.getSFvsPT(lep.pt,unc='Up'))
                 #lep_tauidMsf_down.append(self.tauSFsM.getSFvsPT(lep.pt,unc='Down'))
                 lep_taues.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav))
                 #lep_taues_up.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav,unc='Up'))
                 #lep_taues_down.append(self.testool.getTES(lep.pt,lep.decayMode,lep.genPartFlav,unc='Down'))
	      else:
                 lep_tauidMsf.append(1.0)
                 #lep_tauidMsf_up.append(1.0)
                 #lep_tauidMsf_down.append(1.0)
                 lep_taues.append(1.0)
                 #lep_taues_up.append(1.0)
                 #lep_taues_down.append(1.0)
	      if self.isMC and (lep.genPartFlav==2 or lep.genPartFlav==4):
	         lep_antimusf.append(self.antiMuSFTool.getSFvsEta(lep.eta,lep.genPartFlav))
                 #lep_antimusf_up.append(self.antiMuSFTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                 #lep_antimusf_down.append(self.antiMuSFTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
	      else:
                 lep_antimusf.append(1.0)
                 #lep_antimusf_up.append(1.0)
                 #lep_antimusf_down.append(1.0)
              if self.isMC and (lep.genPartFlav==1 or lep.genPartFlav==3):
                 lep_antielesf.append(self.antiEleSFTool.getSFvsEta(lep.eta,lep.genPartFlav))
                 #lep_antielesf_up.append(self.antiEleSFTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Up'))
                 #lep_antielesf_down.append(self.antiEleSFTool.getSFvsEta(lep.eta,lep.genPartFlav,unc='Down'))
	         lep_fes.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav))
                 #lep_fes_up.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav,unc='Up'))
                 #lep_fes_down.append(self.festool.getFES(lep.eta,lep.decayMode,lep.genPartFlav,unc='Down'))
	      else:
                 lep_antielesf.append(1.0)
                 #lep_antielesf_up.append(1.0)
                 #lep_antielesf_down.append(1.0)
                 lep_fes.append(1.0)
                 #lep_fes_up.append(1.0)
                 #lep_fes_down.append(1.0)

	   else:
	      lep_vsjet.append(0)
              lep_vse.append(0)
              lep_vsmu.append(0)
	      lep_tauidMsf.append(1.0)
              #lep_tauidMsf_up.append(1.0)
              #lep_tauidMsf_down.append(1.0)
              lep_fes.append(1.0)
              #lep_fes_up.append(1.0)
              #lep_fes_down.append(1.0)
              lep_antimusf.append(1.0)
              #lep_antimusf_up.append(1.0)
              #lep_antimusf_down.append(1.0)
              lep_antielesf.append(1.0)
              #lep_antielesf_up.append(1.0)
              #lep_antielesf_down.append(1.0)
              lep_taues.append(1.0)
              #lep_taues_up.append(1.0)
              #lep_taues_down.append(1.0)
        
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

        jet_pt     = [jet.pt for jet in event.selectedAK4Jets]
        jet_eta    = [jet.eta for jet in event.selectedAK4Jets]
        jet_phi    = [jet.phi for jet in event.selectedAK4Jets]
        jet_m      = [jet.mass for jet in event.selectedAK4Jets]
	jet_deepflavB = [jet.btagDeepFlavB for jet in event.selectedAK4Jets]
	jet_puid      = [jet.puId for jet in event.selectedAK4Jets]
        jet_jetid      = [jet.jetId for jet in event.selectedAK4Jets]

	event.pu_weight=-1.0
	if self.isMC:
	   dataw = self.datahist.GetBinContent(self.datahist.GetXaxis().FindBin(event.Pileup_nTrueInt))/self.datahist.Integral() 
           mcw   = self.mchist.GetBinContent(self.mchist.GetXaxis().FindBin(event.Pileup_nTrueInt))/self.mchist.Integral() 
           if mcw>0.:
              event.pu_weight = dataw/mcw
              if event.pu_weight>5.: 
	         event.pu_weight=5.

        ## store branches
        self.out.fillBranch("nLepCand",              len(event.selectedLeptons))
        self.out.fillBranch("LepCand_id" ,           lep_id)
        self.out.fillBranch("LepCand_pt" ,           lep_pt)
        self.out.fillBranch("LepCand_eta" ,          lep_eta)
        self.out.fillBranch("LepCand_phi" ,          lep_phi)
        self.out.fillBranch("LepCand_charge",        lep_charge)
        self.out.fillBranch("LepCand_dxy",           lep_dxy)
        self.out.fillBranch("LepCand_dz",            lep_dz)
        self.out.fillBranch("LepCand_gen",           lep_gen)
        self.out.fillBranch("LepCand_vse",           lep_vse)
        self.out.fillBranch("LepCand_vsmu",          lep_vsmu)
        self.out.fillBranch("LepCand_muonMediumId",  lep_muonMediumId)
        self.out.fillBranch("LepCand_muonIso",       lep_muonIso)
        self.out.fillBranch("LepCand_eleMVAiso90",   lep_eleMVAiso90)
        self.out.fillBranch("LepCand_eleMVAiso80",   lep_eleMVAiso80)
        self.out.fillBranch("LepCand_eleIso",        lep_eleIso)
        self.out.fillBranch("LepCand_vsjet",         lep_vsjet)
        self.out.fillBranch("LepCand_tauidMsf",      lep_tauidMsf)
        #self.out.fillBranch("LepCand_tauidMsf_up",   lep_tauidMsf_up)
        #self.out.fillBranch("LepCand_tauidMsf_down", lep_tauidMsf_down)
        self.out.fillBranch("LepCand_taues",         lep_taues)
        #self.out.fillBranch("LepCand_taues_up",      lep_taues_up)
        #self.out.fillBranch("LepCand_taues_down",    lep_taues_down)
        self.out.fillBranch("LepCand_antielesf",     lep_antielesf)
        #self.out.fillBranch("LepCand_antielesf_up",  lep_antielesf_up)
        #self.out.fillBranch("LepCand_antielesf_down",lep_antielesf_down)
        self.out.fillBranch("LepCand_antimusf",      lep_antimusf)
        #self.out.fillBranch("LepCand_antimusf_up",   lep_antimusf_up)
        #self.out.fillBranch("LepCand_antimusf_down", lep_antimusf_down)
        self.out.fillBranch("LepCand_fes",           lep_fes)
        #self.out.fillBranch("LepCand_fes_up",        lep_fes_up)
        #self.out.fillBranch("LepCand_fes_down",      lep_fes_down)

        self.out.fillBranch("nJets" ,             len(event.selectedAK4Jets))
        self.out.fillBranch("nElectrons" ,        len(event.selectedElectrons))
        self.out.fillBranch("nMuons" ,            len(event.selectedMuons))
        self.out.fillBranch("nTaus" ,             len(event.selectedTaus))

        self.out.fillBranch("JetCand_pt",         jet_pt);
        self.out.fillBranch("JetCand_eta",        jet_eta);
        self.out.fillBranch("JetCand_phi",        jet_phi);
        self.out.fillBranch("JetCand_m",          jet_m);
        self.out.fillBranch("JetCand_puid",       jet_puid);
        self.out.fillBranch("JetCand_jetid",      jet_jetid);
        self.out.fillBranch("JetCand_deepflavB",  jet_deepflavB);
        self.out.fillBranch("V_genpt",            event.V_genpt);
        self.out.fillBranch("pu_weight",          event.pu_weight);

	if self.isMC and len(event.genCand)>0: 
          self.out.fillBranch("nGenCand",           len(event.genCand))
          self.out.fillBranch("GenCand_id" ,        gen_id)
          self.out.fillBranch("GenCand_pt" ,        gen_pt)
          self.out.fillBranch("GenCand_eta" ,       gen_eta)
          self.out.fillBranch("GenCand_phi" ,       gen_phi)

        return True


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
analysis_eemc    = lambda : Analysis(channel="ee", isMC=True)
analysis_emumc    = lambda : Analysis(channel="emu", isMC=True)
analysis_etaumc    = lambda : Analysis(channel="etau", isMC=True)
analysis_mumumc    = lambda : Analysis(channel="mumu", isMC=True)
analysis_mutaumc    = lambda : Analysis(channel="mutau", isMC=True)
analysis_tautaumc    = lambda : Analysis(channel="tautau", isMC=True)

analysis_eedata  = lambda : Analysis(channel="ee", isMC=False)
analysis_emudata  = lambda : Analysis(channel="emu", isMC=False)
analysis_etaudata  = lambda : Analysis(channel="etau", isMC=False)
analysis_mumudata  = lambda : Analysis(channel="mumu", isMC=False)
analysis_mutaudata  = lambda : Analysis(channel="mutau", isMC=False)
analysis_tautaudata  = lambda : Analysis(channel="tautau", isMC=False)

