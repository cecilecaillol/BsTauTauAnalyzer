#include "ApplyFR.h"



TFile *fFRw_mutau = new TFile("FRW_mutau.root","read");
TFile *fFR_mutau = new TFile("FRfit_mutau.root","read");


TH2F *WFR_allDM = (TH2F*)fFRw_mutau->Get("hWFR_mtrans_mvis_allDM");

TF1 *FRQCD_taupt_DM0 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM0_taupt");
TF1 *FRQCD_lownTrk_DM0 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM0_lownTrk");
TF1 *FRQCD_highnTrk_DM0 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM0_highnTrk");

TF1 *FRQCD_taupt_DM1 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM1_taupt");
TF1 *FRQCD_lownTrk_DM1 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM1_lownTrk");
TF1 *FRQCD_highnTrk_DM1 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM1_highnTrk");

TF1 *FRQCD_taupt_DM10 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM10_taupt");
TF1 *FRQCD_lownTrk_DM10 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM10_lownTrk");
TF1 *FRQCD_highnTrk_DM10 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM10_highnTrk");

TF1 *FRQCD_taupt_DM11 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM11_taupt");
TF1 *FRQCD_lownTrk_DM11 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM11_lownTrk");
TF1 *FRQCD_highnTrk_DM11 = (TF1*)fFR_mutau->Get("fitfunc_QCD_DM11_highnTrk");

TF1 *FRW_taupt_DM0 = (TF1*)fFR_mutau->Get("fitfunc_W_DM0_taupt");
TF1 *FRW_lownTrk_DM0 = (TF1*)fFR_mutau->Get("fitfunc_W_DM0_lownTrk");
TF1 *FRW_highnTrk_DM0 = (TF1*)fFR_mutau->Get("fitfunc_W_DM0_highnTrk");

TF1 *FRW_taupt_DM1 = (TF1*)fFR_mutau->Get("fitfunc_W_DM1_taupt");
TF1 *FRW_lownTrk_DM1 = (TF1*)fFR_mutau->Get("fitfunc_W_DM1_lownTrk");
TF1 *FRW_highnTrk_DM1 = (TF1*)fFR_mutau->Get("fitfunc_W_DM1_highnTrk");

TF1 *FRW_taupt_DM10 = (TF1*)fFR_mutau->Get("fitfunc_W_DM10_taupt");
TF1 *FRW_lownTrk_DM10 = (TF1*)fFR_mutau->Get("fitfunc_W_DM10_lownTrk");
TF1 *FRW_highnTrk_DM10 = (TF1*)fFR_mutau->Get("fitfunc_W_DM10_highnTrk");

TF1 *FRW_taupt_DM11 = (TF1*)fFR_mutau->Get("fitfunc_W_DM11_taupt");
TF1 *FRW_lownTrk_DM11 = (TF1*)fFR_mutau->Get("fitfunc_W_DM11_lownTrk");
TF1 *FRW_highnTrk_DM11 = (TF1*)fFR_mutau->Get("fitfunc_W_DM11_highnTrk");

float GetFR_mutau(int taudecaymode, float mvis, float mtrans, float taupt, int nTrk, bool isMuonTauTrigger){
    float fracW= 0;
    float mymvis = mvis;
    float mymtrans = mtrans;
    if (mymvis>300) mymvis=299;
    if (mymvis<50) mymvis=51;
    if (mymtrans>75) {
        fracW=1.0;
    }
    else{
        /*if (taudecaymode==0){
            fracW=WFR_DM0->GetBinContent(WFR_DM0->GetXaxis()->FindBin(mymtrans),WFR_DM0->GetYaxis()->FindBin(mymvis));
            }
        else if (taudecaymode==1){
            fracW=WFR_DM1->GetBinContent(WFR_DM1->GetXaxis()->FindBin(mymtrans),WFR_DM1->GetYaxis()->FindBin(mymvis));
        }
        else if (taudecaymode==10){
            fracW=WFR_DM10->GetBinContent(WFR_DM10->GetXaxis()->FindBin(mymtrans),WFR_DM10->GetYaxis()->FindBin(mymvis));
        }
        else if (taudecaymode==11){
            fracW=WFR_DM11->GetBinContent(WFR_DM11->GetXaxis()->FindBin(mymtrans),WFR_DM11->GetYaxis()->FindBin(mymvis));
        }*/
        fracW = WFR_allDM->GetBinContent(WFR_allDM->GetXaxis()->FindBin(mymtrans),WFR_allDM->GetYaxis()->FindBin(mymvis));
    }


    /*TF1 *FRQCD_taupt = (TF1*)fFR_mutau->Get(Form("fitfunc_QCD_DM%i_taupt",taudecaymode));
    TF1 *FRW_taupt = (TF1*)fFR_mutau->Get(Form("fitfunc_W_DM%i_taupt",taudecaymode));
    TF1 *FRQCD_nTrk = (TF1*)fFR_mutau->Get(Form("fitfunc_QCD_DM%i_nTrk",taudecaymode));
    TF1 *FRW_nTrk = (TF1*)fFR_mutau->Get(Form("fitfunc_W_DM%i_nTrk",taudecaymode));*/

    float mytaupt = taupt;
    if (taupt>300) mytaupt=299;
    int mynTrk=nTrk;
    if (nTrk>=100) mynTrk=99;
    float tfr_W=1.0;
    float tfr_QCD=1.0;

    float ntrkcut = 20;
    if (taudecaymode==0){
        if (mynTrk<ntrkcut){
            tfr_W=TMath::Min(1.0,FRW_taupt_DM0->Eval(mytaupt)*FRW_lownTrk_DM0->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM0->Eval(mytaupt)*FRQCD_lownTrk_DM0->Eval(mynTrk));
        }
        else{
            tfr_W=TMath::Min(1.0,FRW_taupt_DM0->Eval(mytaupt)*FRW_highnTrk_DM0->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM0->Eval(mytaupt)*FRQCD_highnTrk_DM0->Eval(mynTrk));
        }

    }
    else if (taudecaymode==1){
        if (mynTrk<ntrkcut){
            tfr_W=TMath::Min(1.0,FRW_taupt_DM1->Eval(mytaupt)*FRW_lownTrk_DM1->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM1->Eval(mytaupt)*FRQCD_lownTrk_DM1->Eval(mynTrk));
        }
        else{
            tfr_W=TMath::Min(1.0,FRW_taupt_DM1->Eval(mytaupt)*FRW_highnTrk_DM1->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM1->Eval(mytaupt)*FRQCD_highnTrk_DM1->Eval(mynTrk));
        }
    }
    else if (taudecaymode==10){
        if (mynTrk<ntrkcut){
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM10->Eval(mytaupt)*FRQCD_lownTrk_DM10->Eval(mynTrk));
            tfr_W=TMath::Min(1.0,FRW_taupt_DM10->Eval(mytaupt)*FRW_lownTrk_DM10->Eval(mynTrk));
        }
        else{
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM10->Eval(mytaupt)*FRQCD_highnTrk_DM10->Eval(mynTrk));
            tfr_W=TMath::Min(1.0,FRW_taupt_DM10->Eval(mytaupt)*FRW_highnTrk_DM10->Eval(mynTrk));
        }

    }
    else if (taudecaymode==11){
        if (mynTrk<ntrkcut){
            tfr_W=TMath::Min(1.0,FRW_taupt_DM11->Eval(mytaupt)*FRW_lownTrk_DM11->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM11->Eval(mytaupt)*FRQCD_lownTrk_DM11->Eval(mynTrk));
        }
        else{
            tfr_W=TMath::Min(1.0,FRW_taupt_DM11->Eval(mytaupt)*FRW_highnTrk_DM11->Eval(mynTrk));
            tfr_QCD = TMath::Min(1.0,FRQCD_taupt_DM11->Eval(mytaupt)*FRQCD_highnTrk_DM11->Eval(mynTrk));
        }
    }

    if (isMuonTauTrigger){
        tfr_W*=1.7;
        tfr_QCD*=1.7;
    }
    float tfr=fracW*tfr_W + (1-fracW)*tfr_QCD;
    return tfr;
}



TFile *fFR_tautau = new TFile("FRfit_tautau.root","read");

float GetFR_tautau(int taudecaymode,float taupt, int nTrk){

    TF1 *FRQCD_taupt = (TF1*)fFR_tautau->Get(Form("fitfunc_QCD_DM%i_tau2pt",taudecaymode));
    TF1 *FRQCD_nTrk = (TF1*)fFR_tautau->Get(Form("fitfunc_QCD_DM%i_nTrk",taudecaymode));

    float mytaupt = taupt;
    if (taupt>300) mytaupt=299;
    int mynTrk=nTrk;
    if (nTrk>=100) mynTrk=99;
    float tfr_QCD = TMath::Min(1.0,FRQCD_taupt->Eval(mytaupt)*FRQCD_nTrk->Eval(mynTrk));
    float tfr=tfr_QCD;
    return tfr;
}
