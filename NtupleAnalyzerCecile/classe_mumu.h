//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 21 15:17:21 2022 by ROOT version 6.14/09
// from TTree Events/Events
// found on file: /eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/DY.root
//////////////////////////////////////////////////////////

#ifndef classe_mumu_h
#define classe_mumu_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class classe_mumu {
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
   Float_t         ChargedPFCandidates_dz[1859];   //[nChargedPFCandidates]
   Float_t         ChargedPFCandidates_pt[1859];   //[nChargedPFCandidates]
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
   Float_t         LHE_Vpt;
   UChar_t         LHE_Njets;
   UInt_t          nLostTracks;
   Float_t         LostTracks_dz[225];   //[nLostTracks]
   Float_t         LostTracks_pt[225];   //[nLostTracks]
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
   Float_t         PV_ndof;
   Float_t         PV_x;
   Float_t         PV_y;
   Float_t         PV_z;
   Float_t         PV_chi2;
   Float_t         PV_score;
   Int_t           PV_npvs;
   Int_t           PV_npvsGood;
   Float_t         GenVtx_t0;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoMu27;
   Int_t           nLepCand;
   Int_t           LepCand_id[6];   //[nLepCand]
   Float_t         LepCand_pt[6];   //[nLepCand]
   Float_t         LepCand_eta[6];   //[nLepCand]
   Float_t         LepCand_phi[6];   //[nLepCand]
   Int_t           LepCand_charge[6];   //[nLepCand]
   Float_t         LepCand_dxy[6];   //[nLepCand]
   Float_t         LepCand_dz[6];   //[nLepCand]
   Float_t         LepCand_gen[6];   //[nLepCand]
   Int_t           LepCand_vse[6];   //[nLepCand]
   Int_t           LepCand_vsmu[6];   //[nLepCand]
   Int_t           LepCand_vsjet[6];   //[nLepCand]
   Int_t           LepCand_muonMediumId[6];   //[nLepCand]
   Float_t         LepCand_muonIso[6];   //[nLepCand]
   Int_t           LepCand_eleMVAiso90[6];   //[nLepCand]
   Int_t           LepCand_eleMVAiso80[6];   //[nLepCand]
   Float_t         LepCand_eleIso[6];   //[nLepCand]
   Float_t         LepCand_tauidMsf[6];   //[nLepCand]
   Float_t         LepCand_taues[6];   //[nLepCand]
   Float_t         LepCand_fes[6];   //[nLepCand]
   Float_t         LepCand_antimusf[6];   //[nLepCand]
   Float_t         LepCand_antielesf[6];   //[nLepCand]
   Int_t           LepCand_DecayMode[6];   //[nLepCand]
   Float_t         LepCand_tauidMsfDM[6];   //[nLepCand]
   Float_t         LepCand_tautriggersf[6];   //[nLepCand]
   Int_t           nGenCand;
   Int_t           GenCand_id[4];   //[nGenCand]
   Float_t         GenCand_pt[4];   //[nGenCand]
   Float_t         GenCand_eta[4];   //[nGenCand]
   Float_t         GenCand_phi[4];   //[nGenCand]
   Int_t           nJets;
   Float_t         V_genpt;
   Float_t         pu_weight;

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
   TBranch        *b_ChargedPFCandidates_dz;   //!
   TBranch        *b_ChargedPFCandidates_pt;   //!
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
   TBranch        *b_LHE_Vpt;   //!
   TBranch        *b_LHE_Njets;   //!
   TBranch        *b_nLostTracks;   //!
   TBranch        *b_LostTracks_dz;   //!
   TBranch        *b_LostTracks_pt;   //!
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
   TBranch        *b_PV_ndof;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_chi2;   //!
   TBranch        *b_PV_score;   //!
   TBranch        *b_PV_npvs;   //!
   TBranch        *b_PV_npvsGood;   //!
   TBranch        *b_GenVtx_t0;   //!
   TBranch        *b_HLT_IsoMu24;   //!
   TBranch        *b_HLT_IsoMu27;   //!
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
   TBranch        *b_LepCand_eleIso;   //!
   TBranch        *b_LepCand_tauidMsf;   //!
   TBranch        *b_LepCand_taues;   //!
   TBranch        *b_LepCand_fes;   //!
   TBranch        *b_LepCand_antimusf;   //!
   TBranch        *b_LepCand_antielesf;   //!
   TBranch        *b_LepCand_DecayMode;   //!
   TBranch        *b_LepCand_tauidMsfDM;   //!
   TBranch        *b_LepCand_tautriggersf;   //!
   TBranch        *b_nGenCand;   //!
   TBranch        *b_GenCand_id;   //!
   TBranch        *b_GenCand_pt;   //!
   TBranch        *b_GenCand_eta;   //!
   TBranch        *b_GenCand_phi;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_V_genpt;   //!
   TBranch        *b_pu_weight;   //!

   classe_mumu(TTree *tree=0);
   virtual ~classe_mumu();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef classe_mumu_cxx
classe_mumu::classe_mumu(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/DY.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_mumu_2018/DY.root");
      }
      f->GetObject("Events",tree);

   }
   Init(tree);
}

classe_mumu::~classe_mumu()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t classe_mumu::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t classe_mumu::LoadTree(Long64_t entry)
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

void classe_mumu::Init(TTree *tree)
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
   fChain->SetBranchAddress("ChargedPFCandidates_dz", ChargedPFCandidates_dz, &b_ChargedPFCandidates_dz);
   fChain->SetBranchAddress("ChargedPFCandidates_pt", ChargedPFCandidates_pt, &b_ChargedPFCandidates_pt);
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
   fChain->SetBranchAddress("LHE_Vpt", &LHE_Vpt, &b_LHE_Vpt);
   fChain->SetBranchAddress("LHE_Njets", &LHE_Njets, &b_LHE_Njets);
   fChain->SetBranchAddress("nLostTracks", &nLostTracks, &b_nLostTracks);
   fChain->SetBranchAddress("LostTracks_dz", LostTracks_dz, &b_LostTracks_dz);
   fChain->SetBranchAddress("LostTracks_pt", LostTracks_pt, &b_LostTracks_pt);
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
   fChain->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
   fChain->SetBranchAddress("PV_score", &PV_score, &b_PV_score);
   fChain->SetBranchAddress("PV_npvs", &PV_npvs, &b_PV_npvs);
   fChain->SetBranchAddress("PV_npvsGood", &PV_npvsGood, &b_PV_npvsGood);
   fChain->SetBranchAddress("GenVtx_t0", &GenVtx_t0, &b_GenVtx_t0);
   fChain->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24, &b_HLT_IsoMu24);
   fChain->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27, &b_HLT_IsoMu27);
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
   fChain->SetBranchAddress("LepCand_eleIso", LepCand_eleIso, &b_LepCand_eleIso);
   fChain->SetBranchAddress("LepCand_tauidMsf", LepCand_tauidMsf, &b_LepCand_tauidMsf);
   fChain->SetBranchAddress("LepCand_taues", LepCand_taues, &b_LepCand_taues);
   fChain->SetBranchAddress("LepCand_fes", LepCand_fes, &b_LepCand_fes);
   fChain->SetBranchAddress("LepCand_antimusf", LepCand_antimusf, &b_LepCand_antimusf);
   fChain->SetBranchAddress("LepCand_antielesf", LepCand_antielesf, &b_LepCand_antielesf);
   fChain->SetBranchAddress("LepCand_DecayMode", LepCand_DecayMode, &b_LepCand_DecayMode);
   fChain->SetBranchAddress("LepCand_tauidMsfDM", LepCand_tauidMsfDM, &b_LepCand_tauidMsfDM);
   fChain->SetBranchAddress("LepCand_tautriggersf", LepCand_tautriggersf, &b_LepCand_tautriggersf);
   fChain->SetBranchAddress("nGenCand", &nGenCand, &b_nGenCand);
   fChain->SetBranchAddress("GenCand_id", GenCand_id, &b_GenCand_id);
   fChain->SetBranchAddress("GenCand_pt", GenCand_pt, &b_GenCand_pt);
   fChain->SetBranchAddress("GenCand_eta", GenCand_eta, &b_GenCand_eta);
   fChain->SetBranchAddress("GenCand_phi", GenCand_phi, &b_GenCand_phi);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("V_genpt", &V_genpt, &b_V_genpt);
   fChain->SetBranchAddress("pu_weight", &pu_weight, &b_pu_weight);
   Notify();
}

Bool_t classe_mumu::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void classe_mumu::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t classe_mumu::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef classe_mumu_cxx
