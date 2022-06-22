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

//this code is used to calculate fake rate using Same sign region
using namespace std;

int main(int argc, char** argv) {

   //std::string sample = *(argv + 1);
   // std::string name = *(argv + 2);

    //cout << "sample = " << sample << endl;
    //cout << "name = " << name << endl;
    TChain *arbre = new TChain("Events");
    TChain *arbre2 = new TChain("Runs");

    
    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018A-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018A-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018B-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018B-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018C-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018C-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018D-UL2018_MiniAODv2_NanoAODv9-v1_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018D-UL2018_MiniAODv2_NanoAODv9-v1_mutau/*.root");




    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);

    arbre->SetBranchAddress("MET_pt",&MET_pt);
    arbre->SetBranchAddress("MET_phi",&MET_phi);
    arbre->SetBranchAddress("nJets",&nJets);
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
    TFile *fout = new TFile("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/FRSSestimate.root","recreate");
    
    double FRedge[22];
    for (int i=0;i<=21;i++){
        if (i==21){
            FRedge[i]=1000;
        }
        else {
            FRedge[i]=30+i*8;
        }
    }
    TH1D *SS_M = new TH1D("SS_M","",21,FRedge);
    TH1D *SS_VVVL = new TH1D("SS_VVVL","",21,FRedge);  
    TH1D *FRSS= new TH1D("FRSS","",21,FRedge);     
    //TTree *tout = new TTree("Events","Events after basic selection");
    double taupt, mupt, taueta, mueta, tauphi, muphi, taumumass,taumudelphi,Acopl, muiso, mumediumID, tauvsmu, tauvse, tauvsjet, mucharge, taucharge, Mcol, xsweight, MT_muonMET;
    /*tout->Branch("taupt",&taupt);
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
    tout->Branch("MET_pt",&MET_pt);
    tout->Branch("nJets",&nJets);
    tout->Branch("Mcol",&Mcol);
    tout->Branch("MT_muonMET",&MT_muonMET);
*/
    //TH1F* h_taupt = new TH1F("h_taupt","h_taupt",20,0,200); h_taupt->Sumw2();

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        //fflush(stdout);

        TLorentzVector my_tau, my_mu;  
          
        if (nLepCand>1 && LepCand_id[0]==15 && LepCand_id[1]==13){
            my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
            my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
            muiso = LepCand_muonIso[1];
            mumediumID = LepCand_muonMediumId[1];
            tauvsmu = LepCand_vsmu[0];
            tauvse = LepCand_vse[0];
            tauvsjet = LepCand_vsjet[0];
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
            tauvsjet = LepCand_vsjet[1];
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
            tauvsjet = LepCand_vsjet[0];
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

        if (!(tauvse>=7 && tauvsmu >=15 )) continue; //tau id selection: Tight vs muon, VLoose vs electron
        if (!(mumediumID==1 && muiso<0.15)) continue; //muid and isolation cut: medium vs muon and isolation<0.15
        if (mucharge!=taucharge) continue; //same sign region considered
        if (!(HLT_IsoMu24==1 && mupt>26)) continue; // trigger and mupt
        if (!(abs(taueta)<2.3 && abs(mueta)<2.4)) continue; // eta selection

        if (tauvsjet>=1 && tauvsjet<31){//pass VVVLoose but fail Medium vs jet
            SS_VVVL->Fill(taupt);
        }
        else if (tauvsjet>=31){//pass Medium vs jet
            SS_M->Fill(taupt);
        }


/*       TLorentzVector my_tau;
        if (nLepCand>0 and LepCand_id[0]==15) my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==15) my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
        TLorentzVector my_mu;
        if (nLepCand>0 and LepCand_id[0]==13) my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==13) my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);*/

        //if (fabs(my_tau.Eta())>2.1) continue;
        //cout << "haha" << endl;
        /*taumumass = (my_tau + my_mu).M();
        taumudelphi = my_tau.DeltaPhi(my_mu);
        Acopl = 1 - abs(taumudelphi)/TMath::Pi();
        double metx = MET_pt * TMath::Cos(MET_phi);
        double mety = MET_pt * TMath::Sin(MET_phi);
        Mcol = GetCollMass(my_tau,my_mu,metx,mety);
        double muMETdelphi = my_mu.Phi()-MET_phi;
        MT_muonMET = TMath::Sqrt(2*mupt*MET_pt*(1-TMath::Cos(muMETdelphi)));
        xsweight=weight;
        //h_taupt->Fill(my_tau.Pt());
        tout->Fill();*/
    } // end of loop over events

    for (int i=1;i<=21;i++){
        double NVVVL_noM = SS_VVVL->GetBinContent(i);
        double NM = SS_M->GetBinContent(i);
        double FR = NM/NVVVL_noM;
        FRSS->SetBinContent(i,FR);
    }


    //TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    SS_M->Write();
    SS_VVVL->Write();
    FRSS->Write();
    //TDirectory *dir0 =fout->mkdir("tau_pt");
    //dir0->cd();
    //h_taupt->SetName(name.c_str());
    //h_taupt->Write();

    fout->Close();
} 