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
#include "myHelper.h"

using namespace std;

int main(int argc, char** argv) {

    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    TFile *f_friend = new TFile(output.c_str(),"recreate");
    TTree *tree_friend = new TTree("friend_tree","friend_tree");
    int ntracks_friend;
    int ntracksPU_friend;
    int ntracksHS_friend;
    int ntracksAll_friend;
    TBranch *bntracks_friend=tree_friend->Branch("ntracks_friend",&ntracks_friend,"ntracks_friend/I");
    TBranch *bntracksPU_friend=tree_friend->Branch("ntracksPU_friend",&ntracksPU_friend,"ntracksPU_friend/I");
    TBranch *bntracksHS_friend=tree_friend->Branch("ntracksHS_friend",&ntracksHS_friend,"ntracksHS_friend/I");
    TBranch *bntracksAll_friend=tree_friend->Branch("ntracksAll_friend",&ntracksAll_friend,"ntracksAll_friend/I");

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
    arbre->SetBranchAddress("LepCand_vse", &LepCand_vse);
    arbre->SetBranchAddress("LepCand_vsmu", &LepCand_vsmu);
    arbre->SetBranchAddress("LepCand_vsjet", &LepCand_vsjet);
    arbre->SetBranchAddress("LepCand_tauidMsf", &LepCand_tauidMsf);
    arbre->SetBranchAddress("LepCand_taues", &LepCand_taues);
    arbre->SetBranchAddress("LepCand_fes", &LepCand_fes);
    arbre->SetBranchAddress("LepCand_antimusf", &LepCand_antimusf);
    arbre->SetBranchAddress("LepCand_antielesf", &LepCand_antielesf);
    arbre->SetBranchAddress("LepCand_DecayMode", &LepCand_DecayMode);
    arbre->SetBranchAddress("LepCand_tautriggersf", &LepCand_tautriggersf);
    arbre->SetBranchAddress("LepCand_dz2", &LepCand_dz2);
    arbre->SetBranchAddress("LepCand_dz3", &LepCand_dz3);
    arbre->SetBranchAddress("LepCand_tk1Pt", &LepCand_tk1Pt);
    arbre->SetBranchAddress("LepCand_tk1Eta", &LepCand_tk1Eta);
    arbre->SetBranchAddress("LepCand_tk1Phi", &LepCand_tk1Phi);
    arbre->SetBranchAddress("LepCand_tk2Pt", &LepCand_tk2Pt);
    arbre->SetBranchAddress("LepCand_tk2Eta", &LepCand_tk2Eta);
    arbre->SetBranchAddress("LepCand_tk2Phi", &LepCand_tk2Phi);
    arbre->SetBranchAddress("LepCand_tk3Pt", &LepCand_tk3Pt);
    arbre->SetBranchAddress("LepCand_tk3Eta", &LepCand_tk3Eta);
    arbre->SetBranchAddress("LepCand_tk3Phi", &LepCand_tk3Phi);

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("run", &run);

    arbre->SetBranchAddress("nTracks", &nTracks);
    arbre->SetBranchAddress("Track_dz", &Track_dz);
    arbre->SetBranchAddress("Track_eta", &Track_eta);
    arbre->SetBranchAddress("Track_phi", &Track_phi);
    arbre->SetBranchAddress("Track_pt", &Track_pt);
    arbre->SetBranchAddress("Track_isMatchedToHS", &Track_isMatchedToHS);

    arbre->SetBranchAddress("pu_weight", &pu_weight);
    arbre->SetBranchAddress("genWeight", &genWeight);
    arbre->SetBranchAddress("nJets", &nJets);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");
   auto b1_7=arbre->GetBranch("LepCand_taues");
   auto b1_8=arbre->GetBranch("LepCand_fes");
   auto b1_9=arbre->GetBranch("LepCand_DecayMode");
   auto b1_10=arbre->GetBranch("LepCand_dz");
   auto b1_11=arbre->GetBranch("PV_z");
   auto b1_12=arbre->GetBranch("LepCand_dz2");
   auto b1_13=arbre->GetBranch("LepCand_dz3");
   auto b1_14=arbre->GetBranch("LepCand_tk1Pt");
   auto b1_15=arbre->GetBranch("LepCand_tk1Eta");
   auto b1_16=arbre->GetBranch("LepCand_tk1Phi");
   auto b1_17=arbre->GetBranch("LepCand_tk2Pt");
   auto b1_18=arbre->GetBranch("LepCand_tk2Eta");
   auto b1_19=arbre->GetBranch("LepCand_tk2Phi");
   auto b1_20=arbre->GetBranch("LepCand_tk3Pt");
   auto b1_21=arbre->GetBranch("LepCand_tk3Eta");
   auto b1_22=arbre->GetBranch("LepCand_tk3Phi");

   auto b7_1=arbre->GetBranch("nTracks");
   auto b7_2=arbre->GetBranch("Track_dz");
   auto b7_3=arbre->GetBranch("Track_eta");
   auto b7_4=arbre->GetBranch("Track_phi");
   auto b7_5=arbre->GetBranch("Track_pt");
   auto b7_6=arbre->GetBranch("Track_isMatchedToHS");

   float bs_z_mc=0.0;
   float bs_zsigma_mc=3.5;

   TFile* f_bs=new TFile("beamspot_UL2018_Data.root","read");
   TH1F* h_bs_sigma = (TH1F*) f_bs->Get("bs_sigma");
   TH1F* h_bs_z = (TH1F*) f_bs->Get("bs_z");
   TFile* f_bs_mc=new TFile("beamspot_UL2018_MC.root","read");
   TH1F* h_bs_sigma_mc = (TH1F*) f_bs_mc->Get("bs_sigma");
   TH1F* h_bs_z_mc = (TH1F*) f_bs_mc->Get("bs_z");
   bs_z_mc=h_bs_z_mc->GetMean();
   bs_zsigma_mc=h_bs_sigma_mc->GetMean();

   if (year=="2017"){
      TFile* f_bs=new TFile("beamspot_UL2017_Data.root","read");
      h_bs_sigma = (TH1F*) f_bs->Get("bs_sigma");
      h_bs_z = (TH1F*) f_bs->Get("bs_z");
      TFile* f_bs_mc=new TFile("beamspot_UL2017_MC.root","read");
      h_bs_sigma_mc = (TH1F*) f_bs_mc->Get("bs_sigma");
      h_bs_z_mc = (TH1F*) f_bs_mc->Get("bs_z");
      bs_z_mc=h_bs_z_mc->GetMean();
      bs_zsigma_mc=h_bs_sigma_mc->GetMean();
   }
   else if (year=="2016post"){
      TFile* f_bs=new TFile("beamspot_UL2016_postVFP_Data.root","read");
      h_bs_sigma = (TH1F*) f_bs->Get("bs_sigma");
      h_bs_z = (TH1F*) f_bs->Get("bs_z");
      TFile* f_bs_mc=new TFile("beamspot_UL2016_postVFP_MC.root","read");
      h_bs_sigma_mc = (TH1F*) f_bs_mc->Get("bs_sigma");
      h_bs_z_mc = (TH1F*) f_bs_mc->Get("bs_z");
      bs_z_mc=h_bs_z_mc->GetMean();
      bs_zsigma_mc=h_bs_sigma_mc->GetMean();
   }
   else if (year=="2016pre"){
      TFile* f_bs=new TFile("beamspot_UL2016_preVFP_Data.root","read");
      h_bs_sigma = (TH1F*) f_bs->Get("bs_sigma");
      h_bs_z = (TH1F*) f_bs->Get("bs_z");
      TFile* f_bs_mc=new TFile("beamspot_UL2016_preVFP_MC.root","read");
      h_bs_sigma_mc = (TH1F*) f_bs_mc->Get("bs_sigma");
      h_bs_z_mc = (TH1F*) f_bs_mc->Get("bs_z");
      bs_z_mc=h_bs_z_mc->GetMean();
      bs_zsigma_mc=h_bs_sigma_mc->GetMean();
   }

int nb_all=0;
int nb_HS0=0;
int nb_HS0_PU0=0;
int nb_PU0=0;

   for (Int_t i = 0; i < nentries_wtn; i++) {
	//arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        b1_6->GetEntry(i); b1_1->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_2->GetEntry(i); b1_9->GetEntry(i); b1_10->GetEntry(i); b1_11->GetEntry(i);
	b1_12->GetEntry(i);b1_13->GetEntry(i);b1_14->GetEntry(i);b1_15->GetEntry(i);b1_16->GetEntry(i);b1_17->GetEntry(i);b1_18->GetEntry(i);b1_19->GetEntry(i);b1_20->GetEntry(i);b1_21->GetEntry(i);b1_22->GetEntry(i);
        if (sample!="data_obs") {b1_5->GetEntry(i); b1_7->GetEntry(i); b1_8->GetEntry(i);}

        int mu_index=-1;
        for (int j=0; j<nLepCand; ++j){
           if (mu_index<0 and LepCand_id[j]==13) mu_index=j;
        }
        int tau_index=-1; float dz_tmp=10000;
        for (int j=0; j<nLepCand; ++j){
           if (LepCand_id[j]==15 and fabs(LepCand_dz[j]-LepCand_dz[mu_index])<dz_tmp){
              tau_index=j;
              dz_tmp=fabs(LepCand_dz[j]-LepCand_dz[mu_index]);
           }
        }
        TLorentzVector my_tau; my_tau.SetPtEtaPhiM(LepCand_pt[tau_index],LepCand_eta[tau_index],LepCand_phi[tau_index],0);
        TLorentzVector my_tauTk1; my_tauTk1.SetPtEtaPhiM(LepCand_tk1Pt[tau_index],LepCand_tk1Eta[tau_index],LepCand_tk1Phi[tau_index],0);
        TLorentzVector my_tauTk2; my_tauTk2.SetPtEtaPhiM(LepCand_tk2Pt[tau_index],LepCand_tk2Eta[tau_index],LepCand_tk2Phi[tau_index],0);
        TLorentzVector my_tauTk3; my_tauTk3.SetPtEtaPhiM(LepCand_tk3Pt[tau_index],LepCand_tk3Eta[tau_index],LepCand_tk3Phi[tau_index],0);
        TLorentzVector my_mu; my_mu.SetPtEtaPhiM(LepCand_pt[mu_index],LepCand_eta[mu_index],LepCand_phi[mu_index],0);

	// Block tracks
	b7_1->GetEntry(i); b7_2->GetEntry(i); b7_3->GetEntry(i); b7_4->GetEntry(i); b7_5->GetEntry(i); b7_6->GetEntry(i);
	int ntracks=0;
	int ntracksPU=0;
	int ntracksHS=0;
	int ntracksAll=0;
        float bs_zsigma_obs=h_bs_sigma->GetRandom();
        float bs_z_obs=h_bs_z->GetRandom();
        float corr_zsig= (bs_zsigma_obs / bs_zsigma_mc);
        float corr_z= bs_z_obs - corr_zsig * bs_z_mc;
	for (int nt=0; nt<nTracks; ++nt){
                 float raw_dz=fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[mu_index]);
	 	 TLorentzVector mytrack;
                 mytrack.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
		 bool is_matchedToETau=false;
                 TLorentzVector my_track; my_track.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
		 if (fabs(Track_pt[nt]-LepCand_pt[mu_index])/LepCand_pt[mu_index]<0.1 and my_mu.DeltaR(my_track)<0.002) is_matchedToETau=true;
		 if (LepCand_tk1Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk1Pt[tau_index])/LepCand_tk1Pt[tau_index]<0.1 and my_tauTk1.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (LepCand_tk2Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk2Pt[tau_index])/LepCand_tk2Pt[tau_index]<0.1 and my_tauTk2.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (LepCand_tk3Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk3Pt[tau_index])/LepCand_tk3Pt[tau_index]<0.1 and my_tauTk3.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau){ ntracksAll++;}
                 if (sample!="data_obs"){
                    float z_corr = corr_z + corr_zsig * (PV_z+Track_dz[nt]);
                    float BScorrected_dz = fabs(z_corr - PV_z-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[mu_index]);

                    if (Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5  and !is_matchedToETau) ntracksHS++;
                    if (!Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and BScorrected_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau) ntracksPU++;
                 }
	}

	if (sample=="data_obs") ntracks=ntracksAll;
	else ntracks=ntracksPU+ntracksHS;
	if (fabs(LepCand_dz[tau_index]-LepCand_dz[mu_index])>0.2) {ntracks=199; ntracksPU=199; ntracksHS=199; ntracksAll=199;}

        ntracks_friend=ntracks;
        ntracksPU_friend=ntracksPU;
        ntracksHS_friend=ntracksHS;
        ntracksAll_friend=ntracksAll;

        tree_friend->Fill();
    } // end of loop over events
cout<<"All, HS0, HS0PU0, PU0: "<<nb_all<<" "<<nb_HS0<<" "<<nb_HS0_PU0<<" "<<nb_PU0<<endl;
cout<<"Fraction without track: "<<1.0*nb_HS0_PU0/nb_all<<endl;
cout<<"Fraction with HS track: "<<1.0*(nb_all-nb_HS0)/nb_all<<" "<<1.0*(nb_PU0-nb_HS0_PU0)/nb_PU0<<endl;

    f_friend->cd();
    tree_friend->Write();
    delete f_Double;
    delete f_friend;

} 


