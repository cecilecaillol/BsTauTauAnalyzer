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

//Read muon ID scale factor
    TFile *freco = new TFile("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/SFs/Efficiencies_muon_reco.root","READ");//RECO
    TFile *fID = new TFile("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","READ");//ID
    TFile *fiso = new TFile("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","READ");//ISO
    TFile *ftrigger = new TFile("/afs/cern.ch/user/x/xuqin/cernbox/workdir/taug-2/SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root","READ");//Trigger

    TH1D *recoeff = (TH1D*)freco->Get("Efficiencies_muon_reco_abseta");
    TH2F *IDeff = (TH2F*)fID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
    TH2F *isoeff = (TH2F*)fiso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
    TH2F *triggereff = (TH2F*)ftrigger->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");


    TChain *arbre = new TChain("Events");
    TChain *arbre2 = new TChain("Runs");
    if (sample=="data"){

    
    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018A-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018A-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018B-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018B-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018C-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018C-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    arbre->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018D-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");
    arbre2->Add("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/SingleMuon_Run2018D-UL2018_MiniAODv2_NanoAODv9-v2_mutau/*.root");

    }

    else {
    arbre->Add(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/%s/*.root",name.c_str()));
    arbre2->Add(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/ntuple/mutau/%s/*.root",name.c_str()));
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
    arbre->SetBranchAddress("LepCand_tauidMsf",&LepCand_tauidMsf); //tau id scale factor
    arbre->SetBranchAddress("LepCand_taues",&LepCand_taues); //tau energy scale factor
    arbre->SetBranchAddress("pu_weight",&pu_weight);//pile up weight
    TFile *fout = new TFile(Form("/afs/cern.ch/user/x/xuqin/eos/taug-2/nanoplots/mutau/%s.root",sample.c_str()),"recreate");
    //TTree *tout = new TTree("Events","Events after basic selection");
    TTree *tout = (TTree*)arbre->CloneTree(0);
    double taupt, mupt, taueta, mueta, tauphi, muphi, taumumass,taumudelphi,Acopl, muiso, mumediumID, tauvsmu, tauvse, tauvsjet, mucharge, taucharge, Mcol, xsweight, MT_muonMET;
    double muidsf,tauidsf,tauesf;
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
    //tout->Branch("PV_ndof",&PV_ndof);
    //tout->Branch("MET_pt",&MET_pt);
    //tout->Branch("nJets",&nJets);
    tout->Branch("Mcol",&Mcol);
    tout->Branch("MT_muonMET",&MT_muonMET);
    tout->Branch("xsweight",&xsweight);
    tout->Branch("muidsf",&muidsf);
    tout->Branch("tauidsf",&tauidsf);
    tout->Branch("tauesf",&tauesf);
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
            tauvsjet = LepCand_vse[0];
            taucharge = LepCand_charge[0];
            mucharge = LepCand_charge[1]; 
            tauidsf = LepCand_tauidMsf[0];
            tauesf = LepCand_taues[0];           
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
            tauidsf = LepCand_tauidMsf[1];
            tauesf = LepCand_taues[1];   

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
            tauidsf = LepCand_tauidMsf[0];
            tauesf = LepCand_taues[0];    
        }

        else continue;
        my_tau=my_tau*tauesf;
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



        double recosf,IDsf,isosf,triggersf;

        recosf = recoeff->GetBinContent(recoeff->FindBin(abs(mueta)));
        if (recosf==0){
            cout << "mueta = " << mueta << " recosf = 0" << endl; 

        }


        if (mupt<120){
            IDsf = IDeff->GetBinContent(IDeff->FindBin(abs(mueta),mupt));
            isosf = isoeff->GetBinContent(isoeff->FindBin(abs(mueta),mupt));
        }
        else{
            IDsf = IDeff->GetBinContent(IDeff->FindBin(abs(mueta),119));
            isosf = isoeff->GetBinContent(isoeff->FindBin(abs(mueta),119));
        }

        if (mupt<200){
            triggersf = triggereff->GetBinContent(triggereff->FindBin(abs(mueta),mupt));
        }
        else {
            triggersf = triggereff->GetBinContent(triggereff->FindBin(abs(mueta),199));
        }

        muidsf = recosf*IDsf*isosf*triggersf;
        
        //cout << "recosf = " << recosf << " IDsf = " << IDsf << " isosf = " << isosf << " triggersf = " << triggersf << endl;
        //cout << "muidsf = " << muidsf << endl; 

/*       TLorentzVector my_tau;
        if (nLepCand>0 and LepCand_id[0]==15) my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==15) my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);
        TLorentzVector my_mu;
        if (nLepCand>0 and LepCand_id[0]==13) my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0);
        else if (nLepCand>1 and LepCand_id[1]==13) my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0);*/

        //if (fabs(my_tau.Eta())>2.1) continue;
        //cout << "haha" << endl;
        taumumass = (my_tau + my_mu).M();
        taumudelphi = my_tau.DeltaPhi(my_mu);
        Acopl = 1 - abs(taumudelphi)/TMath::Pi();
        double metx = MET_pt * TMath::Cos(MET_phi);
        double mety = MET_pt * TMath::Sin(MET_phi);
        Mcol = GetCollMass(my_tau,my_mu,metx,mety);
        double muMETdelphi = my_mu.Phi()-MET_phi;
        MT_muonMET = TMath::Sqrt(2*mupt*MET_pt*(1-TMath::Cos(muMETdelphi)));
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