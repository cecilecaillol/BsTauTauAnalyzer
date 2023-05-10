#include "basic_sel.h"

//For mutau final states, get mutau index
ROOT::RVec<int> Getmutauindex(int nLepCand, ROOT::VecOps::RVec<int> &LepCand_id ,ROOT::VecOps::RVec<float> &LepCand_dz){
    int mu_index = 0;
    int tau_index = 0;
    //mu id ==13, tau id ==15 , The minimum id corresponding to minimum Lepton id
    mu_index = ArgMin(LepCand_id);
    if (nLepCand==2){
        tau_index = ArgMax(LepCand_id);
    }
    else{
        //Choose the most close tau as our tau
        ROOT::VecOps::RVec<float> abs_diff_mudz = abs(LepCand_dz-LepCand_dz[mu_index]);
        tau_index = std::distance(abs_diff_mudz.begin(),find(abs_diff_mudz.begin(),abs_diff_mudz.end(),Sort(abs_diff_mudz)[1]));
    }
    ROOT::RVec<int> mutauindex = {mu_index, tau_index};
    return mutauindex;

}

//For tautau final states get tautau index
ROOT::RVec<int> Gettautauindex(int nLepCand, ROOT::VecOps::RVec<float> &LepCand_dz){
    int tau1index =0 ;
    int tau2index = 0;
    if (nLepCand==2){
        tau1index = 0;
        tau2index = 1;

    }
    else{
        ROOT::VecOps::RVec<float> LepCand_dz_sort = Sort(LepCand_dz);
        float tau1dz = LepCand_dz_sort[0];
        float tau2dz = LepCand_dz_sort[1];
        float dzdiff_min = tau2dz-tau1dz;
        for (int i =2; i< int(LepCand_dz.size());i++){
            if ((LepCand_dz_sort[i] - LepCand_dz_sort[i-1])<dzdiff_min){
                tau1dz = LepCand_dz_sort[i-1];
                tau2dz = LepCand_dz_sort[i];
                dzdiff_min = tau2dz-tau1dz;
            }
        }
        tau1index = std::distance(LepCand_dz.begin(),find(LepCand_dz.begin(),LepCand_dz.end(),tau1dz));
        tau2index = std::distance(LepCand_dz.begin(),find(LepCand_dz.begin(),LepCand_dz.end(),tau2dz));
        if (tau1index>tau2index){
            int c = tau1index;
            tau1index = tau2index;
            tau2index = c;
        }
    }
    ROOT::RVec<int> tautauindex = {tau1index, tau2index};
    return tautauindex;
}

// Get tau Vector for MC with energy scale factor
TLorentzVector GetLepVector(int Lepindex, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi,ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_taues, ROOT::VecOps::RVec<Float_t> &LepCand_fes){
    TLorentzVector my_lep;
    my_lep.SetPtEtaPhiM(LepCand_pt[Lepindex],LepCand_eta[Lepindex],LepCand_phi[Lepindex],0);

    if (LepCand_gen[Lepindex]==5){
        my_lep=my_lep*LepCand_taues[Lepindex];
    }
    if (LepCand_gen[Lepindex]==1 or LepCand_gen[Lepindex]==3){
        my_lep=my_lep*LepCand_fes[Lepindex];
    }

    return my_lep;
}

//Get mu vector and tau vector for data
TLorentzVector GetLepVector(int Lepindex, ROOT::VecOps::RVec<Float_t> &LepCand_pt, ROOT::VecOps::RVec<Float_t> &LepCand_eta,ROOT::VecOps::RVec<Float_t> &LepCand_phi){
    TLorentzVector my_lep;
    my_lep.SetPtEtaPhiM(LepCand_pt[Lepindex],LepCand_eta[Lepindex],LepCand_phi[Lepindex],0);
    return my_lep;
}


//Get xsweight of WJets
float luminosity = 59830.0;
float nnlo=1.162;
float xsW=52940.0;
float xsW1=8104.0;
float xsW2=2793.0;
float xsW3=992.5;
float xsW4=544.3;

float ngenW=2162743.0/0.0305;
float ngenW1=2315654.0/0.0523;
float ngenW2=1153856.0/0.0928;
float ngenW3=1450912.0/0.132;
float ngenW4=1509958.0/0.184;

float LW=ngenW/xsW;
float LW1=ngenW1/xsW1;
float LW2=ngenW2/xsW2;
float LW3=ngenW3/xsW3;
float LW4=ngenW4/xsW4;

float Getxsweight_W(float LHE_Njets){
    float weight = 0;
    if (LHE_Njets==0) weight=luminosity*nnlo/LW;
    else if (LHE_Njets==1) weight=luminosity*nnlo/(LW+LW1);
    else if (LHE_Njets==2) weight=luminosity*nnlo/(LW+LW2);
    else if (LHE_Njets==3) weight=luminosity*nnlo/(LW+LW3);
    else if (LHE_Njets==4) weight=luminosity*nnlo/(LW+LW4);
    return weight;
}


//Get SFweight for mutau final states, mu SF for singleMuon trigger
TFile *f_reco = new TFile("/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scalefactors/Efficiencies_muon_reco.root","READ");
TFile *f_muonID= new TFile("/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root","read");
TFile *f_muonIso= new TFile("/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root","read");
TFile *f_muonTrg= new TFile("/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scalefactors/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root","read");
TH1F *h_muonRecoeff = (TH1F*)f_reco->Get("Efficiencies_muon_reco_abseta");
TH1F *h_muonRecoeff_stat = (TH1F*)f_reco->Get("Efficiencies_muon_reco_abseta_stat");
TH1F *h_muonRecoeff_syst = (TH1F*)f_reco->Get("Efficiencies_muon_reco_abseta_syst");

TH1F *h_muonIsoSF= (TH1F*)f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt");
TH1F *h_muonIsoSF_stat= (TH1F*)f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt_stat");
TH1F *h_muonIsoSF_syst= (TH1F*)f_muonIso->Get("NUM_TightRelIso_DEN_MediumID_abseta_pt_syst");

TH1F *h_muonIDSF= (TH1F*)f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt");
TH1F *h_muonIDSF_stat= (TH1F*)f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_stat");
TH1F *h_muonIDSF_syst= (TH1F*)f_muonID->Get("NUM_MediumID_DEN_TrackerMuons_abseta_pt_syst");

TH1F *h_muonTrgSF= (TH1F*)f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt");
TH1F *h_muonTrgSF_stat= (TH1F*)f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt_stat");
TH1F *h_muonTrgSF_syst= (TH1F*)f_muonTrg->Get("NUM_IsoMu24_DEN_CutBasedIdMedium_and_PFIsoMedium_abseta_pt_syst");

//muscale factor for mutau cross trigger
TFile *f_HLTMu20Tau27 = new TFile("/afs/cern.ch/user/x/xuqin/work/taug-2/taug-2wkdir/CMSSW_10_6_27/src/MyNanoAnalyzer/NtupleAnalyzerXuelong/scalefactors/sf_mu_2018_HLTMu20Tau27.root","READ");
TH2F *h_musf_HLTMu20Tau27 = (TH2F*) f_HLTMu20Tau27->Get("SF2D");// xaxis: mupt, yaxis: fabs(mueta)


float GetMuonrecoSF(TLorentzVector my_mu){
    float recosf = h_muonRecoeff->GetBinContent(h_muonRecoeff->GetXaxis()->FindBin(abs(my_mu.Eta())));
    return recosf;
}
float GetMuonrecoSF_stat(TLorentzVector my_mu){
    float recosf_stat = h_muonRecoeff_stat->GetBinContent(h_muonRecoeff_stat->GetXaxis()->FindBin(abs(my_mu.Eta())));
    return recosf_stat;
}
float GetMuonrecoSF_syst(TLorentzVector my_mu){
    float recosf_syst = h_muonRecoeff_syst->GetBinContent(h_muonRecoeff_syst->GetXaxis()->FindBin(abs(my_mu.Eta())));
    return recosf_syst;
}

float GetMuonIsoSF(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float isosf= h_muonIsoSF->GetBinContent(h_muonIsoSF->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIsoSF->GetYaxis()->FindBin(mu_pt));
    return isosf;
}

float GetMuonIsoSF_stat(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float isosf_stat = h_muonIsoSF_stat->GetBinError(h_muonIsoSF_stat->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIsoSF_stat->GetYaxis()->FindBin(mu_pt));
    return isosf_stat;
}

float GetMuonIsoSF_syst(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float isosf_syst = h_muonIsoSF_syst->GetBinError(h_muonIsoSF_syst->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIsoSF_syst->GetYaxis()->FindBin(mu_pt));
    return isosf_syst;
}


float GetMuonIDSF(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float idsf = h_muonIDSF->GetBinContent(h_muonIDSF->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIDSF->GetYaxis()->FindBin(mu_pt));
    return idsf;
}

float GetMuonIDSF_stat(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float idsf_stat = h_muonIDSF_stat->GetBinError(h_muonIDSF_stat->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIDSF_stat->GetYaxis()->FindBin(mu_pt));
    return idsf_stat;
}

float GetMuonIDSF_syst(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float idsf_syst = h_muonIDSF_syst->GetBinError(h_muonIDSF_syst->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonIDSF_syst->GetYaxis()->FindBin(mu_pt));
    return idsf_syst;
}


float GetMuonTriggerSF(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float trgsf = h_muonTrgSF->GetBinContent(h_muonTrgSF->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonTrgSF->GetYaxis()->FindBin(mu_pt));
    return trgsf;
}


float GetMuonTriggerSF_stat(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float trgsf_stat = h_muonTrgSF_stat->GetBinError(h_muonTrgSF_stat->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonTrgSF_stat->GetYaxis()->FindBin(mu_pt));
    return trgsf_stat;
}

float GetMuonTriggerSF_syst(TLorentzVector my_mu){
    float mu_pt=my_mu.Pt();
    if (mu_pt>120) mu_pt=119;
    if (mu_pt<15) mu_pt=16;
    float trgsf_syst = h_muonTrgSF_syst->GetBinError(h_muonTrgSF_syst->GetXaxis()->FindBin(abs(my_mu.Eta())),h_muonTrgSF_syst->GetYaxis()->FindBin(mu_pt));
    return trgsf_syst;
}

float GetMuonSF_HLTMu20Tau27(float mupt,float mueta){
    float musf = h_musf_HLTMu20Tau27->GetBinContent(h_musf_HLTMu20Tau27->GetXaxis()->FindBin(mupt),h_musf_HLTMu20Tau27->GetYaxis()->FindBin(fabs(mueta)));
    return musf;
}

float GetSFweight_mutau(float murecosf, float muisosf,float muidsf, float mutrgsf,float musf_HLTMu20Tau27, float puweight, int tauindex, bool isSingleMuonTrigger, bool isMuonTauTrigger,  ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_tauidMsf, ROOT::VecOps::RVec<Float_t> &LepCand_antielesf,ROOT::VecOps::RVec<Float_t> &LepCand_antimusf,ROOT::VecOps::RVec<Float_t> &LepCand_tautriggersf){
    float aweight=1.0;
    aweight=aweight*puweight;
    if (LepCand_gen[tauindex]==5) aweight=aweight*LepCand_tauidMsf[tauindex];
    if (LepCand_gen[tauindex]==1 or LepCand_gen[tauindex]==3) aweight=aweight*LepCand_antielesf[tauindex];
    if (LepCand_gen[tauindex]==2 or LepCand_gen[tauindex]==4) aweight=aweight*LepCand_antimusf[tauindex];
    aweight = aweight*murecosf*muidsf*muisosf;
    if (isSingleMuonTrigger){
        aweight = aweight*mutrgsf;
    }
    else if (isMuonTauTrigger){
        aweight = aweight*musf_HLTMu20Tau27*LepCand_tautriggersf[tauindex];
    }
    return aweight;
}


//Get SFweight for tautau final states
float GetSFweight_tautau(float puweight, int tau1index, int tau2index, ROOT::VecOps::RVec<Float_t> &LepCand_gen, ROOT::VecOps::RVec<Float_t> &LepCand_tauidMsfDM, ROOT::VecOps::RVec<Float_t> &LepCand_antielesf,ROOT::VecOps::RVec<Float_t> &LepCand_antimusf,ROOT::VecOps::RVec<Float_t> &LepCand_tautriggersf){
    float aweight=1.0;
    aweight=aweight*puweight;
    if (LepCand_gen[tau1index]==5) aweight=aweight*LepCand_tauidMsfDM[tau1index];
    if (LepCand_gen[tau1index]==1 or LepCand_gen[tau1index]==3) aweight=aweight*LepCand_antielesf[tau1index];
    if (LepCand_gen[tau1index]==2 or LepCand_gen[tau1index]==4) aweight=aweight*LepCand_antimusf[tau1index];

    if (LepCand_gen[tau2index]==5) aweight=aweight*LepCand_tauidMsfDM[tau2index];
    if (LepCand_gen[tau2index]==1 or LepCand_gen[tau2index]==3) aweight=aweight*LepCand_antielesf[tau2index];
    if (LepCand_gen[tau2index]==2 or LepCand_gen[tau2index]==4) aweight=aweight*LepCand_antimusf[tau2index];

    float trgSF1 = LepCand_tautriggersf[tau1index];
    float trgSF2 = LepCand_tautriggersf[tau2index];
    aweight = aweight*trgSF1*trgSF2;
    return aweight;
}





bool GetisOS(ROOT::VecOps::RVec<Int_t> &LepCand_charge, int lep1index,int lep2index){
    if (LepCand_charge[lep1index]*LepCand_charge[lep2index]<0)
        return true;
    else 
        return false;


}
bool Getis_isolated(ROOT::VecOps::RVec<Int_t> &LepCand_vsjet,int tauindex){
    if (LepCand_vsjet[tauindex]>=31)
        return true;
    else
        return false;
}


float GetTransmass(TLorentzVector my_mu, float MET_pt, float MET_phi){
    float muMETdelphi = my_mu.Phi()-MET_phi;
    float mtrans = sqrt(2*my_mu.Pt()*MET_pt*(1-cos(muMETdelphi)));
    return mtrans;
}

float GetCollMass(TLorentzVector my_lep1, TLorentzVector my_lep2, float MET_pt, float MET_phi){
    float metx = MET_pt * cos(MET_phi);
    float mety = MET_pt * sin(MET_phi); 
    float m_mz_coll=0;
    float x1 = ((my_lep1.Px()*my_lep2.Py())-(my_lep1.Py()*my_lep2.Px())) / ((my_lep1.Px()*my_lep2.Py())-(my_lep1.Py()*my_lep2.Px())+(my_lep2.Py()*metx)-(my_lep2.Px()*mety));
    float x2 = ((my_lep1.Px()*my_lep2.Py())-(my_lep1.Py()*my_lep2.Px())) / ((my_lep1.Px()*my_lep2.Py())-(my_lep1.Py()*my_lep2.Px())+(my_lep1.Px()*mety)-(my_lep1.Py()*metx));
    if( (x1*x2) > 0. ){
        m_mz_coll = ((my_lep1+my_lep2).M())/(sqrt(x1*x2));
    }
    return m_mz_coll;
}

float GetAcopl(TLorentzVector my_lep1, TLorentzVector my_lep2){
    float delphi = my_lep1.DeltaPhi(my_lep2);
    float Acopl = 1 - fabs(delphi)/TMath::Pi();
    return Acopl;
}


float recovtxz1(float lep1dz,float lep2dz,float PV_z){
    float av_z = 0.5*(2*PV_z+lep1dz+lep2dz);
    return av_z;
}

float recovtxz2(TLorentzVector my_Lep1,TLorentzVector my_Lep2,float lep1dz,float lep2dz,float PV_z){
    float theta1 = my_Lep1.Theta();
    float theta2 = my_Lep2.Theta();
    float z1 = lep1dz+PV_z;
    float z2 = lep2dz+PV_z;
    float sin2t1 = sin(theta1)*sin(theta1);
    float sin2t2 = sin(theta2)*sin(theta2);
    float zvtxll  = (z1*sin2t1+z2*sin2t2)/(sin2t1+sin2t2);
    return zvtxll;
}

float recovtxz3(float lep1pt,float lep2pt,float lep1dz,float lep2dz,float PV_z){
    float ptavdz = (lep1dz*lep1pt+lep2dz*lep2dz)/(lep1pt+lep2pt);
    float vtxz = ptavdz+PV_z;
    return vtxz;
}



