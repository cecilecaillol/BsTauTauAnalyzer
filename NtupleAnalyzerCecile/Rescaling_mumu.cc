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
#include "rescaling_Tree.h"

using namespace std;
int main(int argc, char** argv) {
    std::string year = *(argv + 1);
    std::string input = *(argv + 2);
    std::string output = *(argv + 3);
    std::string sample = *(argv + 4);
    std::string name = *(argv + 5);

    TFile *f_Double = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *arbre = (TTree*) f_Double->Get("rescaling_tree");

    arbre->SetBranchAddress("mu1pt_", &mu1pt_);
    arbre->SetBranchAddress("mu1eta_", &mu1eta_);
    arbre->SetBranchAddress("mu1phi_", &mu1phi_);
    arbre->SetBranchAddress("mu2pt_", &mu2pt_);
    arbre->SetBranchAddress("mu2eta_", &mu2eta_);
    arbre->SetBranchAddress("mu2phi_", &mu2phi_);
    arbre->SetBranchAddress("acoplanarity_", &acoplanarity_);
    arbre->SetBranchAddress("aweight_", &aweight_);
    arbre->SetBranchAddress("weight_", &weight_);
    arbre->SetBranchAddress("npvs_weight_", &npvs_weight_);
    arbre->SetBranchAddress("ntpu_weight_", &ntpu_weight_);
    arbre->SetBranchAddress("nths_weight_", &nths_weight_);
    arbre->SetBranchAddress("aco_weight_", &aco_weight_);
    arbre->SetBranchAddress("os_", &os_);
    arbre->SetBranchAddress("ntracksAll_", &ntracksAll_);
    arbre->SetBranchAddress("sum_ntracks_", &sum_ntracks_);

    float binsm[] = {60,65,70,75,80,85,90,95,100,105,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,350,400,450,500,550,600};
    int  binnumm = sizeof(binsm)/sizeof(Float_t) - 1;
    TH1F* h_lownt=new TH1F("h_lownt","h_lownt",binnumm,binsm); h_lownt->Sumw2();
    TH1F* h_highnt=new TH1F("h_highnt","h_highnt",binnumm,binsm); h_highnt->Sumw2();

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	TLorentzVector my_mu1;
	my_mu1.SetPtEtaPhiM(mu1pt_,mu1eta_,mu1phi_,0.1);
        TLorentzVector my_mu2; 
        my_mu2.SetPtEtaPhiM(mu2pt_,mu2eta_,mu2phi_,0.1);
	float mvis=(my_mu1+my_mu2).M();

	//if (my_mu1.Pt()<30 or my_mu2.Pt()<30) continue;

	if (acoplanarity_<0.02 and os_ and ((name!="data_obs" and sum_ntracks_==0) or (name=="data_obs" and ntracksAll_==0))) h_lownt->Fill(mvis,weight_*aweight_*npvs_weight_*ntpu_weight_);
        if (acoplanarity_<0.02 and os_ and ((name!="data_obs" and sum_ntracks_>=5) or (name=="data_obs" and ntracksAll_>=5))) h_highnt->Fill(mvis,weight_*aweight_*npvs_weight_*ntpu_weight_);

    }
    TString postfixlow="_low";
    TString postfixhigh="_high";
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_lownt->SetName(name.c_str()+postfixlow);
    h_highnt->SetName(name.c_str()+postfixhigh);
    h_lownt->Write();
    h_highnt->Write();
    fout->Close();
}
