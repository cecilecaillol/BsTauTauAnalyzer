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

    int is_control=0;

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
    float ngenu=0;
    if (name!="data_obs") {
       Int_t nentries_wtn2 = (Int_t) arbre2->GetEntries();
       arbre2->SetBranchAddress("genEventSumw", &genEventSumw);
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
         ngen+=genEventSumw;
	 ngenu+=genEventCount;
       }
    }
    cout<<"weighted events: "<<ngen<<endl;
    cout<<"unweighted events: "<<ngenu<<endl;

    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (year=="2024") luminosity = 108960.0;
    // AN2025_031
    if (sample=="DYto2E" or sample=="DYto2Mu" or sample=="DYto2Tau"){ xs=6345.99/3; weight=luminosity*xs/ngen;}
    else if (sample=="TTto2L2Nu"){ xs=923.6*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTtoLNu2Q"){ xs=923.6*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TWminusto2L2Nu" or sample=="TbarWplusto2L2Nu"){ xs=43.95*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TWminustoLNu2Q" or sample=="TbarWplustoLNu2Q"){ xs=43.95*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="WtoENu" or sample=="WtoMuNu" or sample=="WtoTauNu"){ xs=64481.58/3; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7*1.06; weight=luminosity*xs/ngen;}//1.06 for 13->13.6 scaling
    else if (sample=="WZ"){ xs=47.13*1.06; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ"){ xs=12.4*1.06; weight=luminosity*xs/ngen;}
    else if (sample=="WWW"){ xs=0.23280; weight=luminosity*xs/ngen;}
    else if (sample=="WWZ"){ xs=0.18510; weight=luminosity*xs/ngen;}
    else if (sample=="WZZ"){ xs=0.06206; weight=luminosity*xs/ngen;}
    else if (sample=="ZZZ"){ xs=0.01591; weight=luminosity*xs/ngen;}
    else if (sample=="TTWW"){ xs=0.0081651; weight=luminosity*xs/ngen;}
    else if (sample=="TTZZ"){ xs=0.0015617; weight=luminosity*xs/ngen;}
    else if (sample=="TTW"){ xs=0.2502; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("luminosityBlock", &luminosityBlock);
    arbre->SetBranchAddress("event", &event);
    arbre->SetBranchAddress("genWeight", &genWeight);
    arbre->SetBranchAddress("PuppiMET_phi", &PuppiMET_phi);
    arbre->SetBranchAddress("PuppiMET_phiUnclusteredDown", &PuppiMET_phiUnclusteredDown);
    arbre->SetBranchAddress("PuppiMET_phiUnclusteredUp", &PuppiMET_phiUnclusteredUp);
    arbre->SetBranchAddress("PuppiMET_pt", &PuppiMET_pt);
    arbre->SetBranchAddress("PuppiMET_ptUnclusteredDown", &PuppiMET_ptUnclusteredDown);
    arbre->SetBranchAddress("PuppiMET_ptUnclusteredUp", &PuppiMET_ptUnclusteredUp);
    arbre->SetBranchAddress("HLT_Ele30_WPTight_Gsf", &HLT_Ele30_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
    arbre->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
    arbre->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
    arbre->SetBranchAddress("e1_pt", &e1_pt);
    arbre->SetBranchAddress("e1_eta", &e1_eta);
    arbre->SetBranchAddress("e1_phi", &e1_phi);
    arbre->SetBranchAddress("e1_dxy", &e1_dxy);
    arbre->SetBranchAddress("e1_dz", &e1_dz);
    arbre->SetBranchAddress("e1_charge", &e1_charge);
    arbre->SetBranchAddress("e1_ID_sf", &e1_ID_sf);
    arbre->SetBranchAddress("e1_reco_sf", &e1_reco_sf);
    arbre->SetBranchAddress("e2_pt", &e2_pt);
    arbre->SetBranchAddress("e2_eta", &e2_eta);
    arbre->SetBranchAddress("e2_phi", &e2_phi);
    arbre->SetBranchAddress("e2_dxy", &e2_dxy);
    arbre->SetBranchAddress("e2_dz", &e2_dz);
    arbre->SetBranchAddress("e2_charge", &e2_charge);
    arbre->SetBranchAddress("e2_ID_sf", &e2_ID_sf);
    arbre->SetBranchAddress("e2_reco_sf", &e2_reco_sf);
    arbre->SetBranchAddress("e1_singletrg", &e1_singletrg);
    arbre->SetBranchAddress("e1_crosstrg", &e1_crosstrg);
    arbre->SetBranchAddress("e1_doubletrg", &e1_doubletrg);
    arbre->SetBranchAddress("e2_singletrg", &e2_singletrg);
    arbre->SetBranchAddress("e2_crosstrg", &e2_crosstrg);
    arbre->SetBranchAddress("e2_doubletrg", &e2_doubletrg);
    arbre->SetBranchAddress("pass_jvm", &pass_jvm);
    arbre->SetBranchAddress("nj", &nj);
    arbre->SetBranchAddress("j_pt", &j_pt);
    arbre->SetBranchAddress("j_eta", &j_eta);
    arbre->SetBranchAddress("j_phi", &j_phi);
    arbre->SetBranchAddress("j_m", &j_m);
    arbre->SetBranchAddress("j_puid", &j_puid);
    arbre->SetBranchAddress("j_deepflavB", &j_deepflavB);
    arbre->SetBranchAddress("j_upartB", &j_upartB);
    arbre->SetBranchAddress("j_upartB_sfL", &j_upartB_sfL);
    arbre->SetBranchAddress("j_upartB_sfM", &j_upartB_sfM);
    arbre->SetBranchAddress("j_upartB_sfT", &j_upartB_sfT);
    arbre->SetBranchAddress("j_upartB_sfXT", &j_upartB_sfXT);
    arbre->SetBranchAddress("j_upartB_sfXXT", &j_upartB_sfXXT);
    arbre->SetBranchAddress("j_hadronFlavour", &j_hadronFlavour);
    arbre->SetBranchAddress("ntau", &ntau);
    arbre->SetBranchAddress("tau_pt", &tau_pt);
    arbre->SetBranchAddress("tau_eta", &tau_eta);
    arbre->SetBranchAddress("tau_phi", &tau_phi);
    arbre->SetBranchAddress("tau_charge", &tau_charge);
    arbre->SetBranchAddress("nGenCand", &nGenCand);
    arbre->SetBranchAddress("GenCand_id", &GenCand_id);
    arbre->SetBranchAddress("GenCand_pt", &GenCand_pt);
    arbre->SetBranchAddress("GenCand_eta", &GenCand_eta);
    arbre->SetBranchAddress("GenCand_phi", &GenCand_phi);
    arbre->SetBranchAddress("GenCand_isBsTauTau", &GenCand_isBsTauTau);

   int nbhist=1;

   std::vector<TH1F*> h0;
   std::vector<TH1F*> h1;
   std::vector<TH1F*> h2;
   std::vector<TH1F*> h3;
   std::vector<TH1F*> h4;
   std::vector<TH1F*> h5;
   std::vector<TH1F*> h6;
   std::vector<TH1F*> h7;
   std::vector<TH1F*> h8;

   float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300};//mvis
   float bins1[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};//e pt
   float bins2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};//mu pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//mu eta
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};//mt1
   float bins7[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200};//mt2
   float bins8[] = {0,1,2,3,4,5,6,7,8,9,10};//nj

   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   int  binnum2 = sizeof(bins2)/sizeof(Float_t) - 1;
   int  binnum3 = sizeof(bins3)/sizeof(Float_t) - 1;
   int  binnum4 = sizeof(bins4)/sizeof(Float_t) - 1;
   int  binnum5 = sizeof(bins5)/sizeof(Float_t) - 1;
   int  binnum6 = sizeof(bins6)/sizeof(Float_t) - 1;
   int  binnum7 = sizeof(bins7)/sizeof(Float_t) - 1;
   int  binnum8 = sizeof(bins8)/sizeof(Float_t) - 1;
   for (int k=0; k<nbhist; ++k){
        ostringstream HN0; HN0 << "h0" << k;
        h0.push_back(new TH1F (HN0.str().c_str(),"InvMa",binnum0,bins0)); h0[k]->Sumw2();
        ostringstream HN1; HN1 << "h1" << k;
        h1.push_back(new TH1F (HN1.str().c_str(),"InvMa",binnum1,bins1)); h1[k]->Sumw2();
        ostringstream HN2; HN2 << "h2" << k;
        h2.push_back(new TH1F (HN2.str().c_str(),"InvMa",binnum2,bins2)); h2[k]->Sumw2();
        ostringstream HN3; HN3 << "h3" << k;
        h3.push_back(new TH1F (HN3.str().c_str(),"InvMa",binnum3,bins3)); h3[k]->Sumw2();
        ostringstream HN4; HN4 << "h4" << k;
        h4.push_back(new TH1F (HN4.str().c_str(),"InvMa",binnum4,bins4)); h4[k]->Sumw2();
        ostringstream HN5; HN5 << "h5" << k;
        h5.push_back(new TH1F (HN5.str().c_str(),"InvMa",binnum5,bins5)); h5[k]->Sumw2();
        ostringstream HN6; HN6 << "h6" << k;
        h6.push_back(new TH1F (HN6.str().c_str(),"InvMa",binnum6,bins6)); h6[k]->Sumw2();
        ostringstream HN7; HN7 << "h7" << k;
        h7.push_back(new TH1F (HN7.str().c_str(),"InvMa",binnum7,bins7)); h7[k]->Sumw2();
        ostringstream HN8; HN8 << "h8" << k;
        h8.push_back(new TH1F (HN8.str().c_str(),"InvMa",binnum8,bins8)); h8[k]->Sumw2();

   }

   TString uncertainties[1]={""};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	TLorentzVector my_e1; my_e1.SetPtEtaPhiM(e1_pt,e1_eta,e1_phi,0.105);
        TLorentzVector my_e2; my_e2.SetPtEtaPhiM(e2_pt,e2_eta,e2_phi,0.105);

	if (fabs(my_e1.Eta())>2.5) continue;
        if (fabs(my_e2.Eta())>2.5) continue;
	if (e1_pt<25 and e2_pt<25) continue;
        if (e1_pt<20 or e2_pt<20) continue;
	if (my_e1.DeltaR(my_e2)<0.5) continue; //FIXME Federica doesnt cut on DR?
	if (!pass_jvm) continue;

	// Trigger block
	bool is_singleele=(HLT_Ele30_WPTight_Gsf and (e1_singletrg or e2_singletrg));
	bool is_doubleele=(HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL and e1_doubletrg and e2_doubletrg);
	if (!is_singleele and !is_doubleele) continue;

	// Block ID/iso/charge
	bool is_OS = (e2_charge*e1_charge<0);

        // Block weights

	float top_genpt=0.0;
        float antitop_genpt=0.0;
	if (sample=="TTto2L2Nu" or sample=="TTtoLNu2Q"){
	   for (int l=0; l<nGenCand; ++l){
	      if (top_genpt<1 and GenCand_id[l]==6) top_genpt=GenCand_pt[l];
              if (antitop_genpt<1 and GenCand_id[l]==-6) antitop_genpt=GenCand_pt[l];
	   }
	}

	float aweight=1.0;
	if (name!="data_obs"){
	   aweight=aweight*genWeight*e1_ID_sf*e1_reco_sf*e2_ID_sf*e2_reco_sf; 
           if (sample=="TTto2L2Nu" or sample=="TTtoLNu2Q") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*top_genpt)*TMath::Exp(0.0615-0.0005*antitop_genpt)),0.5); aweight*=toppt_reweighting; } //top pt reweighting
	}

	// Block MET
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(PuppiMET_pt,0,PuppiMET_phi,0);

	// Block b jets
        int nb=0;
        for (int l=0; l<nj; ++l){
	   if (j_pt[l]>20 and fabs(j_eta[l])<2.5 and j_upartB[l]>0.0246){
	       aweight=aweight*j_upartB_sfL[l]; //FIXME fix btag weight application
	       nb++; //L: 0.0246, M: 0.1272, T: 0.4648 
	   }
	}
	if (nb<2) continue;
	if (my_met.Pt()<20) continue;
	float mt1=TMass_F(my_e1.Pt(), my_e1.Px(), my_e1.Py(), my_met.Pt(), my_met.Phi());
	float mt2=TMass_F(my_e2.Pt(), my_e2.Px(), my_e2.Py(), my_met.Pt(), my_met.Phi());
	if (mt1<50 or mt2<50) continue;

	TLorentzVector save_e1=my_e1;
        TLorentzVector save_e2=my_e2;
        TLorentzVector save_met=my_met;

        for (int k=0; k<nbhist; ++k){
           my_e1=save_e1;
	   my_e2=save_e2;
	   my_met=save_met;
	   float weight2=1.0;

	   float mvis=(my_e2+my_e1).M();
	   if (mvis<20) continue;
	   bool is_inZwindow = (mvis>76.2 and mvis<106.2);

           bool is_cat0=true;
           bool is_cat1=!is_inZwindow;
           bool is_cat2=!is_inZwindow;
           bool is_cat3=!is_inZwindow;
           bool is_cat4=!is_inZwindow;
           bool is_cat5=!is_inZwindow;
           bool is_cat6=!is_inZwindow;
           bool is_cat7=!is_inZwindow;
           bool is_cat8=!is_inZwindow;

	   float var0 = mvis;
           float var1 = my_e1.Pt();
           float var2 = my_e2.Pt();
           float var3 = my_e1.Eta();
           float var4 = my_e2.Eta();
           float var5 = my_met.Pt();
           float var6 = mt1;
           float var7 = mt2;
           float var8 = nj;

	   if (is_OS){
	     if (is_cat0) h0[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) h1[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) h2[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3) h3[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) h4[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) h5[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6) h6[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7) h7[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) h8[k]->Fill(var8,weight*aweight*weight2);
	   }
	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    bool isMC=(name!="data_obs");
    WriteHistToFileEMu(fout, h0, name, "em_0", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h1, name, "em_1", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h2, name, "em_2", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h3, name, "em_3", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h4, name, "em_4", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h5, name, "em_5", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h6, name, "em_6", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h7, name, "em_7", uncertainties, isMC, nbhist);
    WriteHistToFileEMu(fout, h8, name, "em_8", uncertainties, isMC, nbhist);

    fout->Close();
} 


