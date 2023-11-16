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
    if (sample=="Z" or sample=="DY" or sample=="ZL" or sample=="ZTT" or sample=="ZJ" or sample=="ZLL"){ xs=6077.2; weight=luminosity*xs/ngen;}
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
    else if (sample=="WW2L2Nu"){ xs=8.95; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2L2Q"){ xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="WZ2Q2L"){ xs=5.595; weight=luminosity*xs/ngen;}
    else if (sample=="ZZ2L2Nu"){ xs=3.0; weight=luminosity*xs/ngen;}
    else if (sample=="WZ"){ xs=47.13; weight=luminosity*xs/ngen;}
    else if (sample=="WW"){ xs=118.7; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_top"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_tW_antitop"){ xs=35.6; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_top"){ xs=136.02; weight=luminosity*xs/ngen;}
    else if (sample=="ST_t_antitop"){ xs=80.95; weight=luminosity*xs/ngen;}
    else if (sample=="GGWW"){ xs=0.00692 * 0.368; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT"){ xs=1.161*0.008735; weight=luminosity*xs/ngen;}
    else if (sample=="GGTT_Ctb20"){ xs=1.121*0.0269; weight=luminosity*xs/ngen;}
    else if (sample=="CEPDijets"){ xs=0.1468; weight=luminosity*xs/ngen;}
    else if (sample=="QCDpomflux"){ xs=2285000.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGHTT"){ xs=48.30*0.06208; weight=luminosity*xs/ngen;}
    else if (name=="data_obs"){ weight=1.0;}
    else if (name=="test") { xs=1.0; weight=luminosity*xs/ngen;}
    else if (sample=="GGHWW") {xs=48.30*0.2203*0.3258*0.3258; weight=luminosity*xs/ngen;}

cout<<xs<<" "<<ngen<<" "<<ngenu<<" "<<weight<<endl;

    //if (output.find("renano") < 140){
      if (sample=="DY") weight*=0.318;
      else if (sample=="TTTo2L2Nu") weight*=0.657;
      else if (sample=="TTToSemiLeptonic") weight*=0.401;
      else if (sample=="TTToHadronic") weight*=0.170;
      else if (sample=="ST_t_top") weight*=0.118;
      else if (sample=="ST_t_antitop") weight*=0.122;
      else if (sample=="ST_tW_top") weight*=0.273;
      else if (sample=="ST_tW_antitop") weight*=0.272;
      else if (sample=="WW2L2Nu") weight*=0.397;
      else if (sample=="VV2L2Nu") weight*=0.392;
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
      else if (sample=="CEPDijets") weight*=0.0198;
      else if (sample=="QCDpomflux") weight*=0.00259;
      else if (sample=="GGHTT") weight*=0.214;

    //}
    //
    float nnlo=1.162;
    float xsW=52940.0;
    float xsW1=8104.0;
    float xsW2=2793.0;
    float xsW3=992.5;
    float xsW4=544.3;

    float ngenW=2162740.0/0.0305;
    float ngenW1=1761620.0/0.0523;
    float ngenW2=1153860.0/0.0928;
    float ngenW3=1450910.0/0.132;
    float ngenW4=1509960.0/0.184;

    if (year=="2017"){
       /*ngenW=1894170.0/0.0240;
       ngenW1=1782300.0/0.0380;
       ngenW2=1716170.0/0.0637;
       ngenW3=1879860.0/0.1042;
       ngenW4=1228160.0/0.1278;*/
       ngenW=1894170.0/0.0305;
       ngenW1=1782300.0/0.0523;
       ngenW2=1716170.0/0.0928;
       ngenW3=1879860.0/0.132;
       ngenW4=1228160.0/0.184;
    }

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
    arbre->SetBranchAddress("LepCand_tauidMsf_uncert0_up", &LepCand_tauidMsf_uncert0_up);
    arbre->SetBranchAddress("LepCand_tauidMsf_uncert1_up", &LepCand_tauidMsf_uncert1_up);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_alleras_up", &LepCand_tauidMsf_syst_alleras_up);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_era_up", &LepCand_tauidMsf_syst_era_up);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_dm_era_up", &LepCand_tauidMsf_syst_dm_era_up);
    arbre->SetBranchAddress("LepCand_tauidMsf_uncert0_down", &LepCand_tauidMsf_uncert0_down);
    arbre->SetBranchAddress("LepCand_tauidMsf_uncert1_down", &LepCand_tauidMsf_uncert1_down);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_alleras_down", &LepCand_tauidMsf_syst_alleras_down);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_era_down", &LepCand_tauidMsf_syst_era_down);
    arbre->SetBranchAddress("LepCand_tauidMsf_syst_dm_era_down", &LepCand_tauidMsf_syst_dm_era_down);

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
    arbre->SetBranchAddress("LepCand_eleMVAiso80", &LepCand_eleMVAiso80);
    arbre->SetBranchAddress("LepCand_eleMVAiso90", &LepCand_eleMVAiso90);
    arbre->SetBranchAddress("LepCand_trgmatch", &LepCand_trgmatch);

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
    arbre->SetBranchAddress("L1PreFiringWeight_Nom", &L1PreFiringWeight_Nom);
    arbre->SetBranchAddress("L1PreFiringWeight_Up", &L1PreFiringWeight_Up);
    arbre->SetBranchAddress("L1PreFiringWeight_Dn", &L1PreFiringWeight_Dn);
    arbre->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight);
    arbre->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight);
    arbre->SetBranchAddress("PSWeight", &PSWeight);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);
    arbre->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1", &HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1);
    arbre->SetBranchAddress("HLT_Ele25_eta2p1_WPTight_Gsf", &HLT_Ele25_eta2p1_WPTight_Gsf);
    arbre->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG", &HLT_Ele32_WPTight_Gsf_L1DoubleEG);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20);
    arbre->SetBranchAddress("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30", &HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30);

    arbre->SetBranchAddress("TauG2Weights_ceBRe33_40p0", &TauG2Weights_ceBRe33_40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_39p2", &TauG2Weights_ceBRe33_39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_38p4", &TauG2Weights_ceBRe33_38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_37p6", &TauG2Weights_ceBRe33_37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_36p8", &TauG2Weights_ceBRe33_36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_36p0", &TauG2Weights_ceBRe33_36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_35p2", &TauG2Weights_ceBRe33_35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_34p4", &TauG2Weights_ceBRe33_34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_33p6", &TauG2Weights_ceBRe33_33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_32p8", &TauG2Weights_ceBRe33_32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_32p0", &TauG2Weights_ceBRe33_32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_31p2", &TauG2Weights_ceBRe33_31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_30p4", &TauG2Weights_ceBRe33_30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_29p6", &TauG2Weights_ceBRe33_29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_28p8", &TauG2Weights_ceBRe33_28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_28p0", &TauG2Weights_ceBRe33_28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_27p2", &TauG2Weights_ceBRe33_27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_26p4", &TauG2Weights_ceBRe33_26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_25p6", &TauG2Weights_ceBRe33_25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_24p8", &TauG2Weights_ceBRe33_24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_24p0", &TauG2Weights_ceBRe33_24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_23p2", &TauG2Weights_ceBRe33_23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_22p4", &TauG2Weights_ceBRe33_22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_21p6", &TauG2Weights_ceBRe33_21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_20p8", &TauG2Weights_ceBRe33_20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_20p0", &TauG2Weights_ceBRe33_20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_19p2", &TauG2Weights_ceBRe33_19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_18p4", &TauG2Weights_ceBRe33_18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_17p6", &TauG2Weights_ceBRe33_17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_16p8", &TauG2Weights_ceBRe33_16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_16p0", &TauG2Weights_ceBRe33_16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_15p2", &TauG2Weights_ceBRe33_15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_14p4", &TauG2Weights_ceBRe33_14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_13p6", &TauG2Weights_ceBRe33_13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_12p8", &TauG2Weights_ceBRe33_12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_12p0", &TauG2Weights_ceBRe33_12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_11p2", &TauG2Weights_ceBRe33_11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_10p4", &TauG2Weights_ceBRe33_10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_9p6", &TauG2Weights_ceBRe33_9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_8p8", &TauG2Weights_ceBRe33_8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_8p0", &TauG2Weights_ceBRe33_8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_7p2", &TauG2Weights_ceBRe33_7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_6p4", &TauG2Weights_ceBRe33_6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_5p6", &TauG2Weights_ceBRe33_5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_4p8", &TauG2Weights_ceBRe33_4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_4p0", &TauG2Weights_ceBRe33_4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_3p2", &TauG2Weights_ceBRe33_3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_2p4", &TauG2Weights_ceBRe33_2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_1p6", &TauG2Weights_ceBRe33_1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_0p8", &TauG2Weights_ceBRe33_0p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_0p0", &TauG2Weights_ceBRe33_0p0);

    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m40p0", &TauG2Weights_ceBRe33_m40p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m39p2", &TauG2Weights_ceBRe33_m39p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m38p4", &TauG2Weights_ceBRe33_m38p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m37p6", &TauG2Weights_ceBRe33_m37p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m36p8", &TauG2Weights_ceBRe33_m36p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m36p0", &TauG2Weights_ceBRe33_m36p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m35p2", &TauG2Weights_ceBRe33_m35p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m34p4", &TauG2Weights_ceBRe33_m34p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m33p6", &TauG2Weights_ceBRe33_m33p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m32p8", &TauG2Weights_ceBRe33_m32p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m32p0", &TauG2Weights_ceBRe33_m32p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m31p2", &TauG2Weights_ceBRe33_m31p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m30p4", &TauG2Weights_ceBRe33_m30p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m29p6", &TauG2Weights_ceBRe33_m29p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m28p8", &TauG2Weights_ceBRe33_m28p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m28p0", &TauG2Weights_ceBRe33_m28p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m27p2", &TauG2Weights_ceBRe33_m27p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m26p4", &TauG2Weights_ceBRe33_m26p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m25p6", &TauG2Weights_ceBRe33_m25p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m24p8", &TauG2Weights_ceBRe33_m24p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m24p0", &TauG2Weights_ceBRe33_m24p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m23p2", &TauG2Weights_ceBRe33_m23p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m22p4", &TauG2Weights_ceBRe33_m22p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m21p6", &TauG2Weights_ceBRe33_m21p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m20p8", &TauG2Weights_ceBRe33_m20p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m20p0", &TauG2Weights_ceBRe33_m20p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m19p2", &TauG2Weights_ceBRe33_m19p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m18p4", &TauG2Weights_ceBRe33_m18p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m17p6", &TauG2Weights_ceBRe33_m17p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m16p8", &TauG2Weights_ceBRe33_m16p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m16p0", &TauG2Weights_ceBRe33_m16p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m15p2", &TauG2Weights_ceBRe33_m15p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m14p4", &TauG2Weights_ceBRe33_m14p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m13p6", &TauG2Weights_ceBRe33_m13p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m12p8", &TauG2Weights_ceBRe33_m12p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m12p0", &TauG2Weights_ceBRe33_m12p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m11p2", &TauG2Weights_ceBRe33_m11p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m10p4", &TauG2Weights_ceBRe33_m10p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m9p6", &TauG2Weights_ceBRe33_m9p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m8p8", &TauG2Weights_ceBRe33_m8p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m8p0", &TauG2Weights_ceBRe33_m8p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m7p2", &TauG2Weights_ceBRe33_m7p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m6p4", &TauG2Weights_ceBRe33_m6p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m5p6", &TauG2Weights_ceBRe33_m5p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m4p8", &TauG2Weights_ceBRe33_m4p8);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m4p0", &TauG2Weights_ceBRe33_m4p0);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m3p2", &TauG2Weights_ceBRe33_m3p2);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m2p4", &TauG2Weights_ceBRe33_m2p4);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m1p6", &TauG2Weights_ceBRe33_m1p6);
    arbre->SetBranchAddress("TauG2Weights_ceBRe33_m0p8", &TauG2Weights_ceBRe33_m0p8);


    ami->SetBranchAddress("ntracks_friend", &ntracks_friend);
    ami->SetBranchAddress("ntracksAll_friend", &ntracksAll_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   int nbhist=1;
   int nbhist_offset=0;
   int nbhistMC=0;

   /*if (is_control==0){
      if (name!="data_obs"){
           nbhist=1+54+42;
           nbhist_offset=0;
           nbhistMC=54;
      }
      if (name=="data_obs"){
           nbhist=1+42;
           nbhist_offset=54;
           nbhistMC=54;
      }
   }*/

   if (is_control==0){
      if (name=="data_obs"){
           nbhist=1+42;
           nbhist_offset=54;
           nbhistMC=54;
      }
      else if (sample=="DY" or sample=="DYemu"){
           nbhist=1+54+42+6+4+2;
           nbhist_offset=0;
           nbhistMC=54+6+4+2;
      }
      else{
           nbhist=1+54+42;
           nbhist_offset=0;
           nbhistMC=54;
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
   /*float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,400,500};//mvis
   float bins1[] = {25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,110,120};//e pt
   float bins2[] = {20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};//tau pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//tau eta
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};//mt
   float bins7[] = {0,1,2,3,4,5,6,7,8,9,10,11};//njets
   //float bins7[] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};
   float bins8[] = {0,0.015,0.03,0.045,0.06,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6,0.625,0.65,0.675,0.7,0.725,0.75,0.775,0.8,0.825,0.85,0.875,0.9,0.925,0.95,0.975,1.0};//acoplanarity*/

   // Signal region
   float bins0[] = {55,70,85,100,150,200};//mvis
   float bins1[] = {55,70,85,100,150,200};//mvis
   //float bins0[] = {55,70,85,100,115,130,160,190,220};//mvis
   //float bins1[] = {55,70,85,100,115,130,160,190,220};//mvis
   float bins2[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins3[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins4[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins5[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins6[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins7[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins8[] = {40,55,70,85,100,125,150,200,350,500};//mvis

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

   float bins_taupt0[] = {30,40,50,75,100,200,300};
   int  binnum_taupt0 = sizeof(bins_taupt0)/sizeof(Float_t) - 1;
   float bins_taupt1[] = {20,22,24,26,28,30,35,40,45,50,60,80,100,150,200,300};
   int  binnum_taupt1 = sizeof(bins_taupt1)/sizeof(Float_t) - 1;
   float bins_taupt10[] = {20,22,24,26,28,30,35,40,45,50,60,80,100,150,200,250,300};
   int  binnum_taupt10 = sizeof(bins_taupt10)/sizeof(Float_t) - 1;
   float bins_taupt11[] = {20,22,24,26,28,30,35,40,45,50,60,80,100,150,200,250,300};
   int  binnum_taupt11 = sizeof(bins_taupt11)/sizeof(Float_t) - 1;

   //float bins_nt[] = {-1,0,1,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   float bins_nt[] = {-1,0,1,2,3,4,5,7,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100};
   int  binnum_nt = sizeof(bins_nt)/sizeof(Float_t) - 1;

   TH1F *h_tauFR_W_dm0_VVVL=new TH1F("h_tauFR_W_dm0_VVVL","h_tauFR_W_dm0_VVVL",binnum_taupt0,bins_taupt0); h_tauFR_W_dm0_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm1_VVVL=new TH1F("h_tauFR_W_dm1_VVVL","h_tauFR_W_dm1_VVVL",binnum_taupt1,bins_taupt1); h_tauFR_W_dm1_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm10_VVVL=new TH1F("h_tauFR_W_dm10_VVVL","h_tauFR_W_dm10_VVVL",binnum_taupt10,bins_taupt10); h_tauFR_W_dm10_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm11_VVVL=new TH1F("h_tauFR_W_dm11_VVVL","h_tauFR_W_dm11_VVVL",binnum_taupt11,bins_taupt11); h_tauFR_W_dm11_VVVL->Sumw2();
   TH1F *h_tauFR_W_dm0_M=new TH1F("h_tauFR_W_dm0_M","h_tauFR_W_dm0_M",binnum_taupt0,bins_taupt0); h_tauFR_W_dm0_M->Sumw2();
   TH1F *h_tauFR_W_dm1_M=new TH1F("h_tauFR_W_dm1_M","h_tauFR_W_dm1_M",binnum_taupt1,bins_taupt1); h_tauFR_W_dm1_M->Sumw2();
   TH1F *h_tauFR_W_dm10_M=new TH1F("h_tauFR_W_dm10_M","h_tauFR_W_dm10_M",binnum_taupt10,bins_taupt10); h_tauFR_W_dm10_M->Sumw2();
   TH1F *h_tauFR_W_dm11_M=new TH1F("h_tauFR_W_dm11_M","h_tauFR_W_dm11_M",binnum_taupt11,bins_taupt11); h_tauFR_W_dm11_M->Sumw2();

   TH1F *h_tauFR_QCD_dm0_VVVL=new TH1F("h_tauFR_QCD_dm0_VVVL","h_tauFR_QCD_dm0_VVVL",binnum_taupt0,bins_taupt0); h_tauFR_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm1_VVVL=new TH1F("h_tauFR_QCD_dm1_VVVL","h_tauFR_QCD_dm1_VVVL",binnum_taupt1,bins_taupt1); h_tauFR_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm10_VVVL=new TH1F("h_tauFR_QCD_dm10_VVVL","h_tauFR_QCD_dm10_VVVL",binnum_taupt10,bins_taupt10); h_tauFR_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm11_VVVL=new TH1F("h_tauFR_QCD_dm11_VVVL","h_tauFR_QCD_dm11_VVVL",binnum_taupt11,bins_taupt11); h_tauFR_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm0_M=new TH1F("h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_M",binnum_taupt0,bins_taupt0); h_tauFR_QCD_dm0_M->Sumw2();
   TH1F *h_tauFR_QCD_dm1_M=new TH1F("h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_M",binnum_taupt1,bins_taupt1); h_tauFR_QCD_dm1_M->Sumw2();
   TH1F *h_tauFR_QCD_dm10_M=new TH1F("h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_M",binnum_taupt10,bins_taupt10); h_tauFR_QCD_dm10_M->Sumw2();
   TH1F *h_tauFR_QCD_dm11_M=new TH1F("h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_M",binnum_taupt11,bins_taupt11); h_tauFR_QCD_dm11_M->Sumw2();

   TH1F *h_tauFRnt_W_dm0_VVVL=new TH1F("h_tauFRnt_W_dm0_VVVL","h_tauFRnt_W_dm0_VVVL",binnum_nt,bins_nt); h_tauFRnt_W_dm0_VVVL->Sumw2();
   TH1F *h_tauFRnt_W_dm1_VVVL=new TH1F("h_tauFRnt_W_dm1_VVVL","h_tauFRnt_W_dm1_VVVL",binnum_nt,bins_nt); h_tauFRnt_W_dm1_VVVL->Sumw2();
   TH1F *h_tauFRnt_W_dm10_VVVL=new TH1F("h_tauFRnt_W_dm10_VVVL","h_tauFRnt_W_dm10_VVVL",binnum_nt,bins_nt); h_tauFRnt_W_dm10_VVVL->Sumw2();
   TH1F *h_tauFRnt_W_dm11_VVVL=new TH1F("h_tauFRnt_W_dm11_VVVL","h_tauFRnt_W_dm11_VVVL",binnum_nt,bins_nt); h_tauFRnt_W_dm11_VVVL->Sumw2();
   TH1F *h_tauFRnt_W_dm0_M=new TH1F("h_tauFRnt_W_dm0_M","h_tauFRnt_W_dm0_M",binnum_nt,bins_nt); h_tauFRnt_W_dm0_M->Sumw2();
   TH1F *h_tauFRnt_W_dm1_M=new TH1F("h_tauFRnt_W_dm1_M","h_tauFRnt_W_dm1_M",binnum_nt,bins_nt); h_tauFRnt_W_dm1_M->Sumw2();
   TH1F *h_tauFRnt_W_dm10_M=new TH1F("h_tauFRnt_W_dm10_M","h_tauFRnt_W_dm10_M",binnum_nt,bins_nt); h_tauFRnt_W_dm10_M->Sumw2();
   TH1F *h_tauFRnt_W_dm11_M=new TH1F("h_tauFRnt_W_dm11_M","h_tauFRnt_W_dm11_M",binnum_nt,bins_nt); h_tauFRnt_W_dm11_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm0_VVVL=new TH1F("h_tauFRnt_QCD_dm0_VVVL","h_tauFRnt_QCD_dm0_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm1_VVVL=new TH1F("h_tauFRnt_QCD_dm1_VVVL","h_tauFRnt_QCD_dm1_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm10_VVVL=new TH1F("h_tauFRnt_QCD_dm10_VVVL","h_tauFRnt_QCD_dm10_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm11_VVVL=new TH1F("h_tauFRnt_QCD_dm11_VVVL","h_tauFRnt_QCD_dm11_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm0_M=new TH1F("h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm0_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm1_M=new TH1F("h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm1_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm10_M=new TH1F("h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm10_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm11_M=new TH1F("h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm11_M->Sumw2();

   TH1F *h_tauFR_QCD_xtrg_M=new TH1F("h_tauFR_QCD_xtrg_M","h_tauFR_QCD_xtrg_M",3,0,3); h_tauFR_QCD_xtrg_M->Sumw2();
   TH1F *h_tauFR_QCD_xtrg_VVVL=new TH1F("h_tauFR_QCD_xtrg_VVVL","h_tauFR_QCD_xtrg_VVVL",3,0,3); h_tauFR_QCD_xtrg_VVVL->Sumw2();
   TH1F *h_tauFR_W_xtrg_M=new TH1F("h_tauFR_W_xtrg_M","h_tauFR_W_xtrg_M",3,0,3); h_tauFR_W_xtrg_M->Sumw2();
   TH1F *h_tauFR_W_xtrg_VVVL=new TH1F("h_tauFR_W_xtrg_VVVL","h_tauFR_W_xtrg_VVVL",3,0,3); h_tauFR_W_xtrg_VVVL->Sumw2();

   TH1F *h_tauFRpt_QCD_xtrg_M=new TH1F("h_tauFRpt_QCD_xtrg_M","h_tauFRpt_QCD_xtrg_M",binnum_taupt0,bins_taupt0); h_tauFRpt_QCD_xtrg_M->Sumw2();
   TH1F *h_tauFRpt_QCD_xtrg_VVVL=new TH1F("h_tauFRpt_QCD_xtrg_VVVL","h_tauFRpt_QCD_xtrg_VVVL",binnum_taupt0,bins_taupt0); h_tauFRpt_QCD_xtrg_VVVL->Sumw2();
   TH1F *h_tauFRpt_QCD_etrg_M=new TH1F("h_tauFRpt_QCD_etrg_M","h_tauFRpt_QCD_etrg_M",binnum_taupt0,bins_taupt0); h_tauFRpt_QCD_etrg_M->Sumw2();
   TH1F *h_tauFRpt_QCD_etrg_VVVL=new TH1F("h_tauFRpt_QCD_etrg_VVVL","h_tauFRpt_QCD_etrg_VVVL",binnum_taupt0,bins_taupt0); h_tauFRpt_QCD_etrg_VVVL->Sumw2();

   TString uncertainties[67]={"","_CMS_tauid_stat1_dm0_yearDown","_CMS_tauid_stat1_dm0_yearUp","_CMS_tauid_stat1_dm1_yearDown","_CMS_tauid_stat1_dm1_yearUp","_CMS_tauid_stat1_dm10_yearDown","_CMS_tauid_stat1_dm10_yearUp","_CMS_tauid_stat1_dm11_yearDown","_CMS_tauid_stat1_dm11_yearUp","_CMS_tauid_stat2_dm0_yearDown","_CMS_tauid_stat2_dm0_yearUp","_CMS_tauid_stat2_dm1_yearDown","_CMS_tauid_stat2_dm1_yearUp","_CMS_tauid_stat2_dm10_yearDown","_CMS_tauid_stat2_dm10_yearUp","_CMS_tauid_stat2_dm11_yearDown","_CMS_tauid_stat2_dm11_yearUp","_CMS_tauid_syst_allerasDown","_CMS_tauid_syst_allerasUp","_CMS_tauid_syst_yearDown","_CMS_tauid_syst_yearUp","_CMS_tauid_syst_dm0_yearDown","_CMS_tauid_syst_dm0_yearUp","_CMS_tauid_syst_dm1_yearDown","_CMS_tauid_syst_dm1_yearUp","_CMS_tauid_syst_dm10_yearDown","_CMS_tauid_syst_dm10_yearUp","_CMS_tauid_syst_dm11_yearDown","_CMS_tauid_syst_dm11_yearUp","_CMS_taues_dm0_yearDown","_CMS_taues_dm0_yearUp","_CMS_taues_dm1_yearDown","_CMS_taues_dm1_yearUp","_CMS_taues_3prong_yearDown","_CMS_taues_3prong_yearUp","_CMS_etauFR_barrel_yearDown","_CMS_etauFR_barrel_yearUp","_CMS_etauFR_endcap_yearDown","_CMS_etauFR_endcap_yearUp","_CMS_etauFES_dm0_yearDown","_CMS_etauFES_dm0_yearUp","_CMS_etauFES_dm1_yearDown","_CMS_etauFES_dm1_yearUp","_CMS_pileup_yearDown","_CMS_pileup_yearUp","_CMS_etautrg_yearDown","_CMS_etautrg_yearUp","_CMS_etrg_yearDown","_CMS_etrg_yearUp","_CMS_elasticRescalingDown","_CMS_elasticRescalingUp","_CMS_L1PrefiringDown","_CMS_L1PrefiringUp","_CMS_elId_systDown","_CMS_elId_systUp","_CMS_ISRDown","_CMS_ISRUp","_CMS_FSRDown","_CMS_FSRUp","_CMS_PDFDown","_CMS_PDFUp","_CMS_muR0p5_muF0p5","_CMS_muRDown","_CMS_muFDown","_CMS_muFUp","_CMS_muRUp","_CMS_muR2p0_muF2p0"};

   for (int k = 0; k < 55; ++k){
      if (year=="2016pre") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016preVFP");
      if (year=="2016post") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016postVFP");
      if (year=="2017") uncertainties[k]=uncertainties[k].ReplaceAll("year","2017");
      if (year=="2018") uncertainties[k]=uncertainties[k].ReplaceAll("year","2018");
   }


   TString fake_uncertainties[42]={"_CMS_jetfake_w_invertMTDown","_CMS_jetfake_w_invertMTUp","_CMS_jetfake_qcd_invertOSDown","_CMS_jetfake_qcd_invertOSUp","_CMS_jetfake_tauptextrap_w_et_dm0_yearDown","_CMS_jetfake_tauptextrap_w_et_dm0_yearUp","_CMS_jetfake_tauptextrap_w_et_dm1_yearDown","_CMS_jetfake_tauptextrap_w_et_dm1_yearUp","_CMS_jetfake_tauptextrap_w_et_dm10_yearDown","_CMS_jetfake_tauptextrap_w_et_dm10_yearUp","_CMS_jetfake_tauptextrap_w_et_dm11_yearDown","_CMS_jetfake_tauptextrap_w_et_dm11_yearUp","_CMS_jetfake_tauptextrap_qcd_et_dm0_yearDown","_CMS_jetfake_tauptextrap_qcd_et_dm0_yearUp","_CMS_jetfake_tauptextrap_qcd_et_dm1_yearDown","_CMS_jetfake_tauptextrap_qcd_et_dm1_yearUp","_CMS_jetfake_tauptextrap_qcd_et_dm10_yearDown","_CMS_jetfake_tauptextrap_qcd_et_dm10_yearUp","_CMS_jetfake_tauptextrap_qcd_et_dm11_yearDown","_CMS_jetfake_tauptextrap_qcd_et_dm11_yearUp","_CMS_jetfake_wfractionDown","_CMS_jetfake_wfractionUp","_CMS_jetfake_ntracksextrap_w_et_dm0_yearDown","_CMS_jetfake_ntracksextrap_w_et_dm0_yearUp","_CMS_jetfake_ntracksextrap_w_et_dm1_yearDown","_CMS_jetfake_ntracksextrap_w_et_dm1_yearUp","_CMS_jetfake_ntracksextrap_w_et_dm10_yearDown","_CMS_jetfake_ntracksextrap_w_et_dm10_yearUp","_CMS_jetfake_ntracksextrap_w_et_dm11_yearDown","_CMS_jetfake_ntracksextrap_w_et_dm11_yearUp","_CMS_jetfake_ntracksextrap_qcd_et_dm0_yearDown","_CMS_jetfake_ntracksextrap_qcd_et_dm0_yearUp","_CMS_jetfake_ntracksextrap_qcd_et_dm1_yearDown","_CMS_jetfake_ntracksextrap_qcd_et_dm1_yearUp","_CMS_jetfake_ntracksextrap_qcd_et_dm10_yearDown","_CMS_jetfake_ntracksextrap_qcd_et_dm10_yearUp","_CMS_jetfake_ntracksextrap_qcd_et_dm11_yearDown","_CMS_jetfake_ntracksextrap_qcd_et_dm11_yearUp","_CMS_jetfake_ntracksextrap_w_et_yearDown","_CMS_jetfake_ntracksextrap_w_et_yearUp","_CMS_jetfake_ntracksextrap_qcd_et_yearDown","_CMS_jetfake_ntracksextrap_qcd_et_yearUp"};

   for (int k = 0; k < 42; ++k){
      if (year=="2016pre") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2016preVFP");
      if (year=="2016post") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2016postVFP");
      if (year=="2017") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2017");
      if (year=="2018") fake_uncertainties[k]=fake_uncertainties[k].ReplaceAll("year","2018");
   }

   TFile* f_DYEFT6p7=new TFile("Ztautau_CtauB_6p7.root","read");
   TH1F* h_DYEFT6p7= (TH1F*) f_DYEFT6p7->Get("hratioup");

   TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_EGM2D.root","read");
   TH2F* h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
   TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root","read");
   TH2F* h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");

   if (year=="2017"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_EGM2D_MVA80iso_UL17.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2017.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   }
   else if (year=="2016post"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_postVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016postVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   }
   else if (year=="2016pre"){
      TFile* f_eleIDSF=new TFile("scalefactors/egammaEffi.txt_Ele_wp80iso_preVFP_EGM2D.root","read");
      h_eleIDSF= (TH2F*) f_eleIDSF->Get("EGamma_SF2D");
      TFile* f_eleRecoSF=new TFile("scalefactors/egammaEffi_ptAbove20.txt_EGM2D_UL2016preVFP.root","read");
      h_eleRecoSF= (TH2F*) f_eleRecoSF->Get("EGamma_SF2D");
   }

   /*TFile* f_etautrgSF=new TFile("scalefactors/electron_SF_etautrg_2018UL.root","read");
   TH2F* h_etautrgData= (TH2F*) f_etautrgSF->Get("data_trg_eff");
   TH2F* h_etautrgMC= (TH2F*) f_etautrgSF->Get("ZLL_trg_eff");
   TFile* f_e32trgSF=new TFile("scalefactors/electron_SF_e32trg_2018UL.root","read");
   TH2F* h_e32trgData= (TH2F*) f_etautrgSF->Get("data_trg_eff");
   TH2F* h_e32trgMC= (TH2F*) f_etautrgSF->Get("ZLL_trg_eff");*/

   TFile* f_etautrgSF=new TFile("scalefactors/sf_el_2018_HLTEle24Tau30.root","read");
   TH2F* h_etautrgSF= (TH2F*) f_etautrgSF->Get("SF2D");
   TFile* f_etrgSF=new TFile("scalefactors/sf_el_2018_HLTEle32.root","read");
   TH2F* h_etrgSF= (TH2F*) f_etrgSF->Get("SF2D");
   if (year=="2017"){
      TFile* f_etautrgSF=new TFile("scalefactors/sf_el_2017_HLTEle24Tau30.root","read");
      h_etautrgSF= (TH2F*) f_etautrgSF->Get("SF2D");
      TFile* f_etrgSF=new TFile("scalefactors/sf_el_2017_HLTEle32.root","read");
      h_etrgSF= (TH2F*) f_etrgSF->Get("SF2D");
   }
   else if (year=="2016pre"){
      TFile* f_etrgSF=new TFile("scalefactors/sf_el_2016pre_HLTEle25.root","read");
      h_etrgSF= (TH2F*) f_etrgSF->Get("SF2D");
   }
   else if (year=="2016post"){
      TFile* f_etrgSF=new TFile("scalefactors/sf_el_2016post_HLTEle25.root","read");
      h_etrgSF= (TH2F*) f_etrgSF->Get("SF2D");
   }

   TFile* f_taufr = new TFile("fakerate/FitValues_tauFR_2018.root");

   TH1F *err_nt0_ffW = (TH1F*) f_taufr->Get("err_nt0_ffW");
   TH1F *err_nt0_ffQCD = (TH1F*) f_taufr->Get("err_nt0_ffQCD");

   TF1 *fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
   TF1 *fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
   TF1 *fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
   TF1 *fit_taufr_QCD_dm11 = (TF1*) f_taufr->Get("theFit_QCD_dm11");
   TF1 *fit_taufr_W_dm0 = (TF1*) f_taufr->Get("theFit_W_dm0");
   TF1 *fit_taufr_W_dm1 = (TF1*) f_taufr->Get("theFit_W_dm1");
   TF1 *fit_taufr_W_dm10 = (TF1*) f_taufr->Get("theFit_W_dm10");
   TF1 *fit_taufr_W_dm11 = (TF1*) f_taufr->Get("theFit_W_dm11");

   TF1 *fit_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm0");
   TF1 *fit_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm1");
   TF1 *fit_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm10");
   TF1 *fit_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm11");
   TF1 *fit_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit_nt_W_dm0");
   TF1 *fit_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit_nt_W_dm1");
   TF1 *fit_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit_nt_W_dm10");
   TF1 *fit_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit_nt_W_dm11");

   TF1 *fitlow_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm0");
   TF1 *fitlow_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm1");
   TF1 *fitlow_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm10");
   TF1 *fitlow_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm11");
   TF1 *fitlow_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit2_nt_W_dm0");
   TF1 *fitlow_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit2_nt_W_dm1");
   TF1 *fitlow_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit2_nt_W_dm10");
   TF1 *fitlow_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit2_nt_W_dm11");

   TH1F *corr_taufr_QCD_xtrg = (TH1F*) f_taufr->Get("h_tauFR_QCD_xtrg_M");
   TH1F *corr_taufr_W_xtrg = (TH1F*) f_taufr->Get("h_tauFR_W_xtrg_M");

   if (year=="2016pre"){
      TFile* f_taufr = new TFile("fakerate/FitValues_tauFR_2016pre.root"); 
      fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
      fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
      fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
      fit_taufr_QCD_dm11 = (TF1*) f_taufr->Get("theFit_QCD_dm11");
      fit_taufr_W_dm0 = (TF1*) f_taufr->Get("theFit_W_dm0");
      fit_taufr_W_dm1 = (TF1*) f_taufr->Get("theFit_W_dm1");
      fit_taufr_W_dm10 = (TF1*) f_taufr->Get("theFit_W_dm10");
      fit_taufr_W_dm11 = (TF1*) f_taufr->Get("theFit_W_dm11");

      fit_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm0");
      fit_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm1");
      fit_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm10");
      fit_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm11");
      fit_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit_nt_W_dm0");
      fit_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit_nt_W_dm1");
      fit_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit_nt_W_dm10");
      fit_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit_nt_W_dm11");

      fitlow_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm0");
      fitlow_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm1");
      fitlow_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm10");
      fitlow_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm11");
      fitlow_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit2_nt_W_dm0");
      fitlow_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit2_nt_W_dm1");
      fitlow_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit2_nt_W_dm10");
      fitlow_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit2_nt_W_dm11");

      corr_taufr_QCD_xtrg = (TH1F*) f_taufr->Get("theFit_QCD_xtrg");
      corr_taufr_W_xtrg = (TH1F*) f_taufr->Get("theFit_W_xtrg");
   }

   if (year=="2016post"){
      TFile* f_taufr = new TFile("fakerate/FitValues_tauFR_2016post.root");
      fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
      fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
      fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
      fit_taufr_QCD_dm11 = (TF1*) f_taufr->Get("theFit_QCD_dm11");
      fit_taufr_W_dm0 = (TF1*) f_taufr->Get("theFit_W_dm0");
      fit_taufr_W_dm1 = (TF1*) f_taufr->Get("theFit_W_dm1");
      fit_taufr_W_dm10 = (TF1*) f_taufr->Get("theFit_W_dm10");
      fit_taufr_W_dm11 = (TF1*) f_taufr->Get("theFit_W_dm11");

      fit_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm0");
      fit_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm1");
      fit_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm10");
      fit_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm11");
      fit_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit_nt_W_dm0");
      fit_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit_nt_W_dm1");
      fit_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit_nt_W_dm10");
      fit_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit_nt_W_dm11");

      fitlow_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm0");
      fitlow_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm1");
      fitlow_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm10");
      fitlow_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm11");
      fitlow_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit2_nt_W_dm0");
      fitlow_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit2_nt_W_dm1");
      fitlow_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit2_nt_W_dm10");
      fitlow_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit2_nt_W_dm11");

      corr_taufr_QCD_xtrg = (TH1F*) f_taufr->Get("theFit_QCD_xtrg");
      corr_taufr_W_xtrg = (TH1F*) f_taufr->Get("theFit_W_xtrg");
   }

   if (year=="2017"){
      TFile* f_taufr = new TFile("fakerate/FitValues_tauFR_2017.root");
      fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
      fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
      fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
      fit_taufr_QCD_dm11 = (TF1*) f_taufr->Get("theFit_QCD_dm11");
      fit_taufr_W_dm0 = (TF1*) f_taufr->Get("theFit_W_dm0");
      fit_taufr_W_dm1 = (TF1*) f_taufr->Get("theFit_W_dm1");
      fit_taufr_W_dm10 = (TF1*) f_taufr->Get("theFit_W_dm10");
      fit_taufr_W_dm11 = (TF1*) f_taufr->Get("theFit_W_dm11");

      fit_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm0");
      fit_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm1");
      fit_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm10");
      fit_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit_nt_QCD_dm11");
      fit_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit_nt_W_dm0");
      fit_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit_nt_W_dm1");
      fit_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit_nt_W_dm10");
      fit_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit_nt_W_dm11");

      fitlow_taufrnt_QCD_dm0 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm0");
      fitlow_taufrnt_QCD_dm1 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm1");
      fitlow_taufrnt_QCD_dm10 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm10");
      fitlow_taufrnt_QCD_dm11 = (TF1*) f_taufr->Get("theFit2_nt_QCD_dm11");
      fitlow_taufrnt_W_dm0 = (TF1*) f_taufr->Get("theFit2_nt_W_dm0");
      fitlow_taufrnt_W_dm1 = (TF1*) f_taufr->Get("theFit2_nt_W_dm1");
      fitlow_taufrnt_W_dm10 = (TF1*) f_taufr->Get("theFit2_nt_W_dm10");
      fitlow_taufrnt_W_dm11 = (TF1*) f_taufr->Get("theFit2_nt_W_dm11");

      corr_taufr_QCD_xtrg = (TH1F*) f_taufr->Get("h_tauFR_QCD_xtrg_M");
      corr_taufr_W_xtrg = (TH1F*) f_taufr->Get("h_tauFR_W_xtrg_M");
   }

   TH2F *fractionOS=new TH2F("fractionOS","fractionOS",3,0,75,4,50,250);
   TH2F *fractionSS=new TH2F("fractionSS","fractionSS",3,0,75,4,50,250);
   TH1F *fractionNtrackOS=new TH1F("fractionNtrackOS","fractionNtrackOS",14,0,70);
   TH1F *fractionNtrackSS=new TH1F("fractionNtrackSS","fractionNtrackSS",14,0,70);
   TH1F *fractionAcoplanarityOS=new TH1F("fractionAcoplanarityOS","fractionAcoplanarityOS",21,-0.05,1.0);
   TH1F *fractionAcoplanaritySS=new TH1F("fractionAcoplanaritySS","fractionAcoplanaritySS",21,-0.05,1.0);

   //TFile* f_frac=new TFile("output_etau_2018/fractions.root","read");
   TFile* f_frac=new TFile("fakerate/fractions_2018.root","read");
   TH2F* h_fracW= (TH2F*) f_frac->Get("frac_W");

   TH1F* h_vtxresolution_PV = new TH1F("h_vtxresolution_PV","h_vtxresolution_PV",200,-1,1); h_vtxresolution_PV->Sumw2();
   TH1F* h_vtxresolution_simpleditau = new TH1F("h_vtxresolution_simpleditau","h_vtxresolution_simpleditau",200,-1,1); h_vtxresolution_simpleditau->Sumw2();
   TH1F* h_ntracks = new TH1F("h_ntracks","h_ntracks",30,0,30); h_ntracks->Sumw2();
   TH1F* h_aco = new TH1F("h_aco","h_aco",60,0.0,0.3); h_aco->Sumw2();

   TH1F* h_ptll = new TH1F("h_ptll","h_ptll",50,0.0,100.0); h_ptll->Sumw2();
   TH1F* h_dz = new TH1F("h_dz","h_dz",32,0.0,0.4); h_dz->Sumw2();

   Int_t nentries_wtn = (Int_t) arbre->GetEntries();

   /* arbre->SetCacheLearnEntries(1);
    arbre->SetCacheSize(1000000U);
    arbre->SetCacheEntryRange(0,nentries_wtn);
    arbre->AddBranchToCache("*",true);*/

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
   auto b2_3=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1");

   auto b2_2017_1=arbre->GetBranch("HLT_Ele32_WPTight_Gsf_L1DoubleEG");
   auto b2_2017_2=arbre->GetBranch("HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1");

   auto b2_2016_1=arbre->GetBranch("HLT_Ele25_eta2p1_WPTight_Gsf");
   auto b2_2016_2=arbre->GetBranch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20");
   auto b2_2016_3=arbre->GetBranch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau20_SingleL1");
   auto b2_2016_4=arbre->GetBranch("HLT_Ele24_eta2p1_WPLoose_Gsf_LooseIsoPFTau30");

   auto b2_4=arbre->GetBranch("run");

   auto b3_1=arbre->GetBranch("LepCand_vse");
   auto b3_2=arbre->GetBranch("LepCand_vsmu");
   auto b3_3=arbre->GetBranch("LepCand_vsjet");
   auto b3_4=arbre->GetBranch("LepCand_charge");
   auto b3_5=arbre->GetBranch("LepCand_eleMVAiso80");
   auto b3_6=arbre->GetBranch("LepCand_DecayMode");
   auto b3_7=arbre->GetBranch("LepCand_trgmatch");

   auto b4_1=arbre->GetBranch("pu_weight");
   auto b4_2=arbre->GetBranch("genWeight");
   auto b4_3=arbre->GetBranch("LepCand_tauidMsf");
   auto b4_4=arbre->GetBranch("LepCand_antielesf");
   auto b4_5=arbre->GetBranch("LepCand_antimusf");
   auto b4_6=arbre->GetBranch("LepCand_tautriggersf");
   auto b4_7=arbre->GetBranch("PV_npvs");
   auto b4_8=arbre->GetBranch("LepCand_antielesf_up");
   auto b4_9=arbre->GetBranch("LepCand_antimusf_up");
   auto b4_10=arbre->GetBranch("LepCand_tautriggersf_up");
   auto b4_11=arbre->GetBranch("LepCand_antielesf_down");
   auto b4_12=arbre->GetBranch("LepCand_antimusf_down");
   auto b4_13=arbre->GetBranch("LepCand_tautriggersf_down");
   auto b4_14=arbre->GetBranch("LepCand_tauidMsf_syst_dm_era_down");
   auto b4_15=arbre->GetBranch("LepCand_tauidMsf_syst_era_down");
   auto b4_16=arbre->GetBranch("LepCand_tauidMsf_syst_alleras_down");
   auto b4_17=arbre->GetBranch("LepCand_tauidMsf_uncert1_down");
   auto b4_18=arbre->GetBranch("LepCand_tauidMsf_uncert0_down");
   auto b4_19=arbre->GetBranch("LepCand_tauidMsf_syst_dm_era_up");
   auto b4_20=arbre->GetBranch("LepCand_tauidMsf_syst_era_up");
   auto b4_21=arbre->GetBranch("LepCand_tauidMsf_syst_alleras_up");
   auto b4_22=arbre->GetBranch("LepCand_tauidMsf_uncert1_up");
   auto b4_23=arbre->GetBranch("LepCand_tauidMsf_uncert0_up");
   auto b4_24=arbre->GetBranch("puWeight");
   auto b4_25=arbre->GetBranch("puWeightUp");
   auto b4_26=arbre->GetBranch("puWeightDown");
   auto b4_27=arbre->GetBranch("nGenCand");
   auto b4_28=arbre->GetBranch("GenCand_id");
   auto b4_29=arbre->GetBranch("GenCand_pt");
   auto b4_30=arbre->GetBranch("GenCand_eta");
   auto b4_31=arbre->GetBranch("GenCand_phi");
   auto b4_32=arbre->GetBranch("L1PreFiringWeight_Nom");
   auto b4_33=arbre->GetBranch("L1PreFiringWeight_Up");
   auto b4_34=arbre->GetBranch("L1PreFiringWeight_Dn");
   auto b4_35=arbre->GetBranch("LHEPdfWeight");
   auto b4_36=arbre->GetBranch("LHEScaleWeight");
   auto b4_37=arbre->GetBranch("PSWeight");


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

   auto b9_1=arbre->GetBranch("TauG2Weights_ceBRe33_0p0");
   auto b9_2=arbre->GetBranch("TauG2Weights_ceBRe33_0p8");
   auto b9_3=arbre->GetBranch("TauG2Weights_ceBRe33_1p6");
   auto b9_4=arbre->GetBranch("TauG2Weights_ceBRe33_2p4");
   auto b9_5=arbre->GetBranch("TauG2Weights_ceBRe33_3p2");
   auto b9_6=arbre->GetBranch("TauG2Weights_ceBRe33_4p0");
   auto b9_7=arbre->GetBranch("TauG2Weights_ceBRe33_4p8");
   auto b9_8=arbre->GetBranch("TauG2Weights_ceBRe33_5p6");
   auto b9_9=arbre->GetBranch("TauG2Weights_ceBRe33_6p4");
   auto b9_10=arbre->GetBranch("TauG2Weights_ceBRe33_7p2");
   auto b9_11=arbre->GetBranch("TauG2Weights_ceBRe33_8p0");
   auto b9_12=arbre->GetBranch("TauG2Weights_ceBRe33_8p8");
   auto b9_13=arbre->GetBranch("TauG2Weights_ceBRe33_9p6");
   auto b9_14=arbre->GetBranch("TauG2Weights_ceBRe33_10p4");
   auto b9_15=arbre->GetBranch("TauG2Weights_ceBRe33_11p2");
   auto b9_16=arbre->GetBranch("TauG2Weights_ceBRe33_12p0");
   auto b9_17=arbre->GetBranch("TauG2Weights_ceBRe33_12p8");
   auto b9_18=arbre->GetBranch("TauG2Weights_ceBRe33_13p6");
   auto b9_19=arbre->GetBranch("TauG2Weights_ceBRe33_14p4");
   auto b9_20=arbre->GetBranch("TauG2Weights_ceBRe33_15p2");
   auto b9_21=arbre->GetBranch("TauG2Weights_ceBRe33_16p0");
   auto b9_22=arbre->GetBranch("TauG2Weights_ceBRe33_16p8");
   auto b9_23=arbre->GetBranch("TauG2Weights_ceBRe33_17p6");
   auto b9_24=arbre->GetBranch("TauG2Weights_ceBRe33_18p4");
   auto b9_25=arbre->GetBranch("TauG2Weights_ceBRe33_19p2");
   auto b9_26=arbre->GetBranch("TauG2Weights_ceBRe33_20p0");
   auto b9_27=arbre->GetBranch("TauG2Weights_ceBRe33_20p8");
   auto b9_28=arbre->GetBranch("TauG2Weights_ceBRe33_21p6");
   auto b9_29=arbre->GetBranch("TauG2Weights_ceBRe33_22p4");
   auto b9_30=arbre->GetBranch("TauG2Weights_ceBRe33_23p2");
   auto b9_31=arbre->GetBranch("TauG2Weights_ceBRe33_24p0");
   auto b9_32=arbre->GetBranch("TauG2Weights_ceBRe33_24p8");
   auto b9_33=arbre->GetBranch("TauG2Weights_ceBRe33_25p6");
   auto b9_34=arbre->GetBranch("TauG2Weights_ceBRe33_26p4");
   auto b9_35=arbre->GetBranch("TauG2Weights_ceBRe33_27p2");
   auto b9_36=arbre->GetBranch("TauG2Weights_ceBRe33_28p0");
   auto b9_37=arbre->GetBranch("TauG2Weights_ceBRe33_28p8");
   auto b9_38=arbre->GetBranch("TauG2Weights_ceBRe33_29p6");
   auto b9_39=arbre->GetBranch("TauG2Weights_ceBRe33_30p4");
   auto b9_40=arbre->GetBranch("TauG2Weights_ceBRe33_31p2");
   auto b9_41=arbre->GetBranch("TauG2Weights_ceBRe33_32p0");
   auto b9_42=arbre->GetBranch("TauG2Weights_ceBRe33_32p8");
   auto b9_43=arbre->GetBranch("TauG2Weights_ceBRe33_33p6");
   auto b9_44=arbre->GetBranch("TauG2Weights_ceBRe33_34p4");
   auto b9_45=arbre->GetBranch("TauG2Weights_ceBRe33_35p2");
   auto b9_46=arbre->GetBranch("TauG2Weights_ceBRe33_36p0");
   auto b9_47=arbre->GetBranch("TauG2Weights_ceBRe33_36p8");
   auto b9_48=arbre->GetBranch("TauG2Weights_ceBRe33_37p6");
   auto b9_49=arbre->GetBranch("TauG2Weights_ceBRe33_38p4");
   auto b9_50=arbre->GetBranch("TauG2Weights_ceBRe33_39p2");
   auto b9_51=arbre->GetBranch("TauG2Weights_ceBRe33_40p0");

   auto b9_52=arbre->GetBranch("TauG2Weights_ceBRe33_m0p8");
   auto b9_53=arbre->GetBranch("TauG2Weights_ceBRe33_m1p6");
   auto b9_54=arbre->GetBranch("TauG2Weights_ceBRe33_m2p4");
   auto b9_55=arbre->GetBranch("TauG2Weights_ceBRe33_m3p2");
   auto b9_56=arbre->GetBranch("TauG2Weights_ceBRe33_m4p0");
   auto b9_57=arbre->GetBranch("TauG2Weights_ceBRe33_m4p8");
   auto b9_58=arbre->GetBranch("TauG2Weights_ceBRe33_m5p6");
   auto b9_59=arbre->GetBranch("TauG2Weights_ceBRe33_m6p4");
   auto b9_60=arbre->GetBranch("TauG2Weights_ceBRe33_m7p2");
   auto b9_61=arbre->GetBranch("TauG2Weights_ceBRe33_m8p0");
   auto b9_62=arbre->GetBranch("TauG2Weights_ceBRe33_m8p8");
   auto b9_63=arbre->GetBranch("TauG2Weights_ceBRe33_m9p6");
   auto b9_64=arbre->GetBranch("TauG2Weights_ceBRe33_m10p4");
   auto b9_65=arbre->GetBranch("TauG2Weights_ceBRe33_m11p2");
   auto b9_66=arbre->GetBranch("TauG2Weights_ceBRe33_m12p0");
   auto b9_67=arbre->GetBranch("TauG2Weights_ceBRe33_m12p8");
   auto b9_68=arbre->GetBranch("TauG2Weights_ceBRe33_m13p6");
   auto b9_69=arbre->GetBranch("TauG2Weights_ceBRe33_m14p4");
   auto b9_70=arbre->GetBranch("TauG2Weights_ceBRe33_m15p2");
   auto b9_71=arbre->GetBranch("TauG2Weights_ceBRe33_m16p0");
   auto b9_72=arbre->GetBranch("TauG2Weights_ceBRe33_m16p8");
   auto b9_73=arbre->GetBranch("TauG2Weights_ceBRe33_m17p6");
   auto b9_74=arbre->GetBranch("TauG2Weights_ceBRe33_m18p4");
   auto b9_75=arbre->GetBranch("TauG2Weights_ceBRe33_m19p2");
   auto b9_76=arbre->GetBranch("TauG2Weights_ceBRe33_m20p0");
   auto b9_77=arbre->GetBranch("TauG2Weights_ceBRe33_m20p8");
   auto b9_78=arbre->GetBranch("TauG2Weights_ceBRe33_m21p6");
   auto b9_79=arbre->GetBranch("TauG2Weights_ceBRe33_m22p4");
   auto b9_80=arbre->GetBranch("TauG2Weights_ceBRe33_m23p2");
   auto b9_81=arbre->GetBranch("TauG2Weights_ceBRe33_m24p0");
   auto b9_82=arbre->GetBranch("TauG2Weights_ceBRe33_m24p8");
   auto b9_83=arbre->GetBranch("TauG2Weights_ceBRe33_m25p6");
   auto b9_84=arbre->GetBranch("TauG2Weights_ceBRe33_m26p4");
   auto b9_85=arbre->GetBranch("TauG2Weights_ceBRe33_m27p2");
   auto b9_86=arbre->GetBranch("TauG2Weights_ceBRe33_m28p0");
   auto b9_87=arbre->GetBranch("TauG2Weights_ceBRe33_m28p8");
   auto b9_88=arbre->GetBranch("TauG2Weights_ceBRe33_m29p6");
   auto b9_89=arbre->GetBranch("TauG2Weights_ceBRe33_m30p4");
   auto b9_90=arbre->GetBranch("TauG2Weights_ceBRe33_m31p2");
   auto b9_91=arbre->GetBranch("TauG2Weights_ceBRe33_m32p0");
   auto b9_92=arbre->GetBranch("TauG2Weights_ceBRe33_m32p8");
   auto b9_93=arbre->GetBranch("TauG2Weights_ceBRe33_m33p6");
   auto b9_94=arbre->GetBranch("TauG2Weights_ceBRe33_m34p4");
   auto b9_95=arbre->GetBranch("TauG2Weights_ceBRe33_m35p2");
   auto b9_96=arbre->GetBranch("TauG2Weights_ceBRe33_m36p0");
   auto b9_97=arbre->GetBranch("TauG2Weights_ceBRe33_m36p8");
   auto b9_98=arbre->GetBranch("TauG2Weights_ceBRe33_m37p6");
   auto b9_99=arbre->GetBranch("TauG2Weights_ceBRe33_m38p4");
   auto b9_100=arbre->GetBranch("TauG2Weights_ceBRe33_m39p2");
   auto b9_101=arbre->GetBranch("TauG2Weights_ceBRe33_m40p0");

cout<<"g2 branches"<<endl;
   TFile* f_aco=new TFile("correction_acoplanarity_2018.root","read");
   TF1* fit_aco = (TF1*) f_aco->Get("fit_A");

   TFile* f_aco_fine=new TFile("new_new_correction_acoplanarity_fine_2018.root","read");
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
   TF1* fit_aco_all = (TF1*) f_aco_fine->Get("fit_acoplanarity");

   TFile *f_punt=new TFile("corrs_ntracks_pu_UL2018.root");
   TH2F* correction_map=(TH2F*) f_punt->Get("corr");

   TFile *f_hsnt=new TFile("corrs_ntracks_hs_UL2018.root");
   TH2F* correction_mapHS=(TH2F*) f_hsnt->Get("correction_map");

   if (year=="2017"){
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

   if (year=="2016pre"){
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

   if (year=="2016post"){
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

   TH1F* h_mvis_nt0 = new TH1F("h_mvis_nt0","h_mvis_nt0",20,0,200);
   TH1F* h_mvis_nt1 = new TH1F("h_mvis_nt1","h_mvis_nt1",20,0,200);
   TH1F* h_mvis_nt2 = new TH1F("h_mvis_nt2","h_mvis_nt2",20,0,200);
   TH1F* h_mvis_nt3 = new TH1F("h_mvis_nt3","h_mvis_nt3",20,0,200);
   TH1F* h_mvis_nt4 = new TH1F("h_mvis_nt4","h_mvis_nt4",20,0,200);
   TH1F* h_mvis_nt5 = new TH1F("h_mvis_nt5","h_mvis_nt5",20,0,200);
   TH1F* h_mvis_nt6 = new TH1F("h_mvis_nt6","h_mvis_nt6",20,0,200);
   TH1F* h_mvis_nt7 = new TH1F("h_mvis_nt7","h_mvis_nt7",20,0,200);
   TH1F* h_mvis_nt8 = new TH1F("h_mvis_nt8","h_mvis_nt8",20,0,200);
   TH1F* h_mvis_nt9 = new TH1F("h_mvis_nt9","h_mvis_nt9",20,0,200);

   TH1F* h_mvis_nt0to10 = new TH1F("h_mvis_nt0to10","h_mvis_nt0to10",20,0,200);
   TH1F* h_mvis_nt10to20 = new TH1F("h_mvis_nt10to20","h_mvis_nt10to20",20,0,200);
   TH1F* h_mvis_nt20to30 = new TH1F("h_mvis_nt20to30","h_mvis_nt20to30",20,0,200);
   TH1F* h_mvis_nt30to40 = new TH1F("h_mvis_nt30to40","h_mvis_nt30to40",20,0,200);
   TH1F* h_mvis_nt40to50 = new TH1F("h_mvis_nt40to50","h_mvis_nt40to50",20,0,200);
   TH1F* h_mvis_nt50to60 = new TH1F("h_mvis_nt50to60","h_mvis_nt50to60",20,0,200);
   TH1F* h_mvis_nt60to70 = new TH1F("h_mvis_nt60to70","h_mvis_nt60to70",20,0,200);
   TH1F* h_mvis_nt70to80 = new TH1F("h_mvis_nt70to80","h_mvis_nt70to80",20,0,200);
   TH1F* h_mvis_nt80to90 = new TH1F("h_mvis_nt80to90","h_mvis_nt80to90",20,0,200);
   TH1F* h_mvis_nt90to100 = new TH1F("h_mvis_nt90to100","h_mvis_nt90to100",20,0,200);

   cout<<luminosity*nnlo/LW<<endl;
   cout<<luminosity*nnlo/(LW+LW1)<<endl;
   cout<<luminosity*nnlo/(LW+LW2)<<endl;
   cout<<luminosity*nnlo/(LW+LW3)<<endl;
   cout<<luminosity*nnlo/(LW+LW4)<<endl;

   TH1F* h_acoplanarity = new TH1F("h_acoplanarity","h_acoplanarity",25,0.0,0.025);
   TH1F* h_genacoplanarity = new TH1F("h_genacoplanarity","h_genacoplanarity",25,0.0,0.025);
   TH1F* h_acoplanarity_sumptlt100 = new TH1F("h_acoplanarity_sumptlt100","h_acoplanarity_sumptlt100",25,0.0,0.025);
   TH1F* h_acoplanarity_sumptgt100 = new TH1F("h_acoplanarity_sumptgt100","h_acoplanarity_sumptgt100",25,0.0,0.025);

   TH1F* h_resolution_acoplanarity = new TH1F("h_resolution_acoplanarity","h_resolution_acoplanarity",30,-0.01,0.02);
   TH1F* h_resolution_acoplanarity_sumptlt100 = new TH1F("h_resolution_acoplanarity_sumptlt100","h_resolution_acoplanarity_sumptlt100",30,-0.01,0.02);
   TH1F* h_resolution_acoplanarity_sumptgt100 = new TH1F("h_resolution_acoplanarity_sumptgt100","h_resolution_acoplanarity_sumptgt100",30,-0.01,0.02);

   TH1F* h_DY_ABCD=new TH1F("h_DY_ABCD","h_DY_ABCD",6,0,6); h_DY_ABCD->Sumw2();

   TH1F* h_DY_mvis_waco=new TH1F("h_DY_mvis_waco","h_DY_mvis_waco",20,50,150); h_DY_mvis_waco->Sumw2();
   TH1F* h_DY_ptZ_waco=new TH1F("h_DY_ptZ_waco","h_DY_ptZ_waco",20,0,100); h_DY_ptZ_waco->Sumw2();
   TH1F* h_DY_aco_waco=new TH1F("h_DY_aco_waco","h_DY_aco_waco",20,0,1); h_DY_aco_waco->Sumw2();
   TH1F* h_DY_mvis_noaco=new TH1F("h_DY_mvis_noaco","h_DY_mvis_noaco",20,50,150); h_DY_mvis_noaco->Sumw2();
   TH1F* h_DY_ptZ_noaco=new TH1F("h_DY_ptZ_noaco","h_DY_ptZ_noaco",20,0,100); h_DY_ptZ_noaco->Sumw2();
   TH1F* h_DY_aco_noaco=new TH1F("h_DY_aco_noaco","h_DY_aco_noaco",20,0,1); h_DY_aco_noaco->Sumw2();

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
	b6_3->GetEntry(i);
	
	int ele_index=-1;
	for (int j=0; j<nLepCand; ++j){
	   if (ele_index<0 and LepCand_id[j]==11) ele_index=j;
	}
        int tau_index=-1; float dz_tmp=10000;
        for (int j=0; j<nLepCand; ++j){
           if (LepCand_id[j]==15 and fabs(LepCand_dz[j]-LepCand_dz[ele_index])<dz_tmp){
	      tau_index=j; 
	      dz_tmp=fabs(LepCand_dz[j]-LepCand_dz[ele_index]);
	   }
        }
        TLorentzVector my_tau; my_tau.SetPtEtaPhiM(LepCand_pt[tau_index],LepCand_eta[tau_index],LepCand_phi[tau_index],0);
        TLorentzVector my_ele; my_ele.SetPtEtaPhiM(LepCand_pt[ele_index],LepCand_eta[ele_index],LepCand_phi[ele_index],0);

	if (name!="data_obs" and LepCand_gen[tau_index]==5) my_tau=my_tau*LepCand_taues[tau_index];
        if (name!="data_obs" and LepCand_gen[tau_index]>=1 and LepCand_gen[tau_index]<=4) my_tau=my_tau*LepCand_fes[tau_index];

	if (name=="ZTT" and LepCand_gen[tau_index]!=5) continue;
        if (name=="ZLL" and LepCand_gen[tau_index]==5) continue;


	if (fabs(my_tau.Eta())>2.3) continue;
        if (fabs(my_ele.Eta())>2.1) continue;
	if (my_tau.DeltaR(my_ele)<0.5) continue;

	// Trigger block
	b3_7->GetEntry(i);
	if (name=="data_obs") {b2_4->GetEntry(i);}
	if (year=="2018"){
           b2_1->GetEntry(i);
	   if (name=="data_obs" and run<317509) {b2_3->GetEntry(i); }
	   if (name!="data_obs" or run>=317509) {b2_2->GetEntry(i); }
	}
	else if (year=="2017"){
	   b2_2017_1->GetEntry(i); b2_2017_2->GetEntry(i);
        }
	else if (year=="2016" or year=="2016pre" or year=="2016post"){
           b2_2016_1->GetEntry(i); 
	   if (name=="data_obs" and run<276215) b2_2016_3->GetEntry(i);
           else if (name=="data_obs" and run>276214 and run<278270) b2_2016_2->GetEntry(i);
           else if (name=="data_obs" and run>278269) b2_2016_4->GetEntry(i);
        }

	bool is_eletrg=false;
	bool is_etautrg=false;
	bool is_etauHPStrg=false;
	if (year=="2018"){
	   is_eletrg=(HLT_Ele32_WPTight_Gsf and my_ele.Pt()>32 and LepCand_trgmatch[ele_index]);
	   if (name!="data_obs") is_etauHPStrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 and my_ele.Pt()>24 and my_tau.Pt()>34 and my_ele.Pt()<34 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1 and LepCand_trgmatch[ele_index]);
           if (name=="data_obs" and run>=317509) is_etauHPStrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 and my_ele.Pt()>24 and my_tau.Pt()>34 and my_ele.Pt()<34 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
           if (name=="data_obs" and run<317509) is_etautrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 and my_ele.Pt()>24 and my_tau.Pt()>34 and my_ele.Pt()<34 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
	
	   if (name!="data_obs" and !is_eletrg and !is_etauHPStrg) continue;
	   if (name=="data_obs" and run<317509 and !is_eletrg and !is_etautrg) continue;
           if (name=="data_obs" and run>=317509 and !is_eletrg and !is_etauHPStrg) continue;
	}
	else if (year=="2017"){
	   is_eletrg=(HLT_Ele32_WPTight_Gsf_L1DoubleEG and my_ele.Pt()>32 and LepCand_trgmatch[ele_index]);
	   if (name=="data_obs") is_etautrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 and my_ele.Pt()>24 and my_tau.Pt()>34 and my_ele.Pt()<34 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
           if (name!="data_obs") is_etautrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 and my_ele.Pt()>24 and my_tau.Pt()>34 and my_ele.Pt()<34 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1 and LepCand_trgmatch[ele_index] and LepCand_trgmatch[tau_index]);
	   if (!is_eletrg and !is_etautrg) continue;
	}
        else if (year=="2016" or year=="2016pre" or year=="2016post"){
           is_eletrg=(HLT_Ele25_eta2p1_WPTight_Gsf and my_ele.Pt()>25 and LepCand_trgmatch[ele_index]);
	   if (!is_eletrg) continue;
        }

	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_5->GetEntry(i); b3_6->GetEntry(i); //b3_7->GetEntry(i);
	if (LepCand_vse[tau_index]<63 or LepCand_vsmu[tau_index]<1 or LepCand_vsjet[tau_index]<1) continue; //was 127
	if (!LepCand_eleMVAiso80[ele_index]) continue;
	//if (is_eletrg and !LepCand_trgmatch[ele_index]) continue; 
//if (is_etautrg or is_etauHPStrg) cout<<LepCand_trgmatch[ele_index]<<" "<<LepCand_trgmatch[tau_index]<<endl;
	//if (!is_eletrg and !LepCand_trgmatch[tau_index]) continue; //FIXME

	bool is_OS = (LepCand_charge[tau_index]*LepCand_charge[ele_index]<0);
	bool is_isolated = (LepCand_vsjet[tau_index]>=16); 

	// Block weights
	if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_3->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_24->GetEntry(i); }
        if (name!="data_obs" and nbhist>1){ b4_8->GetEntry(i); b4_9->GetEntry(i); b4_10->GetEntry(i); b4_11->GetEntry(i); b4_12->GetEntry(i); b4_13->GetEntry(i); b4_14->GetEntry(i); b4_15->GetEntry(i); b4_16->GetEntry(i); b4_17->GetEntry(i); b4_18->GetEntry(i); b4_19->GetEntry(i); b4_20->GetEntry(i);b4_21->GetEntry(i); b4_22->GetEntry(i); b4_23->GetEntry(i); b4_25->GetEntry(i); b4_26->GetEntry(i);}
        if (name!="data_obs"){ b4_27->GetEntry(i); b4_28->GetEntry(i); b4_29->GetEntry(i); b4_30->GetEntry(i); b4_31->GetEntry(i);}
        if (name!="data_obs"){ b4_32->GetEntry(i); b4_33->GetEntry(i); b4_34->GetEntry(i);}
        if (sample=="DY" or sample=="DYemu"){ b4_35->GetEntry(i); b4_36->GetEntry(i); b4_37->GetEntry(i);}

	b4_7->GetEntry(i);
        float acoplanarity = (1.0 -fabs(my_ele.DeltaPhi(my_tau))/3.14159);

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
//cout<<my_gen1.Pt()<<" "<<my_gen2.Pt()<<" "<<(my_gen1+my_gen2).M()<<endl;
        }
        if (name!="data_obs" and nGenCand<2){
	   gen_aco=acoplanarity; //use reco acoplanarity when the two gen taus are not well saved
           if (my_ele.Pt()>my_tau.Pt()){
              my_gen1=my_ele;
              my_gen2=my_tau;
           }
           else{
              my_gen1=my_tau;
              my_gen2=my_ele;
           }
	}
        if (gen_aco>0.35) gen_aco=0.35;
	float gen_mtt=200.0;
	//if (nGenCand>1 and (sample=="GGTT" or sample=="GGWW" or sample=="GGTT_Ctb20")) gen_mtt=(my_gen1+my_gen2).M();
	gen_mtt=(my_gen1+my_gen2).M();

	float aweight=1.0;
	float tauidSF=1.0;
        float elidsf_nom=1.0;
        float elidsf_up=1.0;
        float elidsf_down=1.0;
	float weight_aco=1.0;

	if (name!="data_obs"){
	   aweight=aweight*puWeight;
	   aweight=aweight*L1PreFiringWeight_Nom;
	   if (name!="W") aweight*=genWeight;
	   if (LepCand_gen[tau_index]==5) tauidSF=LepCand_tauidMsf[tau_index];
           if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*LepCand_antielesf[tau_index];
           if (LepCand_gen[tau_index]==2 or LepCand_gen[tau_index]==4) aweight=aweight*LepCand_antimusf[tau_index];

	   // low ntracks custom SF
	   if (year=="2016pre"){
              if (LepCand_gen[tau_index]==5) aweight=aweight*1.036;
              if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*1.42;
	   }
           else if (year=="2016post"){
              if (LepCand_gen[tau_index]==5) aweight=aweight*1.063;
              if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*1.10;
           }
           else if (year=="2017"){
              if (LepCand_gen[tau_index]==5) aweight=aweight*1.055;
              if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*1.49;
           }
           else if (year=="2018"){
              if (LepCand_gen[tau_index]==5) aweight=aweight*1.043;
              if (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3) aweight=aweight*0.74;
           }

	   /*if (is_etautrg or is_etauHPStrg){ 
	      aweight=aweight*LepCand_tautriggersf[tau_index];
	      float effMC=h_etautrgMC->GetBinContent(h_etautrgMC->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_etautrgMC->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	      float effData=h_etautrgData->GetBinContent(h_etautrgData->GetXaxis()->FindBin(TMath::Min(199.,my_ele.Pt())),h_etautrgData->GetYaxis()->FindBin(fabs(my_ele.Eta())));
	      if (effMC>0) aweight*=effData/effMC;
	   }
	   else{
              float effMC=h_e32trgMC->GetBinContent(h_e32trgMC->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_e32trgMC->GetYaxis()->FindBin(fabs(my_ele.Eta())));
              float effData=h_e32trgData->GetBinContent(h_e32trgData->GetXaxis()->FindBin(TMath::Min(199.,my_ele.Pt())),h_e32trgData->GetYaxis()->FindBin(fabs(my_ele.Eta())));
              if (effMC>0) aweight*=effData/effMC;
	   }*/

	   if (is_etautrg or is_etauHPStrg){
	      aweight=aweight*h_etautrgSF->GetBinContent(h_etautrgSF->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_etautrgSF->GetYaxis()->FindBin(my_ele.Eta()));
              aweight=aweight*LepCand_tautriggersf[tau_index];
	   }
	   else{
              aweight=aweight*TMath::Min(1.1,h_etrgSF->GetBinContent(h_etrgSF->GetXaxis()->FindBin(TMath::Min(my_ele.Pt(),199.)),h_etrgSF->GetYaxis()->FindBin(my_ele.Eta())));
	   }

           float ept=my_ele.Pt();
           if (ept>500) ept=499;
           elidsf_nom = h_eleIDSF->GetBinContent(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
           elidsf_up = elidsf_nom + h_eleIDSF->GetBinError(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
           elidsf_down = elidsf_nom - h_eleIDSF->GetBinError(h_eleIDSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleIDSF->GetYaxis()->FindBin(ept));
	   aweight=aweight*elidsf_nom;
           // low ntracks e ID (custom SF)
           if (fabs(my_ele.Eta())<1.5) aweight*=0.98;
           else aweight*=0.95;

           float elRecoSF = h_eleRecoSF->GetBinContent(h_eleRecoSF->GetXaxis()->FindBin(my_ele.Eta()),h_eleRecoSF->GetYaxis()->FindBin(ept));
           aweight=aweight*elRecoSF;
	   weight_aco=1.0;

           if (sample=="DY" or name=="ZTT" or name=="ZLL"){ 
	      weight_aco=GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 0, year);
	   }
           aweight=aweight*weight_aco; //FIXME Ben
	}

	// Block MET
	b5_1->GetEntry(i); b5_2->GetEntry(i);
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(MET_pt,0,MET_phi,0);
	float mt = TMass_F(my_ele.Pt(), my_ele.Px(), my_ele.Py(), my_met.Pt(), my_met.Phi());


	bool is_QCDregion = (!is_OS and mt<75); 
	bool is_Wregion = (is_OS and mt>75 and mt<150);

	bool is_real=(name=="W" or name=="GGTT" or sample=="GGTT" or sample=="GGTT_Ctb20" or name=="data_obs" or (LepCand_gen[tau_index]>=1 and LepCand_gen[tau_index]<=5));

	// Block vertex
        b6_1->GetEntry(i); 
        if (name!="data_obs") b6_2->GetEntry(i);
	float mydz=fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index]);
	if (mydz>0.4) mydz=0.399;
	if (is_isolated and is_OS) h_dz->Fill(mydz,weight*aweight);

	if (fabs(LepCand_dz[tau_index]-LepCand_dz[ele_index])>0.1) continue;
        float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[tau_index]+LepCand_dz[ele_index]);

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
	b8_1->GetEntry(i); b8_2->GetEntry(i); b8_3->GetEntry(i); b8_4->GetEntry(i);
	int ntracks=ntracks_friend;
	h_ntracks->Fill(TMath::Min(29,ntracks));
	if (acoplanarity>0.3) h_aco->Fill(0.299);
	else h_aco->Fill(acoplanarity);

        float zpos=simple_ditau_z; 
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntracksPU_friend;
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));} //FIXME Ben

        if (sample=="DY" or sample=="VV2L2Nu"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); } //FIXME Ben

	TLorentzVector save_tau=my_tau;
        TLorentzVector save_ele=my_ele;
        TLorentzVector save_met=my_met;

	bool is_lowNT=(ntracks<20000);
	bool is_lowA=(acoplanarity<0.015); 
	if (is_control>0) is_lowA=true;
	//if (mt>50 or (my_ele+my_tau).M()>90) continue;

	//if (!is_lowA or ntracks>10) continue;

        if (sample=="GGWW"){ // rescaling from mumu region
           if (ntracks==0) aweight*=(2.433+0.00152*gen_mtt);
           else if (ntracks==1) aweight*=(2.52+0.0011*gen_mtt);
	}

	/*if (sample=="DYemu" or sample=="DY"){//EFT reweighting //FIXME
	   float my_genmtt=gen_mtt;
	   if (gen_mtt>500) my_genmtt=499;
	   aweight*=h_DYEFT6p7->GetBinContent(h_DYEFT6p7->GetXaxis()->FindBin(my_genmtt));
//cout<<my_genmtt<<" "<<gen_mtt<<" "<<h_DYEFT6p7->GetBinContent(h_DYEFT6p7->GetXaxis()->FindBin(my_genmtt))<<endl;
        }*/

	if (sample=="GGTT" or sample=="GGTT_Ctb20"){ // rescaling from mumu region
           ////if (ntracks==0) cout<<gen_mtt<<endl;
	   if (ntracks==0) aweight*=(2.433+0.00152*gen_mtt); //FIXME Ben
           else if (ntracks==1) aweight*=(2.52+0.0011*gen_mtt); //FIXME Ben
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
	   if (name=="GGTT_0p0") aweight*=TauG2Weights_ceBRe33_0p0;
           else if (name=="GGTT") aweight*=TauG2Weights_ceBRe33_0p0;
           else if (name=="GGTT_0p8") aweight*=TauG2Weights_ceBRe33_0p8;
           else if (name=="GGTT_1p6") aweight*=TauG2Weights_ceBRe33_1p6;
           else if (name=="GGTT_2p4") aweight*=TauG2Weights_ceBRe33_2p4;
           else if (name=="GGTT_3p2") aweight*=TauG2Weights_ceBRe33_3p2;
           else if (name=="GGTT_4p0") aweight*=TauG2Weights_ceBRe33_4p0;
           else if (name=="GGTT_4p8") aweight*=TauG2Weights_ceBRe33_4p8;
           else if (name=="GGTT_5p6") aweight*=TauG2Weights_ceBRe33_5p6;
           else if (name=="GGTT_6p4") aweight*=TauG2Weights_ceBRe33_6p4;
           else if (name=="GGTT_7p2") aweight*=TauG2Weights_ceBRe33_7p2;
           else if (name=="GGTT_8p0") aweight*=TauG2Weights_ceBRe33_8p0;
           else if (name=="GGTT_8p8") aweight*=TauG2Weights_ceBRe33_8p8;
           else if (name=="GGTT_9p6") aweight*=TauG2Weights_ceBRe33_9p6;
           else if (name=="GGTT_10p4") aweight*=TauG2Weights_ceBRe33_10p4;
           else if (name=="GGTT_11p2") aweight*=TauG2Weights_ceBRe33_11p2;
           else if (name=="GGTT_12p0") aweight*=TauG2Weights_ceBRe33_12p0;
           else if (name=="GGTT_12p8") aweight*=TauG2Weights_ceBRe33_12p8;
           else if (name=="GGTT_13p6") aweight*=TauG2Weights_ceBRe33_13p6;
           else if (name=="GGTT_14p4") aweight*=TauG2Weights_ceBRe33_14p4;
           else if (name=="GGTT_15p2") aweight*=TauG2Weights_ceBRe33_15p2;
           else if (name=="GGTT_16p0") aweight*=TauG2Weights_ceBRe33_16p0;
           else if (name=="GGTT_16p8") aweight*=TauG2Weights_ceBRe33_16p8;
           else if (name=="GGTT_17p6") aweight*=TauG2Weights_ceBRe33_17p6;
           else if (name=="GGTT_18p4") aweight*=TauG2Weights_ceBRe33_18p4;
           else if (name=="GGTT_19p2") aweight*=TauG2Weights_ceBRe33_19p2;
           else if (name=="GGTT_20p0") aweight*=TauG2Weights_ceBRe33_20p0;
           else if (name=="GGTT_20p8") aweight*=TauG2Weights_ceBRe33_20p8;
           else if (name=="GGTT_21p6") aweight*=TauG2Weights_ceBRe33_21p6;
           else if (name=="GGTT_22p4") aweight*=TauG2Weights_ceBRe33_22p4;
           else if (name=="GGTT_23p2") aweight*=TauG2Weights_ceBRe33_23p2;
           else if (name=="GGTT_24p0") aweight*=TauG2Weights_ceBRe33_24p0;
           else if (name=="GGTT_24p8") aweight*=TauG2Weights_ceBRe33_24p8;
           else if (name=="GGTT_25p6") aweight*=TauG2Weights_ceBRe33_25p6;
           else if (name=="GGTT_26p4") aweight*=TauG2Weights_ceBRe33_26p4;
           else if (name=="GGTT_27p2") aweight*=TauG2Weights_ceBRe33_27p2;
           else if (name=="GGTT_28p0") aweight*=TauG2Weights_ceBRe33_28p0;
           else if (name=="GGTT_28p8") aweight*=TauG2Weights_ceBRe33_28p8;
           else if (name=="GGTT_29p6") aweight*=TauG2Weights_ceBRe33_29p6;
           else if (name=="GGTT_30p4") aweight*=TauG2Weights_ceBRe33_30p4;
           else if (name=="GGTT_31p2") aweight*=TauG2Weights_ceBRe33_31p2;
           else if (name=="GGTT_32p0") aweight*=TauG2Weights_ceBRe33_32p0;
           else if (name=="GGTT_32p8") aweight*=TauG2Weights_ceBRe33_32p8;
           else if (name=="GGTT_33p6") aweight*=TauG2Weights_ceBRe33_33p6;
           else if (name=="GGTT_34p4") aweight*=TauG2Weights_ceBRe33_34p4;
           else if (name=="GGTT_35p2") aweight*=TauG2Weights_ceBRe33_35p2;
           else if (name=="GGTT_36p0") aweight*=TauG2Weights_ceBRe33_36p0;
           else if (name=="GGTT_36p8") aweight*=TauG2Weights_ceBRe33_36p8;
           else if (name=="GGTT_37p6") aweight*=TauG2Weights_ceBRe33_37p6;
           else if (name=="GGTT_38p4") aweight*=TauG2Weights_ceBRe33_38p4;
           else if (name=="GGTT_39p2") aweight*=TauG2Weights_ceBRe33_39p2;
           else if (name=="GGTT_40p0") aweight*=TauG2Weights_ceBRe33_40p0;
           else if (name=="GGTT_m0p8") aweight*=TauG2Weights_ceBRe33_m0p8;
           else if (name=="GGTT_m1p6") aweight*=TauG2Weights_ceBRe33_m1p6;
           else if (name=="GGTT_m2p4") aweight*=TauG2Weights_ceBRe33_m2p4;
           else if (name=="GGTT_m3p2") aweight*=TauG2Weights_ceBRe33_m3p2;
           else if (name=="GGTT_m4p0") aweight*=TauG2Weights_ceBRe33_m4p0;
           else if (name=="GGTT_m4p8") aweight*=TauG2Weights_ceBRe33_m4p8;
           else if (name=="GGTT_m5p6") aweight*=TauG2Weights_ceBRe33_m5p6;
           else if (name=="GGTT_m6p4") aweight*=TauG2Weights_ceBRe33_m6p4;
           else if (name=="GGTT_m7p2") aweight*=TauG2Weights_ceBRe33_m7p2;
           else if (name=="GGTT_m8p0") aweight*=TauG2Weights_ceBRe33_m8p0;
           else if (name=="GGTT_m8p8") aweight*=TauG2Weights_ceBRe33_m8p8;
           else if (name=="GGTT_m9p6") aweight*=TauG2Weights_ceBRe33_m9p6;
           else if (name=="GGTT_m10p4") aweight*=TauG2Weights_ceBRe33_m10p4;
           else if (name=="GGTT_m11p2") aweight*=TauG2Weights_ceBRe33_m11p2;
           else if (name=="GGTT_m12p0") aweight*=TauG2Weights_ceBRe33_m12p0;
           else if (name=="GGTT_m12p8") aweight*=TauG2Weights_ceBRe33_m12p8;
           else if (name=="GGTT_m13p6") aweight*=TauG2Weights_ceBRe33_m13p6;
           else if (name=="GGTT_m14p4") aweight*=TauG2Weights_ceBRe33_m14p4;
           else if (name=="GGTT_m15p2") aweight*=TauG2Weights_ceBRe33_m15p2;
           else if (name=="GGTT_m16p0") aweight*=TauG2Weights_ceBRe33_m16p0;
           else if (name=="GGTT_m16p8") aweight*=TauG2Weights_ceBRe33_m16p8;
           else if (name=="GGTT_m17p6") aweight*=TauG2Weights_ceBRe33_m17p6;
           else if (name=="GGTT_m18p4") aweight*=TauG2Weights_ceBRe33_m18p4;
           else if (name=="GGTT_m19p2") aweight*=TauG2Weights_ceBRe33_m19p2;
           else if (name=="GGTT_m20p0") aweight*=TauG2Weights_ceBRe33_m20p0;
           else if (name=="GGTT_m20p8") aweight*=TauG2Weights_ceBRe33_m20p8;
           else if (name=="GGTT_m21p6") aweight*=TauG2Weights_ceBRe33_m21p6;
           else if (name=="GGTT_m22p4") aweight*=TauG2Weights_ceBRe33_m22p4;
           else if (name=="GGTT_m23p2") aweight*=TauG2Weights_ceBRe33_m23p2;
           else if (name=="GGTT_m24p0") aweight*=TauG2Weights_ceBRe33_m24p0;
           else if (name=="GGTT_m24p8") aweight*=TauG2Weights_ceBRe33_m24p8;
           else if (name=="GGTT_m25p6") aweight*=TauG2Weights_ceBRe33_m25p6;
           else if (name=="GGTT_m26p4") aweight*=TauG2Weights_ceBRe33_m26p4;
           else if (name=="GGTT_m27p2") aweight*=TauG2Weights_ceBRe33_m27p2;
           else if (name=="GGTT_m28p0") aweight*=TauG2Weights_ceBRe33_m28p0;
           else if (name=="GGTT_m28p8") aweight*=TauG2Weights_ceBRe33_m28p8;
           else if (name=="GGTT_m29p6") aweight*=TauG2Weights_ceBRe33_m29p6;
           else if (name=="GGTT_m30p4") aweight*=TauG2Weights_ceBRe33_m30p4;
           else if (name=="GGTT_m31p2") aweight*=TauG2Weights_ceBRe33_m31p2;
           else if (name=="GGTT_m32p0") aweight*=TauG2Weights_ceBRe33_m32p0;
           else if (name=="GGTT_m32p8") aweight*=TauG2Weights_ceBRe33_m32p8;
           else if (name=="GGTT_m33p6") aweight*=TauG2Weights_ceBRe33_m33p6;
           else if (name=="GGTT_m34p4") aweight*=TauG2Weights_ceBRe33_m34p4;
           else if (name=="GGTT_m35p2") aweight*=TauG2Weights_ceBRe33_m35p2;
           else if (name=="GGTT_m36p0") aweight*=TauG2Weights_ceBRe33_m36p0;
           else if (name=="GGTT_m36p8") aweight*=TauG2Weights_ceBRe33_m36p8;
           else if (name=="GGTT_m37p6") aweight*=TauG2Weights_ceBRe33_m37p6;
           else if (name=="GGTT_m38p4") aweight*=TauG2Weights_ceBRe33_m38p4;
           else if (name=="GGTT_m39p2") aweight*=TauG2Weights_ceBRe33_m39p2;
           else if (name=="GGTT_m40p0") aweight*=TauG2Weights_ceBRe33_m40p0;
	}

        for (int k=0; k<nbhist; ++k){
           my_tau=save_tau;
	   my_ele=save_ele;
	   my_met=save_met;
	   float weight2=1.0;

	   if (name!="data_obs"){
	      if (k==1 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==2 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==3 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==4 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==5 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==6 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==7 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==8 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert0_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==9 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==10 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==11 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==12 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==13 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==14 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==15 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==16 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_uncert1_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==17 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_alleras_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==18 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_alleras_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==19 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_era_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==20 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_era_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==21 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==22 and LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==23 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==24 and LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==25 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==26 and LepCand_DecayMode[tau_index]==10 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_up[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==27 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_down[tau_index] / LepCand_tauidMsf[tau_index];}
              else if (k==28 and LepCand_DecayMode[tau_index]==11 and LepCand_gen[tau_index]==5){ weight2 = LepCand_tauidMsf_syst_dm_era_up[tau_index] / LepCand_tauidMsf[tau_index];}


              else if (k==29 && LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_down[tau_index]/LepCand_taues[tau_index];}
              else if (k==30 && LepCand_DecayMode[tau_index]==0 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_up[tau_index]/LepCand_taues[tau_index]; }
              else if (k==31 && LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_down[tau_index]/LepCand_taues[tau_index];}
              else if (k==32 && LepCand_DecayMode[tau_index]==1 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_up[tau_index]/LepCand_taues[tau_index];}
              else if (k==33 && LepCand_DecayMode[tau_index]>=10 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_down[tau_index]/LepCand_taues[tau_index];}
              else if (k==34 && LepCand_DecayMode[tau_index]>=10 and LepCand_gen[tau_index]==5){my_tau*=LepCand_taues_up[tau_index]/LepCand_taues[tau_index]; }
              else if (k==35 and fabs(my_tau.Eta())<1.5 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){ weight2 = LepCand_antielesf_down[tau_index]/LepCand_antielesf[tau_index];}
              else if (k==36 and fabs(my_tau.Eta())<1.5 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){ weight2 = LepCand_antielesf_up[tau_index]/LepCand_antielesf[tau_index];}
              else if (k==37 and fabs(my_tau.Eta())>=1.5 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){ weight2 = LepCand_antielesf_down[tau_index]/LepCand_antielesf[tau_index];}
              else if (k==38 and fabs(my_tau.Eta())>=1.5 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){ weight2 = LepCand_antielesf_up[tau_index]/LepCand_antielesf[tau_index];}
              else if (k==39 && LepCand_DecayMode[tau_index]==0 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){my_tau*=LepCand_fes_down[tau_index]/LepCand_fes[tau_index];}
              else if (k==40 && LepCand_DecayMode[tau_index]==0 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){my_tau*=LepCand_fes_up[tau_index]/LepCand_fes[tau_index];}
              else if (k==41 && LepCand_DecayMode[tau_index]==1 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){my_tau*=LepCand_fes_down[tau_index]/LepCand_fes[tau_index];}
              else if (k==42 && LepCand_DecayMode[tau_index]==1 and (LepCand_gen[tau_index]==1 or LepCand_gen[tau_index]==3)){my_tau*=LepCand_fes_up[tau_index]/LepCand_fes[tau_index];}
              else if (k==43){ weight2=puWeightDown/puWeight;}
              else if (k==44){ weight2=puWeightUp/puWeight;}
              else if (k==45 and (is_etautrg or is_etauHPStrg)){ weight2=0.99*LepCand_tautriggersf_down[tau_index]/LepCand_tautriggersf[tau_index];}
              else if (k==46 and (is_etautrg or is_etauHPStrg)){ weight2=0.99*LepCand_tautriggersf_up[tau_index]/LepCand_tautriggersf[tau_index];}
              else if (k==47 and is_eletrg){ weight2=0.98;}
              else if (k==48 and is_eletrg){ weight2=1.02;}
	      else if (k==49){ 
		if (ntracks==0) weight2=2.59/(2.433+0.00152*gen_mtt);
                if (ntracks==1) weight2=2.63/(2.52+0.0011*gen_mtt);
	      }
              else if (k==50){ 
                if (ntracks==0) weight2=1.0+(1.0-2.59/(2.433+0.00152*gen_mtt));
                if (ntracks==1) weight2=1.0+(1.0-2.63/(2.52+0.0011*gen_mtt));
              }
              else if (k==51) weight2=L1PreFiringWeight_Dn/L1PreFiringWeight_Nom;
              else if (k==52) weight2=L1PreFiringWeight_Up/L1PreFiringWeight_Nom;
              else if (k==53) weight2=elidsf_down/elidsf_nom;
              else if (k==54) weight2=elidsf_up/elidsf_nom;
	      else if (k==55) weight2=PSWeight[2] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 9, year)/weight_aco;
              else if (k==56) weight2=PSWeight[0] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 7, year)/weight_aco;
              else if (k==57) weight2=PSWeight[3] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 10, year)/weight_aco;
              else if (k==58) weight2=PSWeight[1] * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 8, year)/weight_aco;
	      else if (k==59 or k==60){
                float average_sigma=0.0;
                for (int jj=1; jj<101; ++jj) average_sigma+=0.01*LHEPdfWeight[jj];
                float deltasigma=0.0;
                for (int jj=1; jj<101; ++jj) deltasigma+=(1.0/(100-1))*pow((LHEPdfWeight[jj]-average_sigma),2);
                deltasigma=pow(deltasigma,0.5);
		if (k==59) weight2 = (1.0-deltasigma);
		else if (k==60) weight2 = (1.0+deltasigma);
	      }
	      else if (k==61) weight2=LHEScaleWeight[0]/0.983 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 1, year)/weight_aco;
              else if (k==62) weight2=LHEScaleWeight[1]/1.015 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 2, year)/weight_aco;
              else if (k==63) weight2=LHEScaleWeight[3]/0.960 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 3, year)/weight_aco;
              else if (k==64) weight2=LHEScaleWeight[5]/1.025 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 4, year)/weight_aco;
              else if (k==65) weight2=LHEScaleWeight[7]/0.986 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 5, year)/weight_aco;
              else if (k==66) weight2=LHEScaleWeight[8]/1.018 * GetAcoWeight(my_gen1.Pt(), my_gen2.Pt(), gen_aco, 6, year)/weight_aco;
	   }

	   //Reapply trigger thresholds after shifts
           if (year=="2018"){
              is_eletrg=(HLT_Ele32_WPTight_Gsf and my_ele.Pt()>33);
              if (name!="data_obs" or run>=317509) is_etauHPStrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTauHPS30_eta2p1_CrossL1 and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
              if (name=="data_obs" and run<317509) is_etautrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);

              if (name!="data_obs" and !is_eletrg and !is_etauHPStrg) continue;
              if (name=="data_obs" and run<317509 and !is_eletrg and !is_etautrg) continue;
              if (name=="data_obs" and run>=317509 and !is_eletrg and !is_etauHPStrg) continue;
           }
           else if (year=="2017"){
              is_eletrg=(HLT_Ele32_WPTight_Gsf_L1DoubleEG and my_ele.Pt()>33);
              is_etautrg=(HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1 and my_ele.Pt()>25 and my_tau.Pt()>35 and my_ele.Pt()<33 and fabs(my_tau.Eta())<2.1 and fabs(my_ele.Eta())<2.1);
              if (!is_eletrg and !is_etautrg) continue;
           }
           else if (year=="2016" or year=="2016pre" or year=="2016post"){
              is_eletrg=(HLT_Ele25_eta2p1_WPTight_Gsf and my_ele.Pt()>26);
              if (!is_eletrg) continue;
           }


	   float mvis=(my_ele+my_tau).M();
	   if (mvis<40) continue;
	   if (my_tau.Pt()<30) continue;
	   if (mvis>500) continue; //FIXME

           bool is_cat0=(mt<75);
           bool is_cat1=(mt<75);
           bool is_cat2=(mt<75);
           bool is_cat3=(mt<75);
           bool is_cat4=(mt<75);
           bool is_cat5=(mt<75);
           bool is_cat6=(mt<12000);
           bool is_cat7=(mt<75);
           bool is_cat8=(mt<75);

           bool is_cat0R=(mt<75);
           bool is_cat1R=(mt<75);
           bool is_cat2R=(mt<75);
           bool is_cat3R=(mt<75);
           bool is_cat4R=(mt<75);
           bool is_cat5R=(mt<75);
           bool is_cat6R=(mt<12000);
           bool is_cat7R=(mt<75);
           bool is_cat8R=(mt<75);

	   float var0 = mvis;
           float var1 = my_ele.Pt();
           float var2 = my_tau.Pt();
           float var3 = my_ele.Eta();
           float var4 = my_tau.Eta();//LepCand_DecayMode[tau_index];
           float var5 = my_met.Pt();
           float var6 = mt;
           int var7 = ntracks;
           float var8 = acoplanarity;

	   if (is_control==0){
              /*is_cat0=(mt<75 and LepCand_DecayMode[tau_index]==0 and ntracks==0);
              is_cat1=(mt<75 and LepCand_DecayMode[tau_index]==1 and ntracks==0);
              is_cat2=(mt<75 and LepCand_DecayMode[tau_index]==10 and ntracks==0);
              is_cat3=(mt<75 and LepCand_DecayMode[tau_index]==11 and ntracks==0);
              is_cat4=(mt<75 and LepCand_DecayMode[tau_index]==0 and ntracks==1);
              is_cat5=(mt<75 and LepCand_DecayMode[tau_index]==1 and ntracks==1);
              is_cat6=(mt<75 and LepCand_DecayMode[tau_index]==10 and ntracks==1);
              is_cat7=(mt<75 and LepCand_DecayMode[tau_index]==11 and ntracks==1);
              is_cat8=(mt<75);*/

	      is_cat0=(mt<75 and ntracks==0 and is_lowA);
              is_cat1=(mt<75 and ntracks==1 and is_lowA);
              is_cat2=(mt<75 and (ntracks==3 or ntracks==4) and is_lowA);
              is_cat3=(mt<75 and ntracks==0 and is_lowA and LepCand_DecayMode[tau_index]==1);
              is_cat4=(mt<75 and ntracks==0 and is_lowA and LepCand_DecayMode[tau_index]==10);
              is_cat5=(mt<75 and ntracks==0 and is_lowA and LepCand_DecayMode[tau_index]==11);
              is_cat6=(mt<75 and ntracks==0 and is_lowA);
              is_cat7=(mt<75 and ntracks==0 and is_lowA);
              is_cat8=(mt<75 and ntracks==0 and is_lowA);

              is_cat0R=(mt<75 and ntracks<10 and is_lowA);
              is_cat1R=(mt<75 and ntracks<10 and is_lowA);
              is_cat2R=(mt<75 and ntracks<10 and is_lowA);
              is_cat3R=(mt<75 and ntracks<10 and is_lowA and LepCand_DecayMode[tau_index]==1);
              is_cat4R=(mt<75 and ntracks<10 and is_lowA and LepCand_DecayMode[tau_index]==10);
              is_cat5R=(mt<75 and ntracks<10 and is_lowA and LepCand_DecayMode[tau_index]==11);
              is_cat6R=(mt<75 and ntracks<10 and is_lowA);
              is_cat7R=(mt<75 and ntracks<10 and is_lowA);
              is_cat8R=(mt<75 and ntracks<10 and is_lowA);

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

           if (k==0 and is_OS and is_isolated){
	      if (ntracks==0 and acoplanarity<0.02) h_DY_ABCD->Fill(0.5,weight*aweight*tauidSF);
              if (ntracks==0 and acoplanarity>=0.02) h_DY_ABCD->Fill(1.5,weight*aweight*tauidSF);
              if (ntracks==1 and acoplanarity<0.02) h_DY_ABCD->Fill(2.5,weight*aweight*tauidSF);
              if (ntracks==1 and acoplanarity>=0.02) h_DY_ABCD->Fill(3.5,weight*aweight*tauidSF);
              if (ntracks<10 and acoplanarity<0.02) h_DY_ABCD->Fill(4.5,weight*aweight*tauidSF);
              if (ntracks<10 and acoplanarity>=0.02) h_DY_ABCD->Fill(5.5,weight*aweight*tauidSF);
	   }

	   if (k==0 and is_OS and is_isolated){

              h_DY_mvis_waco->Fill(mvis,weight*aweight*tauidSF);
              h_DY_ptZ_waco->Fill((my_ele+my_tau+my_met).Pt(),weight*aweight*tauidSF);
              h_DY_aco_waco->Fill(acoplanarity,weight*aweight*tauidSF);
              h_DY_mvis_noaco->Fill(mvis,weight*aweight*tauidSF/weight_aco);
              h_DY_ptZ_noaco->Fill((my_ele+my_tau+my_met).Pt(),weight*aweight*tauidSF/weight_aco);
              h_DY_aco_noaco->Fill(acoplanarity,weight*aweight*tauidSF/weight_aco);

	      if (ntracks==0) h_mvis_nt0->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==1) h_mvis_nt1->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==2) h_mvis_nt2->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==3) h_mvis_nt3->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==4) h_mvis_nt4->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==5) h_mvis_nt5->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==6) h_mvis_nt6->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==7) h_mvis_nt7->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==8) h_mvis_nt8->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks==9) h_mvis_nt9->Fill(mvis,weight*aweight*tauidSF);

              if (ntracks>=0 and ntracks<10) h_mvis_nt0to10->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=10 and ntracks<20) h_mvis_nt10to20->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=20 and ntracks<30) h_mvis_nt20to30->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=30 and ntracks<40) h_mvis_nt30to40->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=40 and ntracks<50) h_mvis_nt40to50->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=50 and ntracks<60) h_mvis_nt50to60->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=60 and ntracks<70) h_mvis_nt60to70->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=70 and ntracks<80) h_mvis_nt70to80->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=80 and ntracks<90) h_mvis_nt80to90->Fill(mvis,weight*aweight*tauidSF);
              else if (ntracks>=90 and ntracks<100) h_mvis_nt90to100->Fill(mvis,weight*aweight*tauidSF);
	   }
	   float maxmvis=mvis;
	   if (maxmvis>250) maxmvis=249;
           if (is_OS and is_isolated and mt<75) { 
	      fractionOS->Fill(mt,maxmvis,weight*aweight*weight2*tauidSF);
              fractionNtrackOS->Fill(ntracks,weight*aweight*weight2*tauidSF);
              fractionAcoplanarityOS->Fill(acoplanarity,weight*aweight*weight2*tauidSF);
              fractionAcoplanarityOS->Fill(-0.02,weight*aweight*weight2*tauidSF);
	   }
           if (!is_OS and is_isolated and mt<75){
              fractionSS->Fill(mt,maxmvis,weight*aweight*weight2*tauidSF);
              fractionNtrackSS->Fill(ntracks,weight*aweight*weight2*tauidSF);
              fractionAcoplanaritySS->Fill(acoplanarity,weight*aweight*weight2*tauidSF);
              fractionAcoplanaritySS->Fill(-0.02,weight*aweight*weight2*tauidSF);
           }
	
	   if (k==0 and is_OS and is_isolated and mt<75){
	      h_acoplanarity->Fill(acoplanarity);
              h_genacoplanarity->Fill(gen_aco);
              if (my_ele.Pt()+my_tau.Pt()<100) h_acoplanarity_sumptlt100->Fill(acoplanarity);
              else h_acoplanarity_sumptgt100->Fill(acoplanarity);

	      h_resolution_acoplanarity->Fill(acoplanarity-gen_aco);
              if (my_ele.Pt()+my_tau.Pt()<100) h_resolution_acoplanarity_sumptlt100->Fill(acoplanarity-gen_aco);
              else h_resolution_acoplanarity_sumptgt100->Fill(acoplanarity-gen_aco);

	   }
	   if (is_OS and is_isolated and is_real){
	     float w_iso=weight*aweight*weight2*tauidSF;
	     if (is_cat0) h0[k]->Fill(var0,w_iso);
             if (is_cat1) h1[k]->Fill(var1,w_iso);
             if (is_cat2) h2[k]->Fill(var2,w_iso);
             if (is_cat3) h3[k]->Fill(var3,w_iso);
             if (is_cat4) h4[k]->Fill(var4,w_iso);
             if (is_cat5) h5[k]->Fill(var5,w_iso);
             if (is_cat6) h6[k]->Fill(var6,w_iso);
             if (is_cat7) h7[k]->Fill(var7,w_iso);
             if (is_cat8) h8[k]->Fill(var8,w_iso);

             if (is_cat0R) h0R[k]->Fill(var0,w_iso);
             if (is_cat1R) h1R[k]->Fill(var1,w_iso);
             if (is_cat2R) h2R[k]->Fill(var2,w_iso);
             if (is_cat3R) h3R[k]->Fill(var3,w_iso);
             if (is_cat4R) h4R[k]->Fill(var4,w_iso);
             if (is_cat5R) h5R[k]->Fill(var5,w_iso);
             if (is_cat6R) h6R[k]->Fill(var6,w_iso);
             if (is_cat7R) h7R[k]->Fill(var7,w_iso);
             if (is_cat8R) h8R[k]->Fill(var8,w_iso);

	     if (is_cat0 and k==0) h_ptll->Fill((my_gen1+my_gen2).Pt(),w_iso);
	   }

	   float tpt=my_tau.Pt();
	   if (tpt>200) tpt=199;
	   float tfr_W=0.1;

	   if (LepCand_DecayMode[tau_index]==0){ 
	      tfr_W=TMath::Min(1.0,fit_taufr_W_dm0->Eval(tpt));
	      if (ntracks<25) tfr_W*=fitlow_taufrnt_W_dm0->Eval(TMath::Max(0,ntracks));
	      else tfr_W*=fit_taufrnt_W_dm0->Eval(TMath::Max(0,ntracks)); 
	   }
           else if (LepCand_DecayMode[tau_index]==1){ 
	      tfr_W=TMath::Min(1.0,fit_taufr_W_dm1->Eval(tpt));
              if (ntracks<25) tfr_W*=fitlow_taufrnt_W_dm1->Eval(TMath::Max(0,ntracks));
	      else tfr_W*=fit_taufrnt_W_dm1->Eval(TMath::Max(0,ntracks));
	   }
           else if (LepCand_DecayMode[tau_index]==10){ 
	      tfr_W=TMath::Min(1.0,fit_taufr_W_dm10->Eval(tpt));
              if (ntracks<25) tfr_W*=fitlow_taufrnt_W_dm10->Eval(TMath::Max(0,ntracks));
	      else tfr_W*=fit_taufrnt_W_dm10->Eval(TMath::Max(0,ntracks));
	   }
           else if (LepCand_DecayMode[tau_index]==11){ 
	      tfr_W=TMath::Min(1.0,fit_taufr_W_dm11->Eval(tpt));
              if (ntracks<25) tfr_W*=fitlow_taufrnt_W_dm11->Eval(TMath::Max(0,ntracks));
              else tfr_W*=fit_taufrnt_W_dm11->Eval(TMath::Max(0,ntracks));
	   }
           if (is_etautrg or is_etauHPStrg) tfr_W*=corr_taufr_W_xtrg->GetBinContent(2)/corr_taufr_W_xtrg->GetBinContent(3); 
           //if (is_etautrg or is_etauHPStrg) tfr_W*=1.7;

           float tfr_QCD=0.1;
           if (LepCand_DecayMode[tau_index]==0){
	      tfr_QCD=TMath::Min(1.0,fit_taufr_QCD_dm0->Eval(tpt));
              if (ntracks<25) tfr_QCD*=fitlow_taufrnt_QCD_dm0->Eval(TMath::Max(0,ntracks));
	      else tfr_QCD*=fit_taufrnt_QCD_dm0->Eval(TMath::Max(0,ntracks));
	   }
           else if (LepCand_DecayMode[tau_index]==1){
	      tfr_QCD=TMath::Min(1.0,fit_taufr_QCD_dm1->Eval(tpt));
              if (ntracks<25) tfr_QCD*=fitlow_taufrnt_QCD_dm1->Eval(TMath::Max(0,ntracks));
	      else tfr_QCD*=fit_taufrnt_QCD_dm1->Eval(TMath::Max(0,ntracks));
	   }
           else if (LepCand_DecayMode[tau_index]==10){ 
	      tfr_QCD=TMath::Min(1.0,fit_taufr_QCD_dm10->Eval(tpt));
              if (ntracks<25) tfr_QCD*=fitlow_taufrnt_QCD_dm10->Eval(TMath::Max(0,ntracks));
	      else tfr_QCD*=fit_taufrnt_QCD_dm10->Eval(TMath::Max(0,ntracks));
	   }
           else if (LepCand_DecayMode[tau_index]==11){ 
	      tfr_QCD=TMath::Min(1.0,fit_taufr_QCD_dm11->Eval(tpt));
              if (ntracks<25) tfr_QCD*=fitlow_taufrnt_QCD_dm11->Eval(TMath::Max(0,ntracks));
	      else tfr_QCD*=fit_taufrnt_QCD_dm11->Eval(TMath::Max(0,ntracks));
	   }
           if (is_etautrg or is_etauHPStrg) tfr_QCD*=corr_taufr_QCD_xtrg->GetBinContent(2)/corr_taufr_QCD_xtrg->GetBinContent(3); 
           //if (is_etautrg or is_etauHPStrg) tfr_QCD*=1.7;

	   float mymt=mt;
	   float mymvis=mvis;
	   if (mymvis>250) mymvis=249;
           if (mymvis<50) mymvis=51;
           //if (mymt>75) mymt=74;
	   float fracW=h_fracW->GetBinContent(h_fracW->GetXaxis()->FindBin(mymt),h_fracW->GetYaxis()->FindBin(mymvis));
	   float fracWdown=fracW*0.8;//fracW/2.0;
           float fracWup=fracW*1.2;//2.0;
	   if (fracWup>1) fracWup=1;
	   if (mymt>75) fracW=1.0;
	   float tfr=fracW*tfr_W + (1-fracW)*tfr_QCD;
	   float wfr=tfr;


           if (k==(nbhistMC+1-nbhist_offset)){wfr=fracW*tfr_W*0.95 + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+2-nbhist_offset)){wfr=fracW*tfr_W*1.05 + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+3-nbhist_offset)){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*0.90;}
           else if (k==(nbhistMC+4-nbhist_offset)){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*1.10;}
           else if (k==(nbhistMC+5-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W*(1.0-(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+6-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W*(1.0+(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+7-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W*(1.0-(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+8-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W*(1.0+(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+9-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W*(1.0-(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+10-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W*(1.0+(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+11-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W*(1.0-(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+12-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W*(1.0+(my_tau.Pt()-30)*0.5/470) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+13-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+14-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+15-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+16-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+17-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+18-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+19-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+20-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+(my_tau.Pt()-30)*0.5/470);}
           else if (k==(nbhistMC+21-nbhist_offset)){wfr=fracWdown*tfr_W + (1-fracWdown)*tfr_QCD;}
           else if (k==(nbhistMC+22-nbhist_offset)){wfr=fracWup*tfr_W + (1-fracWup)*tfr_QCD;}
           else if (k==(nbhistMC+23-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W*(1.0-err_nt0_ffW->GetBinContent(1)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+24-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W*(1.0+err_nt0_ffW->GetBinContent(1)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+25-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W*(1.0-err_nt0_ffW->GetBinContent(2)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+26-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W*(1.0+err_nt0_ffW->GetBinContent(2)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+27-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W*(1.0-err_nt0_ffW->GetBinContent(11)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+28-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W*(1.0+err_nt0_ffW->GetBinContent(11)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+29-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W*(1.0-err_nt0_ffW->GetBinContent(12)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+30-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W*(1.0+err_nt0_ffW->GetBinContent(12)) + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+31-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-err_nt0_ffQCD->GetBinContent(1));}
           else if (k==(nbhistMC+32-nbhist_offset) and LepCand_DecayMode[tau_index]==0){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+err_nt0_ffQCD->GetBinContent(1));}
           else if (k==(nbhistMC+33-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-err_nt0_ffQCD->GetBinContent(2));}
           else if (k==(nbhistMC+34-nbhist_offset) and LepCand_DecayMode[tau_index]==1){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+err_nt0_ffQCD->GetBinContent(2));}
           else if (k==(nbhistMC+35-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-err_nt0_ffQCD->GetBinContent(11));}
           else if (k==(nbhistMC+36-nbhist_offset) and LepCand_DecayMode[tau_index]==10){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+err_nt0_ffQCD->GetBinContent(11));}
           else if (k==(nbhistMC+37-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0-err_nt0_ffQCD->GetBinContent(12));}
           else if (k==(nbhistMC+38-nbhist_offset) and LepCand_DecayMode[tau_index]==11){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*(1.0+err_nt0_ffQCD->GetBinContent(12));}
           else if (k==(nbhistMC+39-nbhist_offset)){wfr=fracW*tfr_W*0.90 + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+40-nbhist_offset)){wfr=fracW*tfr_W*1.10 + (1-fracW)*tfr_QCD;}
           else if (k==(nbhistMC+41-nbhist_offset)){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*0.90;}
           else if (k==(nbhistMC+42-nbhist_offset)){wfr=fracW*tfr_W + (1-fracW)*tfr_QCD*1.10;}

           if (is_OS and !is_isolated and is_real){
	     float w_noniso=weight*aweight*weight2*wfr;
             if (is_cat0) h0_anti[k]->Fill(var0,w_noniso);
             if (is_cat1) h1_anti[k]->Fill(var1,w_noniso);
             if (is_cat2) h2_anti[k]->Fill(var2,w_noniso);
             if (is_cat3) h3_anti[k]->Fill(var3,w_noniso);
             if (is_cat4) h4_anti[k]->Fill(var4,w_noniso);
             if (is_cat5) h5_anti[k]->Fill(var5,w_noniso);
             if (is_cat6) h6_anti[k]->Fill(var6,w_noniso);
             if (is_cat7) h7_anti[k]->Fill(var7,w_noniso);
             if (is_cat8) h8_anti[k]->Fill(var8,w_noniso);

             if (is_cat0R) h0R_anti[k]->Fill(var0,w_noniso);
             if (is_cat1R) h1R_anti[k]->Fill(var1,w_noniso);
             if (is_cat2R) h2R_anti[k]->Fill(var2,w_noniso);
             if (is_cat3R) h3R_anti[k]->Fill(var3,w_noniso);
             if (is_cat4R) h4R_anti[k]->Fill(var4,w_noniso);
             if (is_cat5R) h5R_anti[k]->Fill(var5,w_noniso);
             if (is_cat6R) h6R_anti[k]->Fill(var6,w_noniso);
             if (is_cat7R) h7R_anti[k]->Fill(var7,w_noniso);
             if (is_cat8R) h8R_anti[k]->Fill(var8,w_noniso);
           }

	   if (k==0 and is_QCDregion and is_real){
	     float w_iso=weight*aweight*tauidSF;
	     float w_noniso=weight*aweight;
	     if (is_eletrg and !is_isolated){
                if (LepCand_DecayMode[tau_index]==0){ h_tauFR_QCD_dm0_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau_index]==1){ h_tauFR_QCD_dm1_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau_index]==10){ h_tauFR_QCD_dm10_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tauFR_QCD_dm11_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(-1,w_noniso);}
	     }
	     if (is_eletrg and is_isolated){
                if (LepCand_DecayMode[tau_index]==0){ h_tauFR_QCD_dm0_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_QCD_dm0_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau_index]==1){ h_tauFR_QCD_dm1_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_QCD_dm1_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau_index]==10){ h_tauFR_QCD_dm10_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_QCD_dm10_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm10_M->Fill(-1,w_iso);}
                else{ h_tauFR_QCD_dm11_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_QCD_dm11_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm11_M->Fill(-1,w_iso);}
             }

             if (!is_isolated){
                if (is_etautrg or is_etauHPStrg) h_tauFR_QCD_xtrg_VVVL->Fill(1.,w_noniso);
                if (is_eletrg) h_tauFR_QCD_xtrg_VVVL->Fill(2.,w_noniso);
                h_tauFR_QCD_xtrg_VVVL->Fill(0.,w_noniso);
                if (is_etautrg or is_etauHPStrg) h_tauFRpt_QCD_xtrg_VVVL->Fill(my_tau.Pt(),w_noniso);
                if (is_eletrg) h_tauFRpt_QCD_etrg_VVVL->Fill(my_tau.Pt(),w_noniso);
             }
             if (is_isolated){
                if (is_etautrg or is_etauHPStrg) h_tauFR_QCD_xtrg_M->Fill(1.,w_iso);
                if (is_eletrg) h_tauFR_QCD_xtrg_M->Fill(2.,w_iso);
                h_tauFR_QCD_xtrg_M->Fill(0.,w_iso);
                if (is_etautrg or is_etauHPStrg) h_tauFRpt_QCD_xtrg_M->Fill(my_tau.Pt(),w_iso);
                if (is_eletrg) h_tauFRpt_QCD_etrg_M->Fill(my_tau.Pt(),w_iso);
             }
	   }

           if (k==0 and is_Wregion and is_real){
	     float w_noniso=weight*aweight;
             float w_iso=weight*aweight*tauidSF;
             if (is_eletrg and !is_isolated){
                if (LepCand_DecayMode[tau_index]==0){ h_tauFR_W_dm0_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_W_dm0_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_W_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau_index]==1){ h_tauFR_W_dm1_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_W_dm1_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_W_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau_index]==10){ h_tauFR_W_dm10_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_W_dm10_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_W_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tauFR_W_dm11_VVVL->Fill(my_tau.Pt(),w_noniso); h_tauFRnt_W_dm11_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_W_dm11_VVVL->Fill(-1,w_noniso);}
             }
             if (is_eletrg and is_isolated){
                if (LepCand_DecayMode[tau_index]==0){ h_tauFR_W_dm0_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_W_dm0_M->Fill(ntracks,w_iso); h_tauFRnt_W_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau_index]==1){ h_tauFR_W_dm1_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_W_dm1_M->Fill(ntracks,w_iso); h_tauFRnt_W_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau_index]==10){ h_tauFR_W_dm10_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_W_dm10_M->Fill(ntracks,w_iso); h_tauFRnt_W_dm10_M->Fill(-1,w_iso);}
                else{ h_tauFR_W_dm11_M->Fill(my_tau.Pt(),w_iso); h_tauFRnt_W_dm11_M->Fill(ntracks,w_iso); h_tauFRnt_W_dm11_M->Fill(-1,w_iso);}
             }

	     if (!is_isolated){
                if (is_etautrg or is_etauHPStrg) h_tauFR_W_xtrg_VVVL->Fill(1.,w_noniso);
		if (is_eletrg) h_tauFR_W_xtrg_VVVL->Fill(2.,w_noniso);
	    	h_tauFR_W_xtrg_VVVL->Fill(0.,w_noniso);
	     }
             if (is_isolated){
                if (is_etautrg or is_etauHPStrg) h_tauFR_W_xtrg_M->Fill(1.,w_iso);
                if (is_eletrg) h_tauFR_W_xtrg_M->Fill(2.,w_iso);
                h_tauFR_W_xtrg_M->Fill(0.,w_iso);
             }
           } //end loop W FF
           
	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();
    h_dz->Write();

    h_DY_mvis_waco->Write();
    h_DY_ptZ_waco->Write();
    h_DY_aco_waco->Write();
    h_DY_mvis_noaco->Write();
    h_DY_ptZ_noaco->Write();
    h_DY_aco_noaco->Write();

    h_ptll->Write();

    if (sample=="GGTT" or sample=="GGTT_Ctb20"){
      h_acoplanarity->Write();
      h_genacoplanarity->Write();
      h_acoplanarity_sumptlt100->Write();
      h_acoplanarity_sumptgt100->Write();
      h_resolution_acoplanarity->Write();
      h_resolution_acoplanarity_sumptlt100->Write();
      h_resolution_acoplanarity_sumptgt100->Write();
    }

    if (sample=="DY"){
       h_DY_ABCD->Write();

       h_mvis_nt0->Write();
       h_mvis_nt1->Write();
       h_mvis_nt2->Write();
       h_mvis_nt3->Write();
       h_mvis_nt4->Write();
       h_mvis_nt5->Write();
       h_mvis_nt6->Write();
       h_mvis_nt7->Write();
       h_mvis_nt8->Write();
       h_mvis_nt9->Write();

       h_mvis_nt0to10->Write();
       h_mvis_nt10to20->Write();
       h_mvis_nt20to30->Write();
       h_mvis_nt30to40->Write();
       h_mvis_nt40to50->Write();
       h_mvis_nt50to60->Write();
       h_mvis_nt60to70->Write();
       h_mvis_nt70to80->Write();
       h_mvis_nt80to90->Write();
       h_mvis_nt90to100->Write();
    }

    h_vtxresolution_PV->Write();
    h_vtxresolution_simpleditau->Write();
    h_ntracks->Write();
    h_aco->Write();

    fractionOS->Write();
    fractionSS->Write();
    fractionNtrackOS->Write();
    fractionNtrackSS->Write();
    fractionAcoplanarityOS->Write();
    fractionAcoplanaritySS->Write();

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

    h_tauFRnt_W_dm0_M->Write();
    h_tauFRnt_W_dm1_M->Write();
    h_tauFRnt_W_dm10_M->Write();
    h_tauFRnt_W_dm11_M->Write();
    h_tauFRnt_W_dm0_VVVL->Write();
    h_tauFRnt_W_dm1_VVVL->Write();
    h_tauFRnt_W_dm10_VVVL->Write();
    h_tauFRnt_W_dm11_VVVL->Write();
    h_tauFRnt_QCD_dm0_M->Write();
    h_tauFRnt_QCD_dm1_M->Write();
    h_tauFRnt_QCD_dm10_M->Write();
    h_tauFRnt_QCD_dm11_M->Write();
    h_tauFRnt_QCD_dm0_VVVL->Write();
    h_tauFRnt_QCD_dm1_VVVL->Write();
    h_tauFRnt_QCD_dm10_VVVL->Write();
    h_tauFRnt_QCD_dm11_VVVL->Write();

    h_tauFR_QCD_xtrg_VVVL->Write();
    h_tauFR_QCD_xtrg_M->Write();
    h_tauFRpt_QCD_etrg_VVVL->Write();
    h_tauFRpt_QCD_etrg_M->Write();
    h_tauFRpt_QCD_xtrg_VVVL->Write();
    h_tauFRpt_QCD_xtrg_M->Write();
    h_tauFR_W_xtrg_VVVL->Write();
    h_tauFR_W_xtrg_M->Write();

cout<<h0[0]->Integral()<<endl;
    bool isMC=(name!="data_obs");
    WriteHistToFileETau(fout, h0, name, "et_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileETau(fout, h0_anti, name, "et_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileETau(fout, h1, name, "et_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileETau(fout, h1_anti, name, "et_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    WriteHistToFileETau(fout, h2, name, "et_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
    WriteHistToFileETau(fout, h2_anti, name, "et_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    if (is_control>0){
       WriteHistToFileETau(fout, h3, name, "et_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h3_anti, name, "et_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h4, name, "et_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h4_anti, name, "et_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h5, name, "et_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h5_anti, name, "et_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h6, name, "et_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h6_anti, name, "et_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h7, name, "et_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h7_anti, name, "et_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h8, name, "et_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h8_anti, name, "et_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
    }

    if (sample=="DY"){
       WriteHistToFileETau(fout, h0R, name, "etR_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h0R_anti, name, "etR_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h1R, name, "etR_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h1R_anti, name, "etR_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       WriteHistToFileETau(fout, h2R, name, "etR_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
       WriteHistToFileETau(fout, h2R_anti, name, "etR_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       if (is_control>0){
          WriteHistToFileETau(fout, h3R, name, "etR_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h3R_anti, name, "etR_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
          WriteHistToFileETau(fout, h4R, name, "etR_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h4R_anti, name, "etR_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
          WriteHistToFileETau(fout, h5R, name, "etR_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h5R_anti, name, "etR_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
          WriteHistToFileETau(fout, h6R, name, "etR_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h6R_anti, name, "etR_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
          WriteHistToFileETau(fout, h7R, name, "etR_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h7R_anti, name, "etR_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
          WriteHistToFileETau(fout, h8R, name, "etR_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, isMC);
          WriteHistToFileETau(fout, h8R_anti, name, "etR_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset,nbhistMC, true);
       }
    }


    fout->Close();
} 


