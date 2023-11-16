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

    size_t start_pos = input.find("2018/");
    std::string input_friend=input;
    if(start_pos != std::string::npos)  input_friend.replace(start_pos, 5, "2018/friend_");
    start_pos = input.find("2017/");
    if(start_pos != std::string::npos)  input_friend.replace(start_pos, 5, "2017/friend_");
    start_pos = input.find("2016pre/");
    if(start_pos != std::string::npos)  input_friend.replace(start_pos, 8, "2016pre/friend_");
    start_pos = input.find("2016post/");
    if(start_pos != std::string::npos)  input_friend.replace(start_pos, 9, "2016post/friend_");
    cout<<input<<" "<<input_friend<<endl;
    TFile *f_Friend = new TFile(input_friend.c_str());//FIXME
    TTree *ami = (TTree*) f_Friend->Get("friend_tree");


    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6077.2; weight=luminosity*xs/ngen;}
    else if (sample=="DYemu"){ xs=2025.7*(0.178+0.174)*(0.178+0.174); weight=luminosity*xs/ngen;}//FIXME
    else if (sample=="W_Pt100to250"){ xs=689.75; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt250to400"){ xs=24.51; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt400to600"){cout<<"trouve"<<endl; xs=3.110; weight=luminosity*xs/ngen;}
    else if (sample=="W_Pt600toInf"){ xs=0.4683; weight=luminosity*xs/ngen;}
    else if (sample=="W"){ xs=61527.5; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt50to100"){ xs=387.13; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt100to250"){ xs=89.39; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt250to400"){ xs=3.43; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt400to650"){ xs=0.464; weight=luminosity*xs/ngen;}
    else if (sample=="DY_Pt650toInf"){ xs=0.0436; weight=luminosity*xs/ngen;}
    else if (sample=="TTTo2L2Nu"){ xs=791*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic"){ xs=791*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic"){ xs=791*0.4544; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ4L"){ xs=1.212; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=4.42965; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu"){ xs=11.95; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu"){ xs=8.95; weight=luminosity*xs/ngen;}//FIXME
    else if (sample=="WZ2L2Q"){ xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2Q2L"){ xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=3.0; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=134.2; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.0; weight=luminosity*xs/ngen;}
    //else if (sample=="GGTT"){ xs=0.669*0.0172; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00692 * 0.368; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT_Ctb20"){ xs=1.121*0.0269; weight=luminosity*xs/ngen;}
    else if (sample=="GGHTT"){ xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}

//if (sample=="GGTT" and year=="2017") weight*=1.0/0.2984; //FIXME Ctb=20p0


cout<<xs<<" "<<ngen<<" "<<weight<<endl;

    //if (output.find("renano") < 140){
      if (sample=="DY") weight*=0.318;
      else if (sample=="DYemu") weight*=0.10687;
      else if (sample=="TTTo2L2Nu") weight*=0.657;
      else if (sample=="VV2L2Nu") weight*=0.392;
      else if (sample=="TTToSemiLeptonic") weight*=0.401;
      else if (sample=="TTToHadronic") weight*=0.170;
      else if (sample=="ST_t_top") weight*=0.118;
      else if (sample=="ST_t_antitop") weight*=0.122;
      else if (sample=="ST_tW_top") weight*=0.273;
      else if (sample=="ST_tW_antitop") weight*=0.272;
      else if (sample=="WW2L2Nu") weight*=0.397;
      else if (sample=="WW2L2Q") weight*=0.341;
      else if (sample=="WZ3LNu") weight*=0.341;
      else if (sample=="ZZ4L") weight*=0.304;
      else if (sample=="ZZ2L2Nu") weight*=0.302;
      else if (sample=="ZZ2L2Q") weight*=0.373;
      else if (sample=="GGMuMu") weight*=0.941;
      else if (sample=="GGHTT") weight*=0.214;
    //}

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
    arbre->SetBranchAddress("LepCand_eleMVAisoL", &LepCand_eleMVAisoL);
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);
    arbre->SetBranchAddress("LepCand_eleMVAnoiso80", &LepCand_eleMVAnoiso80);
    arbre->SetBranchAddress("LepCand_eleMVAnoisoL", &LepCand_eleMVAnoisoL);
    arbre->SetBranchAddress("LepCand_eleMVAnoiso90", &LepCand_eleMVAnoiso90);
    arbre->SetBranchAddress("LepCand_eleIso", &LepCand_eleIso);
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso);
    arbre->SetBranchAddress("LepCand_muonMediumId", &LepCand_muonMediumId);
    arbre->SetBranchAddress("LepCand_trgmatch", &LepCand_trgmatch);

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("PV_npvs", &PV_npvs);
    arbre->SetBranchAddress("run", &run);

    arbre->SetBranchAddress("GenCand_id", &GenCand_id);
    arbre->SetBranchAddress("GenCand_pt", &GenCand_pt);
    arbre->SetBranchAddress("GenCand_eta", &GenCand_eta);
    arbre->SetBranchAddress("GenCand_phi", &GenCand_phi);
    arbre->SetBranchAddress("nGenCand", &nGenCand);

    arbre->SetBranchAddress("nTracks", &nTracks);
    arbre->SetBranchAddress("Track_dz", &Track_dz);
    arbre->SetBranchAddress("Track_eta", &Track_eta);
    arbre->SetBranchAddress("Track_phi", &Track_phi);
    arbre->SetBranchAddress("Track_pt", &Track_pt);

    arbre->SetBranchAddress("pu_weight", &pu_weight);
    arbre->SetBranchAddress("puWeight", &puWeight);
    arbre->SetBranchAddress("puWeightUp", &puWeightUp);
    arbre->SetBranchAddress("puWeightDown", &puWeightDown);
    arbre->SetBranchAddress("genWeight", &genWeight);
    arbre->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom);
    arbre->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up);
    arbre->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn);
    //arbre->SetBranchAddress("nJets", &nJets);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);

    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
   TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");

   if (year=="2017"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_EGM2D_MVA80iso_UL17.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2017.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2017.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }
   else if (year=="2016post"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_postVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2016postVFP.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }
   else if (year=="2016pre"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_preVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
      TFile* f_eleRecoBelowSF=new TFile("scalefactors/egammaEffi_ptBelow20.txt_EGM2D_UL2016preVFP.root","read");
      h_eleRecoBelowSF= (TH2F*) f_eleRecoBelowSF->Get("EGamma_SF2D");
   }

   TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","read");
   TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","read");
   TH2F* h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
   TH2F* h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
   TH2F* h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
   TH2F* h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
   TH2F* h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
   TH2F* h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");

   if (year=="2016pre"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }
   if (year=="2016post"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }
   if (year=="2017"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonIsoSF_stat= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_stat");
      h_muonIDSF_stat= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
      h_muonIsoSF_syst= (TH2F*) f_muonIso->Get("NUM_LooseRelIso_DEN_MediumID_abseta_pt_syst");
      h_muonIDSF_syst= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");
   }

   TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2018_HLTMu8Ele23.root","read");
   TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2018_HLTMu23Ele12.root","read");
   TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2018_HLTMu23Ele12.root","read");
   TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2018_HLTMu8Ele23.root","read");
   TH2F* h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
   TH2F* h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
   TH2F* h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
   TH2F* h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
   TH2F* h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
   TH2F* h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
   TH2F* h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
   TH2F* h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");

   if (year=="2017"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2017_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2017_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2017_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2017_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }
   else if (year=="2016post"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2016post_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2016post_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2016post_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2016post_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }
   else if (year=="2016pre"){
      TFile* f_e_trg24_c=new TFile("scalefactors/sf_el_2016pre_HLTMu8Ele23.root","read");
      TFile* f_e_trg12_c=new TFile("scalefactors/sf_el_2016pre_HLTMu23Ele12.root","read");
      TFile* f_mu_trg24_c=new TFile("scalefactors/sf_mu_2016pre_HLTMu23Ele12.root","read");
      TFile* f_mu_trg8_c=new TFile("scalefactors/sf_mu_2016pre_HLTMu8Ele23.root","read");
      h_mu_trg24_data_c= (TH2F*) f_mu_trg24_c->Get("eff_data");
      h_mu_trg24_zll_c= (TH2F*) f_mu_trg24_c->Get("eff_mc");
      h_mu_trg8_data_c= (TH2F*) f_mu_trg8_c->Get("eff_data");
      h_mu_trg8_zll_c= (TH2F*) f_mu_trg8_c->Get("eff_mc");
      h_e_trg24_data_c= (TH2F*) f_e_trg24_c->Get("eff_data");
      h_e_trg24_zll_c= (TH2F*) f_e_trg24_c->Get("eff_mc");
      h_e_trg12_data_c= (TH2F*) f_e_trg12_c->Get("eff_data");
      h_e_trg12_zll_c= (TH2F*) f_e_trg12_c->Get("eff_mc");
   }


   TFile* f_fr=new TFile("fakerate/emu_fr_2018.root","read");
   TH2F* h_fr=(TH2F*) f_fr->Get("FR");
   TH2F* h_frantimu=(TH2F*) f_fr->Get("FRantimu");
   TF1* fit_frnt=(TF1*) f_fr->Get("fit_frnt");
   if (year=="2017"){
      TFile* f_fr=new TFile("fakerate/emu_fr_2017.root","read");
      h_fr=(TH2F*) f_fr->Get("FR");
      h_frantimu=(TH2F*) f_fr->Get("FRantimu");
      fit_frnt=(TF1*) f_fr->Get("fit_frnt");
   }
   else if (year=="2016pre"){
      TFile* f_fr=new TFile("fakerate/emu_fr_2016pre.root","read");
      h_fr=(TH2F*) f_fr->Get("FR");
      h_frantimu=(TH2F*) f_fr->Get("FRantimu");
      fit_frnt=(TF1*) f_fr->Get("fit_frnt");
   }
   else if (year=="2016post"){
      TFile* f_fr=new TFile("fakerate/emu_fr_2016post.root","read");
      h_fr=(TH2F*) f_fr->Get("FR");
      h_frantimu=(TH2F*) f_fr->Get("FRantimu");
      fit_frnt=(TF1*) f_fr->Get("fit_frnt");
   }

   TH1F* h_nHS=new TH1F("h_nHS","h_nHS",70,0,70);
   TH1F* h_ptll=new TH1F("h_ptll","h_ptll",50,0,100);
   TH1F* h_nHS_pt0to10=new TH1F("h_nHS_pt0to10","h_nHS_pt0to10",70,0,70);
   TH1F* h_nHS_pt10to20=new TH1F("h_nHS_pt10to20","h_nHS_pt10to20",70,0,70);
   TH1F* h_nHS_pt20to30=new TH1F("h_nHS_pt20to30","h_nHS_pt20to30",70,0,70);
   TH1F* h_nHS_pt30to40=new TH1F("h_nHS_pt30to40","h_nHS_pt30to40",70,0,70);
   TH1F* h_nHS_pt40to50=new TH1F("h_nHS_pt40to50","h_nHS_pt40to50",70,0,70);
   TH1F* h_nHS_pt50to60=new TH1F("h_nHS_pt50to60","h_nHS_pt50to60",70,0,70);

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");

   auto b2_1=arbre->GetBranch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
   auto b2_2=arbre->GetBranch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");
   auto b2_3=arbre->GetBranch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
   auto b2_4=arbre->GetBranch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");

   auto b2_6=arbre->GetBranch("run");

   auto b3_1=arbre->GetBranch("LepCand_eleMVAiso80");
   auto b3_2=arbre->GetBranch("LepCand_muonIso");
   auto b3_3=arbre->GetBranch("LepCand_muonMediumId");
   auto b3_4=arbre->GetBranch("LepCand_charge");
   auto b3_5=arbre->GetBranch("LepCand_eleMVAiso90");
   auto b3_6=arbre->GetBranch("LepCand_eleMVAnoiso80");
   auto b3_7=arbre->GetBranch("LepCand_eleMVAnoiso90");
   auto b3_8=arbre->GetBranch("LepCand_eleIso");
   auto b3_9=arbre->GetBranch("LepCand_eleMVAnoisoL");
   auto b3_10=arbre->GetBranch("LepCand_eleMVAisoL");
   auto b3_11=arbre->GetBranch("LepCand_trgmatch");

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("puWeight");
   auto b4_4=arbre->GetBranch("nGenCand");
   auto b4_5=arbre->GetBranch("GenCand_id");
   auto b4_6=arbre->GetBranch("GenCand_pt");
   auto b4_7=arbre->GetBranch("GenCand_eta");
   auto b4_8=arbre->GetBranch("GenCand_phi");
   auto b4_9=arbre->GetBranch("PV_npvs");
   auto b4_10=arbre->GetBranch("puWeightUp");
   auto b4_11=arbre->GetBranch("puWeightDown");
   auto b4_12=arbre->GetBranch("L1PreFiringWeight_Nom");
   auto b4_13=arbre->GetBranch("L1PreFiringWeight_Up");
   auto b4_14=arbre->GetBranch("L1PreFiringWeight_Dn");


   auto b5_1=arbre->GetBranch("MET_pt");
   auto b5_2=arbre->GetBranch("MET_phi");

   auto b6_1=arbre->GetBranch("PV_z");
   auto b6_2=arbre->GetBranch("GenVtx_z");
   auto b6_3=arbre->GetBranch("LepCand_dz");

   auto b7_1=arbre->GetBranch("nTracks");
   auto b7_2=arbre->GetBranch("Track_dz");
   auto b7_3=arbre->GetBranch("Track_eta");
   auto b7_4=arbre->GetBranch("Track_phi");
   auto b7_5=arbre->GetBranch("Track_pt");

   auto b8_1=ami->GetBranch("ntracks_friend");
   auto b8_3=ami->GetBranch("ntracksHS_friend");
   auto b8_4=ami->GetBranch("ntracksPU_friend");

   TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
   TF1* fit_aco = (TF1*) f_aco->Get("fit_A");

   TFile* f_aco_fine=new TFile("new_correction_acoplanarity_fine_2018.root","read");
   TF1* fit_aco_2030_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_2030_2030");
   TF1* fit_aco_3040_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_2030");
   TF1* fit_aco_4050_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_2030");
   TF1* fit_aco_gt50_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_2030");
   TF1* fit_aco_3040_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_3040");
   TF1* fit_aco_4050_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_3040");
   TF1* fit_aco_gt50_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_3040");
   TF1* fit_aco_4050_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_4050");
   TF1* fit_aco_gt50_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_4050");
   TF1* fit_aco_gt50_gt50 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_gt50");

   TFile *f_punt=new TFile("corrs_ntracks_pu_UL2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("corr");

   TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");

   if (year=="2017"){
      TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
      fit_aco = (TF1*) f_aco->Get("fit_A");
      TFile* f_aco_fine=new TFile("new_correction_acoplanarity_fine_2017.root","read");
      fit_aco_2030_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_2030_2030");
      fit_aco_3040_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_2030");
      fit_aco_4050_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_2030");
      fit_aco_gt50_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_2030");
      fit_aco_3040_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_3040");
      fit_aco_4050_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_3040");
      fit_aco_gt50_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_3040");
      fit_aco_4050_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_4050");
      fit_aco_gt50_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_4050");
      fit_aco_gt50_gt50 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_gt50");
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2017.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2017.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   else if (year=="2016post"){
      TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
      fit_aco = (TF1*) f_aco->Get("fit_A");
      TFile* f_aco_fine=new TFile("new_correction_acoplanarity_fine_2016post.root","read");
      fit_aco_2030_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_2030_2030");
      fit_aco_3040_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_2030");
      fit_aco_4050_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_2030");
      fit_aco_gt50_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_2030");
      fit_aco_3040_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_3040");
      fit_aco_4050_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_3040");
      fit_aco_gt50_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_3040");
      fit_aco_4050_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_4050");
      fit_aco_gt50_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_4050");
      fit_aco_gt50_gt50 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_gt50");
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_postVFP.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_postVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   else if (year=="2016pre"){
      TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
      fit_aco = (TF1*) f_aco->Get("fit_A");
      TFile* f_aco_fine=new TFile("new_correction_acoplanarity_fine_2016pre.root","read");
      fit_aco_2030_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_2030_2030");
      fit_aco_3040_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_2030");
      fit_aco_4050_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_2030");
      fit_aco_gt50_2030 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_2030");
      fit_aco_3040_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_3040_3040");
      fit_aco_4050_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_3040");
      fit_aco_gt50_3040 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_3040");
      fit_aco_4050_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_4050_4050");
      fit_aco_gt50_4050 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_4050");
      fit_aco_gt50_gt50 = (TF1*) f_aco_fine->Get("fit_acoplanarity_gt50_gt50");
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_preVFP.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_preVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();
   for (Int_t i = 0; i < nentries_wtn && i<100000; i++) {
	arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        b1_1->GetEntry(i); b1_2->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_6->GetEntry(i);
        if (name!="data_obs") {b1_5->GetEntry(i);}

	TLorentzVector my_mu;
	int mu_index=0;
	if (nLepCand>0 and LepCand_id[0]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); mu_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); mu_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); mu_index=2;}
        else if (nLepCand>3 and LepCand_id[3]==13) {my_mu.SetPtEtaPhiM(LepCand_pt[3],LepCand_eta[3],LepCand_phi[3],0); mu_index=3;}
        TLorentzVector my_ele;
	int ele_index=0;
        if (nLepCand>0 and LepCand_id[0]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[0],LepCand_eta[0],LepCand_phi[0],0); ele_index=0;}
        else if (nLepCand>1 and LepCand_id[1]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[1],LepCand_eta[1],LepCand_phi[1],0); ele_index=1;}
        else if (nLepCand>2 and LepCand_id[2]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[2],LepCand_eta[2],LepCand_phi[2],0); ele_index=2;}
        else if (nLepCand>3 and LepCand_id[3]==11) {my_ele.SetPtEtaPhiM(LepCand_pt[3],LepCand_eta[3],LepCand_phi[3],0); ele_index=3;}

	if (fabs(my_mu.Eta())>2.4) continue;
        if (fabs(my_ele.Eta())>2.5) continue;
	if (my_mu.DeltaR(my_ele)<0.5) continue;


	// Trigger block
	if (year=="2017" or year=="2018"){b2_1->GetEntry(i); b2_2->GetEntry(i);}
	else if (year=="2016pre"){b2_3->GetEntry(i); b2_4->GetEntry(i);}
	else {b2_1->GetEntry(i); b2_2->GetEntry(i); b2_3->GetEntry(i); b2_4->GetEntry(i); }

	bool is_mu8ele23=false;
	bool is_mu23ele12=false;
	if (year=="2017" or year=="2018"){
	   is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>24 and my_mu.Pt()>10);
	   is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>13 and my_mu.Pt()>24);
	   if (!is_mu8ele23 and !is_mu23ele12) continue;
	}
	else if (year=="2016post"){
           /*if (sample=="aaadata_obs" and year=="2016post" and input!="/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/MuonEGF.root") is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>24 and my_mu.Pt()>10);
	   else is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>24 and my_mu.Pt()>10);
           if (sample=="aaadata_obs" and year=="2016post" and input!="/eos/cms/store/group/cmst3/group/taug2/AnalysisCecile/ntuples_emu_2016post/MuonEGF.root") is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>13 and my_mu.Pt()>24);
 	   else is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>13 and my_mu.Pt()>24);*/
	   if (sample=="data_obs"){
              is_mu8ele23=((HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL or HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) and my_ele.Pt()>24 and my_mu.Pt()>10);
              is_mu23ele12=((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL or HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) and my_ele.Pt()>13 and my_mu.Pt()>24);
	   }
	   else{
              is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>24 and my_mu.Pt()>10);
              is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>13 and my_mu.Pt()>24);
	   }
           if (!is_mu8ele23 and !is_mu23ele12) continue;
        }
        else if (year=="2016pre"){
           is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>24 and my_mu.Pt()>10);
           is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL and my_ele.Pt()>13 and my_mu.Pt()>24);
           if (!is_mu8ele23 and !is_mu23ele12) continue;
	}

	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_5->GetEntry(i); b3_6->GetEntry(i); b3_7->GetEntry(i); b3_8->GetEntry(i);b3_9->GetEntry(i); b3_10->GetEntry(i); b3_11->GetEntry(i);
	//if (LepCand_eleIso[ele_index]>0.50 or !LepCand_eleMVAnoiso90[ele_index]) continue;
	if (!LepCand_eleMVAisoL[ele_index]) continue;
	if (LepCand_muonIso[mu_index]>0.50 or !LepCand_muonMediumId[mu_index]) continue;
        //if (name!="data_obs" and (!LepCand_trgmatch[ele_index] or !LepCand_trgmatch[mu_index])) continue; //FIXME doesnt work in 2016
	if (year=="2018" and (!LepCand_trgmatch[ele_index] or !LepCand_trgmatch[mu_index])) continue;
        if (year!="2018" and !LepCand_trgmatch[ele_index]) continue;

	bool is_OS = (LepCand_charge[mu_index]*LepCand_charge[ele_index]<0);
	/*bool is_isolated = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]<0.15);
	bool is_relaxedisolated = (LepCand_muonIso[mu_index]<0.50 and LepCand_eleIso[ele_index]<0.50);
	bool is_FF = (LepCand_muonIso[mu_index]>0.20 and LepCand_eleIso[ele_index]>0.15);
        bool is_PF = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]>0.15);
        bool is_FP = (LepCand_muonIso[mu_index]>0.20 and LepCand_eleIso[ele_index]<0.15);
        bool is_PP = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]<0.15);*/

 	bool is_isolated = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleMVAiso80[ele_index]);
        bool is_relaxedisolated = (LepCand_muonIso[mu_index]<0.50 and LepCand_eleMVAisoL[ele_index]);
        bool is_FF = (LepCand_muonIso[mu_index]>0.20 and !LepCand_eleMVAiso80[ele_index]);
        bool is_PF = (LepCand_muonIso[mu_index]<0.20 and !LepCand_eleMVAiso80[ele_index]);
        bool is_FP = (LepCand_muonIso[mu_index]>0.20 and LepCand_eleMVAiso80[ele_index]);
        bool is_PP = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleMVAiso80[ele_index]);

	//bool is_isolated = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleMVAiso90[ele_index]);

        // Block weights
        if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_7->GetEntry(i); b4_8->GetEntry(i);b4_3->GetEntry(i); b4_10->GetEntry(i); b4_11->GetEntry(i);}
        if (name!="data_obs") {b4_12->GetEntry(i); b4_13->GetEntry(i); b4_14->GetEntry(i);}
	b4_9->GetEntry(i);

        float acoplanarity = (1.0 -fabs(my_mu.DeltaPhi(my_ele))/3.14159);
        float gen_aco=acoplanarity;
        TLorentzVector my_gen1; my_gen1.SetPtEtaPhiM(0,0,0,0);
        TLorentzVector my_gen2; my_gen2.SetPtEtaPhiM(0,0,0,0);
        if (name!="data_obs" and nGenCand>1) {
           if (GenCand_pt[0]>GenCand_pt[1]){
             my_gen1.SetPtEtaPhiM(GenCand_pt[0],GenCand_eta[0],GenCand_phi[0],0);
             my_gen2.SetPtEtaPhiM(GenCand_pt[1],GenCand_eta[1],GenCand_phi[1],0);
           }
           else{
             my_gen2.SetPtEtaPhiM(GenCand_pt[0],GenCand_eta[0],GenCand_phi[0],0);
             my_gen1.SetPtEtaPhiM(GenCand_pt[1],GenCand_eta[1],GenCand_phi[1],0);
           }
           gen_aco = (1.0 -fabs(my_gen1.DeltaPhi(my_gen2))/3.14159);
        }
        if (nGenCand<2){
	    gen_aco=acoplanarity;
	    if (my_mu.Pt()>my_ele.Pt()){
	 	my_gen1=my_mu;
                my_gen2=my_ele;
	    }
            else{
                my_gen1=my_ele;
                my_gen2=my_mu;
            }
	 }
        if (gen_aco>0.35) gen_aco=0.35;

        float gen_mtt=200.0;
        if (nGenCand>1 and (sample=="GGTT" or sample=="GGWW" or sample=="GGTT_Ctb20")) gen_mtt=(my_gen1+my_gen2).M();

	float top_genpt=0.0;
        float antitop_genpt=0.0;
	if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic"){
	   for (int l=0; l<nGenCand; ++l){
	      if (top_genpt<1 and GenCand_id[l]==6) top_genpt=GenCand_pt[l];
              if (antitop_genpt<1 and GenCand_id[l]==-6) antitop_genpt=GenCand_pt[l];
	   }
	}

	float muidsf_nom=1.0;
        float muisosf_nom=1.0;
        float muidsf_stat_up=1.0;
        float muisosf_stat_up=1.0;
        float muidsf_syst_up=1.0;
        float muisosf_syst_up=1.0;
        float muidsf_stat_down=1.0;
        float muisosf_stat_down=1.0;
        float muidsf_syst_down=1.0;
        float muisosf_syst_down=1.0;
	float elidsf_nom=1.0;
        float elidsf_up=1.0;
        float elidsf_down=1.0;
	float aweight=1.0;
	if (name!="data_obs"){
           aweight=aweight*L1PreFiringWeight_Nom;
	   aweight=aweight*puWeight*genWeight;
	   float ept=my_ele.Pt();
	   if (ept>120) ept=119;
           elidsf_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
	   elidsf_up = elidsf_nom + h_eleIDSF->GetBinError(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
           elidsf_down = elidsf_nom - h_eleIDSF->GetBinError(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
           float elRecoSF = 1.0;
           if (ept<20) elRecoSF = h_eleRecoBelowSF->GetBinContent(h_eleRecoBelowSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleRecoBelowSF->GetYaxis()->FindBin(ept));
	   else elRecoSF = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept));
	   aweight=aweight*elidsf_nom*elRecoSF;
	   // low ntracks e ID (custom SF)
	   if (fabs(my_ele.Eta())<1.5) aweight*=0.98;
           else aweight*=0.95;

           float weight_aco=1.0;
           if (sample=="DY" or name=="ZTT" or name=="ZLL" or sample=="DYemu"){
              if (my_gen1.Pt()<30 and my_gen2.Pt()<30) weight_aco=fit_aco_2030_2030->Eval(gen_aco);
              else if (my_gen1.Pt()>=30  and my_gen1.Pt()<40 and my_gen2.Pt()<30) weight_aco=fit_aco_3040_2030->Eval(gen_aco);
              else if (my_gen1.Pt()>=40  and my_gen1.Pt()<50 and my_gen2.Pt()<30) weight_aco=fit_aco_4050_2030->Eval(gen_aco);
              else if (my_gen1.Pt()>=50  and my_gen2.Pt()<30) weight_aco=fit_aco_gt50_2030->Eval(gen_aco);
              else if (my_gen1.Pt()>=30  and my_gen1.Pt()<40 and my_gen2.Pt()>=30 and my_gen2.Pt()<40) weight_aco=fit_aco_3040_3040->Eval(gen_aco);
              else if (my_gen1.Pt()>=40  and my_gen1.Pt()<50 and my_gen2.Pt()>=30 and my_gen2.Pt()<40) weight_aco=fit_aco_4050_3040->Eval(gen_aco);
              else if (my_gen1.Pt()>=50 and my_gen2.Pt()>=30 and my_gen2.Pt()<40) weight_aco=fit_aco_gt50_3040->Eval(gen_aco);
              else if (my_gen1.Pt()>=40 and my_gen1.Pt()<50 and my_gen2.Pt()>=40 and my_gen2.Pt()<50) weight_aco=fit_aco_4050_4050->Eval(gen_aco);
              else if (my_gen1.Pt()>=50 and my_gen2.Pt()>=40 and my_gen2.Pt()<50) weight_aco=fit_aco_gt50_4050->Eval(gen_aco);
              else if (my_gen1.Pt()>=50 and my_gen2.Pt()>=50) weight_aco=fit_aco_gt50_gt50->Eval(gen_aco);
           }
           aweight=aweight*weight_aco;

           float mu1pt=my_mu.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           muidsf_nom = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           muidsf_stat_up = muidsf_nom + h_muonIDSF_stat->GetBinError(h_muonIDSF_stat->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF_stat->GetYaxis()->FindBin(mu1pt));
           muidsf_syst_up = muidsf_nom + h_muonIDSF_syst->GetBinError(h_muonIDSF_syst->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF_syst->GetYaxis()->FindBin(mu1pt));
           muidsf_stat_down = muidsf_nom - h_muonIDSF_stat->GetBinError(h_muonIDSF_stat->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF_stat->GetYaxis()->FindBin(mu1pt));
           muidsf_syst_down = muidsf_nom - h_muonIDSF_syst->GetBinError(h_muonIDSF_syst->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF_syst->GetYaxis()->FindBin(mu1pt));
           muisosf_nom = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
           muisosf_stat_up = muisosf_nom + h_muonIsoSF_stat->GetBinError(h_muonIsoSF_stat->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF_stat->GetYaxis()->FindBin(mu1pt));
           muisosf_syst_up = muisosf_nom + h_muonIsoSF_syst->GetBinError(h_muonIsoSF_syst->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF_syst->GetYaxis()->FindBin(mu1pt));
           muisosf_stat_down = muisosf_nom - h_muonIsoSF_stat->GetBinError(h_muonIsoSF_stat->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF_stat->GetYaxis()->FindBin(mu1pt));
           muisosf_syst_down = muisosf_nom - h_muonIsoSF_syst->GetBinError(h_muonIsoSF_syst->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF_syst->GetYaxis()->FindBin(mu1pt));
	   aweight=aweight*muidsf_nom*muisosf_nom*GetMuRecoSF(year,my_mu.Eta());

	   float ept2=my_ele.Pt();
	   if (ept2>200) ept2=199;
           float mupt2=my_mu.Pt();
           if (mupt2>200) mupt2=199;

	   if (ept2<15) ept2=15;
           if (mupt2<15) mupt2=15;
           float eff_e_trg24_data=h_e_trg24_data_c->GetBinContent(h_e_trg24_data_c->GetXaxis()->FindBin(ept2),h_e_trg24_data_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_data=h_e_trg12_data_c->GetBinContent(h_e_trg12_data_c->GetXaxis()->FindBin(ept2),h_e_trg12_data_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_data=h_mu_trg24_data_c->GetBinContent(h_mu_trg24_data_c->GetXaxis()->FindBin(mupt2),h_mu_trg24_data_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_data=h_mu_trg8_data_c->GetBinContent(h_mu_trg8_data_c->GetXaxis()->FindBin(mupt2),h_mu_trg8_data_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_e_trg24_zll=h_e_trg24_zll_c->GetBinContent(h_e_trg24_zll_c->GetXaxis()->FindBin(ept2),h_e_trg24_zll_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_zll=h_e_trg12_zll_c->GetBinContent(h_e_trg12_zll_c->GetXaxis()->FindBin(ept2),h_e_trg12_zll_c->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_zll=h_mu_trg24_zll_c->GetBinContent(h_mu_trg24_zll_c->GetXaxis()->FindBin(mupt2),h_mu_trg24_zll_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_zll=h_mu_trg8_zll_c->GetBinContent(h_mu_trg8_zll_c->GetXaxis()->FindBin(mupt2),h_mu_trg8_zll_c->GetYaxis()->FindBin(fabs(my_mu.Eta())));

           float probData =eff_e_trg24_data*eff_mu_trg8_data*int(is_mu8ele23)+eff_mu_trg24_data*eff_e_trg12_data*int(is_mu23ele12)-eff_e_trg24_data*eff_mu_trg24_data*int(is_mu8ele23 && is_mu23ele12);
           float probMC =eff_e_trg24_zll*eff_mu_trg8_zll*int(is_mu8ele23)+eff_mu_trg24_zll*eff_e_trg12_zll*int(is_mu23ele12)-eff_e_trg24_zll*eff_mu_trg24_zll*int(is_mu8ele23 && is_mu23ele12);

           float sf_trg=probData/probMC;
           if (probMC==0) sf_trg=1;
           aweight=aweight*sf_trg;
           if (sample=="TTTo2L2Nu" or sample=="TTToSemiLeptonic" or sample=="TTToHadronic") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*top_genpt)*TMath::Exp(0.0615-0.0005*antitop_genpt)),0.5); aweight*=toppt_reweighting; }
	}

	// Block MET
	b5_1->GetEntry(i); b5_2->GetEntry(i);
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(MET_pt,0,MET_phi,0);
	float mt = TMass_F(my_ele.Pt(), my_ele.Px(), my_ele.Py(), my_met.Pt(), my_met.Phi());


	bool is_QCDregion = (!is_isolated);

	// Block vertex
        b6_1->GetEntry(i); b6_3->GetEntry(i);
        if (name!="data_obs") b6_2->GetEntry(i);
	if (fabs(LepCand_dz[mu_index]-LepCand_dz[ele_index])>0.1) continue;
        float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[mu_index]+LepCand_dz[ele_index]);
        //float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[ele_index]+LepCand_dz[ele_index]);//FIXME

        /*if (is_OS){
           float vtxresolution_PV = (GenVtx_z-PV_z)/GenVtx_z;
           if (vtxresolution_PV>1) vtxresolution_PV=0.99;
           else if (vtxresolution_PV<-1) vtxresolution_PV=-0.99;
           h_vtxresolution_PV->Fill(vtxresolution_PV);

           float vtxresolution_simpleditau = (GenVtx_z-simple_ditau_z)/GenVtx_z;
           if (vtxresolution_simpleditau>1) vtxresolution_simpleditau=0.99;
           else if (vtxresolution_simpleditau<-1) vtxresolution_simpleditau=-0.99;
           h_vtxresolution_simpleditau->Fill(vtxresolution_simpleditau);
        }*/

	// Block tracks
	/*b7_1->GetEntry(i); b7_2->GetEntry(i); b7_3->GetEntry(i); b7_4->GetEntry(i); b7_5->GetEntry(i);
	int ntracks=0;
	for (int nt=0; nt<nTracks; ++nt){
	   if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.05) ntracks++;
	}//FIXME cut eta
	ntracks-=2;
	if (LepCand_DecayMode[tau_index]>=10) ntracks-=2;
	if (ntracks<0) ntracks=0;
	if (ntracks>29) ntracks=29;
	//if (ntracks==1){ 
	//   cout<<ntracks<<" "<<LepCand_dz[tau_index]<<" "<<LepCand_dz[ele_index]<<" "<<(0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<<endl;
	//   cout<<"Electron: "<<my_ele.Pt()<<" "<<my_ele.Eta()<<" "<<my_ele.Phi()<<endl;
        //   cout<<"Tau: "<<my_tau.Pt()<<" "<<my_tau.Eta()<<" "<<my_tau.Phi()<<" "<<LepCand_DecayMode[tau_index]<<endl;
	//   for (int nt=0; nt<nTracks; ++nt){
	//      if (Track_pt[nt]>0.5 and fabs(Track_dz[nt]-0.5*LepCand_dz[tau_index]-0.5*LepCand_dz[ele_index])<0.1)  cout<<"Track: "<<Track_pt[nt]<<" "<<Track_eta[nt]<<" "<<Track_phi[nt]<<" "<<Track_dz[nt]<<endl;
	//   }
	//   cout<<endl;
	//}*/
	//
        b8_1->GetEntry(i); b8_3->GetEntry(i); b8_4->GetEntry(i); 
        int ntracks=ntracks_friend;

        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntracksPU_friend;
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));} 

        //if (sample=="DYemu" or sample=="DY" or sample=="DYcondor" or sample=="VV2L2Nu"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); } 


        bool is_real=(name=="W" or name=="GGTT" or sample=="GGTT" or sample=="GGTT_Ctb20" or name=="data_obs" or (LepCand_gen[ele_index]!=0 and LepCand_gen[mu_index]!=0));

        if (is_OS and is_isolated and is_real and acoplanarity<0.015){
           if (nGenCand==2) h_ptll->Fill((my_gen1+my_gen2).Pt(),weight*aweight);
	   h_nHS->Fill(ntracksHS_friend,weight*aweight);
	   if (nGenCand==2 and (my_gen1+my_gen2).Pt()>2 and (my_gen1+my_gen2).Pt()<10) h_nHS_pt0to10->Fill(ntracksHS_friend,weight*aweight);
           if (nGenCand==2 and (my_gen1+my_gen2).Pt()>10 and (my_gen1+my_gen2).Pt()<20) h_nHS_pt10to20->Fill(ntracksHS_friend,weight*aweight);
           if (nGenCand==2 and (my_gen1+my_gen2).Pt()>20 and (my_gen1+my_gen2).Pt()<30) h_nHS_pt20to30->Fill(ntracksHS_friend,weight*aweight);
           if (nGenCand==2 and (my_gen1+my_gen2).Pt()>30 and (my_gen1+my_gen2).Pt()<40) h_nHS_pt30to40->Fill(ntracksHS_friend,weight*aweight);
           if (nGenCand==2 and (my_gen1+my_gen2).Pt()>40 and (my_gen1+my_gen2).Pt()<50) h_nHS_pt40to50->Fill(ntracksHS_friend,weight*aweight);
           if (nGenCand==2 and (my_gen1+my_gen2).Pt()>50 and (my_gen1+my_gen2).Pt()<60) h_nHS_pt50to60->Fill(ntracksHS_friend,weight*aweight);
        }

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_ptll->Write();
    h_nHS->Write();
    h_nHS_pt0to10->Write();
    h_nHS_pt10to20->Write();
    h_nHS_pt20to30->Write();
    h_nHS_pt30to40->Write();
    h_nHS_pt40to50->Write();
    h_nHS_pt50to60->Write();

    fout->Close();
} 


