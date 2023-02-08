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

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);
    std::string sample = *(argv + 3);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("Events");

    TFile *f_friend = new TFile(output.c_str(),"recreate");
    TTree *tree_friend = new TTree("friend_tree","friend_tree");
    int ntracks_friend;
    TBranch *bntracks_friend=tree_friend->Branch("ntracks_friend",&ntracks_friend,"ntracks_friend/I");
    int ntracksHS_friend;
    TBranch *bntracksHS_friend=tree_friend->Branch("ntracksHS_friend",&ntracksHS_friend,"ntracksHS_friend/I");
    int ntracksPU_friend;
    TBranch *bntracksPU_friend=tree_friend->Branch("ntracksPU_friend",&ntracksPU_friend,"ntracksPU_friend/I");


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
    arbre->SetBranchAddress("LepCand_eleMVAiso80", &LepCand_eleMVAiso80);
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso);
    arbre->SetBranchAddress("LepCand_muonMediumId", &LepCand_muonMediumId);

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
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");
   auto b1_7=arbre->GetBranch("PV_z");
   auto b1_10=arbre->GetBranch("LepCand_dz");

   auto b7_1=arbre->GetBranch("nTracks");
   auto b7_2=arbre->GetBranch("Track_dz");
   auto b7_3=arbre->GetBranch("Track_eta");
   auto b7_4=arbre->GetBranch("Track_phi");
   auto b7_5=arbre->GetBranch("Track_pt");
   auto b7_6=arbre->GetBranch("Track_isMatchedToHS");


   TF1* f_beamspot=new TF1("f_beamspot","gaus",2.5,4.5);
   f_beamspot->SetParameter(0,1);
   f_beamspot->SetParameter(1,3.35);
   f_beamspot->SetParameter(2,0.15);

   TF1* f_beamspotz=new TF1("f_beamspotz","gaus",-10,10);
   f_beamspotz->SetParameter(0,1);
   f_beamspotz->SetParameter(1,-0.138);
   f_beamspotz->SetParameter(2,0.254);


   for (Int_t i = 0; i < nentries_wtn; i++) {
	//arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        b1_1->GetEntry(i); b1_2->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_6->GetEntry(i); b1_7->GetEntry(i); b1_10->GetEntry(i);
        if (sample!="data_obs") {b1_5->GetEntry(i);}

	TLorentzVector my_mu;
	int mu_index=0;
	if (nLepCand>0 and LepCand_id[0]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); mu_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); mu_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); mu_index=2;}
        TLorentzVector my_ele;
	int ele_index=0;
        if (nLepCand>0 and LepCand_id[0]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); ele_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); ele_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); ele_index=2;}

	// Block tracks
	b7_1->GetEntry(i); b7_2->GetEntry(i); b7_3->GetEntry(i); b7_4->GetEntry(i); b7_5->GetEntry(i);
	if (sample!="data_obs") b7_6->GetEntry(i);
	int ntracks=0;
        int ntracksPU=0;
        int ntracksHS=0;
        float rnd_beamspot=f_beamspot->GetRandom();
        float rnd_beamspotz=f_beamspotz->GetRandom();
	int matched=0;
	//cout<<"ele pt, eta, phi, dz: "<<LepCand_pt[ele_index]<<", "<<LepCand_eta[ele_index]<<", "<<LepCand_phi[ele_index]<<", "<<LepCand_dz[ele_index]<<endl;
        //cout<<"mu pt, eta, phi, dz: "<<LepCand_pt[mu_index]<<", "<<LepCand_eta[mu_index]<<", "<<LepCand_phi[mu_index]<<", "<<LepCand_dz[mu_index]<<endl;
	for (int nt=0; nt<nTracks; ++nt){
	   float is_matched=false;
	   TLorentzVector my_track; my_track.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
	   //cout<<"track pt, eta, phi, dz: "<<Track_pt[nt]<<", "<<Track_eta[nt]<<", "<<Track_phi[nt]<<", "<<Track_dz[nt]<<endl;
	   if (fabs(Track_dz[nt]-LepCand_dz[mu_index])<0.1 and fabs(Track_pt[nt]-LepCand_pt[mu_index])/LepCand_pt[mu_index]<0.2 and my_mu.DeltaR(my_track)<0.1) {is_matched=true; matched++;}
           if (fabs(Track_dz[nt]-LepCand_dz[ele_index])<0.1 and fabs(Track_pt[nt]-LepCand_pt[ele_index])/LepCand_pt[ele_index]<0.2 and my_ele.DeltaR(my_track)<0.1) {is_matched=true; matched++;}
	   if (!is_matched){
	      float raw_dz=fabs(Track_dz[nt]-0.5*LepCand_dz[mu_index]-0.5*LepCand_dz[ele_index]);
	      if (Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5) ntracks++;
	      if (sample!="data_obs"){
                 float BScorrected_dz=fabs(((PV_z+Track_dz[nt])*rnd_beamspot/3.5 + (rnd_beamspotz-0.02488))-PV_z-0.5*LepCand_dz[mu_index]-0.5*LepCand_dz[ele_index]);
                 if (Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5) ntracksHS++;
                 if (!Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and BScorrected_dz<0.05 and fabs(Track_eta[nt])<2.5) ntracksPU++;
	      }
	   }
	}
	//cout<<matched<<endl;
	//ntracks-=2;
	//if (ntracks<0) ntracks=0;

	/*if (ntracks==1){
	   cout<<"Ntracks = "<<ntracks<<endl;
           cout<<"Electron: "<<LepCand_pt[ele_index]<<" "<<LepCand_eta[ele_index]<<" "<<LepCand_phi[ele_index]<<" "<<LepCand_dz[ele_index]<<endl;
           cout<<"Tau: "<<LepCand_pt[tau_index]<<" "<<LepCand_eta[tau_index]<<" "<<LepCand_phi[tau_index]<<" "<<LepCand_dz[tau_index]<<endl;
           for (int nt=0; nt<nTracks; ++nt){
              if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.05 and fabs(Track_eta[nt])<2.5) cout<<Track_pt[nt]<<" "<<Track_eta[nt]<<" "<<Track_phi[nt]<<" "<<Track_dz[nt]<<endl;
           }
	   cout<<endl;
	}*/

        ntracks_friend=ntracks;
        ntracksHS_friend=ntracksHS;
        ntracksPU_friend=ntracksPU;
        tree_friend->Fill();
    } // end of loop over events
    f_friend->cd();
    tree_friend->Write();
    delete f_Double;
    delete f_friend;

} 


