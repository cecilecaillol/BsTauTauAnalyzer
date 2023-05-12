#include "GetPFtrk.h"

/*ROOT::RVec<float> Computedz_mu(Vec_t Muontrk_dz, float mudz) {
    auto mod = [mudz]( float dz) { return fabs(dz-mudz); };
    ROOT::RVec<float>  dz_mu = Map(Muontrk_dz,mod);
    return dz_mu;
}

ROOT::RVec<float> Computediffpt_mu(Vec_t Muontrk_pt, float mupt) {
    auto mod = [mupt]( float pt) { return fabs(pt-mupt)/mupt; };
    ROOT::RVec<float> diffpt_mu = Map(Muontrk_pt,mod);
    return diffpt_mu;
}

ROOT::RVec<float> ComputedeltaR_mu(Vec_t Muontrk_pt, Vec_t Muontrk_eta,Vec_t Muontrk_phi, TLorentzVector my_mu) {
    auto mod = [my_mu](float pt, float eta, float phi){
        TLorentzVector Muontrk;
        Muontrk.SetPtEtaPhiM(pt,eta,phi,0);
        return my_mu.DeltaR(Muontrk);
    };
    ROOT::RVec<float> deltaR_mu = Map(Muontrk_pt,Muontrk_eta,Muontrk_phi,mod);
    return deltaR_mu;
}

ROOT::RVec<float> Compute_ditaudz(Vec_t trk_dz, float PV_z, float zvtxll){
    auto mod = [PV_z, zvtxll](float dz){
        float ditaudz = dz+PV_z-zvtxll;
        return fabs(ditaudz);
    };
    ROOT::RVec<float> ditaudz = Map(trk_dz,mod);
    return ditaudz;
}
*/
ROOT::RVec<float> Computedz_lep(Vec_t PF_dz, float lepdz) {
    auto mod = [lepdz]( float dz) { 
        float deltadz = 0;
        if (lepdz==-99){
            deltadz = 99;
        }
        else {
            deltadz = fabs(dz-lepdz);
        }
        return deltadz; };
    ROOT::RVec<float>  dz_mu = Map(PF_dz,mod);
    return dz_mu;
}

ROOT::RVec<float> Computediffpt_lep(Vec_t PF_pt, float leppt) {
    auto mod = [leppt]( float pt) { 
        float ptdiff = 0;
        if (leppt==-99){
            ptdiff= 99;
        }
        else {
            ptdiff = fabs(pt-leppt)/leppt;
        }

        return ptdiff; };
    ROOT::RVec<float> diffpt_lep = Map(PF_pt,mod);
    return diffpt_lep;
}

ROOT::RVec<float> ComputedeltaR_lep(Vec_t PF_eta,Vec_t PF_phi, float lep_eta, float lep_phi) {

    auto mod = [lep_eta,lep_phi](float eta, float phi){
        float deltaR=0;
        if (lep_eta==-99){
            deltaR=99;
        }
        else{
            float dphi = TVector2::Phi_mpi_pi(lep_phi-phi);
            deltaR = sqrt((lep_eta - eta) * (lep_eta - eta) + dphi * dphi);
        }
        return deltaR;
    };
    ROOT::RVec<float> deltaR_lep = Map(PF_eta,PF_phi,mod);
    return deltaR_lep;
}

ROOT::RVec<float> Compute_ditaudz(Vec_t trk_dz, float PV_z, float zvtxll){
    auto mod = [PV_z, zvtxll](float dz){
        float ditaudz = dz+PV_z-zvtxll;
        return fabs(ditaudz);
    };
    ROOT::RVec<float> ditaudz = Map(trk_dz,mod);
    return ditaudz;
}

/*ROOT::RVec<int> GetTautrk(float Tautrk_mintau1dz,float Tautrk_mintau2dz,float Tautrk_mintau3dz,Vec_t Tautrk_tau1dz,Vec_t Tautrk_tau2dz,Vec_t Tautrk_tau3dz){
    auto mode = [Tautrk_mintau1dz,Tautrk_mintau2dz,Tautrk_mintau3dz](float tau1dz,float tau2dz, float tau3dz ){
        bool istautrk=false; 
        if (Tautrk_mintau1dz<1){
            if (tau1dz==Tautrk_mintau1dz){
                istautrk=true;
            }
        }
        if (Tautrk_mintau2dz<1){
            if (tau2dz==Tautrk_mintau2dz){
                istautrk=true;
            }
        }
        if (Tautrk_mintau3dz<1){
            if (tau3dz==Tautrk_mintau3dz){
                istautrk=true;
            }
        }
        if (istautrk){
            return 1;
        }
        else{
            return 0;
        }
    };

    ROOT::RVec<int> CutTautrk = Map(Tautrk_tau1dz,Tautrk_tau2dz,Tautrk_tau3dz,mode);
    return CutTautrk;
}
*/

ROOT::RVec<bool> Gettrkmatch(Vec_t Track_lepptdiff, Vec_t Track_lepdeltaR ){
    auto mod = [](float PF_lepptdiff, float PF_lepdeltaR){
        bool match = false;
        if (PF_lepptdiff<0.1 && PF_lepdeltaR<0.002){
            match = true;
        }
        return match;
    };
    ROOT::RVec<bool> trkmatch = Map(Track_lepptdiff,Track_lepdeltaR,mod);
    return trkmatch;
}


ROOT::RVec<int> Getntrkcut_mutau(Vec_t ChargedPFCandidates_pt,Vec_t ChargedPFCandidates_eta,Vec_t ChargedPFCandidates_phi,Vec_t ChargedPFCandidates_dz,\
    Vec_t FinalMuontrk_pt, Vec_t FinalMuontrk_eta, Vec_t FinalMuontrk_phi, Vec_t FinalMuontrk_dz,\
    Vec_t FinalTautrk_pt, Vec_t FinalTautrk_eta, Vec_t FinalTautrk_phi, Vec_t FinalTautrk_dz){
    auto mod = [FinalMuontrk_pt,FinalMuontrk_eta,FinalMuontrk_phi,FinalMuontrk_dz,\
        FinalTautrk_pt,FinalTautrk_eta,FinalTautrk_phi,FinalTautrk_dz](float PF_pt, float PF_eta, float PF_phi, float PF_dz){
        bool ismuontrk=false;
        bool istautrk=false;
        if (FinalMuontrk_pt.size()>0){
            for (unsigned int i =0; i<FinalMuontrk_pt.size();i++ ){
                if (PF_pt==FinalMuontrk_pt[i] && PF_eta==FinalMuontrk_eta[i] && PF_phi==FinalMuontrk_phi[i] && PF_dz==FinalMuontrk_dz[i])
                ismuontrk=true;
            }
        }
        
        if (FinalTautrk_pt.size()>0){
            for (unsigned int i =0; i<FinalTautrk_pt.size();i++ ){
                if (PF_pt==FinalTautrk_pt[i] && PF_eta==FinalTautrk_eta[i] && PF_phi==FinalTautrk_phi[i] && PF_dz==FinalTautrk_dz[i])
                istautrk=true;
            }
        }
        if (ismuontrk || istautrk){
            return 0;
        }
        else{
            return 1;
        }
    };
    ROOT::RVec<int> cut_excludemutau = Map(ChargedPFCandidates_pt,ChargedPFCandidates_eta,ChargedPFCandidates_phi,ChargedPFCandidates_dz,mod);
    return cut_excludemutau;
}


ROOT::RVec<int> Getntrkcut_tautau(Vec_t ChargedPFCandidates_pt,Vec_t ChargedPFCandidates_eta,Vec_t ChargedPFCandidates_phi,Vec_t ChargedPFCandidates_dz,\
    Vec_t FinalTautrk_pt, Vec_t FinalTautrk_eta, Vec_t FinalTautrk_phi, Vec_t FinalTautrk_dz){
    auto mod = [FinalTautrk_pt,FinalTautrk_eta,FinalTautrk_phi,FinalTautrk_dz](float PF_pt, float PF_eta, float PF_phi, float PF_dz){
        bool istautrk=false;
        if (FinalTautrk_pt.size()>0){
            for (unsigned int i =0; i<FinalTautrk_pt.size();i++ ){
                if (PF_pt==FinalTautrk_pt[i] && PF_eta==FinalTautrk_eta[i] && PF_phi==FinalTautrk_phi[i] && PF_dz==FinalTautrk_dz[i])
                istautrk=true;
            }
        }
        if (istautrk){
            return 0;
        }
        else{
            return 1;
        }
    };
    ROOT::RVec<int> cut_excludetautau = Map(ChargedPFCandidates_pt,ChargedPFCandidates_eta,ChargedPFCandidates_phi,ChargedPFCandidates_dz,mod);
    return cut_excludetautau;
    }








