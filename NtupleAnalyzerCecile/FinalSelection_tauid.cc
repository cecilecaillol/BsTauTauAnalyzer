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
    cout<<"N gen weighted: "<<ngen<<endl;
    cout<<"N gen unweighted: "<<ngenu<<endl;

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
    TFile *f_Friend = new TFile(input_friend.c_str());
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
      else if (sample=="ST_t_SStop") weight*=0.122;
      else if (sample=="ST_tW_top") weight*=0.273;
      else if (sample=="ST_tW_SStop") weight*=0.272;
      else if (sample=="WW2L2Nu") weight*=0.397;
      else if (sample=="WW2L2Q") weight*=0.341;
      else if (sample=="WZ3LNu") weight*=0.341;
      else if (sample=="ZZ4L") weight*=0.304;
      else if (sample=="ZZ2L2Nu") weight*=0.302;
      else if (sample=="ZZ2L2Q") weight*=0.373;
      else if (sample=="GGMuMu") weight*=0.941;
      else if (sample=="W") weight*=0.0305;
      else if (sample=="W1") weight*=0.0523;
      else if (sample=="W2") weight*=0.0928;
      else if (sample=="W3") weight*=0.132;
      else if (sample=="W4") weight*=0.184;
    //}
    //
    float nnlo=1.162;
    float xsW=52940.0;
    float xsW1=8104.0;
    float xsW2=2793.0;
    float xsW3=992.5;
    float xsW4=544.3;

    float ngenW=2162740.0/0.0305;
    float ngenW1=2315650.0/0.0523;
    float ngenW2=1153860.0/0.0928;
    float ngenW3=1450910.0/0.132;
    float ngenW4=1509960.0/0.184;

    float LW=ngenW/xsW;
    float LW1=ngenW1/xsW1;
    float LW2=ngenW2/xsW2;
    float LW3=ngenW3/xsW3;
    float LW4=ngenW4/xsW4;


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
    arbre->SetBranchAddress("LepCand_taues_up", &LepCand_taues_up);
    arbre->SetBranchAddress("LepCand_fes_up", &LepCand_fes_up);
    arbre->SetBranchAddress("LepCand_antimusf_up", &LepCand_antimusf_up);
    arbre->SetBranchAddress("LepCand_antielesf_up", &LepCand_antielesf_up);
    arbre->SetBranchAddress("LepCand_tautriggersf_up", &LepCand_tautriggersf_up);
    arbre->SetBranchAddress("LepCand_taues_down", &LepCand_taues_down);
    arbre->SetBranchAddress("LepCand_fes_down", &LepCand_fes_down);
    arbre->SetBranchAddress("LepCand_antimusf_down", &LepCand_antimusf_down);
    arbre->SetBranchAddress("LepCand_antielesf_down", &LepCand_antielesf_down);
    arbre->SetBranchAddress("LepCand_tautriggersf_down", &LepCand_tautriggersf_down);
    arbre->SetBranchAddress("LepCand_muonIso", &LepCand_muonIso);
    arbre->SetBranchAddress("LepCand_muonMediumId", &LepCand_muonMediumId);

    arbre->SetBranchAddress("GenCand_id", &GenCand_id);
    arbre->SetBranchAddress("GenCand_pt", &GenCand_pt);
    arbre->SetBranchAddress("GenCand_eta", &GenCand_eta);
    arbre->SetBranchAddress("GenCand_phi", &GenCand_phi);
    arbre->SetBranchAddress("nGenCand", &nGenCand);

    arbre->SetBranchAddress("GenVtx_z", &GenVtx_z);
    arbre->SetBranchAddress("PV_z", &PV_z);
    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("PV_npvs", &PV_npvs);
    arbre->SetBranchAddress("LHE_Njets", &LHE_Njets);

    arbre->SetBranchAddress("nTracks", &nTracks);
    arbre->SetBranchAddress("Track_dz", &Track_dz);
    arbre->SetBranchAddress("Track_eta", &Track_eta);
    arbre->SetBranchAddress("Track_phi", &Track_phi);
    arbre->SetBranchAddress("Track_pt", &Track_pt);

    arbre->SetBranchAddress("pu_weight", &pu_weight);
    arbre->SetBranchAddress("puWeight", &puWeight);
    arbre->SetBranchAddress("puWeightDown", &puWeightDown);
    arbre->SetBranchAddress("puWeightUp", &puWeightUp);
    arbre->SetBranchAddress("genWeight", &genWeight);
    arbre->SetBranchAddress("nJets", &nJets);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);

    arbre->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
    arbre->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
    arbre->SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24);

    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);
    ami->SetBranchAddress("ntracksAll_friend", &ntracksAll_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   int nbhist=1+8;
   int nbhist_offset=0;
   //nbhist=1;//FIXME
	
   std::vector<TH1F*> h0;
   std::vector<TH1F*> h0_SS;
   std::vector<TH1F*> h1;
   std::vector<TH1F*> h1_SS;
   std::vector<TH1F*> h2;
   std::vector<TH1F*> h2_SS;
   std::vector<TH1F*> h3;
   std::vector<TH1F*> h3_SS;
   std::vector<TH1F*> h4;
   std::vector<TH1F*> h4_SS;
   std::vector<TH1F*> h5;
   std::vector<TH1F*> h5_SS;
   std::vector<TH1F*> h6;
   std::vector<TH1F*> h6_SS;
   std::vector<TH1F*> h7;
   std::vector<TH1F*> h7_SS;

   float bins0[] = {55,60,65,70,75,80,85,90,95,100,125,150};//mvis
   int  binnum0 = sizeof(bins0)/sizeof(Float_t) - 1;
   float bins1[] = {50,55,60,65,70,75,80,85,90,95,100,105,110,120,130,140,150};//mvis
   int  binnum1 = sizeof(bins1)/sizeof(Float_t) - 1;
   float bins2[] = {80,90,100,110,120,130,140,150,160,170,180,190,200};//mt
   int  binnum2 = sizeof(bins2)/sizeof(Float_t) - 1;
   float bins3[] = {80,90,100,110,120,130,140,150,160,170,180,190,200};//mt
   int  binnum3 = sizeof(bins3)/sizeof(Float_t) - 1;
   float bins4[] = {60,65,70,75,80,85,90,95,100,125,150};//mvis
   int  binnum4 = sizeof(bins4)/sizeof(Float_t) - 1;
   float bins5[] = {80,90,100,110,120,130,140,150,160,170,180,190,200};//mt
   int  binnum5 = sizeof(bins5)/sizeof(Float_t) - 1;
   float bins6[] = {50,55,60,65,70,75,80,85,90,95,100,105,110,120,130,140,150};//mvis
   int  binnum6 = sizeof(bins6)/sizeof(Float_t) - 1;
   float bins7[] = {80,90,100,110,120,130,140,150,160,170,180,190,200};//mt
   int  binnum7 = sizeof(bins7)/sizeof(Float_t) - 1;

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

        ostringstream HN0_SS; HN0_SS << "h0_SS" << k;
        h0_SS.push_back(new TH1F (HN0_SS.str().c_str(),"InvMa",binnum0,bins0)); h0_SS[k]->Sumw2();
        ostringstream HN1_SS; HN1_SS << "h1_SS" << k;
        h1_SS.push_back(new TH1F (HN1_SS.str().c_str(),"InvMa",binnum1,bins1)); h1_SS[k]->Sumw2();
        ostringstream HN2_SS; HN2_SS << "h2_SS" << k;
        h2_SS.push_back(new TH1F (HN2_SS.str().c_str(),"InvMa",binnum2,bins2)); h2_SS[k]->Sumw2();
        ostringstream HN3_SS; HN3_SS << "h3_SS" << k;
        h3_SS.push_back(new TH1F (HN3_SS.str().c_str(),"InvMa",binnum3,bins3)); h3_SS[k]->Sumw2();
        ostringstream HN4_SS; HN4_SS << "h4_SS" << k;
        h4_SS.push_back(new TH1F (HN4_SS.str().c_str(),"InvMa",binnum4,bins4)); h4_SS[k]->Sumw2();
        ostringstream HN5_SS; HN5_SS << "h5_SS" << k;
        h5_SS.push_back(new TH1F (HN5_SS.str().c_str(),"InvMa",binnum5,bins5)); h5_SS[k]->Sumw2();
        ostringstream HN6_SS; HN6_SS << "h6_SS" << k;
        h6_SS.push_back(new TH1F (HN6_SS.str().c_str(),"InvMa",binnum6,bins6)); h6_SS[k]->Sumw2();
        ostringstream HN7_SS; HN7_SS << "h7_SS" << k;
        h7_SS.push_back(new TH1F (HN7_SS.str().c_str(),"InvMa",binnum7,bins7)); h7_SS[k]->Sumw2();

   }


   TString uncertainties[9]={"","_tauesDown","_tauesUp","_mesDown","_mesUp","_fesDown","_fesUp","_mvisresDown","_mvisresUp"};
   TString fake_uncertainties[1]={""};

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   auto b0_1=arbre->GetBranch("LHE_Njets");

   auto b1_1=arbre->GetBranch("LepCand_pt");
   auto b1_2=arbre->GetBranch("LepCand_eta");
   auto b1_3=arbre->GetBranch("LepCand_phi");
   auto b1_4=arbre->GetBranch("LepCand_id");
   auto b1_5=arbre->GetBranch("LepCand_gen");
   auto b1_6=arbre->GetBranch("nLepCand");
   auto b1_7=arbre->GetBranch("LepCand_taues");
   auto b1_8=arbre->GetBranch("LepCand_fes");
   auto b1_9=arbre->GetBranch("LepCand_taues_up");
   auto b1_10=arbre->GetBranch("LepCand_fes_up");
   auto b1_11=arbre->GetBranch("LepCand_taues_down");
   auto b1_12=arbre->GetBranch("LepCand_fes_down");

   auto b2_1=arbre->GetBranch("HLT_IsoMu24");
   auto b2_2=arbre->GetBranch("HLT_IsoTkMu24");
   auto b2_3=arbre->GetBranch("HLT_IsoMu27");

   auto b3_1=arbre->GetBranch("LepCand_vse");
   auto b3_2=arbre->GetBranch("LepCand_vsmu");
   auto b3_3=arbre->GetBranch("LepCand_vsjet");
   auto b3_4=arbre->GetBranch("LepCand_charge");
   auto b3_5=arbre->GetBranch("LepCand_muonIso");
   auto b3_6=arbre->GetBranch("LepCand_DecayMode");
   auto b3_7=arbre->GetBranch("LepCand_muonMediumId");

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("LepCand_tauidMsf");
   auto b4_4=arbre->GetBranch("LepCand_antielesf");
   auto b4_5=arbre->GetBranch("LepCand_antimusf");
   auto b4_6=arbre->GetBranch("LepCand_tautriggersf");
   auto b4_7=arbre->GetBranch("PV_npvs");
   auto b4_9=arbre->GetBranch("LepCand_antielesf_up");
   auto b4_10=arbre->GetBranch("LepCand_antimusf_up");
   auto b4_11=arbre->GetBranch("LepCand_tautriggersf_up");
   auto b4_13=arbre->GetBranch("LepCand_antielesf_down");
   auto b4_14=arbre->GetBranch("LepCand_antimusf_down");
   auto b4_15=arbre->GetBranch("LepCand_tautriggersf_down");
   auto b4_16=arbre->GetBranch("puWeight");
   auto b4_17=arbre->GetBranch("puWeightUp");
   auto b4_18=arbre->GetBranch("puWeightDown");
   auto b4_19=arbre->GetBranch("nGenCand");
   auto b4_20=arbre->GetBranch("GenCand_id");
   auto b4_21=arbre->GetBranch("GenCand_pt");
   auto b4_22=arbre->GetBranch("GenCand_eta");
   auto b4_23=arbre->GetBranch("GenCand_phi");


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
   auto b8_2=ami->GetBranch("ntracksAll_friend");
   auto b8_3=ami->GetBranch("ntracksHS_friend");
   auto b8_4=ami->GetBranch("ntracksPU_friend");


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
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }
   if (year=="2016post"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_ISO.root","read");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2016_UL_SingleMuonTriggers.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu24_or_IsoTkMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }
   if (year=="2017"){
      TFile* f_muonID=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root","read");
      TFile* f_muonIso=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_ISO.root","read");
      TFile* f_muonTrg=new TFile("scalefactors/Efficiencies_muon_generalTracks_Z_Run2017_UL_SingleMuonTriggers.root","read");
      h_muonIsoSF= (TH2F*) f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
      h_muonIDSF= (TH2F*) f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
      h_muonTrgSF= (TH2F*) f_muonTrg->Get("NUM_IsoMu27_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
   }

   TFile *f_punt=new TFile("corrs_ntracks_pu_UL2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("corr");

   TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");

   if (year=="2017"){
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2017.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2017.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   if (year=="2016pre"){
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_preVFP.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_preVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }
   if (year=="2016post"){
      TFile *f_punt=new TFile("corrs_ntracks_pu_UL2016_postVFP.root");
      correction_map=(TH2F*) f_punt->Get("corr");
      TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2016_postVFP.root");
      correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");
   }

   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        //arbre->GetEntry(i);
        if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
	
	if (name=="W"){
	  b0_1->GetEntry(i);
          if (sample=="W" and LHE_Njets==0) weight=luminosity*nnlo/LW;
          else if ((sample=="W" and LHE_Njets==1) or sample=="W1") weight=luminosity*nnlo/(LW+LW1);
          else if ((sample=="W" and LHE_Njets==2) or sample=="W2") weight=luminosity*nnlo/(LW+LW2);
          else if ((sample=="W" and LHE_Njets==3) or sample=="W3") weight=luminosity*nnlo/(LW+LW3);
          else if ((sample=="W" and LHE_Njets==4) or sample=="W4") weight=luminosity*nnlo/(LW+LW4);
	}

        b1_1->GetEntry(i); b1_2->GetEntry(i); b1_3->GetEntry(i); b1_4->GetEntry(i); b1_6->GetEntry(i);
        if (name!="data_obs") {b1_5->GetEntry(i); b1_7->GetEntry(i); b1_8->GetEntry(i);}
        if (name!="data_obs" and nbhist>1) {b1_9->GetEntry(i); b1_10->GetEntry(i); b1_11->GetEntry(i); b1_12->GetEntry(i); }

	int mu_index=-1;
	for (int j=0; j<nLepCand; ++j){
	   if (mu_index<0 and LepCand_id[j]==13) mu_index=j;
	}
        int tau_index=-1; float dz_tmp=10000;
        for (int j=0; j<nLepCand; ++j){
           if (LepCand_id[j]==15 and fabs(LepCand_dz[j]-LepCand_dz[mu_index])<dz_tmp){
	      tau_index=j; 
	      dz_tmp=fabs(LepCand_dz[j]-LepCand_dz[mu_index]);
	   }
        }
        TLorentzVector my_tau; my_tau.SetPtEtaPhiM(LepCand_pt[tau_index],LepCand_eta[tau_index],LepCand_phi[tau_index],0);
        TLorentzVector my_mu; my_mu.SetPtEtaPhiM(LepCand_pt[mu_index],LepCand_eta[mu_index],LepCand_phi[mu_index],0);

	if (name!="data_obs" and LepCand_gen[tau_index]==5) my_tau=my_tau*LepCand_taues[tau_index];
        if (name!="data_obs" and LepCand_gen[tau_index]>=1 and LepCand_gen[tau_index]<=4) my_tau=my_tau*LepCand_fes[tau_index];

	if (name=="ZTT" and LepCand_gen[tau_index]!=5) continue;
        if (name=="ZLL" and (LepCand_gen[tau_index]>4 or LepCand_gen[tau_index]<1)) continue;
        if (name=="ZJ" and LepCand_gen[tau_index]!=0 and LepCand_gen[tau_index]!=6) continue;

	if (fabs(my_tau.Eta())>2.3) continue;
        if (fabs(my_mu.Eta())>2.4) continue;
	if (my_tau.DeltaR(my_mu)<0.5) continue;

	// Trigger block

	bool is_mutrg=false;
	if (year=="2018"){
	   b2_1->GetEntry(i);
	   is_mutrg=(HLT_IsoMu24 and my_mu.Pt()>26);
	}
        if (year=="2017"){
           b2_3->GetEntry(i); 
           is_mutrg=(HLT_IsoMu27 and my_mu.Pt()>29);
        }
        if (year=="2016pre" or year=="2016post" or year=="2016"){
           b2_1->GetEntry(i); b2_2->GetEntry(i);
           is_mutrg=((HLT_IsoMu24 or HLT_IsoTkMu24) and my_mu.Pt()>26);
        }
	if (!is_mutrg) continue;

	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_6->GetEntry(i); b3_5->GetEntry(i); b3_7->GetEntry(i); 
	int dm=LepCand_DecayMode[tau_index];
	if (LepCand_vse[tau_index]<1 or LepCand_vsmu[tau_index]<15 or LepCand_vsjet[tau_index]<1) continue; 
	if (!LepCand_muonMediumId[mu_index] or LepCand_muonIso[mu_index]>0.20) continue;

	bool is_OS = (LepCand_charge[tau_index]*LepCand_charge[mu_index]<0);
	bool is_isolated = (LepCand_vsjet[tau_index]>=16);

	// Block weights
	if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_3->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_16->GetEntry(i); b4_17->GetEntry(i); b4_18->GetEntry(i);}
        if (name!="data_obs" and nbhist>1){ b4_9->GetEntry(i); b4_10->GetEntry(i); b4_11->GetEntry(i); b4_13->GetEntry(i); b4_14->GetEntry(i); b4_15->GetEntry(i);}
        if (name!="data_obs"){ b4_19->GetEntry(i); b4_20->GetEntry(i); b4_21->GetEntry(i); b4_22->GetEntry(i); b4_23->GetEntry(i);}

	b4_7->GetEntry(i);

	float aweight=1.0;
	float tauidSF=1.0;
	if (name!="data_obs"){
	   aweight=aweight*puWeight;
	   if (name!="W") aweight*=genWeight;
	   if (LepCand_gen[tau_index]==5) tauidSF=LepCand_tauidMsf[tau_index];
           if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*LepCand_antielesf[tau_index];
           if (LepCand_gen[tau_index]==2 or LepCand_gen[tau_index]==4) aweight=aweight*LepCand_antimusf[tau_index];

           float trgsf1=1.0;
           float recosf1=1.0;
           float idsf1=1.0;
           float muonIsoSF1=1.0;
           float mu1pt=my_mu.Pt();
           if (mu1pt>120) mu1pt=119;
           if (mu1pt<15) mu1pt=16;
           idsf1 = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu1pt));
           muonIsoSF1 = h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu1pt));
//cout<<mu1pt<<" "<<muonIsoSF1<<endl;
	   aweight*=idsf1*muonIsoSF1;

	   trgsf1 = h_muonTrgSF->GetBinContent(h_muonTrgSF->GetXaxis()->FindBin(fabs(my_mu.Eta())),h_muonTrgSF->GetYaxis()->FindBin(mu1pt));
//cout<<trgsf1<<endl;
           aweight*=trgsf1;

	}

	// Block MET
	b5_1->GetEntry(i); b5_2->GetEntry(i);
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(MET_pt,0,MET_phi,0);
	float mt = TMass_F(my_mu.Pt(), my_mu.Px(), my_mu.Py(), my_met.Pt(), my_met.Phi());


        float norm_zeta=norm_F(my_tau.Px()/my_tau.Pt()+my_mu.Px()/my_mu.Pt(),my_tau.Py()/my_tau.Pt()+my_mu.Py()/my_mu.Pt());
        float x_zeta= (my_tau.Px()/my_tau.Pt()+my_mu.Px()/my_mu.Pt())/norm_zeta;
        float y_zeta= (my_tau.Py()/my_tau.Pt()+my_mu.Py()/my_mu.Pt())/norm_zeta;
        float p_zeta_mis=my_met.Px()*x_zeta+my_met.Py()*y_zeta;
        float pzeta_vis=(my_tau.Px()+my_mu.Px())*x_zeta+(my_tau.Py()+my_mu.Py())*y_zeta;
        float dzeta=p_zeta_mis-0.85*pzeta_vis;

	// Block vertex
        b6_1->GetEntry(i); b6_3->GetEntry(i);
        if (name!="data_obs") b6_2->GetEntry(i);
	if (fabs(LepCand_dz[tau_index]-LepCand_dz[mu_index])>0.1) continue;
        float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[tau_index]+LepCand_dz[mu_index]);

	b8_1->GetEntry(i); b8_2->GetEntry(i); b8_3->GetEntry(i); b8_4->GetEntry(i);
	int ntracks=ntracks_friend;

        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntracksPU_friend;
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));}

        if (sample=="DY"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(0.1)); } //FIXME genaco

        float acoplanarity = (1.0 -fabs(my_mu.DeltaPhi(my_tau))/3.14159);

	TLorentzVector save_tau=my_tau;
        TLorentzVector save_mu=my_mu;
        TLorentzVector save_met=my_met;

        for (int k=0; k<nbhist; ++k){
           my_tau=save_tau;
	   my_mu=save_mu;
	   my_met=save_met;
	   float weight2=1.0;
           if (sample!="data_obs"){
              if (k==1 and LepCand_gen[tau_index]==5){my_tau=0.97*my_tau;}
              else if (k==2 and LepCand_gen[tau_index]==5){my_tau=1.03*my_tau;}
              else if (k==3){my_mu=0.99*my_mu;}
              else if (k==4){my_mu=1.01*my_mu;}
              else if (k==5 and LepCand_gen[tau_index]<5){my_tau=0.95*my_tau;}
              else if (k==6 and LepCand_gen[tau_index]<5){my_tau=1.05*my_tau;}
           }
           float mvis=(my_mu+my_tau).M();
           if (sample!="data_obs"){
              if (k==7 and LepCand_gen[tau_index]<5){mvis=0.8*(mvis-90)+90;}
              else if (k==8 and LepCand_gen[tau_index]<5){mvis=1.2*(mvis-90)+90;}
           }
	   if (mvis<50) continue;
	   if (my_tau.Pt()<30) continue;

           bool is_cat0=(mt<60 and dzeta>-25 and fabs(my_mu.Eta()-my_tau.Eta())<1.5 and ntracks<10 and ntracks>1);
           bool is_cat1=(mt<60 and dzeta>-25 and fabs(my_mu.Eta()-my_tau.Eta())<1.5);
           bool is_cat2=(mt>80 and ntracks<10 and ntracks>1);
           bool is_cat3=(mt>80);
           bool is_cat4=(my_mu.Pt()>35 and mt<50 and dzeta>-50 and fabs(my_mu.Eta()-my_tau.Eta())<1.5 and ntracks<10 and ntracks>1 and dm==0);
           bool is_cat5=(my_mu.Pt()>35 and mt>80 and ntracks<10 and ntracks>1 and dm==0);
           bool is_cat6=(my_mu.Pt()>35 and mt<50 and dzeta>-50 and fabs(my_mu.Eta()-my_tau.Eta())<1.5 and dm==0);
           bool is_cat7=(my_mu.Pt()>35 and mt>80 and dm==0);

	   float var0 = mvis;
           float var1 = mvis;
           float var2 = mt;
           float var3 = mt;
           float var4 = mvis;
           float var5 = mt;
           float var6 = mvis;
           float var7 = mt;

           float w_iso=weight*aweight*weight2*tauidSF;
	   if (is_OS and is_isolated){
	     if (is_cat0) h0[k]->Fill(var0,w_iso);
             if (is_cat1) h1[k]->Fill(var1,w_iso);
             if (is_cat2) h2[k]->Fill(var2,w_iso);
             if (is_cat3) h3[k]->Fill(var3,w_iso);
             if (is_cat4) h4[k]->Fill(var4,w_iso);
             if (is_cat5) h5[k]->Fill(var5,w_iso);
             if (is_cat6) h6[k]->Fill(var6,w_iso);
             if (is_cat7) h7[k]->Fill(var7,w_iso);
	   }

           if (!is_OS and is_isolated){
             if (is_cat0) h0_SS[k]->Fill(var0,w_iso*1.10);
             if (is_cat1) h1_SS[k]->Fill(var1,w_iso*1.10);
             if (is_cat2) h2_SS[k]->Fill(var2,w_iso*1.10);
             if (is_cat3) h3_SS[k]->Fill(var3,w_iso*1.10);
             if (is_cat4) h4_SS[k]->Fill(var4,w_iso*1.10);
             if (is_cat5) h5_SS[k]->Fill(var5,w_iso*1.10);
             if (is_cat6) h6_SS[k]->Fill(var6,w_iso*1.10);
             if (is_cat7) h7_SS[k]->Fill(var7,w_iso*1.10);
           }

	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    bool isMC=(name!="data_obs");
    WriteHistToFileTauID(fout, h0, name, "tauid_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h0_SS, name, "tauid_0_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h1, name, "tauid_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h1_SS, name, "tauid_1_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h2, name, "tauid_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h2_SS, name, "tauid_2_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h3, name, "tauid_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h3_SS, name, "tauid_3_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h4, name, "tauid_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h4_SS, name, "tauid_4_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h5, name, "tauid_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h5_SS, name, "tauid_5_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h6, name, "tauid_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h6_SS, name, "tauid_6_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h7, name, "tauid_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauID(fout, h7_SS, name, "tauid_7_SS", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    fout->Close();
} 


