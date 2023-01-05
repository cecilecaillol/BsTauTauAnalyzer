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
    arbre->SetBranchAddress("LepCand_eleMVAiso80", &LepCand_eleMVAiso80);
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("run", &run);

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
    arbre->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1);

    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);

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

   std::vector<TH1F*> h0_lowNT_highA;
   std::vector<TH1F*> h0_lowNT_highA_anti;
   std::vector<TH1F*> h1_lowNT_highA;
   std::vector<TH1F*> h1_lowNT_highA_anti;
   std::vector<TH1F*> h2_lowNT_highA;
   std::vector<TH1F*> h2_lowNT_highA_anti;
   std::vector<TH1F*> h3_lowNT_highA;
   std::vector<TH1F*> h3_lowNT_highA_anti;
   std::vector<TH1F*> h4_lowNT_highA;
   std::vector<TH1F*> h4_lowNT_highA_anti;
   std::vector<TH1F*> h5_lowNT_highA;
   std::vector<TH1F*> h5_lowNT_highA_anti;
   std::vector<TH1F*> h6_lowNT_highA;
   std::vector<TH1F*> h6_lowNT_highA_anti;
   std::vector<TH1F*> h7_lowNT_highA;
   std::vector<TH1F*> h7_lowNT_highA_anti;
   std::vector<TH1F*> h8_lowNT_highA;
   std::vector<TH1F*> h8_lowNT_highA_anti;

   // Control 1
   /*float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,300,500};//mvis
   float bins1[] = {25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,110,120};//e pt
   float bins2[] = {20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};//tau pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};//tau dm
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};//mt
   float bins7[] = {0,1,2,3,4,5,6,7,8};//njets
   float bins8[] = {0,0.01,0.02,0.03,0.04,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0};//acoplanarity*/

   // Signal region
   float bins0[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins1[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins2[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins3[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins4[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins5[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins6[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins7[] = {40,55,70,85,100,150,200,350,500};//mvis
   float bins8[] = {40,55,70,85,100,150,200,350,500};//mvis

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

        ostringstream HN0LNLA; HN0LNLA << "h0_lowNT_highA" << k;
        h0_lowNT_highA.push_back(new TH1F (HN0LNLA.str().c_str(),"InvMa",binnum0,bins0)); h0_lowNT_highA[k]->Sumw2();
        ostringstream HN1LNLA; HN1LNLA << "h1_lowNT_highA" << k;
        h1_lowNT_highA.push_back(new TH1F (HN1LNLA.str().c_str(),"InvMa",binnum1,bins1)); h1_lowNT_highA[k]->Sumw2();
        ostringstream HN2LNLA; HN2LNLA << "h2_lowNT_highA" << k;
        h2_lowNT_highA.push_back(new TH1F (HN2LNLA.str().c_str(),"InvMa",binnum2,bins2)); h2_lowNT_highA[k]->Sumw2();
        ostringstream HN3LNLA; HN3LNLA << "h3_lowNT_highA" << k;
        h3_lowNT_highA.push_back(new TH1F (HN3LNLA.str().c_str(),"InvMa",binnum3,bins3)); h3_lowNT_highA[k]->Sumw2();
        ostringstream HN4LNLA; HN4LNLA << "h4_lowNT_highA" << k;
        h4_lowNT_highA.push_back(new TH1F (HN4LNLA.str().c_str(),"InvMa",binnum4,bins4)); h4_lowNT_highA[k]->Sumw2();
        ostringstream HN5LNLA; HN5LNLA << "h5_lowNT_highA" << k;
        h5_lowNT_highA.push_back(new TH1F (HN5LNLA.str().c_str(),"InvMa",binnum5,bins5)); h5_lowNT_highA[k]->Sumw2();
        ostringstream HN6LNLA; HN6LNLA << "h6_lowNT_highA" << k;
        h6_lowNT_highA.push_back(new TH1F (HN6LNLA.str().c_str(),"InvMa",binnum6,bins6)); h6_lowNT_highA[k]->Sumw2();
        ostringstream HN7LNLA; HN7LNLA << "h7_lowNT_highA" << k;
        h7_lowNT_highA.push_back(new TH1F (HN7LNLA.str().c_str(),"InvMa",binnum7,bins7)); h7_lowNT_highA[k]->Sumw2();
        ostringstream HN8LNLA; HN8LNLA << "h8_lowNT_highA" << k;
        h8_lowNT_highA.push_back(new TH1F (HN8LNLA.str().c_str(),"InvMa",binnum8,bins8)); h8_lowNT_highA[k]->Sumw2();

        ostringstream HN0LNLA_lowNT_highA_anti; HN0LNLA_lowNT_highA_anti << "h0_lowNT_highA_anti" << k;
        h0_lowNT_highA_anti.push_back(new TH1F (HN0LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum0,bins0)); h0_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN1LNLA_lowNT_highA_anti; HN1LNLA_lowNT_highA_anti << "h1_lowNT_highA_anti" << k;
        h1_lowNT_highA_anti.push_back(new TH1F (HN1LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum1,bins1)); h1_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN2LNLA_lowNT_highA_anti; HN2LNLA_lowNT_highA_anti << "h2_lowNT_highA_anti" << k;
        h2_lowNT_highA_anti.push_back(new TH1F (HN2LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum2,bins2)); h2_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN3LNLA_lowNT_highA_anti; HN3LNLA_lowNT_highA_anti << "h3_lowNT_highA_anti" << k;
        h3_lowNT_highA_anti.push_back(new TH1F (HN3LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum3,bins3)); h3_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN4LNLA_lowNT_highA_anti; HN4LNLA_lowNT_highA_anti << "h4_lowNT_highA_anti" << k;
        h4_lowNT_highA_anti.push_back(new TH1F (HN4LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum4,bins4)); h4_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN5LNLA_lowNT_highA_anti; HN5LNLA_lowNT_highA_anti << "h5_lowNT_highA_anti" << k;
        h5_lowNT_highA_anti.push_back(new TH1F (HN5LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum5,bins5)); h5_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN6LNLA_lowNT_highA_anti; HN6LNLA_lowNT_highA_anti << "h6_lowNT_highA_anti" << k;
        h6_lowNT_highA_anti.push_back(new TH1F (HN6LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum6,bins6)); h6_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN7LNLA_lowNT_highA_anti; HN7LNLA_lowNT_highA_anti << "h7_lowNT_highA_anti" << k;
        h7_lowNT_highA_anti.push_back(new TH1F (HN7LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum7,bins7)); h7_lowNT_highA_anti[k]->Sumw2();
        ostringstream HN8LNLA_lowNT_highA_anti; HN8LNLA_lowNT_highA_anti << "h8_lowNT_highA_anti" << k;
        h8_lowNT_highA_anti.push_back(new TH1F (HN8LNLA_lowNT_highA_anti.str().c_str(),"InvMa",binnum8,bins8)); h8_lowNT_highA_anti[k]->Sumw2();
   }

   float bins_taupt[] = {20,22,24,26,28,30,35,40,45,50,60,70,80,90,100,150,200};
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   TH1F *h_tauFR_W_dm0_VVVL=new TH1F("h_tauFR_W_dm0_VVVL","h_tauFR_W_dm0_VVVL",binnum_taupt,bins_taupt); h_tauFR_W_dm0_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm1_VVVL=new TH1F("h_tauFR_W_dm1_VVVL","h_tauFR_W_dm1_VVVL",binnum_taupt,bins_taupt); h_tauFR_W_dm1_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm10_VVVL=new TH1F("h_tauFR_W_dm10_VVVL","h_tauFR_W_dm10_VVVL",binnum_taupt,bins_taupt); h_tauFR_W_dm10_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm11_VVVL=new TH1F("h_tauFR_W_dm11_VVVL","h_tauFR_W_dm11_VVVL",binnum_taupt,bins_taupt); h_tauFR_W_dm11_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm0_M=new TH1F("h_tauFR_W_dm0_M","h_tauFR_W_dm0_M",binnum_taupt,bins_taupt); h_tauFR_W_dm0_M->Sumw2();
   TH1F *h_tauFR_W_dm1_M=new TH1F("h_tauFR_W_dm1_M","h_tauFR_W_dm1_M",binnum_taupt,bins_taupt); h_tauFR_W_dm1_M->Sumw2();
   TH1F *h_tauFR_W_dm10_M=new TH1F("h_tauFR_W_dm10_M","h_tauFR_W_dm10_M",binnum_taupt,bins_taupt); h_tauFR_W_dm10_M->Sumw2();
   TH1F *h_tauFR_W_dm11_M=new TH1F("h_tauFR_W_dm11_M","h_tauFR_W_dm11_M",binnum_taupt,bins_taupt); h_tauFR_W_dm11_M->Sumw2();

   TH1F *h_tauFR_QCD_dm0_VVVL=new TH1F("h_tauFR_QCD_dm0_VVVL","h_tauFR_QCD_dm0_VVVL",binnum_taupt,bins_taupt); h_tauFR_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm1_VVVL=new TH1F("h_tauFR_QCD_dm1_VVVL","h_tauFR_QCD_dm1_VVVL",binnum_taupt,bins_taupt); h_tauFR_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm10_VVVL=new TH1F("h_tauFR_QCD_dm10_VVVL","h_tauFR_QCD_dm10_VVVL",binnum_taupt,bins_taupt); h_tauFR_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm11_VVVL=new TH1F("h_tauFR_QCD_dm11_VVVL","h_tauFR_QCD_dm11_VVVL",binnum_taupt,bins_taupt); h_tauFR_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm0_M=new TH1F("h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_M",binnum_taupt,bins_taupt); h_tauFR_QCD_dm0_M->Sumw2();
   TH1F *h_tauFR_QCD_dm1_M=new TH1F("h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_M",binnum_taupt,bins_taupt); h_tauFR_QCD_dm1_M->Sumw2();
   TH1F *h_tauFR_QCD_dm10_M=new TH1F("h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_M",binnum_taupt,bins_taupt); h_tauFR_QCD_dm10_M->Sumw2();
   TH1F *h_tauFR_QCD_dm11_M=new TH1F("h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_M",binnum_taupt,bins_taupt); h_tauFR_QCD_dm11_M->Sumw2();

   TH1F *h_tauFR_QCD_xtrg_M=new TH1F("h_tauFR_QCD_xtrg_M","h_tauFR_QCD_xtrg_M",binnum_taupt,bins_taupt); h_tauFR_QCD_xtrg_M->Sumw2();
   TH1F *h_tauFR_QCD_xtrg_VVVL=new TH1F("h_tauFR_QCD_xtrg_VVVL","h_tauFR_QCD_xtrg_VVVL",binnum_taupt,bins_taupt); h_tauFR_QCD_xtrg_VVVL->Sumw2();
   TH1F *h_tauFR_W_xtrg_M=new TH1F("h_tauFR_W_xtrg_M","h_tauFR_W_xtrg_M",binnum_taupt,bins_taupt); h_tauFR_W_xtrg_M->Sumw2();
   TH1F *h_tauFR_W_xtrg_VVVL=new TH1F("h_tauFR_W_xtrg_VVVL","h_tauFR_W_xtrg_VVVL",binnum_taupt,bins_taupt); h_tauFR_W_xtrg_VVVL->Sumw2();

   TString uncertainties[1]={""};
   TString fake_uncertainties[1]={""};
   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp90noiso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");

   TFile* f_etautrgSF=new TFile("scalefactors/electron_SF_etautrg_2018UL.root","read");
   TH2F* h_etautrgData= (TH2F*) f_etautrgSF->Get("data_trg_eff");
   TH2F* h_etautrgMC= (TH2F*) f_etautrgSF->Get("ZLL_trg_eff");
   TFile* f_e32trgSF=new TFile("scalefactors/electron_SF_e32trg_2018UL.root","read");
   TH2F* h_e32trgData= (TH2F*) f_etautrgSF->Get("data_trg_eff");
   TH2F* h_e32trgMC= (TH2F*) f_etautrgSF->Get("ZLL_trg_eff");

   TFile* f_taufr = new TFile("fakerate/FitValues_tauFR_2018.root");
   TF1 *fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
   TF1 *fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
   TF1 *fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
   TF1 *fit_taufr_W_dm0 = (TF1*) f_taufr->Get("theFit_W_dm0");
   TF1 *fit_taufr_W_dm1 = (TF1*) f_taufr->Get("theFit_W_dm1");
   TF1 *fit_taufr_W_dm10 = (TF1*) f_taufr->Get("theFit_W_dm10");
   TF1 *fit_taufr_QCD_xtrg = (TF1*) f_taufr->Get("theFit_QCD_xtrg");
   TF1 *fit_taufr_W_xtrg = (TF1*) f_taufr->Get("theFit_W_xtrg");

   TH2F *fractionOS=new TH2F("fractionOS","fractionOS",3,0,75,5,50,300);
   TH2F *fractionSS=new TH2F("fractionSS","fractionSS",3,0,75,5,50,300);

   TFile* f_frac=new TFile("output_etau_2018/fractions.root","read");
   TH2F* h_fracW= (TH2F*) f_frac->Get("frac_W");

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpleditau = new TH1F("h_vtxresolution_simpleditau","h_vtxresolution_simpleditau",200,-1,1); h_vtxresolution_simpleditau->Sumw2();
   TH1F* h_ntracks = new TH1F("h_ntracks","h_ntracks",30,0,30); h_ntracks->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   /* arbre->SetCacheLearnEntries(1);
    arbre->SetCacheSize(1000000U);
    arbre->SetCacheEntryRange(0,nentries_wtn);
    arbre->AddBranchToCache("*",true);*/

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");
   auto b1_7=arbre->GetBranch("LepCand_taues");
   auto b1_8=arbre->GetBranch("LepCand_fes");
   /*arbre->AddBranchToCache(b1_1, true);
   arbre->AddBranchToCache(b1_2, true);
   arbre->AddBranchToCache(b1_3, true);
   arbre->AddBranchToCache(b1_4, true);
   arbre->AddBranchToCache(b1_5, true);
   arbre->AddBranchToCache(b1_6, true);
   arbre->AddBranchToCache(b1_7, true);
   arbre->AddBranchToCache(b1_8, true);*/

   auto b2_1=arbre->GetBranch("HLT_Ele32_WPTight_Gsf");
   auto b2_2=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1");
   auto b2_3=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1");
   auto b2_4=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1");
   auto b2_5=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1");
   auto b2_6=arbre->GetBranch("run");

   auto b3_1=arbre->GetBranch("LepCand_vse");
   auto b3_2=arbre->GetBranch("LepCand_vsmu");
   auto b3_3=arbre->GetBranch("LepCand_vsjet");
   auto b3_4=arbre->GetBranch("LepCand_charge");
   auto b3_5=arbre->GetBranch("LepCand_eleMVAiso90");
   auto b3_6=arbre->GetBranch("LepCand_DecayMode");

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("LepCand_tauidMsf");
   auto b4_4=arbre->GetBranch("LepCand_antielesf");
   auto b4_5=arbre->GetBranch("LepCand_antimusf");
   auto b4_6=arbre->GetBranch("LepCand_tautriggersf");

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

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);

        b1_1->GetEntry(i); b1_2->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_6->GetEntry(i);
        if (name!="data_obs") {b1_5->GetEntry(i); b1_7->GetEntry(i); b1_8->GetEntry(i);}

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

	if (name=="ZTT" and LepCand_gen[tau_index]!=5) continue;
        if (name=="ZLL" and LepCand_gen[tau_index]==5) continue;

	if (fabs(my_tau.Eta())>2.3) continue;
        if (fabs(my_ele.Eta())>2.1) continue;
	if (my_tau.DeltaR(my_ele)<0.5) continue;


	// Trigger block
	b2_1->GetEntry(i); 
	if (name=="data_obs") {b2_6->GetEntry(i);}
	if (name=="data_obs" and run<317509) {b2_4->GetEntry(i); b2_5->GetEntry(i);}
	if (name!="data_obs" or run>=317509) {b2_2->GetEntry(i); b2_3->GetEntry(i);}

	bool is_eletrg=false;
	bool is_etautrg=false;
	bool is_etauHPStrg=false;
	if (year=="2018"){
	   is_eletrg=(HLT_Ele32_WPTight_Gsf and my_ele.Pt()>33);
	   if (name!="data_obs" or run>=317509) is_etauHPStrg=((HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 or HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_TightID_CrossL1) and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
           if (name=="data_obs" and run<317509) is_etautrg=((HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 or HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1) and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
	
	   if (name!="data_obs" and !is_eletrg and !is_etauHPStrg) continue;
	   if (name=="data_obs" and run<317509 and !is_eletrg and !is_etautrg) continue;
           if (name=="data_obs" and run>=317509 and !is_eletrg and !is_etauHPStrg) continue;
	}

	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_5->GetEntry(i); b3_6->GetEntry(i);
	if (LepCand_vse[tau_index]<127 or LepCand_vsmu[tau_index]<1 or LepCand_vsjet[tau_index]<1) continue;
	if (!LepCand_eleMVAiso90[ele_index]) continue;

	bool is_OS = (LepCand_charge[tau_index]*LepCand_charge[ele_index]<0);
	bool is_isolated = (LepCand_vsjet[tau_index]>=16);

	// Block weights
	if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_3->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i);}
	float aweight=1.0;
	if (name!="data_obs"){
	   aweight=aweight*pu_weight*genWeight;
	   if (LepCand_gen[tau_index]==5) aweight=aweight*LepCand_tauidMsf[tau_index];
           if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*LepCand_antielesf[tau_index];
           if (LepCand_gen[tau_index]==2 or LepCand_gen[tau_index]==4) aweight=aweight*LepCand_antimusf[tau_index];
	   if (is_etautrg or is_etauHPStrg){ 
	      aweight=aweight*LepCand_tautriggersf[tau_index];
	      float effMC=h_etautrgMC->GetBinContent(h_etautrgMC->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_etautrgMC->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	      float effData=h_etautrgData->GetBinContent(h_etautrgData->GetXaxis()->FindBin(TMath::Min(199.,my_ele.Pt())),h_etautrgData->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	      if (effMC>0) aweight*=effData/effMC;
	   }
	   else{
              float effMC=h_e32trgMC->GetBinContent(h_e32trgMC->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_e32trgMC->GetYaxis()->FindBin(fabs(my_ele.Eta())));
              float effData=h_e32trgData->GetBinContent(h_e32trgData->GetXaxis()->FindBin(TMath::Min(199.,my_ele.Pt())),h_e32trgData->GetYaxis()->FindBin(fabs(my_ele.Eta())));
              if (effMC>0) aweight*=effData/effMC;
	   }
           float ept=my_ele.Pt();
           if (ept>500) ept=499;
           float elIDSF = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
	   aweight=aweight*elIDSF;
	}

	// Block MET
	b5_1->GetEntry(i); b5_2->GetEntry(i);
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(MET_pt,0,MET_phi,0);
	float mt = TMass_F(my_ele.Pt(), my_ele.Px(), my_ele.Py(), my_met.Pt(), my_met.Phi());


	bool is_QCDregion = (mt<50 and !is_OS);
	bool is_Wregion = (is_OS and mt>80 and mt<120);

	bool is_real=(name=="GGTT" or name=="data_obs" or (LepCand_gen[tau_index]>=1 and LepCand_gen[tau_index]<=5));


	// Block vertex
        b6_1->GetEntry(i); b6_3->GetEntry(i);
        if (name!="data_obs") b6_2->GetEntry(i);
	if (fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index])>0.1) continue;
        float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[tau_index]+LepCand_dz[ele_index]);
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
	b8_1->GetEntry(i);
	int ntracks=ntracks_friend;
	h_ntracks->Fill(ntracks);

        float acoplanarity = (1.0 -fabs(my_ele.DeltaPhi(my_tau))/3.14159);

	TLorentzVector save_tau=my_tau;
        TLorentzVector save_ele=my_ele;
        TLorentzVector save_met=my_met;

	bool is_lowNT=(ntracks<2);
	bool is_lowA=(acoplanarity<0.02);

        for (int k=0; k<nbhist; ++k){
           my_tau=save_tau;
	   my_ele=save_ele;
	   my_met=save_met;
	   float weight2=1.0;

	   float mvis=(my_ele+my_tau).M();
	   if (mvis<40) continue;
	   if (my_tau.Pt()<30) continue;

           bool is_cat0=(mt<75);
           bool is_cat1=(mt<75);
           bool is_cat2=(mt<75);
           bool is_cat3=(mt<75);
           bool is_cat4=(mt<75);
           bool is_cat5=(mt<75);
           bool is_cat6=(mt<12000);
           bool is_cat7=(mt<75);
           bool is_cat8=(mt<75);

	   float var0 = mvis;
           float var1 = my_ele.Pt();
           float var2 = my_tau.Pt();
           float var3 = my_ele.Eta();
           float var4 = LepCand_DecayMode[tau_index];
           float var5 = my_met.Pt();
           float var6 = mt;
           int var7 = ntracks;
           float var8 = acoplanarity;

	   if (is_control==0){
              is_cat0=(mt<75 and LepCand_DecayMode[tau_index]==0 and ntracks==0);
              is_cat1=(mt<75 and LepCand_DecayMode[tau_index]==1 and ntracks==0);
              is_cat2=(mt<75 and LepCand_DecayMode[tau_index]==10 and ntracks==0);
              is_cat3=(mt<75 and LepCand_DecayMode[tau_index]==11 and ntracks==0);
              is_cat4=(mt<75 and LepCand_DecayMode[tau_index]==0 and ntracks==1);
              is_cat5=(mt<75 and LepCand_DecayMode[tau_index]==1 and ntracks==1);
              is_cat6=(mt<75 and LepCand_DecayMode[tau_index]==10 and ntracks==1);
              is_cat7=(mt<75 and LepCand_DecayMode[tau_index]==11 and ntracks==1);
              is_cat8=(mt<75);

              var0 = mvis;
              var1 = mvis;
              var2 = mvis;
              var3 = mvis;
              var4 = mvis;
              var5 = mvis;
              var6 = mvis;
              var7 = mvis;
              var8 = mvis;

	   }

           if (is_OS and is_isolated){
	      fractionOS->Fill(mt,mvis,weight*aweight*weight2);
	   }
           if (!is_OS and is_isolated){
              fractionSS->Fill(mt,mvis,weight*aweight*weight2);
           }
	
	   if (is_OS and is_isolated and is_real and is_lowNT and is_lowA){
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

           if (is_OS and is_isolated and is_real and is_lowNT and !is_lowA){
             if (is_cat0) h0_lowNT_highA[k]->Fill(var0,weight*aweight*weight2);
             if (is_cat1) h1_lowNT_highA[k]->Fill(var1,weight*aweight*weight2);
             if (is_cat2) h2_lowNT_highA[k]->Fill(var2,weight*aweight*weight2);
             if (is_cat3) h3_lowNT_highA[k]->Fill(var3,weight*aweight*weight2);
             if (is_cat4) h4_lowNT_highA[k]->Fill(var4,weight*aweight*weight2);
             if (is_cat5) h5_lowNT_highA[k]->Fill(var5,weight*aweight*weight2);
             if (is_cat6) h6_lowNT_highA[k]->Fill(var6,weight*aweight*weight2);
             if (is_cat7) h7_lowNT_highA[k]->Fill(var7,weight*aweight*weight2);
             if (is_cat8) h8_lowNT_highA[k]->Fill(var8,weight*aweight*weight2);
           }
	
	   float tpt=my_tau.Pt();
	   if (tpt>200) tpt=199;
	   float tfr_W=0.1;
           if (is_eletrg and LepCand_DecayMode[tau_index]==0) tfr_W=TMath::Min(0.5,fit_taufr_W_dm0->Eval(tpt));
           else if (is_eletrg and LepCand_DecayMode[tau_index]==1) tfr_W=TMath::Min(0.5,fit_taufr_W_dm1->Eval(tpt));
           else if (is_eletrg) tfr_W=TMath::Min(0.5,fit_taufr_W_dm10->Eval(tpt));
	   else if (is_etautrg or is_etauHPStrg) tfr_W=TMath::Min(0.5,fit_taufr_W_xtrg->Eval(tpt));
           float tfr_QCD=0.1;
           if (is_eletrg and LepCand_DecayMode[tau_index]==0) tfr_QCD=TMath::Min(0.5,fit_taufr_QCD_dm0->Eval(tpt));
           else if (is_eletrg and LepCand_DecayMode[tau_index]==1) tfr_QCD=TMath::Min(0.5,fit_taufr_QCD_dm1->Eval(tpt));
           else if (is_eletrg) tfr_QCD=TMath::Min(0.5,fit_taufr_QCD_dm10->Eval(tpt));
           else if (is_etautrg or is_etauHPStrg) tfr_QCD=TMath::Min(0.5,fit_taufr_QCD_xtrg->Eval(tpt));

	   float mymt=mt;
	   float mymvis=mvis;
	   if (mymvis>300) mymvis=299;
           if (mymvis<50) mymvis=51;
           if (mymt>75) mymt=74;
	   float fracW=h_fracW->GetBinContent(h_fracW->GetXaxis()->FindBin(mymt),h_fracW->GetYaxis()->FindBin(mymvis));
	   if (mymt>75) fracW=1.0;
	   //fracW=1.0;//FIXME
	   float tfr=fracW*tfr_W + (1-fracW)*tfr_QCD;
	   float wfr=tfr;

           if (is_OS and !is_isolated and is_real and is_lowNT and is_lowA){
             if (is_cat0) h0_anti[k]->Fill(var0,weight*aweight*weight2*wfr);
             if (is_cat1) h1_anti[k]->Fill(var1,weight*aweight*weight2*wfr);
             if (is_cat2) h2_anti[k]->Fill(var2,weight*aweight*weight2*wfr);
             if (is_cat3) h3_anti[k]->Fill(var3,weight*aweight*weight2*wfr);
             if (is_cat4) h4_anti[k]->Fill(var4,weight*aweight*weight2*wfr);
             if (is_cat5) h5_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
             if (is_cat6) h6_anti[k]->Fill(var6,weight*aweight*weight2*wfr);
             if (is_cat7) h7_anti[k]->Fill(var7,weight*aweight*weight2*wfr);
             if (is_cat8) h8_anti[k]->Fill(var8,weight*aweight*weight2*wfr);
           }

           if (is_OS and !is_isolated and is_real and is_lowNT and !is_lowA){
             if (is_cat0) h0_lowNT_highA_anti[k]->Fill(var0,weight*aweight*weight2*wfr);
             if (is_cat1) h1_lowNT_highA_anti[k]->Fill(var1,weight*aweight*weight2*wfr);
             if (is_cat2) h2_lowNT_highA_anti[k]->Fill(var2,weight*aweight*weight2*wfr);
             if (is_cat3) h3_lowNT_highA_anti[k]->Fill(var3,weight*aweight*weight2*wfr);
             if (is_cat4) h4_lowNT_highA_anti[k]->Fill(var4,weight*aweight*weight2*wfr);
             if (is_cat5) h5_lowNT_highA_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
             if (is_cat6) h6_lowNT_highA_anti[k]->Fill(var6,weight*aweight*weight2*wfr);
             if (is_cat7) h7_lowNT_highA_anti[k]->Fill(var7,weight*aweight*weight2*wfr);
             if (is_cat8) h8_lowNT_highA_anti[k]->Fill(var8,weight*aweight*weight2*wfr);
           }
	
	   if (k==0 and is_QCDregion and is_real and ntracks>2 and ntracks<10){
	     if (is_eletrg and !is_isolated){
                if (LepCand_DecayMode[tau_index]==0) h_tauFR_QCD_dm0_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==1) h_tauFR_QCD_dm1_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==10) h_tauFR_QCD_dm10_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else h_tauFR_QCD_dm11_VVVL->Fill(my_tau.Pt(),weight*aweight);
	     }
	     if (is_eletrg and is_isolated){
                if (LepCand_DecayMode[tau_index]==0) h_tauFR_QCD_dm0_M->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==1) h_tauFR_QCD_dm1_M->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==10) h_tauFR_QCD_dm10_M->Fill(my_tau.Pt(),weight*aweight);
                else h_tauFR_QCD_dm11_M->Fill(my_tau.Pt(),weight*aweight);
             }

             if (!is_isolated and (is_etautrg or is_etauHPStrg)){
                h_tauFR_QCD_xtrg_VVVL->Fill(my_tau.Pt(),weight*aweight);
             }
             if (is_isolated and (is_etautrg or is_etauHPStrg)){
                h_tauFR_QCD_xtrg_M->Fill(my_tau.Pt(),weight*aweight);
             }
	   }

           if (k==0 and is_Wregion and is_real and ntracks>2 and ntracks<10){
             if (is_eletrg and !is_isolated){
                if (LepCand_DecayMode[tau_index]==0) h_tauFR_W_dm0_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==1) h_tauFR_W_dm1_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==10) h_tauFR_W_dm10_VVVL->Fill(my_tau.Pt(),weight*aweight);
                else h_tauFR_W_dm11_VVVL->Fill(my_tau.Pt(),weight*aweight);
             }
             if (is_eletrg and is_isolated){
                if (LepCand_DecayMode[tau_index]==0) h_tauFR_W_dm0_M->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==1) h_tauFR_W_dm1_M->Fill(my_tau.Pt(),weight*aweight);
                else if (LepCand_DecayMode[tau_index]==10) h_tauFR_W_dm10_M->Fill(my_tau.Pt(),weight*aweight);
                else h_tauFR_W_dm11_M->Fill(my_tau.Pt(),weight*aweight);
             }

	     if (!is_isolated and (is_etautrg or is_etauHPStrg)){
		h_tauFR_W_xtrg_VVVL->Fill(my_tau.Pt(),weight*aweight);
	     }
             if (is_isolated and (is_etautrg or is_etauHPStrg)){
                h_tauFR_W_xtrg_M->Fill(my_tau.Pt(),weight*aweight);
             }
           } //end loop W FF
           
	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_vtxresolution_PV->Write();
    h_vtxresolution_simpleditau->Write();
    h_ntracks->Write();

    fractionOS->Write();
    fractionSS->Write();

    h_tauFR_W_dm0_M->Write();
    h_tauFR_W_dm1_M->Write();
    h_tauFR_W_dm10_M->Write();
    h_tauFR_W_dm11_M->Write();
    h_tauFR_W_dm0_VVVL->Write();
    h_tauFR_W_dm1_VVVL->Write();
    h_tauFR_W_dm10_VVVL->Write();
    h_tauFR_W_dm11_VVVL->Write();

    h_tauFR_QCD_dm0_M->Write();
    h_tauFR_QCD_dm1_M->Write();
    h_tauFR_QCD_dm10_M->Write();
    h_tauFR_QCD_dm11_M->Write();
    h_tauFR_QCD_dm0_VVVL->Write();
    h_tauFR_QCD_dm1_VVVL->Write();
    h_tauFR_QCD_dm10_VVVL->Write();
    h_tauFR_QCD_dm11_VVVL->Write();

    h_tauFR_QCD_xtrg_VVVL->Write();
    h_tauFR_QCD_xtrg_M->Write();
    h_tauFR_W_xtrg_VVVL->Write();
    h_tauFR_W_xtrg_M->Write();

    bool isMC=(name!="data_obs");
    WriteHistToFileETau(fout, h0, name, "et_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h0_anti, name, "et_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h1, name, "et_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h1_anti, name, "et_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h2, name, "et_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h2_anti, name, "et_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h3, name, "et_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h3_anti, name, "et_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h4, name, "et_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h4_anti, name, "et_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h5, name, "et_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h5_anti, name, "et_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h6, name, "et_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h6_anti, name, "et_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h7, name, "et_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h7_anti, name, "et_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h8, name, "et_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h8_anti, name, "et_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    WriteHistToFileETau(fout, h0_lowNT_highA, name, "et_0_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h0_lowNT_highA_anti, name, "et_0_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h1_lowNT_highA, name, "et_1_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h1_lowNT_highA_anti, name, "et_1_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h2_lowNT_highA, name, "et_2_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h2_lowNT_highA_anti, name, "et_2_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h3_lowNT_highA, name, "et_3_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h3_lowNT_highA_anti, name, "et_3_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h4_lowNT_highA, name, "et_4_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h4_lowNT_highA_anti, name, "et_4_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h5_lowNT_highA, name, "et_5_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h5_lowNT_highA_anti, name, "et_5_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h6_lowNT_highA, name, "et_6_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h6_lowNT_highA_anti, name, "et_6_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h7_lowNT_highA, name, "et_7_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h7_lowNT_highA_anti, name, "et_7_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h8_lowNT_highA, name, "et_8_lNlA", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileETau(fout, h8_lowNT_highA_anti, name, "et_8_lNlA_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    fout->Close();
} 


