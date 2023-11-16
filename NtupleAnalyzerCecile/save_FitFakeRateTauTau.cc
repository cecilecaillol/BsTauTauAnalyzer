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

    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos){ // normalize to average FR = 1
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
    TF1 * theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 40, nPar);

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

    if (year==2018 and num.find("tauFRnt_")!=std::string::npos) theFit = new TF1("theFit", fitFunc_Exp3Par2, fMin, fMax, nPar);

    if (year==2018 and num.find("tauFRnt_W")!=std::string::npos) theFit = new TF1("theFit", fitFunc_Line2Par, fMin, fMax, 2);

    /*theFit->SetParameter(0, 0.15);
    theFit->SetParameter(1, 0.0);
    theFit->SetParameter(2, 0.0);
    theFit->SetParameter(3, 0.0);*/

    theFit->SetParameter(0, 0.04);
    theFit->SetParameter(1, 0.7);
    theFit->SetParameter(2, 300);
    theFit->SetParameter(3, 70);

    if (year==2018 and num.find("dm1_")!=std::string::npos){
      theFit->SetParameter(0, 0.7);
      theFit->SetParameter(1, -3.0);
      theFit->SetParameter(2, 191);
      theFit->SetParameter(3, 248);
    }

    if (year==2018 and num.find("dm0_")!=std::string::npos){
      theFit->SetParameter(0, 7.0);
      theFit->SetParameter(1, -37);
      theFit->SetParameter(2, 99);
      theFit->SetParameter(3, 180);
    }

    if (year==2018 and num.find("W_dm0_")!=std::string::npos){
      theFit->SetParameter(0, 1.8);
      theFit->SetParameter(1, -9);
      theFit->SetParameter(2, 130);
      theFit->SetParameter(3, 240);
    }

    if (year==2018 and num.find("dm10_")!=std::string::npos){
      theFit->SetParameter(0, 0.24);
      theFit->SetParameter(1, -1.4);
      theFit->SetParameter(2, 2410);
      theFit->SetParameter(3, 1630);
    }

    if (year==2018 and num.find("tauFRnt_")!=std::string::npos){
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

    if (year==2018 and num.find("tauFRnt_W")!=std::string::npos){
      theFit->SetParameter(0, 1.5);
      theFit->SetParameter(1, -0.01);
    }

    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.00);
    if (num.find("dm10")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm11")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);


    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 3.50);

    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 5000);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos) TGraph_FR->GetXaxis()->SetTitle("N_{tracks}");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE0");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "plots_tautau/fit" + num + "_" + denum + ".pdf";
    if (year==2016) outNaming = "plots_tautau_tau_2016/fit" + num + "_" + denum + ".pdf";
    if (year==2017) outNaming = "plots_tautau_tau_2017/fit" + num + "_" + denum + ".pdf";
    if (year==2018) outNaming = "plots_tautau_2018/fit" + num + "_" + denum + ".pdf";
    std::string outNamingPng = "plots_tautau/fit" + num + "_" + denum + ".png";
    if (year==2016) outNamingPng = "plots_tautau_tau_2016/fit" + num + "_" + denum + ".png";
    if (year==2017) outNamingPng = "plots_tautau_tau_2017/fit" + num + "_" + denum + ".png";
    if (year==2018) outNamingPng = "plots_tautau_2018/fit" + num + "_" + denum + ".png";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.04);
    if (year==2016) t.DrawLatex(0.55, .95, "36 fb^{-1} (2016, 13 TeV)");
    if (year==2017) t.DrawLatex(0.55, .95, "41 fb^{-1} (2017, 13 TeV)");
    if (year==2018) t.DrawLatex(0.55, .95, "60 fb^{-1} (2018, 13 TeV)");

    theFit->Draw("SAME");
    theFit->SetLineColor(2);

    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos){
      TH1D *hint = new TH1D("hint",
         "Fitted Gaussian with .68 conf.band", 100, 0, 100);
      (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint,0.68);
      hint->SetStats(false);
      hint->SetFillColor(kCyan);
      hint->SetFillStyle(3001);
      hint->Draw("e3 same");
    }

    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos) TGraph_FR->Fit("theFit2", "R0");
    theFit->Draw("SAME");
    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos) theFit2->Draw("SAME");
    if (num.find("tauFRnt")!=std::string::npos or num.find("tau1FRnt")!=std::string::npos or num.find("tau2FRnt")!=std::string::npos) theFit2->SetLineColor(3);
   
    canvas->SaveAs(outNaming.c_str());
    canvas->SaveAs(outNamingPng.c_str());

    TFile *FR_H = new TFile("FitHistograms_FR.root", "UPDATE");
    if (year==2016) FR_H = new TFile("FitHistograms_tauFR_2016.root", "UPDATE");
    if (year==2017) FR_H = new TFile("FitHistograms_tauFR_2017.root", "UPDATE");
    if (year==2018) FR_H = new TFile("FitHistograms_tautau_tauFR_2018.root", "UPDATE");
    FR_H->cd();
    TGraph_FR->SetName(TString(num) + "_" + TString(denum));
    TGraph_FR->Write();
    FR_H->Close();

    return theFit;
}

void FitFakeRateTauTau(int year) {

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");
    if (year==2016) FR_File = new TFile("FitValues_tauFR_2016.root", "RECREATE");
    if (year==2017) FR_File = new TFile("FitValues_tauFR_2017.root", "RECREATE");
    if (year==2018) FR_File = new TFile("FitValues_tautau_tauFR_2018.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 30;
    Double_t fMax = 300;
    std::string datafile="output_tautau_2018/DataSub.root";
    if (year==2016) datafile="output_tautau_2016/DataSub.root";
    if (year==2017) datafile="output_tautau_2017/DataSub.root";
    if (year==2018) datafile="output_tautau_2018/DataSub.root";

    double *err;
    *err=0.0;

    TF1* m101 = M_FR(1, "Exp3Par", datafile, "h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m102 = M_FR(2, "Exp3Par", datafile, "h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m103 = M_FR(3, "Exp3Par", datafile, "h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m104 = M_FR(4, "Exp3Par", datafile, "h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);

    TF1* m111 = M_FR(11, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m112 = M_FR(12, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m113 = M_FR(13, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m114 = M_FR(14, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);

    TF1* m201 = M_FR(20, "Exp3Par", datafile, "h_tau1FR_QCD_dm0_M","h_tau1FR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m202 = M_FR(21, "Exp3Par", datafile, "h_tau1FR_QCD_dm1_M","h_tau1FR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m203 = M_FR(22, "Exp3Par", datafile, "h_tau1FR_QCD_dm10_M","h_tau1FR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m204 = M_FR(23, "Exp3Par", datafile, "h_tau1FR_QCD_dm11_M","h_tau1FR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m211 = M_FR(24, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm0_M","h_tau1FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m212 = M_FR(25, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm1_M","h_tau1FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m213 = M_FR(26, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm10_M","h_tau1FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m214 = M_FR(27, "Exp3Par", datafile, "h_tau1FRnt_QCD_dm11_M","h_tau1FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);

    TF1* m301 = M_FR(28, "Exp3Par", datafile, "h_tau2FR_QCD_dm0_M","h_tau2FR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m302 = M_FR(29, "Exp3Par", datafile, "h_tau2FR_QCD_dm1_M","h_tau2FR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m303 = M_FR(30, "Exp3Par", datafile, "h_tau2FR_QCD_dm10_M","h_tau2FR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m304 = M_FR(31, "Exp3Par", datafile, "h_tau2FR_QCD_dm11_M","h_tau2FR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m311 = M_FR(32, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm0_M","h_tau2FRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m312 = M_FR(33, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm1_M","h_tau2FRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m313 = M_FR(34, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm10_M","h_tau2FRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m314 = M_FR(35, "Exp3Par", datafile, "h_tau2FRnt_QCD_dm11_M","h_tau2FRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);

    FR_File->Write();
    FR_File->cd();
    m101->SetName("theFit_QCD_dm0");
    m101->Write();
    m102->SetName("theFit_QCD_dm1");
    m102->Write();
    m103->SetName("theFit_QCD_dm10");
    m103->Write();
    m104->SetName("theFit_QCD_dm11");
    m104->Write();
    m111->SetName("theFit_nt_QCD_dm0");
    m111->Write();
    m112->SetName("theFit_nt_QCD_dm1");
    m112->Write();
    m113->SetName("theFit_nt_QCD_dm10");
    m113->Write();
    m114->SetName("theFit_nt_QCD_dm11");
    m114->Write();

    m201->SetName("theFit1_QCD_dm0");
    m201->Write();
    m202->SetName("theFit1_QCD_dm1");
    m202->Write();
    m203->SetName("theFit1_QCD_dm10");
    m203->Write();
    m204->SetName("theFit1_QCD_dm11");
    m204->Write();
    m211->SetName("theFit1_nt_QCD_dm0");
    m211->Write();
    m212->SetName("theFit1_nt_QCD_dm1");
    m212->Write();
    m213->SetName("theFit1_nt_QCD_dm10");
    m213->Write();
    m214->SetName("theFit1_nt_QCD_dm11");
    m214->Write();

    m301->SetName("theFit2_QCD_dm0");
    m301->Write();
    m302->SetName("theFit2_QCD_dm1");
    m302->Write();
    m303->SetName("theFit2_QCD_dm10");
    m303->Write();
    m304->SetName("theFit2_QCD_dm11");
    m304->Write();
    m311->SetName("theFit2_nt_QCD_dm0");
    m311->Write();
    m312->SetName("theFit2_nt_QCD_dm1");
    m312->Write();
    m313->SetName("theFit2_nt_QCD_dm10");
    m313->Write();
    m314->SetName("theFit2_nt_QCD_dm11");
    m314->Write();

    FR_File->Close();
}

