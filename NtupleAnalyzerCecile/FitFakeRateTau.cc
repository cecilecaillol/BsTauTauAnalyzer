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

Double_t fitFunc_Line2Par(Double_t *x, Double_t *par) {
    return par[0] + par[1] * x[0] + par[2] *0;
}

Double_t fitOther(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Landau(x[0],par[2],par[3],0));
}

Double_t fitFlat(Double_t *x, Double_t *par) {
    return par[0];
}

TF1 *M_FR(int WP, std::string type, std::string files, std::string num, std::string denum, TH2F * hist2D_lep, Double_t fMin, Double_t fMax, int year) {
    //SetStyle();
    TFile *inputFile = new TFile(files.c_str());

    TH1D *Numerator = (TH1D*) inputFile->Get(num.c_str());
    TH1D *Denumerator = (TH1D*) inputFile->Get(denum.c_str());

    TH1D *histogram_pass = (TH1D*) Numerator->Rebin(1);
    TH1D *histogram_fail = (TH1D*) Denumerator->Rebin(1);

    makeBinsInteger(histogram_pass, histogram_fail);

    if (num.find("tauFRnt")!=std::string::npos){ // normalize to average FR = 1
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
      theFit->SetParameter(0, 0.2);
      theFit->SetParameter(1, 70);
      theFit->SetParameter(2, -90);
      theFit->SetParameter(3, 10);
    }

    if (year==2018 and num.find("dm10_")!=std::string::npos){
      theFit->SetParameter(0, 0.24);
      theFit->SetParameter(1, -1.4);
      theFit->SetParameter(2, 2410);
      theFit->SetParameter(3, 1630);
    }

    if (year==2018 and num.find("tauFRnt_QCD_")!=std::string::npos){
      theFit->SetParameter(0, 0.54);
      theFit->SetParameter(1, 0.61);
      theFit->SetParameter(2, -1.2);
      theFit->SetParameter(3, 11);
    }

    if (year==2018 and num.find("tauFRnt_W_")!=std::string::npos){
      theFit->SetParameter(0, -0.24);
      theFit->SetParameter(1, 10.7);
      theFit->SetParameter(2, -12);
      theFit->SetParameter(3, 27);
    }

    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 800);
    canvas->SetTitle("");
    canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.00);
    if (num.find("dm10")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm11")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);


    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 3.50);

    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 5000);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetXaxis()->SetTitle("N_{tracks}");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE0");
    TGraph_FR->SetLineWidth(3);
    std::string outNaming = "plots/fit" + num + "_" + denum + ".pdf";
    if (year==2016) outNaming = "plots_tau_2016/fit" + num + "_" + denum + ".pdf";
    if (year==2017) outNaming = "plots_tau_2017/fit" + num + "_" + denum + ".pdf";
    if (year==2018) outNaming = "plots_2018/fit" + num + "_" + denum + ".pdf";
    std::string outNamingPng = "plots/fit" + num + "_" + denum + ".png";
    if (year==2016) outNamingPng = "plots_tau_2016/fit" + num + "_" + denum + ".png";
    if (year==2017) outNamingPng = "plots_tau_2017/fit" + num + "_" + denum + ".png";
    if (year==2018) outNamingPng = "plots_2018/fit" + num + "_" + denum + ".png";
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
   
    TLine *l_high=new TLine(600,theFit->Eval(600),1600,theFit->Eval(600));
    l_high->SetLineColor(6);
    l_high->SetLineWidth(2);
    l_high->Draw("lsame");

    TLine *l_down=new TLine(600,0.7*theFit->Eval(600),1600,0.7*theFit->Eval(600));
    l_down->SetLineColor(6);
    l_down->SetLineWidth(2);
    l_down->SetLineStyle(2);
    l_down->Draw("lsame");

    TLine *l_up=new TLine(600,1.3*theFit->Eval(600),1600,1.3*theFit->Eval(600));
    l_up->SetLineColor(6);
    l_up->SetLineWidth(2);
    l_up->SetLineStyle(2);
    l_up->Draw("lsame");

    canvas->SaveAs(outNaming.c_str());
    canvas->SaveAs(outNamingPng.c_str());

    TFile *FR_H = new TFile("FitHistograms_FR.root", "UPDATE");
    if (year==2016) FR_H = new TFile("FitHistograms_tauFR_2016.root", "UPDATE");
    if (year==2017) FR_H = new TFile("FitHistograms_tauFR_2017.root", "UPDATE");
    if (year==2018) FR_H = new TFile("FitHistograms_tauFR_2018.root", "UPDATE");
    FR_H->cd();
    TGraph_FR->SetName(TString(num) + "_" + TString(denum));
    TGraph_FR->Write();
    FR_H->Close();

    return theFit;
}

void FitFakeRateTau(int year) {

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");
    if (year==2016) FR_File = new TFile("FitValues_tauFR_2016.root", "RECREATE");
    if (year==2017) FR_File = new TFile("FitValues_tauFR_2017.root", "RECREATE");
    if (year==2018) FR_File = new TFile("FitValues_tauFR_2018.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 30;
    Double_t fMax = 300;
    std::string datafile="output_etau_2018/DataSub.root";
    if (year==2016) datafile="output_etau_2016/DataSub.root";
    if (year==2017) datafile="output_etau_2017/DataSub.root";
    if (year==2018) datafile="output_etau_2018/DataSub.root";

    TF1* m101 = M_FR(1, "Exp3Par", datafile, "h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m102 = M_FR(2, "Exp3Par", datafile, "h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m103 = M_FR(3, "Exp3Par", datafile, "h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m104 = M_FR(4, "Exp3Par", datafile, "h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m105 = M_FR(5, "Exp3Par", datafile, "h_tauFR_W_dm0_M","h_tauFR_W_dm0_VVVL", Fit_Value_tau, fMin, 400, year);
    TF1* m106 = M_FR(6, "Exp3Par", datafile, "h_tauFR_W_dm1_M","h_tauFR_W_dm1_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m107 = M_FR(7, "Exp3Par", datafile, "h_tauFR_W_dm10_M","h_tauFR_W_dm10_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m108 = M_FR(8, "Exp3Par", datafile, "h_tauFR_W_dm11_M","h_tauFR_W_dm11_VVVL", Fit_Value_tau, fMin, fMax, year);
    TF1* m109 = M_FR(9, "Flat", datafile, "h_tauFR_QCD_xtrg_M","h_tauFR_QCD_xtrg_VVVL", Fit_Value_tau, 35, fMax, year);
    TF1* m110 = M_FR(10, "Flat", datafile, "h_tauFR_W_xtrg_M","h_tauFR_W_xtrg_VVVL", Fit_Value_tau, 35, fMax, year);

    TF1* m111 = M_FR(11, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 0, 100, year);
    TF1* m112 = M_FR(12, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 0, 100, year);
    TF1* m113 = M_FR(13, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 0, 100, year);
    TF1* m114 = M_FR(14, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 0, 100, year);
    TF1* m115 = M_FR(15, "Exp3Par", datafile, "h_tauFRnt_W_dm0_M","h_tauFRnt_W_dm0_VVVL", Fit_Value_tau, 0, 60, year);
    TF1* m116 = M_FR(16, "Exp3Par", datafile, "h_tauFRnt_W_dm1_M","h_tauFRnt_W_dm1_VVVL", Fit_Value_tau, 0, 80, year);
    TF1* m117 = M_FR(17, "Exp3Par", datafile, "h_tauFRnt_W_dm10_M","h_tauFRnt_W_dm10_VVVL", Fit_Value_tau, 0, 100, year);
    TF1* m118 = M_FR(18, "Exp3Par", datafile, "h_tauFRnt_W_dm11_M","h_tauFRnt_W_dm11_VVVL", Fit_Value_tau, 0, 100, year);

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
    m105->SetName("theFit_W_dm0");
    m105->Write();
    m106->SetName("theFit_W_dm1");
    m106->Write();
    m107->SetName("theFit_W_dm10");
    m107->Write();
    m108->SetName("theFit_W_dm11");
    m108->Write();
    m109->SetName("theFit_QCD_xtrg");
    m109->Write();
    m110->SetName("theFit_W_xtrg");
    m110->Write();

    m111->SetName("theFit_nt_QCD_dm0");
    m111->Write();
    m112->SetName("theFit_nt_QCD_dm1");
    m112->Write();
    m113->SetName("theFit_nt_QCD_dm10");
    m113->Write();
    m114->SetName("theFit_nt_QCD_dm11");
    m114->Write();
    m115->SetName("theFit_nt_W_dm0");
    m115->Write();
    m116->SetName("theFit_nt_W_dm1");
    m116->Write();
    m117->SetName("theFit_nt_W_dm10");
    m117->Write();
    m118->SetName("theFit_nt_W_dm11");
    m118->Write();

    FR_File->Close();
}

