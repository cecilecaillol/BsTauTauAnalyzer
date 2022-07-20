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
// this code used to do basic selection on data samples (as no sf included)

Double_t GetCollMass(const TLorentzVector _lep1, const TLorentzVector _lep2, const Double_t _metx, const Double_t _mety)
{
  Double_t m_mz_coll=0;

  Double_t x1 = ((_lep1.Px()*_lep2.Py())-(_lep1.Py()*_lep2.Px())) / ((_lep1.Px()*_lep2.Py())-(_lep1.Py()*_lep2.Px())+(_lep2.Py()*_metx)-(_lep2.Px()*_mety));
  Double_t x2 = ((_lep1.Px()*_lep2.Py())-(_lep1.Py()*_lep2.Px())) / ((_lep1.Px()*_lep2.Py())-(_lep1.Py()*_lep2.Px())+(_lep1.Px()*_mety)-(_lep1.Py()*_metx));

  //cout << "x1 is " << x1 << " x2 is " << x2 << endl;

  if( (x1*x2) > 0. )
    m_mz_coll = ((_lep1+_lep2).M())/(sqrt(x1*x2));
  else m_mz_coll = 0;

  return m_mz_coll;
}

int main(int argc, char** argv) {

    std::string sample = *(argv + 1);
    std::string name = *(argv + 2);

    cout << "sample = " << sample << endl;
    cout << "name = " << name << endl;
    TChain *arbre = new TChain("Events");
    TChain *arbre2 = new TChain("Runs");
    if (sample=="data"){

    
    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018A-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018A-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018B-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018B-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018C-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018C-UL2018_MiniAODv2_NanoAODv9-v1_tautau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018D-UL2018_MiniAODv2_NanoAODv9-v2_tautau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/Tau_Run2018D-UL2018_MiniAODv2_NanoAODv9-v2_tautau/*.root");

    }

    else {
    arbre->Add(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/%s/*.root",name.c_str()));
    arbre2->Add(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/tautaunew/%s/*.root",name.c_str()));
    }

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
    if (sample == "DYJetsToLL_M-50") xs=6077.22; 
    else if (sample == "WJetsToLNu") xs=61526.7;
    else if (sample == "ST_t-channel_antitop_5f_InclusiveDecays") xs=80.95;
    else if (sample == "ST_t-channel_top_4f_InclusiveDecays") xs=136.02;
    else if (sample == "ST_tW_top_5f_inclusiveDecays") xs=35.85;
    else if (sample == "ST_tW_antitop_5f_inclusiveDecays") xs=35.85;
    else if (sample == "TTTo2L2Nu") xs=88.29;
    else if (sample == "TTToHadronic") xs=377.96;
    else if (sample == "TTToSemiLeptonic") xs=365.35;
    else if (sample == "WW") xs=75.8;
    else if (sample == "WZ") xs=27.6;
    else if (sample == "ZZTo2L2Nu") xs=0.6008;
    else if (sample == "ZZTo2Q2L_mllmin4p0") xs=3.38;
    else if (sample == "ZZTo4L") xs=1.26;
    else if (sample == "data" || sample == "dataA" || sample == "dataB" || sample == "dataC" || sample == "dataD") xs=1; //No use here
    else { 
        cout << "Wrong sample, please check" << endl;
        exit(1);
    }

    
    weight=luminosity*xs/ngen;

    cout << "luminosity = " <<  luminosity <<" xs = " << xs << " ngen = " << ngen << endl;
    cout << "calculate weight = luminosity*xs/ngen = " << weight << endl;

    if (sample == "data"|| sample == "dataA" || sample == "dataB" || sample == "dataC" || sample == "dataD") weight=1; //Set weight of data sample to 1

    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(10);


    arbre->SetBranchAddress("run",&run);
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
    arbre->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);  
    arbre->SetBranchAddress("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg);  
    arbre->SetBranchAddress("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg" ,&HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
    arbre->SetBranchAddress("HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg",&HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg);   
    arbre->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg",&HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg);      
    TFile *fout = new TFile(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/tautau/Sigregion/%s.root",sample.c_str()),"recreate");
    TTree *tout = (TTree*)arbre->CloneTree(0);
    double tau1pt, tau2pt, tau1eta, tau2eta, tau1phi, tau2phi, tautaumass,tautaudelphi,Acopl, tau1vsmu, tau1vse, tau1vsjet, tau2vsmu, tau2vse, tau2vsjet, tau1charge, tau2charge, Mcol, xsweight, tautaudelR;
    tout->Branch("tau1pt",&tau1pt);
    tout->Branch("tau2pt",&tau2pt);
    tout->Branch("tau1eta",&tau1eta);
    tout->Branch("tau2eta",&tau2eta);
    tout->Branch("tau1phi",&tau1phi);
    tout->Branch("tau2phi",&tau2phi);
    tout->Branch("tautaumass",&tautaumass);
    tout->Branch("tautaudelphi",&tautaudelphi);
    tout->Branch("tautaudelR",&tautaudelR);
    tout->Branch("tau1vsmu",&tau1vsmu);
    tout->Branch("tau1vse",&tau1vse);
    tout->Branch("tau1vsjet",&tau1vsjet);
    tout->Branch("tau2vsmu",&tau2vsmu);
    tout->Branch("tau2vse",&tau2vse);
    tout->Branch("tau2vsjet",&tau2vsjet);
    tout->Branch("tau1charge",&tau1charge);
    tout->Branch("tau2charge",&tau2charge);
    tout->Branch("Acopl",&Acopl);
    tout->Branch("PV_ndof",&PV_ndof);
    tout->Branch("MET_pt",&MET_pt);
    tout->Branch("nJets",&nJets);
    tout->Branch("Mcol",&Mcol);
    tout->Branch("xsweight",&xsweight);

    //TH1F* h_taupt = new TH1F("h_taupt","h_taupt",20,0,200); h_taupt->Sumw2();

    Int_t nentries_wtn = (Int_t) arbre->GetEntries();
    for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        //fflush(stdout);

        TLorentzVector my_tau1, my_tau2;  
        my_tau1.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        my_tau2.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);

        tau1vsmu = LepCand_vsmu[0];
        tau1vse = LepCand_vse[0];
        tau1vsjet = LepCand_vsjet[0];

        tau2vsmu = LepCand_vsmu[1];
        tau2vse = LepCand_vse[1];
        tau2vsjet = LepCand_vsjet[1];

        tau1charge = LepCand_charge[0];
        tau2charge = LepCand_charge[1]; 

        tau1pt = my_tau1.Pt();
        tau2pt = my_tau2.Pt();
        tau1eta = my_tau1.Eta();
        tau2eta = my_tau2.Eta();
        tau1phi = my_tau1.Phi();
        tau2phi = my_tau2.Phi();

        if (!(tau1vse>=15 && tau1vsmu >=3 && tau1vsjet>=31)) continue; //tau id selection: Medium vs jet, Loose vs muon, Loose vs electron
        if (!(tau2vse>=15 && tau2vsmu >=3 && tau2vsjet>=31)) continue; //tau id selection: Medium vs jet, Loose vs muon, Loose vs electron
        if (tau1charge==tau2charge) continue; //opposite sign of tautau
        if (!(abs(tau1eta)<2.1 && abs(tau2eta)<2.1)) continue; // eta selection
        if (!(tau1pt>40 && tau2pt>40)) continue; // pt selection
        if (run>= 317509){
            if (!HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg)
                continue;
        }
        else {
            if (!(HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg || HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg || HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg))
                continue;
        }
        //Trigger

/*       TLorentzVector my_tau;
        if (nLepCand>0 and LepCand_id[0]==15) my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==15) my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
        TLorentzVector my_mu;
        if (nLepCand>0 and LepCand_id[0]==13) my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==13) my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);*/

        //if (fabs(my_tau.Eta())>2.1) continue;
        //cout << "haha" << endl;
        tautaumass = (my_tau1 + my_tau2).M();
        tautaudelphi = my_tau1.DeltaPhi(my_tau2);
        tautaudelR = my_tau1.DeltaR(my_tau2);
        Acopl = 1 - abs(tautaudelphi)/TMath::Pi();
        double metx = MET_pt * TMath::Cos(MET_phi);
        double mety = MET_pt * TMath::Sin(MET_phi);
        Mcol = GetCollMass(my_tau1,my_tau2,metx,mety);
        //double muMETdelphi = my_mu.Phi()-MET_phi;
        //MT_muonMET = TMath::Sqrt(2*mupt*MET_pt*(1-TMath::Cos(muMETdelphi)));
        xsweight=weight;
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