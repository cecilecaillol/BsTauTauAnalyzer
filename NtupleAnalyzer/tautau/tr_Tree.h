   Long64_t       genEventCount; 
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Float_t         btagWeight_DeepCSVB;
   Float_t         Generator_binvar;
   Float_t         Generator_scalePDF;
   Float_t         Generator_weight;
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   Float_t         genWeight;
   Float_t         MET_phi;
   Float_t         MET_pt;
   Float_t         MET_px;
   Float_t         MET_py;
   Float_t         MET_pz;
   Float_t         PuppiMET_phi;
   Float_t         PuppiMET_phiJERDown;
   Float_t         PuppiMET_phiJERUp;
   Float_t         PuppiMET_phiJESDown;
   Float_t         PuppiMET_phiJESUp;
   Float_t         PuppiMET_phiUnclusteredDown;
   Float_t         PuppiMET_phiUnclusteredUp;
   Float_t         PuppiMET_pt;
   Float_t         PuppiMET_ptJERDown;
   Float_t         PuppiMET_ptJERUp;
   Float_t         PuppiMET_ptJESDown;
   Float_t         PuppiMET_ptJESUp;
   Float_t         PuppiMET_ptUnclusteredDown;
   Float_t         PuppiMET_ptUnclusteredUp;
   Float_t         PuppiMET_px;
   Float_t         PuppiMET_py;
   Float_t         PuppiMET_pz;
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPTight_Gsf;
   Bool_t          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
   Bool_t          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;
   Bool_t          HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;
   Bool_t          HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoMu27;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          HLT_Mu50;
   Bool_t          HLT_OldMu100;
   Bool_t          HLT_TkMu100;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Photon200;
   Bool_t          HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1;
   Bool_t          HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
   Bool_t          HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg;
   Bool_t          HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;

   Int_t           nLepCand;
   Int_t           LepCand_id[3];   //[nLepCand]
   Float_t         LepCand_pt[3];   //[nLepCand]
   Float_t         LepCand_eta[3];   //[nLepCand]
   Float_t         LepCand_phi[3];   //[nLepCand]
   Int_t           LepCand_charge[3];   //[nLepCand]
   Float_t         LepCand_dxy[3];   //[nLepCand]
   Float_t         LepCand_dz[3];   //[nLepCand]
   Float_t         LepCand_gen[3];   //[nLepCand]
   Int_t           LepCand_vse[3];   //[nLepCand]
   Int_t           LepCand_vsmu[3];   //[nLepCand]
   Int_t           LepCand_vsjet[3];   //[nLepCand]
   Int_t           LepCand_muonMediumId[3];   //[nLepCand]
   Float_t         LepCand_muonIso[3];   //[nLepCand]
   Int_t           LepCand_eleMVAiso90[3];   //[nLepCand]
   Int_t           LepCand_eleMVAiso80[3];   //[nLepCand]
   Float_t         LepCand_eleIso[3];   //[nLepCand]
   Float_t         LepCand_tauidMsf[3];   //[nLepCand]
   Float_t         LepCand_taues[3];   //[nLepCand]
   Float_t         LepCand_tauidMsfDM[3];//tau id scale factor for ditau final state
   Float_t         LepCand_tautriggersf[3];//trigger scale factor for ditau trigger
   Float_t         LepCand_fes[3];   //[nLepCand]
   Float_t         LepCand_antimusf[3];   //[nLepCand]
   Float_t         LepCand_antielesf[3];   //[nLepCand]
   Int_t           nJets;
   Int_t           nElectrons;
   Int_t           nMuons;
   Int_t           nTaus;
   Float_t         JetCand_pt[4];   //[nJets]
   Float_t         JetCand_eta[4];   //[nJets]
   Float_t         JetCand_phi[4];   //[nJets]
   Float_t         JetCand_m[4];   //[nJets]
   Int_t           JetCand_puid[4];   //[nJets]
   Int_t           JetCand_jetid[4];   //[nJets]
   Float_t         JetCand_deepflavB[4];   //[nJets]
   Float_t         V_genpt;
   Float_t         pu_weight;

