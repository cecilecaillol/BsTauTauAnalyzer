#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include "TMultiGraph.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <TF1.h>
#include <TDirectoryFile.h>
#include <TRandom3.h>
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TKey.h"
#include "THashList.h"
#include "THStack.h"
#include "TPaveLabel.h"
#include "TFile.h"
#include "TTree.h"
#include "tr_Tree.h"

using namespace std;

int main(int argc, char** argv) {

    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string name = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    TTree *arbre2 = (TTree*) f_Double->Get("Runs");
    float ngen=0;
    if (name!="data_obs") {
       Int_t nentries_wtn2 = (Int_t) arbre2->GetEntries();
       arbre2->SetBranchAddress("genEventSumw", &genEventSumw);
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
         ngen+=genEventSumw;
       }
    }
    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6077.2; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt100to250"){ xs=689.75; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt250to400"){ xs=24.51; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt400to600"){cout<<"trouve"<<endl; xs=3.110; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt600toInf"){ xs=0.4683; weight=luminosity*xs/ngen;}
    else if (sample=="WJets"){ xs=61527.5; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt50to100"){ xs=387.13; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt100to250"){ xs=89.39; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt250to400"){ xs=3.43; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt400to650"){ xs=0.464; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt650toInf"){ xs=0.0436; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu"){ xs=831.76*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic"){ xs=831.76*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic"){ xs=831.76*0.4544; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L"){ xs=1.212; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=4.42965; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu"){ xs=11.95; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q"){ xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=3.0; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu"){ xs=118.7*0.3*0.3; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_tau"){ xs=(80.95+136.02)*0.108; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.95; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}

    //if (input.find("renano") < 140){
      if (sample=="DY") weight*=0.318*0.98;
      else if (sample=="TTTo2L2Nu") weight*=0.657;
      else if (sample=="TTToSemiLeptonic") weight*=0.401;
      else if (sample=="TTToHadronic") weight*=0.170;
      else if (sample=="ST_t_top") weight*=0.118;
      else if (sample=="ST_t_antitop") weight*=0.122;
      else if (sample=="ST_tW_top") weight*=0.273;
      else if (sample=="ST_tW_antitop") weight*=0.272;
      else if (sample=="WW2L2Nu") weight*=0.397;
      else if (sample=="WW2L2Q") weight*=0.341;
      else if (sample=="WZ3LNu") weight*=0.341;
      else if (sample=="ZZ4L") weight*=0.304;
      else if (sample=="ZZ2L2Nu") weight*=0.302;
      else if (sample=="ZZ2L2Q") weight*=0.373;
      else if (sample=="GGMuMu") weight*=0.941;
    //}


    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("nLepCand", &nLepCand);
    arbre->SetBranchAddress("LepCand_id", &LepCand_id);
    arbre->SetBranchAddress("LepCand_gen", &LepCand_gen);
    arbre->SetBranchAddress("LepCand_pt", &LepCand_pt);
    arbre->SetBranchAddress("LepCand_eta", &LepCand_eta);
    arbre->SetBranchAddress("LepCand_phi", &LepCand_phi);
    arbre->SetBranchAddress("LepCand_charge", &LepCand_charge);
    arbre->SetBranchAddress("LepCand_dxy", &LepCand_dxy);
    arbre->SetBranchAddress("LepCand_dz", &LepCand_dz);
    arbre->SetBranchAddress("LepCand_muonMediumId", &LepCand_muonMediumId);
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso);

    arbre->SetBranchAddress("GenCand_id", &GenCand_id);
    arbre->SetBranchAddress("GenCand_pt", &GenCand_pt);
    arbre->SetBranchAddress("GenCand_eta", &GenCand_eta);
    arbre->SetBranchAddress("GenCand_phi", &GenCand_phi);
    arbre->SetBranchAddress("nGenCand", &nGenCand);

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("beamspot_sigmaZ", &beamspot_sigmaZ);
    arbre->SetBranchAddress("beamspot_z0", &beamspot_z0);
    arbre->SetBranchAddress("PV_npvs", &PV_npvs);

    arbre->SetBranchAddress("nChargedPFCandidates", &nChargedPFCandidates);
    //arbre->SetBranchAddress("ChargedPFCandidates_dxy", &ChargedPFCandidates_dxy);
    arbre->SetBranchAddress("ChargedPFCandidates_dz", &ChargedPFCandidates_dz);
    //arbre->SetBranchAddress("ChargedPFCandidates_eta", &ChargedPFCandidates_eta);
    //arbre->SetBranchAddress("ChargedPFCandidates_mass", &ChargedPFCandidates_mass);
    //arbre->SetBranchAddress("ChargedPFCandidates_phi", &ChargedPFCandidates_phi);
    arbre->SetBranchAddress("ChargedPFCandidates_pt", &ChargedPFCandidates_pt);
    //arbre->SetBranchAddress("ChargedPFCandidates_charge", &ChargedPFCandidates_charge);
    //arbre->SetBranchAddress("ChargedPFCandidates_fromPV", &ChargedPFCandidates_fromPV);
    //arbre->SetBranchAddress("ChargedPFCandidates_lostInnerHits", &ChargedPFCandidates_lostInnerHits);
    //arbre->SetBranchAddress("ChargedPFCandidates_pdgId", &ChargedPFCandidates_pdgId);
    //arbre->SetBranchAddress("ChargedPFCandidates_trackHighPurity", &ChargedPFCandidates_trackHighPurity);
    //arbre->SetBranchAddress("ChargedPFCandidates_isMatchedToGenHS", &ChargedPFCandidates_isMatchedToGenHS);

    arbre->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
    arbre->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
    arbre->SetBranchAddress("pu_weight", &pu_weight);
    arbre->SetBranchAddress("puWeight", &puWeight);
    arbre->SetBranchAddress("genWeight", &genWeight);

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");
   auto b1_7=arbre->GetBranch("LepCand_dxy");
   auto b1_8=arbre->GetBranch("LepCand_dz");
   /*arbre->AddBranchToCache(b1_1, true);
   arbre->AddBranchToCache(b1_2, true);
   arbre->AddBranchToCache(b1_3, true);
   arbre->AddBranchToCache(b1_4, true);
   arbre->AddBranchToCache(b1_5, true);
   arbre->AddBranchToCache(b1_6, true);
   arbre->AddBranchToCache(b1_7, true);
   arbre->AddBranchToCache(b1_8, true);*/

   auto b2_1=arbre->GetBranch("HLT_IsoMu24");
   //arbre->AddBranchToCache(b2_1, true);

   auto b3_1=arbre->GetBranch("LepCand_charge");
   auto b3_2=arbre->GetBranch("LepCand_muonMediumId");
   auto b3_3=arbre->GetBranch("LepCand_muonIso");
   /*arbre->AddBranchToCache(b3_1, true);
   arbre->AddBranchToCache(b3_2, true);
   arbre->AddBranchToCache(b3_3, true);*/

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("puWeight");
   auto b4_4=arbre->GetBranch("nGenCand");
   auto b4_5=arbre->GetBranch("GenCand_id");
   auto b4_6=arbre->GetBranch("GenCand_pt");
   auto b4_7=arbre->GetBranch("GenCand_eta");
   auto b4_8=arbre->GetBranch("GenCand_phi");

   /*arbre->AddBranchToCache(b4_1, true);
   arbre->AddBranchToCache(b4_2, true);*/

   auto b5_1=arbre->GetBranch("PV_z");
   auto b5_2=arbre->GetBranch("GenVtx_z");
   auto b5_3=arbre->GetBranch("beamspot_sigmaZ");
   auto b5_4=arbre->GetBranch("beamspot_z0");
   auto b5_5=arbre->GetBranch("PV_npvs");
   /*arbre->AddBranchToCache(b5_1, true);
   arbre->AddBranchToCache(b5_2, true);*/


   auto b6_1=arbre->GetBranch("nChargedPFCandidates");
   auto b6_2=arbre->GetBranch("ChargedPFCandidates_pt");
   auto b6_3=arbre->GetBranch("ChargedPFCandidates_dz");

   TH1F* h_beamspot = new TH1F("h_beamspot","h_beamspot",200,2.5,4.5); h_beamspot->Sumw2();
   TH1F* h_beamspotz = new TH1F("h_beamspotz","h_beamspotz",150,-15,15); h_beamspotz->Sumw2();

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpledimu = new TH1F("h_vtxresolution_simpledimu","h_vtxresolution_simpledimu",200,-1,1); h_vtxresolution_simpledimu->Sumw2();
   TH1F* h_dimumass = new TH1F("h_dimumass","h_dimumass",20,0,200); h_dimumass->Sumw2();

   TH1F* h0 = new TH1F("h0","h0",20,0,200); h0->Sumw2();
   TH1F* h0SS = new TH1F("h0SS","h0SS",20,0,200); h0SS->Sumw2();
   TH1F* h1 = new TH1F("h1","h1",100,0,1); h1->Sumw2();
   TH1F* h1SS = new TH1F("h1SS","h1SS",100,0,1); h1SS->Sumw2();
   TH1F* h2 = new TH1F("h2","h2",20,0,200); h2->Sumw2();
   TH1F* h2SS = new TH1F("h2SS","h2SS",20,0,200); h2SS->Sumw2();
   TH1F* h3 = new TH1F("h3","h3",200,0,200); h3->Sumw2();
   TH1F* h3SS = new TH1F("h3SS","h3SS",200,0,200); h3SS->Sumw2();

   TH1F* h_ntracks_test = new TH1F("h_ntracks_test","h_ntracks_test",30,0,30); h_ntracks_test->Sumw2();

   TH1F* h_tracksz = new TH1F("h_tracksz","h_tracksz",200,-20,20); h_tracksz->Sumw2();

   std::vector<TH1F*> h_ntracks;
   int nslices=100;
   for (int k=0; k<nslices; ++k){
     ostringstream HN0; HN0 << "h_ntracks" << k;
     h_ntracks.push_back(new TH1F (HN0.str().c_str(),"Ntracks",30,0,30)); h_ntracks[k]->Sumw2();
   }

   std::vector<TH1F*> h_ntracks_corrected;
   for (int k=0; k<nslices; ++k){
     ostringstream HN1; HN1 << "h_ntracks_corrected" << k;
     h_ntracks_corrected.push_back(new TH1F (HN1.str().c_str(),"Ntracks_corrected",30,0,30)); h_ntracks_corrected[k]->Sumw2();
   }

   std::vector<TH1F*> h_ntracks0p1;
   int nslices0p1=200;
   for (int k=0; k<nslices0p1; ++k){
     ostringstream HN0; HN0 << "h_ntracks0p1" << k;
     h_ntracks0p1.push_back(new TH1F (HN0.str().c_str(),"Ntracks",30,0,30)); h_ntracks0p1[k]->Sumw2();
   }

   std::vector<TH1F*> h_ntracks0p1_corrected;
   for (int k=0; k<nslices0p1; ++k){
     ostringstream HN1; HN1 << "h_ntracks0p1_corrected" << k;
     h_ntracks0p1_corrected.push_back(new TH1F (HN1.str().c_str(),"Ntracks_corrected",30,0,30)); h_ntracks0p1_corrected[k]->Sumw2();
   }

   // Scale factors
   TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","read");
   TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","read");
   TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root","read");
   TH2F* h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
   TH2F* h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
   TH2F* h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");

   if (year=="2016pre"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root","read");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_SingleMuonTriggers.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }
   if (year=="2016post"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root","read");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_SingleMuonTriggers.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }
   if (year=="2017"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root","read");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_SingleMuonTriggers.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }

   TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
   TF1* fit_aco = (TF1*) f_aco->Get("fit_A");

   TF1* fit_npvs = (TF1*) f_aco->Get("fit_npvs");

   TF1* f_beamspot=new TF1("f_beamspot","gaus",2.5,4.5);
   f_beamspot->SetParameter(0,1);
   f_beamspot->SetParameter(1,3.35);
   f_beamspot->SetParameter(2,0.15);

   TF1* f_beamspotz=new TF1("f_beamspotz","gaus",-10,10);
   f_beamspotz->SetParameter(0,1);
   f_beamspotz->SetParameter(1,-0.138);
   f_beamspotz->SetParameter(2,0.254);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	// Block build muons
        b1_1->GetEntry(i); b1_2->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_6->GetEntry(i); b1_7->GetEntry(i); b1_8->GetEntry(i);
        if (name!="data_obs") {b1_5->GetEntry(i);}

	TLorentzVector my_mu1;
	my_mu1.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        TLorentzVector my_mu2;
        my_mu2.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); //FIXME check muons are picked LepCand_id[0]==13

	float z1 = PV_z + LepCand_dz[0];
        float z2 = PV_z + LepCand_dz[1];

	if (fabs(my_mu1.Eta())>2.4) continue;
        if (fabs(my_mu2.Eta())>2.4) continue;
	if (my_mu1.Pt()<25 and my_mu2.Pt()<25) continue;
        if (my_mu1.Pt()<10 or my_mu2.Pt()<10) continue;
        if (LepCand_dxy[0]>0.05 or LepCand_dxy[1]>0.05) continue;
        if (fabs(LepCand_dz[0]-LepCand_dz[1])>0.2) continue;

	// Block trigger
        b2_1->GetEntry(i);
        if (!HLT_IsoMu24) continue;
	if ((my_mu1+my_mu2).M()<50) continue;

	// Block ID/iso
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i);
	if (!LepCand_muonMediumId[0] or !LepCand_muonMediumId[1]) continue;
	if (LepCand_muonIso[0]>0.10 or LepCand_muonIso[1]>0.10) continue;
        bool is_OS=(LepCand_charge[0]*LepCand_charge[1]<0);

	// Block weights
	if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_7->GetEntry(i); b4_8->GetEntry(i);b4_3->GetEntry(i);}

	TLorentzVector my_genmu1; my_genmu1.SetPtEtaPhiM(0,0,0,0);
        TLorentzVector my_genmu2; my_genmu2.SetPtEtaPhiM(0,0,0,0);
	float gen_aco=1.0;
	if (name!="data_obs") {
          for (int k=0; k<nGenCand; ++k){
	     if (fabs(GenCand_id[k])==13 and my_genmu1.Pt()<1) my_genmu1.SetPtEtaPhiM(GenCand_pt[k],GenCand_eta[k],GenCand_phi[k],0);
             else if (fabs(GenCand_id[k])==13 and my_genmu2.Pt()<1) my_genmu2.SetPtEtaPhiM(GenCand_pt[k],GenCand_eta[k],GenCand_phi[k],0);
  	  }
	  gen_aco = (1.0 -fabs(my_genmu1.DeltaPhi(my_genmu2))/3.14159);
	  if (gen_aco>0.35) gen_aco=0.35;
	}

        float aweight=1.0;
        if (name!="data_obs"){
           aweight*=genWeight;
           //aweight*=pu_weight;
           aweight*=puWeight;
           float trgsf1=1.0;
           float recosf1=1.0;
           float idsf1=1.0;
           float muonIsoSF1=1.0;
           float mu1pt=my_mu1.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;

           float trgsf2=1.0;
           float recosf2=1.0;
           float idsf2=1.0;
           float muonIsoSF2=1.0;
           float mu2pt=my_mu2.Pt();
           if (mu2pt>120) mu2pt=119;
           if (mu2pt<15) mu2pt=16;

           trgsf1 = h_muonTrgSF->GetBinContent(h_muonTrgSF->GetXaxis()->FindBin(fabs(my_mu1.Eta())),h_muonTrgSF->GetYaxis()->FindBin(mu1pt));
           idsf1 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu1.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           muonIsoSF1 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu1.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
           trgsf2 = h_muonTrgSF->GetBinContent(h_muonTrgSF->GetXaxis()->FindBin(fabs(my_mu2.Eta())),h_muonTrgSF->GetYaxis()->FindBin(mu2pt));
           idsf2 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu2.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu2pt));
           muonIsoSF2 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu2.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu2pt));

	   float trgsf=1.0;
	   if (my_mu1.Pt()>25 and my_mu2.Pt()<=25) trgsf=trgsf1;
	   else if (my_mu1.Pt()<=25 and my_mu2.Pt()>25) trgsf=trgsf1;
	   else if (my_mu1.Pt()>25 and my_mu2.Pt()>25) trgsf=(1-(1-trgsf1)*(1-trgsf2));

	   float aco_weight=1.0;
	   if (sample=="DY") aco_weight=fit_aco->Eval(gen_aco);
           aweight=aweight*trgsf*recosf1*idsf1*muonIsoSF1*recosf2*idsf2*muonIsoSF2*aco_weight;
        }

	// Block vertices
	b5_1->GetEntry(i);b5_3->GetEntry(i);b5_4->GetEntry(i);b5_5->GetEntry(i);
	if (name!="data_obs") b5_2->GetEntry(i);
	float simple_dimu_z=0.5*(2*PV_z+LepCand_dz[0]+LepCand_dz[1]);

        if (sample=="DY") aweight*=fit_npvs->Eval(TMath::Min(70,PV_npvs));
	h_beamspot->Fill(beamspot_sigmaZ);
        h_beamspotz->Fill(beamspot_z0);

	if (is_OS){
	   float vtxresolution_PV = (GenVtx_z-PV_z)/GenVtx_z;
	   if (vtxresolution_PV>1) vtxresolution_PV=0.99;
           else if (vtxresolution_PV<-1) vtxresolution_PV=-0.99;
	   h_vtxresolution_PV->Fill(vtxresolution_PV);

           float vtxresolution_simpledimu = (GenVtx_z-simple_dimu_z)/GenVtx_z;
           if (vtxresolution_simpledimu>1) vtxresolution_simpledimu=0.99;
           else if (vtxresolution_simpledimu<-1) vtxresolution_simpledimu=-0.99;
           h_vtxresolution_simpledimu->Fill(vtxresolution_simpledimu);
	}

	float aco = (1.0 -fabs(my_mu1.DeltaPhi(my_mu2))/3.14159);
	if (is_OS){
	   h_dimumass->Fill((my_mu1+my_mu2).M(),aweight*weight);
	   h0->Fill((my_mu1+my_mu2).M(),aweight*weight);
           h1->Fill(aco,aweight*weight);
           h2->Fill((my_mu1+my_mu2).Pt(),aweight*weight);
           h3->Fill(PV_npvs,aweight*weight);
	}

        if (!is_OS){
           h0SS->Fill((my_mu1+my_mu2).M(),aweight*weight);
           h1SS->Fill(aco,aweight*weight);
           h2SS->Fill((my_mu1+my_mu2).Pt(),aweight*weight);
           h3SS->Fill(PV_npvs,aweight*weight);
        }

	b6_1->GetEntry(i); b6_2->GetEntry(i); b6_3->GetEntry(i);

	//0p2 window width
        int ntracks1=0;
        for (int nt=0; nt<nChargedPFCandidates; ++nt){
           if (ChargedPFCandidates_pt[nt]>0.5 and ChargedPFCandidates_dz[nt]>3.0 and ChargedPFCandidates_dz[nt]<3.05) {ntracks1++;}
        }

	if (fabs(91.2-(my_mu1+my_mu2).M())<15 and is_OS){
	   for (int j=0; j<100; ++j){
             int ntracks1=0;
	     if (simple_dimu_z<-10+(j-5)*0.2 or simple_dimu_z>-10+(j+5)*0.2){
                for (int nt=0; nt<nChargedPFCandidates; ++nt){
                   if (ChargedPFCandidates_pt[nt]>0.5 and (PV_z+ChargedPFCandidates_dz[nt])>=-10+j*0.2 and (PV_z+ChargedPFCandidates_dz[nt])<-10+(j+1)*0.2) {
		     ntracks1++;
		   }
                }
	        h_ntracks[j]->Fill(ntracks1,aweight*weight);
	     }
	   }
	}

	if (name!="data_obs"){
	   float rnd_beamspot=f_beamspot->GetRandom();
           float rnd_beamspotz=f_beamspotz->GetRandom();
           if (fabs(91.2-(my_mu1+my_mu2).M())<15 and is_OS){
              for (int j=0; j<100; ++j){
                int ntracks_corrected1=0;
                if (simple_dimu_z<-10+(j-5)*0.2 or simple_dimu_z>-10+(j+5)*0.2){
                   for (int nt=0; nt<nChargedPFCandidates; ++nt){
	   	   float newz=(PV_z+ChargedPFCandidates_dz[nt])*rnd_beamspot/3.5 + (rnd_beamspotz-0.02488);
                      if (ChargedPFCandidates_pt[nt]>0.5 and newz>=-10+j*0.2 and newz<-10+(j+1)*0.2) {            
                        ntracks_corrected1++;
                      }
                   }
                   h_ntracks_corrected[j]->Fill(ntracks_corrected1,aweight*weight);
                }
              }
           }
	}

        //0p1 window width
        if (fabs(91.2-(my_mu1+my_mu2).M())<15 and is_OS){
           for (int j=0; j<200; ++j){
             int ntracks1=0;
             if (simple_dimu_z<-10+(j-10)*0.1 or simple_dimu_z>-10+(j+10)*0.1){
                for (int nt=0; nt<nChargedPFCandidates; ++nt){
                   if (ChargedPFCandidates_pt[nt]>0.5 and (PV_z+ChargedPFCandidates_dz[nt])>=-10+j*0.1 and (PV_z+ChargedPFCandidates_dz[nt])<-10+(j+1)*0.1) {
                     ntracks1++;
                   }
                }
                h_ntracks0p1[j]->Fill(ntracks1,aweight*weight);
             }
           }
        }

        if (name!="data_obs"){
           float rnd_beamspot=f_beamspot->GetRandom();
           float rnd_beamspotz=f_beamspotz->GetRandom();
           if (fabs(91.2-(my_mu1+my_mu2).M())<15 and is_OS){
              for (int j=0; j<200; ++j){
                int ntracks_corrected1=0;
                if (simple_dimu_z<-10+(j-10)*0.1 or simple_dimu_z>-10+(j+10)*0.1){
                   for (int nt=0; nt<nChargedPFCandidates; ++nt){
                   float newz=(PV_z+ChargedPFCandidates_dz[nt])*rnd_beamspot/3.5 + (rnd_beamspotz-0.02488);
                      if (ChargedPFCandidates_pt[nt]>0.5 and newz>=-10+j*0.1 and newz<-10+(j+1)*0.1) {
                        ntracks_corrected1++;
                      }
                   }
                   h_ntracks0p1_corrected[j]->Fill(ntracks_corrected1,aweight*weight);
                }
              }
           }
        }

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_ntracks_test->Write();
    h_tracksz->Write();

    h_beamspot->Write();
    h_beamspotz->Write();

    h_dimumass->Write();
    h_vtxresolution_PV->Write();
    h_vtxresolution_simpledimu->Write();
    for (int i=0; i<nslices; ++i){
      h_ntracks[i]->Write();
      if (name!="data_obs") h_ntracks_corrected[i]->Write();
    }

    for (int i=0; i<nslices0p1; ++i){
      h_ntracks0p1[i]->Write();
      if (name!="data_obs") h_ntracks0p1_corrected[i]->Write();
    }

    TDirectory *dir0 =fout->mkdir("mumu0");
    dir0->cd();
    h0->SetName(name.c_str());
    h0->Write();

    TDirectory *dir0SS =fout->mkdir("mumu0_SS");
    dir0SS->cd();
    h0SS->SetName(name.c_str());
    h0SS->Write();

    TDirectory *dir1 =fout->mkdir("mumu1");
    dir1->cd();
    h1->SetName(name.c_str());
    h1->Write();

    TDirectory *dir1SS =fout->mkdir("mumu1_SS");
    dir1SS->cd();
    h1SS->SetName(name.c_str());
    h1SS->Write();

    TDirectory *dir2 =fout->mkdir("mumu2");
    dir2->cd();
    h2->SetName(name.c_str());
    h2->Write();

    TDirectory *dir2SS =fout->mkdir("mumu2_SS");
    dir2SS->cd();
    h2SS->SetName(name.c_str());
    h2SS->Write();

    TDirectory *dir3 =fout->mkdir("mumu3");
    dir3->cd();
    h3->SetName(name.c_str());
    h3->Write();

    TDirectory *dir3SS =fout->mkdir("mumu3_SS");
    dir3SS->cd();
    h3SS->SetName(name.c_str());
    h3SS->Write();

    fout->Close();
} 


