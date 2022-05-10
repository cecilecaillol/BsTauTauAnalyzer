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
#include "TChain.h"
#include "TMath.h"
#include "tr_Tree.h"


using namespace std;

int main(int argc, char** argv) {

    std::string sample = *(argv + 1);
    std::string name = *(argv + 2);
    TChain *arbre = new TChain("Events");
    TChain *arbre2 = new TChain("Runs");
    arbre->Add("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/ntuple_mutau/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/ntuple_mutau/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIISummer20UL18NanoAODv9-106X_upgrade2018_realistic_v16_L1v1-v1_mutau/*.root");

    float ngen=0;
    if (name!="data_obs") {
       Int_t nentries_wtn2 = (Int_t) arbre2->GetEntries();
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
	 ngen+=genEventCount;
       }
    }


    float xs=1.0; float weight=1.0; float luminosity=59740.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}

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
    arbre->SetBranchAddress("PV_ndof", &PV_ndof);
    arbre->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);  
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso); 
    arbre->SetBranchAddress("LepCand_charge", &LepCand_charge);    
    arbre->SetBranchAddress("LepCand_muonMediumId",&LepCand_muonMediumId);
    TFile *fout = new TFile("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/test.root","recreate");
    TTree *tout = new TTree("DYTree","DYTree");
    double taupt, mupt, taueta, mueta, tauphi, muphi, taumumass,taumudelphi,Acopl, muiso, mumediumID, tauvsmu, tauvse, tauvsjet, mucharge, taucharge;
    tout->Branch("taupt",&taupt);
    tout->Branch("mupt",&mupt);
    tout->Branch("taueta",&taueta);
    tout->Branch("mueta",&mueta);
    tout->Branch("tauphi",&tauphi);
    tout->Branch("muphi",&muphi);
    tout->Branch("taumumass",&taumumass);
    tout->Branch("taumudelphi",&taumudelphi);
    tout->Branch("muiso",&muiso);
    tout->Branch("mumediumID",&mumediumID);
    tout->Branch("tauvsmu",&tauvsmu);
    tout->Branch("tauvse",&tauvse);
    tout->Branch("tauvsjet",&tauvsjet);
    tout->Branch("mucharge",&mucharge);
    tout->Branch("taucharge",&taucharge);
    tout->Branch("Acopl",&Acopl);
    tout->Branch("PV_ndof",&PV_ndof);

    //TH1F* h_taupt = new TH1F("h_taupt","h_taupt",20,0,200); h_taupt->Sumw2();

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        TLorentzVector my_tau, my_mu;  
          
        if (nLepCand>1 && LepCand_id[0]==15 && LepCand_id[1]==13){
            my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
            my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
            muiso = LepCand_muonIso[1];
            mumediumID = LepCand_muonMediumId[1];
            tauvsmu = LepCand_vsmu[0];
            tauvse = LepCand_vse[0];
            tauvsjet = LepCand_vse[0];
            taucharge = LepCand_charge[0];
            mucharge = LepCand_charge[1];            
        }

        else if (nLepCand>1 && LepCand_id[0]==13 && LepCand_id[1]==15){
            my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
            my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
            muiso = LepCand_muonIso[0];
            mumediumID = LepCand_muonMediumId[0];
            tauvsmu = LepCand_vsmu[1];
            tauvse = LepCand_vse[1];
            tauvsjet = LepCand_vse[1];
            taucharge = LepCand_charge[1];
            mucharge = LepCand_charge[0];  

        }

        else if (nLepCand>2 && LepCand_id[0]==15 && LepCand_id[1]==15 && LepCand_id[2]==13){
            my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
            my_mu.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0);
            muiso = LepCand_muonIso[2];
            mumediumID = LepCand_muonMediumId[2];
            tauvsmu = LepCand_vsmu[0];
            tauvse = LepCand_vse[0];
            tauvsjet = LepCand_vse[0];
            taucharge = LepCand_charge[0];
            mucharge = LepCand_charge[2];  
        }

        else continue;
        taupt = my_tau.Pt();
        mupt = my_mu.Pt();
        taueta = my_tau.Eta();
        mueta = my_mu.Eta();
        tauphi = my_tau.Phi();
        muphi = my_mu.Phi();

        if (!(tauvse>=7 && tauvsmu >=15 && tauvsjet>=31)) continue; //tau id selection: Medium vs jet, Tight vs muon, VLoose vs electron
        if (!(mumediumID==1 && muiso<0.15)) continue; //muid and isolation cut: medium vs muon and isolation<0.15
        if (mucharge==taucharge) continue; //oposite sign of mutau
        if (!(HLT_IsoMu24==1 && mupt>26)) continue; // trigger and mupt
        if (!(taueta<2.3 && mueta<2.4)) continue; // eta selection

/*       TLorentzVector my_tau;
        if (nLepCand>0 and LepCand_id[0]==15) my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==15) my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
        TLorentzVector my_mu;
        if (nLepCand>0 and LepCand_id[0]==13) my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==13) my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);*/

        //if (fabs(my_tau.Eta())>2.1) continue;
        cout << "haha" << endl;
        taumumass = (my_tau + my_mu).M();
        taumudelphi = my_tau.DeltaPhi(my_mu);
        Acopl = 1 - abs(taumudelphi)/TMath::Pi();
        //h_taupt->Fill(my_tau.Pt());
        tout->Fill();

    } // end of loop over events
    //TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    tout->Write();

    //TDirectory *dir0 =fout->mkdir("tau_pt");
    //dir0->cd();
    //h_taupt->SetName(name.c_str());
    //h_taupt->Write();

    fout->Close();
} 