//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May  2 14:18:59 2023 by ROOT version 6.14/09
// from TTree Events/Events
// found on file: /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/DY.root
//////////////////////////////////////////////////////////

#ifndef classe_tautau_h
#define classe_tautau_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class classe_tautau {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Float_t         beamspot_dxdz;
   Float_t         beamspot_dydz;
   Float_t         beamspot_sigmaZ;
   Float_t         beamspot_sigmaZ0Error;
   Float_t         beamspot_x0;
   Float_t         beamspot_y0;
   Float_t         beamspot_z0;
   UInt_t          nChargedPFCandidates;
   Float_t         ChargedPFCandidates_dxy[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_dz[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_dzError[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_eta[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_mass[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_phi[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_pt[1859];   //[nChargedPFCandidates]
   Int_t           ChargedPFCandidates_charge[1859];   //[nChargedPFCandidates]
   Int_t           ChargedPFCandidates_fromPV[1859];   //[nChargedPFCandidates]
   Int_t           ChargedPFCandidates_lostInnerHits[1859];   //[nChargedPFCandidates]
   Int_t           ChargedPFCandidates_pdgId[1859];   //[nChargedPFCandidates]
   Bool_t          ChargedPFCandidates_trackHighPurity[1859];   //[nChargedPFCandidates]
   Bool_t          ChargedPFCandidates_isMatchedToGenHS[1859];   //[nChargedPFCandidates]
   Float_t         Generator_binvar;
   Float_t         Generator_scalePDF;
   Float_t         Generator_weight;
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   Float_t         GenVtx_x;
   Float_t         GenVtx_y;
   Float_t         GenVtx_z;
   Float_t         genWeight;
   UInt_t          nLHEPdfWeight;
   Float_t         LHEPdfWeight[103];   //[nLHEPdfWeight]
   UInt_t          nLHEScaleWeight;
   Float_t         LHEScaleWeight[9];   //[nLHEScaleWeight]
   Float_t         L1PreFiringWeight_Dn;
   Float_t         L1PreFiringWeight_ECAL_Dn;
   Float_t         L1PreFiringWeight_ECAL_Nom;
   Float_t         L1PreFiringWeight_ECAL_Up;
   Float_t         L1PreFiringWeight_Muon_Nom;
   Float_t         L1PreFiringWeight_Muon_StatDn;
   Float_t         L1PreFiringWeight_Muon_StatUp;
   Float_t         L1PreFiringWeight_Muon_SystDn;
   Float_t         L1PreFiringWeight_Muon_SystUp;
   Float_t         L1PreFiringWeight_Nom;
   Float_t         L1PreFiringWeight_Up;
   Float_t         LHE_Vpt;
   UChar_t         LHE_Njets;
   UInt_t          nLostTracks;
   Float_t         LostTracks_dxy[225];   //[nLostTracks]
   Float_t         LostTracks_dz[225];   //[nLostTracks]
   Float_t         LostTracks_dzError[225];   //[nLostTracks]
   Float_t         LostTracks_eta[225];   //[nLostTracks]
   Float_t         LostTracks_mass[225];   //[nLostTracks]
   Float_t         LostTracks_phi[225];   //[nLostTracks]
   Float_t         LostTracks_pt[225];   //[nLostTracks]
   Int_t           LostTracks_charge[225];   //[nLostTracks]
   Int_t           LostTracks_fromPV[225];   //[nLostTracks]
   Int_t           LostTracks_lostInnerHits[225];   //[nLostTracks]
   Int_t           LostTracks_pdgId[225];   //[nLostTracks]
   Bool_t          LostTracks_trackHighPurity[225];   //[nLostTracks]
   Float_t         MET_phi;
   Float_t         MET_pt;
   Float_t         Pileup_nTrueInt;
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
   Float_t         fixedGridRhoFastjetAll;
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   Float_t         GenVtx_t0;
   Bool_t          HLT_Ele27_WPTight_Gsf;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPTight_Gsf;
   Bool_t          HLT_Ele32_WPTight_Gsf_L1DoubleEG;
   Bool_t          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
   Bool_t          HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoMu27;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          HLT_Mu50;
   Bool_t          HLT_OldMu100;
   Bool_t          HLT_TkMu100;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Photon200;
   Bool_t          HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg;
   Int_t           nLepCand;
   Int_t           LepCand_id[5];   //[nLepCand]
   Float_t         LepCand_pt[5];   //[nLepCand]
   Float_t         LepCand_eta[5];   //[nLepCand]
   Float_t         LepCand_phi[5];   //[nLepCand]
   Int_t           LepCand_charge[5];   //[nLepCand]
   Float_t         LepCand_dxy[5];   //[nLepCand]
   Float_t         LepCand_dz[5];   //[nLepCand]
   Float_t         LepCand_gen[5];   //[nLepCand]
   Int_t           LepCand_vse[5];   //[nLepCand]
   Int_t           LepCand_vsmu[5];   //[nLepCand]
   Int_t           LepCand_vsjet[5];   //[nLepCand]
   Int_t           LepCand_muonMediumId[5];   //[nLepCand]
   Float_t         LepCand_muonIso[5];   //[nLepCand]
   Int_t           LepCand_eleMVAiso90[5];   //[nLepCand]
   Int_t           LepCand_eleMVAiso80[5];   //[nLepCand]
   Int_t           LepCand_eleMVAisoL[5];   //[nLepCand]
   Int_t           LepCand_eleMVAnoiso90[5];   //[nLepCand]
   Int_t           LepCand_eleMVAnoiso80[5];   //[nLepCand]
   Int_t           LepCand_eleMVAnoisoL[5];   //[nLepCand]
   Float_t         LepCand_eleIso[5];   //[nLepCand]
   Float_t         LepCand_eleSigmaDown[5];   //[nLepCand]
   Float_t         LepCand_eleSigmaUp[5];   //[nLepCand]
   Float_t         LepCand_eleScaleDown[5];   //[nLepCand]
   Float_t         LepCand_eleScaleUp[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert0_up[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert1_up[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_alleras_up[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_era_up[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_dm_era_up[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert0_down[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert1_down[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_alleras_down[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_era_down[5];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_dm_era_down[5];   //[nLepCand]
   Float_t         LepCand_taues[5];   //[nLepCand]
   Float_t         LepCand_taues_up[5];   //[nLepCand]
   Float_t         LepCand_taues_down[5];   //[nLepCand]
   Float_t         LepCand_fes[5];   //[nLepCand]
   Float_t         LepCand_fes_up[5];   //[nLepCand]
   Float_t         LepCand_fes_down[5];   //[nLepCand]
   Float_t         LepCand_antimusf[5];   //[nLepCand]
   Float_t         LepCand_antimusf_up[5];   //[nLepCand]
   Float_t         LepCand_antimusf_down[5];   //[nLepCand]
   Float_t         LepCand_antielesf[5];   //[nLepCand]
   Float_t         LepCand_antielesf_up[5];   //[nLepCand]
   Float_t         LepCand_antielesf_down[5];   //[nLepCand]
   Int_t           LepCand_DecayMode[5];   //[nLepCand]
   Float_t         LepCand_tautriggersf[5];   //[nLepCand]
   Float_t         LepCand_tautriggersf_up[5];   //[nLepCand]
   Float_t         LepCand_tautriggersf_down[5];   //[nLepCand]
   Int_t           LepCand_trgmatch[5];   //[nLepCand]
   Float_t         LepCand_dz2[5];   //[nLepCand]
   Float_t         LepCand_dz3[5];   //[nLepCand]
   Float_t         LepCand_tk1Pt[5];   //[nLepCand]
   Float_t         LepCand_tk1Eta[5];   //[nLepCand]
   Float_t         LepCand_tk1Phi[5];   //[nLepCand]
   Float_t         LepCand_tk2Pt[5];   //[nLepCand]
   Float_t         LepCand_tk2Eta[5];   //[nLepCand]
   Float_t         LepCand_tk2Phi[5];   //[nLepCand]
   Float_t         LepCand_tk3Pt[5];   //[nLepCand]
   Float_t         LepCand_tk3Eta[5];   //[nLepCand]
   Float_t         LepCand_tk3Phi[5];   //[nLepCand]
   Int_t           nGenCand;
   Int_t           GenCand_id[2];   //[nGenCand]
   Float_t         GenCand_pt[2];   //[nGenCand]
   Float_t         GenCand_eta[2];   //[nGenCand]
   Float_t         GenCand_phi[2];   //[nGenCand]
   Int_t           nElectrons;
   Int_t           nMuons;
   Int_t           nTaus;
   Float_t         V_genpt;
   Float_t         pu_weight;
   Float_t         puWeight;
   Float_t         puWeightUp;
   Float_t         puWeightDown;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_luminosityBlock;   //!
   TBranch        *b_event;   //!
   TBranch        *b_beamspot_dxdz;   //!
   TBranch        *b_beamspot_dydz;   //!
   TBranch        *b_beamspot_sigmaZ;   //!
   TBranch        *b_beamspot_sigmaZ0Error;   //!
   TBranch        *b_beamspot_x0;   //!
   TBranch        *b_beamspot_y0;   //!
   TBranch        *b_beamspot_z0;   //!
   TBranch        *b_nChargedPFCandidates;   //!
   TBranch        *b_ChargedPFCandidates_dxy;   //!
   TBranch        *b_ChargedPFCandidates_dz;   //!
   TBranch        *b_ChargedPFCandidates_dzError;   //!
   TBranch        *b_ChargedPFCandidates_eta;   //!
   TBranch        *b_ChargedPFCandidates_mass;   //!
   TBranch        *b_ChargedPFCandidates_phi;   //!
   TBranch        *b_ChargedPFCandidates_pt;   //!
   TBranch        *b_ChargedPFCandidates_charge;   //!
   TBranch        *b_ChargedPFCandidates_fromPV;   //!
   TBranch        *b_ChargedPFCandidates_lostInnerHits;   //!
   TBranch        *b_ChargedPFCandidates_pdgId;   //!
   TBranch        *b_ChargedPFCandidates_trackHighPurity;   //!
   TBranch        *b_ChargedPFCandidates_isMatchedToGenHS;   //!
   TBranch        *b_Generator_binvar;   //!
   TBranch        *b_Generator_scalePDF;   //!
   TBranch        *b_Generator_weight;   //!
   TBranch        *b_Generator_x1;   //!
   TBranch        *b_Generator_x2;   //!
   TBranch        *b_Generator_xpdf1;   //!
   TBranch        *b_Generator_xpdf2;   //!
   TBranch        *b_Generator_id1;   //!
   TBranch        *b_Generator_id2;   //!
   TBranch        *b_GenVtx_x;   //!
   TBranch        *b_GenVtx_y;   //!
   TBranch        *b_GenVtx_z;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_nLHEPdfWeight;   //!
   TBranch        *b_LHEPdfWeight;   //!
   TBranch        *b_nLHEScaleWeight;   //!
   TBranch        *b_LHEScaleWeight;   //!
   TBranch        *b_L1PreFiringWeight_Dn;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Dn;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Nom;   //!
   TBranch        *b_L1PreFiringWeight_ECAL_Up;   //!
   TBranch        *b_L1PreFiringWeight_Muon_Nom;   //!
   TBranch        *b_L1PreFiringWeight_Muon_StatDn;   //!
   TBranch        *b_L1PreFiringWeight_Muon_StatUp;   //!
   TBranch        *b_L1PreFiringWeight_Muon_SystDn;   //!
   TBranch        *b_L1PreFiringWeight_Muon_SystUp;   //!
   TBranch        *b_L1PreFiringWeight_Nom;   //!
   TBranch        *b_L1PreFiringWeight_Up;   //!
   TBranch        *b_LHE_Vpt;   //!
   TBranch        *b_LHE_Njets;   //!
   TBranch        *b_nLostTracks;   //!
   TBranch        *b_LostTracks_dxy;   //!
   TBranch        *b_LostTracks_dz;   //!
   TBranch        *b_LostTracks_dzError;   //!
   TBranch        *b_LostTracks_eta;   //!
   TBranch        *b_LostTracks_mass;   //!
   TBranch        *b_LostTracks_phi;   //!
   TBranch        *b_LostTracks_pt;   //!
   TBranch        *b_LostTracks_charge;   //!
   TBranch        *b_LostTracks_fromPV;   //!
   TBranch        *b_LostTracks_lostInnerHits;   //!
   TBranch        *b_LostTracks_pdgId;   //!
   TBranch        *b_LostTracks_trackHighPurity;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_MET_pt;   //!
   TBranch        *b_Pileup_nTrueInt;   //!
   TBranch        *b_PuppiMET_phi;   //!
   TBranch        *b_PuppiMET_phiJERDown;   //!
   TBranch        *b_PuppiMET_phiJERUp;   //!
   TBranch        *b_PuppiMET_phiJESDown;   //!
   TBranch        *b_PuppiMET_phiJESUp;   //!
   TBranch        *b_PuppiMET_phiUnclusteredDown;   //!
   TBranch        *b_PuppiMET_phiUnclusteredUp;   //!
   TBranch        *b_PuppiMET_pt;   //!
   TBranch        *b_PuppiMET_ptJERDown;   //!
   TBranch        *b_PuppiMET_ptJERUp;   //!
   TBranch        *b_PuppiMET_ptJESDown;   //!
   TBranch        *b_PuppiMET_ptJESUp;   //!
   TBranch        *b_PuppiMET_ptUnclusteredDown;   //!
   TBranch        *b_PuppiMET_ptUnclusteredUp;   //!
   TBranch        *b_fixedGridRhoFastjetAll;   //!
   TBranch        *b_PV_ndof;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_chi2;   //!
   TBranch        *b_PV_score;   //!
   TBranch        *b_PV_npvs;   //!
   TBranch        *b_PV_npvsGood;   //!
   TBranch        *b_GenVtx_t0;   //!
   TBranch        *b_HLT_Ele27_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele32_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele35_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele32_WPTight_Gsf_L1DoubleEG;   //!
   TBranch        *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;   //!
   TBranch        *b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1;   //!
   TBranch        *b_HLT_IsoMu24;   //!
   TBranch        *b_HLT_IsoMu27;   //!
   TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;   //!
   TBranch        *b_HLT_Mu50;   //!
   TBranch        *b_HLT_OldMu100;   //!
   TBranch        *b_HLT_TkMu100;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;   //!
   TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;   //!
   TBranch        *b_HLT_Photon200;   //!
   TBranch        *b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg;   //!
   TBranch        *b_nLepCand;   //!
   TBranch        *b_LepCand_id;   //!
   TBranch        *b_LepCand_pt;   //!
   TBranch        *b_LepCand_eta;   //!
   TBranch        *b_LepCand_phi;   //!
   TBranch        *b_LepCand_charge;   //!
   TBranch        *b_LepCand_dxy;   //!
   TBranch        *b_LepCand_dz;   //!
   TBranch        *b_LepCand_gen;   //!
   TBranch        *b_LepCand_vse;   //!
   TBranch        *b_LepCand_vsmu;   //!
   TBranch        *b_LepCand_vsjet;   //!
   TBranch        *b_LepCand_muonMediumId;   //!
   TBranch        *b_LepCand_muonIso;   //!
   TBranch        *b_LepCand_eleMVAiso90;   //!
   TBranch        *b_LepCand_eleMVAiso80;   //!
   TBranch        *b_LepCand_eleMVAisoL;   //!
   TBranch        *b_LepCand_eleMVAnoiso90;   //!
   TBranch        *b_LepCand_eleMVAnoiso80;   //!
   TBranch        *b_LepCand_eleMVAnoisoL;   //!
   TBranch        *b_LepCand_eleIso;   //!
   TBranch        *b_LepCand_eleSigmaDown;   //!
   TBranch        *b_LepCand_eleSigmaUp;   //!
   TBranch        *b_LepCand_eleScaleDown;   //!
   TBranch        *b_LepCand_eleScaleUp;   //!
   TBranch        *b_LepCand_tauidMsf;   //!
   TBranch        *b_LepCand_tauidMsf_uncert0_up;   //!
   TBranch        *b_LepCand_tauidMsf_uncert1_up;   //!
   TBranch        *b_LepCand_tauidMsf_syst_alleras_up;   //!
   TBranch        *b_LepCand_tauidMsf_syst_era_up;   //!
   TBranch        *b_LepCand_tauidMsf_syst_dm_era_up;   //!
   TBranch        *b_LepCand_tauidMsf_uncert0_down;   //!
   TBranch        *b_LepCand_tauidMsf_uncert1_down;   //!
   TBranch        *b_LepCand_tauidMsf_syst_alleras_down;   //!
   TBranch        *b_LepCand_tauidMsf_syst_era_down;   //!
   TBranch        *b_LepCand_tauidMsf_syst_dm_era_down;   //!
   TBranch        *b_LepCand_taues;   //!
   TBranch        *b_LepCand_taues_up;   //!
   TBranch        *b_LepCand_taues_down;   //!
   TBranch        *b_LepCand_fes;   //!
   TBranch        *b_LepCand_fes_up;   //!
   TBranch        *b_LepCand_fes_down;   //!
   TBranch        *b_LepCand_antimusf;   //!
   TBranch        *b_LepCand_antimusf_up;   //!
   TBranch        *b_LepCand_antimusf_down;   //!
   TBranch        *b_LepCand_antielesf;   //!
   TBranch        *b_LepCand_antielesf_up;   //!
   TBranch        *b_LepCand_antielesf_down;   //!
   TBranch        *b_LepCand_DecayMode;   //!
   TBranch        *b_LepCand_tautriggersf;   //!
   TBranch        *b_LepCand_tautriggersf_up;   //!
   TBranch        *b_LepCand_tautriggersf_down;   //!
   TBranch        *b_LepCand_trgmatch;   //!
   TBranch        *b_LepCand_dz2;   //!
   TBranch        *b_LepCand_dz3;   //!
   TBranch        *b_LepCand_tk1Pt;   //!
   TBranch        *b_LepCand_tk1Eta;   //!
   TBranch        *b_LepCand_tk1Phi;   //!
   TBranch        *b_LepCand_tk2Pt;   //!
   TBranch        *b_LepCand_tk2Eta;   //!
   TBranch        *b_LepCand_tk2Phi;   //!
   TBranch        *b_LepCand_tk3Pt;   //!
   TBranch        *b_LepCand_tk3Eta;   //!
   TBranch        *b_LepCand_tk3Phi;   //!
   TBranch        *b_nGenCand;   //!
   TBranch        *b_GenCand_id;   //!
   TBranch        *b_GenCand_pt;   //!
   TBranch        *b_GenCand_eta;   //!
   TBranch        *b_GenCand_phi;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_nTaus;   //!
   TBranch        *b_V_genpt;   //!
   TBranch        *b_pu_weight;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_puWeightUp;   //!
   TBranch        *b_puWeightDown;   //!

   classe_tautau(TTree *tree=0);
   virtual ~classe_tautau();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef classe_tautau_cxx
classe_tautau::classe_tautau(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/DY.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_tautau_2018/DY.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

classe_tautau::~classe_tautau()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t classe_tautau::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t classe_tautau::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void classe_tautau::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("luminosityBlock", &luminosityBlock, &b_luminosityBlock);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("beamspot_dxdz", &beamspot_dxdz, &b_beamspot_dxdz);
   fChain->SetBranchAddress("beamspot_dydz", &beamspot_dydz, &b_beamspot_dydz);
   fChain->SetBranchAddress("beamspot_sigmaZ", &beamspot_sigmaZ, &b_beamspot_sigmaZ);
   fChain->SetBranchAddress("beamspot_sigmaZ0Error", &beamspot_sigmaZ0Error, &b_beamspot_sigmaZ0Error);
   fChain->SetBranchAddress("beamspot_x0", &beamspot_x0, &b_beamspot_x0);
   fChain->SetBranchAddress("beamspot_y0", &beamspot_y0, &b_beamspot_y0);
   fChain->SetBranchAddress("beamspot_z0", &beamspot_z0, &b_beamspot_z0);
   fChain->SetBranchAddress("nChargedPFCandidates", &nChargedPFCandidates, &b_nChargedPFCandidates);
   fChain->SetBranchAddress("ChargedPFCandidates_dxy", ChargedPFCandidates_dxy, &b_ChargedPFCandidates_dxy);
   fChain->SetBranchAddress("ChargedPFCandidates_dz", ChargedPFCandidates_dz, &b_ChargedPFCandidates_dz);
   fChain->SetBranchAddress("ChargedPFCandidates_dzError", ChargedPFCandidates_dzError, &b_ChargedPFCandidates_dzError);
   fChain->SetBranchAddress("ChargedPFCandidates_eta", ChargedPFCandidates_eta, &b_ChargedPFCandidates_eta);
   fChain->SetBranchAddress("ChargedPFCandidates_mass", ChargedPFCandidates_mass, &b_ChargedPFCandidates_mass);
   fChain->SetBranchAddress("ChargedPFCandidates_phi", ChargedPFCandidates_phi, &b_ChargedPFCandidates_phi);
   fChain->SetBranchAddress("ChargedPFCandidates_pt", ChargedPFCandidates_pt, &b_ChargedPFCandidates_pt);
   fChain->SetBranchAddress("ChargedPFCandidates_charge", ChargedPFCandidates_charge, &b_ChargedPFCandidates_charge);
   fChain->SetBranchAddress("ChargedPFCandidates_fromPV", ChargedPFCandidates_fromPV, &b_ChargedPFCandidates_fromPV);
   fChain->SetBranchAddress("ChargedPFCandidates_lostInnerHits", ChargedPFCandidates_lostInnerHits, &b_ChargedPFCandidates_lostInnerHits);
   fChain->SetBranchAddress("ChargedPFCandidates_pdgId", ChargedPFCandidates_pdgId, &b_ChargedPFCandidates_pdgId);
   fChain->SetBranchAddress("ChargedPFCandidates_trackHighPurity", ChargedPFCandidates_trackHighPurity, &b_ChargedPFCandidates_trackHighPurity);
   fChain->SetBranchAddress("ChargedPFCandidates_isMatchedToGenHS", ChargedPFCandidates_isMatchedToGenHS, &b_ChargedPFCandidates_isMatchedToGenHS);
   fChain->SetBranchAddress("Generator_binvar", &Generator_binvar, &b_Generator_binvar);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF, &b_Generator_scalePDF);
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("Generator_x1", &Generator_x1, &b_Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2, &b_Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1, &b_Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2, &b_Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1, &b_Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2, &b_Generator_id2);
   fChain->SetBranchAddress("GenVtx_x", &GenVtx_x, &b_GenVtx_x);
   fChain->SetBranchAddress("GenVtx_y", &GenVtx_y, &b_GenVtx_y);
   fChain->SetBranchAddress("GenVtx_z", &GenVtx_z, &b_GenVtx_z);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight, &b_nLHEPdfWeight);
   fChain->SetBranchAddress("LHEPdfWeight", LHEPdfWeight, &b_LHEPdfWeight);
   fChain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight, &b_nLHEScaleWeight);
   fChain->SetBranchAddress("LHEScaleWeight", LHEScaleWeight, &b_LHEScaleWeight);
   fChain->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn, &b_L1PreFiringWeight_Dn);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Dn", &L1PreFiringWeight_ECAL_Dn, &b_L1PreFiringWeight_ECAL_Dn);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Nom", &L1PreFiringWeight_ECAL_Nom, &b_L1PreFiringWeight_ECAL_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_ECAL_Up", &L1PreFiringWeight_ECAL_Up, &b_L1PreFiringWeight_ECAL_Up);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_Nom", &L1PreFiringWeight_Muon_Nom, &b_L1PreFiringWeight_Muon_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_StatDn", &L1PreFiringWeight_Muon_StatDn, &b_L1PreFiringWeight_Muon_StatDn);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_StatUp", &L1PreFiringWeight_Muon_StatUp, &b_L1PreFiringWeight_Muon_StatUp);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_SystDn", &L1PreFiringWeight_Muon_SystDn, &b_L1PreFiringWeight_Muon_SystDn);
   fChain->SetBranchAddress("L1PreFiringWeight_Muon_SystUp", &L1PreFiringWeight_Muon_SystUp, &b_L1PreFiringWeight_Muon_SystUp);
   fChain->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom, &b_L1PreFiringWeight_Nom);
   fChain->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up, &b_L1PreFiringWeight_Up);
   fChain->SetBranchAddress("LHE_Vpt", &LHE_Vpt, &b_LHE_Vpt);
   fChain->SetBranchAddress("LHE_Njets", &LHE_Njets, &b_LHE_Njets);
   fChain->SetBranchAddress("nLostTracks", &nLostTracks, &b_nLostTracks);
   fChain->SetBranchAddress("LostTracks_dxy", LostTracks_dxy, &b_LostTracks_dxy);
   fChain->SetBranchAddress("LostTracks_dz", LostTracks_dz, &b_LostTracks_dz);
   fChain->SetBranchAddress("LostTracks_dzError", LostTracks_dzError, &b_LostTracks_dzError);
   fChain->SetBranchAddress("LostTracks_eta", LostTracks_eta, &b_LostTracks_eta);
   fChain->SetBranchAddress("LostTracks_mass", LostTracks_mass, &b_LostTracks_mass);
   fChain->SetBranchAddress("LostTracks_phi", LostTracks_phi, &b_LostTracks_phi);
   fChain->SetBranchAddress("LostTracks_pt", LostTracks_pt, &b_LostTracks_pt);
   fChain->SetBranchAddress("LostTracks_charge", LostTracks_charge, &b_LostTracks_charge);
   fChain->SetBranchAddress("LostTracks_fromPV", LostTracks_fromPV, &b_LostTracks_fromPV);
   fChain->SetBranchAddress("LostTracks_lostInnerHits", LostTracks_lostInnerHits, &b_LostTracks_lostInnerHits);
   fChain->SetBranchAddress("LostTracks_pdgId", LostTracks_pdgId, &b_LostTracks_pdgId);
   fChain->SetBranchAddress("LostTracks_trackHighPurity", LostTracks_trackHighPurity, &b_LostTracks_trackHighPurity);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("MET_pt", &MET_pt, &b_MET_pt);
   fChain->SetBranchAddress("Pileup_nTrueInt", &Pileup_nTrueInt, &b_Pileup_nTrueInt);
   fChain->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi, &b_PuppiMET_phi);
   fChain->SetBranchAddress("PuppiMET_phiJERDown", &PuppiMET_phiJERDown, &b_PuppiMET_phiJERDown);
   fChain->SetBranchAddress("PuppiMET_phiJERUp", &PuppiMET_phiJERUp, &b_PuppiMET_phiJERUp);
   fChain->SetBranchAddress("PuppiMET_phiJESDown", &PuppiMET_phiJESDown, &b_PuppiMET_phiJESDown);
   fChain->SetBranchAddress("PuppiMET_phiJESUp", &PuppiMET_phiJESUp, &b_PuppiMET_phiJESUp);
   fChain->SetBranchAddress("PuppiMET_phiUnclusteredDown", &PuppiMET_phiUnclusteredDown, &b_PuppiMET_phiUnclusteredDown);
   fChain->SetBranchAddress("PuppiMET_phiUnclusteredUp", &PuppiMET_phiUnclusteredUp, &b_PuppiMET_phiUnclusteredUp);
   fChain->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt, &b_PuppiMET_pt);
   fChain->SetBranchAddress("PuppiMET_ptJERDown", &PuppiMET_ptJERDown, &b_PuppiMET_ptJERDown);
   fChain->SetBranchAddress("PuppiMET_ptJERUp", &PuppiMET_ptJERUp, &b_PuppiMET_ptJERUp);
   fChain->SetBranchAddress("PuppiMET_ptJESDown", &PuppiMET_ptJESDown, &b_PuppiMET_ptJESDown);
   fChain->SetBranchAddress("PuppiMET_ptJESUp", &PuppiMET_ptJESUp, &b_PuppiMET_ptJESUp);
   fChain->SetBranchAddress("PuppiMET_ptUnclusteredDown", &PuppiMET_ptUnclusteredDown, &b_PuppiMET_ptUnclusteredDown);
   fChain->SetBranchAddress("PuppiMET_ptUnclusteredUp", &PuppiMET_ptUnclusteredUp, &b_PuppiMET_ptUnclusteredUp);
   fChain->SetBranchAddress("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll, &b_fixedGridRhoFastjetAll);
   fChain->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
   fChain->SetBranchAddress("PV_score", &PV_score, &b_PV_score);
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
   fChain->SetBranchAddress("GenVtx_t0", &GenVtx_t0, &b_GenVtx_t0);
   fChain->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf, &b_HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, &b_HLT_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf, &b_HLT_Ele35_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG", &HLT_Ele32_WPTight_Gsf_L1DoubleEG, &b_HLT_Ele32_WPTight_Gsf_L1DoubleEG);
   fChain->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1, &b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
   fChain->SetBranchAddress("HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1", &HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1, &b_HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1);
   fChain->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24, &b_HLT_IsoMu24);
   fChain->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27, &b_HLT_IsoMu27);
   fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
   fChain->SetBranchAddress("HLT_Mu50", &HLT_Mu50, &b_HLT_Mu50);
   fChain->SetBranchAddress("HLT_OldMu100", &HLT_OldMu100, &b_HLT_OldMu100);
   fChain->SetBranchAddress("HLT_TkMu100", &HLT_TkMu100, &b_HLT_TkMu100);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
   fChain->SetBranchAddress("HLT_Photon200", &HLT_Photon200, &b_HLT_Photon200);
   fChain->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg, &b_HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg);
   fChain->SetBranchAddress("nLepCand", &nLepCand, &b_nLepCand);
   fChain->SetBranchAddress("LepCand_id", LepCand_id, &b_LepCand_id);
   fChain->SetBranchAddress("LepCand_pt", LepCand_pt, &b_LepCand_pt);
   fChain->SetBranchAddress("LepCand_eta", LepCand_eta, &b_LepCand_eta);
   fChain->SetBranchAddress("LepCand_phi", LepCand_phi, &b_LepCand_phi);
   fChain->SetBranchAddress("LepCand_charge", LepCand_charge, &b_LepCand_charge);
   fChain->SetBranchAddress("LepCand_dxy", LepCand_dxy, &b_LepCand_dxy);
   fChain->SetBranchAddress("LepCand_dz", LepCand_dz, &b_LepCand_dz);
   fChain->SetBranchAddress("LepCand_gen", LepCand_gen, &b_LepCand_gen);
   fChain->SetBranchAddress("LepCand_vse", LepCand_vse, &b_LepCand_vse);
   fChain->SetBranchAddress("LepCand_vsmu", LepCand_vsmu, &b_LepCand_vsmu);
   fChain->SetBranchAddress("LepCand_vsjet", LepCand_vsjet, &b_LepCand_vsjet);
   fChain->SetBranchAddress("LepCand_muonMediumId", LepCand_muonMediumId, &b_LepCand_muonMediumId);
   fChain->SetBranchAddress("LepCand_muonIso", LepCand_muonIso, &b_LepCand_muonIso);
   fChain->SetBranchAddress("LepCand_eleMVAiso90", LepCand_eleMVAiso90, &b_LepCand_eleMVAiso90);
   fChain->SetBranchAddress("LepCand_eleMVAiso80", LepCand_eleMVAiso80, &b_LepCand_eleMVAiso80);
   fChain->SetBranchAddress("LepCand_eleMVAisoL", LepCand_eleMVAisoL, &b_LepCand_eleMVAisoL);
   fChain->SetBranchAddress("LepCand_eleMVAnoiso90", LepCand_eleMVAnoiso90, &b_LepCand_eleMVAnoiso90);
   fChain->SetBranchAddress("LepCand_eleMVAnoiso80", LepCand_eleMVAnoiso80, &b_LepCand_eleMVAnoiso80);
   fChain->SetBranchAddress("LepCand_eleMVAnoisoL", LepCand_eleMVAnoisoL, &b_LepCand_eleMVAnoisoL);
   fChain->SetBranchAddress("LepCand_eleIso", LepCand_eleIso, &b_LepCand_eleIso);
   fChain->SetBranchAddress("LepCand_eleSigmaDown", LepCand_eleSigmaDown, &b_LepCand_eleSigmaDown);
   fChain->SetBranchAddress("LepCand_eleSigmaUp", LepCand_eleSigmaUp, &b_LepCand_eleSigmaUp);
   fChain->SetBranchAddress("LepCand_eleScaleDown", LepCand_eleScaleDown, &b_LepCand_eleScaleDown);
   fChain->SetBranchAddress("LepCand_eleScaleUp", LepCand_eleScaleUp, &b_LepCand_eleScaleUp);
   fChain->SetBranchAddress("LepCand_tauidMsf", LepCand_tauidMsf, &b_LepCand_tauidMsf);
   fChain->SetBranchAddress("LepCand_tauidMsf_uncert0_up", LepCand_tauidMsf_uncert0_up, &b_LepCand_tauidMsf_uncert0_up);
   fChain->SetBranchAddress("LepCand_tauidMsf_uncert1_up", LepCand_tauidMsf_uncert1_up, &b_LepCand_tauidMsf_uncert1_up);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_alleras_up", LepCand_tauidMsf_syst_alleras_up, &b_LepCand_tauidMsf_syst_alleras_up);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_era_up", LepCand_tauidMsf_syst_era_up, &b_LepCand_tauidMsf_syst_era_up);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_dm_era_up", LepCand_tauidMsf_syst_dm_era_up, &b_LepCand_tauidMsf_syst_dm_era_up);
   fChain->SetBranchAddress("LepCand_tauidMsf_uncert0_down", LepCand_tauidMsf_uncert0_down, &b_LepCand_tauidMsf_uncert0_down);
   fChain->SetBranchAddress("LepCand_tauidMsf_uncert1_down", LepCand_tauidMsf_uncert1_down, &b_LepCand_tauidMsf_uncert1_down);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_alleras_down", LepCand_tauidMsf_syst_alleras_down, &b_LepCand_tauidMsf_syst_alleras_down);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_era_down", LepCand_tauidMsf_syst_era_down, &b_LepCand_tauidMsf_syst_era_down);
   fChain->SetBranchAddress("LepCand_tauidMsf_syst_dm_era_down", LepCand_tauidMsf_syst_dm_era_down, &b_LepCand_tauidMsf_syst_dm_era_down);
   fChain->SetBranchAddress("LepCand_taues", LepCand_taues, &b_LepCand_taues);
   fChain->SetBranchAddress("LepCand_taues_up", LepCand_taues_up, &b_LepCand_taues_up);
   fChain->SetBranchAddress("LepCand_taues_down", LepCand_taues_down, &b_LepCand_taues_down);
   fChain->SetBranchAddress("LepCand_fes", LepCand_fes, &b_LepCand_fes);
   fChain->SetBranchAddress("LepCand_fes_up", LepCand_fes_up, &b_LepCand_fes_up);
   fChain->SetBranchAddress("LepCand_fes_down", LepCand_fes_down, &b_LepCand_fes_down);
   fChain->SetBranchAddress("LepCand_antimusf", LepCand_antimusf, &b_LepCand_antimusf);
   fChain->SetBranchAddress("LepCand_antimusf_up", LepCand_antimusf_up, &b_LepCand_antimusf_up);
   fChain->SetBranchAddress("LepCand_antimusf_down", LepCand_antimusf_down, &b_LepCand_antimusf_down);
   fChain->SetBranchAddress("LepCand_antielesf", LepCand_antielesf, &b_LepCand_antielesf);
   fChain->SetBranchAddress("LepCand_antielesf_up", LepCand_antielesf_up, &b_LepCand_antielesf_up);
   fChain->SetBranchAddress("LepCand_antielesf_down", LepCand_antielesf_down, &b_LepCand_antielesf_down);
   fChain->SetBranchAddress("LepCand_DecayMode", LepCand_DecayMode, &b_LepCand_DecayMode);
   fChain->SetBranchAddress("LepCand_tautriggersf", LepCand_tautriggersf, &b_LepCand_tautriggersf);
   fChain->SetBranchAddress("LepCand_tautriggersf_up", LepCand_tautriggersf_up, &b_LepCand_tautriggersf_up);
   fChain->SetBranchAddress("LepCand_tautriggersf_down", LepCand_tautriggersf_down, &b_LepCand_tautriggersf_down);
   fChain->SetBranchAddress("LepCand_trgmatch", LepCand_trgmatch, &b_LepCand_trgmatch);
   fChain->SetBranchAddress("LepCand_dz2", LepCand_dz2, &b_LepCand_dz2);
   fChain->SetBranchAddress("LepCand_dz3", LepCand_dz3, &b_LepCand_dz3);
   fChain->SetBranchAddress("LepCand_tk1Pt", LepCand_tk1Pt, &b_LepCand_tk1Pt);
   fChain->SetBranchAddress("LepCand_tk1Eta", LepCand_tk1Eta, &b_LepCand_tk1Eta);
   fChain->SetBranchAddress("LepCand_tk1Phi", LepCand_tk1Phi, &b_LepCand_tk1Phi);
   fChain->SetBranchAddress("LepCand_tk2Pt", LepCand_tk2Pt, &b_LepCand_tk2Pt);
   fChain->SetBranchAddress("LepCand_tk2Eta", LepCand_tk2Eta, &b_LepCand_tk2Eta);
   fChain->SetBranchAddress("LepCand_tk2Phi", LepCand_tk2Phi, &b_LepCand_tk2Phi);
   fChain->SetBranchAddress("LepCand_tk3Pt", LepCand_tk3Pt, &b_LepCand_tk3Pt);
   fChain->SetBranchAddress("LepCand_tk3Eta", LepCand_tk3Eta, &b_LepCand_tk3Eta);
   fChain->SetBranchAddress("LepCand_tk3Phi", LepCand_tk3Phi, &b_LepCand_tk3Phi);
   fChain->SetBranchAddress("nGenCand", &nGenCand, &b_nGenCand);
   fChain->SetBranchAddress("GenCand_id", GenCand_id, &b_GenCand_id);
   fChain->SetBranchAddress("GenCand_pt", GenCand_pt, &b_GenCand_pt);
   fChain->SetBranchAddress("GenCand_eta", GenCand_eta, &b_GenCand_eta);
   fChain->SetBranchAddress("GenCand_phi", GenCand_phi, &b_GenCand_phi);
   fChain->SetBranchAddress("nElectrons", &nElectrons, &b_nElectrons);
   fChain->SetBranchAddress("nMuons", &nMuons, &b_nMuons);
   fChain->SetBranchAddress("nTaus", &nTaus, &b_nTaus);
   fChain->SetBranchAddress("V_genpt", &V_genpt, &b_V_genpt);
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("puWeightUp", &puWeightUp, &b_puWeightUp);
   fChain->SetBranchAddress("puWeightDown", &puWeightDown, &b_puWeightDown);
   Notify();
}

Bool_t classe_tautau::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void classe_tautau::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t classe_tautau::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef classe_tautau_cxx
