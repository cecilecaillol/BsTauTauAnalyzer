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
    arbre->SetBranchAddress("LepCand_eleMVAiso80", &LepCand_eleMVAiso80);
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);
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
    arbre->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1);

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

   TFile* f_bs=new TFile("beamspot_TF1_2018.root","read");
   TF1* h_bs_width = (TF1*) f_bs->Get("f1");

   TF1* f_beamspotz=new TF1("f_beamspotz","gaus",-1.1,1.1);
   f_beamspotz->SetParameter(0,1);
   f_beamspotz->SetParameter(1,-0.138);
   f_beamspotz->SetParameter(2,0.254);

int nb_all=0;
int nb_HS0=0;
int nb_HS0_PU0=0;
int nb_PU0=0;

   for (Int_t i = 0; i < nentries_wtn; i++) {
	//arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

      if (input=="/eoaaaaas/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_etau_2018/EGammaA.root" and i>=464459 and i<475000){
        ntracks_friend=9999;
        ntracksPU_friend=9999;
        ntracksHS_friend=9999;
        ntracksAll_friend=9999;
      }
      else{
        b1_6->GetEntry(i); b1_1->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_2->GetEntry(i); b1_9->GetEntry(i); b1_10->GetEntry(i); b1_11->GetEntry(i);
	b1_12->GetEntry(i);b1_13->GetEntry(i);b1_14->GetEntry(i);b1_15->GetEntry(i);b1_16->GetEntry(i);b1_17->GetEntry(i);b1_18->GetEntry(i);b1_19->GetEntry(i);b1_20->GetEntry(i);b1_21->GetEntry(i);b1_22->GetEntry(i);
        if (sample!="data_obs") {b1_5->GetEntry(i); b1_7->GetEntry(i); b1_8->GetEntry(i);}

	/*TLorentzVector my_tau;
	int tau_index=0;
	if (nLepCand>0 and LepCand_id[0]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); tau_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); tau_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); tau_index=2;}
        TLorentzVector my_ele;
	int ele_index=0;
        if (nLepCand>0 and LepCand_id[0]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); ele_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); ele_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); ele_index=2;}*/

        int ele_index=-1;
        for (int j=0; j<nLepCand; ++j){
           if (ele_index<0 and LepCand_id[j]==11) ele_index=j;
        }
        int tau_index=-1; float dz_tmp=10000;
        for (int j=0; j<nLepCand; ++j){
           if (LepCand_id[j]==15 and fabs(LepCand_dz[j]-LepCand_dz[ele_index])<dz_tmp){
              tau_index=j;
              dz_tmp=fabs(LepCand_dz[j]-LepCand_dz[ele_index]);
           }
        }
        TLorentzVector my_tau; my_tau.SetPtEtaPhiM(LepCand_pt[tau_index],LepCand_eta[tau_index],LepCand_phi[tau_index],0);
        TLorentzVector my_tauTk1; my_tauTk1.SetPtEtaPhiM(LepCand_tk1Pt[tau_index],LepCand_tk1Eta[tau_index],LepCand_tk1Phi[tau_index],0);
        TLorentzVector my_tauTk2; my_tauTk2.SetPtEtaPhiM(LepCand_tk2Pt[tau_index],LepCand_tk2Eta[tau_index],LepCand_tk2Phi[tau_index],0);
        TLorentzVector my_tauTk3; my_tauTk3.SetPtEtaPhiM(LepCand_tk3Pt[tau_index],LepCand_tk3Eta[tau_index],LepCand_tk3Phi[tau_index],0);
        TLorentzVector my_ele; my_ele.SetPtEtaPhiM(LepCand_pt[ele_index],LepCand_eta[ele_index],LepCand_phi[ele_index],0);

	// Block tracks
	b7_1->GetEntry(i); b7_2->GetEntry(i); b7_3->GetEntry(i); b7_4->GetEntry(i); b7_5->GetEntry(i); b7_6->GetEntry(i);
	int ntracks=0;
	int ntracksPU=0;
	int ntracksHS=0;
	int ntracksAll=0;
        float rnd_beamspot=h_bs_width->GetRandom();
        float rnd_beamspotz=f_beamspotz->GetRandom();
        //cout<<"ele pt, eta, phi, dz: "<<LepCand_pt[ele_index]<<", "<<LepCand_eta[ele_index]<<", "<<LepCand_phi[ele_index]<<", "<<LepCand_dz[ele_index]<<endl;
        //cout<<"tau pt, eta, phi, dz: "<<LepCand_pt[tau_index]<<", "<<LepCand_eta[tau_index]<<", "<<LepCand_phi[tau_index]<<", "<<LepCand_dz[tau_index]<<endl;
        //cout<<"tau track1 pt, eta, phi, dz: "<<LepCand_tk1Pt[tau_index]<<", "<<LepCand_tk1Eta[tau_index]<<", "<<LepCand_tk1Phi[tau_index]<<", "<<LepCand_dz[tau_index]<<endl;
        //cout<<"tau track2 pt, eta, phi, dz: "<<LepCand_tk2Pt[tau_index]<<", "<<LepCand_tk2Eta[tau_index]<<", "<<LepCand_tk2Phi[tau_index]<<", "<<LepCand_dz2[tau_index]<<endl;
        //cout<<"tau track3 pt, eta, phi, dz: "<<LepCand_tk3Pt[tau_index]<<", "<<LepCand_tk3Eta[tau_index]<<", "<<LepCand_tk3Phi[tau_index]<<", "<<LepCand_dz3[tau_index]<<endl;
	for (int nt=0; nt<nTracks; ++nt){
//cout<<"track pt, eta, phi, dz: "<<Track_pt[nt]<<", "<<Track_eta[nt]<<", "<<Track_phi[nt]<<", "<<Track_dz[nt]<<endl;
                 float raw_dz=fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index]);
	 	 TLorentzVector mytrack;
                 mytrack.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
		 bool is_matchedToETau=false;
                 TLorentzVector my_track; my_track.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
		 if (fabs(Track_pt[nt]-LepCand_pt[ele_index])/LepCand_pt[ele_index]<0.1 and my_ele.DeltaR(my_track)<0.002) is_matchedToETau=true;
		 if (LepCand_tk1Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk1Pt[tau_index])/LepCand_tk1Pt[tau_index]<0.1 and my_tauTk1.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (LepCand_tk2Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk2Pt[tau_index])/LepCand_tk2Pt[tau_index]<0.1 and my_tauTk2.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (LepCand_tk3Pt[tau_index]>0 and fabs(Track_pt[nt]-LepCand_tk3Pt[tau_index])/LepCand_tk3Pt[tau_index]<0.1 and my_tauTk3.DeltaR(my_track)<0.002) is_matchedToETau=true;
                 if (Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau){ ntracksAll++;}
                 if (sample!="data_obs"){
                    float BScorrected_dz=fabs(((PV_z+Track_dz[nt])*rnd_beamspot/3.5 + (rnd_beamspotz-0.02488))-PV_z-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index]);
		    //cout<<raw_dz<<" "<<BScorrected_dz<<" "<<rnd_beamspot<<" "<<rnd_beamspotz<<endl;
                    //float BScorrected_dz=raw_dz;//FIXME
                    if (Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5  and !is_matchedToETau) ntracksHS++;
                    if (!Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and BScorrected_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau) ntracksPU++;
                 }


	}
//cout<<ntracksHS+ntracksPU<<" "<<ntracksHS<<" "<<ntracksPU<<endl;

/*nb_all++;
if (ntracksHS==0) nb_HS0++;
if (ntracksHS==0 and ntracksPU==0) nb_HS0_PU0++;
if (ntracksPU==0) nb_PU0++;

///////////////////////////////////////////////////
if (ntracksHS>0){
        cout<<"ele pt, eta, phi, dz: "<<LepCand_pt[ele_index]<<", "<<LepCand_eta[ele_index]<<", "<<LepCand_phi[ele_index]<<", "<<LepCand_dz[ele_index]<<endl;
        cout<<"tau pt, eta, phi, dz: "<<LepCand_pt[tau_index]<<", "<<LepCand_eta[tau_index]<<", "<<LepCand_phi[tau_index]<<", "<<LepCand_dz[tau_index]<<endl;
        cout<<"tau DM: "<<LepCand_DecayMode[tau_index]<<endl;
        cout<<"tau track1 pt, eta, phi, dz: "<<LepCand_tk1Pt[tau_index]<<", "<<LepCand_tk1Eta[tau_index]<<", "<<LepCand_tk1Phi[tau_index]<<", "<<LepCand_dz[tau_index]<<endl;
        cout<<"tau track2 pt, eta, phi, dz: "<<LepCand_tk2Pt[tau_index]<<", "<<LepCand_tk2Eta[tau_index]<<", "<<LepCand_tk2Phi[tau_index]<<", "<<LepCand_dz2[tau_index]<<endl;
        cout<<"tau track3 pt, eta, phi, dz: "<<LepCand_tk3Pt[tau_index]<<", "<<LepCand_tk3Eta[tau_index]<<", "<<LepCand_tk3Phi[tau_index]<<", "<<LepCand_dz3[tau_index]<<endl;
        for (int nt=0; nt<nTracks; ++nt){
                 float raw_dz=fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index]);
                 TLorentzVector mytrack;
                 mytrack.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
//cout<<"track pt, eta, phi, dz: "<<Track_pt[nt]<<", "<<Track_eta[nt]<<", "<<Track_phi[nt]<<", "<<Track_dz[nt]<<endl;
                 bool is_matchedToETau=false;
                 TLorentzVector my_track; my_track.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
                 if (fabs(Track_dz[nt]-LepCand_dz[ele_index])<0.05 and fabs(Track_pt[nt]-LepCand_pt[ele_index])/LepCand_pt[ele_index]<0.1 and my_ele.DeltaR(my_track)<0.001) is_matchedToETau=true;
                 if (LepCand_tk1Pt[tau_index]>0 and fabs(Track_dz[nt]-LepCand_dz[tau_index])<0.05 and fabs(Track_pt[nt]-LepCand_tk1Pt[tau_index])/LepCand_tk1Pt[tau_index]<0.1 and my_tauTk1.DeltaR(my_track)<0.001) is_matchedToETau=true;
                 if (LepCand_tk2Pt[tau_index]>0 and fabs(Track_dz[nt]-LepCand_dz2[tau_index])<0.05 and fabs(Track_pt[nt]-LepCand_tk2Pt[tau_index])/LepCand_tk2Pt[tau_index]<0.1 and my_tauTk2.DeltaR(my_track)<0.001) is_matchedToETau=true;
                 if (LepCand_tk3Pt[tau_index]>0 and fabs(Track_dz[nt]-LepCand_dz3[tau_index])<0.05 and fabs(Track_pt[nt]-LepCand_tk3Pt[tau_index])/LepCand_tk3Pt[tau_index]<0.1 and my_tauTk3.DeltaR(my_track)<0.001) is_matchedToETau=true;
                 if (Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau){ ntracksAll++;}
                 if (sample!="data_obs"){
                    float BScorrected_dz=fabs(((PV_z+Track_dz[nt])*rnd_beamspot/3.5 + (rnd_beamspotz-0.02488))-PV_z-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index]);
                    if (Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and raw_dz<0.05 and fabs(Track_eta[nt])<2.5  and !is_matchedToETau) cout<<"track HS pt, eta, phi, dz: "<<Track_pt[nt]<<", "<<Track_eta[nt]<<", "<<Track_phi[nt]<<", "<<Track_dz[nt]<<endl;
                    if (!Track_isMatchedToHS[nt] and Track_pt[nt]>0.5 and BScorrected_dz<0.05 and fabs(Track_eta[nt])<2.5 and !is_matchedToETau) cout<<"track PU pt, eta, phi, dz: "<<Track_pt[nt]<<", "<<Track_eta[nt]<<", "<<Track_phi[nt]<<", "<<Track_dz[nt]<<endl;
                 }


        }
cout<<endl;
}*/
//////////////////////////////////////////////////////

//if (i>460000) cout<<"test4"<<endl;
	/*ntracksAll-=1; // for the electron
	if (ntracksHS>0) ntracksHS-=1;
	else if (ntracksPU>0) ntracksPU-=1;
	int tautracks=1;
	if (LepCand_DecayMode[tau_index]>=10){ 
	   for (int nt=0; nt<nTracks; ++nt){
              if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.05 and fabs(Track_eta[nt])<2.5){
		 TLorentzVector mytrack;
		 mytrack.SetPtEtaPhiM(Track_pt[nt],Track_eta[nt],Track_phi[nt],0);
	         if (my_tau.DeltaR(mytrack)<0.2)  tautracks++;
	      }
           }
	}
	if (tautracks>3) tautracks=3;
        ntracksAll-=tautracks;
	ntracksHS-=tautracks;
	if (ntracksAll<0) ntracksAll=0;*/
	if (sample=="data_obs") ntracks=ntracksAll;
	else ntracks=ntracksPU+ntracksHS;
        //if (ntracks<0) ntracks=0;
        //if (ntracksHS<0) ntracksHS=0;
	if (fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index])>0.2) {ntracks=199; ntracksPU=199; ntracksHS=199; ntracksAll=199;}

        /*if(LepCand_DecayMode[tau_index]>=-10 and fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index])<0.2){
           cout<<"Ntracks = "<<ntracks<<endl;
           cout<<"Electron: "<<LepCand_pt[ele_index]<<" "<<LepCand_eta[ele_index]<<" "<<LepCand_phi[ele_index]<<" "<<LepCand_dz[ele_index]<<endl;
           cout<<"Tau: "<<LepCand_pt[tau_index]<<" "<<LepCand_eta[tau_index]<<" "<<LepCand_phi[tau_index]<<" "<<LepCand_dz[tau_index]<<" "<<LepCand_DecayMode[tau_index]<<endl;
           for (int nt=0; nt<nTracks; ++nt){
              if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.05 and fabs(Track_eta[nt])<2.5) cout<<Track_pt[nt]<<" "<<Track_eta[nt]<<" "<<Track_phi[nt]<<" "<<Track_dz[nt]<<endl;
           }
           cout<<endl;
        }*/

	/*if (ntracks==0 and fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index])<0.1){
	   cout<<"Ntracks = "<<ntracks<<endl;
           cout<<"Electron: "<<LepCand_pt[ele_index]<<" "<<LepCand_eta[ele_index]<<" "<<LepCand_phi[ele_index]<<" "<<LepCand_dz[ele_index]<<endl;
           cout<<"Tau: "<<LepCand_pt[tau_index]<<" "<<LepCand_eta[tau_index]<<" "<<LepCand_phi[tau_index]<<" "<<LepCand_dz[tau_index]<<" "<<LepCand_DecayMode[tau_index]<<endl;
           for (int nt=0; nt<nTracks; ++nt){
              if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.05 and fabs(Track_eta[nt])<2.5) cout<<Track_pt[nt]<<" "<<Track_eta[nt]<<" "<<Track_phi[nt]<<" "<<Track_dz[nt]<<endl;
           }
	   cout<<endl;
	}*/
//if (i>460000) cout<<"test5"<<endl;
        ntracks_friend=ntracks;
        ntracksPU_friend=ntracksPU;
        ntracksHS_friend=ntracksHS;
        ntracksAll_friend=ntracksAll;
      }
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


