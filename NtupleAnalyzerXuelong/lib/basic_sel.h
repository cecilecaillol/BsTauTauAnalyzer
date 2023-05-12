#ifndef basic_sel_H
#define basic_sel_H

#include <ROOT/RDataFrame.hxx>
#include "TLorentzVector.h"

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"
#include <cmath>
#include "ROOT/RVec.hxx"
#include "ROOT/RDF/RInterface.hxx"
using namespace std;
using namespace ROOT;
using namespace ROOT::VecOps;
//using Vec_t = const ROOT::RVec<float>&;


ROOT::RVec<int> Getmutauindex(int nLepCand, ROOT::VecOps::RVec<int> &LepCand_id ,ROOT::VecOps::RVec<float> &LepCand_dz);
ROOT::RVec<int> Gettautauindex(int nLepCand, ROOT::VecOps::RVec<float> &LepCand_dz);
TLorentzVector GetLepVector(int Lepindex, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi,ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_taues, ROOT::VecOps::RVec<Float_t> &LepCand_fes);
TLorentzVector GetLepVector(int Lepindex, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi);
float Getxsweight_W(float LHE_Njets);
float GetMuonrecoSF(TLorentzVector my_mu);
float GetMuonrecoSF_stat(TLorentzVector my_mu);
float GetMuonrecoSF_syst(TLorentzVector my_mu);
float GetMuonIsoSF(TLorentzVector my_mu);
float GetMuonIsoSF_stat(TLorentzVector my_mu);
float GetMuonIsoSF_syst(TLorentzVector my_mu);
float GetMuonIDSF(TLorentzVector my_mu);
float GetMuonIDSF_stat(TLorentzVector my_mu);
float GetMuonIDSF_syst(TLorentzVector my_mu);
float GetMuonTriggerSF(TLorentzVector my_mu);
float GetMuonTriggerSF_stat(TLorentzVector my_mu);
float GetMuonTriggerSF_syst(TLorentzVector my_mu);
float GetMuonSF_HLTMu20Tau27(float mupt,float mueta);
float GetSFweight_mutau(float murecosf, float muisosf,float muidsf, float mutrgsf,float musf_HLTMu20Tau27, float puweight, int tauindex, bool isSingleMuonTrigger, bool isMuonTauTrigger,  ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_tauidMsf, ROOT::VecOps::RVec<Float_t> &LepCand_antielesf,ROOT::VecOps::RVec<Float_t> &LepCand_antimusf,ROOT::VecOps::RVec<Float_t> &LepCand_tautriggersf);
//float GetSFweight_mutau(TLorentzVector my_mu,float puweight, int tauindex, ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_tauidMsf, ROOT::VecOps::RVec<Float_t> &LepCand_antielesf,ROOT::VecOps::RVec<Float_t> &LepCand_antimusf);
float GetSFweight_tautau(float puweight, int tau1index, int tau2index, ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_tauidMsf, ROOT::VecOps::RVec<Float_t> &LepCand_antielesf,ROOT::VecOps::RVec<Float_t> &LepCand_antimusf,ROOT::VecOps::RVec<Float_t> &LepCand_tautriggersf);
bool GetisOS(ROOT::VecOps::RVec<Int_t> &LepCand_charge, int lep1index,int lep2index);
bool Getis_isolated(ROOT::VecOps::RVec<Int_t> &LepCand_vsjet,int tauindex);
float GetTransmass(TLorentzVector my_mu, float MET_pt, float MET_phi);
float GetCollMass(TLorentzVector my_lep1, TLorentzVector my_lep2, float MET_pt, float MET_phi);
float GetAcopl(TLorentzVector my_lep1, TLorentzVector my_lep2);
float recovtxz1(float lep1dz,float lep2dz,float PV_z);
float recovtxz2(TLorentzVector my_Lep1,TLorentzVector my_Lep2,float lep1dz,float lep2dz,float PV_z);
float recovtxz3(float lep1pt,float lep2pt,float lep1dz,float lep2dz,float PV_z);
#endif

