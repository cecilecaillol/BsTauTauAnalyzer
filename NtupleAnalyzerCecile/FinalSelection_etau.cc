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
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
	 ngen+=genEventCount;
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

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("run", &run);

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

    arbre->SetBranchAddress("pu_weight", &pu_weight);
    arbre->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1);

   int nbhist=1;
   int nbhist_offset=0;

   std::vector<TH1F*> h0;
   std::vector<TH1F*> h0_anti;
   float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   for (int k=0; k<nbhist; ++k){
        ostringstream HN0; HN0 << "h0" << k;
        h0.push_back(new TH1F (HN0.str().c_str(),"InvMa",binnum0,bins0)); h0[k]->Sumw2();

        ostringstream HN0_anti; HN0_anti << "h0_anti" << k;
        h0_anti.push_back(new TH1F (HN0_anti.str().c_str(),"InvMa",binnum0,bins0)); h0_anti[k]->Sumw2();
   }

   TString uncertainties[1]={""};
   TString fake_uncertainties[1]={""};

   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp90noiso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn; i++) {
        arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

	TLorentzVector my_tau;
	int tau_index=0;
	if (nLepCand>0 and LepCand_id[0]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); tau_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); tau_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==15) {my_tau.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); tau_index=2;}
        TLorentzVector my_ele;
	int ele_index=0;
        if (nLepCand>0 and LepCand_id[0]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); ele_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); ele_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); ele_index=2;}

	if (name!="data_obs" and LepCand_gen[tau_index]==5) my_tau=my_tau*LepCand_taues[tau_index];
        if (name!="data_obs" and LepCand_gen[tau_index]>=1 and LepCand_gen[tau_index]<=4) my_tau=my_tau*LepCand_fes[tau_index];

	if (fabs(my_tau.Eta())>2.3) continue;
        if (fabs(my_ele.Eta())>2.5) continue;

	bool is_eletrg=false;
	bool is_etautrg=false;
	if (year=="2018"){
	   is_eletrg=(HLT_Ele32_WPTight_Gsf and my_ele.Pt()>33);
	   is_etauHPStrg=((HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 or HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1) and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta()<2.1);
           is_etautrg=((HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 or HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1) and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta()<2.1);
	
	   if (name!="data_obs" and !is_eletrg and !is_etauHPStrg) continue;
	   if (sample=="data_obs" and run<317509 and !is_eletrg and !is_etautrg) continue;
           if (sample=="data_obs" and run>=317509 and !is_eletrg and !is_etauHPStrg) continue;
	}


	bool is_OS = (LepCand_charge[tau_index]*LepCand_charge[ele_index]<0);
	bool is_isolated = true;

	float aweight=1.0;
	if (name!="data_obs"){
	   aweight=aweight*pu_weight;
	   if (LepCand_gen[tau_index]==5) aweight=aweight*LepCand_tauidsfM[tau_index];
           if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*LepCand_antielesf[tau_index];
           if (LepCand_gen[tau_index]==2 or LepCand_gen[tau_index]==4) aweight=aweight*LepCand_antimusf[tau_index];
	   if (is_etautrg) aweight=aweight*LepCand_tautrgsf[tau_index];
           float ept=my_ele.Pt();
           if (ept>500) ept=499;
           float elIDSF = h_eleSF_M->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
	   aweight=aweight*elIDSF;
	   //else ;
	}

	TLorentzVector save_tau=my_tau;
        TLorentzVector save_ele=my_ele;
        TLorentzVector save_met=my_met;

        for (int k=0; k<nbhist; ++k){
           my_tau=save_tau;
	   my_ele=save_ele;
	   my_met=save_met;
	   float weight2=1.0;
	  
	   if (is_OS and is_isolated){
	     h0[k]->Fill((my_ele+my_tau).M(),weight*aweight*weight2);
	   }

           if (is_OS and !is_isolated){
             h0_anti[k]->Fill((my_ele+my_tau).M(),weight*aweight*weight2);
           }

	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    bool isMC=(name!="data_obs");
    WriteHistToFileETau(fout, h0, name, "et_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h0_anti, name, "et_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    fout->Close();
} 


