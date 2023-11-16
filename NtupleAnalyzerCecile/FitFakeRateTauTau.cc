#include <TLatex.h>
#include <TGraph.h>

#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
//#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TMatrixD.h"
#include "TMinuit.h"
#include "TVirtualFitter.h"
#include "TRandom.h"
//#include "HttStyles.h"

double square(double x)
{
  return x*x;
}

void makeBinsInteger(TH1* histogram_pass, TH1* histogram_fail)
{
  assert(histogram_pass->GetNbinsX() == histogram_fail->GetNbinsX());
  int numBins = histogram_pass->GetNbinsX();
  for ( int iBin = 1; iBin <= numBins; ++iBin ) {
    if (histogram_pass->GetBinContent(iBin)<0){ histogram_pass->SetBinContent(iBin,0); histogram_pass->SetBinError(iBin,0);}
    if (histogram_fail->GetBinContent(iBin)<0){ histogram_fail->SetBinContent(iBin,0); histogram_fail->SetBinError(iBin,0);}
    double binContent_sum = histogram_pass->GetBinContent(iBin) + histogram_fail->GetBinContent(iBin);
    double binError2_sum = square(histogram_pass->GetBinError(iBin)) + square(histogram_fail->GetBinError(iBin));
    double binError_sum = TMath::Sqrt(binError2_sum);
    if ( binContent_sum > 0. && binError_sum > 0. ) {
      double nEff = square(binContent_sum/binError_sum);
      double avWeight = binContent_sum/nEff;
      double binContent_pass = TMath::Nint(histogram_pass->GetBinContent(iBin)/avWeight);
      double binError_pass = TMath::Sqrt(binContent_pass);
      histogram_pass->SetBinContent(iBin, binContent_pass);
      histogram_pass->SetBinError(iBin, binError_pass);
      double binContent_fail = TMath::Nint(histogram_fail->GetBinContent(iBin)/avWeight);
      double binError_fail = TMath::Sqrt(binContent_fail);
      histogram_fail->SetBinContent(iBin, binContent_fail);
      histogram_fail->SetBinError(iBin, binError_fail);
    }
  }
}

double fitFunction(double x, double par0, double par1) {
    return par0 + par1 *(x-40);
}

Double_t fitFunc_Exp3Par(Double_t *x, Double_t *par) {
    //return par[0] + par[1]* (x[0]-40);
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
    //return par[0] + par[1]*(TMath::Exp(-(par[2]*x[0]+par[3])));
    //return par[0] + par[1] * x[0] + par[2] * x[0] * x[0] + par[3] * x[0] * x[0] *x[0];
}

Double_t fitFunc_Exp3Par2(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(-(par[2]*x[0]+par[3])));
}

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * x[0];
}

Double_t fitOther(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
}

Double_t fitFlat(Double_t *x, Double_t *par) {
    return par[0];
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax, int year, int myfit, double *err) {
    //SetStyle();
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);

    makeBinsInteger(histogram_pass, histogram_fail);

    if (num.find("nt")!=std::string::npos){ // normalize to average FR = 1
	float ratio=histogram_pass->GetBinContent(1)/histogram_fail->GetBinContent(1);
	for (int j=1; j<histogram_pass->GetSize()-1; ++j){
	    histogram_pass->SetBinContent(j,histogram_pass->GetBinContent(j)/ratio);
            histogram_pass->SetBinError(j,histogram_pass->GetBinError(j)/ratio);
	}
    }

    TGraphAsymmErrors* TGraph_FR = new TGraphAsymmErrors(26);
    TGraph_FR->Divide(histogram_pass, histogram_fail, "pois");

    Double_t *yg = TGraph_FR->GetY();
    for (int i = 0; i<3; i++) printf("yg[%d] = %g\n", i,yg[i]);


    const int nPar = 4; // number of parameters in the fit

    TF1 * theFit = new TF1("theFit", fitFunc_Exp3Par, fMin, fMax, nPar);
    TF1 * theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 25, nPar); //FIXME default 25

    if (type=="Flat"){
      theFit = new TF1("theFit", fitFlat, fMin, fMax, 1);
    }

    if (type=="Other"){
      theFit = new TF1("theFit", fitOther, fMin, fMax, 4);
      theFit->SetParameter(0, 0.16);
      theFit->SetParameter(1, 0.12);
      theFit->SetParameter(2, 0.001);
      theFit->SetParameter(3, 400);
    }

    if (num.find("nt_")!=std::string::npos) theFit = new TF1("theFit", fitFunc_Exp3Par2, fMin, fMax, nPar);

    /*theFit->SetParameter(0, 0.15);
    theFit->SetParameter(1, 0.0);
    theFit->SetParameter(2, 0.0);
    theFit->SetParameter(3, 0.0);*/

    theFit->SetParameter(0, 0.04);
    theFit->SetParameter(1, 0.7);
    theFit->SetParameter(2, 300);
    theFit->SetParameter(3, 70);

    if (num.find("dm1_")!=std::string::npos){
      theFit->SetParameter(0, 0.7);
      theFit->SetParameter(1, -3.0);
      theFit->SetParameter(2, 191);
      theFit->SetParameter(3, 248);
    }

    if (num.find("dm0_")!=std::string::npos){
      theFit->SetParameter(0, 0.6);
      theFit->SetParameter(1, -0.9);
      theFit->SetParameter(2, 83);
      theFit->SetParameter(3, 75);
    }

    if (num.find("dm10_")!=std::string::npos){
      theFit->SetParameter(0, 0.03);
      theFit->SetParameter(1, 0.3);
      theFit->SetParameter(2, 120);
      theFit->SetParameter(3, 344);
      //theFit->SetParLimits(2,0,10);
    }

    if (num.find("nt_")!=std::string::npos){
      /*theFit->SetParameter(0, 0.54);
      theFit->SetParameter(1, 12.6);
      theFit->SetParameter(2, -26);
      theFit->SetParameter(3, 11);*/

      theFit->SetParameter(0, 0.9);
      theFit->SetParameter(1, 1.9);
      theFit->SetParameter(2, 0.04);
      theFit->SetParameter(3, 0.9);

      theFit2->SetParameter(0, 0.9);
      theFit2->SetParameter(1, 1.9);
      theFit2->SetParameter(2, 0.04);
      theFit2->SetParameter(3, 0.9);
    }
    if ((num.find("nt_QCD_dm0")!=std::string::npos or num.find("nt_QCD_dm11")!=std::string::npos)){
      theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 25, nPar); //FIXME
      theFit2->SetParameter(0, 0.56);
      theFit2->SetParameter(1, 1.2);
      theFit2->SetParameter(2, 0.04);
      theFit2->SetParameter(3, -0.16);
std::cout<<"found"<<std::endl;

    }

    if (num.find("nt_QCD_dm11")!=std::string::npos){
      theFit2->SetParameter(0, 0.0);
      theFit2->SetParameter(1, 1.2);
      theFit2->SetParameter(2, 0.0);
      theFit2->SetParameter(3, 0.0);

    }


    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.00);
    if (num.find("dm10")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm11")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm0")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.5);


    if (num.find("nt")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 5.00);

    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 5000);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    if (num.find("nt")!=std::string::npos) TGraph_FR->GetXaxis()->SetTitle("N_{tracks}");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE0");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "plots_tautau_2018/fit" + num + "_" + denum + ".pdf";
    if (year==2016) outNaming = "plots_tautau_2016/fit" + num + "_" + denum + ".pdf";
    if (year==20161) outNaming = "plots_tautau_2016pre/fit" + num + "_" + denum + ".pdf";
    if (year==20162) outNaming = "plots_tautau_2016post/fit" + num + "_" + denum + ".pdf";
    if (year==2017) outNaming = "plots_tautau_2017/fit" + num + "_" + denum + ".pdf";
    if (year==2018) outNaming = "plots_tautau_2018/fit" + num + "_" + denum + ".pdf";
    std::string outNamingPng = "plots_tautau/fit" + num + "_" + denum + ".png";
    if (year==2016) outNamingPng = "plots_tautau_2016/fit" + num + "_" + denum + ".png";
    if (year==20161) outNamingPng = "plots_tautau_2016pre/fit" + num + "_" + denum + ".png";
    if (year==20162) outNamingPng = "plots_tautau_2016post/fit" + num + "_" + denum + ".png";
    if (year==2017) outNamingPng = "plots_tautau_2017/fit" + num + "_" + denum + ".png";
    if (year==2018) outNamingPng = "plots_tautau_2018/fit" + num + "_" + denum + ".png";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    if (year==2016) t.DrawLatex(0.55, .95, "36 fb^{-1} (2016, 13 TeV)");
    if (year==20161) t.DrawLatex(0.5, .95, "19 fb^{-1} (2016 preVFP, 13 TeV)");
    if (year==20162) t.DrawLatex(0.5, .95, "16 fb^{-1} (2016 postVFP, 13 TeV)");
    if (year==2017) t.DrawLatex(0.55, .95, "41 fb^{-1} (2017, 13 TeV)");
    if (year==2018) t.DrawLatex(0.55, .95, "60 fb^{-1} (2018, 13 TeV)");

    theFit->Draw("SAME");
    theFit->SetLineColor(2);

    /*if (num.find("tauFRnt")!=std::string::npos){
      TH1D *hint = new TH1D("hint",
         "Fitted Gaussian with .68 conf.band", 100, 0, 100);
      (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint,0.68);
      hint->SetStats(false);
      hint->SetFillColor(kCyan);
      hint->SetFillStyle(3001);
      hint->Draw("e3 same");
    }*/

    if (num.find("nt")!=std::string::npos) TGraph_FR->Fit("theFit2", "R0");
    theFit->Draw("SAME");
    if (num.find("nt")!=std::string::npos) theFit2->Draw("SAME");
    if (num.find("nt")!=std::string::npos) theFit2->SetLineColor(3);

    if (num.find("nt")!=std::string::npos){
      TH1D *hint = new TH1D("hint",
         "Fitted Gaussian with .68 conf.band", 100, 0, 25);
      (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint,0.68);
      hint->SetStats(false);
      hint->SetFillColor(kCyan);
      hint->SetFillStyle(3001);
      hint->Draw("e3 same");
      cout<<hint->GetBinContent(1)<<" "<<hint->GetBinError(1)<<endl;
      *err=hint->GetBinError(1)/hint->GetBinContent(1);
    }
    theFit->Draw("SAME");
    theFit2->Draw("SAME");

    if (num.find("nt")==std::string::npos){
       double x[100], yup[100], ydown[100];
       int n = 100;
       for (int i=0;i<n;i++) {
         x[i] = 40+i*2.6;
         yup[i] = theFit->Eval(x[i])*(1.0+((x[i]-40)/520+0.00));
         ydown[i] = theFit->Eval(x[i])*(1.0-((x[i]-40)/520+0.00));
       }
       auto gup = new TGraph(n,x,yup);
       gup->SetLineColor(2);
       gup->Draw("CSAME");
       auto gdown = new TGraph(n,x,ydown);
       gdown->SetLineColor(2);
       gdown->Draw("CSAME");
    }
   
    canvas->SaveAs(outNaming.c_str());
    canvas->SaveAs(outNamingPng.c_str());

    TFile *FR_H = new TFile("FitHistograms_FR.root", "UPDATE");
    if (year==2016) FR_H = new TFile("FitHistograms_tauFR_2016.root", "UPDATE");
    if (year==20161) FR_H = new TFile("FitHistograms_tauFR_2016pre.root", "UPDATE");
    if (year==20162) FR_H = new TFile("FitHistograms_tauFR_2016post.root", "UPDATE");
    if (year==2017) FR_H = new TFile("FitHistograms_tauFR_2017.root", "UPDATE");
    if (year==2018) FR_H = new TFile("FitHistograms_tauFR_2018.root", "UPDATE");
    FR_H->cd();
    TGraph_FR->SetName(TString(num) + "_" + TString(denum));
    TGraph_FR->Write();
    FR_H->Close();
    
    if (myfit==2) return theFit2;
    else return theFit;
}

void FitFakeRateTauTau(int year) {

    TFile *FR_File = new TFile("FitValues_tautau_FR.root", "RECREATE");
    if (year==2016) FR_File = new TFile("FitValues_tautau_tauFR_2016.root", "RECREATE");
    if (year==2017) FR_File = new TFile("FitValues_tautau_tauFR_2017.root", "RECREATE");
    if (year==2018) FR_File = new TFile("FitValues_tautau_tauFR_2018.root", "RECREATE");
    if (year==20161) FR_File = new TFile("FitValues_tautau_tauFR_2016pre.root", "RECREATE");
    if (year==20162) FR_File = new TFile("FitValues_tautau_tauFR_2016post.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 40;
    Double_t fMax = 300;
    std::string datafile="output_tautau_2018/DataSub.root";
    if (year==2016) datafile="output_tautau_2016/DataSub.root";
    if (year==2017) datafile="output_tautau_2017/DataSub.root";
    if (year==2018) datafile="output_tautau_2018/DataSub.root";
    if (year==20161) datafile="output_tautau_2016pre/DataSub.root";
    if (year==20162) datafile="output_tautau_2016post/DataSub.root";

    double *err;
    *err=0.0;
    TH1F *err_nt0_ffQCD=new TH1F("err_nt0_ffQCD","err_nt0_ffQCD",12,0,12);

    TF1* m101 = M_FR(1, "Exp3Par", datafile, "h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m102 = M_FR(2, "Exp3Par", datafile, "h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m103 = M_FR(3, "Exp3Par", datafile, "h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m104 = M_FR(4, "Exp3Par", datafile, "h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m105 = M_FR(5, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m106 = M_FR(6, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m107 = M_FR(7, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m108 = M_FR(8, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m109 = M_FR(9, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(1,*err);
    TF1* m110 = M_FR(10, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(2,*err);
    TF1* m111 = M_FR(11, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(11,*err);
    TF1* m112 = M_FR(12, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(12,*err);

    TF1* m113 = M_FR(1, "Exp3Par", datafile, "h_tau1FR_QCD_dm0_M","h_tau1FR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m114 = M_FR(2, "Exp3Par", datafile, "h_tau1FR_QCD_dm1_M","h_tau1FR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m115 = M_FR(3, "Exp3Par", datafile, "h_tau1FR_QCD_dm10_M","h_tau1FR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m116 = M_FR(4, "Exp3Par", datafile, "h_tau1FR_QCD_dm11_M","h_tau1FR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m117 = M_FR(5, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm0_M","h_tau1FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m118 = M_FR(6, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm1_M","h_tau1FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m119 = M_FR(7, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm10_M","h_tau1FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m120 = M_FR(8, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm11_M","h_tau1FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m121 = M_FR(9, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm0_M","h_tau1FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(1,*err);
    TF1* m122 = M_FR(10, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm1_M","h_tau1FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(2,*err);
    TF1* m123 = M_FR(11, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm10_M","h_tau1FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(11,*err);
    TF1* m124 = M_FR(12, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm11_M","h_tau1FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(12,*err);

    TF1* m125 = M_FR(1, "Exp3Par", datafile, "h_tau2FR_QCD_dm0_M","h_tau2FR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m126 = M_FR(2, "Exp3Par", datafile, "h_tau2FR_QCD_dm1_M","h_tau2FR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m127 = M_FR(3, "Exp3Par", datafile, "h_tau2FR_QCD_dm10_M","h_tau2FR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m128 = M_FR(4, "Exp3Par", datafile, "h_tau2FR_QCD_dm11_M","h_tau2FR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m129 = M_FR(5, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm0_M","h_tau2FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m130 = M_FR(6, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm1_M","h_tau2FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m131 = M_FR(7, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm10_M","h_tau2FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m132 = M_FR(8, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm11_M","h_tau2FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m133 = M_FR(9, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm0_M","h_tau2FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(1,*err);
    TF1* m134 = M_FR(10, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm1_M","h_tau2FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(2,*err);
    TF1* m135 = M_FR(11, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm10_M","h_tau2FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(11,*err);
    TF1* m136 = M_FR(12, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm11_M","h_tau2FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(12,*err);

    FR_File->Write();
    FR_File->cd();
    err_nt0_ffQCD->Write();
    m101->SetName("theFit_QCD_dm0");
    m101->Write();
    m102->SetName("theFit_QCD_dm1");
    m102->Write();
    m103->SetName("theFit_QCD_dm10");
    m103->Write();
    m104->SetName("theFit_QCD_dm11");
    m104->Write();
    m105->SetName("theFit_nt_QCD_dm0");
    m105->Write();
    m106->SetName("theFit_nt_QCD_dm1");
    m106->Write();
    m107->SetName("theFit_nt_QCD_dm10");
    m107->Write();
    m108->SetName("theFit_nt_QCD_dm11");
    m108->Write();
    m109->SetName("theFit2_nt_QCD_dm0");
    m109->Write();
    m110->SetName("theFit2_nt_QCD_dm1");
    m110->Write();
    m111->SetName("theFit2_nt_QCD_dm10");
    m111->Write();
    m112->SetName("theFit2_nt_QCD_dm11");
    m112->Write();


    m113->SetName("theFit_QCD1_dm0");
    m113->Write();
    m114->SetName("theFit_QCD1_dm1");
    m114->Write();
    m115->SetName("theFit_QCD1_dm10");
    m115->Write();
    m116->SetName("theFit_QCD1_dm11");
    m116->Write();
    m117->SetName("theFit_nt_QCD1_dm0");
    m117->Write();
    m118->SetName("theFit_nt_QCD1_dm1");
    m118->Write();
    m119->SetName("theFit_nt_QCD1_dm10");
    m119->Write();
    m120->SetName("theFit_nt_QCD1_dm11");
    m120->Write();
    m121->SetName("theFit2_nt_QCD1_dm0");
    m121->Write();
    m122->SetName("theFit2_nt_QCD1_dm1");
    m122->Write();
    m123->SetName("theFit2_nt_QCD1_dm10");
    m123->Write();
    m124->SetName("theFit2_nt_QCD1_dm11");
    m124->Write();


    m125->SetName("theFit_QCD2_dm0");
    m125->Write();
    m126->SetName("theFit_QCD2_dm1");
    m126->Write();
    m127->SetName("theFit_QCD2_dm10");
    m127->Write();
    m128->SetName("theFit_QCD2_dm11");
    m128->Write();
    m129->SetName("theFit_nt_QCD2_dm0");
    m129->Write();
    m130->SetName("theFit_nt_QCD2_dm1");
    m130->Write();
    m131->SetName("theFit_nt_QCD2_dm10");
    m131->Write();
    m132->SetName("theFit_nt_QCD2_dm11");
    m132->Write();
    m133->SetName("theFit2_nt_QCD2_dm0");
    m133->Write();
    m134->SetName("theFit2_nt_QCD2_dm1");
    m134->Write();
    m135->SetName("theFit2_nt_QCD2_dm10");
    m135->Write();
    m136->SetName("theFit2_nt_QCD2_dm11");
    m136->Write();

    TFile *inputFileX = new TFile(datafile.c_str());
    TH1D *Numerator2_dm0= (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm0_M")->Clone();
    TH1D *Denominator2_dm0 = (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm0_VVVL")->Clone();
    float ratio=Numerator2_dm0->GetBinContent(1)/Denominator2_dm0->GetBinContent(1);
    std::cout<<ratio<<std::endl;
    for (int j=1; j<Numerator2_dm0->GetSize()-1; ++j){
        Numerator2_dm0->SetBinContent(j,Numerator2_dm0->GetBinContent(j)/ratio);
        Numerator2_dm0->SetBinError(j,Numerator2_dm0->GetBinError(j)/ratio);
    }
    Numerator2_dm0->Divide(Denominator2_dm0);

    TH1D *Numerator2_dm1= (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm1_M")->Clone();
    TH1D *Denominator2_dm1 = (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm1_VVVL")->Clone();
    ratio=Numerator2_dm1->GetBinContent(1)/Denominator2_dm1->GetBinContent(1);
    for (int j=1; j<Numerator2_dm1->GetSize()-1; ++j){
        Numerator2_dm1->SetBinContent(j,Numerator2_dm1->GetBinContent(j)/ratio);
        Numerator2_dm1->SetBinError(j,Numerator2_dm1->GetBinError(j)/ratio);
    }
    Numerator2_dm1->Divide(Denominator2_dm1);

    TH1D *Numerator2_dm10= (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm10_M")->Clone();
    TH1D *Denominator2_dm10 = (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm10_VVVL")->Clone();
    ratio=Numerator2_dm10->GetBinContent(1)/Denominator2_dm10->GetBinContent(1);
    for (int j=1; j<Numerator2_dm10->GetSize()-1; ++j){
        Numerator2_dm10->SetBinContent(j,Numerator2_dm10->GetBinContent(j)/ratio);
        Numerator2_dm10->SetBinError(j,Numerator2_dm10->GetBinError(j)/ratio);
    }
    Numerator2_dm10->Divide(Denominator2_dm10);

    TH1D *Numerator2_dm11= (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm11_M")->Clone();
    TH1D *Denominator2_dm11 = (TH1D*) inputFileX->Get("h_tau2FRnt_QCD_dm11_VVVL")->Clone();
    ratio=Numerator2_dm11->GetBinContent(1)/Denominator2_dm11->GetBinContent(1);
    for (int j=1; j<Numerator2_dm11->GetSize()-1; ++j){
        Numerator2_dm11->SetBinContent(j,Numerator2_dm11->GetBinContent(j)/ratio);
        Numerator2_dm11->SetBinError(j,Numerator2_dm11->GetBinError(j)/ratio);
    }
    Numerator2_dm11->Divide(Denominator2_dm11);

////////////////////////////////

    TH1D *Numerator1_dm0= (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm0_M")->Clone();
    TH1D *Denominator1_dm0 = (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm0_VVVL")->Clone();
    ratio=Numerator1_dm0->GetBinContent(1)/Denominator1_dm0->GetBinContent(1);
    for (int j=1; j<Numerator1_dm0->GetSize()-1; ++j){
        Numerator1_dm0->SetBinContent(j,Numerator1_dm0->GetBinContent(j)/ratio);
        Numerator1_dm0->SetBinError(j,Numerator1_dm0->GetBinError(j)/ratio);
    }
    Numerator1_dm0->Divide(Denominator1_dm0);

    TH1D *Numerator1_dm1= (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm1_M")->Clone();
    TH1D *Denominator1_dm1 = (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm1_VVVL")->Clone();
    ratio=Numerator1_dm1->GetBinContent(1)/Denominator1_dm1->GetBinContent(1);
    for (int j=1; j<Numerator1_dm1->GetSize()-1; ++j){
        Numerator1_dm1->SetBinContent(j,Numerator1_dm1->GetBinContent(j)/ratio);
        Numerator1_dm1->SetBinError(j,Numerator1_dm1->GetBinError(j)/ratio);
    }
    Numerator1_dm1->Divide(Denominator1_dm1);

    TH1D *Numerator1_dm10= (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm10_M")->Clone();
    TH1D *Denominator1_dm10 = (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm10_VVVL")->Clone();
    ratio=Numerator1_dm10->GetBinContent(1)/Denominator1_dm10->GetBinContent(1);
    for (int j=1; j<Numerator1_dm10->GetSize()-1; ++j){
        Numerator1_dm10->SetBinContent(j,Numerator1_dm10->GetBinContent(j)/ratio);
        Numerator1_dm10->SetBinError(j,Numerator1_dm10->GetBinError(j)/ratio);
    }
    Numerator1_dm10->Divide(Denominator1_dm10);

    TH1D *Numerator1_dm11= (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm11_M")->Clone();
    TH1D *Denominator1_dm11 = (TH1D*) inputFileX->Get("h_tau1FRnt_QCD_dm11_VVVL")->Clone();
    ratio=Numerator1_dm11->GetBinContent(1)/Denominator1_dm11->GetBinContent(1);
    for (int j=1; j<Numerator1_dm11->GetSize()-1; ++j){
        Numerator1_dm11->SetBinContent(j,Numerator1_dm11->GetBinContent(j)/ratio);
        Numerator1_dm11->SetBinError(j,Numerator1_dm11->GetBinError(j)/ratio);
    }
    Numerator1_dm11->Divide(Denominator1_dm11);

    FR_File->cd();
    Numerator1_dm0->Write();
    Numerator1_dm1->Write();
    Numerator1_dm10->Write();
    Numerator1_dm11->Write();
    Numerator2_dm0->Write();
    Numerator2_dm1->Write();
    Numerator2_dm10->Write();
    Numerator2_dm11->Write();

    FR_File->Close();
}

