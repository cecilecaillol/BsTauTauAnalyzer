#include "Sys.h"


float Gettauidsysweight_dm(int decaymode, int taudecaymode, float taugen, float tauidsf, float tauidsf_change){
    float sysweight = 1.0;
    if (taugen==5 && taudecaymode==decaymode){
        sysweight = tauidsf_change/tauidsf;
    }
    return sysweight;
}
float Gettauidsysweight( float taugen, float tauidsf, float tauidsf_change){
    float sysweight = 1.0;
    if (taugen==5){
        sysweight = tauidsf_change/tauidsf;
    }
    return sysweight;
}

float Getpusysweight( float puWeight, float puWeight_change,  float npvs_weight, float npvs_weight_change){
    float pusysweight=1.0;
    pusysweight = puWeight_change*npvs_weight_change/(puWeight*npvs_weight);
    return pusysweight;
}

float Getditautrigweight(float tautrigweight, float tautrigweight_change){
    float ditautrigweight=1.0;
    ditautrigweight = tautrigweight_change/tautrigweight;
    return ditautrigweight;
}

TLorentzVector Gettauessys(int decaymode, int taudecaymode, float taugen, float taues, float taues_change, TLorentzVector my_tau){
    TLorentzVector my_newtau = my_tau;
    if (taugen==5){
        if ((decaymode==1011 && (taudecaymode==10 || taudecaymode==11))|| (decaymode!=1011 && taudecaymode==decaymode) ){
            my_newtau*=(taues_change/taues);
        }
    }
    return my_newtau;
}

float Gettauantimusysweight( bool barrel, float taugen, float tau_antimusf, float tau_antimusf_change, float taueta){
    float tauantimusysweight=1.0;
    if ((barrel && taueta<1.5) || (!barrel && taueta>=1.5)){
        if (taugen==2 || taugen==4){
            tauantimusysweight = tau_antimusf_change/tau_antimusf;
        }
    }
    return tauantimusysweight;
}

/*float Gettauantielesysweight( bool up, bool barrel, Vec_t LepCand_gen, Vec_t LepCand_antielesf, Vec_t LepCand_antielesf_up, Vec_t LepCand_antielesf_down, int tauindex, float taueta){
    float tauantielesysweight=1.0;

    if ((barrel && taueta<1.5) || (!barrel && taueta>=1.5)){
        if (LepCand_gen[tauindex]==2 or LepCand_gen[tauindex]==4){
            if (up){
                tauantielesysweight = LepCand_antielesf_up[tauindex] / LepCand_antielesf[tauindex];
            }
            else{
                tauantielesysweight = LepCand_antielesf_down[tauindex] / LepCand_antielesf[tauindex];
            }

        }
    }
    return tauantielesysweight;
}


TLorentzVector Gettaufessys(bool up, Vec_t LepCand_DecayMode, Vec_t LepCand_gen,Vec_t LepCand_fes, Vec_t LepCand_fes_down, Vec_t LepCand_fes_up, int tauindex, TLorentzVector my_tau, int decaymode){
    //decaymode: 0, 1 
    TLorentzVector my_newtau = my_tau;

    if (LepCand_gen[tauindex]==1 || LepCand_gen[tauindex]==3 ){
        if ( LepCand_DecayMode[tauindex]==decaymode ){
            if (up){
                my_newtau*=LepCand_fes_up[tauindex]/LepCand_fes[tauindex];
            }
            else {
                my_newtau*=LepCand_fes_down[tauindex]/LepCand_fes[tauindex];
            }

        }
    }

    return my_newtau;
}
*/

float Getmutautrgweight(bool isMuonTauTrigger, float tautrigsf, float tautrigsf_change){
    float mutautrgweight=1.0;
    if (isMuonTauTrigger){
        mutautrgweight = tautrigsf_change/tautrigsf;
    }
    return mutautrgweight;

}

float Getsinglemutrgweight(bool isSingleMuonTrigger, float weight){
    float singlemutrgweight=1.0;
    if (isSingleMuonTrigger){
        singlemutrgweight = weight;
    }
    return singlemutrgweight;
}








