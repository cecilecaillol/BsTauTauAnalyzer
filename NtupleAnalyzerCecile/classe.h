//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 31 14:51:00 2023 by ROOT version 6.14/09
// from TTree Events/Events
// found on file: /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau.root
//////////////////////////////////////////////////////////

#ifndef classe_h
#define classe_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class classe {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          luminosityBlock;
   ULong64_t       event;
   Float_t         beamspot_sigmaZ;
   Float_t         beamspot_z0;
   Float_t         Generator_weight;
   Float_t         GenVtx_x;
   Float_t         GenVtx_y;
   Float_t         GenVtx_z;
   Float_t         genWeight;
   UInt_t          nLHEPdfWeight;
   Float_t         LHEPdfWeight[1];   //[nLHEPdfWeight]
   UInt_t          nLHEScaleWeight;
   Float_t         LHEScaleWeight[1];   //[nLHEScaleWeight]
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
   Float_t         TauG2Weights_ceBRe33_m40p0;
   Float_t         TauG2Weights_ceBRe33_m39p2;
   Float_t         TauG2Weights_ceBRe33_m38p4;
   Float_t         TauG2Weights_ceBRe33_m37p6;
   Float_t         TauG2Weights_ceBRe33_m36p8;
   Float_t         TauG2Weights_ceBRe33_m36p0;
   Float_t         TauG2Weights_ceBRe33_m35p2;
   Float_t         TauG2Weights_ceBRe33_m34p4;
   Float_t         TauG2Weights_ceBRe33_m33p6;
   Float_t         TauG2Weights_ceBRe33_m32p8;
   Float_t         TauG2Weights_ceBRe33_m32p0;
   Float_t         TauG2Weights_ceBRe33_m31p2;
   Float_t         TauG2Weights_ceBRe33_m30p4;
   Float_t         TauG2Weights_ceBRe33_m29p6;
   Float_t         TauG2Weights_ceBRe33_m28p8;
   Float_t         TauG2Weights_ceBRe33_m28p0;
   Float_t         TauG2Weights_ceBRe33_m27p2;
   Float_t         TauG2Weights_ceBRe33_m26p4;
   Float_t         TauG2Weights_ceBRe33_m25p6;
   Float_t         TauG2Weights_ceBRe33_m24p8;
   Float_t         TauG2Weights_ceBRe33_m24p0;
   Float_t         TauG2Weights_ceBRe33_m23p2;
   Float_t         TauG2Weights_ceBRe33_m22p4;
   Float_t         TauG2Weights_ceBRe33_m21p6;
   Float_t         TauG2Weights_ceBRe33_m20p8;
   Float_t         TauG2Weights_ceBRe33_m20p0;
   Float_t         TauG2Weights_ceBRe33_m19p2;
   Float_t         TauG2Weights_ceBRe33_m18p4;
   Float_t         TauG2Weights_ceBRe33_m17p6;
   Float_t         TauG2Weights_ceBRe33_m16p8;
   Float_t         TauG2Weights_ceBRe33_m16p0;
   Float_t         TauG2Weights_ceBRe33_m15p2;
   Float_t         TauG2Weights_ceBRe33_m14p4;
   Float_t         TauG2Weights_ceBRe33_m13p6;
   Float_t         TauG2Weights_ceBRe33_m12p8;
   Float_t         TauG2Weights_ceBRe33_m12p0;
   Float_t         TauG2Weights_ceBRe33_m11p2;
   Float_t         TauG2Weights_ceBRe33_m10p4;
   Float_t         TauG2Weights_ceBRe33_m9p6;
   Float_t         TauG2Weights_ceBRe33_m8p8;
   Float_t         TauG2Weights_ceBRe33_m8p0;
   Float_t         TauG2Weights_ceBRe33_m7p2;
   Float_t         TauG2Weights_ceBRe33_m6p4;
   Float_t         TauG2Weights_ceBRe33_m5p6;
   Float_t         TauG2Weights_ceBRe33_m4p8;
   Float_t         TauG2Weights_ceBRe33_m4p0;
   Float_t         TauG2Weights_ceBRe33_m3p2;
   Float_t         TauG2Weights_ceBRe33_m2p4;
   Float_t         TauG2Weights_ceBRe33_m1p6;
   Float_t         TauG2Weights_ceBRe33_m0p8;
   Float_t         TauG2Weights_ceBRe33_0p0;
   Float_t         TauG2Weights_ceBRe33_0p8;
   Float_t         TauG2Weights_ceBRe33_1p6;
   Float_t         TauG2Weights_ceBRe33_2p4;
   Float_t         TauG2Weights_ceBRe33_3p2;
   Float_t         TauG2Weights_ceBRe33_4p0;
   Float_t         TauG2Weights_ceBRe33_4p8;
   Float_t         TauG2Weights_ceBRe33_5p6;
   Float_t         TauG2Weights_ceBRe33_6p4;
   Float_t         TauG2Weights_ceBRe33_7p2;
   Float_t         TauG2Weights_ceBRe33_8p0;
   Float_t         TauG2Weights_ceBRe33_8p8;
   Float_t         TauG2Weights_ceBRe33_9p6;
   Float_t         TauG2Weights_ceBRe33_10p4;
   Float_t         TauG2Weights_ceBRe33_11p2;
   Float_t         TauG2Weights_ceBRe33_12p0;
   Float_t         TauG2Weights_ceBRe33_12p8;
   Float_t         TauG2Weights_ceBRe33_13p6;
   Float_t         TauG2Weights_ceBRe33_14p4;
   Float_t         TauG2Weights_ceBRe33_15p2;
   Float_t         TauG2Weights_ceBRe33_16p0;
   Float_t         TauG2Weights_ceBRe33_16p8;
   Float_t         TauG2Weights_ceBRe33_17p6;
   Float_t         TauG2Weights_ceBRe33_18p4;
   Float_t         TauG2Weights_ceBRe33_19p2;
   Float_t         TauG2Weights_ceBRe33_20p0;
   Float_t         TauG2Weights_ceBRe33_20p8;
   Float_t         TauG2Weights_ceBRe33_21p6;
   Float_t         TauG2Weights_ceBRe33_22p4;
   Float_t         TauG2Weights_ceBRe33_23p2;
   Float_t         TauG2Weights_ceBRe33_24p0;
   Float_t         TauG2Weights_ceBRe33_24p8;
   Float_t         TauG2Weights_ceBRe33_25p6;
   Float_t         TauG2Weights_ceBRe33_26p4;
   Float_t         TauG2Weights_ceBRe33_27p2;
   Float_t         TauG2Weights_ceBRe33_28p0;
   Float_t         TauG2Weights_ceBRe33_28p8;
   Float_t         TauG2Weights_ceBRe33_29p6;
   Float_t         TauG2Weights_ceBRe33_30p4;
   Float_t         TauG2Weights_ceBRe33_31p2;
   Float_t         TauG2Weights_ceBRe33_32p0;
   Float_t         TauG2Weights_ceBRe33_32p8;
   Float_t         TauG2Weights_ceBRe33_33p6;
   Float_t         TauG2Weights_ceBRe33_34p4;
   Float_t         TauG2Weights_ceBRe33_35p2;
   Float_t         TauG2Weights_ceBRe33_36p0;
   Float_t         TauG2Weights_ceBRe33_36p8;
   Float_t         TauG2Weights_ceBRe33_37p6;
   Float_t         TauG2Weights_ceBRe33_38p4;
   Float_t         TauG2Weights_ceBRe33_39p2;
   Float_t         TauG2Weights_ceBRe33_40p0;
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
   UInt_t          nOtherPV;
   Float_t         OtherPV_z[5];   //[nOtherPV]
   Int_t           OtherPV_ntracks0p9[5];   //[nOtherPV]
   Int_t           OtherPV_ntracks0p5[5];   //[nOtherPV]
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   Float_t         GenVtx_t0;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele35_WPTight_Gsf;
   Bool_t          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;
   Bool_t          HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;
   Int_t           nLepCand;
   Int_t           LepCand_id[4];   //[nLepCand]
   Float_t         LepCand_pt[4];   //[nLepCand]
   Float_t         LepCand_eta[4];   //[nLepCand]
   Float_t         LepCand_phi[4];   //[nLepCand]
   Int_t           LepCand_charge[4];   //[nLepCand]
   Float_t         LepCand_dxy[4];   //[nLepCand]
   Float_t         LepCand_dz[4];   //[nLepCand]
   Float_t         LepCand_gen[4];   //[nLepCand]
   Int_t           LepCand_vse[4];   //[nLepCand]
   Int_t           LepCand_vsmu[4];   //[nLepCand]
   Int_t           LepCand_vsjet[4];   //[nLepCand]
   Int_t           LepCand_eleMVAiso90[4];   //[nLepCand]
   Int_t           LepCand_eleMVAiso80[4];   //[nLepCand]
   Int_t           LepCand_eleMVAnoiso90[4];   //[nLepCand]
   Int_t           LepCand_eleMVAnoiso80[4];   //[nLepCand]
   Float_t         LepCand_eleIso[4];   //[nLepCand]
   Float_t         LepCand_eleSigmaDown[4];   //[nLepCand]
   Float_t         LepCand_eleSigmaUp[4];   //[nLepCand]
   Float_t         LepCand_eleScaleDown[4];   //[nLepCand]
   Float_t         LepCand_eleScaleUp[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert0_up[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert1_up[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_alleras_up[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_era_up[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_dm_era_up[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert0_down[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_uncert1_down[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_alleras_down[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_era_down[4];   //[nLepCand]
   Float_t         LepCand_tauidMsf_syst_dm_era_down[4];   //[nLepCand]
   Float_t         LepCand_taues[4];   //[nLepCand]
   Float_t         LepCand_taues_up[4];   //[nLepCand]
   Float_t         LepCand_taues_down[4];   //[nLepCand]
   Float_t         LepCand_fes[4];   //[nLepCand]
   Float_t         LepCand_fes_up[4];   //[nLepCand]
   Float_t         LepCand_fes_down[4];   //[nLepCand]
   Float_t         LepCand_antimusf[4];   //[nLepCand]
   Float_t         LepCand_antimusf_up[4];   //[nLepCand]
   Float_t         LepCand_antimusf_down[4];   //[nLepCand]
   Float_t         LepCand_antielesf[4];   //[nLepCand]
   Float_t         LepCand_antielesf_up[4];   //[nLepCand]
   Float_t         LepCand_antielesf_down[4];   //[nLepCand]
   Int_t           LepCand_DecayMode[4];   //[nLepCand]
   Float_t         LepCand_tautriggersf[4];   //[nLepCand]
   Float_t         LepCand_tautriggersf_up[4];   //[nLepCand]
   Float_t         LepCand_tautriggersf_down[4];   //[nLepCand]
   Int_t           nGenCand;
   Int_t           GenCand_id[1];   //[nGenCand]
   Float_t         GenCand_pt[1];   //[nGenCand]
   Float_t         GenCand_eta[1];   //[nGenCand]
   Float_t         GenCand_phi[1];   //[nGenCand]
   Int_t           nTracks;
   Float_t         Track_pt[624];   //[nTracks]
   Float_t         Track_eta[624];   //[nTracks]
   Float_t         Track_phi[624];   //[nTracks]
   Float_t         Track_dz[624];   //[nTracks]
   Float_t         Track_dxy[624];   //[nTracks]
   Int_t           Track_charge[624];   //[nTracks]
   Int_t           Track_isMatchedToHS[624];   //[nTracks]
   Int_t           Track_lostInnerHits[624];   //[nTracks]
   Int_t           Track_trackHighPurity[624];   //[nTracks]
   Int_t           nJets;
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
   TBranch        *b_beamspot_sigmaZ;   //!
   TBranch        *b_beamspot_z0;   //!
   TBranch        *b_Generator_weight;   //!
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
   TBranch        *b_TauG2Weights_ceBRe33_m40p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m39p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m38p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m37p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m36p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m36p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m35p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m34p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m33p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m32p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m32p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m31p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m30p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m29p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m28p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m28p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m27p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m26p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m25p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m24p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m24p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m23p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m22p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m21p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m20p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m20p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m19p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m18p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m17p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m16p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m16p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m15p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m14p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m13p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m12p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m12p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m11p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m10p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m9p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m8p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m8p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m7p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m6p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m5p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m4p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m4p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m3p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m2p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m1p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_m0p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_0p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_0p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_1p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_2p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_3p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_4p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_4p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_5p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_6p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_7p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_8p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_8p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_9p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_10p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_11p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_12p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_12p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_13p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_14p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_15p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_16p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_16p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_17p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_18p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_19p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_20p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_20p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_21p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_22p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_23p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_24p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_24p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_25p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_26p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_27p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_28p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_28p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_29p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_30p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_31p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_32p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_32p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_33p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_34p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_35p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_36p0;   //!
   TBranch        *b_TauG2Weights_ceBRe33_36p8;   //!
   TBranch        *b_TauG2Weights_ceBRe33_37p6;   //!
   TBranch        *b_TauG2Weights_ceBRe33_38p4;   //!
   TBranch        *b_TauG2Weights_ceBRe33_39p2;   //!
   TBranch        *b_TauG2Weights_ceBRe33_40p0;   //!
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
   TBranch        *b_nOtherPV;   //!
   TBranch        *b_OtherPV_z;   //!
   TBranch        *b_OtherPV_ntracks0p9;   //!
   TBranch        *b_OtherPV_ntracks0p5;   //!
   TBranch        *b_PV_ndof;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_chi2;   //!
   TBranch        *b_PV_score;   //!
   TBranch        *b_PV_npvs;   //!
   TBranch        *b_PV_npvsGood;   //!
   TBranch        *b_GenVtx_t0;   //!
   TBranch        *b_HLT_Ele32_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele35_WPTight_Gsf;   //!
   TBranch        *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1;   //!
   TBranch        *b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1;   //!
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
   TBranch        *b_LepCand_eleMVAiso90;   //!
   TBranch        *b_LepCand_eleMVAiso80;   //!
   TBranch        *b_LepCand_eleMVAnoiso90;   //!
   TBranch        *b_LepCand_eleMVAnoiso80;   //!
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
   TBranch        *b_nGenCand;   //!
   TBranch        *b_GenCand_id;   //!
   TBranch        *b_GenCand_pt;   //!
   TBranch        *b_GenCand_eta;   //!
   TBranch        *b_GenCand_phi;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_Track_pt;   //!
   TBranch        *b_Track_eta;   //!
   TBranch        *b_Track_phi;   //!
   TBranch        *b_Track_dz;   //!
   TBranch        *b_Track_dxy;   //!
   TBranch        *b_Track_charge;   //!
   TBranch        *b_Track_isMatchedToHS;   //!
   TBranch        *b_Track_lostInnerHits;   //!
   TBranch        *b_Track_trackHighPurity;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_nElectrons;   //!
   TBranch        *b_nMuons;   //!
   TBranch        *b_nTaus;   //!
   TBranch        *b_V_genpt;   //!
   TBranch        *b_pu_weight;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_puWeightUp;   //!
   TBranch        *b_puWeightDown;   //!

   classe(TTree *tree=0);
   virtual ~classe();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef classe_cxx
classe::classe(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/GGToTauTau.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

classe::~classe()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t classe::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t classe::LoadTree(Long64_t entry)
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

void classe::Init(TTree *tree)
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
   fChain->SetBranchAddress("beamspot_sigmaZ", &beamspot_sigmaZ, &b_beamspot_sigmaZ);
   fChain->SetBranchAddress("beamspot_z0", &beamspot_z0, &b_beamspot_z0);
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("GenVtx_x", &GenVtx_x, &b_GenVtx_x);
   fChain->SetBranchAddress("GenVtx_y", &GenVtx_y, &b_GenVtx_y);
   fChain->SetBranchAddress("GenVtx_z", &GenVtx_z, &b_GenVtx_z);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight, &b_nLHEPdfWeight);
   fChain->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight, &b_LHEPdfWeight);
   fChain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight, &b_nLHEScaleWeight);
   fChain->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight, &b_LHEScaleWeight);
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
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m40p0", &TauG2Weights_ceBRe33_m40p0, &b_TauG2Weights_ceBRe33_m40p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m39p2", &TauG2Weights_ceBRe33_m39p2, &b_TauG2Weights_ceBRe33_m39p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m38p4", &TauG2Weights_ceBRe33_m38p4, &b_TauG2Weights_ceBRe33_m38p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m37p6", &TauG2Weights_ceBRe33_m37p6, &b_TauG2Weights_ceBRe33_m37p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m36p8", &TauG2Weights_ceBRe33_m36p8, &b_TauG2Weights_ceBRe33_m36p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m36p0", &TauG2Weights_ceBRe33_m36p0, &b_TauG2Weights_ceBRe33_m36p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m35p2", &TauG2Weights_ceBRe33_m35p2, &b_TauG2Weights_ceBRe33_m35p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m34p4", &TauG2Weights_ceBRe33_m34p4, &b_TauG2Weights_ceBRe33_m34p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m33p6", &TauG2Weights_ceBRe33_m33p6, &b_TauG2Weights_ceBRe33_m33p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m32p8", &TauG2Weights_ceBRe33_m32p8, &b_TauG2Weights_ceBRe33_m32p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m32p0", &TauG2Weights_ceBRe33_m32p0, &b_TauG2Weights_ceBRe33_m32p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m31p2", &TauG2Weights_ceBRe33_m31p2, &b_TauG2Weights_ceBRe33_m31p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m30p4", &TauG2Weights_ceBRe33_m30p4, &b_TauG2Weights_ceBRe33_m30p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m29p6", &TauG2Weights_ceBRe33_m29p6, &b_TauG2Weights_ceBRe33_m29p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m28p8", &TauG2Weights_ceBRe33_m28p8, &b_TauG2Weights_ceBRe33_m28p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m28p0", &TauG2Weights_ceBRe33_m28p0, &b_TauG2Weights_ceBRe33_m28p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m27p2", &TauG2Weights_ceBRe33_m27p2, &b_TauG2Weights_ceBRe33_m27p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m26p4", &TauG2Weights_ceBRe33_m26p4, &b_TauG2Weights_ceBRe33_m26p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m25p6", &TauG2Weights_ceBRe33_m25p6, &b_TauG2Weights_ceBRe33_m25p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m24p8", &TauG2Weights_ceBRe33_m24p8, &b_TauG2Weights_ceBRe33_m24p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m24p0", &TauG2Weights_ceBRe33_m24p0, &b_TauG2Weights_ceBRe33_m24p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m23p2", &TauG2Weights_ceBRe33_m23p2, &b_TauG2Weights_ceBRe33_m23p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m22p4", &TauG2Weights_ceBRe33_m22p4, &b_TauG2Weights_ceBRe33_m22p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m21p6", &TauG2Weights_ceBRe33_m21p6, &b_TauG2Weights_ceBRe33_m21p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m20p8", &TauG2Weights_ceBRe33_m20p8, &b_TauG2Weights_ceBRe33_m20p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m20p0", &TauG2Weights_ceBRe33_m20p0, &b_TauG2Weights_ceBRe33_m20p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m19p2", &TauG2Weights_ceBRe33_m19p2, &b_TauG2Weights_ceBRe33_m19p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m18p4", &TauG2Weights_ceBRe33_m18p4, &b_TauG2Weights_ceBRe33_m18p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m17p6", &TauG2Weights_ceBRe33_m17p6, &b_TauG2Weights_ceBRe33_m17p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m16p8", &TauG2Weights_ceBRe33_m16p8, &b_TauG2Weights_ceBRe33_m16p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m16p0", &TauG2Weights_ceBRe33_m16p0, &b_TauG2Weights_ceBRe33_m16p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m15p2", &TauG2Weights_ceBRe33_m15p2, &b_TauG2Weights_ceBRe33_m15p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m14p4", &TauG2Weights_ceBRe33_m14p4, &b_TauG2Weights_ceBRe33_m14p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m13p6", &TauG2Weights_ceBRe33_m13p6, &b_TauG2Weights_ceBRe33_m13p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m12p8", &TauG2Weights_ceBRe33_m12p8, &b_TauG2Weights_ceBRe33_m12p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m12p0", &TauG2Weights_ceBRe33_m12p0, &b_TauG2Weights_ceBRe33_m12p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m11p2", &TauG2Weights_ceBRe33_m11p2, &b_TauG2Weights_ceBRe33_m11p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m10p4", &TauG2Weights_ceBRe33_m10p4, &b_TauG2Weights_ceBRe33_m10p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m9p6", &TauG2Weights_ceBRe33_m9p6, &b_TauG2Weights_ceBRe33_m9p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m8p8", &TauG2Weights_ceBRe33_m8p8, &b_TauG2Weights_ceBRe33_m8p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m8p0", &TauG2Weights_ceBRe33_m8p0, &b_TauG2Weights_ceBRe33_m8p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m7p2", &TauG2Weights_ceBRe33_m7p2, &b_TauG2Weights_ceBRe33_m7p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m6p4", &TauG2Weights_ceBRe33_m6p4, &b_TauG2Weights_ceBRe33_m6p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m5p6", &TauG2Weights_ceBRe33_m5p6, &b_TauG2Weights_ceBRe33_m5p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m4p8", &TauG2Weights_ceBRe33_m4p8, &b_TauG2Weights_ceBRe33_m4p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m4p0", &TauG2Weights_ceBRe33_m4p0, &b_TauG2Weights_ceBRe33_m4p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m3p2", &TauG2Weights_ceBRe33_m3p2, &b_TauG2Weights_ceBRe33_m3p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m2p4", &TauG2Weights_ceBRe33_m2p4, &b_TauG2Weights_ceBRe33_m2p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m1p6", &TauG2Weights_ceBRe33_m1p6, &b_TauG2Weights_ceBRe33_m1p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_m0p8", &TauG2Weights_ceBRe33_m0p8, &b_TauG2Weights_ceBRe33_m0p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_0p0", &TauG2Weights_ceBRe33_0p0, &b_TauG2Weights_ceBRe33_0p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_0p8", &TauG2Weights_ceBRe33_0p8, &b_TauG2Weights_ceBRe33_0p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_1p6", &TauG2Weights_ceBRe33_1p6, &b_TauG2Weights_ceBRe33_1p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_2p4", &TauG2Weights_ceBRe33_2p4, &b_TauG2Weights_ceBRe33_2p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_3p2", &TauG2Weights_ceBRe33_3p2, &b_TauG2Weights_ceBRe33_3p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_4p0", &TauG2Weights_ceBRe33_4p0, &b_TauG2Weights_ceBRe33_4p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_4p8", &TauG2Weights_ceBRe33_4p8, &b_TauG2Weights_ceBRe33_4p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_5p6", &TauG2Weights_ceBRe33_5p6, &b_TauG2Weights_ceBRe33_5p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_6p4", &TauG2Weights_ceBRe33_6p4, &b_TauG2Weights_ceBRe33_6p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_7p2", &TauG2Weights_ceBRe33_7p2, &b_TauG2Weights_ceBRe33_7p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_8p0", &TauG2Weights_ceBRe33_8p0, &b_TauG2Weights_ceBRe33_8p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_8p8", &TauG2Weights_ceBRe33_8p8, &b_TauG2Weights_ceBRe33_8p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_9p6", &TauG2Weights_ceBRe33_9p6, &b_TauG2Weights_ceBRe33_9p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_10p4", &TauG2Weights_ceBRe33_10p4, &b_TauG2Weights_ceBRe33_10p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_11p2", &TauG2Weights_ceBRe33_11p2, &b_TauG2Weights_ceBRe33_11p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_12p0", &TauG2Weights_ceBRe33_12p0, &b_TauG2Weights_ceBRe33_12p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_12p8", &TauG2Weights_ceBRe33_12p8, &b_TauG2Weights_ceBRe33_12p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_13p6", &TauG2Weights_ceBRe33_13p6, &b_TauG2Weights_ceBRe33_13p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_14p4", &TauG2Weights_ceBRe33_14p4, &b_TauG2Weights_ceBRe33_14p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_15p2", &TauG2Weights_ceBRe33_15p2, &b_TauG2Weights_ceBRe33_15p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_16p0", &TauG2Weights_ceBRe33_16p0, &b_TauG2Weights_ceBRe33_16p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_16p8", &TauG2Weights_ceBRe33_16p8, &b_TauG2Weights_ceBRe33_16p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_17p6", &TauG2Weights_ceBRe33_17p6, &b_TauG2Weights_ceBRe33_17p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_18p4", &TauG2Weights_ceBRe33_18p4, &b_TauG2Weights_ceBRe33_18p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_19p2", &TauG2Weights_ceBRe33_19p2, &b_TauG2Weights_ceBRe33_19p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_20p0", &TauG2Weights_ceBRe33_20p0, &b_TauG2Weights_ceBRe33_20p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_20p8", &TauG2Weights_ceBRe33_20p8, &b_TauG2Weights_ceBRe33_20p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_21p6", &TauG2Weights_ceBRe33_21p6, &b_TauG2Weights_ceBRe33_21p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_22p4", &TauG2Weights_ceBRe33_22p4, &b_TauG2Weights_ceBRe33_22p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_23p2", &TauG2Weights_ceBRe33_23p2, &b_TauG2Weights_ceBRe33_23p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_24p0", &TauG2Weights_ceBRe33_24p0, &b_TauG2Weights_ceBRe33_24p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_24p8", &TauG2Weights_ceBRe33_24p8, &b_TauG2Weights_ceBRe33_24p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_25p6", &TauG2Weights_ceBRe33_25p6, &b_TauG2Weights_ceBRe33_25p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_26p4", &TauG2Weights_ceBRe33_26p4, &b_TauG2Weights_ceBRe33_26p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_27p2", &TauG2Weights_ceBRe33_27p2, &b_TauG2Weights_ceBRe33_27p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_28p0", &TauG2Weights_ceBRe33_28p0, &b_TauG2Weights_ceBRe33_28p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_28p8", &TauG2Weights_ceBRe33_28p8, &b_TauG2Weights_ceBRe33_28p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_29p6", &TauG2Weights_ceBRe33_29p6, &b_TauG2Weights_ceBRe33_29p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_30p4", &TauG2Weights_ceBRe33_30p4, &b_TauG2Weights_ceBRe33_30p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_31p2", &TauG2Weights_ceBRe33_31p2, &b_TauG2Weights_ceBRe33_31p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_32p0", &TauG2Weights_ceBRe33_32p0, &b_TauG2Weights_ceBRe33_32p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_32p8", &TauG2Weights_ceBRe33_32p8, &b_TauG2Weights_ceBRe33_32p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_33p6", &TauG2Weights_ceBRe33_33p6, &b_TauG2Weights_ceBRe33_33p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_34p4", &TauG2Weights_ceBRe33_34p4, &b_TauG2Weights_ceBRe33_34p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_35p2", &TauG2Weights_ceBRe33_35p2, &b_TauG2Weights_ceBRe33_35p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_36p0", &TauG2Weights_ceBRe33_36p0, &b_TauG2Weights_ceBRe33_36p0);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_36p8", &TauG2Weights_ceBRe33_36p8, &b_TauG2Weights_ceBRe33_36p8);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_37p6", &TauG2Weights_ceBRe33_37p6, &b_TauG2Weights_ceBRe33_37p6);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_38p4", &TauG2Weights_ceBRe33_38p4, &b_TauG2Weights_ceBRe33_38p4);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_39p2", &TauG2Weights_ceBRe33_39p2, &b_TauG2Weights_ceBRe33_39p2);
   fChain->SetBranchAddress("TauG2Weights_ceBRe33_40p0", &TauG2Weights_ceBRe33_40p0, &b_TauG2Weights_ceBRe33_40p0);
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
   fChain->SetBranchAddress("nOtherPV", &nOtherPV, &b_nOtherPV);
   fChain->SetBranchAddress("OtherPV_z", OtherPV_z, &b_OtherPV_z);
   fChain->SetBranchAddress("OtherPV_ntracks0p9", OtherPV_ntracks0p9, &b_OtherPV_ntracks0p9);
   fChain->SetBranchAddress("OtherPV_ntracks0p5", OtherPV_ntracks0p5, &b_OtherPV_ntracks0p5);
   fChain->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
   fChain->SetBranchAddress("PV_score", &PV_score, &b_PV_score);
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
   fChain->SetBranchAddress("GenVtx_t0", &GenVtx_t0, &b_GenVtx_t0);
   fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, &b_HLT_Ele32_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf, &b_HLT_Ele35_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1, &b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
   fChain->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1, &b_HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
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
   fChain->SetBranchAddress("LepCand_eleMVAiso90", LepCand_eleMVAiso90, &b_LepCand_eleMVAiso90);
   fChain->SetBranchAddress("LepCand_eleMVAiso80", LepCand_eleMVAiso80, &b_LepCand_eleMVAiso80);
   fChain->SetBranchAddress("LepCand_eleMVAnoiso90", LepCand_eleMVAnoiso90, &b_LepCand_eleMVAnoiso90);
   fChain->SetBranchAddress("LepCand_eleMVAnoiso80", LepCand_eleMVAnoiso80, &b_LepCand_eleMVAnoiso80);
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
   fChain->SetBranchAddress("nGenCand", &nGenCand, &b_nGenCand);
   fChain->SetBranchAddress("GenCand_id", &GenCand_id, &b_GenCand_id);
   fChain->SetBranchAddress("GenCand_pt", &GenCand_pt, &b_GenCand_pt);
   fChain->SetBranchAddress("GenCand_eta", &GenCand_eta, &b_GenCand_eta);
   fChain->SetBranchAddress("GenCand_phi", &GenCand_phi, &b_GenCand_phi);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("Track_pt", Track_pt, &b_Track_pt);
   fChain->SetBranchAddress("Track_eta", Track_eta, &b_Track_eta);
   fChain->SetBranchAddress("Track_phi", Track_phi, &b_Track_phi);
   fChain->SetBranchAddress("Track_dz", Track_dz, &b_Track_dz);
   fChain->SetBranchAddress("Track_dxy", Track_dxy, &b_Track_dxy);
   fChain->SetBranchAddress("Track_charge", Track_charge, &b_Track_charge);
   fChain->SetBranchAddress("Track_isMatchedToHS", Track_isMatchedToHS, &b_Track_isMatchedToHS);
   fChain->SetBranchAddress("Track_lostInnerHits", Track_lostInnerHits, &b_Track_lostInnerHits);
   fChain->SetBranchAddress("Track_trackHighPurity", Track_trackHighPurity, &b_Track_trackHighPurity);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
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

Bool_t classe::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void classe::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t classe::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef classe_cxx
