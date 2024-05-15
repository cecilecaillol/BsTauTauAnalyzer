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
#include "dz_Tree.h"

using namespace std;

int main(int argc, char** argv) {

    int is_control=1;

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
    TFile *f_Friend = new TFile(input_friend.c_str());//FIXME
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
    else if (sample=="VV2L2Nu"){ xs=14.26; weight=luminosity*xs/ngen;}
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

    arbre->SetBranchAddress("run", &run);
    arbre->SetBranchAddress("event", &event);

    arbre->SetBranchAddress("MET_pt", &MET_pt);
    arbre->SetBranchAddress("MET_phi", &MET_phi);
    arbre->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg);
    arbre->SetBranchAddress("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg);
    arbre->SetBranchAddress("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg", &HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg);
    arbre->SetBranchAddress("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg", &HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg);


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
    ami->SetBranchAddress("ntracksAll_friend", &ntracksAll_friend);
    ami->SetBranchAddress("ntracksHS_friend", &ntracksHS_friend);
    ami->SetBranchAddress("ntracksPU_friend", &ntracksPU_friend);

    arbre->AddFriend(ami);

   int nbhist=1;
   int nbhist_offset=0;
   nbhist=1;//FIXME
	
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
   float bins0[] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,400,500};//mvis
   float bins1[] = {25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99,110,120};//e pt
   float bins2[] = {20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120};//tau pt
   float bins3[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//e eta
   float bins4[] = {-2.5,-2.3,-2.1,-1.9,-1.7,-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};//tau eta
   float bins5[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,80,90,100,110,120};//met
   float bins6[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180};//mt
   //float bins7[] = {0,1,2,3,4,5,6,7,8,9,10,11};//njets
   float bins7[] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
   float bins8[] = {0,0.025,0.05,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6,0.625,0.65,0.675,0.7,0.725,0.75,0.775,0.8,0.825,0.85,0.875,0.9,0.925,0.95,0.975,1.0};//acoplanarity

   // Signal region
   /*float bins0[] = {70,85,100,150,200,250};//mvis
   float bins1[] = {70,85,100,150,200,250};//mvis
   float bins2[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins3[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins4[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins5[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins6[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins7[] = {40,55,70,85,100,125,150,200,350,500};//mvis
   float bins8[] = {40,55,70,85,100,125,150,200,350,500};//mvis*/

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

   float bins_taupt0[] = {40,50,75,100,200,300};
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

   TH1F *h_tauFR_QCD_dm0_VVVL=new TH1F("h_tauFR_QCD_dm0_VVVL","h_tauFR_QCD_dm0_VVVL",binnum_taupt0,bins_taupt0); h_tauFR_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm1_VVVL=new TH1F("h_tauFR_QCD_dm1_VVVL","h_tauFR_QCD_dm1_VVVL",binnum_taupt1,bins_taupt1); h_tauFR_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm10_VVVL=new TH1F("h_tauFR_QCD_dm10_VVVL","h_tauFR_QCD_dm10_VVVL",binnum_taupt10,bins_taupt10); h_tauFR_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm11_VVVL=new TH1F("h_tauFR_QCD_dm11_VVVL","h_tauFR_QCD_dm11_VVVL",binnum_taupt11,bins_taupt11); h_tauFR_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tauFR_QCD_dm0_M=new TH1F("h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_M",binnum_taupt0,bins_taupt0); h_tauFR_QCD_dm0_M->Sumw2();
   TH1F *h_tauFR_QCD_dm1_M=new TH1F("h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_M",binnum_taupt1,bins_taupt1); h_tauFR_QCD_dm1_M->Sumw2();
   TH1F *h_tauFR_QCD_dm10_M=new TH1F("h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_M",binnum_taupt10,bins_taupt10); h_tauFR_QCD_dm10_M->Sumw2();
   TH1F *h_tauFR_QCD_dm11_M=new TH1F("h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_M",binnum_taupt11,bins_taupt11); h_tauFR_QCD_dm11_M->Sumw2();

   TH1F *h_tauFRnt_QCD_dm0_VVVL=new TH1F("h_tauFRnt_QCD_dm0_VVVL","h_tauFRnt_QCD_dm0_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm1_VVVL=new TH1F("h_tauFRnt_QCD_dm1_VVVL","h_tauFRnt_QCD_dm1_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm10_VVVL=new TH1F("h_tauFRnt_QCD_dm10_VVVL","h_tauFRnt_QCD_dm10_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm11_VVVL=new TH1F("h_tauFRnt_QCD_dm11_VVVL","h_tauFRnt_QCD_dm11_VVVL",binnum_nt,bins_nt); h_tauFRnt_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tauFRnt_QCD_dm0_M=new TH1F("h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm0_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm1_M=new TH1F("h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm1_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm10_M=new TH1F("h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm10_M->Sumw2();
   TH1F *h_tauFRnt_QCD_dm11_M=new TH1F("h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_M",binnum_nt,bins_nt); h_tauFRnt_QCD_dm11_M->Sumw2();

   TH1F *h_tau1FR_QCD_dm0_VVVL=new TH1F("h_tau1FR_QCD_dm0_VVVL","h_tau1FR_QCD_dm0_VVVL",binnum_taupt0,bins_taupt0); h_tau1FR_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tau1FR_QCD_dm1_VVVL=new TH1F("h_tau1FR_QCD_dm1_VVVL","h_tau1FR_QCD_dm1_VVVL",binnum_taupt1,bins_taupt1); h_tau1FR_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tau1FR_QCD_dm10_VVVL=new TH1F("h_tau1FR_QCD_dm10_VVVL","h_tau1FR_QCD_dm10_VVVL",binnum_taupt10,bins_taupt10); h_tau1FR_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tau1FR_QCD_dm11_VVVL=new TH1F("h_tau1FR_QCD_dm11_VVVL","h_tau1FR_QCD_dm11_VVVL",binnum_taupt11,bins_taupt11); h_tau1FR_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tau1FR_QCD_dm0_M=new TH1F("h_tau1FR_QCD_dm0_M","h_tau1FR_QCD_dm0_M",binnum_taupt0,bins_taupt0); h_tau1FR_QCD_dm0_M->Sumw2();
   TH1F *h_tau1FR_QCD_dm1_M=new TH1F("h_tau1FR_QCD_dm1_M","h_tau1FR_QCD_dm1_M",binnum_taupt1,bins_taupt1); h_tau1FR_QCD_dm1_M->Sumw2();
   TH1F *h_tau1FR_QCD_dm10_M=new TH1F("h_tau1FR_QCD_dm10_M","h_tau1FR_QCD_dm10_M",binnum_taupt10,bins_taupt10); h_tau1FR_QCD_dm10_M->Sumw2();
   TH1F *h_tau1FR_QCD_dm11_M=new TH1F("h_tau1FR_QCD_dm11_M","h_tau1FR_QCD_dm11_M",binnum_taupt11,bins_taupt11); h_tau1FR_QCD_dm11_M->Sumw2();

   TH1F *h_tau1FRnt_QCD_dm0_VVVL=new TH1F("h_tau1FRnt_QCD_dm0_VVVL","h_tau1FRnt_QCD_dm0_VVVL",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm1_VVVL=new TH1F("h_tau1FRnt_QCD_dm1_VVVL","h_tau1FRnt_QCD_dm1_VVVL",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm10_VVVL=new TH1F("h_tau1FRnt_QCD_dm10_VVVL","h_tau1FRnt_QCD_dm10_VVVL",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm11_VVVL=new TH1F("h_tau1FRnt_QCD_dm11_VVVL","h_tau1FRnt_QCD_dm11_VVVL",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm0_M=new TH1F("h_tau1FRnt_QCD_dm0_M","h_tau1FRnt_QCD_dm0_M",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm0_M->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm1_M=new TH1F("h_tau1FRnt_QCD_dm1_M","h_tau1FRnt_QCD_dm1_M",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm1_M->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm10_M=new TH1F("h_tau1FRnt_QCD_dm10_M","h_tau1FRnt_QCD_dm10_M",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm10_M->Sumw2();
   TH1F *h_tau1FRnt_QCD_dm11_M=new TH1F("h_tau1FRnt_QCD_dm11_M","h_tau1FRnt_QCD_dm11_M",binnum_nt,bins_nt); h_tau1FRnt_QCD_dm11_M->Sumw2();


   TH1F *h_tau2FR_QCD_dm0_VVVL=new TH1F("h_tau2FR_QCD_dm0_VVVL","h_tau2FR_QCD_dm0_VVVL",binnum_taupt0,bins_taupt0); h_tau2FR_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tau2FR_QCD_dm1_VVVL=new TH1F("h_tau2FR_QCD_dm1_VVVL","h_tau2FR_QCD_dm1_VVVL",binnum_taupt1,bins_taupt1); h_tau2FR_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tau2FR_QCD_dm10_VVVL=new TH1F("h_tau2FR_QCD_dm10_VVVL","h_tau2FR_QCD_dm10_VVVL",binnum_taupt10,bins_taupt10); h_tau2FR_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tau2FR_QCD_dm11_VVVL=new TH1F("h_tau2FR_QCD_dm11_VVVL","h_tau2FR_QCD_dm11_VVVL",binnum_taupt11,bins_taupt11); h_tau2FR_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tau2FR_QCD_dm0_M=new TH1F("h_tau2FR_QCD_dm0_M","h_tau2FR_QCD_dm0_M",binnum_taupt0,bins_taupt0); h_tau2FR_QCD_dm0_M->Sumw2();
   TH1F *h_tau2FR_QCD_dm1_M=new TH1F("h_tau2FR_QCD_dm1_M","h_tau2FR_QCD_dm1_M",binnum_taupt1,bins_taupt1); h_tau2FR_QCD_dm1_M->Sumw2();
   TH1F *h_tau2FR_QCD_dm10_M=new TH1F("h_tau2FR_QCD_dm10_M","h_tau2FR_QCD_dm10_M",binnum_taupt10,bins_taupt10); h_tau2FR_QCD_dm10_M->Sumw2();
   TH1F *h_tau2FR_QCD_dm11_M=new TH1F("h_tau2FR_QCD_dm11_M","h_tau2FR_QCD_dm11_M",binnum_taupt11,bins_taupt11); h_tau2FR_QCD_dm11_M->Sumw2();

   TH1F *h_tau2FRnt_QCD_dm0_VVVL=new TH1F("h_tau2FRnt_QCD_dm0_VVVL","h_tau2FRnt_QCD_dm0_VVVL",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm0_VVVL->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm1_VVVL=new TH1F("h_tau2FRnt_QCD_dm1_VVVL","h_tau2FRnt_QCD_dm1_VVVL",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm1_VVVL->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm10_VVVL=new TH1F("h_tau2FRnt_QCD_dm10_VVVL","h_tau2FRnt_QCD_dm10_VVVL",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm10_VVVL->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm11_VVVL=new TH1F("h_tau2FRnt_QCD_dm11_VVVL","h_tau2FRnt_QCD_dm11_VVVL",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm11_VVVL->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm0_M=new TH1F("h_tau2FRnt_QCD_dm0_M","h_tau2FRnt_QCD_dm0_M",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm0_M->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm1_M=new TH1F("h_tau2FRnt_QCD_dm1_M","h_tau2FRnt_QCD_dm1_M",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm1_M->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm10_M=new TH1F("h_tau2FRnt_QCD_dm10_M","h_tau2FRnt_QCD_dm10_M",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm10_M->Sumw2();
   TH1F *h_tau2FRnt_QCD_dm11_M=new TH1F("h_tau2FRnt_QCD_dm11_M","h_tau2FRnt_QCD_dm11_M",binnum_nt,bins_nt); h_tau2FRnt_QCD_dm11_M->Sumw2();


   TString uncertainties[1]={""};

   for (int k = 0; k < 1; ++k){
      if (year=="2016pre") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016preVFP");
      if (year=="2016post") uncertainties[k]=uncertainties[k].ReplaceAll("year","2016postVFP");
      if (year=="2017") uncertainties[k]=uncertainties[k].ReplaceAll("year","2017");
      if (year=="2018") uncertainties[k]=uncertainties[k].ReplaceAll("year","2018");
   }

   TFile* f_zpt= new TFile("zptm_weights_2018_kit.root");
   TH2F* h_zpt= (TH2F*) f_zpt->Get("zptmass_histo");

   TString fake_uncertainties[1]={""};

   TFile* f_taufr = new TFile("fakerate/FitValues_tautau_tauFR_2018.root");
   TF1 *fit_taufr_QCD_dm0 = (TF1*) f_taufr->Get("theFit_QCD_dm0");
   TF1 *fit_taufr_QCD_dm1 = (TF1*) f_taufr->Get("theFit_QCD_dm1");
   TF1 *fit_taufr_QCD_dm10 = (TF1*) f_taufr->Get("theFit_QCD_dm10");
   TF1 *fit_taufr_QCD_dm11 = (TF1*) f_taufr->Get("theFit_QCD_dm11");

   TF1 *fit_taufr_QCD1_dm0 = (TF1*) f_taufr->Get("theFit_QCD1_dm0");
   TF1 *fit_taufr_QCD1_dm1 = (TF1*) f_taufr->Get("theFit_QCD1_dm1");
   TF1 *fit_taufr_QCD1_dm10 = (TF1*) f_taufr->Get("theFit_QCD1_dm10");
   TF1 *fit_taufr_QCD1_dm11 = (TF1*) f_taufr->Get("theFit_QCD1_dm11");

   TF1 *fit_taufr_QCD2_dm0 = (TF1*) f_taufr->Get("theFit_QCD2_dm0");
   TF1 *fit_taufr_QCD2_dm1 = (TF1*) f_taufr->Get("theFit_QCD2_dm1");
   TF1 *fit_taufr_QCD2_dm10 = (TF1*) f_taufr->Get("theFit_QCD2_dm10");
   TF1 *fit_taufr_QCD2_dm11 = (TF1*) f_taufr->Get("theFit_QCD2_dm11");

   TH1F *h_tau1_nt_dm0 = (TH1F*) f_taufr->Get("h_tau1FRnt_QCD_dm0_M");
   TH1F *h_tau1_nt_dm1 = (TH1F*) f_taufr->Get("h_tau1FRnt_QCD_dm1_M");
   TH1F *h_tau1_nt_dm10 = (TH1F*) f_taufr->Get("h_tau1FRnt_QCD_dm10_M");
   TH1F *h_tau1_nt_dm11 = (TH1F*) f_taufr->Get("h_tau1FRnt_QCD_dm11_M");
   TH1F *h_tau2_nt_dm0 = (TH1F*) f_taufr->Get("h_tau2FRnt_QCD_dm0_M");
   TH1F *h_tau2_nt_dm1 = (TH1F*) f_taufr->Get("h_tau2FRnt_QCD_dm1_M");
   TH1F *h_tau2_nt_dm10 = (TH1F*) f_taufr->Get("h_tau2FRnt_QCD_dm10_M");
   TH1F *h_tau2_nt_dm11 = (TH1F*) f_taufr->Get("h_tau2FRnt_QCD_dm11_M");


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

   auto b2_1=arbre->GetBranch("HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg");
   auto b2_2=arbre->GetBranch("HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg");
   auto b2_3=arbre->GetBranch("HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg");
   auto b2_4=arbre->GetBranch("HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg");
   auto b2_5=arbre->GetBranch("run");

   auto b3_1=arbre->GetBranch("LepCand_vse");
   auto b3_2=arbre->GetBranch("LepCand_vsmu");
   auto b3_3=arbre->GetBranch("LepCand_vsjet");
   auto b3_4=arbre->GetBranch("LepCand_charge");
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

   auto b10_1=arbre->GetBranch("run");
   auto b10_2=arbre->GetBranch("event");

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

   TH1F *h_dz_beforetrigger=new TH1F("h_dz_beforetrigger","h_dz_beforetrigger",40,-10,10); h_dz_beforetrigger->Sumw2();
   TH1F *h_dz_aftertrigger=new TH1F("h_dz_aftertrigger","h_dz_aftertrigger",40,-10,10); h_dz_aftertrigger->Sumw2();
   TH1F *h_logdz_beforetrigger=new TH1F("h_logdz_beforetrigger","h_logdz_beforetrigger",50,-10,1); h_logdz_beforetrigger->Sumw2();
   TH1F *h_logdz_aftertrigger=new TH1F("h_logdz_aftertrigger","h_logdz_aftertrigger",50,-10,1); h_logdz_aftertrigger->Sumw2();

    TTree * tree2 = new TTree("dz_tree", "dz_tree");
    tree2->SetDirectory(0);
    tree2->Branch("tau1pt_", &tau1pt_, "tau1pt_/F");
    tree2->Branch("tau2pt_", &tau2pt_, "tau2pt_/F");
    tree2->Branch("tau1eta_", &tau1eta_, "tau1eta_/F");
    tree2->Branch("tau2eta_", &tau2eta_, "tau2eta_/F");
    tree2->Branch("tau1phi_", &tau1phi_, "tau1phi_/F");
    tree2->Branch("tau2phi_", &tau2phi_, "tau2phi_/F");
    tree2->Branch("tau1dm_", &tau1dm_, "tau1dm_/I");
    tree2->Branch("tau2dm_", &tau2dm_, "tau2dm_/I");
    tree2->Branch("GenVtx_z_", &GenVtx_z_, "GenVtx_z_/F");
    tree2->Branch("recoDitau_z_", &recoDitau_z_, "recoDitau_z_/F");
    tree2->Branch("tau1dz_", &tau1dz_, "tau1dz_/F");
    tree2->Branch("tau2dz_", &tau2dz_, "tau2dz_/F");
    tree2->Branch("weight_", &weight_, "weight_/F");


   for (Int_t i = 0; i < nentries_wtn; i++) {
	arbre->LoadTree(i);
        //arbre->GetEntry(i);
        //if (i % 10000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        //fflush(stdout);

        b10_1->GetEntry(i); b10_2->GetEntry(i);
	bool is_found=false;
	//if (event==1028757907 or event==1748120543 or event==614015687){ cout<<"found "<<event<<endl; is_found=true;}

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

	int tau1_index=-1;
	for (int j=0; j<nLepCand; ++j){
	   if (fabs(LepCand_eta[j])<2.1 and tau1_index<0 and LepCand_id[j]==15) tau1_index=j;
	}
        int tau2_index=-1; float dz_tmp=10000;
        for (int j=0; j<nLepCand; ++j){
           if (fabs(LepCand_eta[j])<2.1 and j!=tau1_index and LepCand_id[j]==15 and fabs(LepCand_dz[j]-LepCand_dz[tau1_index])<dz_tmp){
	      tau2_index=j; 
	      dz_tmp=fabs(LepCand_dz[j]-LepCand_dz[tau1_index]);
	   }
        }
        TLorentzVector my_tau1; my_tau1.SetPtEtaPhiM(LepCand_pt[tau1_index],LepCand_eta[tau1_index],LepCand_phi[tau1_index],0);
        TLorentzVector my_tau2; my_tau2.SetPtEtaPhiM(LepCand_pt[tau2_index],LepCand_eta[tau2_index],LepCand_phi[tau2_index],0);

	if (name!="data_obs" and LepCand_gen[tau2_index]==5) my_tau2=my_tau2*LepCand_taues[tau2_index];
        if (name!="data_obs" and LepCand_gen[tau2_index]>=1 and LepCand_gen[tau1_index]<=4) my_tau2=my_tau2*LepCand_fes[tau2_index];
        if (name!="data_obs" and LepCand_gen[tau1_index]==5) my_tau1=my_tau1*LepCand_taues[tau1_index];
        if (name!="data_obs" and LepCand_gen[tau1_index]>=1 and LepCand_gen[tau1_index]<=4) my_tau1=my_tau1*LepCand_fes[tau1_index];


	if (fabs(my_tau1.Eta())>2.1) continue;
        if (fabs(my_tau2.Eta())>2.1) continue;
	if (my_tau2.DeltaR(my_tau1)<0.5) continue;

if (is_found) cout<<event<<" passed eta DR"<<endl;

	// Trigger block
	if (name=="data_obs") {b2_5->GetEntry(i);}
	if (year=="2018"){
	   if (name=="data_obs" and run<317509) {b2_2->GetEntry(i); b2_3->GetEntry(i); b2_4->GetEntry(i);}
	   else {b2_1->GetEntry(i); }
	}
        b3_7->GetEntry(i);

//cout<<my_tau1.Pt()<<" "<<my_tau2.Pt()<<" "<<LepCand_vsjet[tau1_index]<<" "<<LepCand_vsjet[tau2_index]<<" "<<fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])<<" "<<LepCand_gen[tau1_index]<<" "<<LepCand_gen[tau2_index]<<endl;
	if (my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1 and fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])<0.1 and LepCand_gen[tau1_index]==5 and LepCand_gen[tau2_index]==5) h_dz_beforetrigger->Fill(LepCand_dz[tau1_index]);
        if (my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1 and fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])<0.1 and LepCand_gen[tau1_index]==5 and LepCand_gen[tau2_index]==5) h_logdz_beforetrigger->Fill(log10(fabs(LepCand_dz[tau1_index])));
	bool is_trg=false;
	if (year=="2018"){
	   if (name!="data_obs" or run>=317509) is_trg=(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg and my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1);
	   else is_trg=((HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg or HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg or HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg) and my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1);
	}
	if (year=="2017"){
           //is_trg=((HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg or HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg or HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg) and my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1);
	   is_trg=(LepCand_trgmatch[tau1_index]==1 and LepCand_trgmatch[tau2_index]==1);
	}
//cout<<is_trg<<" "<<LepCand_trgmatch[tau1_index]<<" "<<LepCand_trgmatch[tau2_index]<<endl;
	if (!is_trg) continue;
        if (my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1 and fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])<0.1 and LepCand_gen[tau1_index]==5 and LepCand_gen[tau2_index]==5) h_dz_aftertrigger->Fill(LepCand_dz[tau1_index]);
        if (my_tau1.Pt()>40 and my_tau2.Pt()>40 and fabs(my_tau1.Eta())<2.1 and fabs(my_tau2.Eta())<2.1 and fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])<0.1 and LepCand_gen[tau1_index]==5 and LepCand_gen[tau2_index]==5) h_logdz_aftertrigger->Fill(log10(fabs(LepCand_dz[tau1_index])));

if (is_found) cout<<event<<" passed trigger"<<endl;

	// Block ID/iso/charge
	b3_1->GetEntry(i); b3_2->GetEntry(i); b3_3->GetEntry(i); b3_4->GetEntry(i); b3_6->GetEntry(i); 
	if (LepCand_vse[tau1_index]<2 or LepCand_vsmu[tau1_index]<1 or LepCand_vsjet[tau1_index]<1) continue; //was 127
        if (LepCand_vse[tau2_index]<2 or LepCand_vsmu[tau2_index]<1 or LepCand_vsjet[tau2_index]<1) continue;
	bool is_OS = (LepCand_charge[tau1_index]*LepCand_charge[tau2_index]<0);
	bool is_isolated = (LepCand_vsjet[tau1_index]>=16 and LepCand_vsjet[tau2_index]>=16);
	bool is_PF=(LepCand_vsjet[tau1_index]>=16 and LepCand_vsjet[tau2_index]<16);
        bool is_FP=(LepCand_vsjet[tau1_index]<16 and LepCand_vsjet[tau2_index]>=16);
        bool is_FF=(LepCand_vsjet[tau1_index]<16 and LepCand_vsjet[tau2_index]<16);

if (is_found) cout<<event<<" passed loose iso"<<endl;

	// Block weights
	if (name!="data_obs") {b4_1->GetEntry(i); b4_2->GetEntry(i); b4_3->GetEntry(i); b4_4->GetEntry(i); b4_5->GetEntry(i); b4_6->GetEntry(i); b4_24->GetEntry(i); }
        if (name!="data_obs" and nbhist>1){ b4_8->GetEntry(i); b4_9->GetEntry(i); b4_10->GetEntry(i); b4_11->GetEntry(i); b4_12->GetEntry(i); b4_13->GetEntry(i); b4_14->GetEntry(i); b4_15->GetEntry(i); b4_16->GetEntry(i); b4_17->GetEntry(i); b4_18->GetEntry(i); b4_19->GetEntry(i); b4_20->GetEntry(i);b4_21->GetEntry(i); b4_22->GetEntry(i); b4_23->GetEntry(i); b4_25->GetEntry(i); b4_26->GetEntry(i);}
        if (name!="data_obs"){ b4_27->GetEntry(i); b4_28->GetEntry(i); b4_29->GetEntry(i); b4_30->GetEntry(i); b4_31->GetEntry(i);}

	b4_7->GetEntry(i);
        float acoplanarity = (1.0 -fabs(my_tau1.DeltaPhi(my_tau2))/3.14159);

	float gen_aco=acoplanarity;
        TLorentzVector my_gen1; my_gen1.SetPtEtaPhiM(0,0,0,0);
        TLorentzVector my_gen2; my_gen2.SetPtEtaPhiM(0,0,0,0);
//cout<<event<<" "<<nGenCand<<" "<<GenCand_pt[0]<<" "<<GenCand_pt[1]<<endl;
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
        float gen_mtt=200.0;
        if (nGenCand>1 and (sample=="GGTT" or sample=="GGWW" or sample=="GGTT_Ctb20")) gen_mtt=(my_gen1+my_gen2).M();


	float aweight=1.0;
	float tauidSF=1.0;
	if (name!="data_obs"){
	   aweight=aweight*puWeight;
	   if (name!="W") aweight*=genWeight;
	   if (LepCand_gen[tau1_index]==5) tauidSF=LepCand_tauidMsf[tau1_index];
           if (LepCand_gen[tau2_index]==5) tauidSF=tauidSF*LepCand_tauidMsf[tau2_index];
           if (LepCand_gen[tau1_index]==1 or LepCand_gen[tau1_index]==3) aweight=aweight*LepCand_antielesf[tau1_index];
           if (LepCand_gen[tau1_index]==2 or LepCand_gen[tau1_index]==4) aweight=aweight*LepCand_antimusf[tau1_index];
           if (LepCand_gen[tau2_index]==1 or LepCand_gen[tau2_index]==3) aweight=aweight*LepCand_antielesf[tau2_index];
           if (LepCand_gen[tau2_index]==2 or LepCand_gen[tau2_index]==4) aweight=aweight*LepCand_antimusf[tau2_index];
	   aweight=aweight*LepCand_tautriggersf[tau1_index]*LepCand_tautriggersf[tau2_index];
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
	}
	aweight=aweight*h_zpt->GetBinContent(h_zpt->GetXaxis()->FindBin((my_gen1+my_gen2).M()),h_zpt->GetYaxis()->FindBin((my_gen1+my_gen2).Pt())); //FIXME z pt Bisnupriya
	//cout<<h_zpt->GetBinContent(h_zpt->GetXaxis()->FindBin((my_gen1+my_gen2).M()),h_zpt->GetXaxis()->FindBin((my_gen1+my_gen2).Pt()))<<" "<<(my_gen1+my_gen2).M()<<" "<<(my_gen1+my_gen2).Pt()<<endl;


	// Block MET
	b5_1->GetEntry(i); b5_2->GetEntry(i);
	TLorentzVector my_met;
	my_met.SetPtEtaPhiM(MET_pt,0,MET_phi,0);

	bool is_QCDregion = (!is_OS);

	bool is_real=(name=="GGTT" or name=="GGTT2" or name=="data_obs" or (LepCand_gen[tau1_index]>=1 and LepCand_gen[tau1_index]<=5 and LepCand_gen[tau2_index]>=1 and LepCand_gen[tau2_index]<=5));
//if (is_real) cout<<TMath::Min((my_tau1.DeltaR(my_gen1)+my_tau2.DeltaR(my_gen2)),(my_tau1.DeltaR(my_gen2)+my_tau2.DeltaR(my_gen1)))<<" "<<my_gen1.Pt()<<" "<<my_gen2.Pt()<<" "<<nGenCand<<endl;
	if ((name=="ZTT" or sample=="GGTT" or sample=="GGTT_Ctb20") and (my_tau1.DeltaR(my_gen1)+my_tau2.DeltaR(my_gen2))>0.2 and (my_tau1.DeltaR(my_gen2)+my_tau2.DeltaR(my_gen1))>0.2) is_real=false; //FIXME

	//is_real=true;//FIXME


	// Block vertex
        b6_1->GetEntry(i); 
        if (name!="data_obs") b6_2->GetEntry(i);
	//if (fabs(LepCand_dz[tau1_index]-LepCand_dz[tau2_index])>0.1) continue; //FIXME
        float simple_ditau_z=0.5*(2*PV_z+LepCand_dz[tau1_index]+LepCand_dz[tau2_index]);

if (is_found) cout<<event<<" passed dz"<<endl;

        b8_1->GetEntry(i); b8_2->GetEntry(i); b8_3->GetEntry(i); b8_4->GetEntry(i);
        int ntracks=ntracks_friend;

        float zpos=simple_ditau_z;
        if (zpos<-10) zpos=-9.99;
        else if (zpos>10) zpos=9.99;
        int ntpu=ntracksPU_friend;
        if (ntpu>49) ntpu=49;
        if (sample!="data_obs") {aweight*=correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos));}

        if (sample=="DY"){ aweight*=correction_mapHS->GetBinContent(correction_mapHS->GetXaxis()->FindBin(TMath::Min(30,ntracksHS_friend)),correction_mapHS->GetYaxis()->FindBin(gen_aco)); }

        if (sample=="GGTT" or sample=="GGTT_Ctb20"){ // rescaling from mumu region
           if (ntracks==0) aweight*=(2.22+0.00572*gen_mtt);
           else if (ntracks==1) aweight*=(1.93+0.00218*gen_mtt);
           b9_1->GetEntry(i);
           if (name=="GGTT_0p0" or name=="GGTT") aweight*=TauG2Weights_ceBRe_0p0;
        }

	bool is_lowNT=true;//FIXME
	bool is_lowA=(acoplanarity<0.015);

        for (int k=0; k<nbhist; ++k){
	   float weight2=1.0;


	   float mvis=(my_tau1+my_tau2).M();
	   if (mvis<40) continue;
	   if (my_tau2.Pt()<40) continue;
           if (my_tau1.Pt()<40) continue;

if (is_found) cout<<event<<" passed pt mvis"<<endl;

           bool is_cat0=true;
           bool is_cat1=true;
           bool is_cat2=true;
           bool is_cat3=true;
           bool is_cat4=true;
           bool is_cat5=true;
           bool is_cat6=true;
           bool is_cat7=true;
           bool is_cat8=true;

           bool is_cat0R=true;
           bool is_cat1R=true;
           bool is_cat2R=true;
           bool is_cat3R=true;
           bool is_cat4R=true;
           bool is_cat5R=true;
           bool is_cat6R=true;
           bool is_cat7R=true;
           bool is_cat8R=true;

	   float var0 = mvis;
           float var1 = my_tau1.Pt();
           float var2 = my_tau2.Pt();
           float var3 = my_tau1.Eta();
           float var4 = my_tau2.Eta();//LepCand_DecayMode[tau1_index];
           float var5 = my_met.Pt();
           float var6 = (my_tau1+my_tau2).Pt();
           float var7 = my_tau1.DeltaR(my_tau2);
           float var8 = acoplanarity;

	   if (is_control==0){
	      is_cat0=(is_lowA and ntracks==0 );
              is_cat1=(is_lowA and ntracks==1 );
              is_cat2=(is_lowA and LepCand_DecayMode[tau1_index]==0);
              is_cat3=(is_lowA and LepCand_DecayMode[tau1_index]==1);
              is_cat4=(is_lowA and LepCand_DecayMode[tau1_index]==10);
              is_cat5=(is_lowA and LepCand_DecayMode[tau1_index]==11);
              is_cat6=(is_lowA);
              is_cat7=(is_lowA);
              is_cat8=(is_lowA);

              is_cat0R=(is_lowA and ntracks<10);
              is_cat1R=(is_lowA and ntracks<10);
              is_cat2R=(is_lowA and LepCand_DecayMode[tau1_index]==0);
              is_cat3R=(is_lowA and LepCand_DecayMode[tau1_index]==1);
              is_cat4R=(is_lowA and LepCand_DecayMode[tau1_index]==10);
              is_cat5R=(is_lowA and LepCand_DecayMode[tau1_index]==11);
              is_cat6R=(is_lowA);
              is_cat7R=(is_lowA);
              is_cat8R=(is_lowA);

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

	   if (is_OS and is_isolated and is_real){
	     float w_iso=weight*aweight*weight2*tauidSF;

/*if (is_cat0R) cout<<"reco: ("<<my_tau1.Pt()<<", "<<my_tau1.Eta()<<", "<<my_tau1.Phi()<<") ("<<my_tau2.Pt()<<", "<<my_tau2.Eta()<<", "<<my_tau2.Phi()<<")"<<endl;
if (is_cat0R) cout<<"gen match: "<<LepCand_gen[tau1_index]<<" "<<LepCand_gen[tau2_index]<<endl;
if (is_cat0R) cout<<"gen: ("<<my_gen1.Pt()<<", "<<my_gen1.Eta()<<", "<<my_gen1.Phi()<<") ("<<my_gen2.Pt()<<", "<<my_gen2.Eta()<<", "<<my_gen2.Phi()<<")"<<endl;*/
//if (is_cat0) cout<<run<<":"<<event<<endl;

if (is_found) cout<<event<<" passed OS iso real"<<endl;
if (is_found) cout<<acoplanarity<<" "<<ntracks<<endl;
if (is_found and is_cat0) cout<<event<<" passed ntracks and aco"<<endl;

//if (is_cat0) cout<<event<<" "<<my_tau1.Pt()<<" "<<my_tau2.Pt()<<" "<<var0<<" "<<weight*genWeight<<" "<<puWeight<<" "<<TauG2Weights_ceBRe_0p0<<" "<<(LepCand_tautriggersf[tau1_index]*LepCand_tautriggersf[tau2_index])<<" "<<tauidSF<<" "<<correction_map->GetBinContent(correction_map->GetXaxis()->FindBin(ntpu),correction_map->GetYaxis()->FindBin(zpos))<<" "<<(2.22+0.00572*gen_mtt)<<endl;
//
             if (k==0) fillTreeDzTautau(tree2,my_tau1.Pt(),my_tau2.Pt(),my_tau1.Eta(),my_tau2.Eta(),my_tau1.Phi(),my_tau2.Phi(),LepCand_DecayMode[tau1_index],LepCand_DecayMode[tau2_index],GenVtx_z,simple_ditau_z,LepCand_dz[tau1_index],LepCand_dz[tau2_index],w_iso);


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
	   }

	   float tpt1=my_tau1.Pt();
	   if (tpt1>300) tpt1=299;
           float tfr1_QCD=0.1;
           if (LepCand_DecayMode[tau1_index]==0) tfr1_QCD=TMath::Min(1.0,fit_taufr_QCD1_dm0->Eval(tpt1));
           else if (LepCand_DecayMode[tau1_index]==1) tfr1_QCD=TMath::Min(1.0,fit_taufr_QCD1_dm1->Eval(tpt1));
           else if (LepCand_DecayMode[tau1_index]==10) tfr1_QCD=TMath::Min(1.0,fit_taufr_QCD1_dm10->Eval(tpt1));
           else if (LepCand_DecayMode[tau1_index]==11) tfr1_QCD=TMath::Min(1.0,fit_taufr_QCD1_dm11->Eval(tpt1));
	   if (ntracks==0){
              if (LepCand_DecayMode[tau1_index]==0) tfr1_QCD*=h_tau1_nt_dm0->GetBinContent(2);
              else if (LepCand_DecayMode[tau1_index]==1) tfr1_QCD*=h_tau1_nt_dm1->GetBinContent(2);
              else if (LepCand_DecayMode[tau1_index]==10) tfr1_QCD*=h_tau1_nt_dm10->GetBinContent(2);
              else if (LepCand_DecayMode[tau1_index]==11) tfr1_QCD*=h_tau1_nt_dm11->GetBinContent(2);
 	   }
	   else if (ntracks==1){
              if (LepCand_DecayMode[tau1_index]==0) tfr1_QCD*=h_tau1_nt_dm0->GetBinContent(3);
              else if (LepCand_DecayMode[tau1_index]==1) tfr1_QCD*=h_tau1_nt_dm1->GetBinContent(3);
              else if (LepCand_DecayMode[tau1_index]==10) tfr1_QCD*=h_tau1_nt_dm10->GetBinContent(3);
              else if (LepCand_DecayMode[tau1_index]==11) tfr1_QCD*=h_tau1_nt_dm11->GetBinContent(3);
           }
	   float wfr1=tfr1_QCD;

           float tpt2=my_tau2.Pt();
           if (tpt2>300) tpt2=299;
           float tfr2_QCD=0.1;
           if (LepCand_DecayMode[tau2_index]==0) tfr2_QCD=TMath::Min(1.0,fit_taufr_QCD2_dm0->Eval(tpt2));
           else if (LepCand_DecayMode[tau2_index]==1) tfr2_QCD=TMath::Min(1.0,fit_taufr_QCD2_dm1->Eval(tpt2));
           else if (LepCand_DecayMode[tau2_index]==10) tfr2_QCD=TMath::Min(1.0,fit_taufr_QCD2_dm10->Eval(tpt2));
           else if (LepCand_DecayMode[tau2_index]==11) tfr2_QCD=TMath::Min(1.0,fit_taufr_QCD2_dm11->Eval(tpt2));
           if (ntracks==0){
              if (LepCand_DecayMode[tau2_index]==0) tfr2_QCD*=h_tau2_nt_dm0->GetBinContent(2);
              else if (LepCand_DecayMode[tau2_index]==1) tfr2_QCD*=h_tau2_nt_dm1->GetBinContent(2);
              else if (LepCand_DecayMode[tau2_index]==10) tfr2_QCD*=h_tau2_nt_dm10->GetBinContent(2);
              else if (LepCand_DecayMode[tau2_index]==11) tfr2_QCD*=h_tau2_nt_dm11->GetBinContent(2);
           }
           else if (ntracks==1){
              if (LepCand_DecayMode[tau2_index]==0) tfr2_QCD*=h_tau2_nt_dm0->GetBinContent(3);
              else if (LepCand_DecayMode[tau2_index]==1) tfr2_QCD*=h_tau2_nt_dm1->GetBinContent(3);
              else if (LepCand_DecayMode[tau2_index]==10) tfr2_QCD*=h_tau2_nt_dm10->GetBinContent(3);
              else if (LepCand_DecayMode[tau2_index]==11) tfr2_QCD*=h_tau2_nt_dm11->GetBinContent(3);
           }
           float wfr2=tfr2_QCD;

           if (is_OS and is_PF and is_real){
             float w_noniso=weight*aweight*weight2*wfr2;
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
           if (is_OS and is_FP and is_real){
             float w_noniso=weight*aweight*weight2*wfr1;
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
           if (is_OS and is_FF and is_real){
             float w_noniso=weight*aweight*weight2*wfr1*wfr2*(-1.0);
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
	     //tau2
             //if (is_PF){
             if (is_FF){
                if (LepCand_DecayMode[tau2_index]==0){ h_tau2FR_QCD_dm0_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tau2FRnt_QCD_dm0_VVVL->Fill(ntracks,w_noniso); h_tau2FRnt_QCD_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau2_index]==1){ h_tau2FR_QCD_dm1_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tau2FRnt_QCD_dm1_VVVL->Fill(ntracks,w_noniso); h_tau2FRnt_QCD_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau2_index]==10){ h_tau2FR_QCD_dm10_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tau2FRnt_QCD_dm10_VVVL->Fill(ntracks,w_noniso); h_tau2FRnt_QCD_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tau2FR_QCD_dm11_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tau2FRnt_QCD_dm11_VVVL->Fill(ntracks,w_noniso); h_tau2FRnt_QCD_dm11_VVVL->Fill(-1,w_noniso);}
             }
             //if (is_isolated){
             if (is_FP){
                if (LepCand_DecayMode[tau2_index]==0){ h_tau2FR_QCD_dm0_M->Fill(my_tau2.Pt(),w_iso); h_tau2FRnt_QCD_dm0_M->Fill(ntracks,w_iso); h_tau2FRnt_QCD_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau2_index]==1){ h_tau2FR_QCD_dm1_M->Fill(my_tau2.Pt(),w_iso); h_tau2FRnt_QCD_dm1_M->Fill(ntracks,w_iso); h_tau2FRnt_QCD_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau2_index]==10){ h_tau2FR_QCD_dm10_M->Fill(my_tau2.Pt(),w_iso); h_tau2FRnt_QCD_dm10_M->Fill(ntracks,w_iso); h_tau2FRnt_QCD_dm10_M->Fill(-1,w_iso);}
                else{ h_tau2FR_QCD_dm11_M->Fill(my_tau2.Pt(),w_iso); h_tau2FRnt_QCD_dm11_M->Fill(ntracks,w_iso); h_tau2FRnt_QCD_dm11_M->Fill(-1,w_iso);}
             }

	     // tau 1
             //if (is_FP){
             if (is_FF){
                if (LepCand_DecayMode[tau1_index]==0){ h_tau1FR_QCD_dm0_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tau1FRnt_QCD_dm0_VVVL->Fill(ntracks,w_noniso); h_tau1FRnt_QCD_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau1_index]==1){ h_tau1FR_QCD_dm1_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tau1FRnt_QCD_dm1_VVVL->Fill(ntracks,w_noniso); h_tau1FRnt_QCD_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau1_index]==10){ h_tau1FR_QCD_dm10_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tau1FRnt_QCD_dm10_VVVL->Fill(ntracks,w_noniso); h_tau1FRnt_QCD_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tau1FR_QCD_dm11_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tau1FRnt_QCD_dm11_VVVL->Fill(ntracks,w_noniso); h_tau1FRnt_QCD_dm11_VVVL->Fill(-1,w_noniso);}
             }
             //if (is_isolated){
             if (is_PF){
                if (LepCand_DecayMode[tau1_index]==0){ h_tau1FR_QCD_dm0_M->Fill(my_tau1.Pt(),w_iso); h_tau1FRnt_QCD_dm0_M->Fill(ntracks,w_iso); h_tau1FRnt_QCD_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau1_index]==1){ h_tau1FR_QCD_dm1_M->Fill(my_tau1.Pt(),w_iso); h_tau1FRnt_QCD_dm1_M->Fill(ntracks,w_iso); h_tau1FRnt_QCD_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau1_index]==10){ h_tau1FR_QCD_dm10_M->Fill(my_tau1.Pt(),w_iso); h_tau1FRnt_QCD_dm10_M->Fill(ntracks,w_iso); h_tau1FRnt_QCD_dm10_M->Fill(-1,w_iso);}
                else{ h_tau1FR_QCD_dm11_M->Fill(my_tau1.Pt(),w_iso); h_tau1FRnt_QCD_dm11_M->Fill(ntracks,w_iso); h_tau1FRnt_QCD_dm11_M->Fill(-1,w_iso);}
             }

	     // combined
	     if (is_FF){
                if (LepCand_DecayMode[tau2_index]==0){ h_tauFR_QCD_dm0_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau2_index]==1){ h_tauFR_QCD_dm1_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau2_index]==10){ h_tauFR_QCD_dm10_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tauFR_QCD_dm11_VVVL->Fill(my_tau2.Pt(),w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(-1,w_noniso);}
	     }
	     if (is_FP){
                if (LepCand_DecayMode[tau2_index]==0){ h_tauFR_QCD_dm0_M->Fill(my_tau2.Pt(),w_iso); h_tauFRnt_QCD_dm0_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau2_index]==1){ h_tauFR_QCD_dm1_M->Fill(my_tau2.Pt(),w_iso); h_tauFRnt_QCD_dm1_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau2_index]==10){ h_tauFR_QCD_dm10_M->Fill(my_tau2.Pt(),w_iso); h_tauFRnt_QCD_dm10_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm10_M->Fill(-1,w_iso);}
                else{ h_tauFR_QCD_dm11_M->Fill(my_tau2.Pt(),w_iso); h_tauFRnt_QCD_dm11_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm11_M->Fill(-1,w_iso);}
             }
             if (is_FF){
                if (LepCand_DecayMode[tau1_index]==0){ h_tauFR_QCD_dm0_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm0_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau1_index]==1){ h_tauFR_QCD_dm1_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm1_VVVL->Fill(-1,w_noniso);}
                else if (LepCand_DecayMode[tau1_index]==10){ h_tauFR_QCD_dm10_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm10_VVVL->Fill(-1,w_noniso);}
                else{ h_tauFR_QCD_dm11_VVVL->Fill(my_tau1.Pt(),w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(ntracks,w_noniso); h_tauFRnt_QCD_dm11_VVVL->Fill(-1,w_noniso);}
             }
             if (is_PF){
                if (LepCand_DecayMode[tau1_index]==0){ h_tauFR_QCD_dm0_M->Fill(my_tau1.Pt(),w_iso); h_tauFRnt_QCD_dm0_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm0_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau1_index]==1){ h_tauFR_QCD_dm1_M->Fill(my_tau1.Pt(),w_iso); h_tauFRnt_QCD_dm1_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm1_M->Fill(-1,w_iso);}
                else if (LepCand_DecayMode[tau1_index]==10){ h_tauFR_QCD_dm10_M->Fill(my_tau1.Pt(),w_iso); h_tauFRnt_QCD_dm10_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm10_M->Fill(-1,w_iso);}
                else{ h_tauFR_QCD_dm11_M->Fill(my_tau1.Pt(),w_iso); h_tauFRnt_QCD_dm11_M->Fill(ntracks,w_iso); h_tauFRnt_QCD_dm11_M->Fill(-1,w_iso);}
             }

	   }

           
	}

    } // end of loop over events
    TFile *fout = TFile::Open(output.c_str(), "RECREATE");
    fout->cd();

    tree2->Write();

    h_dz_beforetrigger->Write();
    h_dz_aftertrigger->Write();
    h_logdz_beforetrigger->Write();
    h_logdz_aftertrigger->Write();

    h_tauFR_QCD_dm0_M->Write();
    h_tauFR_QCD_dm1_M->Write();
    h_tauFR_QCD_dm10_M->Write();
    h_tauFR_QCD_dm11_M->Write();
    h_tauFR_QCD_dm0_VVVL->Write();
    h_tauFR_QCD_dm1_VVVL->Write();
    h_tauFR_QCD_dm10_VVVL->Write();
    h_tauFR_QCD_dm11_VVVL->Write();

    h_tauFRnt_QCD_dm0_M->Write();
    h_tauFRnt_QCD_dm1_M->Write();
    h_tauFRnt_QCD_dm10_M->Write();
    h_tauFRnt_QCD_dm11_M->Write();
    h_tauFRnt_QCD_dm0_VVVL->Write();
    h_tauFRnt_QCD_dm1_VVVL->Write();
    h_tauFRnt_QCD_dm10_VVVL->Write();
    h_tauFRnt_QCD_dm11_VVVL->Write();


    h_tau1FR_QCD_dm0_M->Write();
    h_tau1FR_QCD_dm1_M->Write();
    h_tau1FR_QCD_dm10_M->Write();
    h_tau1FR_QCD_dm11_M->Write();
    h_tau1FR_QCD_dm0_VVVL->Write();
    h_tau1FR_QCD_dm1_VVVL->Write();
    h_tau1FR_QCD_dm10_VVVL->Write();
    h_tau1FR_QCD_dm11_VVVL->Write();

    h_tau1FRnt_QCD_dm0_M->Write();
    h_tau1FRnt_QCD_dm1_M->Write();
    h_tau1FRnt_QCD_dm10_M->Write();
    h_tau1FRnt_QCD_dm11_M->Write();
    h_tau1FRnt_QCD_dm0_VVVL->Write();
    h_tau1FRnt_QCD_dm1_VVVL->Write();
    h_tau1FRnt_QCD_dm10_VVVL->Write();
    h_tau1FRnt_QCD_dm11_VVVL->Write();



    h_tau2FR_QCD_dm0_M->Write();
    h_tau2FR_QCD_dm1_M->Write();
    h_tau2FR_QCD_dm10_M->Write();
    h_tau2FR_QCD_dm11_M->Write();
    h_tau2FR_QCD_dm0_VVVL->Write();
    h_tau2FR_QCD_dm1_VVVL->Write();
    h_tau2FR_QCD_dm10_VVVL->Write();
    h_tau2FR_QCD_dm11_VVVL->Write();

    h_tau2FRnt_QCD_dm0_M->Write();
    h_tau2FRnt_QCD_dm1_M->Write();
    h_tau2FRnt_QCD_dm10_M->Write();
    h_tau2FRnt_QCD_dm11_M->Write();
    h_tau2FRnt_QCD_dm0_VVVL->Write();
    h_tau2FRnt_QCD_dm1_VVVL->Write();
    h_tau2FRnt_QCD_dm10_VVVL->Write();
    h_tau2FRnt_QCD_dm11_VVVL->Write();

cout<<h0[0]->Integral()<<endl;
    bool isMC=(name!="data_obs");
    WriteHistToFileTauTau(fout, h0, name, "tt_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h0_anti, name, "tt_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h1, name, "tt_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h1_anti, name, "tt_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h2, name, "tt_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h2_anti, name, "tt_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h3, name, "tt_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h3_anti, name, "tt_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h4, name, "tt_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h4_anti, name, "tt_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h5, name, "tt_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h5_anti, name, "tt_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h6, name, "tt_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h6_anti, name, "tt_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h7, name, "tt_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h7_anti, name, "tt_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h8, name, "tt_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    WriteHistToFileTauTau(fout, h8_anti, name, "tt_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);

    if (sample=="DY"){
       WriteHistToFileTauTau(fout, h0R, name, "ttR_0", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h0R_anti, name, "ttR_0_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h1R, name, "ttR_1", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h1R_anti, name, "ttR_1_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h2R, name, "ttR_2", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h2R_anti, name, "ttR_2_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h3R, name, "ttR_3", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h3R_anti, name, "ttR_3_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h4R, name, "ttR_4", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h4R_anti, name, "ttR_4_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h5R, name, "ttR_5", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h5R_anti, name, "ttR_5_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h6R, name, "ttR_6", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h6R_anti, name, "ttR_6_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h7R, name, "ttR_7", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h7R_anti, name, "ttR_7_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h8R, name, "ttR_8", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
       WriteHistToFileTauTau(fout, h8R_anti, name, "ttR_8_anti", uncertainties, fake_uncertainties, isMC, nbhist, nbhist_offset, isMC);
    }


    fout->Close();
} 


