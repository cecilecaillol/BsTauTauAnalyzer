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
#include "GetAcoWeight.h"

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
    else if (sample=="ZZ4L"){ xs=1.325; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Q"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2Q2L"){ xs=3.22; weight=luminosity*xs/ngen;}
    else if (sample=="WZ3LNu"){ xs=5.213; weight=luminosity*xs/ngen;}
    else if (sample=="VV2L2Nu"){ xs=11.09+0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WW2L2Nu"){ xs=11.09; weight=luminosity*xs/ngen;}//FIXME
    else if (sample=="WZ2L2Q"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2Q2L"){ xs=6.419; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=0.9738; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=39.65; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=134.2; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.0; weight=luminosity*xs/ngen;}
    //else if (sample=="GGTT"){ xs=0.669*0.0172; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    //else if (sample=="GGWW"){ xs=0.00692 * 0.368; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00692; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}
    //else if (sample=="GGTT_Ctb20"){ xs=1.118*0.0226; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT_Ctb20"){ xs=1.118*0.03915; weight=luminosity*xs/ngen;}
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
      //else if (sample=="GGMuMu") weight*=0.941;
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
    arbre->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight);
    arbre->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight);
    arbre->SetBranchAddress("PSWeight", &PSWeight);
    //arbre->SetBranchAddress("nJets", &nJets);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
    arbre->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
    arbre->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);

    arbre->SetBranchAddress("TauG2Weights_ceBIm_40p0", &TauG2Weights_ceBIm_40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_39p2", &TauG2Weights_ceBIm_39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_38p4", &TauG2Weights_ceBIm_38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_37p6", &TauG2Weights_ceBIm_37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_36p8", &TauG2Weights_ceBIm_36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_36p0", &TauG2Weights_ceBIm_36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_35p2", &TauG2Weights_ceBIm_35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_34p4", &TauG2Weights_ceBIm_34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_33p6", &TauG2Weights_ceBIm_33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_32p8", &TauG2Weights_ceBIm_32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_32p0", &TauG2Weights_ceBIm_32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_31p2", &TauG2Weights_ceBIm_31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_30p4", &TauG2Weights_ceBIm_30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_29p6", &TauG2Weights_ceBIm_29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_28p8", &TauG2Weights_ceBIm_28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_28p0", &TauG2Weights_ceBIm_28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_27p2", &TauG2Weights_ceBIm_27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_26p4", &TauG2Weights_ceBIm_26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_25p6", &TauG2Weights_ceBIm_25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_24p8", &TauG2Weights_ceBIm_24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_24p0", &TauG2Weights_ceBIm_24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_23p2", &TauG2Weights_ceBIm_23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_22p4", &TauG2Weights_ceBIm_22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_21p6", &TauG2Weights_ceBIm_21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_20p8", &TauG2Weights_ceBIm_20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_20p0", &TauG2Weights_ceBIm_20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_19p2", &TauG2Weights_ceBIm_19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_18p4", &TauG2Weights_ceBIm_18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_17p6", &TauG2Weights_ceBIm_17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_16p8", &TauG2Weights_ceBIm_16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_16p0", &TauG2Weights_ceBIm_16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_15p2", &TauG2Weights_ceBIm_15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_14p4", &TauG2Weights_ceBIm_14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_13p6", &TauG2Weights_ceBIm_13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_12p8", &TauG2Weights_ceBIm_12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_12p0", &TauG2Weights_ceBIm_12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_11p2", &TauG2Weights_ceBIm_11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_10p4", &TauG2Weights_ceBIm_10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_9p6", &TauG2Weights_ceBIm_9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_8p8", &TauG2Weights_ceBIm_8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_8p0", &TauG2Weights_ceBIm_8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_7p2", &TauG2Weights_ceBIm_7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_6p4", &TauG2Weights_ceBIm_6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_5p6", &TauG2Weights_ceBIm_5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_4p8", &TauG2Weights_ceBIm_4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_4p0", &TauG2Weights_ceBIm_4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_3p2", &TauG2Weights_ceBIm_3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_2p4", &TauG2Weights_ceBIm_2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_1p6", &TauG2Weights_ceBIm_1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_0p8", &TauG2Weights_ceBIm_0p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_0p0", &TauG2Weights_ceBIm_0p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m40p0", &TauG2Weights_ceBIm_m40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m39p2", &TauG2Weights_ceBIm_m39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m38p4", &TauG2Weights_ceBIm_m38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m37p6", &TauG2Weights_ceBIm_m37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m36p8", &TauG2Weights_ceBIm_m36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m36p0", &TauG2Weights_ceBIm_m36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m35p2", &TauG2Weights_ceBIm_m35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m34p4", &TauG2Weights_ceBIm_m34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m33p6", &TauG2Weights_ceBIm_m33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m32p8", &TauG2Weights_ceBIm_m32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m32p0", &TauG2Weights_ceBIm_m32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m31p2", &TauG2Weights_ceBIm_m31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m30p4", &TauG2Weights_ceBIm_m30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m29p6", &TauG2Weights_ceBIm_m29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m28p8", &TauG2Weights_ceBIm_m28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m28p0", &TauG2Weights_ceBIm_m28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m27p2", &TauG2Weights_ceBIm_m27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m26p4", &TauG2Weights_ceBIm_m26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m25p6", &TauG2Weights_ceBIm_m25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m24p8", &TauG2Weights_ceBIm_m24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m24p0", &TauG2Weights_ceBIm_m24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m23p2", &TauG2Weights_ceBIm_m23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m22p4", &TauG2Weights_ceBIm_m22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m21p6", &TauG2Weights_ceBIm_m21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m20p8", &TauG2Weights_ceBIm_m20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m20p0", &TauG2Weights_ceBIm_m20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m19p2", &TauG2Weights_ceBIm_m19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m18p4", &TauG2Weights_ceBIm_m18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m17p6", &TauG2Weights_ceBIm_m17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m16p8", &TauG2Weights_ceBIm_m16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m16p0", &TauG2Weights_ceBIm_m16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m15p2", &TauG2Weights_ceBIm_m15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m14p4", &TauG2Weights_ceBIm_m14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m13p6", &TauG2Weights_ceBIm_m13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m12p8", &TauG2Weights_ceBIm_m12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m12p0", &TauG2Weights_ceBIm_m12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m11p2", &TauG2Weights_ceBIm_m11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m10p4", &TauG2Weights_ceBIm_m10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m9p6", &TauG2Weights_ceBIm_m9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m8p8", &TauG2Weights_ceBIm_m8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m8p0", &TauG2Weights_ceBIm_m8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m7p2", &TauG2Weights_ceBIm_m7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m6p4", &TauG2Weights_ceBIm_m6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m5p6", &TauG2Weights_ceBIm_m5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m4p8", &TauG2Weights_ceBIm_m4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m4p0", &TauG2Weights_ceBIm_m4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m3p2", &TauG2Weights_ceBIm_m3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m2p4", &TauG2Weights_ceBIm_m2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m1p6", &TauG2Weights_ceBIm_m1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBIm_m0p8", &TauG2Weights_ceBIm_m0p8);

    arbre->SetBranchAddress("TauG2Weights_ceBRe_40p0", &TauG2Weights_ceBRe_40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_39p2", &TauG2Weights_ceBRe_39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_38p4", &TauG2Weights_ceBRe_38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_37p6", &TauG2Weights_ceBRe_37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_36p8", &TauG2Weights_ceBRe_36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_36p0", &TauG2Weights_ceBRe_36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_35p2", &TauG2Weights_ceBRe_35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_34p4", &TauG2Weights_ceBRe_34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_33p6", &TauG2Weights_ceBRe_33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_32p8", &TauG2Weights_ceBRe_32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_32p0", &TauG2Weights_ceBRe_32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_31p2", &TauG2Weights_ceBRe_31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_30p4", &TauG2Weights_ceBRe_30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_29p6", &TauG2Weights_ceBRe_29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_28p8", &TauG2Weights_ceBRe_28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_28p0", &TauG2Weights_ceBRe_28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_27p2", &TauG2Weights_ceBRe_27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_26p4", &TauG2Weights_ceBRe_26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_25p6", &TauG2Weights_ceBRe_25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_24p8", &TauG2Weights_ceBRe_24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_24p0", &TauG2Weights_ceBRe_24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_23p2", &TauG2Weights_ceBRe_23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_22p4", &TauG2Weights_ceBRe_22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_21p6", &TauG2Weights_ceBRe_21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_20p8", &TauG2Weights_ceBRe_20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_20p0", &TauG2Weights_ceBRe_20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_19p2", &TauG2Weights_ceBRe_19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_18p4", &TauG2Weights_ceBRe_18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_17p6", &TauG2Weights_ceBRe_17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_16p8", &TauG2Weights_ceBRe_16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_16p0", &TauG2Weights_ceBRe_16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_15p2", &TauG2Weights_ceBRe_15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_14p4", &TauG2Weights_ceBRe_14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_13p6", &TauG2Weights_ceBRe_13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_12p8", &TauG2Weights_ceBRe_12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_12p0", &TauG2Weights_ceBRe_12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_11p2", &TauG2Weights_ceBRe_11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_10p4", &TauG2Weights_ceBRe_10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_9p6", &TauG2Weights_ceBRe_9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_8p8", &TauG2Weights_ceBRe_8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_8p0", &TauG2Weights_ceBRe_8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_7p2", &TauG2Weights_ceBRe_7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_6p4", &TauG2Weights_ceBRe_6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_5p6", &TauG2Weights_ceBRe_5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_4p8", &TauG2Weights_ceBRe_4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_4p0", &TauG2Weights_ceBRe_4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_3p2", &TauG2Weights_ceBRe_3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_2p4", &TauG2Weights_ceBRe_2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_1p6", &TauG2Weights_ceBRe_1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_0p8", &TauG2Weights_ceBRe_0p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_0p0", &TauG2Weights_ceBRe_0p0);

    arbre->SetBranchAddress("TauG2Weights_ceBRe_m40p0", &TauG2Weights_ceBRe_m40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m39p2", &TauG2Weights_ceBRe_m39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m38p4", &TauG2Weights_ceBRe_m38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m37p6", &TauG2Weights_ceBRe_m37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m36p8", &TauG2Weights_ceBRe_m36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m36p0", &TauG2Weights_ceBRe_m36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m35p2", &TauG2Weights_ceBRe_m35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m34p4", &TauG2Weights_ceBRe_m34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m33p6", &TauG2Weights_ceBRe_m33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m32p8", &TauG2Weights_ceBRe_m32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m32p0", &TauG2Weights_ceBRe_m32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m31p2", &TauG2Weights_ceBRe_m31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m30p4", &TauG2Weights_ceBRe_m30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m29p6", &TauG2Weights_ceBRe_m29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m28p8", &TauG2Weights_ceBRe_m28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m28p0", &TauG2Weights_ceBRe_m28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m27p2", &TauG2Weights_ceBRe_m27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m26p4", &TauG2Weights_ceBRe_m26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m25p6", &TauG2Weights_ceBRe_m25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m24p8", &TauG2Weights_ceBRe_m24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m24p0", &TauG2Weights_ceBRe_m24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m23p2", &TauG2Weights_ceBRe_m23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m22p4", &TauG2Weights_ceBRe_m22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m21p6", &TauG2Weights_ceBRe_m21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m20p8", &TauG2Weights_ceBRe_m20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m20p0", &TauG2Weights_ceBRe_m20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m19p2", &TauG2Weights_ceBRe_m19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m18p4", &TauG2Weights_ceBRe_m18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m17p6", &TauG2Weights_ceBRe_m17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m16p8", &TauG2Weights_ceBRe_m16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m16p0", &TauG2Weights_ceBRe_m16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m15p2", &TauG2Weights_ceBRe_m15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m14p4", &TauG2Weights_ceBRe_m14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m13p6", &TauG2Weights_ceBRe_m13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m12p8", &TauG2Weights_ceBRe_m12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m12p0", &TauG2Weights_ceBRe_m12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m11p2", &TauG2Weights_ceBRe_m11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m10p4", &TauG2Weights_ceBRe_m10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m9p6", &TauG2Weights_ceBRe_m9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m8p8", &TauG2Weights_ceBRe_m8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m8p0", &TauG2Weights_ceBRe_m8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m7p2", &TauG2Weights_ceBRe_m7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m6p4", &TauG2Weights_ceBRe_m6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m5p6", &TauG2Weights_ceBRe_m5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m4p8", &TauG2Weights_ceBRe_m4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m4p0", &TauG2Weights_ceBRe_m4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m3p2", &TauG2Weights_ceBRe_m3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m2p4", &TauG2Weights_ceBRe_m2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m1p6", &TauG2Weights_ceBRe_m1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe_m0p8", &TauG2Weights_ceBRe_m0p8);


    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   int nbhist=1;
   int nbhist_offset=0;
   int nbhistMC=0;

   /*if (is_control==0 and name!="data_obs"){
        nbhist=1+22+30;
        nbhist_offset=0;
        nbhistMC=22;
   }
   if (is_control==0 and name=="data_obs"){
        nbhist=1+30;
        nbhist_offset=22;
        nbhistMC=22;
   }*/

   if (is_control==0){
      if (name=="data_obs"){
           nbhist=1+30;
           nbhist_offset=22;
           nbhistMC=22;
      }
      else if (sample=="DY" or sample=="DYemu"){
           nbhist=1+22+30+6+4+2;
           nbhist_offset=0;
           nbhistMC=22+6+4+2;
      }
      else{
           nbhist=1+22+30;
           nbhist_offset=0;
           nbhistMC=22;
      }
   }

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
   float bins1[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};//e pt
   float bins2[] = {10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};//tau pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//mu eta
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};//mt
   float bins7[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};//ntracks
   float bins8[] = {0,0.025,0.05,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6,0.625,0.65,0.675,0.7,0.725,0.75,0.775,0.8,0.825,0.85,0.875,0.9,0.925,0.95,0.975,1.0};//acoplanarity*/

   // Signal region
   float bins0[] = {40,55,70,85,100,150,200};//mvis
   float bins1[] = {40,55,70,85,100,150,200};//mvis
   //float bins0[] = {30,45,60,75,90,105,120,150,180,210};
   //float bins1[] = {30,45,60,75,90,105,120,150,180,210};
   float bins2[] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};//mvis
   float bins3[] = {0.0,0.015,0.03,0.045,0.06,0.1,0.20,0.50,1.0};//mvis
   float bins4[] = {0,1,2,3,4,5,6,7,8,9,10};//mvis
   float bins5[] = {0,1,2,3,4,5,6,7,8,9,10};//mvis
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

   float bins_taupt[] = {15,24,35,45,55};
   int  binnum_taupt = sizeof(bins_taupt)/sizeof(Float_t) - 1;
   float bins_nt[] = {-1,0,2,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   int  binnum_nt = sizeof(bins_nt)/sizeof(Float_t) - 1;
   TH2F *h_fr_iso=new TH2F("h_fr_iso","h_fr_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_fr_iso->Sumw2();
   TH2F *h_fr_anti=new TH2F("h_fr_anti","h_fr_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_fr_anti->Sumw2();
   TH2F *h_frlow_iso=new TH2F("h_frlow_iso","h_frlow_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frlow_iso->Sumw2();
   TH2F *h_frlow_anti=new TH2F("h_frlow_anti","h_frlow_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frlow_anti->Sumw2();
   TH2F *h_frhigh_iso=new TH2F("h_frhigh_iso","h_frhigh_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frhigh_iso->Sumw2();
   TH2F *h_frhigh_anti=new TH2F("h_frhigh_anti","h_frhigh_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frhigh_anti->Sumw2();
   TH1F *h_frnt_iso=new TH1F("h_frnt_iso","h_frnt_iso",binnum_nt,bins_nt); h_frnt_iso->Sumw2();
   TH1F *h_frnt_anti=new TH1F("h_frnt_anti","h_frnt_anti",binnum_nt,bins_nt); h_frnt_anti->Sumw2();
   TH2F *h_frFP_iso=new TH2F("h_frFP_iso","h_frFP_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFP_iso->Sumw2();
   TH2F *h_frFP_anti=new TH2F("h_frFP_anti","h_frFP_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFP_anti->Sumw2();
   TH2F *h_frFF_iso=new TH2F("h_frFF_iso","h_frFF_iso",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFF_iso->Sumw2();
   TH2F *h_frFF_anti=new TH2F("h_frFF_anti","h_frFF_anti",binnum_taupt,bins_taupt,binnum_taupt,bins_taupt); h_frFF_anti->Sumw2();

   TString uncertainties[35]={"","_CMS_pileup_yearDown","_CMS_pileup_yearUp","_CMS_emutrg_lowmuhighe_systDown","_CMS_emutrg_lowmuhighe_systUp","_CMS_emutrg_highmulowe_systDown","_CMS_emutrg_highmulowe_systUp","_CMS_emutrg_highmuhighe_systDown","_CMS_emutrg_highmuhighe_systUp","_CMS_elasticRescalingDown","_CMS_elasticRescalingUp","_CMS_L1PrefiringDown","_CMS_L1PrefiringUp","_CMS_muId_systDown","_CMS_muId_systUp","_CMS_muId_stat_yearDown","_CMS_muId_stat_yearUp","_CMS_muIso_systDown","_CMS_muIso_systUp","_CMS_muIso_stat_yearDown","_CMS_muIso_stat_yearUp","_CMS_elId_systDown","_CMS_elId_systUp","_CMS_ISRDown","_CMS_ISRUp","_CMS_FSRDown","_CMS_FSRUp","_CMS_PDFDown","_CMS_PDFUp","_CMS_muR0p5_muF0p5","_CMS_muRDown","_CMS_muFDown","_CMS_muFUp","_CMS_muRUp","_CMS_muR2p0_muF2p0"};

   for (int k = 0; k < 23; ++k){
      if (year=="2016pre") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016preVFP");
      if (year=="2016post") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016postVFP");
      if (year=="2017") uncertainties[k]=uncertainties[k].ReplaceAll("year","2017");
      if (year=="2018") uncertainties[k]=uncertainties[k].ReplaceAll("year","2018");
   }


   TString fake_uncertainties[30]={"_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_yearDown","_CMS_fakebkg_emu_stat_pte15to24_ptmu24to35_yearUp","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_yearDown","_CMS_fakebkg_emu_stat_pte15to24_ptmu35to45_yearUp","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_yearDown","_CMS_fakebkg_emu_stat_pte15to24_ptmugt45_yearUp","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_yearDown","_CMS_fakebkg_emu_stat_pte24to35_ptmu15to24_yearUp","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_yearDown","_CMS_fakebkg_emu_stat_pte24to35_ptmu24to35_yearUp","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_yearDown","_CMS_fakebkg_emu_stat_pte24to35_ptmu35to45_yearUp","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_yearDown","_CMS_fakebkg_emu_stat_pte24to35_ptmugt45_yearUp","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_yearDown","_CMS_fakebkg_emu_stat_pte35to45_ptmu15to24_yearUp","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_yearDown","_CMS_fakebkg_emu_stat_pte35to45_ptmu24to35_yearUp","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_yearDown","_CMS_fakebkg_emu_stat_pte35to45_ptmu35to45_yearUp","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_yearDown","_CMS_fakebkg_emu_stat_pte35to45_ptmugt45_yearUp","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_yearDown","_CMS_fakebkg_emu_stat_ptegt45_ptmu15to24_yearUp","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_yearDown","_CMS_fakebkg_emu_stat_ptegt45_ptmu24to35_yearUp","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_yearDown","_CMS_fakebkg_emu_stat_ptegt45_ptmu35to45_yearUp","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_yearDown","_CMS_fakebkg_emu_stat_ptegt45_ptmugt45_yearUp"};

   for (int k = 0; k < 30; ++k){
      if (year=="2016pre") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2016preVFP");
      if (year=="2016post") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2016postVFP");
      if (year=="2017") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2017");
      if (year=="2018") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2018");
   }

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

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpleditau = new TH1F("h_vtxresolution_simpleditau","h_vtxresolution_simpleditau",200,-1,1); h_vtxresolution_simpleditau->Sumw2();
   TH1F* h_ntracks = new TH1F("h_ntracks","h_ntracks",30,0,30); h_ntracks->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   TH1F* h_acoreso=new TH1F("h_acoreso","h_acoreso",100,0,0.1);
   TH1F* h_acoreso_high=new TH1F("h_acoreso_high","h_acoreso_high",100,0,0.1);

   TH1F* h_nHS=new TH1F("h_nHS","h_nHS",70,0,70);

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
   auto b4_15=arbre->GetBranch("LHEPdfWeight");
   auto b4_16=arbre->GetBranch("LHEScaleWeight");
   auto b4_17=arbre->GetBranch("PSWeight");


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

   auto b9_1=arbre->GetBranch("TauG2Weights_ceBRe_0p0");
   auto b9_2=arbre->GetBranch("TauG2Weights_ceBRe_0p8");
   auto b9_3=arbre->GetBranch("TauG2Weights_ceBRe_1p6");
   auto b9_4=arbre->GetBranch("TauG2Weights_ceBRe_2p4");
   auto b9_5=arbre->GetBranch("TauG2Weights_ceBRe_3p2");
   auto b9_6=arbre->GetBranch("TauG2Weights_ceBRe_4p0");
   auto b9_7=arbre->GetBranch("TauG2Weights_ceBRe_4p8");
   auto b9_8=arbre->GetBranch("TauG2Weights_ceBRe_5p6");
   auto b9_9=arbre->GetBranch("TauG2Weights_ceBRe_6p4");
   auto b9_10=arbre->GetBranch("TauG2Weights_ceBRe_7p2");
   auto b9_11=arbre->GetBranch("TauG2Weights_ceBRe_8p0");
   auto b9_12=arbre->GetBranch("TauG2Weights_ceBRe_8p8");
   auto b9_13=arbre->GetBranch("TauG2Weights_ceBRe_9p6");
   auto b9_14=arbre->GetBranch("TauG2Weights_ceBRe_10p4");
   auto b9_15=arbre->GetBranch("TauG2Weights_ceBRe_11p2");
   auto b9_16=arbre->GetBranch("TauG2Weights_ceBRe_12p0");
   auto b9_17=arbre->GetBranch("TauG2Weights_ceBRe_12p8");
   auto b9_18=arbre->GetBranch("TauG2Weights_ceBRe_13p6");
   auto b9_19=arbre->GetBranch("TauG2Weights_ceBRe_14p4");
   auto b9_20=arbre->GetBranch("TauG2Weights_ceBRe_15p2");
   auto b9_21=arbre->GetBranch("TauG2Weights_ceBRe_16p0");
   auto b9_22=arbre->GetBranch("TauG2Weights_ceBRe_16p8");
   auto b9_23=arbre->GetBranch("TauG2Weights_ceBRe_17p6");
   auto b9_24=arbre->GetBranch("TauG2Weights_ceBRe_18p4");
   auto b9_25=arbre->GetBranch("TauG2Weights_ceBRe_19p2");
   auto b9_26=arbre->GetBranch("TauG2Weights_ceBRe_20p0");
   auto b9_27=arbre->GetBranch("TauG2Weights_ceBRe_20p8");
   auto b9_28=arbre->GetBranch("TauG2Weights_ceBRe_21p6");
   auto b9_29=arbre->GetBranch("TauG2Weights_ceBRe_22p4");
   auto b9_30=arbre->GetBranch("TauG2Weights_ceBRe_23p2");
   auto b9_31=arbre->GetBranch("TauG2Weights_ceBRe_24p0");
   auto b9_32=arbre->GetBranch("TauG2Weights_ceBRe_24p8");
   auto b9_33=arbre->GetBranch("TauG2Weights_ceBRe_25p6");
   auto b9_34=arbre->GetBranch("TauG2Weights_ceBRe_26p4");
   auto b9_35=arbre->GetBranch("TauG2Weights_ceBRe_27p2");
   auto b9_36=arbre->GetBranch("TauG2Weights_ceBRe_28p0");
   auto b9_37=arbre->GetBranch("TauG2Weights_ceBRe_28p8");
   auto b9_38=arbre->GetBranch("TauG2Weights_ceBRe_29p6");
   auto b9_39=arbre->GetBranch("TauG2Weights_ceBRe_30p4");
   auto b9_40=arbre->GetBranch("TauG2Weights_ceBRe_31p2");
   auto b9_41=arbre->GetBranch("TauG2Weights_ceBRe_32p0");
   auto b9_42=arbre->GetBranch("TauG2Weights_ceBRe_32p8");
   auto b9_43=arbre->GetBranch("TauG2Weights_ceBRe_33p6");
   auto b9_44=arbre->GetBranch("TauG2Weights_ceBRe_34p4");
   auto b9_45=arbre->GetBranch("TauG2Weights_ceBRe_35p2");
   auto b9_46=arbre->GetBranch("TauG2Weights_ceBRe_36p0");
   auto b9_47=arbre->GetBranch("TauG2Weights_ceBRe_36p8");
   auto b9_48=arbre->GetBranch("TauG2Weights_ceBRe_37p6");
   auto b9_49=arbre->GetBranch("TauG2Weights_ceBRe_38p4");
   auto b9_50=arbre->GetBranch("TauG2Weights_ceBRe_39p2");
   auto b9_51=arbre->GetBranch("TauG2Weights_ceBRe_40p0");
   auto b9_52=arbre->GetBranch("TauG2Weights_ceBRe_m0p8");
   auto b9_53=arbre->GetBranch("TauG2Weights_ceBRe_m1p6");
   auto b9_54=arbre->GetBranch("TauG2Weights_ceBRe_m2p4");
   auto b9_55=arbre->GetBranch("TauG2Weights_ceBRe_m3p2");
   auto b9_56=arbre->GetBranch("TauG2Weights_ceBRe_m4p0");
   auto b9_57=arbre->GetBranch("TauG2Weights_ceBRe_m4p8");
   auto b9_58=arbre->GetBranch("TauG2Weights_ceBRe_m5p6");
   auto b9_59=arbre->GetBranch("TauG2Weights_ceBRe_m6p4");
   auto b9_60=arbre->GetBranch("TauG2Weights_ceBRe_m7p2");
   auto b9_61=arbre->GetBranch("TauG2Weights_ceBRe_m8p0");
   auto b9_62=arbre->GetBranch("TauG2Weights_ceBRe_m8p8");
   auto b9_63=arbre->GetBranch("TauG2Weights_ceBRe_m9p6");
   auto b9_64=arbre->GetBranch("TauG2Weights_ceBRe_m10p4");
   auto b9_65=arbre->GetBranch("TauG2Weights_ceBRe_m11p2");
   auto b9_66=arbre->GetBranch("TauG2Weights_ceBRe_m12p0");
   auto b9_67=arbre->GetBranch("TauG2Weights_ceBRe_m12p8");
   auto b9_68=arbre->GetBranch("TauG2Weights_ceBRe_m13p6");
   auto b9_69=arbre->GetBranch("TauG2Weights_ceBRe_m14p4");
   auto b9_70=arbre->GetBranch("TauG2Weights_ceBRe_m15p2");
   auto b9_71=arbre->GetBranch("TauG2Weights_ceBRe_m16p0");
   auto b9_72=arbre->GetBranch("TauG2Weights_ceBRe_m16p8");
   auto b9_73=arbre->GetBranch("TauG2Weights_ceBRe_m17p6");
   auto b9_74=arbre->GetBranch("TauG2Weights_ceBRe_m18p4");
   auto b9_75=arbre->GetBranch("TauG2Weights_ceBRe_m19p2");
   auto b9_76=arbre->GetBranch("TauG2Weights_ceBRe_m20p0");
   auto b9_77=arbre->GetBranch("TauG2Weights_ceBRe_m20p8");
   auto b9_78=arbre->GetBranch("TauG2Weights_ceBRe_m21p6");
   auto b9_79=arbre->GetBranch("TauG2Weights_ceBRe_m22p4");
   auto b9_80=arbre->GetBranch("TauG2Weights_ceBRe_m23p2");
   auto b9_81=arbre->GetBranch("TauG2Weights_ceBRe_m24p0");
   auto b9_82=arbre->GetBranch("TauG2Weights_ceBRe_m24p8");
   auto b9_83=arbre->GetBranch("TauG2Weights_ceBRe_m25p6");
   auto b9_84=arbre->GetBranch("TauG2Weights_ceBRe_m26p4");
   auto b9_85=arbre->GetBranch("TauG2Weights_ceBRe_m27p2");
   auto b9_86=arbre->GetBranch("TauG2Weights_ceBRe_m28p0");
   auto b9_87=arbre->GetBranch("TauG2Weights_ceBRe_m28p8");
   auto b9_88=arbre->GetBranch("TauG2Weights_ceBRe_m29p6");
   auto b9_89=arbre->GetBranch("TauG2Weights_ceBRe_m30p4");
   auto b9_90=arbre->GetBranch("TauG2Weights_ceBRe_m31p2");
   auto b9_91=arbre->GetBranch("TauG2Weights_ceBRe_m32p0");
   auto b9_92=arbre->GetBranch("TauG2Weights_ceBRe_m32p8");
   auto b9_93=arbre->GetBranch("TauG2Weights_ceBRe_m33p6");
   auto b9_94=arbre->GetBranch("TauG2Weights_ceBRe_m34p4");
   auto b9_95=arbre->GetBranch("TauG2Weights_ceBRe_m35p2");
   auto b9_96=arbre->GetBranch("TauG2Weights_ceBRe_m36p0");
   auto b9_97=arbre->GetBranch("TauG2Weights_ceBRe_m36p8");
   auto b9_98=arbre->GetBranch("TauG2Weights_ceBRe_m37p6");
   auto b9_99=arbre->GetBranch("TauG2Weights_ceBRe_m38p4");
   auto b9_100=arbre->GetBranch("TauG2Weights_ceBRe_m39p2");
   auto b9_101=arbre->GetBranch("TauG2Weights_ceBRe_m40p0");

   auto b10_1=arbre->GetBranch("TauG2Weights_ceBIm_0p0");
   auto b10_2=arbre->GetBranch("TauG2Weights_ceBIm_0p8");
   auto b10_3=arbre->GetBranch("TauG2Weights_ceBIm_1p6");
   auto b10_4=arbre->GetBranch("TauG2Weights_ceBIm_2p4");
   auto b10_5=arbre->GetBranch("TauG2Weights_ceBIm_3p2");
   auto b10_6=arbre->GetBranch("TauG2Weights_ceBIm_4p0");
   auto b10_7=arbre->GetBranch("TauG2Weights_ceBIm_4p8");
   auto b10_8=arbre->GetBranch("TauG2Weights_ceBIm_5p6");
   auto b10_9=arbre->GetBranch("TauG2Weights_ceBIm_6p4");
   auto b10_10=arbre->GetBranch("TauG2Weights_ceBIm_7p2");
   auto b10_11=arbre->GetBranch("TauG2Weights_ceBIm_8p0");
   auto b10_12=arbre->GetBranch("TauG2Weights_ceBIm_8p8");
   auto b10_13=arbre->GetBranch("TauG2Weights_ceBIm_9p6");
   auto b10_14=arbre->GetBranch("TauG2Weights_ceBIm_10p4");
   auto b10_15=arbre->GetBranch("TauG2Weights_ceBIm_11p2");
   auto b10_16=arbre->GetBranch("TauG2Weights_ceBIm_12p0");
   auto b10_17=arbre->GetBranch("TauG2Weights_ceBIm_12p8");
   auto b10_18=arbre->GetBranch("TauG2Weights_ceBIm_13p6");
   auto b10_19=arbre->GetBranch("TauG2Weights_ceBIm_14p4");
   auto b10_20=arbre->GetBranch("TauG2Weights_ceBIm_15p2");
   auto b10_21=arbre->GetBranch("TauG2Weights_ceBIm_16p0");
   auto b10_22=arbre->GetBranch("TauG2Weights_ceBIm_16p8");
   auto b10_23=arbre->GetBranch("TauG2Weights_ceBIm_17p6");
   auto b10_24=arbre->GetBranch("TauG2Weights_ceBIm_18p4");
   auto b10_25=arbre->GetBranch("TauG2Weights_ceBIm_19p2");
   auto b10_26=arbre->GetBranch("TauG2Weights_ceBIm_20p0");
   auto b10_27=arbre->GetBranch("TauG2Weights_ceBIm_20p8");
   auto b10_28=arbre->GetBranch("TauG2Weights_ceBIm_21p6");
   auto b10_29=arbre->GetBranch("TauG2Weights_ceBIm_22p4");
   auto b10_30=arbre->GetBranch("TauG2Weights_ceBIm_23p2");
   auto b10_31=arbre->GetBranch("TauG2Weights_ceBIm_24p0");
   auto b10_32=arbre->GetBranch("TauG2Weights_ceBIm_24p8");
   auto b10_33=arbre->GetBranch("TauG2Weights_ceBIm_25p6");
   auto b10_34=arbre->GetBranch("TauG2Weights_ceBIm_26p4");
   auto b10_35=arbre->GetBranch("TauG2Weights_ceBIm_27p2");
   auto b10_36=arbre->GetBranch("TauG2Weights_ceBIm_28p0");
   auto b10_37=arbre->GetBranch("TauG2Weights_ceBIm_28p8");
   auto b10_38=arbre->GetBranch("TauG2Weights_ceBIm_29p6");
   auto b10_39=arbre->GetBranch("TauG2Weights_ceBIm_30p4");
   auto b10_40=arbre->GetBranch("TauG2Weights_ceBIm_31p2");
   auto b10_41=arbre->GetBranch("TauG2Weights_ceBIm_32p0");
   auto b10_42=arbre->GetBranch("TauG2Weights_ceBIm_32p8");
   auto b10_43=arbre->GetBranch("TauG2Weights_ceBIm_33p6");
   auto b10_44=arbre->GetBranch("TauG2Weights_ceBIm_34p4");
   auto b10_45=arbre->GetBranch("TauG2Weights_ceBIm_35p2");
   auto b10_46=arbre->GetBranch("TauG2Weights_ceBIm_36p0");
   auto b10_47=arbre->GetBranch("TauG2Weights_ceBIm_36p8");
   auto b10_48=arbre->GetBranch("TauG2Weights_ceBIm_37p6");
   auto b10_49=arbre->GetBranch("TauG2Weights_ceBIm_38p4");
   auto b10_50=arbre->GetBranch("TauG2Weights_ceBIm_39p2");
   auto b10_51=arbre->GetBranch("TauG2Weights_ceBIm_40p0");
   auto b10_52=arbre->GetBranch("TauG2Weights_ceBIm_m0p8");
   auto b10_53=arbre->GetBranch("TauG2Weights_ceBIm_m1p6");
   auto b10_54=arbre->GetBranch("TauG2Weights_ceBIm_m2p4");
   auto b10_55=arbre->GetBranch("TauG2Weights_ceBIm_m3p2");
   auto b10_56=arbre->GetBranch("TauG2Weights_ceBIm_m4p0");
   auto b10_57=arbre->GetBranch("TauG2Weights_ceBIm_m4p8");
   auto b10_58=arbre->GetBranch("TauG2Weights_ceBIm_m5p6");
   auto b10_59=arbre->GetBranch("TauG2Weights_ceBIm_m6p4");
   auto b10_60=arbre->GetBranch("TauG2Weights_ceBIm_m7p2");
   auto b10_61=arbre->GetBranch("TauG2Weights_ceBIm_m8p0");
   auto b10_62=arbre->GetBranch("TauG2Weights_ceBIm_m8p8");
   auto b10_63=arbre->GetBranch("TauG2Weights_ceBIm_m9p6");
   auto b10_64=arbre->GetBranch("TauG2Weights_ceBIm_m10p4");
   auto b10_65=arbre->GetBranch("TauG2Weights_ceBIm_m11p2");
   auto b10_66=arbre->GetBranch("TauG2Weights_ceBIm_m12p0");
   auto b10_67=arbre->GetBranch("TauG2Weights_ceBIm_m12p8");
   auto b10_68=arbre->GetBranch("TauG2Weights_ceBIm_m13p6");
   auto b10_69=arbre->GetBranch("TauG2Weights_ceBIm_m14p4");
   auto b10_70=arbre->GetBranch("TauG2Weights_ceBIm_m15p2");
   auto b10_71=arbre->GetBranch("TauG2Weights_ceBIm_m16p0");
   auto b10_72=arbre->GetBranch("TauG2Weights_ceBIm_m16p8");
   auto b10_73=arbre->GetBranch("TauG2Weights_ceBIm_m17p6");
   auto b10_74=arbre->GetBranch("TauG2Weights_ceBIm_m18p4");
   auto b10_75=arbre->GetBranch("TauG2Weights_ceBIm_m19p2");
   auto b10_76=arbre->GetBranch("TauG2Weights_ceBIm_m20p0");
   auto b10_77=arbre->GetBranch("TauG2Weights_ceBIm_m20p8");
   auto b10_78=arbre->GetBranch("TauG2Weights_ceBIm_m21p6");
   auto b10_79=arbre->GetBranch("TauG2Weights_ceBIm_m22p4");
   auto b10_80=arbre->GetBranch("TauG2Weights_ceBIm_m23p2");
   auto b10_81=arbre->GetBranch("TauG2Weights_ceBIm_m24p0");
   auto b10_82=arbre->GetBranch("TauG2Weights_ceBIm_m24p8");
   auto b10_83=arbre->GetBranch("TauG2Weights_ceBIm_m25p6");
   auto b10_84=arbre->GetBranch("TauG2Weights_ceBIm_m26p4");
   auto b10_85=arbre->GetBranch("TauG2Weights_ceBIm_m27p2");
   auto b10_86=arbre->GetBranch("TauG2Weights_ceBIm_m28p0");
   auto b10_87=arbre->GetBranch("TauG2Weights_ceBIm_m28p8");
   auto b10_88=arbre->GetBranch("TauG2Weights_ceBIm_m29p6");
   auto b10_89=arbre->GetBranch("TauG2Weights_ceBIm_m30p4");
   auto b10_90=arbre->GetBranch("TauG2Weights_ceBIm_m31p2");
   auto b10_91=arbre->GetBranch("TauG2Weights_ceBIm_m32p0");
   auto b10_92=arbre->GetBranch("TauG2Weights_ceBIm_m32p8");
   auto b10_93=arbre->GetBranch("TauG2Weights_ceBIm_m33p6");
   auto b10_94=arbre->GetBranch("TauG2Weights_ceBIm_m34p4");
   auto b10_95=arbre->GetBranch("TauG2Weights_ceBIm_m35p2");
   auto b10_96=arbre->GetBranch("TauG2Weights_ceBIm_m36p0");
   auto b10_97=arbre->GetBranch("TauG2Weights_ceBIm_m36p8");
   auto b10_98=arbre->GetBranch("TauG2Weights_ceBIm_m37p6");
   auto b10_99=arbre->GetBranch("TauG2Weights_ceBIm_m38p4");
   auto b10_100=arbre->GetBranch("TauG2Weights_ceBIm_m39p2");
   auto b10_101=arbre->GetBranch("TauG2Weights_ceBIm_m40p0");

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

   TH1F* h_DY_ABCD=new TH1F("h_DY_ABCD","h_DY_ABCD",6,0,6); h_DY_ABCD->Sumw2();

   TH1F* h_acoplanarity = new TH1F("h_acoplanarity","h_acoplanarity",25,0.0,0.025);
   TH1F* h_acoplanarity_sumptlt100 = new TH1F("h_acoplanarity_sumptlt100","h_acoplanarity_sumptlt100",25,0.0,0.025);
   TH1F* h_acoplanarity_sumptgt100 = new TH1F("h_acoplanarity_sumptgt100","h_acoplanarity_sumptgt100",25,0.0,0.025);

   TH1F* h_resolution_acoplanarity = new TH1F("h_resolution_acoplanarity","h_resolution_acoplanarity",30,-0.01,0.02);
   TH1F* h_resolution_acoplanarity_sumptlt100 = new TH1F("h_resolution_acoplanarity_sumptlt100","h_resolution_acoplanarity_sumptlt100",30,-0.01,0.02);
   TH1F* h_resolution_acoplanarity_sumptgt100 = new TH1F("h_resolution_acoplanarity_sumptgt100","h_resolution_acoplanarity_sumptgt100",30,-0.01,0.02);

   TH1F* h_mvis_nt0 = new TH1F("h_mvis_nt0","h_mvis_nt0",20,0,200);
   TH1F* h_mvis_nt0to10 = new TH1F("h_mvis_nt0to10","h_mvis_nt0to10",20,0,200);

   TH1F* h_dz = new TH1F("h_dz","h_dz",32,0.0,0.4); h_dz->Sumw2();

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
	if (sample=="DY" or sample=="DYemu"){b4_15->GetEntry(i); b4_16->GetEntry(i); b4_17->GetEntry(i);}
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
        float weight_aco=1.0;

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

           weight_aco=1.0;
           if (sample=="DY" or name=="ZTT" or name=="ZLL" or sample=="DYemu"){
	      weight_aco=GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 0, year);
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
        float mydz=fabs(LepCand_dz[mu_index]-LepCand_dz[ele_index]);
        if (mydz>0.4) mydz=0.399;
        if (is_isolated and is_OS) h_dz->Fill(mydz,weight*aweight);

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
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));}  //FIXME Ben

        if (sample=="DYemu" or sample=="DY" or sample=="DYcondor" or sample=="VV2L2Nu"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); } //FIXME Ben


        h_acoreso->Fill(fabs(gen_aco-acoplanarity));
	if (my_mu.Pt()>30 and my_ele.Pt()>30) h_acoreso_high->Fill(fabs(gen_aco-acoplanarity));


	TLorentzVector save_mu=my_mu;
        TLorentzVector save_ele=my_ele;
        TLorentzVector save_met=my_met;

	bool is_lowA=true;
	if (is_control==0) is_lowA=(acoplanarity<0.015); 

        if (sample=="GGWW"){ // rescaling from mumu region
           if (ntracks==0) aweight*=(2.433+0.00152*gen_mtt);
           else if (ntracks==1) aweight*=(2.52+0.0011*gen_mtt);
	}

        if (sample=="GGTT" or sample=="GGTT_Ctb20"){ // rescaling from mumu region
           if (ntracks==0) aweight*=(2.433+0.00152*gen_mtt);
           else if (ntracks==1) aweight*=(2.52+0.0011*gen_mtt);
           b9_1->GetEntry(i); b9_2->GetEntry(i); b9_3->GetEntry(i);b9_4->GetEntry(i); b9_5->GetEntry(i); b9_6->GetEntry(i);b9_7->GetEntry(i); b9_8->GetEntry(i); b9_9->GetEntry(i);
           b9_10->GetEntry(i); b9_11->GetEntry(i); b9_12->GetEntry(i); b9_13->GetEntry(i);b9_14->GetEntry(i); b9_15->GetEntry(i); b9_16->GetEntry(i);b9_17->GetEntry(i); b9_18->GetEntry(i); b9_19->GetEntry(i);
           b9_20->GetEntry(i); b9_21->GetEntry(i); b9_22->GetEntry(i); b9_23->GetEntry(i);b9_24->GetEntry(i); b9_25->GetEntry(i); b9_26->GetEntry(i);b9_27->GetEntry(i); b9_28->GetEntry(i); b9_29->GetEntry(i);
           b9_30->GetEntry(i); b9_31->GetEntry(i); b9_32->GetEntry(i); b9_33->GetEntry(i);b9_34->GetEntry(i); b9_35->GetEntry(i); b9_36->GetEntry(i);b9_37->GetEntry(i); b9_38->GetEntry(i); b9_39->GetEntry(i);
           b9_40->GetEntry(i); b9_41->GetEntry(i); b9_42->GetEntry(i); b9_43->GetEntry(i);b9_44->GetEntry(i); b9_45->GetEntry(i); b9_46->GetEntry(i);b9_47->GetEntry(i); b9_48->GetEntry(i); b9_49->GetEntry(i);
           b9_50->GetEntry(i); b9_51->GetEntry(i); b9_52->GetEntry(i); b9_53->GetEntry(i);b9_54->GetEntry(i); b9_55->GetEntry(i); b9_56->GetEntry(i);b9_57->GetEntry(i); b9_58->GetEntry(i); b9_59->GetEntry(i);
           b9_60->GetEntry(i); b9_61->GetEntry(i); b9_62->GetEntry(i); b9_63->GetEntry(i);b9_64->GetEntry(i); b9_65->GetEntry(i); b9_66->GetEntry(i);b9_67->GetEntry(i); b9_68->GetEntry(i); b9_69->GetEntry(i);
           b9_70->GetEntry(i); b9_71->GetEntry(i); b9_72->GetEntry(i); b9_73->GetEntry(i);b9_74->GetEntry(i); b9_75->GetEntry(i); b9_76->GetEntry(i);b9_77->GetEntry(i); b9_78->GetEntry(i); b9_79->GetEntry(i);
           b9_80->GetEntry(i); b9_81->GetEntry(i); b9_82->GetEntry(i); b9_83->GetEntry(i);b9_84->GetEntry(i); b9_85->GetEntry(i); b9_86->GetEntry(i);b9_87->GetEntry(i); b9_88->GetEntry(i); b9_89->GetEntry(i);
           b9_90->GetEntry(i); b9_91->GetEntry(i); b9_92->GetEntry(i); b9_93->GetEntry(i);b9_94->GetEntry(i); b9_95->GetEntry(i); b9_96->GetEntry(i);b9_97->GetEntry(i); b9_98->GetEntry(i); b9_99->GetEntry(i);
           b9_100->GetEntry(i); b9_101->GetEntry(i);

           b10_1->GetEntry(i); b10_2->GetEntry(i); b10_3->GetEntry(i);b10_4->GetEntry(i); b10_5->GetEntry(i); b10_6->GetEntry(i);b10_7->GetEntry(i); b10_8->GetEntry(i); b10_9->GetEntry(i);
           b10_10->GetEntry(i); b10_11->GetEntry(i); b10_12->GetEntry(i); b10_13->GetEntry(i);b10_14->GetEntry(i); b10_15->GetEntry(i); b10_16->GetEntry(i);b10_17->GetEntry(i); b10_18->GetEntry(i); b10_19->GetEntry(i);
           b10_20->GetEntry(i); b10_21->GetEntry(i); b10_22->GetEntry(i); b10_23->GetEntry(i);b10_24->GetEntry(i); b10_25->GetEntry(i); b10_26->GetEntry(i);b10_27->GetEntry(i); b10_28->GetEntry(i); b10_29->GetEntry(i);
           b10_30->GetEntry(i); b10_31->GetEntry(i); b10_32->GetEntry(i); b10_33->GetEntry(i);b10_34->GetEntry(i); b10_35->GetEntry(i); b10_36->GetEntry(i);b10_37->GetEntry(i); b10_38->GetEntry(i); b10_39->GetEntry(i);
           b10_40->GetEntry(i); b10_41->GetEntry(i); b10_42->GetEntry(i); b10_43->GetEntry(i);b10_44->GetEntry(i); b10_45->GetEntry(i); b10_46->GetEntry(i);b10_47->GetEntry(i); b10_48->GetEntry(i); b10_49->GetEntry(i);
           b10_50->GetEntry(i); b10_51->GetEntry(i); b10_52->GetEntry(i); b10_53->GetEntry(i);b10_54->GetEntry(i); b10_55->GetEntry(i); b10_56->GetEntry(i);b10_57->GetEntry(i); b10_58->GetEntry(i); b10_59->GetEntry(i);
           b10_60->GetEntry(i); b10_61->GetEntry(i); b10_62->GetEntry(i); b10_63->GetEntry(i);b10_64->GetEntry(i); b10_65->GetEntry(i); b10_66->GetEntry(i);b10_67->GetEntry(i); b10_68->GetEntry(i); b10_69->GetEntry(i);
           b10_70->GetEntry(i); b10_71->GetEntry(i); b10_72->GetEntry(i); b10_73->GetEntry(i);b10_74->GetEntry(i); b10_75->GetEntry(i); b10_76->GetEntry(i);b10_77->GetEntry(i); b10_78->GetEntry(i); b10_79->GetEntry(i);
           b10_80->GetEntry(i); b10_81->GetEntry(i); b10_82->GetEntry(i); b10_83->GetEntry(i);b10_84->GetEntry(i); b10_85->GetEntry(i); b10_86->GetEntry(i);b10_87->GetEntry(i); b10_88->GetEntry(i); b10_89->GetEntry(i);
           b10_90->GetEntry(i); b10_91->GetEntry(i); b10_92->GetEntry(i); b10_93->GetEntry(i);b10_94->GetEntry(i); b10_95->GetEntry(i); b10_96->GetEntry(i);b10_97->GetEntry(i); b10_98->GetEntry(i); b10_99->GetEntry(i);
           b10_100->GetEntry(i); b10_101->GetEntry(i);

           if (name=="GGTT_0p0") {aweight*=TauG2Weights_ceBRe_0p0;}
           else if (name=="GGTT") aweight*=TauG2Weights_ceBRe_0p0;
           else if (name=="GGTT_0p8") aweight*=TauG2Weights_ceBRe_0p8;
           else if (name=="GGTT_1p6") aweight*=TauG2Weights_ceBRe_1p6;
           else if (name=="GGTT_2p4") aweight*=TauG2Weights_ceBRe_2p4;
           else if (name=="GGTT_3p2") aweight*=TauG2Weights_ceBRe_3p2;
           else if (name=="GGTT_4p0") aweight*=TauG2Weights_ceBRe_4p0;
           else if (name=="GGTT_4p8") aweight*=TauG2Weights_ceBRe_4p8;
           else if (name=="GGTT_5p6") aweight*=TauG2Weights_ceBRe_5p6;
           else if (name=="GGTT_6p4") aweight*=TauG2Weights_ceBRe_6p4;
           else if (name=="GGTT_7p2") aweight*=TauG2Weights_ceBRe_7p2;
           else if (name=="GGTT_8p0") aweight*=TauG2Weights_ceBRe_8p0;
           else if (name=="GGTT_8p8") aweight*=TauG2Weights_ceBRe_8p8;
           else if (name=="GGTT_9p6") aweight*=TauG2Weights_ceBRe_9p6;
           else if (name=="GGTT_10p4") aweight*=TauG2Weights_ceBRe_10p4;
           else if (name=="GGTT_11p2") aweight*=TauG2Weights_ceBRe_11p2;
           else if (name=="GGTT_12p0") aweight*=TauG2Weights_ceBRe_12p0;
           else if (name=="GGTT_12p8") aweight*=TauG2Weights_ceBRe_12p8;
           else if (name=="GGTT_13p6") aweight*=TauG2Weights_ceBRe_13p6;
           else if (name=="GGTT_14p4") aweight*=TauG2Weights_ceBRe_14p4;
           else if (name=="GGTT_15p2") aweight*=TauG2Weights_ceBRe_15p2;
           else if (name=="GGTT_16p0") aweight*=TauG2Weights_ceBRe_16p0;
           else if (name=="GGTT_16p8") aweight*=TauG2Weights_ceBRe_16p8;
           else if (name=="GGTT_17p6") aweight*=TauG2Weights_ceBRe_17p6;
           else if (name=="GGTT_18p4") aweight*=TauG2Weights_ceBRe_18p4;
           else if (name=="GGTT_19p2") aweight*=TauG2Weights_ceBRe_19p2;
           else if (name=="GGTT_20p0") aweight*=TauG2Weights_ceBRe_20p0;
           else if (name=="GGTT_20p8") aweight*=TauG2Weights_ceBRe_20p8;
           else if (name=="GGTT_21p6") aweight*=TauG2Weights_ceBRe_21p6;
           else if (name=="GGTT_22p4") aweight*=TauG2Weights_ceBRe_22p4;
           else if (name=="GGTT_23p2") aweight*=TauG2Weights_ceBRe_23p2;
           else if (name=="GGTT_24p0") aweight*=TauG2Weights_ceBRe_24p0;
           else if (name=="GGTT_24p8") aweight*=TauG2Weights_ceBRe_24p8;
           else if (name=="GGTT_25p6") aweight*=TauG2Weights_ceBRe_25p6;
           else if (name=="GGTT_26p4") aweight*=TauG2Weights_ceBRe_26p4;
           else if (name=="GGTT_27p2") aweight*=TauG2Weights_ceBRe_27p2;
           else if (name=="GGTT_28p0") aweight*=TauG2Weights_ceBRe_28p0;
           else if (name=="GGTT_28p8") aweight*=TauG2Weights_ceBRe_28p8;
           else if (name=="GGTT_29p6") aweight*=TauG2Weights_ceBRe_29p6;
           else if (name=="GGTT_30p4") aweight*=TauG2Weights_ceBRe_30p4;
           else if (name=="GGTT_31p2") aweight*=TauG2Weights_ceBRe_31p2;
           else if (name=="GGTT_32p0") aweight*=TauG2Weights_ceBRe_32p0;
           else if (name=="GGTT_32p8") aweight*=TauG2Weights_ceBRe_32p8;
           else if (name=="GGTT_33p6") aweight*=TauG2Weights_ceBRe_33p6;
           else if (name=="GGTT_34p4") aweight*=TauG2Weights_ceBRe_34p4;
           else if (name=="GGTT_35p2") aweight*=TauG2Weights_ceBRe_35p2;
           else if (name=="GGTT_36p0") aweight*=TauG2Weights_ceBRe_36p0;
           else if (name=="GGTT_36p8") aweight*=TauG2Weights_ceBRe_36p8;
           else if (name=="GGTT_37p6") aweight*=TauG2Weights_ceBRe_37p6;
           else if (name=="GGTT_38p4") aweight*=TauG2Weights_ceBRe_38p4;
           else if (name=="GGTT_39p2") aweight*=TauG2Weights_ceBRe_39p2;
           else if (name=="GGTT_40p0") aweight*=TauG2Weights_ceBRe_40p0;
           else if (name=="GGTT_m0p8") aweight*=TauG2Weights_ceBRe_m0p8;
           else if (name=="GGTT_m1p6") aweight*=TauG2Weights_ceBRe_m1p6;
           else if (name=="GGTT_m2p4") aweight*=TauG2Weights_ceBRe_m2p4;
           else if (name=="GGTT_m3p2") aweight*=TauG2Weights_ceBRe_m3p2;
           else if (name=="GGTT_m4p0") aweight*=TauG2Weights_ceBRe_m4p0;
           else if (name=="GGTT_m4p8") aweight*=TauG2Weights_ceBRe_m4p8;
           else if (name=="GGTT_m5p6") aweight*=TauG2Weights_ceBRe_m5p6;
           else if (name=="GGTT_m6p4") aweight*=TauG2Weights_ceBRe_m6p4;
           else if (name=="GGTT_m7p2") aweight*=TauG2Weights_ceBRe_m7p2;
           else if (name=="GGTT_m8p0") aweight*=TauG2Weights_ceBRe_m8p0;
           else if (name=="GGTT_m8p8") aweight*=TauG2Weights_ceBRe_m8p8;
           else if (name=="GGTT_m9p6") aweight*=TauG2Weights_ceBRe_m9p6;
           else if (name=="GGTT_m10p4") aweight*=TauG2Weights_ceBRe_m10p4;
           else if (name=="GGTT_m11p2") aweight*=TauG2Weights_ceBRe_m11p2;
           else if (name=="GGTT_m12p0") aweight*=TauG2Weights_ceBRe_m12p0;
           else if (name=="GGTT_m12p8") aweight*=TauG2Weights_ceBRe_m12p8;
           else if (name=="GGTT_m13p6") aweight*=TauG2Weights_ceBRe_m13p6;
           else if (name=="GGTT_m14p4") aweight*=TauG2Weights_ceBRe_m14p4;
           else if (name=="GGTT_m15p2") aweight*=TauG2Weights_ceBRe_m15p2;
           else if (name=="GGTT_m16p0") aweight*=TauG2Weights_ceBRe_m16p0;
           else if (name=="GGTT_m16p8") aweight*=TauG2Weights_ceBRe_m16p8;
           else if (name=="GGTT_m17p6") aweight*=TauG2Weights_ceBRe_m17p6;
           else if (name=="GGTT_m18p4") aweight*=TauG2Weights_ceBRe_m18p4;
           else if (name=="GGTT_m19p2") aweight*=TauG2Weights_ceBRe_m19p2;
           else if (name=="GGTT_m20p0") aweight*=TauG2Weights_ceBRe_m20p0;
           else if (name=="GGTT_m20p8") aweight*=TauG2Weights_ceBRe_m20p8;
           else if (name=="GGTT_m21p6") aweight*=TauG2Weights_ceBRe_m21p6;
           else if (name=="GGTT_m22p4") aweight*=TauG2Weights_ceBRe_m22p4;
           else if (name=="GGTT_m23p2") aweight*=TauG2Weights_ceBRe_m23p2;
           else if (name=="GGTT_m24p0") aweight*=TauG2Weights_ceBRe_m24p0;
           else if (name=="GGTT_m24p8") aweight*=TauG2Weights_ceBRe_m24p8;
           else if (name=="GGTT_m25p6") aweight*=TauG2Weights_ceBRe_m25p6;
           else if (name=="GGTT_m26p4") aweight*=TauG2Weights_ceBRe_m26p4;
           else if (name=="GGTT_m27p2") aweight*=TauG2Weights_ceBRe_m27p2;
           else if (name=="GGTT_m28p0") aweight*=TauG2Weights_ceBRe_m28p0;
           else if (name=="GGTT_m28p8") aweight*=TauG2Weights_ceBRe_m28p8;
           else if (name=="GGTT_m29p6") aweight*=TauG2Weights_ceBRe_m29p6;
           else if (name=="GGTT_m30p4") aweight*=TauG2Weights_ceBRe_m30p4;
           else if (name=="GGTT_m31p2") aweight*=TauG2Weights_ceBRe_m31p2;
           else if (name=="GGTT_m32p0") aweight*=TauG2Weights_ceBRe_m32p0;
           else if (name=="GGTT_m32p8") aweight*=TauG2Weights_ceBRe_m32p8;
           else if (name=="GGTT_m33p6") aweight*=TauG2Weights_ceBRe_m33p6;
           else if (name=="GGTT_m34p4") aweight*=TauG2Weights_ceBRe_m34p4;
           else if (name=="GGTT_m35p2") aweight*=TauG2Weights_ceBRe_m35p2;
           else if (name=="GGTT_m36p0") aweight*=TauG2Weights_ceBRe_m36p0;
           else if (name=="GGTT_m36p8") aweight*=TauG2Weights_ceBRe_m36p8;
           else if (name=="GGTT_m37p6") aweight*=TauG2Weights_ceBRe_m37p6;
           else if (name=="GGTT_m38p4") aweight*=TauG2Weights_ceBRe_m38p4;
           else if (name=="GGTT_m39p2") aweight*=TauG2Weights_ceBRe_m39p2;
           else if (name=="GGTT_m40p0") aweight*=TauG2Weights_ceBRe_m40p0;

           if (name=="GGTT_Im_0p0") {aweight*=TauG2Weights_ceBIm_0p0;}
           else if (name=="GGTT_Im_0p8") aweight*=TauG2Weights_ceBIm_0p8;
           else if (name=="GGTT_Im_1p6") aweight*=TauG2Weights_ceBIm_1p6;
           else if (name=="GGTT_Im_2p4") aweight*=TauG2Weights_ceBIm_2p4;
           else if (name=="GGTT_Im_3p2") aweight*=TauG2Weights_ceBIm_3p2;
           else if (name=="GGTT_Im_4p0") aweight*=TauG2Weights_ceBIm_4p0;
           else if (name=="GGTT_Im_4p8") aweight*=TauG2Weights_ceBIm_4p8;
           else if (name=="GGTT_Im_5p6") aweight*=TauG2Weights_ceBIm_5p6;
           else if (name=="GGTT_Im_6p4") aweight*=TauG2Weights_ceBIm_6p4;
           else if (name=="GGTT_Im_7p2") aweight*=TauG2Weights_ceBIm_7p2;
           else if (name=="GGTT_Im_8p0") aweight*=TauG2Weights_ceBIm_8p0;
           else if (name=="GGTT_Im_8p8") aweight*=TauG2Weights_ceBIm_8p8;
           else if (name=="GGTT_Im_9p6") aweight*=TauG2Weights_ceBIm_9p6;
           else if (name=="GGTT_Im_10p4") aweight*=TauG2Weights_ceBIm_10p4;
           else if (name=="GGTT_Im_11p2") aweight*=TauG2Weights_ceBIm_11p2;
           else if (name=="GGTT_Im_12p0") aweight*=TauG2Weights_ceBIm_12p0;
           else if (name=="GGTT_Im_12p8") aweight*=TauG2Weights_ceBIm_12p8;
           else if (name=="GGTT_Im_13p6") aweight*=TauG2Weights_ceBIm_13p6;
           else if (name=="GGTT_Im_14p4") aweight*=TauG2Weights_ceBIm_14p4;
           else if (name=="GGTT_Im_15p2") aweight*=TauG2Weights_ceBIm_15p2;
           else if (name=="GGTT_Im_16p0") aweight*=TauG2Weights_ceBIm_16p0;
           else if (name=="GGTT_Im_16p8") aweight*=TauG2Weights_ceBIm_16p8;
           else if (name=="GGTT_Im_17p6") aweight*=TauG2Weights_ceBIm_17p6;
           else if (name=="GGTT_Im_18p4") aweight*=TauG2Weights_ceBIm_18p4;
           else if (name=="GGTT_Im_19p2") aweight*=TauG2Weights_ceBIm_19p2;
           else if (name=="GGTT_Im_20p0") aweight*=TauG2Weights_ceBIm_20p0;
           else if (name=="GGTT_Im_20p8") aweight*=TauG2Weights_ceBIm_20p8;
           else if (name=="GGTT_Im_21p6") aweight*=TauG2Weights_ceBIm_21p6;
           else if (name=="GGTT_Im_22p4") aweight*=TauG2Weights_ceBIm_22p4;
           else if (name=="GGTT_Im_23p2") aweight*=TauG2Weights_ceBIm_23p2;
           else if (name=="GGTT_Im_24p0") aweight*=TauG2Weights_ceBIm_24p0;
           else if (name=="GGTT_Im_24p8") aweight*=TauG2Weights_ceBIm_24p8;
           else if (name=="GGTT_Im_25p6") aweight*=TauG2Weights_ceBIm_25p6;
           else if (name=="GGTT_Im_26p4") aweight*=TauG2Weights_ceBIm_26p4;
           else if (name=="GGTT_Im_27p2") aweight*=TauG2Weights_ceBIm_27p2;
           else if (name=="GGTT_Im_28p0") aweight*=TauG2Weights_ceBIm_28p0;
           else if (name=="GGTT_Im_28p8") aweight*=TauG2Weights_ceBIm_28p8;
           else if (name=="GGTT_Im_29p6") aweight*=TauG2Weights_ceBIm_29p6;
           else if (name=="GGTT_Im_30p4") aweight*=TauG2Weights_ceBIm_30p4;
           else if (name=="GGTT_Im_31p2") aweight*=TauG2Weights_ceBIm_31p2;
           else if (name=="GGTT_Im_32p0") aweight*=TauG2Weights_ceBIm_32p0;
           else if (name=="GGTT_Im_32p8") aweight*=TauG2Weights_ceBIm_32p8;
           else if (name=="GGTT_Im_33p6") aweight*=TauG2Weights_ceBIm_33p6;
           else if (name=="GGTT_Im_34p4") aweight*=TauG2Weights_ceBIm_34p4;
           else if (name=="GGTT_Im_35p2") aweight*=TauG2Weights_ceBIm_35p2;
           else if (name=="GGTT_Im_36p0") aweight*=TauG2Weights_ceBIm_36p0;
           else if (name=="GGTT_Im_36p8") aweight*=TauG2Weights_ceBIm_36p8;
           else if (name=="GGTT_Im_37p6") aweight*=TauG2Weights_ceBIm_37p6;
           else if (name=="GGTT_Im_38p4") aweight*=TauG2Weights_ceBIm_38p4;
           else if (name=="GGTT_Im_39p2") aweight*=TauG2Weights_ceBIm_39p2;
           else if (name=="GGTT_Im_m0p8") aweight*=TauG2Weights_ceBIm_m0p8;
           else if (name=="GGTT_Im_m1p6") aweight*=TauG2Weights_ceBIm_m1p6;
           else if (name=="GGTT_Im_m2p4") aweight*=TauG2Weights_ceBIm_m2p4;
           else if (name=="GGTT_Im_m3p2") aweight*=TauG2Weights_ceBIm_m3p2;
           else if (name=="GGTT_Im_m4p0") aweight*=TauG2Weights_ceBIm_m4p0;
           else if (name=="GGTT_Im_m4p8") aweight*=TauG2Weights_ceBIm_m4p8;
           else if (name=="GGTT_Im_m5p6") aweight*=TauG2Weights_ceBIm_m5p6;
           else if (name=="GGTT_Im_m6p4") aweight*=TauG2Weights_ceBIm_m6p4;
           else if (name=="GGTT_Im_m7p2") aweight*=TauG2Weights_ceBIm_m7p2;
           else if (name=="GGTT_Im_m8p0") aweight*=TauG2Weights_ceBIm_m8p0;
           else if (name=="GGTT_Im_m8p8") aweight*=TauG2Weights_ceBIm_m8p8;
           else if (name=="GGTT_Im_m9p6") aweight*=TauG2Weights_ceBIm_m9p6;
           else if (name=="GGTT_Im_m10p4") aweight*=TauG2Weights_ceBIm_m10p4;
           else if (name=="GGTT_Im_m11p2") aweight*=TauG2Weights_ceBIm_m11p2;
           else if (name=="GGTT_Im_m12p0") aweight*=TauG2Weights_ceBIm_m12p0;
           else if (name=="GGTT_Im_m12p8") aweight*=TauG2Weights_ceBIm_m12p8;
           else if (name=="GGTT_Im_m13p6") aweight*=TauG2Weights_ceBIm_m13p6;
           else if (name=="GGTT_Im_m14p4") aweight*=TauG2Weights_ceBIm_m14p4;
           else if (name=="GGTT_Im_m15p2") aweight*=TauG2Weights_ceBIm_m15p2;
           else if (name=="GGTT_Im_m16p0") aweight*=TauG2Weights_ceBIm_m16p0;
           else if (name=="GGTT_Im_m16p8") aweight*=TauG2Weights_ceBIm_m16p8;
           else if (name=="GGTT_Im_m17p6") aweight*=TauG2Weights_ceBIm_m17p6;
           else if (name=="GGTT_Im_m18p4") aweight*=TauG2Weights_ceBIm_m18p4;
           else if (name=="GGTT_Im_m19p2") aweight*=TauG2Weights_ceBIm_m19p2;
           else if (name=="GGTT_Im_m20p0") aweight*=TauG2Weights_ceBIm_m20p0;
           else if (name=="GGTT_Im_m20p8") aweight*=TauG2Weights_ceBIm_m20p8;
           else if (name=="GGTT_Im_m21p6") aweight*=TauG2Weights_ceBIm_m21p6;
           else if (name=="GGTT_Im_m22p4") aweight*=TauG2Weights_ceBIm_m22p4;
           else if (name=="GGTT_Im_m23p2") aweight*=TauG2Weights_ceBIm_m23p2;
           else if (name=="GGTT_Im_m24p0") aweight*=TauG2Weights_ceBIm_m24p0;
           else if (name=="GGTT_Im_m24p8") aweight*=TauG2Weights_ceBIm_m24p8;
           else if (name=="GGTT_Im_m25p6") aweight*=TauG2Weights_ceBIm_m25p6;
           else if (name=="GGTT_Im_m26p4") aweight*=TauG2Weights_ceBIm_m26p4;
           else if (name=="GGTT_Im_m27p2") aweight*=TauG2Weights_ceBIm_m27p2;
           else if (name=="GGTT_Im_m28p0") aweight*=TauG2Weights_ceBIm_m28p0;
           else if (name=="GGTT_Im_m28p8") aweight*=TauG2Weights_ceBIm_m28p8;
           else if (name=="GGTT_Im_m29p6") aweight*=TauG2Weights_ceBIm_m29p6;
           else if (name=="GGTT_Im_m30p4") aweight*=TauG2Weights_ceBIm_m30p4;
           else if (name=="GGTT_Im_m31p2") aweight*=TauG2Weights_ceBIm_m31p2;
           else if (name=="GGTT_Im_m32p0") aweight*=TauG2Weights_ceBIm_m32p0;
           else if (name=="GGTT_Im_m32p8") aweight*=TauG2Weights_ceBIm_m32p8;
           else if (name=="GGTT_Im_m33p6") aweight*=TauG2Weights_ceBIm_m33p6;
           else if (name=="GGTT_Im_m34p4") aweight*=TauG2Weights_ceBIm_m34p4;
           else if (name=="GGTT_Im_m35p2") aweight*=TauG2Weights_ceBIm_m35p2;
           else if (name=="GGTT_Im_m36p0") aweight*=TauG2Weights_ceBIm_m36p0;
           else if (name=="GGTT_Im_m36p8") aweight*=TauG2Weights_ceBIm_m36p8;
           else if (name=="GGTT_Im_m37p6") aweight*=TauG2Weights_ceBIm_m37p6;
           else if (name=="GGTT_Im_m38p4") aweight*=TauG2Weights_ceBIm_m38p4;
           else if (name=="GGTT_Im_m39p2") aweight*=TauG2Weights_ceBIm_m39p2;
           else if (name=="GGTT_Im_m40p0") aweight*=TauG2Weights_ceBIm_m40p0;
           else if (name=="GGTT_Im_40p0") aweight*=TauG2Weights_ceBIm_40p0;
        }

        float central=1.0;
        float correction=1.0;
        float err_central=0.0;
        float err_correction=0.0;
        float err_fr=0.0;

        bool is_real=(name=="W" or name=="GGTT" or sample=="GGTT" or sample=="GGTT_Ctb20" or name=="data_obs" or (LepCand_gen[ele_index]!=0 and LepCand_gen[mu_index]!=0));


        for (int k=0; k<nbhist; ++k){
           my_mu=save_mu;
	   my_ele=save_ele;
	   my_met=save_met;
	   float weight2=1.0;

	   if (name!="data_obs"){
              if (k==1){ weight2=puWeightDown/puWeight;}
              else if (k==2){ weight2=puWeightUp/puWeight;}
	      else if (k==3 and my_mu.Pt()<24 and my_ele.Pt()>=24){ weight2=0.96;}
              else if (k==4 and my_mu.Pt()<24 and my_ele.Pt()>=24){ weight2=1.04;}
              else if (k==5 and my_mu.Pt()>=24 and my_ele.Pt()<24){ weight2=0.96;}
              else if (k==6 and my_mu.Pt()>=24 and my_ele.Pt()<24){ weight2=1.04;}
              else if (k==7 and my_mu.Pt()>=24 and my_ele.Pt()>=24){ weight2=0.96;}
              else if (k==8 and my_mu.Pt()>=24 and my_ele.Pt()>=24){ weight2=1.04;}
              else if (k==9){ 
                if (ntracks==0) weight2=2.59/(2.433+0.00152*gen_mtt);
                if (ntracks==1) weight2=2.63/(2.52+0.0011*gen_mtt);
              }
              else if (k==10){
                if (ntracks==0) weight2=1.0+(1.0-2.59/(2.433+0.00152*gen_mtt));
                if (ntracks==1) weight2=1.0+(1.0-2.63/(2.52+0.0011*gen_mtt));
              }
              else if (k==11) weight2=L1PreFiringWeight_Dn/L1PreFiringWeight_Nom;
              else if (k==12) weight2=L1PreFiringWeight_Up/L1PreFiringWeight_Nom;
	      else if (k==13) weight2=muidsf_syst_down/muidsf_nom;
              else if (k==14) weight2=muidsf_syst_up/muidsf_nom;
              else if (k==15) weight2=muidsf_stat_down/muidsf_nom;
              else if (k==16) weight2=muidsf_stat_up/muidsf_nom;
              else if (k==17) weight2=muisosf_syst_down/muisosf_nom;
              else if (k==18) weight2=muisosf_syst_up/muisosf_nom;
              else if (k==19) weight2=muisosf_stat_down/muisosf_nom;
              else if (k==20) weight2=muisosf_stat_up/muisosf_nom;
	      else if (k==21) weight2=elidsf_down/elidsf_nom;
              else if (k==22) weight2=elidsf_up/elidsf_nom;
              else if (k==23) weight2=PSWeight[2] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 9, year)/weight_aco;
              else if (k==24) weight2=PSWeight[0] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 7, year)/weight_aco;
              else if (k==25) weight2=PSWeight[3] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 10, year)/weight_aco;
              else if (k==26) weight2=PSWeight[1] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 8, year)/weight_aco;
              else if (k==27 or k==28){
                float average_sigma=0.0;
                for (int jj=1; jj<101; ++jj) average_sigma+=0.01*LHEPdfWeight[jj];
                float deltasigma=0.0;
                for (int jj=1; jj<101; ++jj) deltasigma+=(1.0/(100-1))*pow((LHEPdfWeight[jj]-average_sigma),2);
                deltasigma=pow(deltasigma,0.5);
                if (k==27) weight2 = (1.0-deltasigma);
                else if (k==28) weight2 = (1.0+deltasigma);
              }
              else if (k==29) weight2=LHEScaleWeight[0]/0.983 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 1, year)/weight_aco;
              else if (k==30) weight2=LHEScaleWeight[1]/1.015 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 2, year)/weight_aco;
              else if (k==31) weight2=LHEScaleWeight[3]/0.960 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 3, year)/weight_aco;
              else if (k==32 and sample=="DY") weight2=LHEScaleWeight[5]/1.025 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 4, year)/weight_aco;
              else if (k==32 and sample=="DYemu") weight2=LHEScaleWeight[4]/1.025 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 4, year)/weight_aco;
              else if (k==33 and sample=="DY") weight2=LHEScaleWeight[7]/0.986 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 5, year)/weight_aco;
              else if (k==33 and sample=="DYemu") weight2=LHEScaleWeight[6]/0.986 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 5, year)/weight_aco;
              else if (k==34 and sample=="DY") weight2=LHEScaleWeight[8]/1.018 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 6, year)/weight_aco;
              else if (k==34 and sample=="DYemu") weight2=LHEScaleWeight[7]/1.018 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 6, year)/weight_aco;
	   }

	   float mvis=(my_ele+my_mu).M();
	   if (mvis<20) continue;
	   if (mvis>500) continue; //FIXME

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
              is_cat0=(is_lowA and mvis>20 and ntracks==0);
              is_cat1=(is_lowA and mvis>20 and ntracks==1);
              is_cat2=(is_lowA and mvis>20 and (ntracks==3 or ntracks==4));
              is_cat3=(mvis<100 and (ntracks==0 or ntracks==1));
              is_cat4=(ntracks<10 and mvis<100 and is_lowA);
              is_cat5=(ntracks<10 and mvis>100 and is_lowA);
              is_cat6=(mvis>0);
              is_cat7=(mvis>0);
              is_cat8=(mvis>0);

              is_cat0R=(is_lowA and mvis>20 and ntracks<10);
              is_cat1R=(is_lowA and mvis>20 and ntracks<10);
              is_cat2R=(is_lowA and mvis>20 and ntracks<10);
              is_cat3R=(mvis<100 and (ntracks==0 or ntracks==1));
              is_cat4R=(ntracks<10 and mvis<100 and is_lowA);
              is_cat5R=(ntracks<10 and mvis>100 and is_lowA);
              is_cat6R=(mvis>0);
              is_cat7R=(mvis>0);
              is_cat8R=(mvis>0);

              var0 = mvis;
              var1 = mvis;
              var2 = mvis;
              var3 = acoplanarity;
              var4 = ntracks;
              var5 = ntracks;
              var6 = mvis;
              var7 = mvis;
              var8 = mvis;

	   }

           if (k==0 and is_OS and is_isolated and is_real){
	      h_nHS->Fill(ntracksHS_friend,weight);
              if (ntracks==0 and acoplanarity<0.015) h_DY_ABCD->Fill(0.5,weight*aweight);
              if (ntracks==0 and acoplanarity>=0.015) h_DY_ABCD->Fill(1.5,weight*aweight);
              if (ntracks==1 and acoplanarity<0.015) h_DY_ABCD->Fill(2.5,weight*aweight);
              if (ntracks==1 and acoplanarity>=0.015) h_DY_ABCD->Fill(3.5,weight*aweight);
              if (ntracks<10 and acoplanarity<0.015) h_DY_ABCD->Fill(4.5,weight*aweight);
              if (ntracks<10 and acoplanarity>=0.015) h_DY_ABCD->Fill(5.5,weight*aweight);

              if (ntracks==0 and is_lowA) h_mvis_nt0->Fill(mvis,weight*aweight);
              if (ntracks>=0 and ntracks<10 and is_lowA) h_mvis_nt0to10->Fill(mvis,weight*aweight);
           }

           if (k==0 and is_OS and is_isolated and is_real){
              h_acoplanarity->Fill(acoplanarity);
              if (my_ele.Pt()+my_mu.Pt()<100) h_acoplanarity_sumptlt100->Fill(acoplanarity);
              else h_acoplanarity_sumptgt100->Fill(acoplanarity);

              h_resolution_acoplanarity->Fill(acoplanarity-gen_aco);
              if (my_ele.Pt()+my_mu.Pt()<100) h_resolution_acoplanarity_sumptlt100->Fill(acoplanarity-gen_aco);
              else h_resolution_acoplanarity_sumptgt100->Fill(acoplanarity-gen_aco);

           }

	   if (is_OS and is_isolated and is_real){
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

	   float fr=h_fr->GetBinContent(h_fr->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_fr->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt())));
	   fr*=h_frantimu->GetBinContent(h_frantimu->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_frantimu->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt())));
	   fr*=fit_frnt->Eval(ntracks);
	   float wfr=fr;//fr/(1-fr);

	   if (k>=(nbhistMC+1-nbhist_offset)){
	      central=h_fr->GetBinContent(h_fr->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_fr->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt())));
	      correction=h_frantimu->GetBinContent(h_frantimu->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_frantimu->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt())));
	      err_central=(h_fr->GetBinError(h_fr->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_fr->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt()))))/central;
              err_correction=(h_frantimu->GetBinError(h_frantimu->GetXaxis()->FindBin(TMath::Min(54.,my_ele.Pt())),h_frantimu->GetYaxis()->FindBin(TMath::Min(54.,my_mu.Pt()))))/correction;
	      err_fr=TMath::Sqrt(err_central*err_central+err_correction*err_correction);
	   }

           if (k==(nbhistMC+1-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0-err_fr);}
	   else if (k==(nbhistMC+2-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0+err_fr);}
	   else if (k==(nbhistMC+3-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+4-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+5-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+6-nbhist_offset) and my_ele.Pt()<=24 and my_mu.Pt()>45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+7-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()<=24){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+8-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()<=24){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+9-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+10-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+11-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+12-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+13-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+14-nbhist_offset) and my_ele.Pt()>24 and my_ele.Pt()<=35 and my_mu.Pt()>45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+15-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()<=24){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+16-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()<=24){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+17-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+18-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+19-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+20-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+21-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+22-nbhist_offset) and my_ele.Pt()>35 and my_ele.Pt()<=45 and my_mu.Pt()>45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+23-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()<=24){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+24-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()<=24){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+25-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+26-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>24 and my_mu.Pt()<=35){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+27-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+28-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>35 and my_mu.Pt()<=45){ wfr=fr*(1.0+err_fr);}
           else if (k==(nbhistMC+29-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>45){ wfr=fr*(1.0-err_fr);}
           else if (k==(nbhistMC+30-nbhist_offset) and my_ele.Pt()>45 and my_mu.Pt()>45){ wfr=fr*(1.0+err_fr);}


           if (!is_OS and is_isolated and is_real){
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
             if (is_control>0 and is_cat5R) h5R_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
             if (is_cat6R) h6R_anti[k]->Fill(var6,weight*aweight*weight2*wfr);
             if (is_cat7R) h7R_anti[k]->Fill(var7,weight*aweight*weight2*wfr);
             if (is_cat8R) h8R_anti[k]->Fill(var8,weight*aweight*weight2*wfr);
           }
           if (!is_OS and (is_PF or is_FP or is_FF or is_isolated) and is_real){
             if (is_control==0 and is_cat5R) h5R_anti[k]->Fill(var5,weight*aweight*weight2*wfr);
           }

	   if (k==0){
	     if (is_PF){
	        if (is_OS) h_fr_iso->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                else h_fr_anti->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                if (is_OS and (my_mu+my_ele).Pt()>30) h_frhigh_iso->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                else if ((my_mu+my_ele).Pt()>30) h_frhigh_anti->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                if (is_OS and (my_mu+my_ele).Pt()<30) h_frlow_iso->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                else if ((my_mu+my_ele).Pt()<30) h_frlow_anti->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                if (is_OS) h_frnt_iso->Fill(ntracks,weight*aweight);
                else h_frnt_anti->Fill(ntracks,weight*aweight);
                if (is_OS) h_frnt_iso->Fill(-1,weight*aweight);
                else h_frnt_anti->Fill(-1,weight*aweight);
	     }
	     if (is_FP){
                if (is_OS) h_frFP_iso->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                else h_frFP_anti->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
	     }
             if (is_FF){
                if (is_OS) h_frFF_iso->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
                else h_frFF_anti->Fill(TMath::Min(54.9,my_ele.Pt()),TMath::Min(54.9,my_mu.Pt()),weight*aweight);
             }
	   }

	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    h_dz->Write();
    h_nHS->Write();

    if (sample=="GGTT" or sample=="GGTT_Ctb20"){
      h_acoplanarity->Write();
      h_acoplanarity_sumptlt100->Write();
      h_acoplanarity_sumptgt100->Write();
      h_resolution_acoplanarity->Write();
      h_resolution_acoplanarity_sumptlt100->Write();
      h_resolution_acoplanarity_sumptgt100->Write();
    }


    h_DY_ABCD->Write();
    h_mvis_nt0->Write();
    h_mvis_nt0to10->Write();

    h_acoreso->Write();
    h_acoreso_high->Write();

    h_vtxresolution_PV->Write();
    h_vtxresolution_simpleditau->Write();
    h_ntracks->Write();

    h_fr_anti->Write();
    h_fr_iso->Write();
    h_frlow_anti->Write();
    h_frlow_iso->Write();
    h_frhigh_anti->Write();
    h_frhigh_iso->Write();

    h_frnt_anti->Write();
    h_frnt_iso->Write();

    h_frFF_anti->Write();
    h_frFF_iso->Write();
    h_frFP_anti->Write();
    h_frFP_iso->Write();

cout<<h0[0]->Integral()<<endl;

    bool isMC=(name!="data_obs");
    WriteHistToFileEMu(fout, h0, name, "em_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h0_anti, name, "em_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h1, name, "em_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h1_anti, name, "em_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h2, name, "em_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h2_anti, name, "em_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h3, name, "em_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h3_anti, name, "em_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h4, name, "em_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h4_anti, name, "em_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h5, name, "em_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileEMu(fout, h5_anti, name, "em_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    if (is_control>0){
       WriteHistToFileEMu(fout, h6, name, "em_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h6_anti, name, "em_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileEMu(fout, h7, name, "em_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h7_anti, name, "em_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileEMu(fout, h8, name, "em_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h8_anti, name, "em_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    }

    if (sample=="DY" or sample=="DYemu"){
       WriteHistToFileEMu(fout, h0R, name, "emR_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h1R, name, "emR_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h2R, name, "emR_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h3R, name, "emR_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h4R, name, "emR_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileEMu(fout, h5R, name, "emR_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       if (is_control>0){
          WriteHistToFileEMu(fout, h6R, name, "emR_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileEMu(fout, h7R, name, "emR_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileEMu(fout, h8R, name, "emR_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       }
    }

    WriteHistToFileEMu(fout, h0R_anti, name, "emR_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h1R_anti, name, "emR_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h2R_anti, name, "emR_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h3R_anti, name, "emR_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h4R_anti, name, "emR_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileEMu(fout, h5R_anti, name, "emR_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    if (is_control>0){
       WriteHistToFileEMu(fout, h6R_anti, name, "emR_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileEMu(fout, h7R_anti, name, "emR_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileEMu(fout, h8R_anti, name, "emR_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    }

    fout->Close();
} 


