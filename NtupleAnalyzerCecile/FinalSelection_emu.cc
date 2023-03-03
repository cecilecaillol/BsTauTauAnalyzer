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
    if (name!="data_obs") {
       Int_t nentries_wtn2 = (Int_t) arbre2->GetEntries();
       arbre2->SetBranchAddress("genEventSumw", &genEventSumw);
       arbre2->SetBranchAddress("genEventCount", &genEventCount);
       for (Int_t i = 0; i < nentries_wtn2; i++) {
         arbre2->GetEntry(i);
         ngen+=genEventSumw;
       }
    }

    size_t start_pos = input.find("2018/");
    std::string input_friend=input;
    if(start_pos != std::string::npos)  input_friend.replace(start_pos, 5, "2018/friend_");
    cout<<input<<" "<<input_friend<<endl;
    TFile *f_Friend = new TFile(input_friend.c_str());//FIXME
    TTree *ami = (TTree*) f_Friend->Get("friend_tree");


    float xs=1.0; float weight=1.0; float luminosity=59830.0;
    if (year=="2017") luminosity=41480.0;
    if (year=="2016pre") luminosity=19520.0;
    if (year=="2016post") luminosity=16810.0;
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6225.42; weight=luminosity*xs/ngen;}
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
    else if (sample=="TTTo2L2Nu"){ xs=831.76*0.1061; weight=luminosity*xs/ngen;}
    else if (sample=="TTToSemiLeptonic"){ xs=831.76*0.4392; weight=luminosity*xs/ngen;}
    else if (sample=="TTToHadronic"){ xs=831.76*0.4544; weight=luminosity*xs/ngen;}
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
    else if (sample=="ST_tW_top"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.95; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=0.669*0.0172; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.009625 * 0.40; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT2"){ xs=0.669*0.0172*3.59; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}

cout<<xs<<" "<<ngen<<" "<<weight<<endl;

    //if (output.find("renano") < 140){
      if (sample=="DY") weight*=0.318*0.985;
      else if (sample=="TTTo2L2Nu") weight*=0.657;
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
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);
    arbre->SetBranchAddress("LepCand_eleMVAnoiso80", &LepCand_eleMVAnoiso80);
    arbre->SetBranchAddress("LepCand_eleMVAnoiso90", &LepCand_eleMVAnoiso90);
    arbre->SetBranchAddress("LepCand_eleIso", &LepCand_eleIso);
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso);
    arbre->SetBranchAddress("LepCand_muonMediumId", &LepCand_muonMediumId);

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
    arbre->SetBranchAddress("genWeight", &genWeight);
    arbre->SetBranchAddress("nJets", &nJets);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);

    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   int nbhist=1;
   int nbhist_offset=0;

   std::vector<TH1F*> h0;
   std::vector<TH1F*> h0_anti;
   std::vector<TH1F*> h1;
   std::vector<TH1F*> h1_anti;
   std::vector<TH1F*> h2;
   std::vector<TH1F*> h2_anti;
   std::vector<TH1F*> h3;
   std::vector<TH1F*> h3_anti;
   std::vector<TH1F*> h4;
   std::vector<TH1F*> h4_anti;
   std::vector<TH1F*> h5;
   std::vector<TH1F*> h5_anti;
   std::vector<TH1F*> h6;
   std::vector<TH1F*> h6_anti;
   std::vector<TH1F*> h7;
   std::vector<TH1F*> h7_anti;
   std::vector<TH1F*> h8;
   std::vector<TH1F*> h8_anti;

   std::vector<TH1F*> h0R;
   std::vector<TH1F*> h0R_anti;
   std::vector<TH1F*> h1R;
   std::vector<TH1F*> h1R_anti;
   std::vector<TH1F*> h2R;
   std::vector<TH1F*> h2R_anti;
   std::vector<TH1F*> h3R;
   std::vector<TH1F*> h3R_anti;
   std::vector<TH1F*> h4R;
   std::vector<TH1F*> h4R_anti;
   std::vector<TH1F*> h5R;
   std::vector<TH1F*> h5R_anti;
   std::vector<TH1F*> h6R;
   std::vector<TH1F*> h6R_anti;
   std::vector<TH1F*> h7R;
   std::vector<TH1F*> h7R_anti;
   std::vector<TH1F*> h8R;
   std::vector<TH1F*> h8R_anti;


   // Control 1
   /*float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,300,500};//mvis
   float bins1[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120};//e pt
   float bins2[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120};//tau pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//mu eta
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};//mt
   float bins7[] = {0,1,2,3,4,5,6,7,8,9,10};//njets
   float bins8[] = {0,0.025,0.05,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6,0.625,0.65,0.675,0.7,0.725,0.75,0.775,0.8,0.825,0.85,0.875,0.9,0.925,0.95,0.975,1.0};//acoplanarity*/

   // Signal region
   float bins0[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins1[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};//mvis
   float bins3[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};//mvis
   float bins4[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins5[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins6[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins7[] = {25,40,55,70,85,100,150,200,350,500};//mvis
   float bins8[] = {25,40,55,70,85,100,150,200,350,500};//mvis

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

        ostringstream HN0R; HN0R << "h0R" << k;
        h0R.push_back(new TH1F (HN0R.str().c_str(),"InvMa",binnum0,bins0)); h0R[k]->Sumw2();
        ostringstream HN1R; HN1R << "h1R" << k;
        h1R.push_back(new TH1F (HN1R.str().c_str(),"InvMa",binnum1,bins1)); h1R[k]->Sumw2();
        ostringstream HN2R; HN2R << "h2R" << k;
        h2R.push_back(new TH1F (HN2R.str().c_str(),"InvMa",binnum2,bins2)); h2R[k]->Sumw2();
        ostringstream HN3R; HN3R << "h3R" << k;
        h3R.push_back(new TH1F (HN3R.str().c_str(),"InvMa",binnum3,bins3)); h3R[k]->Sumw2();
        ostringstream HN4R; HN4R << "h4R" << k;
        h4R.push_back(new TH1F (HN4R.str().c_str(),"InvMa",binnum4,bins4)); h4R[k]->Sumw2();
        ostringstream HN5R; HN5R << "h5R" << k;
        h5R.push_back(new TH1F (HN5R.str().c_str(),"InvMa",binnum5,bins5)); h5R[k]->Sumw2();
        ostringstream HN6R; HN6R << "h6R" << k;
        h6R.push_back(new TH1F (HN6R.str().c_str(),"InvMa",binnum6,bins6)); h6R[k]->Sumw2();
        ostringstream HN7R; HN7R << "h7R" << k;
        h7R.push_back(new TH1F (HN7R.str().c_str(),"InvMa",binnum7,bins7)); h7R[k]->Sumw2();
        ostringstream HN8R; HN8R << "h8R" << k;
        h8R.push_back(new TH1F (HN8R.str().c_str(),"InvMa",binnum8,bins8)); h8R[k]->Sumw2();

        ostringstream HN0_anti; HN0_anti << "h0_anti" << k;
        h0_anti.push_back(new TH1F (HN0_anti.str().c_str(),"InvMa",binnum0,bins0)); h0_anti[k]->Sumw2();
        ostringstream HN1_anti; HN1_anti << "h1_anti" << k;
        h1_anti.push_back(new TH1F (HN1_anti.str().c_str(),"InvMa",binnum1,bins1)); h1_anti[k]->Sumw2();
        ostringstream HN2_anti; HN2_anti << "h2_anti" << k;
        h2_anti.push_back(new TH1F (HN2_anti.str().c_str(),"InvMa",binnum2,bins2)); h2_anti[k]->Sumw2();
        ostringstream HN3_anti; HN3_anti << "h3_anti" << k;
        h3_anti.push_back(new TH1F (HN3_anti.str().c_str(),"InvMa",binnum3,bins3)); h3_anti[k]->Sumw2();
        ostringstream HN4_anti; HN4_anti << "h4_anti" << k;
        h4_anti.push_back(new TH1F (HN4_anti.str().c_str(),"InvMa",binnum4,bins4)); h4_anti[k]->Sumw2();
        ostringstream HN5_anti; HN5_anti << "h5_anti" << k;
        h5_anti.push_back(new TH1F (HN5_anti.str().c_str(),"InvMa",binnum5,bins5)); h5_anti[k]->Sumw2();
        ostringstream HN6_anti; HN6_anti << "h6_anti" << k;
        h6_anti.push_back(new TH1F (HN6_anti.str().c_str(),"InvMa",binnum6,bins6)); h6_anti[k]->Sumw2();
        ostringstream HN7_anti; HN7_anti << "h7_anti" << k;
        h7_anti.push_back(new TH1F (HN7_anti.str().c_str(),"InvMa",binnum7,bins7)); h7_anti[k]->Sumw2();
        ostringstream HN8_anti; HN8_anti << "h8_anti" << k;
        h8_anti.push_back(new TH1F (HN8_anti.str().c_str(),"InvMa",binnum8,bins8)); h8_anti[k]->Sumw2();

        ostringstream HN0R_anti; HN0R_anti << "h0R_anti" << k;
        h0R_anti.push_back(new TH1F (HN0R_anti.str().c_str(),"InvMa",binnum0,bins0)); h0R_anti[k]->Sumw2();
        ostringstream HN1R_anti; HN1R_anti << "h1R_anti" << k;
        h1R_anti.push_back(new TH1F (HN1R_anti.str().c_str(),"InvMa",binnum1,bins1)); h1R_anti[k]->Sumw2();
        ostringstream HN2R_anti; HN2R_anti << "h2R_anti" << k;
        h2R_anti.push_back(new TH1F (HN2R_anti.str().c_str(),"InvMa",binnum2,bins2)); h2R_anti[k]->Sumw2();
        ostringstream HN3R_anti; HN3R_anti << "h3R_anti" << k;
        h3R_anti.push_back(new TH1F (HN3R_anti.str().c_str(),"InvMa",binnum3,bins3)); h3R_anti[k]->Sumw2();
        ostringstream HN4R_anti; HN4R_anti << "h4R_anti" << k;
        h4R_anti.push_back(new TH1F (HN4R_anti.str().c_str(),"InvMa",binnum4,bins4)); h4R_anti[k]->Sumw2();
        ostringstream HN5R_anti; HN5R_anti << "h5R_anti" << k;
        h5R_anti.push_back(new TH1F (HN5R_anti.str().c_str(),"InvMa",binnum5,bins5)); h5R_anti[k]->Sumw2();
        ostringstream HN6R_anti; HN6R_anti << "h6R_anti" << k;
        h6R_anti.push_back(new TH1F (HN6R_anti.str().c_str(),"InvMa",binnum6,bins6)); h6R_anti[k]->Sumw2();
        ostringstream HN7R_anti; HN7R_anti << "h7R_anti" << k;
        h7R_anti.push_back(new TH1F (HN7R_anti.str().c_str(),"InvMa",binnum7,bins7)); h7R_anti[k]->Sumw2();
        ostringstream HN8R_anti; HN8R_anti << "h8R_anti" << k;
        h8R_anti.push_back(new TH1F (HN8R_anti.str().c_str(),"InvMa",binnum8,bins8)); h8R_anti[k]->Sumw2();

   }

   float bins_taupt[] = {10,15,20,24,30,40,100};
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   float bins_nt[] = {-1,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   int  binnum_nt = sizeof(bins_nt)/sizeof(Float_t) - 1;
   TH2F *h_fr_iso=new TH2F("h_fr_iso","h_fr_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_fr_iso->Sumw2();
   TH2F *h_fr_anti=new TH2F("h_fr_anti","h_fr_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_fr_anti->Sumw2();
   TH1F *h_frnt_iso=new TH1F("h_frnt_iso","h_frnt_iso",binnum_nt,bins_nt); h_frnt_iso->Sumw2();
   TH1F *h_frnt_anti=new TH1F("h_frnt_anti","h_frnt_anti",binnum_nt,bins_nt); h_frnt_anti->Sumw2();
   TH2F *h_frFP_iso=new TH2F("h_frFP_iso","h_frFP_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFP_iso->Sumw2();
   TH2F *h_frFP_anti=new TH2F("h_frFP_anti","h_frFP_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFP_anti->Sumw2();
   TH2F *h_frFF_iso=new TH2F("h_frFF_iso","h_frFF_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFF_iso->Sumw2();
   TH2F *h_frFF_anti=new TH2F("h_frFF_anti","h_frFF_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFF_anti->Sumw2();

   TString uncertainties[11]={"","_CMS_pileup_2018Down","_CMS_pileup_2018Up","_CMS_topptreweightingDown","_CMS_topptreweightingUp","_CMS_emutrg_lowmuhighe_2018Down","_CMS_emutrg_lowmuhighe_2018Up","_CMS_emutrg_highmulowe_2018Down","_CMS_emutrg_highmulowe_2018Up","_CMS_emutrg_highmuhighe_2018Down","_CMS_emutrg_highmuhighe_2018Up"};
   TString fake_uncertainties[1]={""};
   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp90noiso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");

   TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","read");
   TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","read");
   TH2F* h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
   TH2F* h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");

   TFile* f_e_trg24=new TFile("scalefactors_emu/e_trg24_UL18.root","read");
   TFile* f_e_trg12=new TFile("scalefactors_emu/e_trg12_UL18.root","read");
   TH2F* h_e_trg24_data= (TH2F*) f_e_trg24->Get("data_trg_eff");
   TH2F* h_e_trg24_zll= (TH2F*) f_e_trg24->Get("ZLL_trg_eff");
   TH2F* h_e_trg12_data= (TH2F*) f_e_trg12->Get("data_trg_eff");
   TH2F* h_e_trg12_zll= (TH2F*) f_e_trg12->Get("ZLL_trg_eff");
   TH2F* h_e_id24_data= (TH2F*) f_e_trg24->Get("data_id_eff");
   TH2F* h_e_id24_zll= (TH2F*) f_e_trg24->Get("ZLL_id_eff");
   TH2F* h_e_id12_data= (TH2F*) f_e_trg12->Get("data_id_eff");
   TH2F* h_e_id12_zll= (TH2F*) f_e_trg12->Get("ZLL_id_eff");
   TH2F* h_e_iso24_data= (TH2F*) f_e_trg24->Get("data_iso_eff");
   TH2F* h_e_iso24_zll= (TH2F*) f_e_trg24->Get("ZLL_iso_eff");
   TH2F* h_e_iso12_data= (TH2F*) f_e_trg12->Get("data_iso_eff");
   TH2F* h_e_iso12_zll= (TH2F*) f_e_trg12->Get("ZLL_iso_eff");
   TFile* f_mu_trg24=new TFile("scalefactors_emu/mu_trg24_UL18.root","read");
   TFile* f_mu_trg8=new TFile("scalefactors_emu/mu_trg8_UL18.root","read");
   TH2F* h_mu_trg24_data= (TH2F*) f_mu_trg24->Get("data_trg_eff");
   TH2F* h_mu_trg24_zll= (TH2F*) f_mu_trg24->Get("ZLL_trg_eff");
   TH2F* h_mu_trg8_data= (TH2F*) f_mu_trg8->Get("data_trg_eff");
   TH2F* h_mu_trg8_zll= (TH2F*) f_mu_trg8->Get("ZLL_trg_eff");
   TH2F* h_mu_id24_data= (TH2F*) f_mu_trg24->Get("data_id_eff");
   TH2F* h_mu_id24_zll= (TH2F*) f_mu_trg24->Get("ZLL_id_eff");
   TH2F* h_mu_id8_data= (TH2F*) f_mu_trg8->Get("data_id_eff");
   TH2F* h_mu_id8_zll= (TH2F*) f_mu_trg8->Get("ZLL_id_eff");
   TH2F* h_mu_iso24_data= (TH2F*) f_mu_trg24->Get("data_iso_eff");
   TH2F* h_mu_iso24_zll= (TH2F*) f_mu_trg24->Get("ZLL_iso_eff");
   TH2F* h_mu_iso8_data= (TH2F*) f_mu_trg8->Get("data_iso_eff");
   TH2F* h_mu_iso8_zll= (TH2F*) f_mu_trg8->Get("ZLL_iso_eff");

   TFile* f_fr=new TFile("emu_fr_2018.root","read");
   TH2F* h_fr=(TH2F*) f_fr->Get("FR");
   TH2F* h_frantimu=(TH2F*) f_fr->Get("FRantimu");
   TF1* fit_frnt=(TF1*) f_fr->Get("fit_frnt");

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpleditau = new TH1F("h_vtxresolution_simpleditau","h_vtxresolution_simpleditau",200,-1,1); h_vtxresolution_simpleditau->Sumw2();
   TH1F* h_ntracks = new TH1F("h_ntracks","h_ntracks",30,0,30); h_ntracks->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   TH1F* h_acoreso=new TH1F("h_acoreso","h_acoreso",100,0,0.1);
   TH1F* h_acoreso_high=new TH1F("h_acoreso_high","h_acoreso_high",100,0,0.1);

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");

   auto b2_1=arbre->GetBranch("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ");
   auto b2_2=arbre->GetBranch("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ");

   auto b2_6=arbre->GetBranch("run");

   auto b3_1=arbre->GetBranch("LepCand_eleMVAiso80");
   auto b3_2=arbre->GetBranch("LepCand_muonIso");
   auto b3_3=arbre->GetBranch("LepCand_muonMediumId");
   auto b3_4=arbre->GetBranch("LepCand_charge");
   auto b3_5=arbre->GetBranch("LepCand_eleMVAiso90");
   auto b3_6=arbre->GetBranch("LepCand_eleMVAnoiso80");
   auto b3_7=arbre->GetBranch("LepCand_eleMVAnoiso90");
   auto b3_8=arbre->GetBranch("LepCand_eleIso");

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("puWeight");
   auto b4_4=arbre->GetBranch("nGenCand");
   auto b4_5=arbre->GetBranch("GenCand_id");
   auto b4_6=arbre->GetBranch("GenCand_pt");
   auto b4_7=arbre->GetBranch("GenCand_eta");
   auto b4_8=arbre->GetBranch("GenCand_phi");
   auto b4_9=arbre->GetBranch("PV_npvs");

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

   TFile* f_aco_fine=new TFile("correction_acoplanarity_fine_2018.root","read");
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

   TFile *f_punt=new TFile("npu_correction_2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("correction_map");

   TFile *f_hsnt=new TFile("nhs_correction_2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");

   TFile* f_npvs=new TFile("correction_npvs_2018.root","read");
   TH1F* h_npvs_weight = (TH1F*) f_npvs->Get("correction_hist_npvs");


   for (Int_t i = 0; i < nentries_wtn; i++) {
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
	b2_1->GetEntry(i); b2_2->GetEntry(i);

	bool is_mu8ele23=(HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>24 and my_mu.Pt()>10);
	bool is_mu23ele12=(HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ and my_ele.Pt()>13 and my_mu.Pt()>24);
	if (!is_mu8ele23 and !is_mu23ele12) continue;


	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_5->GetEntry(i); b3_6->GetEntry(i); b3_7->GetEntry(i); b3_8->GetEntry(i);
	if (LepCand_eleIso[ele_index]>0.50 or !LepCand_eleMVAnoiso90[ele_index]) continue;
	if (LepCand_muonIso[mu_index]>0.50 or !LepCand_muonMediumId[mu_index]) continue;

	bool is_OS = (LepCand_charge[mu_index]*LepCand_charge[ele_index]<0);
	bool is_isolated = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]<0.15);
	bool is_relaxedisolated = (LepCand_muonIso[mu_index]<0.50 and LepCand_eleIso[ele_index]<0.50);
	bool is_FF = (LepCand_muonIso[mu_index]>0.20 and LepCand_eleIso[ele_index]>0.15);
        bool is_PF = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]>0.15);
        bool is_FP = (LepCand_muonIso[mu_index]>0.20 and LepCand_eleIso[ele_index]<0.15);
        bool is_PP = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleIso[ele_index]<0.15);

	//bool is_isolated = (LepCand_muonIso[mu_index]<0.20 and LepCand_eleMVAiso90[ele_index]);

        // Block weights
        if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_7->GetEntry(i); b4_8->GetEntry(i);b4_3->GetEntry(i);}
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
        if (gen_aco>0.35) gen_aco=0.35;
	float top_genpt=0.0;
        float antitop_genpt=0.0;
	if (name=="TT"){
	   for (int l=0; l<nGenCand; ++l){
	      if (top_genpt<1 and GenCand_id[l]==6) top_genpt=GenCand_pt[l];
              if (antitop_genpt<1 and GenCand_id[l]==-6) antitop_genpt=GenCand_pt[l];
	   }
	}

	float aweight=1.0;
	if (name!="data_obs"){
	   aweight=aweight*pu_weight*genWeight;
	   //float ept=my_ele.Pt();
	   //if (ept>120) ept=119;
           //float elIDSF = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
	   //aweight=aweight*elIDSF;
           aweight*=h_npvs_weight->GetBinContent(h_npvs_weight->GetXaxis()->FindBin(PV_npvs));

           float weight_aco=1.0;
           if (sample=="DY" or name=="ZTT" or name=="ZLL"){
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

           float idsf1=1.0;
           float muonIsoSF1=1.0;
           float mu1pt=my_mu.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           idsf1 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           muonIsoSF1 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
	   aweight=aweight*idsf1*muonIsoSF1;

           /*float eff_mu_id8_data=h_mu_id8_data->GetBinContent(h_mu_id8_data->GetXaxis()->FindBin(TMath::Max(15.,my_mu.Pt())),h_mu_id8_data->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_iso8_data=h_mu_iso8_data->GetBinContent(h_mu_iso8_data->GetXaxis()->FindBin(TMath::Max(15.,my_mu.Pt())),h_mu_iso8_data->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_id8_zll=h_mu_id8_zll->GetBinContent(h_mu_id8_zll->GetXaxis()->FindBin(TMath::Max(15.,my_mu.Pt())),h_mu_id8_zll->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_iso8_zll=h_mu_iso8_zll->GetBinContent(h_mu_iso8_zll->GetXaxis()->FindBin(TMath::Max(15.,my_mu.Pt())),h_mu_iso8_zll->GetYaxis()->FindBin(fabs(my_mu.Eta())));
cout<<idsf1*muonIsoSF1<<" "<<((eff_mu_id8_data*eff_mu_iso8_data)/(eff_mu_id8_zll*eff_mu_iso8_zll))<<endl;*/

	   float ept2=my_ele.Pt();
	   if (ept2>200) ept2=199;
           float mupt2=my_mu.Pt();
           if (mupt2>200) mupt2=199;
	   float eff_e_id12_data=h_e_id12_data->GetBinContent(h_e_id12_data->GetXaxis()->FindBin(ept2),h_e_id12_data->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_iso12_data=h_e_iso12_data->GetBinContent(h_e_iso12_data->GetXaxis()->FindBin(ept2),h_e_iso12_data->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_id12_zll=h_e_id12_zll->GetBinContent(h_e_id12_zll->GetXaxis()->FindBin(ept2),h_e_id12_zll->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_iso12_zll=h_e_iso12_zll->GetBinContent(h_e_iso12_zll->GetXaxis()->FindBin(ept2),h_e_iso12_zll->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	   aweight*=((eff_e_id12_data*eff_e_iso12_data)/(eff_e_id12_zll*eff_e_iso12_zll));
	   //cout<<elIDSF<<" "<<((eff_e_id12_data*eff_e_iso12_data)/(eff_e_id12_zll*eff_e_iso12_zll))<<" "<<((eff_e_id24_data*eff_e_iso24_data)/(eff_e_id24_zll*eff_e_iso24_zll))<<endl;

	   if (ept2<20) ept2=20;
           if (mupt2<20) mupt2=15;
	   float eff_e_trg24_data=h_e_trg24_data->GetBinContent(h_e_trg24_data->GetXaxis()->FindBin(ept2),h_e_trg24_data->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_data=h_e_trg12_data->GetBinContent(h_e_trg12_data->GetXaxis()->FindBin(ept2),h_e_trg12_data->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_data=h_mu_trg24_data->GetBinContent(h_mu_trg24_data->GetXaxis()->FindBin(mupt2),h_mu_trg24_data->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_data=h_mu_trg8_data->GetBinContent(h_mu_trg8_data->GetXaxis()->FindBin(mupt2),h_mu_trg8_data->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_e_trg24_zll=h_e_trg24_zll->GetBinContent(h_e_trg24_zll->GetXaxis()->FindBin(ept2),h_e_trg24_zll->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_e_trg12_zll=h_e_trg12_zll->GetBinContent(h_e_trg12_zll->GetXaxis()->FindBin(ept2),h_e_trg12_zll->GetYaxis()->FindBin(fabs(my_ele.Eta())));
           float eff_mu_trg24_zll=h_mu_trg24_zll->GetBinContent(h_mu_trg24_zll->GetXaxis()->FindBin(mupt2),h_mu_trg24_zll->GetYaxis()->FindBin(fabs(my_mu.Eta())));
           float eff_mu_trg8_zll=h_mu_trg8_zll->GetBinContent(h_mu_trg8_zll->GetXaxis()->FindBin(mupt2),h_mu_trg8_zll->GetYaxis()->FindBin(fabs(my_mu.Eta())));

           float probData =eff_e_trg24_data*eff_mu_trg8_data*int(is_mu8ele23)+eff_mu_trg24_data*eff_e_trg12_data*int(is_mu23ele12)-eff_e_trg24_data*eff_mu_trg24_data*int(is_mu8ele23 && is_mu23ele12);
           float probMC =eff_e_trg24_zll*eff_mu_trg8_zll*int(is_mu8ele23)+eff_mu_trg24_zll*eff_e_trg12_zll*int(is_mu23ele12)-eff_e_trg24_zll*eff_mu_trg24_zll*int(is_mu8ele23 && is_mu23ele12);
           float sf_trg=probData/probMC;
           if (probMC==0) sf_trg=1;
           aweight=aweight*sf_trg;
           if (name=="TT") {float toppt_reweighting=pow((TMath::Exp(0.0615-0.0005*top_genpt)*TMath::Exp(0.0615-0.0005*antitop_genpt)),0.5); aweight*=toppt_reweighting; }
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
        h_ntracks->Fill(ntracks);

        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntracksPU_friend;
        if (ntpu>50) ntpu=50;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));}

        if (sample=="DY" or sample=="DYcondor"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }


        h_acoreso->Fill(fabs(gen_aco-acoplanarity));
	if (my_mu.Pt()>30 and my_ele.Pt()>30) h_acoreso_high->Fill(fabs(gen_aco-acoplanarity));

	TLorentzVector save_mu=my_mu;
        TLorentzVector save_ele=my_ele;
        TLorentzVector save_met=my_met;

	bool is_lowNT=(ntracks<20000);
	bool is_lowA=(acoplanarity<200000.02);

        for (int k=0; k<nbhist; ++k){
           my_mu=save_mu;
	   my_ele=save_ele;
	   my_met=save_met;
	   float weight2=1.0;

	   float mvis=(my_ele+my_mu).M();
	   if (mvis<20) continue;
	   if (my_ele.Pt()<15) continue;
           if (my_mu.Pt()<15) continue;
           if (my_ele.Pt()<24 and my_mu.Pt()<24) continue;
	   if (is_mu8ele23 and !is_mu23ele12 and my_ele.Pt()<24) continue;
           if (!is_mu8ele23 and is_mu23ele12 and my_mu.Pt()<24) continue;

           bool is_cat0=(mvis>0);
           bool is_cat1=(mvis>0);
           bool is_cat2=(mvis>0);
           bool is_cat3=(mvis>0);
           bool is_cat4=(mvis>0);
           bool is_cat5=(mvis>0);
           bool is_cat6=(mvis>0);
           bool is_cat7=(mvis>0);
           bool is_cat8=(mvis>0);

           bool is_cat0R=(mvis>0);
           bool is_cat1R=(mvis>0);
           bool is_cat2R=(mvis>0);
           bool is_cat3R=(mvis>0);
           bool is_cat4R=(mvis>0);
           bool is_cat5R=(mvis>0);
           bool is_cat6R=(mvis>0);
           bool is_cat7R=(mvis>0);
           bool is_cat8R=(mvis>0);

	   float var0 = mvis;
           float var1 = my_ele.Pt();
           float var2 = my_mu.Pt();
           float var3 = my_ele.Eta();
           float var4 = my_mu.Eta();
           float var5 = my_met.Pt();
           float var6 = (my_ele+my_mu).Pt();
           int var7 = ntracks;
           float var8 = acoplanarity;

	   if (is_control==0){
              is_cat0=(acoplanarity < 0.02 and mvis>20 and ntracks==0);
              is_cat1=(acoplanarity < 0.02 and mvis>20 and ntracks==1);
              is_cat2=(mvis>20 and ntracks==0);
              is_cat3=(mvis>20 and ntracks==1);
              is_cat4=(mvis>0);
              is_cat5=(mvis>0);
              is_cat6=(mvis>0);
              is_cat7=(mvis>0);
              is_cat8=(mvis>0);

              is_cat0R=(acoplanarity<0.02 and mvis>20 and ntracks<10);
              is_cat1R=(acoplanarity<0.02 and mvis>20 and ntracks<10);
              is_cat2R=(mvis>20 and ntracks<10);
              is_cat3R=(mvis>20 and ntracks<10);
              is_cat4R=(mvis>0);
              is_cat5R=(mvis>0);
              is_cat6R=(mvis>0);
              is_cat7R=(mvis>0);
              is_cat8R=(mvis>0);

              var0 = mvis;
              var1 = mvis;
              var2 = (my_ele+my_mu).Pt();
              var3 = (my_ele+my_mu).Pt();
              var4 = mvis;
              var5 = mvis;
              var6 = mvis;
              var7 = mvis;
              var8 = mvis;

	   }

	   if (is_OS and is_isolated and is_lowNT and is_lowA){
	     if (is_cat0) h0[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) h1[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) h2[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3) h3[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) h4[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) h5[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6) h6[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7) h7[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) h8[k]->Fill(var8,weight*aweight*weight2);

             if (is_cat0R) h0R[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1R) h1R[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2R) h2R[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3R) h3R[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4R) h4R[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5R) h5R[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6R) h6R[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7R) h7R[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8R) h8R[k]->Fill(var8,weight*aweight*weight2);
	   }

	   float fr=h_fr->GetBinContent(h_fr->GetXaxis()->FindBin(TMath::Min(99.,my_ele.Pt())),h_fr->GetYaxis()->FindBin(TMath::Min(99.,my_mu.Pt())));
	   fr*=h_frantimu->GetBinContent(h_frantimu->GetXaxis()->FindBin(TMath::Min(99.,my_ele.Pt())),h_frantimu->GetYaxis()->FindBin(TMath::Min(99.,my_mu.Pt())));
	   fr*=fit_frnt->Eval(ntracks);
	   float wfr=fr;//fr/(1-fr);

           //if (is_OS and !is_isolated and is_lowNT and is_lowA){
           if (!is_OS and is_isolated and is_lowNT and is_lowA){
             if (is_cat0) h0_anti[k]->Fill(var0,weight*aweight*weight2*wfr);
             if (is_cat1) h1_anti[k]->Fill(var1,weight*aweight*weight2*wfr);
             if (is_cat2) h2_anti[k]->Fill(var2,weight*aweight*weight2*wfr);
             if (is_cat3) h3_anti[k]->Fill(var3,weight*aweight*weight2*wfr);
             if (is_cat4) h4_anti[k]->Fill(var4,weight*aweight*weight2*wfr);
             if (is_cat5) h5_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
             if (is_cat6) h6_anti[k]->Fill(var6,weight*aweight*weight2*wfr);
             if (is_cat7) h7_anti[k]->Fill(var7,weight*aweight*weight2*wfr);
             if (is_cat8) h8_anti[k]->Fill(var8,weight*aweight*weight2*wfr);

             if (is_cat0R) h0R_anti[k]->Fill(var0,weight*aweight*weight2*wfr);
             if (is_cat1R) h1R_anti[k]->Fill(var1,weight*aweight*weight2*wfr);
             if (is_cat2R) h2R_anti[k]->Fill(var2,weight*aweight*weight2*wfr);
             if (is_cat3R) h3R_anti[k]->Fill(var3,weight*aweight*weight2*wfr);
             if (is_cat4R) h4R_anti[k]->Fill(var4,weight*aweight*weight2*wfr);
             if (is_cat5R) h5R_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
             if (is_cat6R) h6R_anti[k]->Fill(var6,weight*aweight*weight2*wfr);
             if (is_cat7R) h7R_anti[k]->Fill(var7,weight*aweight*weight2*wfr);
             if (is_cat8R) h8R_anti[k]->Fill(var8,weight*aweight*weight2*wfr);
           }

	   if (k==0){
	     if (is_PF){
	        if (is_OS) h_fr_iso->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
                else h_fr_anti->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
                if (is_OS) h_frnt_iso->Fill(ntracks,weight*aweight);
                else h_frnt_anti->Fill(ntracks,weight*aweight);
                if (is_OS) h_frnt_iso->Fill(-1,weight*aweight);
                else h_frnt_anti->Fill(-1,weight*aweight);
	     }
	     if (is_FP){
                if (is_OS) h_frFP_iso->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
                else h_frFP_anti->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
	     }
             if (is_FF){
                if (is_OS) h_frFF_iso->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
                else h_frFF_anti->Fill(my_ele.Pt(),my_mu.Pt(),weight*aweight);
             }
	   }

	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_acoreso->Write();
    h_acoreso_high->Write();

    h_vtxresolution_PV->Write();
    h_vtxresolution_simpleditau->Write();
    h_ntracks->Write();

    h_fr_anti->Write();
    h_fr_iso->Write();
    h_frnt_anti->Write();
    h_frnt_iso->Write();

    h_frFF_anti->Write();
    h_frFF_iso->Write();
    h_frFP_anti->Write();
    h_frFP_iso->Write();

    bool isMC=(name!="data_obs");
    WriteHistToFileEMu(fout, h0, name, "em_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h0_anti, name, "em_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h1, name, "em_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h1_anti, name, "em_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h2, name, "em_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h2_anti, name, "em_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h3, name, "em_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h3_anti, name, "em_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h4, name, "em_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h4_anti, name, "em_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h5, name, "em_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h5_anti, name, "em_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h6, name, "em_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h6_anti, name, "em_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h7, name, "em_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h7_anti, name, "em_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h8, name, "em_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileEMu(fout, h8_anti, name, "em_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    if (sample=="DY"){
       WriteHistToFileETau(fout, h0R, name, "emR_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h1R, name, "emR_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h2R, name, "emR_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h3R, name, "emR_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h4R, name, "emR_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h5R, name, "emR_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h6R, name, "emR_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h7R, name, "emR_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileETau(fout, h8R, name, "emR_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    }

    WriteHistToFileETau(fout, h0R_anti, name, "emR_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h1R_anti, name, "emR_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h2R_anti, name, "emR_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h3R_anti, name, "emR_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h4R_anti, name, "emR_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h5R_anti, name, "emR_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h6R_anti, name, "emR_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h7R_anti, name, "emR_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h8R_anti, name, "emR_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);


    fout->Close();
} 


