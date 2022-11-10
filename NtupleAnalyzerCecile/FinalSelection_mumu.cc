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
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
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
    else if (sample=="ST_tW_top"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_tau"){ xs=(80.95+136.02)*0.108; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.95; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}

    float filter_eff=1.0;
    if (sample=="DY") filter_eff=0.345;
    weight=weight*filter_eff;

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

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);

    arbre->SetBranchAddress("nChargedPFCandidates", &nChargedPFCandidates);
    arbre->SetBranchAddress("ChargedPFCandidates_dxy", &ChargedPFCandidates_dxy);
    arbre->SetBranchAddress("ChargedPFCandidates_dz", &ChargedPFCandidates_dz);
    arbre->SetBranchAddress("ChargedPFCandidates_eta", &ChargedPFCandidates_eta);
    arbre->SetBranchAddress("ChargedPFCandidates_mass", &ChargedPFCandidates_mass);
    arbre->SetBranchAddress("ChargedPFCandidates_phi", &ChargedPFCandidates_phi);
    arbre->SetBranchAddress("ChargedPFCandidates_pt", &ChargedPFCandidates_pt);
    arbre->SetBranchAddress("ChargedPFCandidates_charge", &ChargedPFCandidates_charge);
    arbre->SetBranchAddress("ChargedPFCandidates_fromPV", &ChargedPFCandidates_fromPV);
    arbre->SetBranchAddress("ChargedPFCandidates_lostInnerHits", &ChargedPFCandidates_lostInnerHits);
    arbre->SetBranchAddress("ChargedPFCandidates_pdgId", &ChargedPFCandidates_pdgId);
    arbre->SetBranchAddress("ChargedPFCandidates_trackHighPurity", &ChargedPFCandidates_trackHighPurity);
    arbre->SetBranchAddress("ChargedPFCandidates_isMatchedToGenHS", &ChargedPFCandidates_isMatchedToGenHS);

    arbre->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
    arbre->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
    arbre->SetBranchAddress("pu_weight", &pu_weight);

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpledimu = new TH1F("h_vtxresolution_simpledimu","h_vtxresolution_simpledimu",200,-1,1); h_vtxresolution_simpledimu->Sumw2();
   TH1F* h_dimumass = new TH1F("h_dimumass","h_dimumass",20,0,200); h_dimumass->Sumw2();

   TH1F* h0 = new TH1F("h0","h0",20,0,200); h0->Sumw2();
   TH1F* h0SS = new TH1F("h0SS","h0SS",20,0,200); h0SS->Sumw2();

   std::vector<TH1F*> h_ntracks;
   int nslices=35;
   for (int k=0; k<nslices; ++k){
     ostringstream HN0; HN0 << "h_ntracks" << k;
     h_ntracks.push_back(new TH1F (HN0.str().c_str(),"Ntracks",30,0,30)); h_ntracks[k]->Sumw2();
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

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	if (!HLT_IsoMu24) continue;

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
	if (!LepCand_muonMediumId[0] or !LepCand_muonMediumId[1]) continue;
	if (LepCand_muonIso[0]>0.10 or LepCand_muonIso[1]>0.10) continue;
	if (fabs(LepCand_dz[0]-LepCand_dz[1])>0.2) continue;

        float aweight=1.0;
        if (name!="data_obs"){
           //aweight*=genWeight;
           aweight*=pu_weight;
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

           aweight=aweight*trgsf*recosf1*idsf1*muonIsoSF1*recosf2*idsf2*muonIsoSF2;
        }

	float simple_dimu_z=0.5*(2*PV_z+LepCand_dz[0]+LepCand_dz[1]);

	bool is_OS=(LepCand_charge[0]*LepCand_charge[1]<0);

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

	if (is_OS){
	   h_dimumass->Fill((my_mu1+my_mu2).M(),weight);
	   h0->Fill((my_mu1+my_mu2).M(),weight);
	}

        if (!is_OS){
           h0SS->Fill((my_mu1+my_mu2).M(),weight);
        }

	if (fabs(91.2-(my_mu1+my_mu2).M())<15 and is_OS){
	   for (int j=0; j<nslices; ++j){
	      int ntracks=0;
              float minz=-3.5+j*0.2;
              float maxz=minz+0.2;
	      if (fabs(minz+0.1-simple_dimu_z)>1.0){ //remove dimuon vertex window
	         for (int k=0; k<nChargedPFCandidates; ++k){
	            float trackz=ChargedPFCandidates_dz[k]+PV_z;
	            if (ChargedPFCandidates_pt[k]>0.5 and trackz>minz and trackz<=maxz) ntracks++;
	         }
		 if (ntracks>29) ntracks=29;
	         h_ntracks[j]->Fill(ntracks,weight);
	      }
	   }
	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_dimumass->Write();
    h_vtxresolution_PV->Write();
    h_vtxresolution_simpledimu->Write();
    for (int i=0; i<nslices; ++i){
      h_ntracks[i]->Write();
    }

    TDirectory *dir0 =fout->mkdir("mumu0");
    dir0->cd();
    h0->SetName(name.c_str());
    h0->Write();

    TDirectory *dir0SS =fout->mkdir("mumu0_SS");
    dir0SS->cd();
    h0SS->SetName(name.c_str());
    h0SS->Write();

    fout->Close();
} 


