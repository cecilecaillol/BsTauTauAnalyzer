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
    TF1 * theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 15, nPar); //FIXME default 25
    if ((num.find("tauFRnt_W"))!=std::string::npos) theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 10, nPar);
    if ((num.find("tauFRnt_W_dm11"))!=std::string::npos) theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 15, nPar);

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

    if (num.find("tauFRnt_")!=std::string::npos) theFit = new TF1("theFit", fitFunc_Exp3Par2, fMin, fMax, nPar);

    if (num.find("tauFRnt_W")!=std::string::npos) theFit = new TF1("theFit", fitFunc_Line2Par, fMin, fMax, 2);

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
      theFit->SetParameter(0, 7.0);
      theFit->SetParameter(1, -37);
      theFit->SetParameter(2, 99);
      theFit->SetParameter(3, 180);
    }

    if (num.find("W_dm0_")!=std::string::npos){
      theFit->SetParameter(0, 1.8);
      theFit->SetParameter(1, -9);
      theFit->SetParameter(2, 130);
      theFit->SetParameter(3, 240);
    }

    if (num.find("dm10_")!=std::string::npos){
      theFit->SetParameter(0, 0.24);
      theFit->SetParameter(1, -1.4);
      theFit->SetParameter(2, 2410);
      theFit->SetParameter(3, 1630);
    }

    if (num.find("tauFRnt_")!=std::string::npos){
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
    if ((num.find("tauFRnt_QCD_dm0")!=std::string::npos or num.find("tauFRnt_QCD_dm11")!=std::string::npos)){
      theFit2 = new TF1("theFit2", fitFunc_Exp3Par2, 0, 15, nPar); //FIXME
      theFit2->SetParameter(0, 0.56);
      theFit2->SetParameter(1, 1.2);
      theFit2->SetParameter(2, 0.04);
      theFit2->SetParameter(3, -0.16);
std::cout<<"found"<<std::endl;

    }

    if (num.find("tauFRnt_QCD_dm11")!=std::string::npos){
      theFit2->SetParameter(0, 0.0);
      theFit2->SetParameter(1, 1.2);
      theFit2->SetParameter(2, 0.0);
      theFit2->SetParameter(3, 0.0);

    }


    if (num.find("tauFRnt_W")!=std::string::npos){
      theFit->SetParameter(0, 1.5);
      theFit->SetParameter(1, -0.01);
    }

    if (num.find("tauFRnt_W")!=std::string::npos){
      theFit2->SetParameter(0, 1.5);
      theFit2->SetParameter(1, 5.0);
      theFit2->SetParameter(2, 0.6);
      theFit2->SetParameter(3, 0.1);

    }

    float xAxisMax = 500;
    TGraph_FR->Fit("theFit", "R0");

    TCanvas* canvas = new TCanvas("canvas", "", 800, 600);
    canvas->SetTitle("");
    //canvas->SetGrid();
    TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.00);
    if (num.find("dm10")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm11")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 0.30);
    if (num.find("dm0")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 1.5);


    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, 5.00);
    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetYaxis()->SetRangeUser(0.00, TMath::Max(yg[1],yg[2])*1.3);

    TGraph_FR->GetYaxis()->SetTitle("f_{#tau}");
    TGraph_FR->GetXaxis()->SetRangeUser(0, 100);
    TGraph_FR->GetXaxis()->SetTitle("#tau_{h} p_{T} [GeV]");
    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetXaxis()->SetTitle("N_{tracks}");
    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->GetYaxis()->SetTitle("MF correction factor");
    TGraph_FR->SetTitle("");
    TGraph_FR->Draw("PAE0");
    TGraph_FR->SetLineWidth(1);
    TGraph_FR->SetMarkerStyle(20);
    TGraph_FR->GetXaxis()->SetTitleSize(0.06);
    TGraph_FR->GetYaxis()->SetTitleSize(0.06);
    TGraph_FR->GetXaxis()->SetLabelSize(0.05);
    TGraph_FR->GetYaxis()->SetLabelSize(0.05);
    TGraph_FR->GetXaxis()->SetTitleOffset(0.7);
    TGraph_FR->GetYaxis()->SetTitleOffset(0.8);
    std::string outNaming = "plots/fit" + num + "_" + denum + ".pdf";
    if (year==2016) outNaming = "plots_tau_2016/fit" + num + "_" + denum + ".pdf";
    if (year==20161) outNaming = "plots_tau_2016pre/fit" + num + "_" + denum + ".pdf";
    if (year==20162) outNaming = "plots_tau_2016post/fit" + num + "_" + denum + ".pdf";
    if (year==2017) outNaming = "plots_tau_2017/fit" + num + "_" + denum + ".pdf";
    if (year==2018) outNaming = "plots_2018/fit" + num + "_" + denum + ".pdf";
    std::string outNamingPng = "plots/fit" + num + "_" + denum + ".png";
    if (year==2016) outNamingPng = "plots_tau_2016/fit" + num + "_" + denum + ".png";
    if (year==20161) outNamingPng = "plots_tau_2016pre/fit" + num + "_" + denum + ".png";
    if (year==20162) outNamingPng = "plots_tau_2016post/fit" + num + "_" + denum + ".png";
    if (year==2017) outNamingPng = "plots_tau_2017/fit" + num + "_" + denum + ".png";
    if (year==2018) outNamingPng = "plots_2018/fit" + num + "_" + denum + ".png";
    TLatex t = TLatex();
    t.SetNDC();
    t.SetTextFont(42);
    t.SetTextAlign(12);
    t.SetTextSize(0.06);
    if (year==2016) t.DrawLatex(0.55, .95, "36 fb^{-1} (2016, 13 TeV)");
    if (year==20161) t.DrawLatex(0.5, .95, "19 fb^{-1} (2016 preVFP, 13 TeV)");
    if (year==20162) t.DrawLatex(0.5, .95, "16 fb^{-1} (2016 postVFP, 13 TeV)");
    if (year==2017) t.DrawLatex(0.55, .95, "41 fb^{-1} (2017, 13 TeV)");
    if (year==2018) t.DrawLatex(0.55, .95, "60 fb^{-1} (2018, 13 TeV)");
    if (year==0) t.DrawLatex(0.59, .95, "138 fb^{-1} (13 TeV)");

    TLatex t2 = TLatex();
    t2.SetNDC();
    t2.SetTextFont(61);
    t2.SetTextAlign(12);
    t2.SetTextSize(0.08);
    t2.DrawLatex(0.15, .95, "CMS");

    if ((num.find("tauFRnt_")!=std::string::npos)){
       TLatex t3 = TLatex();
       t3.SetNDC();
       t3.SetTextFont(42);
       t3.SetTextAlign(12);
       t3.SetTextSize(0.06);
       if ((num.find("tauFRnt_QCD_dm0_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "SS CR, e#tau_{h}, 1-prong");
       if ((num.find("tauFRnt_QCD_dm1_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "SS CR, e#tau_{h}, 1-prong+#pi^{0}");
       if ((num.find("tauFRnt_QCD_dm10_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "SS CR, e#tau_{h}, 3-prong");
       if ((num.find("tauFRnt_QCD_dm11_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "SS CR, e#tau_{h}, 3-prong+#pi^{0}");
       if ((num.find("tauFRnt_W_dm0_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "High-m_{T} CR, e#tau_{h}, 1-prong");
       if ((num.find("tauFRnt_W_dm1_")!=std::string::npos)) t3.DrawLatex(0.38, .55, "High-m_{T} CR, e#tau_{h}, 1-prong+#pi^{0}");
       if ((num.find("tauFRnt_W_dm10_")!=std::string::npos)) t3.DrawLatex(0.4, .55, "High-m_{T} CR, e#tau_{h}, 3-prong");
       if ((num.find("tauFRnt_W_dm11_")!=std::string::npos)) t3.DrawLatex(0.38, .55, "High-m_{T} CR, e#tau_{h}, 3-prong+#pi^{0}");
    }

    //theFit->Draw("SAME");
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

    if (num.find("tauFRnt")!=std::string::npos) TGraph_FR->Fit("theFit2", "R0");
    //theFit->Draw("SAME");
    if (num.find("tauFRnt")!=std::string::npos) theFit2->Draw("SAME");
    if (num.find("tauFRnt")!=std::string::npos) theFit2->SetLineColor(kMagenta);

    if (num.find("tauFRnt")!=std::string::npos){
      TH1D *hint = new TH1D("hint",
         "Fitted Gaussian with .68 conf.band", 100, 0, 15);
      if (num.find("tauFRnt_W")!=std::string::npos) hint = new TH1D("hint", "Fitted Gaussian with .68 conf.band", 100, 0, 10);
      if (num.find("tauFRnt_W_dm11")!=std::string::npos) hint = new TH1D("hint", "Fitted Gaussian with .68 conf.band", 100, 0, 15);
      (TVirtualFitter::GetFitter())->GetConfidenceIntervals(hint,0.68);
      hint->SetStats(false);
      hint->SetFillColor(kCyan);
      hint->SetFillStyle(3001);
      hint->Draw("e3 same");
      cout<<hint->GetBinContent(1)<<" "<<hint->GetBinError(1)<<endl;
      *err=hint->GetBinError(1)/hint->GetBinContent(1);
    }
    //theFit->Draw("SAME");
    theFit2->Draw("SAME");

    TGraph_FR->Draw("P");

    if (num.find("tauFRnt")==std::string::npos){
       double x[100], yup[100], ydown[100];
       int n = 100;
       for (int i=0;i<n;i++) {
         x[i] = 30+i*2.7;
         yup[i] = theFit->Eval(x[i])*(1.0+((x[i]-30)/540+0.00));
         ydown[i] = theFit->Eval(x[i])*(1.0-((x[i]-30)/540+0.00));
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

void FitFakeRateTau(int year) {

    TFile *FR_File = new TFile("FitValues_FR.root", "RECREATE");
    if (year==2016) FR_File = new TFile("FitValues_tauFR_2016.root", "RECREATE");
    if (year==2017) FR_File = new TFile("FitValues_tauFR_2017.root", "RECREATE");
    if (year==2018) FR_File = new TFile("FitValues_tauFR_2018.root", "RECREATE");
    if (year==20161) FR_File = new TFile("FitValues_tauFR_2016pre.root", "RECREATE");
    if (year==20162) FR_File = new TFile("FitValues_tauFR_2016post.root", "RECREATE");

    TH2F * Fit_Value_tau = new TH2F("Fit_Value_tau", "Fit_Value_tau", 40, 0, 40, 40, 0, 40);

    Double_t fMin = 30;
    Double_t fMax = 300;
    std::string datafile="output_etau_2018/DataSub.root";
    if (year==2016) datafile="output_etau_2016/DataSub.root";
    if (year==2017) datafile="output_etau_2017/DataSub.root";
    if (year==2018) datafile="output_etau_2018/DataSub.root";
    if (year==20161) datafile="output_etau_2016pre/DataSub.root";
    if (year==20162) datafile="output_etau_2016post/DataSub.root";
    if (year==0) datafile="output_etau_all/DataSub.root";

    double *err;
    *err=0.0;
    TH1F *err_nt0_ffW=new TH1F("err_nt0_ffW","err_nt0_ffW",12,0,12);
    TH1F *err_nt0_ffQCD=new TH1F("err_nt0_ffQCD","err_nt0_ffQCD",12,0,12);

    TF1* m101 = M_FR(1, "Exp3Par", datafile, "h_tauFR_QCD_dm0_M","h_tauFR_QCD_dm0_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m102 = M_FR(2, "Exp3Par", datafile, "h_tauFR_QCD_dm1_M","h_tauFR_QCD_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m103 = M_FR(3, "Exp3Par", datafile, "h_tauFR_QCD_dm10_M","h_tauFR_QCD_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m104 = M_FR(4, "Exp3Par", datafile, "h_tauFR_QCD_dm11_M","h_tauFR_QCD_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m105 = M_FR(5, "Exp3Par", datafile, "h_tauFR_W_dm0_M","h_tauFR_W_dm0_VVVL", Fit_Value_tau, fMin, 400, year, 1, err);
    TF1* m106 = M_FR(6, "Exp3Par", datafile, "h_tauFR_W_dm1_M","h_tauFR_W_dm1_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m107 = M_FR(7, "Exp3Par", datafile, "h_tauFR_W_dm10_M","h_tauFR_W_dm10_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m108 = M_FR(8, "Exp3Par", datafile, "h_tauFR_W_dm11_M","h_tauFR_W_dm11_VVVL", Fit_Value_tau, fMin, fMax, year, 1, err);
    TF1* m109 = m108;
    TF1* m110 = m108;
    TF1* m0 = m108;
    TF1* m1 = m108;
    if (year!=20161 and year!=20162){
	m109 = M_FR(9, "Flat", datafile, "h_tauFR_QCD_xtrg_M","h_tauFR_QCD_xtrg_VVVL", Fit_Value_tau, 35, fMax, year, 1, err);
    	m110 = M_FR(10, "Flat", datafile, "h_tauFR_W_xtrg_M","h_tauFR_W_xtrg_VVVL", Fit_Value_tau, 35, fMax, year, 1, err);
    	m0 = M_FR(11111, "Flat", datafile, "h_tauFRpt_QCD_xtrg_M","h_tauFRpt_QCD_xtrg_VVVL", Fit_Value_tau, 35, fMax, year, 1, err);
    	m1 = M_FR(11112, "Flat", datafile, "h_tauFRpt_QCD_etrg_M","h_tauFRpt_QCD_etrg_VVVL", Fit_Value_tau, 35, fMax, year, 1, err);
    }

    TF1* m111 = M_FR(11, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m112 = M_FR(12, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m113 = M_FR(13, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m114 = M_FR(14, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m115 = M_FR(15, "Exp3Par", datafile, "h_tauFRnt_W_dm0_M","h_tauFRnt_W_dm0_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m116 = M_FR(16, "Exp3Par", datafile, "h_tauFRnt_W_dm1_M","h_tauFRnt_W_dm1_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m117 = M_FR(17, "Exp3Par", datafile, "h_tauFRnt_W_dm10_M","h_tauFRnt_W_dm10_VVVL", Fit_Value_tau, 25, 100, year, 1, err);
    TF1* m118 = M_FR(18, "Exp3Par", datafile, "h_tauFRnt_W_dm11_M","h_tauFRnt_W_dm11_VVVL", Fit_Value_tau, 25, 100, year, 1, err);

    TF1* m111_2 = M_FR(21, "Exp3Par", datafile, "h_tauFRnt_QCD_dm0_M","h_tauFRnt_QCD_dm0_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(1,*err);
    TF1* m112_2 = M_FR(22, "Exp3Par", datafile, "h_tauFRnt_QCD_dm1_M","h_tauFRnt_QCD_dm1_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(2,*err);
    TF1* m113_2 = M_FR(23, "Exp3Par", datafile, "h_tauFRnt_QCD_dm10_M","h_tauFRnt_QCD_dm10_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(11,*err);
    TF1* m114_2 = M_FR(24, "Exp3Par", datafile, "h_tauFRnt_QCD_dm11_M","h_tauFRnt_QCD_dm11_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffQCD->SetBinContent(12,*err);
    TF1* m115_2 = M_FR(25, "Exp3Par", datafile, "h_tauFRnt_W_dm0_M","h_tauFRnt_W_dm0_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffW->SetBinContent(1,*err);
    TF1* m116_2 = M_FR(26, "Exp3Par", datafile, "h_tauFRnt_W_dm1_M","h_tauFRnt_W_dm1_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffW->SetBinContent(2,*err);
    TF1* m117_2 = M_FR(27, "Exp3Par", datafile, "h_tauFRnt_W_dm10_M","h_tauFRnt_W_dm10_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffW->SetBinContent(11,*err);
    TF1* m118_2 = M_FR(28, "Exp3Par", datafile, "h_tauFRnt_W_dm11_M","h_tauFRnt_W_dm11_VVVL", Fit_Value_tau, 25, 100, year, 2, err);
    err_nt0_ffW->SetBinContent(12,*err);

    FR_File->Write();
    FR_File->cd();
    err_nt0_ffQCD->Write();
    err_nt0_ffW->Write();
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

    m111_2->SetName("theFit2_nt_QCD_dm0");
    m111_2->Write();
    m112_2->SetName("theFit2_nt_QCD_dm1");
    m112_2->Write();
    m113_2->SetName("theFit2_nt_QCD_dm10");
    m113_2->Write();
    m114_2->SetName("theFit2_nt_QCD_dm11");
    m114_2->Write();
    m115_2->SetName("theFit2_nt_W_dm0");
    m115_2->Write();
    m116_2->SetName("theFit2_nt_W_dm1");
    m116_2->Write();
    m117_2->SetName("theFit2_nt_W_dm10");
    m117_2->Write();
    m118_2->SetName("theFit2_nt_W_dm11");
    m118_2->Write();

    TFile *inputFileX = new TFile(datafile.c_str());
    TH1D *NumeratorQCD = (TH1D*) inputFileX->Get("h_tauFR_QCD_xtrg_M");
    TH1D *DenumeratorQCD = (TH1D*) inputFileX->Get("h_tauFR_QCD_xtrg_VVVL");
    NumeratorQCD->Divide(DenumeratorQCD);

    TH1D *NumeratorW = (TH1D*) inputFileX->Get("h_tauFR_W_xtrg_M");
    TH1D *DenumeratorW = (TH1D*) inputFileX->Get("h_tauFR_W_xtrg_VVVL");
    NumeratorW->Divide(DenumeratorW);

    FR_File->cd();
    NumeratorQCD->Write();
    NumeratorW->Write();

    FR_File->Close();
}

